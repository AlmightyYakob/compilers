#include "tree.h"
#define STACK_LENGTH 3
/*
 * ACTIVATION RECORD LAYOUT
 * -----------------------------------
 * 
 * Lower Memory Addresses
 * -----------------------------------
 * | .
 * -----------------------------------
 * | .
 * -----------------------------------
 * | Local Variables
 * -----------------------------------
 * | Previous Base Pointer
 * -----------------------------------
 * | Return Address
 * ---------------------------------------------------------------
 * | Passed Argument 1
 * -----------------------------------
 * | Passed Argument 2
 * -----------------------------------
 * | .
 * -----------------------------------
 * | .
 * -----------------------------------
 * 
 * Higher Memory Addresses
 *
 *
 *
 * REGISTERS
 * -----------------------------------
 * %eax - returns
 * %edx - div and mod
 * %ecx - to track static parent pointer
 *
 * Stack: %ebx, %esi, %edi
 *
 * %ebp: base pointer
 * %esp: stack pointer
 * 
 * 
 * Storing stack of indicies, which index array of registers that could be used.
 * 
 * 
 * STEPS
 * -----------------------------------
 * prologue:
 *      pushl    %ebp
 *      movl     %esp, %ebp
 * 
 * --stuff--
 * 
 * epilogue:
 *      movl $return_val, eax
 *      popl     %ebp
 *      ret
 * 
 */

int top_reg_stack = 2;
int reg_stack[STACK_LENGTH] = {0,1,2};
char *reg_names[STACK_LENGTH] = {
    "%ebx",
    "%esi",
    "%edi"
};

void gen_stmt(tree_t *node);
void gen_expr(tree_t *node, int left);
int leaf_node(tree_t *node);
int label_node(tree_t *node, int left);