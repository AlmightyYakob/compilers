#ifndef NODE_H
#define NODE_H

#include "type.h"

struct node_s;
struct arg_node_s;

/* Linked list */
typedef struct node_s {
    char *name;
    struct node_s *next;

    /* For code gen */
    int offset;

    /* Only valid if type.array is true */    
    int array_lower_bound, array_upper_bound;

    /* Variable type */
    type_t type;

    /* Stores arguments for functions */
    struct arg_node_s *func_arguments;
    
} node_t;

typedef struct arg_node_s {
    type_t type;
    struct arg_node_s *next;

} arg_node_t;

/* Constructors */
node_t *mknode(char *);

/* Helpers */
node_t *node_search(node_t *, char *);
node_t *node_insert(node_t *, char *);
void node_print(node_t *);

#endif