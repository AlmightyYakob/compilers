#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "hash_table.h"

// find_entry
// create_entry
// pop
// push

typedef struct scope_s {
    // Hash table contents

    struct scope_s *prev;
} scope_t;

typedef struct {
    int stack_length;
    scope_t *root;
    scope_t *top;
} symbol_table_t;


// Create new table
symbol_table_t *init_table();

// Create new scope_t on the stack of symbol table "table"
int push(symbol_table_t *table);

// Removes top scope_t from stack of symbol table "table"
int pop(symbol_table_t *table);

/*  Search for entry in symbol table.
    Do this by iterating through the stack of hash tables,
    starting at the top, and search each one for the key.
    Either return the first one found, or NULL if not found.
*/
// hash_table_entry* search

#endif
