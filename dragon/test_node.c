#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "node.h"

int main() {
    node_t *top = NULL;
    node_t *tmp;

    int choice;
    char name[32];

    while(1){
        fprintf(stderr, "(0) node_search (1) node_insert (2) print: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 0:     /* node_search */
                fprintf(stderr, "Name to node_search: ");
                scanf("%s", name);
                tmp = node_search(top, name);
                if (tmp != NULL) fprintf(stderr, "Found[%s]\n", tmp->name);
                else fprintf(stderr, "Not Found[%s]\n", name);
                break;
            case 1:     /* node_insert */
                fprintf(stderr, "Name to node_insert: ");
                scanf("%s", name);
                top = node_insert(top, name);
                break;
            case 2:     /* print */
                node_print(top);
            default:
                break;
        }
    }
}