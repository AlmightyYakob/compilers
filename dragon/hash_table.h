#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

union val_type {
    int inum_data;
    float rnum_data;
    char *str_data;
};

struct DataItem {
    int type;
    union val_type val;
    int key;
};

struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
   return key % SIZE;
}

struct DataItem *search(int key);
void insert(int key,int data);
struct DataItem* delete(struct DataItem* item);

void display();
