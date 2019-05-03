#ifndef GENCODE_H
#define GENCODE_H

#include "tree.h"
#include "node.h"

/* How many registers in the stack */
#define RSTACK_LENGTH 3

/* How many temp memnory locations for large expressions */
#define TSTACK_LENGTH 2

/* Size of each var/entry in activation record */
#define VAR_SIZE 4

/*
 * ACTIVATION RECORD LAYOUT
 * -----------------------------------
 * 
 * Lower Memory Addresses
 * -----------------------------------
 * | Passing Argument 1
 * -----------------------------------
 * | Passing Argument 2
 * -----------------------------------
 * | Passing Argument 3 - n
 * -----------------------------------
 * | Local Variables = 4*numVars    ✓
 * -----------------------------------
 * | Temp Expr Memory 2 = 4 bytes ✓
 * -----------------------------------
 * | Temp Expr Memory 1 = 4 bytes ✓
 * -----------------------------------
 * | Static Parent Pointer  = 4 bytes ✓
 * -----------------------------------
 * | Previous Base Pointer          ✓
 * -----------------------------------
 * | Return Address                 ✓
 * --------------------------------------------- <-- Divider between function activation records
 * | Passed Argument 1
 * -----------------------------------
 * | Passed Argument 2
 * -----------------------------------
 * | Passed Argument 3 - n
 * -----------------------------------
 * 
 * Higher Memory Addresses
 *
 * 
 **** Could handle passing arguments by just pushing vars onto stack when they're called, and then adding after
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
 *      subl     $record_size, %esp
 * 
 * --stuff--
 * 
 * epilogue:
 *      movl $return_val, eax
 *      popl     %ebp
 *      ret
 * 
 */

/* Index of top (end) of rstack */
int top_rstack_i;

int top_tstack_i;

/* Stores indices to rnames array */
int rstack[RSTACK_LENGTH];

/* Stores integers that represent mem locations */
int tstack[TSTACK_LENGTH];

/* Stores name of registers to use */
char *rnames[RSTACK_LENGTH];

/* Stores the current identifier num */
int CURR_IDENT;

/* Offset into the variable portion of the stack */
const int VAR_OFFSET;



char *convert_op(tree_t *opnode);
int get_byte_offset(tree_t *id_node);
void gen_array_access(tree_t *access_node);

void handle_write_call(tree_t *call_node);
void handle_read_call(tree_t *call_node);

int top_rstack();
int pop_rstack();
void push_rstack();
void swap_rstack();
void print_rstack();

void gen_format_section();
void gen_file_header();

void gen_main(const char *prog_name);
void gen_main_prologue();
void gen_main_epilogue();
void gen_main_footer();

void gen_prologue(tree_t *func_node, int record_size);
void gen_epilogue(tree_t *func_node, int record_size);

void gen_push_args(tree_t *arg);
int gen_get_args(tree_t *arg, int curr_arg);
void gen_function_call(tree_t *call_node);

void gen_mulop(tree_t *node, int case_num, int R, char *return_loc);
void gen_write_format();

void gen_stmt(tree_t *node);
void gen_bool_expr(tree_t *node, int then_lc);
void gen_expr(tree_t *node, int left);
int leaf_node(tree_t *node);
int label_node(tree_t *node, int left);

#endif
