// #include "tree.h"
// #include "type.h"
// #include "scope.h"
// #include "y.tab.h"

// int super_type(tree_t *node) {return node->left->type->super_type;}
// int child_types_match(tree_t *root){
//     return (super_type(root->left) == super_type(root->right));
// }

// /* Recusively sets the type->super_type for nodes in the syntax tree. */
// void eval_type(tree_t *root){
//     switch (root->type->tree_node_type){
//         case ID:
//             /* set super_type of ID to the symbol table entry */
//             root->type->super_type = root->attribute.sval->type;
//             break;
//         case RELOP:
//             /*
//              * Check that both children are same type.
//              * If so, return bool.
//              * Else, return error.
//              */
//             eval_type(root->left);
//             eval_type(root->right);
            
//             if (child_types_match(root)) root->type->super_type = BOOL;
//             else root->type->super_type = ERROR;

//             break;
//         case ADDOP:
//         case MULOP:
//             /* --ADDOP MULOP--
//              * Check that both children are same type.
//              * If so, return that type.
//              * Else, return error.
//              */

//             eval_type(root->left);
//             eval_type(root->right);

//             if (child_types_match(root)) root->type->super_type = super_type(root->left);
//             else root->type->super_type = ERROR;

//             break;
//         case INUM:
//             /* return INTEGER */
//             root->type->super_type = INTEGER;
//             break;
//         case RNUM:
//             /* return REAL */
//             root->type->super_type = REAL;
//             break;
//         case NOT:
//             /*
//              * check if child is type bool.
//              * If so, return bool.
//              * Else, error.
//             */
//             eval_type(root->left);
//             if (super_type(root->left) == BOOL) root->type->super_type = BOOL;
//             else root->type->super_type = ERROR;
            
//             break;

//         default:
//             break;
//     }

//     return;
// }