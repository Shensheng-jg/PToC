%{
#include <stdio.h>
#include <string.h>
#include "syntax_tree.h"

int yylex(void);
void yyerror(const char *s);

Node *syntax_root = NULL;
int syntax_error_count = 0;
static int last_syntax_error_line = -1;

static void report_syntax_error_line(int line, const char *msg){
    if(line <= 0) line = 1;
    if(last_syntax_error_line == line) return;
    printf("Error type B at Line %d: %s\n", line, msg);
    syntax_error_count++;
    last_syntax_error_line = line;
}
%}

%define parse.error verbose
%locations

%union{
    Node *node;
}

%token <node> ID TYPE INT FLOAT
%token <node> SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT
%token <node> LP RP LB RB LC RC
%token <node> STRUCT RETURN IF ELSE WHILE

%type <node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag
%type <node> VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT UMINUS
%left LP RP LB RB DOT

%%
Program
    : ExtDefList
      { syntax_root = $$ = new_nonterm("Program", @1.first_line, 1, $1); }
    ;

ExtDefList
    : ExtDef ExtDefList
      { $$ = new_nonterm("ExtDefList", @1.first_line, 2, $1, $2); }
    | /* empty */
      { $$ = NULL; }
    ;

ExtDef
    : Specifier ExtDecList SEMI
      { $$ = new_nonterm("ExtDef", @1.first_line, 3, $1, $2, $3); }
    | Specifier SEMI
      { $$ = new_nonterm("ExtDef", @1.first_line, 2, $1, $2); }
    | Specifier FunDec CompSt
      { $$ = new_nonterm("ExtDef", @1.first_line, 3, $1, $2, $3); }
    | error SEMI
      {
          report_syntax_error_line(@1.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;

ExtDecList
    : VarDec
      { $$ = new_nonterm("ExtDecList", @1.first_line, 1, $1); }
    | VarDec COMMA ExtDecList
      { $$ = new_nonterm("ExtDecList", @1.first_line, 3, $1, $2, $3); }
    | VarDec COMMA error
      {
          report_syntax_error_line(@3.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;

Specifier
    : TYPE
      { $$ = new_nonterm("Specifier", @1.first_line, 1, $1); }
    | StructSpecifier
      { $$ = new_nonterm("Specifier", @1.first_line, 1, $1); }
    ;

StructSpecifier
    : STRUCT OptTag LC DefList RC
      { $$ = new_nonterm("StructSpecifier", @1.first_line, 5, $1, $2, $3, $4, $5); }
    | STRUCT Tag
      { $$ = new_nonterm("StructSpecifier", @1.first_line, 2, $1, $2); }
    | STRUCT error
      {
          report_syntax_error_line(@2.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;
OptTag
    : ID
      { $$ = new_nonterm("OptTag", @1.first_line, 1, $1); }
    | /* empty */
      { $$ = NULL; }
    ;

Tag
    : ID
      { $$ = new_nonterm("Tag", @1.first_line, 1, $1); }
    ;

VarDec
    : ID
      { $$ = new_nonterm("VarDec", @1.first_line, 1, $1); }
    | VarDec LB INT RB
      { $$ = new_nonterm("VarDec", @1.first_line, 4, $1, $2, $3, $4); }
    | VarDec LB error RB
      {
          report_syntax_error_line(@4.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;

FunDec
    : ID LP VarList RP
      { $$ = new_nonterm("FunDec", @1.first_line, 4, $1, $2, $3, $4); }
    | ID LP RP
      { $$ = new_nonterm("FunDec", @1.first_line, 3, $1, $2, $3); }
    | ID LP error RP
      {
          report_syntax_error_line(@4.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;

VarList
    : ParamDec COMMA VarList
      { $$ = new_nonterm("VarList", @1.first_line, 3, $1, $2, $3); }
    | ParamDec
      { $$ = new_nonterm("VarList", @1.first_line, 1, $1); }
    | ParamDec COMMA error
      {
          report_syntax_error_line(@3.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;

ParamDec
    : Specifier VarDec
      { $$ = new_nonterm("ParamDec", @1.first_line, 2, $1, $2); }
    | Specifier error
      {
          report_syntax_error_line(@2.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;

CompSt
    : LC DefList StmtList RC
      { $$ = new_nonterm("CompSt", @1.first_line, 4, $1, $2, $3, $4); }
    | LC error RC
      {
          report_syntax_error_line(@2.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;

StmtList
    : Stmt StmtList
      { $$ = new_nonterm("StmtList", @1.first_line, 2, $1, $2); }
    | /* empty */
      { $$ = NULL; }
    ;

Stmt
    : Exp SEMI
      { $$ = new_nonterm("Stmt", @1.first_line, 2, $1, $2); }
    | CompSt
      { $$ = new_nonterm("Stmt", @1.first_line, 1, $1); }
    | RETURN Exp SEMI
      { $$ = new_nonterm("Stmt", @1.first_line, 3, $1, $2, $3); }
    | RETURN error SEMI
      {
          report_syntax_error_line(@2.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
      { $$ = new_nonterm("Stmt", @1.first_line, 5, $1, $2, $3, $4, $5); }
    | IF LP Exp RP Stmt ELSE Stmt
      { $$ = new_nonterm("Stmt", @1.first_line, 7, $1, $2, $3, $4, $5, $6, $7); }
    | IF LP error RP Stmt %prec LOWER_THAN_ELSE
      {
          report_syntax_error_line(@4.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    | IF LP error RP Stmt ELSE Stmt
      {
          report_syntax_error_line(@4.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    | WHILE LP Exp RP Stmt
      { $$ = new_nonterm("Stmt", @1.first_line, 5, $1, $2, $3, $4, $5); }
    | WHILE LP Exp RP error
      {
          report_syntax_error_line(@5.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    | Exp error
      {
          report_syntax_error_line(@2.first_line, "Missing \";\".");
          yyerrok;
          $$ = NULL;
      }
    | error SEMI
      {
          report_syntax_error_line(@1.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;

DefList
    : Def DefList
      { $$ = new_nonterm("DefList", @1.first_line, 2, $1, $2); }
    | /* empty */
      { $$ = NULL; }
    ;

Def
    : Specifier DecList SEMI
      { $$ = new_nonterm("Def", @1.first_line, 3, $1, $2, $3); }
    | error SEMI
      {
          report_syntax_error_line(@1.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;

DecList
    : Dec
      { $$ = new_nonterm("DecList", @1.first_line, 1, $1); }
    | Dec COMMA DecList
      { $$ = new_nonterm("DecList", @1.first_line, 3, $1, $2, $3); }
    | Dec COMMA error
      {
          report_syntax_error_line(@3.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;

Dec
    : VarDec
      { $$ = new_nonterm("Dec", @1.first_line, 1, $1); }
    | VarDec ASSIGNOP Exp
      { $$ = new_nonterm("Dec", @1.first_line, 3, $1, $2, $3); }
    | VarDec ASSIGNOP error
      {
          report_syntax_error_line(@3.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    ;

Exp
    : Exp ASSIGNOP Exp
      { $$ = new_nonterm("Exp", @1.first_line, 3, $1, $2, $3); }
    | Exp AND Exp
      { $$ = new_nonterm("Exp", @1.first_line, 3, $1, $2, $3); }
    | Exp OR Exp
      { $$ = new_nonterm("Exp", @1.first_line, 3, $1, $2, $3); }
    | Exp RELOP Exp
      { $$ = new_nonterm("Exp", @1.first_line, 3, $1, $2, $3); }
    | Exp PLUS Exp
      { $$ = new_nonterm("Exp", @1.first_line, 3, $1, $2, $3); }
    | Exp MINUS Exp
      { $$ = new_nonterm("Exp", @1.first_line, 3, $1, $2, $3); }
    | Exp STAR Exp
      { $$ = new_nonterm("Exp", @1.first_line, 3, $1, $2, $3); }
    | Exp DIV Exp
      { $$ = new_nonterm("Exp", @1.first_line, 3, $1, $2, $3); }
    | LP Exp RP
      { $$ = new_nonterm("Exp", @1.first_line, 3, $1, $2, $3); }
    | MINUS Exp %prec UMINUS
      { $$ = new_nonterm("Exp", @1.first_line, 2, $1, $2); }
    | NOT Exp
      { $$ = new_nonterm("Exp", @1.first_line, 2, $1, $2); }
    | ID LP Args RP
      { $$ = new_nonterm("Exp", @1.first_line, 4, $1, $2, $3, $4); }
    | ID LP RP
      { $$ = new_nonterm("Exp", @1.first_line, 3, $1, $2, $3); }
    | ID LP error RP
      {
          report_syntax_error_line(@4.first_line, "Invalid function call.");
          yyerrok;
          $$ = NULL;
      }
    | Exp LB Exp RB
      { $$ = new_nonterm("Exp", @1.first_line, 4, $1, $2, $3, $4); }
    | Exp LB error RB
      {
          report_syntax_error_line(@4.first_line, "Missing \"]\".");
          yyerrok;
          $$ = NULL;
      }
    | Exp RELOP error
      {
          report_syntax_error_line(@3.first_line, "Syntax error.");
          yyerrok;
          $$ = NULL;
      }
    | Exp DOT ID
      { $$ = new_nonterm("Exp", @1.first_line, 3, $1, $2, $3); }
    | ID
      { $$ = new_nonterm("Exp", @1.first_line, 1, $1); }
    | INT
      { $$ = new_nonterm("Exp", @1.first_line, 1, $1); }
    | FLOAT
      { $$ = new_nonterm("Exp", @1.first_line, 1, $1); }
    ;

Args
    : Exp COMMA Args
      { $$ = new_nonterm("Args", @1.first_line, 3, $1, $2, $3); }
    | Exp
      { $$ = new_nonterm("Args", @1.first_line, 1, $1); }
    | Exp COMMA error
      {
          report_syntax_error_line(@3.first_line, "Invalid function call.");
          yyerrok;
          $$ = NULL;
      }
    ;

%%

void yyerror(const char *s){
    extern YYLTYPE yylloc;
    report_syntax_error_line(yylloc.first_line, s);
}

#include "lex.yy.c"