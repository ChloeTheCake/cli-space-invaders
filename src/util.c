#include "../include/util.h"

void addNodeToGenericList(NodeContainer* nodeCon, void* data, int dataSize) {
    if (nodeCon->first == NULL && nodeCon->last == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->next = NULL;

        newNode->data = malloc(dataSize);
        memcpy(newNode->data, data, dataSize);

        nodeCon->first = newNode;
        nodeCon->last = newNode;
    }
    else if (nodeCon->first != NULL && nodeCon->last != NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->next = NULL;

        newNode->data = malloc(dataSize);
        memcpy(newNode->data, data, dataSize);

        nodeCon->last->next = newNode;
        nodeCon->last = newNode;
    }
    else {
        assert(false);
    }
}

void removeAtIndex(NodeContainer* nodeCon, int index) {
    if (nodeCon->first != NULL && nodeCon->last != NULL) {
        Node* currentNode = nodeCon->first;

        for(int i = 0; i < index - 1; i++) {
            if (currentNode->next == NULL) {
                assert(false);
            }
            currentNode = currentNode->next;
        }

        // Free if it's in the middle of the list
        if (currentNode != nodeCon->first && currentNode->next != nodeCon->last) {
            Node* nodeToFree = currentNode->next;
            currentNode->next = currentNode->next->next;
            free(nodeToFree->data);
            free(nodeToFree);
        }
        // Free if it's the ONLY node in the list
        else if (currentNode == nodeCon->first && currentNode == nodeCon->last) {
            free(currentNode->data);
            free(currentNode);
            nodeCon->first = NULL;
            nodeCon->last = NULL;
        }
        // Free if it's the first node in the list
        else if (currentNode == nodeCon->first && currentNode != nodeCon->last) {
            nodeCon->first = currentNode->next;
            free(currentNode->data);
            free(currentNode);
        }
        // Free if it's the last node in the list
        else if (currentNode->next == nodeCon->last) {
            Node* nodeToFree = currentNode->next;
            free(nodeToFree->data);
            free(nodeToFree);
            currentNode->next = NULL;
            nodeCon->last = currentNode;
        }
        // Otherwise something has gone very wrong
        else {
            assert(false);
        }
    }
}

void removeAllNodes(NodeContainer* nodeCon) {
    if (nodeCon->first != NULL && nodeCon->last != NULL) {
        Node* currentNode = nodeCon->first;

        while(1) {
            // Should be last node
            if (currentNode->next == NULL) {
                free(currentNode->data);
                free(currentNode);
                nodeCon->first = NULL;
                nodeCon->last = NULL;
                return;
            }
            // Otherwise...
            else {
                Node* nodeToFree = currentNode;
                currentNode = currentNode->next;
                free(nodeToFree->data);
                free(nodeToFree);
            }
        }
    }
}

bool isEven(int num) {
    if (num % 2 == 0) {
        return true;
    }
    else {
        return false;
    }
}
