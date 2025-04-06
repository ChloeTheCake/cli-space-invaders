#pragma once
#include <stdbool.h>

enum dynTags {
    ARR_OK,
    ARR_ERROR
};

union dynData {
    void* data;
    char error[256];
};

typedef struct dynamicArray {
    int size;
    int capacity;
    int memberSize;
    enum dynTags tag;
    union dynData contents;
} DynamicArray;


// Functions
bool isEven(int num);
DynamicArray initDynamicArray(int typeSize);
void pushToDynArray(DynamicArray* dynArray, void* data);
void augmentDynamicArray(DynamicArray* dynArray);
int removeFromArray(DynamicArray* dynArray, int index);
