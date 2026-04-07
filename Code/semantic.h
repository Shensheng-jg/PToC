#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "syntax_tree.h"


extern int semantic_error_count;

void semantic_analyze(Node *root);

#endif