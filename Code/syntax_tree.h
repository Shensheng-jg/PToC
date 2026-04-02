#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <stdarg.h>

typedef struct Node{
    char *name;     // 节点名字
    int line;      // 行号
    char *text;    // 叶子结点的附加文本
    int is_token;  // 是否为终结符
    struct Node *first_child; // 第一个子节点
    struct Node *next_sibling; // 下一个兄弟节点    
} Node;

Node *new_token(const char *name, int line, const char *text);
Node *new_nonterm(const char *name, int line, int child_count, ...);

void print_tree(Node *root, int depth);
void free_tree(Node *root);

#endif