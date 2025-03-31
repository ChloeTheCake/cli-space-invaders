#include "../include/projectile.h"

void spawnProjectile(NodeContainer* nodeCon, struct projectile proj) {
    //Node* node = (Node*)malloc(sizeof(Node));
    addNodeToGenericList(nodeCon, &proj, sizeof(proj));



    /*node->data.dmg = proj.dmg;*/
    /*node->data.speed = proj.speed;*/
    /*node->data.posX = proj.posX;*/
    /*node->data.posY = proj.posY;*/
    /*addProjectileToList(nodeCon, node);*/

}

/*void addProjectileToList(struct nodeContainer* nodeCon, NODE* node) {*/
/*    if(nodeCon->first == NULL && nodeCon->last == NULL) {*/
/*        nodeCon->first = node;*/
/*        nodeCon->last= node;*/
/*        nodeCon->last->next = NULL;*/
/*    }*/
/*    else if (nodeCon->first != NULL && nodeCon->last != NULL) {*/
/*        nodeCon->last->next = node;*/
/*        nodeCon->last = node;*/
/*        nodeCon->last->next = NULL;*/
/*    }*/
/*}*/
/**/
/*void freeAllNodes(struct nodeContainer* nodeCon) {*/
/*    if (nodeCon->first != NULL && nodeCon->last != NULL) {*/
/*        NODE* currentNode = nodeCon->first;*/
/**/
/*        while(1) {*/
/*            // Should be last node*/
/*            if (currentNode->next == NULL) {*/
/*                free(currentNode);*/
/*                return;*/
/*            }*/
/*            // Otherwise...*/
/*            else {*/
/*                NODE* nodeToFree = currentNode;*/
/*                currentNode = currentNode->next;*/
/*                free(nodeToFree);*/
/*            }*/
/*        }*/
/*    }*/
/*}*/
/**/
/*void removeAtIndex(struct nodeContainer* nodeCon, int index) {*/
/*    if (nodeCon->first != NULL && nodeCon->last != NULL) {*/
/*        NODE* currentNode = nodeCon->first;*/
/**/
/*        for(int i = 0; i < index - 1; i++) {*/
/*            if (currentNode->next == NULL) {*/
/*                assert(false);*/
/*            }*/
/*            currentNode = currentNode->next;*/
/*        }*/
/**/
/*        // Free if it's in the middle of the list*/
/*        if (currentNode != nodeCon->first && currentNode->next != nodeCon->last) {*/
/*            NODE* nodeToFree = currentNode->next;*/
/*            currentNode->next = currentNode->next->next;*/
/*            free(nodeToFree);*/
/*        }*/
/*        // Free if it's the ONLY node in the list*/
/*        else if (currentNode == nodeCon->first && currentNode == nodeCon->last) {*/
/*            free(currentNode);*/
/*            nodeCon->first = NULL;*/
/*            nodeCon->last = NULL;*/
/*        }*/
/*        // Free if it's the first node in the list*/
/*        else if (currentNode == nodeCon->first && currentNode != nodeCon->last) {*/
/*            nodeCon->first = currentNode->next;*/
/*            free(currentNode);*/
/*        }*/
/*        // Free if it's the last node in the list*/
/*        else if (currentNode->next == nodeCon->last) {*/
/*            NODE* nodeToFree = currentNode->next;*/
/*            free(nodeToFree);*/
/*            currentNode->next = NULL;*/
/*            nodeCon->last = currentNode;*/
/*        }*/
/*        // Otherwise something has gone very wrong*/
/*        else {*/
/*            assert(false);*/
/*        }*/
/*    }*/
/*}*/
