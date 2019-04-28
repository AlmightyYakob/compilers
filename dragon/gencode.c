#include <stdio.h>
#include <stdlib.h>
#include "gencode.h"
#include "y.tab.h"

extern FILE *OUTFILE;
extern node_t *BUILTIN_READ;
extern node_t *BUILTIN_WRITE;

/* Start at 3 because 0 and 1 used for printf int and float, 2 used for scanf of int */
int CURR_IDENT = 3;

int VAR_OFFSET = 8;

int top_rstack_i = 2;
int rstack[STACK_LENGTH] = {0,1,2};
char *rnames[STACK_LENGTH] = {
    "%ebx",
    "%esi",
    "%edi"
};

char *convert_op(tree_t *opnode){
    switch (opnode->type){
        case ADDOP:
            switch (opnode->attribute.opval){
                case PLUS:
                    return "addl";
                    break;

                case MINUS:
                    return "subl";
                    break;

                case OR:
                    /* code */
                    fprintf(stderr, "ADDOP - OR\n");
                    break;
            
                default:
                    fprintf(stderr, "ADDOP - DEFAULT\n");
                    break;
            }
            break;

        case MULOP:
            /* code */
            fprintf(stderr, "MULOP\n");
            break;

        case RELOP:
            /* code */
            fprintf(stderr, "RELOP\n");
            break;
    
        default:
            fprintf(stderr, "DEFAULT CASE IN COVERT_OP\n");
            break;
    }
}

int get_byte_offset(tree_t *id_node){
    return id_node->attribute.sval->offset*4;
}

void handle_write_call(tree_t *call_node){
    if (call_node->right->type == ID){
        fprintf(OUTFILE, "\tpushl\t-%d(%%ebp)\n", VAR_OFFSET + get_byte_offset(call_node->right));

        if (call_node->right->attribute.sval->type.super_type == INTEGER) {
            fprintf(OUTFILE, "\tpushl\t$.LC0\n");
        }
        else if (call_node->right->attribute.sval->type.super_type == REAL) {
            fprintf(OUTFILE, "\tpushl\t$.LC1\n");
        }
    }
    else {
        if (call_node->right->type == INUM) {
            fprintf(OUTFILE, "\tpushl\t$%d\n", call_node->right->attribute.ival);
            fprintf(OUTFILE, "\tpushl\t$.LC0\n");
        }
        if (call_node->right->type == RNUM) {
            fprintf(OUTFILE, "\tpushl\t$%f\n", call_node->right->attribute.rval);
            fprintf(OUTFILE, "\tpushl\t$.LC1\n");
        }
    }

    fprintf(OUTFILE, "\tcall\tprintf\n");
    fprintf(OUTFILE, "\taddl\t$8, %%esp\n");
}

void handle_read_call(tree_t *call_node){
    if (call_node->right->type == ID){
        fprintf(OUTFILE, "\tpushl\t-%d(%%ebp)\n", VAR_OFFSET + get_byte_offset(call_node->right));

        if (call_node->right->attribute.sval->type.super_type == INTEGER) {
            fprintf(OUTFILE, "\tpushl\t$.LC2\n");
        }
        else if (call_node->right->attribute.sval->type.super_type == REAL) {
            // fprintf(OUTFILE, "\tpushl\t$.LC3\n");
        }
    }
    else {
        fprintf(stderr, "CALLING WRITE ON CONSTANT\n");
    }

    fprintf(OUTFILE, "\tcall\tscanf\n");
    fprintf(OUTFILE, "\taddl\t$4, %%esp\n");
    fprintf(OUTFILE, "\tpopl\t-%d(%%ebp)\n", VAR_OFFSET + get_byte_offset(call_node->right));
}

/* Stack Routines */

int top_rstack() {
    return rstack[top_rstack_i];
}

int pop_rstack() {
    if (top_rstack > 0) return rstack[top_rstack_i--];
    else {
        fprintf(stderr, "CANNOT POP, ONLY 1 REGISTER IN STACK\n");
        return rstack[top_rstack_i];
    }
}

void push_rstack(int reg_index) {
    if (top_rstack_i + 1 < STACK_LENGTH) rstack[++top_rstack_i] = reg_index;
    else fprintf(stderr, "CANNOT PUSH, MAX REGISTERS IN STACK\n");
}

void swap_rstack() {
    int a = pop_rstack();
    int b = pop_rstack();

    push_rstack(a);
    push_rstack(b);
}

void print_rstack(){
    int i;
    fprintf(stderr, "RSTACK: [");
    for (i=0; i <= top_rstack_i; i++){
        fprintf(stderr, "%s", rnames[rstack[i]]);

        if (i != top_rstack_i) fprintf(stderr, ", ");
    }
    fprintf(stderr, "]\n");
}

void gen_format_section() {
    fprintf(OUTFILE, "\t.section\t.rodata\n");
    
    /* For printf */
    fprintf(OUTFILE, ".LC0:\n");
    fprintf(OUTFILE, "\t.string \"%%d\\n\"\n");
    fprintf(OUTFILE, ".LC1:\n");
    fprintf(OUTFILE, "\t.string \"%%f\\n\"\n");

    /* For scanf */
    fprintf(OUTFILE, ".LC2:\n");
    fprintf(OUTFILE, "\t.string \"%%d\"\n");

}

void gen_file_header() {
    // fprintf(stderr, "\t.file\t\"%s.s\"\n", filename);
    gen_format_section();
    fprintf(OUTFILE, "\t.text\n");
    fprintf(OUTFILE, "\t.globl\tmain\n");
    fprintf(OUTFILE, "\t.type\tmain, @function\n");
}

void gen_main_footer() {
     fprintf(OUTFILE, "\t.size   main, .-main\n");
     fprintf(OUTFILE, "\t.section    .text.__x86.get_pc_thunk.ax,\"axG\",@progbits,__x86.get_pc_thunk.ax,comdat\n");
     fprintf(OUTFILE, "\t.globl  __x86.get_pc_thunk.ax\n");
     fprintf(OUTFILE, "\t.hidden __x86.get_pc_thunk.ax\n");
     fprintf(OUTFILE, "\t.type   __x86.get_pc_thunk.ax, @function\n");
     fprintf(OUTFILE, "__x86.get_pc_thunk.ax:\n");
     fprintf(OUTFILE, "\tmovl    (%%esp), %%eax\n");
     fprintf(OUTFILE, "\tret\n");
     fprintf(OUTFILE, "\t.ident  \"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0\"\n");
     fprintf(OUTFILE, "\t.section    .note.GNU-stack,\"\",@progbits\n");
}

void gen_prologue(char *func_name, int record_size) {
    fprintf(OUTFILE, "%s:\n", func_name);
    fprintf(OUTFILE, "\tpushl\t%%ebp\n");
    fprintf(OUTFILE, "\tmovl\t%%esp, %%ebp\n");
    if (record_size > 0) fprintf(OUTFILE, "\tsubl\t$%d, %%esp\n", record_size);
}

void gen_epilogue(int record_size, int useVal, char *returnval_loc, int return_val) {
    if (useVal) fprintf(OUTFILE, "\tmovl\t$%d, %%eax\n", return_val);
    else fprintf(OUTFILE, "\tmovl\t%s, %%eax\n", returnval_loc);

    if (record_size > 0) fprintf(OUTFILE, "\taddl\t$%d, %%esp\n", record_size);

    fprintf(OUTFILE, "\tpopl\t%%ebp\n");
    fprintf(OUTFILE, "\tret\n");
}

void gen_main(const char *prog_name) {
    gen_prologue("main", 0);
    fprintf(OUTFILE, "\tcall\t%s\n", prog_name);
    gen_epilogue(0, 1, NULL, 0);
}

/* Type of call_node should be either proc_call or func_call */
void gen_function_call(tree_t *call_node){
    if (call_node->type != PROCEDURE_CALL && call_node->type != FUNCTION_CALL) return;

    arg_node_t *curr_arg = call_node->left->attribute.sval->func_arguments;
    tree_t *curr_tree_arg = call_node->right;

    while(curr_arg != NULL) {
        if (curr_tree_arg->type != LISTOP) {
            /* Last iteration of loop */

            if (curr_tree_arg->type == ID){
                /* push that arg onto stack */
                fprintf(OUTFILE, "\tpushl\t-%d(%%ebp)\n", curr_tree_arg->attribute.sval->offset);
            }
            else {
                /* push val onto stack */
            }
            
            break;
        }
        
        if (curr_tree_arg->right->type == ID){
            /* push that arg onto stack */
            fprintf(OUTFILE, "\tpushl\t-%d(%%ebp)\n", curr_tree_arg->right->attribute.sval->offset);
        }
        else {
            /* push val onto stack */
            
            /* Maybe this:  */
            /* call gen_expr */
            /* push value in register at top of stack */
            fprintf(OUTFILE, "\tpushl\t-%d(%%ebp)\n", curr_tree_arg->right->attribute.sval->offset);

        }

        curr_arg = curr_arg->next;
        curr_tree_arg = curr_tree_arg->left;
    }
}

void gen_write_format() {
    fprintf(OUTFILE, ".LC%d:\n", CURR_IDENT);
    fprintf(OUTFILE, "\t.string \"%d\"\n", CURR_IDENT);
    
}

/* Wrapper for gen_expr */
void gen_stmt(tree_t *node){
    switch (node->type) {
        case LISTOP:
            gen_stmt(node->left);
            gen_stmt(node->right);
            break;
        case IF:
            fprintf(stderr, "GEN_STMT - IF\n");
            break;
        
        case FOR:
            fprintf(stderr, "GEN_STMT - FOR\n");
            break;
        
        case WHILE:
            fprintf(stderr, "GEN_STMT - WHILE\n");
            break;
        
        case ASSIGNOP:
            fprintf(stderr, "GEN_STMT - ASSIGNOP\n");
            /* If right is a func call, call gen_func_call instead of gen_expr */
            gen_expr(node->right, 1);

            /* val should be in top register. Move that into mem_loc of var */
            fprintf(OUTFILE, "\tmovl\t%s, -%d(%%ebp)\n",rnames[top_rstack()], VAR_OFFSET + get_byte_offset(node->left));
            
            break;

        case PROCEDURE_CALL:
            fprintf(stderr, "GEN_STMT - PROC_CALL\n");
            if (node->left->attribute.sval == BUILTIN_WRITE) {
                fprintf(stderr, "GEN_STMT - BUILTIN_WRITE\n");
                handle_write_call(node);
            }
            else if (node->left->attribute.sval == BUILTIN_READ) {
                fprintf(stderr, "GEN_STMT - BUILTIN_READ\n");
                handle_read_call(node);
            }
            else {
                /* Normal Case */
                // fprintf(OUTFILE, "\tcall\t%s", node->);

            }
            break;

        case BBEGIN:
            fprintf(stderr, "GEN_STMT - BBEGIN\n");
            if (node->left != NULL) gen_stmt(node->left);
            break;
    
        default:
            break;
    }
}

/* AKA gencode, left is 1 to represent its the left child or 0 if not */
void gen_expr(tree_t *node, int left){
    /* Replace with action out file */
    
    /* To store popped registers */
    int R;

    /* To store name of operation */
    char *opname;

    label_node(node, 1);

    /* Case 0 */
    if (left && node->left == NULL && node->right == NULL){
        fprintf(stderr, "GEN_EXPR - CASE 0\n");
        if (node->type == ID) {
            /* EVENTUALLY REPLACE THIS WITH MEM LOCATION OF VAR */
            // fprintf(OUTFILE, "\tmovl\t-%d(%%ebp), %s\n", node->attribute.sval->offset, rnames[top_rstack()]);
            fprintf(OUTFILE, "\tmovl\t%s, %s\n", node->attribute.sval->name, rnames[top_rstack()]);
        }
        else if (node->type == INUM){
            fprintf(OUTFILE, "\tmovl\t$%d, %s\n", node->attribute.ival, rnames[top_rstack()]);
        }
        else if (node->type == RNUM) {
            fprintf(OUTFILE, "\tmovl\t%f, %s\n", node->attribute.rval, rnames[top_rstack()]);
        }
    }
    /* Case 1 */
    else if (node->right->label ==  0){
        fprintf(stderr, "GEN_EXPR - CASE 1\n");
        opname = convert_op(node);

        gen_expr(node->left, 1);    
        if (node->right->type == ID)        fprintf(OUTFILE, "\t%s\t%s, %s\n", opname, node->right->attribute.sval->name, rnames[top_rstack()]);
        else if (node->right->type == INUM) fprintf(OUTFILE, "\t%s\t$%d, %s\n", opname, node->right->attribute.ival, rnames[top_rstack()]);
        else if (node->right->type == RNUM) fprintf(OUTFILE, "\t%s\t$%f, %s\n", opname, node->right->attribute.rval, rnames[top_rstack()]);
    }
    /* Case 2 */
    else if (1 <= node->left->label < node->right->label && node->left->label < (top_rstack_i + 1)) {
        fprintf(stderr, "GEN_EXPR - CASE 2\n");
        opname = convert_op(node);

        swap_rstack();
        gen_expr(node->right, 0);
        R = pop_rstack();
        gen_expr(node->left, 1);
        
        fprintf(OUTFILE, "\t%s\t%s, %s\n", opname, rnames[R], rnames[top_rstack()]);

        push_rstack(R);
        swap_rstack();
    }
    /* Case 3 */
    else if (1 <= node->right->label <= node->left->label && node->right->label < (top_rstack_i + 1)){
        fprintf(stderr, "GEN_EXPR - CASE 3\n");
        opname = convert_op(node);

        gen_expr(node->left, 1);
        R = pop_rstack();
        gen_expr(node->right, 0);
        fprintf(OUTFILE, "\t%s\t%s, %s\n", opname, rnames[top_rstack()], rnames[R]);
        push_rstack(R);
    }
    /* Case 4, ignoring this for now */
    else {
        fprintf(stderr, "GEN_EXPR - CASE 4\n");
    }

    // print_rstack();
}

/* Returns 1 if the passed node is a leaf node, else 0. */
int leaf_node(tree_t *node){ return (node->left == NULL && node->right == NULL); }

/* Gencode */
int label_node(tree_t *node, int left){
    /* Probably a few more cases here */
    if (node == NULL) return 0;
    else if (node->label != -1) return node->label;

    if (leaf_node(node)) {
        if (left) node->label = 1;
        else node->label = 0;
    }
    else {
        if (label_node(node->left, 1) == label_node(node->right, 0)) node->label = label_node(node->left, 1) + 1;
        else if (label_node(node->left, 1) > label_node(node->right, 0)) node->label = label_node(node->left, 1);
        else node->label = label_node(node->right, 0);
    }

    return node->label;
}
