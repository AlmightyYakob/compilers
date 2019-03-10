#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

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

#endif
