#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "../include/util.h"

DynamicArray initDynamicArray(int typeSize) {
    DynamicArray dynArr;

    dynArr.capacity = 0;
    dynArr.size = 0;
    dynArr.memberSize = typeSize;
    dynArr.tag = ARR_OK;
    dynArr.contents.data = NULL;


    return dynArr;
}

void pushToDynArray(DynamicArray* dynArray, void* data) {
    switch (dynArray->tag) {
        case ARR_OK:
            if (dynArray->size > dynArray->capacity) {
                assert(false);
            }
            if (dynArray->size == dynArray->capacity) {
                augmentDynamicArray(dynArray);
            }
            if (dynArray->tag == ARR_ERROR) {
                fprintf(stderr, "ERROR IN DYNAMIC ARRAY: %s", dynArray->contents.error);
                assert(false);
            }
            memcpy((char*)dynArray->contents.data + (dynArray->memberSize * dynArray->size), data, dynArray->memberSize);
            dynArray->size += 1;
            return;

        case ARR_ERROR:
            fprintf(stderr, "ERROR IN DYNAMIC ARRAY: %s\n", dynArray->contents.error);
            assert(false);
    }
}

void augmentDynamicArray(DynamicArray* dynArray) {
    int growthFactor = 2;

    switch (dynArray->tag) {
        case ARR_OK:
            if (dynArray->capacity == 0) {
                dynArray->contents.data = malloc(dynArray->memberSize);
                if (dynArray->contents.data == NULL) {
                    dynArray->tag = ARR_ERROR;
                    strncpy(dynArray->contents.error, "Unable to create first element of dynamic array", sizeof(dynArray->contents.error) - 1);
                }
                dynArray->capacity = 1;
                return;
            }

            dynArray->contents.data = realloc(dynArray->contents.data, dynArray->memberSize * (dynArray->capacity * growthFactor));
            if (dynArray->contents.data == NULL) {
                dynArray->tag = ARR_ERROR;
                strncpy(dynArray->contents.error, "Unable to resize dynamic array", sizeof(dynArray->contents.error) - 1);
            }
            else {
                dynArray->capacity *= growthFactor;
                return;
            }

        case ARR_ERROR:
            fprintf(stderr, "ERROR IN 'augmentDynamicArray': %s\n", dynArray->contents.error);

        default:
            assert(false);
    }
}

int removeFromArray(DynamicArray* dynArray, int index) {
    if (dynArray->tag == ARR_ERROR) {
        fprintf(stderr, "Found an error'd array while trying to remove: %s", dynArray->contents.error);
        assert(false);
    }
    if (index > dynArray->size) {
        return -1;
    }

    if (index == dynArray->size) {
        dynArray->size -= 1;
        return 0;
    }

    void* check = NULL;
    check = memmove(
            (char*)dynArray->contents.data + (dynArray->memberSize * index),
            (char*)dynArray->contents.data + (dynArray->memberSize * (index + 1)),
            dynArray->memberSize * ((dynArray->size - index) - 1)
            );

    if (check == NULL) {
        dynArray->tag = ARR_ERROR;
        strncpy(dynArray->contents.error, "Unable to move right side of array while removing", sizeof(dynArray->contents.error) - 1);
        return -1;
    }

    dynArray->size -= 1;
    return 0;
}

bool isEven(int num) {
    if (num % 2 == 0) {
        return true;
    }
    else {
        return false;
    }
}
