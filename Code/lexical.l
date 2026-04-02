%option noyywrap
%option yylineno
%option nounput noinput

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax_tree.h"
#include "syntax.tab.h"

int lexical_error_count = 0;
extern int syntax_error_count;

#define YY_USER_ACTION                    \
    yylloc.first_line = yylineno;         \
    yylloc.last_line = yylineno;          \
    yylloc.first_column = 1;              \
    yylloc.last_column = 1;

static Node *make_plain(const char *name){
    return new_token(name, yylineno, NULL);
}

static Node *make_text(const char *name, const char *text){
    return new_token(name, yylineno, text);
}

static Node *make_int_token_base(const char *lexeme, int base){
    char buf[64];
    long v = strtol(lexeme, NULL, base);
    snprintf(buf, sizeof(buf), "%ld", v);
    return new_token("INT", yylineno, buf);
}

static Node *make_float_token(const char *lexeme){
    char buf[64];
    double v = strtod(lexeme, NULL);
    snprintf(buf, sizeof(buf), "%f", v);
    return new_token("FLOAT", yylineno, buf);
}

static void report_lex_char(const char *text){
    printf("Error type A at Line %d: Mysterious character \"%s\".\n", yylineno, text);
    lexical_error_count++;
}

static void report_lex_id(const char *text){
    printf("Error type A at Line %d: Illegal ID '%s'.\n", yylineno, text);
    lexical_error_count++;
}

static void report_lex_float(const char *text){
    printf("Error type A at Line %d: Illegal FLOAT number '%s'.\n", yylineno, text);
    lexical_error_count++;
}

static void report_lex_oct(const char *text){
    printf("Error type A at Line %d: Illegal octal number '%s'.\n", yylineno, text);
    lexical_error_count++;
}

static void report_lex_hex(const char *text){
    printf("Error type A at Line %d: Illegal hexadecimal number '%s'.\n", yylineno, text);
    lexical_error_count++;
}
%}

DIGIT       [0-9]
NZDIGIT     [1-9]
LETTER      [A-Za-z_]
IDCHAR      [A-Za-z_0-9]
OCTDIGIT    [0-7]
HEXDIGIT    [0-9a-fA-F]

INT10       0|{NZDIGIT}{DIGIT}*
FLOAT_BASE  ({DIGIT}+\.{DIGIT}*|{DIGIT}*\.{DIGIT}+)
ID          {LETTER}{IDCHAR}*


%%
"int" {
    yylval.node = make_text("TYPE", yytext);
    return TYPE;
}

"float" {
    yylval.node = make_text("TYPE", yytext);
    return TYPE;
}

"struct" {
    yylval.node = make_plain("STRUCT");
    return STRUCT;
}

"return" {
    yylval.node = make_plain("RETURN");
    return RETURN;
}

"if" {
    yylval.node = make_plain("IF");
    return IF;
}

"else" {
    yylval.node = make_plain("ELSE");
    return ELSE;
}

"while" {
    yylval.node = make_plain("WHILE");
    return WHILE;
}

";" {
    yylval.node = make_plain("SEMI");
    return SEMI;
}

"," {
    yylval.node = make_plain("COMMA");
    return COMMA;
}

"+=" {
    printf("Error type B at Line %d: '+=' is not supported.\n", yylineno);
    syntax_error_count++;
    yylval.node = make_plain("ASSIGNOP");
    return ASSIGNOP;
}

"-=" {
    printf("Error type B at Line %d: '-=' is not supported.\n", yylineno);
    syntax_error_count++;
    yylval.node = make_plain("ASSIGNOP");
    return ASSIGNOP;
}

"*=" {
    printf("Error type B at Line %d: '*=' is not supported.\n", yylineno);
    syntax_error_count++;
    yylval.node = make_plain("ASSIGNOP");
    return ASSIGNOP;
}

"/=" {
    printf("Error type B at Line %d: '/=' is not supported.\n", yylineno);
    syntax_error_count++;
    yylval.node = make_plain("ASSIGNOP");
    return ASSIGNOP;
}

"%=" {
    printf("Error type B at Line %d: '%%=' is not supported.\n", yylineno);
    syntax_error_count++;
    yylval.node = make_plain("ASSIGNOP");
    return ASSIGNOP;
}

"=" {
    yylval.node = make_plain("ASSIGNOP");
    return ASSIGNOP;
}

"&&" {
    yylval.node = make_plain("AND");
    return AND;
}

"||" {
    yylval.node = make_plain("OR");
    return OR;
}

"." {
    yylval.node = make_plain("DOT");
    return DOT;
}

"!" {
    yylval.node = make_plain("NOT");
    return NOT;
}

"+" {
    yylval.node = make_plain("PLUS");
    return PLUS;
}

"-" {
    yylval.node = make_plain("MINUS");
    return MINUS;
}

"*" {
    yylval.node = make_plain("STAR");
    return STAR;
}

"/" {
    yylval.node = make_plain("DIV");
    return DIV;
}

"(" {
    yylval.node = make_plain("LP");
    return LP;
}

")" {
    yylval.node = make_plain("RP");
    return RP;
}

"[" {
    yylval.node = make_plain("LB");
    return LB;
}

"]" {
    yylval.node = make_plain("RB");
    return RB;
}

"{" {
    yylval.node = make_plain("LC");
    return LC;
}

"}" {
    yylval.node = make_plain("RC");
    return RC;
}

"<=" {
    yylval.node = make_text("RELOP", yytext);
    return RELOP;
}

">=" {
    yylval.node = make_text("RELOP", yytext);
    return RELOP;
}

"==" {
    yylval.node = make_text("RELOP", yytext);
    return RELOP;
}

"!=" {
    yylval.node = make_text("RELOP", yytext);
    return RELOP;
}

"<" {
    yylval.node = make_text("RELOP", yytext);
    return RELOP;
}

">" {
    yylval.node = make_text("RELOP", yytext);
    return RELOP;
}


({DIGIT}+\.{DIGIT}*|{DIGIT}*\.{DIGIT}+)(\.{DIGIT}+)+ {
    report_lex_float(yytext);
    yylval.node = new_token("FLOAT", yylineno, "0.000000");
    return FLOAT;
}

0[xX][0-9a-fA-F]*[g-zG-Z_][A-Za-z_0-9]* {
    report_lex_hex(yytext);
    yylval.node = new_token("INT", yylineno, "0");
    return INT;
}

0[xX] {
    report_lex_hex(yytext);
    yylval.node = new_token("INT", yylineno, "0");
    return INT;
}

0[0-7]*[89][0-9]* {
    report_lex_oct(yytext);
    yylval.node = new_token("INT", yylineno, "0");
    return INT;
}

0[xX]{HEXDIGIT}+ {
    yylval.node = make_int_token_base(yytext, 0);
    return INT;
}

0{OCTDIGIT}+ {
    yylval.node = make_int_token_base(yytext, 0);
    return INT;
}

{DIGIT}+{LETTER}{IDCHAR}* {
    report_lex_id(yytext);
    yylval.node = new_token("ID", yylineno, yytext);
    return ID;
}

{FLOAT_BASE} {
    yylval.node = make_float_token(yytext);
    return FLOAT;
}

{INT10} {
    yylval.node = make_int_token_base(yytext, 10);
    return INT;
}

{ID} {
    yylval.node = make_text("ID", yytext);
    return ID;
}

[ \t\r]+ {
}

\n {
}

. {
    report_lex_char(yytext);
}
%%
