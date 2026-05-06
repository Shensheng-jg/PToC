#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "semantic.h"

#define HASH_SIZE 0x3fff

int semantic_error_count = 0;

static char *xstrdup(const char *s){
    if(s == NULL) return NULL;
    char *p = (char *)malloc(strlen(s) + 1);
    if(!p){
        perror("malloc");
        exit(1);
    }
    strcpy(p, s);
    return p;
}

static Node *child(Node *node, int k){
    Node *p = node ? node->first_child :NULL;
    while(p && k > 0){
        p = p->next_sibling;
        k--;
    }
    return p;
}

static int is_token(Node *node, const char *name){
    return node && node->is_token && strcmp(node->name, name) == 0;
}

static int is_nonterm(Node *node, const char *name){
    return node && !node->is_token && strcmp(node->name, name) == 0;
}

static void semantic_error(int type, int line, const char *fmt, ...){
    va_list ap;
    printf("Error type %d at Line %d: ", type, line);
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    printf("\n");
    semantic_error_count++;
}

typedef struct Type_ *Type;
typedef struct FieldList_ *FieldList;
typedef struct Symbol_ Symbol;
typedef struct Scope_ Scope;

struct Type_ {
    enum { BASIC, ARRAY, STRUCTURE, FUNCTION }kind;
    union {
        int basic;
        struct{
            Type elem;
            int size;
        }array;
        struct {
            char *name;      /* 结构体名；匿名结构体也给隐藏名 */
            FieldList fields;
        } structure;
        struct {
            Type ret;
            FieldList params;
            int param_count;
        } function;
    } u;
};

struct FieldList_ {
    char *name;
    Type type;
    FieldList tail;
};

typedef enum { SYM_VAR, SYM_FUNC, SYM_STRUCT } SymbolKind;

struct Symbol_ {
    char *name;
    SymbolKind kind;
    Type type;
    int depth;
    Symbol *hash_next;
    Symbol *scope_next;
};

struct Scope_ {
    Symbol *symbols;
    Scope *prev;
    int depth;
};

typedef struct ExpInfo_ {
    Type type;
    int is_lvalue;
} ExpInfo;


static unsigned hash_pjw(const char *name) {
    unsigned val = 0, i;
    for(; *name; ++name){
        val = (val << 2) + (unsigned char)(*name);
        if((i = val & ~HASH_SIZE)) val = (val ^ (i >> 12)) & HASH_SIZE;
    }
    return val;
}

static Symbol *hash_table[HASH_SIZE + 1];
static Scope *current_scope = NULL;
static int current_depth = -1;
static int anonymous_struct_id = 0;


static Type new_type_basic(int basic){
    Type t = (Type)malloc(sizeof(*t));
    t->kind = BASIC;
    t->u.basic = basic;
    return t;
}

static Type new_type_array(Type elem, int size) {
    Type t = (Type)malloc(sizeof(*t));
    t->kind = ARRAY;
    t->u.array.elem = elem;
    t->u.array.size = size;
    return t;
}

static Type new_type_structure(const char *name, FieldList fields) {
    Type t = (Type)malloc(sizeof(*t));
    t->kind = STRUCTURE;
    t->u.structure.name = xstrdup(name);
    t->u.structure.fields = fields;
    return t;
}

static Type new_type_function(Type ret, FieldList params, int param_count){
    Type t = (Type)malloc(sizeof(*t));
    t->kind = FUNCTION;
    t->u.function.ret = ret;
    t->u.function.params = params;
    t->u.function.param_count = param_count;
    return t;
}

static FieldList new_field(const char *name, Type type){
    FieldList f = (FieldList)malloc(sizeof(*f));
    f->name = xstrdup(name);
    f->type = type;
    f->tail = NULL;
    return f;
}

static char *new_anonymous_struct_name(void){
    char buf[64];
    sprintf(buf, "anon_struct_%d", ++anonymous_struct_id);
    return xstrdup(buf);
}

static int type_equal(Type a, Type b) {
    if (a == NULL || b == NULL) return 0;
    if (a->kind != b->kind) return 0;

    switch (a->kind) {
    case BASIC:
        return a->u.basic == b->u.basic;

    case ARRAY:
        return type_equal(a->u.array.elem, b->u.array.elem);

    case STRUCTURE:
        return strcmp(a->u.structure.name, b->u.structure.name) == 0;

    case FUNCTION: {
        if (!type_equal(a->u.function.ret, b->u.function.ret)) return 0;
        if (a->u.function.param_count != b->u.function.param_count) return 0;
        FieldList p = a->u.function.params;
        FieldList q = b->u.function.params;
        while (p && q) {
            if (!type_equal(p->type, q->type)) return 0;
            p = p->tail;
            q = q->tail;
        }
        return p == NULL && q == NULL;
    }
    }
    return 0;
}

static void enter_scope(void) {
    Scope *s = (Scope *)malloc(sizeof(*s));
    s->symbols = NULL;
    s->prev = current_scope;
    s->depth = ++current_depth;
    current_scope = s;
}

static void leave_scope(void){
    if(!current_scope) return;
    Symbol *p = current_scope->symbols;
    while(p){
        unsigned h = hash_pjw(p->name);
        Symbol *cur = hash_table[h];
        Symbol *pre = NULL;
        while(cur){
            if(cur == p){
                if(pre) pre->hash_next = cur->hash_next;
                else hash_table[h] = cur->hash_next;
                break;
            }
            pre = cur;
            cur = cur->hash_next;
        }
        p = p->scope_next;
    }
    Scope *old = current_scope;
    current_scope = current_scope->prev;
    free(old);
    current_depth--;

}

static Symbol *new_symbol(const char *name, SymbolKind kind, Type type) {
    Symbol *s = (Symbol *)malloc(sizeof(*s));
    s->name = xstrdup(name);
    s->kind = kind;
    s->type = type;
    s->depth = current_depth;
    s->hash_next = NULL;
    s->scope_next = NULL;
    return s;
}

static void insert_symbol(Symbol *sym) {
    unsigned h = hash_pjw(sym->name);
    sym->hash_next = hash_table[h];
    hash_table[h] = sym;

    sym->scope_next = current_scope->symbols;
    current_scope->symbols = sym;
}

static Symbol *lookup_innermost(const char *name) {
    unsigned h = hash_pjw(name);
    Symbol *p = hash_table[h];
    while (p) {
        if (strcmp(p->name, name) == 0) return p;
        p = p->hash_next;
    }
    return NULL;
}

static Symbol *lookup_kind(const char *name, SymbolKind kind) {
    unsigned h = hash_pjw(name);
    Symbol *p = hash_table[h];
    while (p) {
        if (strcmp(p->name, name) == 0 && p->kind == kind) return p;
        p = p->hash_next;
    }
    return NULL;
}

static Symbol *lookup_current_scope(const char *name, SymbolKind kind) {
    if (!current_scope) return NULL;
    Symbol *p = current_scope->symbols;
    while (p) {
        if (p->kind == kind && strcmp(p->name, name) == 0) return p;
        p = p->scope_next;
    }
    return NULL;
}

static int current_scope_has_name(const char *name) {
    if (!current_scope) return 0;
    Symbol *p = current_scope->symbols;
    while (p) {
        if (strcmp(p->name, name) == 0) return 1;
        p = p->scope_next;
    }
    return 0;
}

/* =========================
 * 前置声明
 * ========================= */
static void analyze_Program(Node *node);
static void analyze_ExtDefList(Node *node);
static void analyze_ExtDef(Node *node);
static Type analyze_Specifier(Node *node);
static Type analyze_StructSpecifier(Node *node);
static Type build_VarDec_type(Node *node, Type base, char **out_name);
static FieldList analyze_VarList(Node *node, int *param_count);
static void analyze_CompSt(Node *node, Type ret_type, int create_scope);
static void analyze_DefList(Node *node, int in_struct, FieldList *fields_out);
static void analyze_Def(Node *node, int in_struct, FieldList *fields_out);
static void analyze_DecList(Node *node, Type spec_type, int in_struct, FieldList *fields_out);
static void analyze_Dec(Node *node, Type spec_type, int in_struct, FieldList *fields_out);
static void analyze_StmtList(Node *node, Type ret_type);
static void analyze_Stmt(Node *node, Type ret_type);
static ExpInfo analyze_Exp(Node *node);
static FieldList analyze_Args(Node *node, int *argc);
static FieldList build_VarList_fields(Node *node, int *param_count);

/* =========================
 * 表达式辅助
 * ========================= */
static ExpInfo make_exp(Type t, int lv) {
    ExpInfo x;
    x.type = t;
    x.is_lvalue = lv;
    return x;
}

static int is_int(Type t) {
    return t && t->kind == BASIC && t->u.basic == 0;
}

static int is_float(Type t) {
    return t && t->kind == BASIC && t->u.basic == 1;
}

static int is_numeric(Type t) {
    return is_int(t) || is_float(t);
}

static FieldList find_field(FieldList f, const char *name) {
    while (f) {
        if (strcmp(f->name, name) == 0) return f;
        f = f->tail;
    }
    return NULL;
}

static FieldList append_field(FieldList head, FieldList node) {
    if (!head) return node;
    FieldList p = head;
    while (p->tail) p = p->tail;
    p->tail = node;
    return head;
}

/* =========================
 * Program / ExtDef
 * ========================= */
static void insert_builtin_functions(void) {
    /* int read() */
    Type read_type = new_type_function(new_type_basic(0), NULL, 0);
    insert_symbol(new_symbol("read", SYM_FUNC, read_type));

    /* int write(int) */
    FieldList write_param = new_field("x", new_type_basic(0));
    Type write_type = new_type_function(new_type_basic(0), write_param, 1);
    insert_symbol(new_symbol("write", SYM_FUNC, write_type));
}

void semantic_analyze(Node *root) {
    memset(hash_table, 0, sizeof(hash_table));
    semantic_error_count = 0;
    current_scope = NULL;
    current_depth = -1;
    anonymous_struct_id = 0;

    enter_scope();
    insert_builtin_functions();
    analyze_Program(root);
    leave_scope();
}

static void analyze_Program(Node *node) {
    if (!node) return;
    analyze_ExtDefList(child(node, 0));
}

static void analyze_ExtDefList(Node *node) {
    if (!node) return;
    analyze_ExtDef(child(node, 0));
    analyze_ExtDefList(child(node, 1));
}

static void analyze_ExtDef(Node *node) {
    if (!node) return;

    Node *a = child(node, 0);
    Node *b = child(node, 1);
    Node *c = child(node, 2);

    /* ExtDef -> Specifier ExtDecList SEMI */
    if (a && b && c && is_nonterm(a, "Specifier") && is_nonterm(b, "ExtDecList")) {
        Type spec_type = analyze_Specifier(a);

        Node *p = b;
        while (p) {
            Node *v = child(p, 0);
            char *name = NULL;
            Type var_type = build_VarDec_type(v, spec_type, &name);

            if (name) {
                if (lookup_current_scope(name, SYM_VAR)) {
                    semantic_error(3, v->line, "Redefined variable \"%s\".", name);
                } else if (lookup_kind(name, SYM_STRUCT)) {
                    semantic_error(3, v->line, "Redefined variable \"%s\".", name);
                } else {
                    insert_symbol(new_symbol(name, SYM_VAR, var_type));
                }
            }

            if (child(p, 2)) p = child(p, 2);
            else break;
        }
        return;
    }

    /* ExtDef -> Specifier SEMI */
    if (a && b && !c && is_nonterm(a, "Specifier") && is_token(b, "SEMI")) {
        (void)analyze_Specifier(a);
        return;
    }

    /* ExtDef -> Specifier FunDec CompSt */
    if (a && b && c && is_nonterm(a, "Specifier") && is_nonterm(b, "FunDec") && is_nonterm(c, "CompSt")) {
        Type ret_type = analyze_Specifier(a);

        Node *idnode = child(b, 0);
        char *fname = idnode->text;

        int param_count = 0;
        FieldList params = NULL;

        if (child(b, 2) && is_nonterm(child(b, 2), "VarList")) {
            params = build_VarList_fields(child(b, 2), &param_count);
        }

        Type ftype = new_type_function(ret_type, params, param_count);

        Symbol *oldf = lookup_current_scope(fname, SYM_FUNC);
        if (oldf) {
            semantic_error(4, idnode->line, "Redefined function \"%s\".", fname);
        } else {
            insert_symbol(new_symbol(fname, SYM_FUNC, ftype));
        }

        /* 真正进入函数体作用域，只分析一次形参 */
        enter_scope();
        if (child(b, 2) && is_nonterm(child(b, 2), "VarList")) {
            int dummy = 0;
            (void)analyze_VarList(child(b, 2), &dummy);
        }
        analyze_CompSt(c, ret_type, 0);
        leave_scope();
        return;
    }
}

/* =========================
 * Specifier / StructSpecifier
 * ========================= */
static Type analyze_Specifier(Node *node) {
    Node *c0 = child(node, 0);
    if (is_token(c0, "TYPE")) {
        if (strcmp(c0->text, "int") == 0) return new_type_basic(0);
        return new_type_basic(1);
    }
    return analyze_StructSpecifier(c0);
}

static Type analyze_StructSpecifier(Node *node) {
    Node *c0 = child(node, 0);
    Node *c1 = child(node, 1);

    /* STRUCT Tag */
    if (c0 && c1 && is_nonterm(c1, "Tag")) {
        Node *idnode = child(c1, 0);
        Symbol *s = lookup_kind(idnode->text, SYM_STRUCT);
        if (!s) {
            semantic_error(17, idnode->line, "Undefined structure \"%s\".", idnode->text);
            return new_type_structure("#undefined", NULL);
        }
        return s->type;
    }

    /* STRUCT OptTag LC DefList RC
       或 STRUCT LC DefList RC（OptTag 为空时） */
    char *sname = NULL;
    Node *deflist = NULL;

    if (c1 && is_nonterm(c1, "OptTag")) {
        if (child(c1, 0)) {
            sname = child(c1, 0)->text;
        }
        deflist = child(node, 3);   /* STRUCT OptTag LC DefList RC */
    } else {
        deflist = child(node, 2);   /* STRUCT LC DefList RC */
    }

    if (!sname) {
        sname = new_anonymous_struct_name();
    } else {
        if (lookup_kind(sname, SYM_STRUCT) || lookup_kind(sname, SYM_VAR)) {
            semantic_error(16, node->line, "Duplicated name \"%s\".", sname);
        }
    }

    FieldList fields = NULL;
    analyze_DefList(deflist, 1, &fields);

    Type stype = new_type_structure(sname, fields);

    /* 只有具名结构体才登记到符号表 */
    if (c1 && is_nonterm(c1, "OptTag") && child(c1, 0)) {
        if (!lookup_kind(sname, SYM_STRUCT) && !lookup_kind(sname, SYM_VAR)) {
            insert_symbol(new_symbol(sname, SYM_STRUCT, stype));
        }
    }

    return stype;
}

/* =========================
 * VarDec / VarList
 * ========================= */
static Type build_VarDec_type(Node *node, Type base, char **out_name) {
    Node *c0 = child(node, 0);
    Node *c1 = child(node, 1);

    if (c0 && is_token(c0, "ID") && !c1) {
        *out_name = c0->text;
        return base;
    }

    /* VarDec -> VarDec LB INT RB */
    if (c0 && c1) {
        Type inner = build_VarDec_type(c0, base, out_name);
        Node *intnode = child(node, 2);
        int size = intnode ? atoi(intnode->text) : 0;
        return new_type_array(inner, size);
    }

    *out_name = NULL;
    return base;
}

static FieldList analyze_VarList(Node *node, int *param_count) {
    if (!node) return NULL;

    /* VarList -> ParamDec COMMA VarList | ParamDec */
    Node *param = child(node, 0);
    Node *rest = child(node, 2);

    Node *spec = child(param, 0);
    Node *vardec = child(param, 1);

    Type spec_type = analyze_Specifier(spec);
    char *name = NULL;
    Type var_type = build_VarDec_type(vardec, spec_type, &name);

    if (name) {
        if (current_scope_has_name(name)) {
            semantic_error(3, vardec->line, "Redefined variable \"%s\".", name);
        } else {
            if (lookup_kind(name, SYM_STRUCT)) {
                semantic_error(3, vardec->line, "Redefined variable \"%s\".", name);
            }
            insert_symbol(new_symbol(name, SYM_VAR, var_type));
        }
    }

    FieldList head = new_field(name ? name : "#param", var_type);
    (*param_count)++;

    if (rest) {
        head->tail = analyze_VarList(rest, param_count);
    }
    return head;
}

/* =========================
 * CompSt / Def / Stmt
 * ========================= */
static void analyze_CompSt(Node *node, Type ret_type, int create_scope) {
    if (!node) return;
    if (create_scope) enter_scope();

    Node *p = child(node, 1);   // 跳过 LC

    if (p && is_nonterm(p, "DefList")) {
        analyze_DefList(p, 0, NULL);
        p = p->next_sibling;
    }

    if (p && is_nonterm(p, "StmtList")) {
        analyze_StmtList(p, ret_type);
    }

    if (create_scope) leave_scope();
}

static void analyze_DefList(Node *node, int in_struct, FieldList *fields_out) {
    if (!node) return;
    analyze_Def(child(node, 0), in_struct, fields_out);
    analyze_DefList(child(node, 1), in_struct, fields_out);
}

static void analyze_Def(Node *node, int in_struct, FieldList *fields_out) {
    if (!node) return;
    Type spec_type = analyze_Specifier(child(node, 0));
    analyze_DecList(child(node, 1), spec_type, in_struct, fields_out);
}

static void analyze_DecList(Node *node, Type spec_type, int in_struct, FieldList *fields_out) {
    if (!node) return;
    analyze_Dec(child(node, 0), spec_type, in_struct, fields_out);
    if (child(node, 2)) analyze_DecList(child(node, 2), spec_type, in_struct, fields_out);
}

static void analyze_Dec(Node *node, Type spec_type, int in_struct, FieldList *fields_out) {
    if (!node) return;

    Node *vardec = child(node, 0);
    Node *assignop = child(node, 1);
    Node *exp = child(node, 2);

    char *name = NULL;
    Type var_type = build_VarDec_type(vardec, spec_type, &name);

    if (in_struct) {
        if (assignop) {
            semantic_error(15, node->line, "Initialize field \"%s\" when defining struct.", name ? name : "");
        }
        if (fields_out) {
            if (find_field(*fields_out, name)) {
                semantic_error(15, vardec->line, "Redefined field \"%s\".", name);
            } else {
                *fields_out = append_field(*fields_out, new_field(name, var_type));
            }
        }
        return;
    }

    if (name) {
        if (current_scope_has_name(name)) {
            semantic_error(3, vardec->line, "Redefined variable \"%s\".", name);
        } else if (lookup_kind(name, SYM_STRUCT)) {
            semantic_error(3, vardec->line, "Redefined variable \"%s\".", name);
        } else {
            insert_symbol(new_symbol(name, SYM_VAR, var_type));
        }
    }

    if (assignop && exp) {
        ExpInfo rhs = analyze_Exp(exp);
        if (rhs.type && !type_equal(var_type, rhs.type)) {
            semantic_error(5, node->line, "Type mismatched for assignment.");
        }
    }
}

static void analyze_StmtList(Node *node, Type ret_type) {
    if (!node) return;
    analyze_Stmt(child(node, 0), ret_type);
    analyze_StmtList(child(node, 1), ret_type);
}

static void analyze_Stmt(Node *node, Type ret_type) {
    if (!node) return;

    Node *c0 = child(node, 0);
    Node *c1 = child(node, 1);
    Node *c2 = child(node, 2);
    Node *c4 = child(node, 4);

    /* Stmt -> Exp SEMI */
    if (c0 && is_nonterm(c0, "Exp") && c1 && is_token(c1, "SEMI")) {
        analyze_Exp(c0);
        return;
    }

    /* Stmt -> CompSt */
    if (c0 && is_nonterm(c0, "CompSt")) {
        analyze_CompSt(c0, ret_type, 1);
        return;
    }

    /* RETURN Exp SEMI */
    if (c0 && is_token(c0, "RETURN")) {
        ExpInfo x = analyze_Exp(c1);
        if (x.type && !type_equal(x.type, ret_type)) {
            semantic_error(8, node->line, "Type mismatched for return.");
        }
        return;
    }

    /* IF LP Exp RP Stmt */
    if (c0 && is_token(c0, "IF") && c4 && !child(node, 5)) {
        ExpInfo cond = analyze_Exp(c2);
        if (cond.type && !is_int(cond.type)) {
            semantic_error(7, c2->line, "Type mismatched for operands.");
        }
        analyze_Stmt(c4, ret_type);
        return;
    }

    /* IF LP Exp RP Stmt ELSE Stmt */
    if (c0 && is_token(c0, "IF") && child(node, 5)) {
        ExpInfo cond = analyze_Exp(c2);
        if (cond.type && !is_int(cond.type)) {
            semantic_error(7, c2->line, "Type mismatched for operands.");
        }
        analyze_Stmt(c4, ret_type);
        analyze_Stmt(child(node, 6), ret_type);
        return;
    }

    /* WHILE LP Exp RP Stmt */
    if (c0 && is_token(c0, "WHILE")) {
        ExpInfo cond = analyze_Exp(c2);
        if (cond.type && !is_int(cond.type)) {
            semantic_error(7, c2->line, "Type mismatched for operands.");
        }
        analyze_Stmt(c4, ret_type);
        return;
    }
}

/* =========================
 * Args
 * ========================= */
static FieldList analyze_Args(Node *node, int *argc) {
    if (!node) return NULL;

    Node *e = child(node, 0);
    ExpInfo x = analyze_Exp(e);
    FieldList head = new_field("#arg", x.type);
    (*argc)++;

    if (child(node, 2)) {
        head->tail = analyze_Args(child(node, 2), argc);
    }
    return head;
}

/* =========================
 * Exp
 * ========================= */
static ExpInfo analyze_Exp(Node *node) {
    if (!node) return make_exp(NULL, 0);

    Node *c0 = child(node, 0);
    Node *c1 = child(node, 1);
    Node *c2 = child(node, 2);
    Node *c3 = child(node, 3);

    /* ID / INT / FLOAT */
    if (c0 && !c1) {
        if (is_token(c0, "ID")) {
            Symbol *s = lookup_kind(c0->text, SYM_VAR);
            if (!s) {
                semantic_error(1, c0->line, "Undefined variable \"%s\".", c0->text);
                return make_exp(NULL, 0);
            }
            return make_exp(s->type, 1);
        }
        if (is_token(c0, "INT")) return make_exp(new_type_basic(0), 0);
        if (is_token(c0, "FLOAT")) return make_exp(new_type_basic(1), 0);
    }

    /* LP Exp RP */
    if (c0 && is_token(c0, "LP")) {
        ExpInfo x = analyze_Exp(c1);
        return make_exp(x.type, 0);
    }

    /* MINUS Exp */
    if (c0 && is_token(c0, "MINUS") && c1 && !c2) {
        ExpInfo x = analyze_Exp(c1);
        if (x.type && !is_numeric(x.type)) {
            semantic_error(7, node->line, "Type mismatched for operands.");
            return make_exp(NULL, 0);
        }
        return make_exp(x.type, 0);
    }

    /* NOT Exp */
    if (c0 && is_token(c0, "NOT")) {
        ExpInfo x = analyze_Exp(c1);
        if (x.type && !is_int(x.type)) {
            semantic_error(7, node->line, "Type mismatched for operands.");
            return make_exp(NULL, 0);
        }
        return make_exp(new_type_basic(0), 0);
    }

    /* ID LP RP */
    if (c0 && is_token(c0, "ID") && c1 && is_token(c1, "LP") && c2 && is_token(c2, "RP")) {
        Symbol *f = lookup_kind(c0->text, SYM_FUNC);
        if (!f) {
            Symbol *x = lookup_kind(c0->text, SYM_VAR);
            if (x) {
                semantic_error(11, c0->line, "\"%s\" is not a function.", c0->text);
            } else {
                semantic_error(2, c0->line, "Undefined function \"%s\".", c0->text);
            }
            return make_exp(NULL, 0);
        }
        if (f->type->u.function.param_count != 0) {
            semantic_error(9, node->line, "Function \"%s\" is not applicable for arguments.", c0->text);
            return make_exp(f->type->u.function.ret, 0);
        }
        return make_exp(f->type->u.function.ret, 0);
    }

    /* ID LP Args RP */
    if (c0 && is_token(c0, "ID") && c1 && is_token(c1, "LP") && c2 && is_nonterm(c2, "Args")) {
        Symbol *f = lookup_kind(c0->text, SYM_FUNC);
        if (!f) {
            Symbol *x = lookup_kind(c0->text, SYM_VAR);
            if (x) {
                semantic_error(11, c0->line, "\"%s\" is not a function.", c0->text);
            } else {
                semantic_error(2, c0->line, "Undefined function \"%s\".", c0->text);
            }
            analyze_Args(c2, &(int){0});
            return make_exp(NULL, 0);
        }

        int argc = 0;
        FieldList args = analyze_Args(c2, &argc);

        if (argc != f->type->u.function.param_count) {
            semantic_error(9, node->line, "Function \"%s\" is not applicable for arguments.", c0->text);
            return make_exp(f->type->u.function.ret, 0);
        }

        FieldList p = f->type->u.function.params;
        FieldList q = args;
        while (p && q) {
            if (!type_equal(p->type, q->type)) {
                semantic_error(9, node->line, "Function \"%s\" is not applicable for arguments.", c0->text);
                break;
            }
            p = p->tail;
            q = q->tail;
        }
        return make_exp(f->type->u.function.ret, 0);
    }

    /* Exp LB Exp RB */
    if (c0 && is_nonterm(c0, "Exp") && c1 && is_token(c1, "LB")) {
        ExpInfo arr = analyze_Exp(c0);
        ExpInfo idx = analyze_Exp(c2);

        if (arr.type && arr.type->kind != ARRAY) {
            semantic_error(10, node->line, "Not an array.");
            return make_exp(NULL, 0);
        }
        if (idx.type && !is_int(idx.type)) {
            semantic_error(12, node->line, "Array index is not an integer.");
            return make_exp(NULL, 0);
        }
        if (arr.type && arr.type->kind == ARRAY) {
            return make_exp(arr.type->u.array.elem, 1);
        }
        return make_exp(NULL, 0);
    }

    /* Exp DOT ID */
    if (c0 && is_nonterm(c0, "Exp") && c1 && is_token(c1, "DOT")) {
        ExpInfo st = analyze_Exp(c0);

        if (st.type && st.type->kind != STRUCTURE) {
            semantic_error(13, node->line, "Illegal use of \".\".");
            return make_exp(NULL, 0);
        }
        if (st.type && st.type->kind == STRUCTURE) {
            FieldList f = find_field(st.type->u.structure.fields, c2->text);
            if (!f) {
                semantic_error(14, c2->line, "Non-existent field \"%s\".", c2->text);
                return make_exp(NULL, 0);
            }
            return make_exp(f->type, 1);
        }
        return make_exp(NULL, 0);
    }

    /* 二元运算 */
    if (c0 && c1 && c2 && is_nonterm(c0, "Exp") && is_nonterm(c2, "Exp")) {
        ExpInfo lhs = analyze_Exp(c0);
        ExpInfo rhs = analyze_Exp(c2);

        /* ASSIGNOP */
        if (is_token(c1, "ASSIGNOP")) {
            if (lhs.type != NULL && !lhs.is_lvalue) {
                semantic_error(6, node->line, "The left-hand side of an assignment must be a variable.");
                return make_exp(lhs.type, 0);
            }
            if (lhs.type && rhs.type && !type_equal(lhs.type, rhs.type)) {
                semantic_error(5, node->line, "Type mismatched for assignment.");
            }
            return make_exp(lhs.type, 0);
        }

        /* AND / OR */
        if (is_token(c1, "AND") || is_token(c1, "OR")) {
            if (!lhs.type || !rhs.type) {
                return make_exp(NULL, 0);
            }
            if (!is_int(lhs.type) || !is_int(rhs.type)) {
                semantic_error(7, node->line, "Type mismatched for operands.");
                return make_exp(NULL, 0);
            }
            return make_exp(new_type_basic(0), 0);
        }

        /* RELOP */
        if (is_token(c1, "RELOP")) {
            if (!lhs.type || !rhs.type) {
                return make_exp(NULL, 0);
            }
            if (!type_equal(lhs.type, rhs.type) || !is_numeric(lhs.type)) {
                semantic_error(7, node->line, "Type mismatched for operands.");
                return make_exp(NULL, 0);
            }
            return make_exp(new_type_basic(0), 0);
        }

        /* PLUS MINUS STAR DIV */
        if (is_token(c1, "PLUS") || is_token(c1, "MINUS") || is_token(c1, "STAR") || is_token(c1, "DIV")) {
            if (!lhs.type || !rhs.type) {
                return make_exp(NULL, 0);
            }
            if (!type_equal(lhs.type, rhs.type) || !is_numeric(lhs.type)) {
                semantic_error(7, node->line, "Type mismatched for operands.");
                return make_exp(NULL, 0);
            }
            return make_exp(lhs.type, 0);
        }
    }

    return make_exp(NULL, 0);
}

static FieldList build_VarList_fields(Node *node, int *param_count) {
    if (!node) return NULL;

    /* VarList -> ParamDec COMMA VarList | ParamDec */
    Node *param = child(node, 0);
    Node *rest = child(node, 2);

    Node *spec = child(param, 0);
    Node *vardec = child(param, 1);

    Type spec_type = analyze_Specifier(spec);
    char *name = NULL;
    Type var_type = build_VarDec_type(vardec, spec_type, &name);

    FieldList head = new_field(name ? name : "#param", var_type);
    (*param_count)++;

    if (rest) {
        head->tail = build_VarList_fields(rest, param_count);
    }
    return head;
}







