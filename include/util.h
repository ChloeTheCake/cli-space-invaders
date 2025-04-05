#pragma once

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
Node* removeAtIndex(NodeContainer* nodeCon, int index);
void removeAllNodes(NodeContainer* nodeCon);
bool isEven(int num);
