#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "node.h"
#include "tree.h"
#include "y.tab.h"

/* Constructors */
node_t *mknode(char *s){
    node_t *p = (node_t *) malloc(sizeof(node_t));
    assert(p != NULL);
    p->name = strdup(s);
    p->next = NULL;

    p->type.super_type = -1;
    p->type.tree_node_type = -1;
    p->type.array = 0;
    
    return p;
}

/* Helpers */
node_t *node_search(node_t *top, char *name){
    node_t *p = top;

    while(p != NULL){
        if (strcmp(p->name, name) == 0) return p;
        p = p->next;
    }
    return NULL;
}

node_t *node_insert(node_t *top, char *name){
    node_t *p = mknode(name);
    p->next = top;
    return p;
}

void node_print(node_t *top){
    node_t *p = top;
    fprintf(stderr, "BEGIN LIST PRINT");
    while(p != NULL){
        fprintf(stderr, "[%s]", p->name);
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "END LIST PRINT");
}

int num_args(node_t *node){
    arg_node_t *curr_node = node->func_arguments;
    int num = 0;

    while(curr_node != NULL) {
        ++num;
        curr_node = curr_node->next;
    }

    return num;
}
