#include <stdio.h>
#include <stdlib.h>
#include "syntax_tree.h"
#include "semantic.h"

extern FILE *yyin;
extern int yyparse(void);
extern int lexical_error_count;
extern int syntax_error_count;
extern Node *syntax_root;

int main(int argc, char **argv){
    if(argc <= 1) return 1;
    yyin = fopen(argv[1], "r");
    if(!yyin){
        perror(argv[1]);
        return 1;
    }

    yyparse();

    fclose(yyin);

    if(lexical_error_count == 0 && syntax_error_count == 0 && syntax_root != NULL){
        semantic_analyze(syntax_root);
        // if(semantic_error_count == 0){
        //     print_tree(syntax_root, 0);
        // }
    }
    free_tree(syntax_root);
    return 0;

}