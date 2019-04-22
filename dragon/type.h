#ifndef TYPE_H
#define TYPE_H

typedef struct type_s {
    int tree_node_type;
    int super_type;

    /* Boolean indicating whether type is an array or not */
    int array;
    
} type_t;



#endif