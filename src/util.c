#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

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

Node* removeAtIndex(NodeContainer* nodeCon, int index) {
    if (nodeCon->first != NULL && nodeCon->last != NULL) {
        Node* currentNode = nodeCon->first;

        // Minus one seems strange buts it's because to relink we have to start
        // at the node before, link it to the one after, then delete the one we
        // want to. If we went straight to the node we want to remove there is
        // no reference to the one behind it to relink it
        for(int i = 0; i < index - 1; i++) {
            if (currentNode->next == NULL) {
                assert(false);
            }
            currentNode = currentNode->next;
        }

        // Free if it's in the middle of the list
        if (currentNode->next != nodeCon->last && index != 0) {
            Node* nodeToFree = currentNode->next;
            Node* nodeToReturn = nodeToFree->next;
            currentNode->next = currentNode->next->next;
            nodeToFree->next = NULL;
            free(nodeToFree->data);
            nodeToFree->data = NULL;
            free(nodeToFree);
            nodeToFree = NULL;
            return nodeToReturn;
        }
        // Free if it's the ONLY node in the list
        else if (currentNode == nodeCon->first && currentNode == nodeCon->last) {
            free(currentNode->data);
            currentNode->data = NULL;
            currentNode->next = NULL;
            free(currentNode);
            currentNode = NULL;
            nodeCon->first = NULL;
            nodeCon->last = NULL;
            return NULL;
        }
        // Free if it's the first node in the list
        else if (currentNode == nodeCon->first && currentNode != nodeCon->last && index == 0) {
            nodeCon->first = currentNode->next;
            Node* nodeToReturn = currentNode->next;
            free(currentNode->data);
            currentNode->data = NULL;
            currentNode->next = NULL;
            free(currentNode);
            currentNode = NULL;
            return nodeToReturn;
        }
        // Free if it's the last node in the list
        else if (currentNode->next == nodeCon->last) {
            Node* nodeToFree = currentNode->next;
            free(nodeToFree->data);
            nodeToFree->data = NULL;
            nodeToFree->next = NULL;
            free(nodeToFree);
            nodeToFree = NULL;
            currentNode->next = NULL;
            nodeCon->last = currentNode;
            return NULL;
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
