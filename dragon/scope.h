#ifndef SCOPE_H
#define SCOPE_H

#include "node.h"

#define HASH_SIZE 211

typedef struct scope_s {
    node_t *table[HASH_SIZE];
    struct scope_s *next;
} scope_t;

/* Constructors/Destructors */
scope_t *mkscope();
void free_scope(scope_t *);

/* stack routines */
scope_t *push_scope(scope_t *);
scope_t  *pop_scope(scope_t *);

/* Helpers */
node_t *scope_search_all(scope_t *top, char *name);
node_t     *scope_search(scope_t *top, char *name);
node_t     *scope_insert(scope_t *top, char *name);
node_t        *scope_del(scope_t *top, char *name);

/* Misc */
void scope_print(scope_t *current_scope);

#endif
