#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "ir.h"

static Node *child(Node *node, int k) {
    Node *p = node ? node->first_child : NULL;
    while (p && k > 0) {
        p = p->next_sibling;
        --k;
    }
    return p;
}

static int is_token(Node *node, const char *name) {
    return node && node->is_token && strcmp(node->name, name) == 0;
}

static int is_nonterm(Node *node, const char *name) {
    return node && !node->is_token && strcmp(node->name, name) == 0;
}

static char *xstrdup(const char *s) {
    char *p = (char *)malloc(strlen(s) + 1);
    if (!p) { perror("malloc"); exit(1); }
    strcpy(p, s);
    return p;
}

static int has_struct_feature(Node *node) {
    if (!node) return 0;

    if (is_nonterm(node, "StructSpecifier")) return 1;
    if (is_token(node, "DOT")) return 1;

    for (Node *p = node->first_child; p; p = p->next_sibling) {
        if (has_struct_feature(p)) return 1;
    }
    return 0;
}

int ir_supported(Node *root) {
    return !has_struct_feature(root);
}

/* ---------- type system ---------- */
typedef struct Type_ *Type;
typedef struct Field_ *Field;
typedef struct Symbol_ Symbol;

enum { TY_INT, TY_ARRAY, TY_FUNC };

struct Type_ {
    int kind;
    union {
        struct { Type elem; int size; } array;
        struct { Type ret; Field params; int param_count; } func;
    } u;
};

struct Field_ {
    char *name;
    Type type;
    Field next;
};

struct Symbol_ {
    char *name;
    Type type;
    int is_param;
    Symbol *next;
};

static Type ty_int(void) {
    static struct Type_ t = { TY_INT, {{0}} };
    return &t;
}

static Type new_array(Type elem, int size) {
    Type t = (Type)malloc(sizeof(*t));
    if (!t) { perror("malloc"); exit(1); }
    t->kind = TY_ARRAY;
    t->u.array.elem = elem;
    t->u.array.size = size;
    return t;
}

static Type new_func(Type ret, Field params, int param_count) {
    Type t = (Type)malloc(sizeof(*t));
    if (!t) { perror("malloc"); exit(1); }
    t->kind = TY_FUNC;
    t->u.func.ret = ret;
    t->u.func.params = params;
    t->u.func.param_count = param_count;
    return t;
}

static Field new_field(const char *name, Type type) {
    Field f = (Field)malloc(sizeof(*f));
    if (!f) { perror("malloc"); exit(1); }
    f->name = xstrdup(name);
    f->type = type;
    f->next = NULL;
    return f;
}

static int type_width(Type t) {
    if (!t) return 4;
    if (t->kind == TY_INT) return 4;
    if (t->kind == TY_ARRAY) return t->u.array.size * type_width(t->u.array.elem);
    return 4;
}

/* ---------- symbol tables ---------- */
static Symbol *global_funcs = NULL;
static Symbol *local_vars = NULL;
static FILE *irout = NULL;
static int temp_no = 1;
static int label_no = 1;

static Symbol *new_symbol(const char *name, Type type, int is_param) {
    Symbol *s = (Symbol *)malloc(sizeof(*s));
    if (!s) { perror("malloc"); exit(1); }
    s->name = xstrdup(name);
    s->type = type;
    s->is_param = is_param;
    s->next = NULL;
    return s;
}

static void insert_local(const char *name, Type type, int is_param) {
    Symbol *s = new_symbol(name, type, is_param);
    s->next = local_vars;
    local_vars = s;
}

static void insert_global_func(const char *name, Type type) {
    Symbol *s = new_symbol(name, type, 0);
    s->next = global_funcs;
    global_funcs = s;
}

static Symbol *lookup(Symbol *head, const char *name) {
    while (head) {
        if (strcmp(head->name, name) == 0) return head;
        head = head->next;
    }
    return NULL;
}

static Symbol *lookup_var(const char *name) { return lookup(local_vars, name); }
static Symbol *lookup_func(const char *name) { return lookup(global_funcs, name); }

static void clear_locals(void) {
    Symbol *p = local_vars;
    while (p) {
        Symbol *n = p->next;
        free(p->name);
        free(p);
        p = n;
    }
    local_vars = NULL;
}

/* ---------- IR emit ---------- */
static void emit(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(irout, fmt, ap);
    va_end(ap);
    fputc('\n', irout);
}

static char *new_temp_name(void) {
    char buf[32];
    sprintf(buf, "t%d", temp_no++);
    return xstrdup(buf);
}

static char *new_label_name(void) {
    char buf[32];
    sprintf(buf, "label%d", label_no++);
    return xstrdup(buf);
}

/* ---------- declarations / types ---------- */
static Type build_vardec_type(Node *node, Type base, char **out_name) {
    Node *c0 = child(node, 0);
    Node *c1 = child(node, 1);

    if (c0 && is_token(c0, "ID") && !c1) {
        *out_name = c0->text;
        return base;
    }
    if (c0 && c1 && is_nonterm(c0, "VarDec") && is_token(c1, "LB")) {
        Type inner = build_vardec_type(c0, base, out_name);
        Node *intnode = child(node, 2);
        int size = intnode ? atoi(intnode->text) : 0;
        return new_array(inner, size);
    }
    *out_name = NULL;
    return base;
}

static Type analyze_specifier(Node *node) {
    Node *c0 = child(node, 0);

    if (c0 && is_token(c0, "TYPE")) {
        return ty_int();
    }

    return NULL;
}

static Type infer_exp_type(Node *node);

/* ---------- lvalue helpers ---------- */
static int exp_is_id(Node *node, char **name_out) {
    Node *c0 = child(node, 0);
    if (node && is_nonterm(node, "Exp") && c0 && is_token(c0, "ID") && !child(node, 1)) {
        if (name_out) *name_out = c0->text;
        return 1;
    }
    return 0;
}

static int exp_is_array_access(Node *node) {
    return node && is_nonterm(node, "Exp") && child(node,0) && child(node,1) && child(node,2) && child(node,3)
           && is_token(child(node,1), "LB") && is_token(child(node,3), "RB");
}

static void translate_exp(Node *node, const char *place);
static void translate_cond(Node *node, const char *lt, const char *lf);
static void translate_stmt(Node *node);
static void translate_compst(Node *node);
static char *translate_operand(Node *node);

static void translate_var_address(Node *exp, const char *place) {
    char *name = NULL;
    if (!exp_is_id(exp, &name)) return;
    Symbol *sym = lookup_var(name);
    if (sym && sym->is_param && sym->type->kind == TY_ARRAY) {
        emit("%s := %s", place, name);
    } else {
        emit("%s := &%s", place, name);
    }
}

static void translate_array_addr(Node *node, const char *place) {
    Node *base = child(node, 0);
    Node *idx = child(node, 2);
    Type base_type = infer_exp_type(base);
    Type elem_type = (base_type && base_type->kind == TY_ARRAY) ? base_type->u.array.elem : ty_int();

    char *base_addr = new_temp_name();
    //char *idxv = new_temp_name();
    char *off = new_temp_name();

    if (exp_is_array_access(base)) {
        translate_array_addr(base, base_addr);
    } else {
        translate_var_address(base, base_addr);
    }
    char *idxv = translate_operand(idx);
    emit("%s := %s * #%d", off, idxv, type_width(elem_type));
    emit("%s := %s + %s", place, base_addr, off);
}

/* ---------- type inference ---------- */
static Type infer_exp_type(Node *node) {
    if (!node) return ty_int();
    Node *c0 = child(node, 0), *c1 = child(node, 1), *c2 = child(node, 2);

    if (exp_is_id(node, NULL)) {
        Symbol *sym = lookup_var(c0->text);
        return sym ? sym->type : ty_int();
    }
    if (c0 && is_token(c0, "INT")) return ty_int();
    if (c0 && is_token(c0, "ID") && c1 && is_token(c1, "LP")) {
        Symbol *f = lookup_func(c0->text);
        if (f && f->type && f->type->kind == TY_FUNC) return f->type->u.func.ret;
        return ty_int();
    }
    if (exp_is_array_access(node)) {
        Type t = infer_exp_type(c0);
        if (t && t->kind == TY_ARRAY) return t->u.array.elem;
        return ty_int();
    }
    if (c0 && c1 && c2 && is_token(c1, "ASSIGNOP")) return infer_exp_type(c0);
    if (c0 && c1 && c2 && (is_token(c1, "PLUS") || is_token(c1, "MINUS") || is_token(c1, "STAR") || is_token(c1, "DIV") || is_token(c1, "RELOP") || is_token(c1, "AND") || is_token(c1, "OR"))) return ty_int();
    if (c0 && is_token(c0, "LP")) return infer_exp_type(c1);
    if (c0 && (is_token(c0, "MINUS") || is_token(c0, "NOT"))) return ty_int();
    return ty_int();
}

/* ---------- args ---------- */
typedef struct ArgNode_ {
    char *op;
    struct ArgNode_ *next;
} ArgNode;

static void args_push_front(ArgNode **head, char *op) {
    ArgNode *n = (ArgNode *)malloc(sizeof(*n));
    if (!n) { perror("malloc"); exit(1); }
    n->op = op;
    n->next = *head;
    *head = n;
}

static void translate_args(Node *node, ArgNode **list) {
    if (!node) return;

    Node *exp = child(node, 0);
    Node *rest = child(node, 2);

    char *name = NULL;
    if (exp_is_id(exp, &name)) {
        Symbol *sym = lookup_var(name);
        if (sym && sym->type->kind == TY_ARRAY) {
            char *op;
            if (sym->is_param) op = xstrdup(name);
            else {
                op = (char *)malloc(strlen(name) + 2);
                op[0] = '&';
                strcpy(op + 1, name);
            }
            args_push_front(list, op);
        } else {
            args_push_front(list, translate_operand(exp));
        }
    } else {
        args_push_front(list, translate_operand(exp));
    }

    if (rest) translate_args(rest, list);
}

/* ---------- expressions ---------- */
static void translate_bool_value(Node *node, const char *place) {
    char *lt = new_label_name();
    char *lf = new_label_name();
    char *le = new_label_name();
    emit("%s := #0", place);
    translate_cond(node, lt, lf);
    emit("LABEL %s :", lt);
    emit("%s := #1", place);
    emit("GOTO %s", le);
    emit("LABEL %s :", lf);
    emit("LABEL %s :", le);
}

static int is_simple_exp(Node *node) {
    if (!node) return 0;
    Node *c0 = child(node, 0);
    Node *c1 = child(node, 1);

    if (c0 && is_token(c0, "INT") && !c1) return 1;
    if (c0 && is_token(c0, "ID") && !c1) return 1;
    return 0;
}

static char *translate_operand(Node *node) {
    if (!node) return xstrdup("#0");

    Node *c0 = child(node, 0);
    Node *c1 = child(node, 1);

    if (c0 && is_token(c0, "INT") && !c1) {
        char buf[64];
        sprintf(buf, "#%s", c0->text);
        return xstrdup(buf);
    }

    if (c0 && is_token(c0, "ID") && !c1) {
        return xstrdup(c0->text);
    }

    {
        char *t = new_temp_name();
        translate_exp(node, t);
        return t;
    }
}

static void translate_exp(Node *node, const char *place) {
    if (!node) return;
    Node *c0 = child(node,0), *c1 = child(node,1), *c2 = child(node,2), *c3 = child(node,3);

    if (exp_is_id(node, NULL)) {
        if (place) emit("%s := %s", place, c0->text);
        return;
    }
    if (c0 && is_token(c0, "INT") && !c1) {
        if (place) emit("%s := #%s", place, c0->text);
        return;
    }
    if (c0 && is_token(c0, "LP")) {
        translate_exp(c1, place);
        return;
    }
    if (c0 && is_token(c0, "MINUS") && c1) {
        if (place) {
            char *t = translate_operand(c1);
            emit("%s := #0 - %s", place, t);
        }
        return;
    }
    if (c0 && is_token(c0, "NOT") && c1) {
        if (place) {
            translate_bool_value(node, place);
        } else {
            /* 表达式语句里丢弃结果 */
            (void)translate_operand(c1);
        }
        return;
    }
    if (c0 && c1 && c2 && is_token(c1, "ASSIGNOP")) {
        char *rhs = translate_operand(c2);
        if (exp_is_id(c0, NULL)) {
            emit("%s := %s", child(c0,0)->text, rhs);
            if (place) emit("%s := %s", place, child(c0,0)->text);
        } else if (exp_is_array_access(c0)) {
            char *addr = new_temp_name();
            translate_array_addr(c0, addr);
            emit("*%s := %s", addr, rhs);
            if (place) emit("%s := %s", place, rhs);
        }
        return;
    }
    if (exp_is_array_access(node)) {
        Type elem = infer_exp_type(node);
        char *addr = new_temp_name();
        translate_array_addr(node, addr);

        if (place) {
            if (elem && elem->kind == TY_ARRAY) {
                emit("%s := %s", place, addr);
            } else {
                emit("%s := *%s", place, addr);
            }
        }
        return;
    }
    if (c0 && c1 && c2 &&
        (is_token(c1, "PLUS") || is_token(c1, "MINUS") ||
        is_token(c1, "STAR") || is_token(c1, "DIV"))) {
        if (place) {
            char *t1 = translate_operand(c0);
            char *t2 = translate_operand(c2);
            emit("%s := %s %s %s", place, t1,
                is_token(c1,"PLUS")?"+":is_token(c1,"MINUS")?"-":
                is_token(c1,"STAR")?"*":"/",
                t2);
        }
        return;
    }
    if (c0 && c1 && c2 && (is_token(c1, "RELOP") || is_token(c1, "AND") || is_token(c1, "OR"))) {
        if (place) {
            translate_bool_value(node, place);
        } else {
            /* 表达式语句里只保证子表达式被求值 */
            (void)translate_operand(c0);
            (void)translate_operand(c2);
        }
        return;
    }
    if (c0 && is_token(c0, "ID") && c1 && is_token(c1, "LP") && c2 && is_token(c2, "RP")) {
        if (strcmp(c0->text, "read") == 0) {
            if (place) emit("READ %s", place);
        } else {
            if (place) {
                emit("%s := CALL %s", place, c0->text);
            } else {
                char *t = new_temp_name();
                emit("%s := CALL %s", t, c0->text);
            }
        }
        return;
    }
    if (c0 && is_token(c0, "ID") && c1 && is_token(c1, "LP") && c2 && c3 && is_token(c3, "RP")) {
        if (strcmp(c0->text, "write") == 0) {
            char *op = translate_operand(child(c2,0));
            emit("WRITE %s", op);
            if (place) emit("%s := #0", place);
        } else {
            ArgNode *args = NULL, *p;
            translate_args(c2, &args);
            for (p = args; p; p = p->next) emit("ARG %s", p->op);

            if (place) {
                emit("%s := CALL %s", place, c0->text);
            } else {
                char *t = new_temp_name();
                emit("%s := CALL %s", t, c0->text);
            }
        }
        return;
    }
}

static void translate_cond(Node *node, const char *lt, const char *lf) {
    Node *c0 = child(node,0), *c1 = child(node,1), *c2 = child(node,2);
    if (!node) return;

    if (c0 && is_token(c0, "NOT")) {
        translate_cond(c1, lf, lt);
        return;
    }
    if (c0 && c1 && c2 && is_token(c1, "AND")) {
        char *l1 = new_label_name();
        translate_cond(c0, l1, lf);
        emit("LABEL %s :", l1);
        translate_cond(c2, lt, lf);
        return;
    }
    if (c0 && c1 && c2 && is_token(c1, "OR")) {
        char *l1 = new_label_name();
        translate_cond(c0, lt, l1);
        emit("LABEL %s :", l1);
        translate_cond(c2, lt, lf);
        return;
    }
    if (c0 && c1 && c2 && is_token(c1, "RELOP")) {
        char *t1 = translate_operand(c0);
        char *t2 = translate_operand(c2);
        emit("IF %s %s %s GOTO %s", t1, c1->text, t2, lt);
        emit("GOTO %s", lf);
        return;
    }
    {
        char *t = translate_operand(node);
        emit("IF %s != #0 GOTO %s", t, lt);
        emit("GOTO %s", lf);
    }
}

/* ---------- statements ---------- */
static void translate_dec(Node *node, Type spec_type) {
    Node *vardec = child(node, 0);
    Node *init = child(node, 2);
    char *name = NULL;

    if (spec_type == NULL) return;

    Type t = build_vardec_type(vardec, spec_type, &name);
    if (t == NULL || name == NULL) return;

    insert_local(name, t, 0);
    if (t->kind == TY_ARRAY) emit("DEC %s %d", name, type_width(t));
    if (init) {
        char *rhs = translate_operand(init);
        emit("%s := %s", name, rhs);
    }
}
static void translate_declist(Node *node, Type spec_type) {
    if (!node) return;
    translate_dec(child(node,0), spec_type);
    if (child(node,2)) translate_declist(child(node,2), spec_type);
}

static void translate_deflist(Node *node) {
    if (!node) return;
    Node *def = child(node, 0);
    if (def) {
        Type spec = analyze_specifier(child(def, 0));
        translate_declist(child(def, 1), spec);
    }
    translate_deflist(child(node, 1));
}

static void translate_stmtlist(Node *node) {
    if (!node) return;
    translate_stmt(child(node,0));
    translate_stmtlist(child(node,1));
}

static int stmt_ends_control(Node *node) {
    if (!node) return 0;

    Node *c0 = child(node, 0);
    Node *c1 = child(node, 1);
    Node *c2 = child(node, 2);
    Node *c3 = child(node, 3);
    Node *c4 = child(node, 4);
    Node *c5 = child(node, 5);
    Node *c6 = child(node, 6);

    /* RETURN Exp SEMI */
    if (c0 && is_token(c0, "RETURN")) {
        return 1;
    }

    /* CompSt -> LC DefList StmtList RC */
    if (c0 && is_nonterm(c0, "CompSt")) {
        Node *stmtlist = child(c0, 2);
        if (!stmtlist) return 0;

        Node *p = stmtlist;
        Node *last_stmt = NULL;
        while (p) {
            last_stmt = child(p, 0);
            p = child(p, 1);
        }
        return stmt_ends_control(last_stmt);
    }

    /* IF ... ELSE ... */
    if (c0 && is_token(c0, "IF") && c5 && is_token(c5, "ELSE")) {
        return stmt_ends_control(c4) && stmt_ends_control(c6);
    }

    return 0;
}

static void translate_stmt(Node *node) {
    if (!node) return;

    Node *c0 = child(node, 0);
    Node *c1 = child(node, 1);
    Node *c2 = child(node, 2);
    Node *c3 = child(node, 3);
    Node *c4 = child(node, 4);
    Node *c5 = child(node, 5);
    Node *c6 = child(node, 6);

    /* Stmt -> Exp SEMI */
    if (c0 && is_nonterm(c0, "Exp") && c1 && is_token(c1, "SEMI")) {
        translate_exp(c0, NULL);
        return;
    }

    /* Stmt -> CompSt */
    if (c0 && is_nonterm(c0, "CompSt")) {
        translate_compst(c0);
        return;
    }

    /* Stmt -> RETURN Exp SEMI */
    if (c0 && is_token(c0, "RETURN")) {
        char *op = translate_operand(c1);
        emit("RETURN %s", op);
        return;
    }

    /* Stmt -> IF LP Exp RP Stmt */
    if (c0 && is_token(c0, "IF") &&
        c1 && is_token(c1, "LP") &&
        c2 &&
        c3 && is_token(c3, "RP") &&
        c4 && !c5) {

        char *lt = new_label_name();
        char *lf = new_label_name();

        translate_cond(c2, lt, lf);

        emit("LABEL %s :", lt);
        translate_stmt(c4);

        emit("LABEL %s :", lf);
        return;
    }

    /* Stmt -> IF LP Exp RP Stmt ELSE Stmt */
    if (c0 && is_token(c0, "IF") &&
        c1 && is_token(c1, "LP") &&
        c2 &&
        c3 && is_token(c3, "RP") &&
        c4 &&
        c5 && is_token(c5, "ELSE") &&
        c6) {

        char *lt = new_label_name();
        char *lf = new_label_name();
        char *le = new_label_name();

        int then_ends = stmt_ends_control(c4);
        int else_ends = stmt_ends_control(c6);

        translate_cond(c2, lt, lf);

        emit("LABEL %s :", lt);
        translate_stmt(c4);
        if (!then_ends) {
            emit("GOTO %s", le);
        }

        emit("LABEL %s :", lf);
        translate_stmt(c6);

        if (!then_ends || !else_ends) {
            emit("LABEL %s :", le);
        }
        return;
    }

    /* Stmt -> WHILE LP Exp RP Stmt */
    if (c0 && is_token(c0, "WHILE") &&
        c1 && is_token(c1, "LP") &&
        c2 &&
        c3 && is_token(c3, "RP") &&
        c4) {

        char *lb = new_label_name();
        char *lt = new_label_name();
        char *lf = new_label_name();

        emit("LABEL %s :", lb);
        translate_cond(c2, lt, lf);

        emit("LABEL %s :", lt);
        translate_stmt(c4);
        emit("GOTO %s", lb);

        emit("LABEL %s :", lf);
        return;
    }
}

static void translate_compst(Node *node) {
    if (!node) return;
    Node *p = child(node, 1);
    if (p && is_nonterm(p, "DefList")) {
        translate_deflist(p);
        p = p->next_sibling;
    }
    if (p && is_nonterm(p, "StmtList")) translate_stmtlist(p);
}

/* ---------- function handling ---------- */
static Field collect_params(Node *node, int *count, int insert_into_locals) {
    if (!node) return NULL;

    Node *param = child(node, 0);
    Node *rest = child(node, 2);

    Type spec = analyze_specifier(child(param, 0));
    char *name = NULL;
    Type t = NULL;

    if (spec != NULL) {
        t = build_vardec_type(child(param, 1), spec, &name);
    }

    if (t == NULL || name == NULL) {
        return NULL;
    }

    Field head = new_field(name, t);
    (*count)++;

    if (insert_into_locals) {
        insert_local(name, t, 1);
    }

    if (rest) {
        head->next = collect_params(rest, count, insert_into_locals);
    }
    return head;
}

static void collect_function_signatures(Node *extdeflist) {
    for (Node *p = extdeflist; p; p = child(p,1)) {
        Node *extdef = child(p,0);
        if (!extdef) continue;
        Node *a = child(extdef,0), *b = child(extdef,1), *c = child(extdef,2);
        if (a && b && c && is_nonterm(b, "FunDec")) {
            Node *id = child(b,0);
            int cnt = 0;
            Field params = NULL;
            if (child(b,2) && is_nonterm(child(b,2), "VarList")) params = collect_params(child(b,2), &cnt, 0);
            insert_global_func(id->text, new_func(ty_int(), params, cnt));
        }
    }
    if (!lookup_func("read")) insert_global_func("read", new_func(ty_int(), NULL, 0));
    if (!lookup_func("write")) {
        Field p = new_field("x", ty_int());
        insert_global_func("write", new_func(ty_int(), p, 1));
    }
}

static void translate_function(Node *extdef) {
    Node *fundec = child(extdef,1);
    Node *compst = child(extdef,2);
    Node *id = child(fundec,0);
    clear_locals();
    emit("FUNCTION %s :", id->text);
    if (child(fundec,2) && is_nonterm(child(fundec,2), "VarList")) {
        int cnt = 0;
        Field params = collect_params(child(fundec,2), &cnt, 1);
        for (Field p = params; p; p = p->next) emit("PARAM %s", p->name);
    }
    translate_compst(compst);
}

void ir_generate(Node *root, FILE *out) {
    if (!root || !out) return;
    irout = out;
    temp_no = 1;
    label_no = 1;
    global_funcs = NULL;
    local_vars = NULL;

    Node *extdeflist = child(root, 0);
    collect_function_signatures(extdeflist);

    for (Node *p = extdeflist; p; p = child(p,1)) {
        Node *extdef = child(p,0);
        if (!extdef) continue;
        Node *a = child(extdef,0), *b = child(extdef,1), *c = child(extdef,2);
        if (a && b && c && is_nonterm(b, "FunDec") && is_nonterm(c, "CompSt")) {
            translate_function(extdef);
        }
    }
    clear_locals();
}