#ifndef IR_H
#define IR_H

#include <stdio.h>
#include "syntax_tree.h"

int ir_supported(Node *root);
void ir_generate(Node *root, FILE *out);

#endif