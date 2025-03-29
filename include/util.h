#pragma once

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    struct node* next;
    void* data;
} Node;

typedef struct nodeContainer {
    Node* first;
    Node* last;
} NodeContainer;

// Functions
void addNodeToGenericList(NodeContainer* nodeCon, void* data, int dataSize);
void removeAtIndex(NodeContainer* nodeCon, int index);
void removeAllNodes(NodeContainer* nodeCon);
