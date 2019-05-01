#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "gencode.h"
#include "scope.h"
#include "y.tab.h"

extern FILE *OUTFILE;
extern node_t *BUILTIN_READ;
extern node_t *BUILTIN_WRITE;
extern scope_t *top_scope;

const int VAR_OFFSET = 8;
const int VAR_SIZE = 4;

/* Start at 3 because 0 and 1 used for printf int and float, 2 used for scanf of int */
int CURR_IDENT = 3;

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
        fprintf(stderr, "ADDOP\n");
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
            fprintf(stderr, "MULOP\n");
            switch (opnode->attribute.opval) {
                case STAR:
                    return "mul";
                    break;

                case SLASH:
                    /* code */
                    break;

                case DIV:
                    return "div";
                    break;

                case MOD:
                    /* code */
                    break;

                case AND:
                    /* code */
                    break;

                default:
                    break;
            }
            break;
        case RELOP:
            /* code */
            fprintf(stderr, "RELOP\n");
            break;
    
        default:
            fprintf(stderr, "DEFAULT CASE IN COVERT_OP: %d\n", opnode->type);
            return "???";
            break;
    }
}

/* Determines which register to use for offset */
char *get_ref_reg(tree_t *id_node) {
    if (id_node->scope_offset == 0) return "%%ebp";
    else                            return "%%ecx";
}

void gen_nonlocal_lookup(tree_t *id_node){
    if (id_node->scope_offset == 0) return;

    fprintf(OUTFILE, "\tmovl\t-4(%%ebp). %%ecx");

    int i;
    for (i = 0; i < id_node->scope_offset; i++) {
        fprintf(OUTFILE, "\tmovl\t(%%ecx). %%ecx");
    }
}

int get_byte_offset(tree_t *id_node){
    assert(id_node->type == ID);
    return id_node->attribute.sval->offset*VAR_SIZE + VAR_OFFSET;
}

void handle_write_call(tree_t *call_node){
    if (call_node->right->type == ID){
        fprintf(OUTFILE, "\tpushl\t-%d(%%ebp)\n", get_byte_offset(call_node->right));

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
    /**
     * Process should be:
     *      leal var address into some register
     *      push that register
     *      push format
     *      call scanf
     *      add 8 (for now) back to esp
    */

    if (call_node->right->type == ID){
        fprintf(OUTFILE, "\tleal\t-%d(%%ebp), %s\n", get_byte_offset(call_node->right),  rnames[top_rstack()]);
        fprintf(OUTFILE, "\tpushl\t%s\n", rnames[top_rstack()]);

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
    fprintf(OUTFILE, "\taddl\t$8, %%esp\n");
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

    /* Assigning Static Parent */
    fprintf(OUTFILE, "\tmovl\t%%ecx, -4(%%ebp)\n");
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
    int num_args = 0;

    while(curr_arg != NULL) {
        num_args++;
        /* Last iteration of loop */
        if (curr_tree_arg->type != LISTOP) {
            if (curr_tree_arg->type == ID){
                /* push that arg onto stack */

                fprintf(OUTFILE, "\tpushl\t-%d(%%ebp)\n", get_byte_offset(curr_tree_arg));
            }
            else {
                /* Maybe this:  */
                /* call gen_expr */
                /* push value in register at top of stack */

                gen_expr(curr_tree_arg, 1);
                fprintf(OUTFILE, "\tpushl\t%s\n", rnames[top_rstack()]);
            }
            break;
        }
        
        /* Normal Loop Execution */
        if (curr_tree_arg->right->type == ID){
            /* push that arg onto stack */
            fprintf(OUTFILE, "\tpushl\t-%d(%%ebp)\n", get_byte_offset(curr_tree_arg->right));
        }
        else {
            /* Maybe this:  */
            /* call gen_expr */
            /* push value in register at top of stack */

            gen_expr(curr_tree_arg->right, 1);
            fprintf(OUTFILE, "\tpushl\t%s\n", rnames[top_rstack()]);
        }

        curr_arg = curr_arg->next;
        curr_tree_arg = curr_tree_arg->left;
    }

    /* All args now pushed onto stack */
    
    /* Scope_search on callee */
    /* If result == NULL, then callee is child */
    /* Else, callee is a child */

    if (scope_search(top_scope, call_node->left->attribute.sval->name) == NULL) {
        /* Sibling */
        /* This means that name of callee is in scope above, since inserted there */
        /* Pass own static parent to child */
        fprintf(OUTFILE, "\tmovl\t-4(%%ebp), %%ecx\n");
    }
    else {
        /* Child */
        /* This means that name of callee is in current scope, and child scope is the callee's scope */
        /* Pass own base pointer to child */
        fprintf(OUTFILE, "\tmovl\t%%ebp, %%ecx\n");
    }

    /* Call function */
    fprintf(OUTFILE, "\tcall\t%s\n", call_node->left->attribute.sval->name);
    
    /* Add num_args*VAR_SIZE back to esp */
    fprintf(OUTFILE, "\addl\t$%d, %%esp\n", num_args*VAR_SIZE);
}

void gen_mulop(tree_t *node, int case_num, int R, char *return_loc) {
    /* mul R --> eax = eax*R */
    /* result is in EDX:EAX. */
    /* div R --> eax = eax/R */
    /* mod R = edx, given above */
    /* EAX contains result, EDX contains remainder */

    switch(node->attribute.opval) {
        case STAR:
            /* move val 2 into eax */
            switch(case_num) {
                case 1:
                    if      (node->right->type == ID)   fprintf(OUTFILE, "\tmovl\t-%d(%%ebp), %%eax\n", get_byte_offset(node->right));
                    else if (node->right->type == INUM) fprintf(OUTFILE, "\tmovl\t$%d, %%eax\n", node->right->attribute.ival);
                    else if (node->right->type == RNUM) fprintf(OUTFILE, "\tmovl\t$%f, %%eax\n", node->right->attribute.rval);
                    break;
                case 2:
                case 3:
                    fprintf(OUTFILE, "\tmovl\t%s, %%eax\n", rnames[R]);
                    break;
            }

            /* mul top of stack*/
            fprintf(OUTFILE, "\tmul\t\t%s\n", rnames[top_rstack()]);
            /* mov eax into return_loc */
            fprintf(OUTFILE, "\tmovl\t%%eax, %s\n", return_loc);
            break;

        case SLASH:
            break;

        case DIV:
        case MOD:
            switch(case_num) {
                case 1:
                case 2:
                    fprintf(OUTFILE, "\tmovl\t%s, %%eax\n", rnames[top_rstack()]);
                    if (case_num == 2) fprintf(OUTFILE, "\tmovl\t%s, %s\n", rnames[R], rnames[top_rstack()]);
                    else if (node->right->type == ID)   fprintf(OUTFILE, "\tmovl\t-%d(%%ebp), %s\n", get_byte_offset(node->right), rnames[top_rstack()]);
                    else if (node->right->type == INUM) fprintf(OUTFILE, "\tmovl\t$%d, %s\n", node->right->attribute.ival, rnames[top_rstack()]);
                    else if (node->right->type == RNUM) fprintf(OUTFILE, "\tmovl\t$%f, %s\n", node->right->attribute.rval, rnames[top_rstack()]);
                    break;
                case 3:
                    fprintf(OUTFILE, "\tmovl\t%s, %%eax\n", rnames[R]);
                    break;
            }

            fprintf(OUTFILE, "\tmovl\t$0, %%edx\n");
            fprintf(OUTFILE, "\tdiv\t\t%s\n", rnames[top_rstack()]);

            if (node->attribute.opval == MOD)   fprintf(OUTFILE, "\tmovl\t%%edx, %s\n", return_loc);
            else                                fprintf(OUTFILE, "\tmovl\t%%eax, %s\n", return_loc);
            break;

        case AND:
            break;
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
            int then_lc = CURR_IDENT++;
            int end_lc  = CURR_IDENT++;
            
            /* Gen the expr and first cond. jump */
            gen_bool_expr(node->left, then_lc);

            /* Else case */
            gen_stmt(node->right->right);
            fprintf(OUTFILE, "\tjmp\t.LC%d\n", end_lc);
            
            /* Then case */
            fprintf(OUTFILE, ".LC%d:\n", then_lc);
            gen_stmt(node->right->left);

            fprintf(OUTFILE, ".LC%d:\n", end_lc);
            break;
        
        case FOR: {
            fprintf(stderr, "GEN_STMT - FOR\n");
            int start_lc = CURR_IDENT++;
            int body_lc = CURR_IDENT++;
            int R;
            
            /* Set initial val */
            gen_stmt(node->left->left);

            fprintf(OUTFILE, "\tjmp\t.LC%d\n", start_lc);
            fprintf(OUTFILE, ".LC%d:\n", body_lc);
            gen_stmt(node->right);

            /* increment val */
            gen_expr(node->left->left->left, 1);
            fprintf(OUTFILE, "\taddl\t$1, %s\n", rnames[top_rstack()]);
            fprintf(OUTFILE, "\tmovl\t%s, -%d(%%ebp)\n", rnames[top_rstack()], get_byte_offset(node->left->left->left));

            fprintf(OUTFILE, ".LC%d:\n", start_lc);
            gen_expr(node->left->right, 1);
            R = pop_rstack();
            gen_expr(node->left->left->left, 1);

            /* R contains the expr to check against */
            /* Top of stack contains the var to check */
            fprintf(OUTFILE, "\tcmpl\t%s, %s\n", rnames[top_rstack()], rnames[R]);
            fprintf(OUTFILE, "\tjge\t.LC%d\n", body_lc);
            break;
        }

        case WHILE: {
            fprintf(stderr, "GEN_STMT - WHILE\n");

            int start_lc = CURR_IDENT++;
            int body_lc = CURR_IDENT++;
            
            fprintf(OUTFILE, "\tjmp\t.LC%d\n", start_lc);
            fprintf(OUTFILE, ".LC%d:\n", body_lc);
            gen_stmt(node->right);

            fprintf(OUTFILE, ".LC%d:\n", start_lc);
            gen_bool_expr(node->left, body_lc);
            break;
        }
        
        case ASSIGNOP:
            fprintf(stderr, "GEN_STMT - ASSIGNOP\n");
            /* If right is a func call, call gen_func_call instead of gen_expr */
            gen_expr(node->right, 1);

            /* val should be in top register. Move that into mem_loc of var */
            fprintf(OUTFILE, "\tmovl\t%s, -%d(%%ebp)\n",rnames[top_rstack()], get_byte_offset(node->left));
            
            break;

        case PROCEDURE_CALL:
        case  FUNCTION_CALL:
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
                gen_function_call(node);
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

void gen_bool_expr(tree_t *node, int then_lc) {
    /* node is root of bool expr to test */
    /* node->type should be RELOP I think */
    /* then_lc is the .LCX number to jump to if the comparison is true */
    int R;

    gen_expr(node->left, 1);
    R = pop_rstack();
    gen_expr(node->right, 1);
    // fprintf(OUTFILE, "\tcmpl\t%s, %s\n", rnames[R], rnames[top_rstack()]);
    fprintf(OUTFILE, "\tcmpl\t%s, %s\n", rnames[top_rstack()], rnames[R]);

    /* To decide what to test */
    switch (node->attribute.opval) {
        case EQ:
            fprintf(OUTFILE, "\tje\t.LC%d\n", then_lc);
            break;
            
        case NE:
            fprintf(OUTFILE, "\tjne\t.LC%d\n", then_lc);
            break;

        case LT:
            fprintf(OUTFILE, "\tjl\t.LC%d\n", then_lc);
            break;

        case LE:
            fprintf(OUTFILE, "\tjle\t.LC%d\n", then_lc);
            break;

        case GT:
            fprintf(OUTFILE, "\tjg\t.LC%d\n", then_lc);
            break;

        case GE:
            fprintf(OUTFILE, "\tjge\t.LC%d\n", then_lc);
            break;

        default:
            break;
    }
}

/* AKA gencode, left is 1 to represent its the left child or 0 if not */
/* Left is always 1 if it is the root of an expression tree */
void gen_expr(tree_t *node, int left){
    /* To store name of operation */
    char *opname;

    label_node(node, 1);

    /* Case 0 */
    if (left && node->left == NULL && node->right == NULL){
        int R = -1;
        fprintf(stderr, "GEN_EXPR - CASE 0\n");
        if (node->type == ID) {
            /* EVENTUALLY REPLACE THIS WITH MEM LOCATION OF VAR */
            // fprintf(OUTFILE, "\tmovl\t%s, %s\n", node->attribute.sval->name, rnames[top_rstack()]);
            fprintf(OUTFILE, "\tmovl\t-%d(%%ebp), %s\n", get_byte_offset(node), rnames[top_rstack()]);
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
        int R = -1;
        fprintf(stderr, "GEN_EXPR - CASE 1\n");
        opname = convert_op(node);
        gen_expr(node->left, 1);

        if (node->type == MULOP){
            gen_mulop(node, 1, R, rnames[top_rstack()]);
        }
        else {
            if      (node->right->type == ID)   fprintf(OUTFILE, "\t%s\t-%d(%%ebp), %s\n", opname, get_byte_offset(node->right), rnames[top_rstack()]);
            else if (node->right->type == INUM) fprintf(OUTFILE, "\t%s\t$%d, %s\n", opname, node->right->attribute.ival, rnames[top_rstack()]);
            else if (node->right->type == RNUM) fprintf(OUTFILE, "\t%s\t$%f, %s\n", opname, node->right->attribute.rval, rnames[top_rstack()]);
        }
    }
    /* Case 2 */
    else if (1 <= node->left->label < node->right->label && node->left->label < (top_rstack_i + 1)) {
        int R = -1;
        fprintf(stderr, "GEN_EXPR - CASE 2\n");
        opname = convert_op(node);

        swap_rstack();
        gen_expr(node->right, 0);
        R = pop_rstack();
        gen_expr(node->left, 1);

        if (node->type == MULOP) {
            gen_mulop(node, 2, R, rnames[top_rstack()]);
        }
        else {
            fprintf(OUTFILE, "\t%s\t%s, %s\n", opname, rnames[R], rnames[top_rstack()]);
        }
        
        push_rstack(R);
        swap_rstack();
    }
    /* Case 3 */
    else if (1 <= node->right->label <= node->left->label && node->right->label < (top_rstack_i + 1)){
        int R = -1;
        fprintf(stderr, "GEN_EXPR - CASE 3\n");
        opname = convert_op(node);

        gen_expr(node->left, 1);
        R = pop_rstack();
        gen_expr(node->right, 0);

        if (node->type == MULOP) {
            gen_mulop(node, 3, R, rnames[R]);
        }
        else {
            fprintf(OUTFILE, "\t%s\t%s, %s\n", opname, rnames[top_rstack()], rnames[R]);
        }

        push_rstack(R);
    }
    /* Case 4, ignoring this for now */
    else {
        fprintf(stderr, "GEN_EXPR - CASE 4\n");
    }
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
