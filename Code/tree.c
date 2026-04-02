#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "syntax_tree.h"

static char *dupstr(const char *s){     // 复制字符串
    if(s == NULL) return NULL;
    char *p = (char *)malloc(strlen(s) + 1);
    if(p == NULL){
        perror("malloc");
        exit(1);
    }
    strcpy(p, s);
    return p;
}

static Node *alloc_node(const char *name, int line, const char *text, int is_token){    //统一分配节点
    Node *node = (Node *)malloc(sizeof(Node));
    if(node == NULL){
        perror("malloc");
        exit(1);
    }
    node->name = dupstr(name);
    node->line = line;
    node->text = dupstr(text);
    node->is_token = is_token;
    node->first_child = NULL;
    node->next_sibling = NULL;
    return node;
}

Node *new_token(const char *name, int line, const char *text){//创建叶子节点
    return alloc_node(name, line, text, 1);
}

Node *new_nonterm(const char *name, int line, int child_count, ...){//创建非终结符节点，并把右部孩子串起来
    Node *parent = alloc_node(name, line, NULL, 0);

    va_list ap;
    va_start(ap, child_count);

    Node *first = NULL;
    Node *prev = NULL;

    for(int i = 0; i < child_count; i++){
        Node *child = va_arg(ap, Node *);
        if(child == NULL) continue;
        if(first == NULL){
            first = child;
        } else {
            prev->next_sibling = child;
        }
        prev = child;
    }

    va_end(ap);
    parent->first_child = first;
    return parent;
}

static void print_indent(int depth){
    for( int i = 0; i < depth; i++){
        printf("  ");
    }
}

void print_tree(Node *root, int depth){
    if(root == NULL) return;
    print_indent(depth);

    if(root->is_token){
        if(root->text != NULL){
            printf("%s: %s\n", root->name, root->text);
        } else {
            printf("%s\n", root->name);
        }
    } else {
        printf("%s (%d)\n", root->name, root->line);
    }

    for(Node *child = root->first_child; child != NULL; child = child->next_sibling){
        print_tree(child, depth + 1);
    }

}

void free_tree(Node *root){
    if(root == NULL) return;

    Node *child = root->first_child;
    while(child != NULL){
        Node *next = child->next_sibling;
        free_tree(child);
        child = next;
    }

    free(root->name);
    free(root->text);
    free(root);
}






