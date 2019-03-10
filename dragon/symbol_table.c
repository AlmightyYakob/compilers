#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symbol_table.h"
// #include "y.tab.h"


// Create new table
symbol_table_t *init_table(){
    symbol_table_t *table = malloc(sizeof(symbol_table_t));
    table->stack_length = 0;
    table->root = table->top = NULL;    
    
    /* change to pointer to new hash table if default to stack_length 1*/
}

// Create new scope_t on the stack of symbol table "table"
int push(symbol_table_t *table){
    // malloc new_scope
    // set new_scope->prev = table->top
    // set table->top = &new_scope
}

// Removes top scope_t from stack of symbol table "table"
int pop(symbol_table_t *table){

}

