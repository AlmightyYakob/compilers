#ifndef TYPE_H
#define TYPE_H

typedef struct type_s {
    int tree_node_type;
    int super_type;

    
    // struct type_s sub_type;

    // union {
    //     int expr_type; /* For expressions */
    // } subtype;

} type_t;

// void eval_type(tree_t *root);


#endif