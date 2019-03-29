#ifndef TYPE_H
#define TYPE_H

typedef struct type_s {
    int tree_node_type;

    union {
        int expr_type; /* For expressions */
    } subtype;
} type_t;

#endif