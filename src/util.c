#pragma once
#include <stdlib.h>
#include <assert.h>
#include "../include/util.h"
#include <ncurses.h>

// Woah globals
static NODE* last = NULL;
static NODE* first = NULL;

NODE* spawnProjectile(int posX, int posY, int dmg, int speed) {
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->data.dmg = dmg;
    node->data.speed = speed;
    node->data.posX = posX;
    node->data.posY = posY;
    addProjectileToList(node);

    return node;
}


void addProjectileToList(NODE* node) {
    if (last == NULL) {
        first = node;
        last = node;
        // Literally points to itself, used for some other checks
        last->next = node;
    }
    else if (last != NULL) {
        last->next = node;
        node->next = first;
        last = node;
    }
}

struct projectile* getListIndex(int index, NODE* lastNode) {
    // This is where things get strange
    int timesToAdvance = index;
    // getting first allows me to check for wrapping by checking if it's first again
    NODE* currentNode = lastNode->next;

    // This WILL wrap
    for(int i = 0; i < timesToAdvance; i++) {
        currentNode = currentNode->next;
        if (currentNode == lastNode) {
            // wrapping isn't cool kids
            assert("false");
        }
    }
    return &currentNode->data;
}

void removeAtIndex(int index) {
    int timesToAdvance = index;
    // setting it to be the first allows us to determine the end easier
    // and thus break a loop
    NODE* currentNode = last->next;

    if (last == last->next) {
        free(last);
        first->next = NULL;
        first = NULL;
        last->next = NULL;
        last = NULL;
    }

    for(int i = 0; i < timesToAdvance - 1; i++) {
        currentNode = currentNode->next;
        if (currentNode == last) {
            // wrapping isn't cool kids
            assert("false");
        }

        // skip over the target node
        currentNode->next = currentNode->next->next;

        if (currentNode->next == last) {
            last = currentNode;
        }

        // set the actual target to free
        currentNode = currentNode->next;

        free(currentNode);
    }
}

void wDebugPrint(const char* msg) {
    mvprintw(5, 5, msg);
}























/*linked list for any type?????*/


/*void* createLinkedList(int size) {*/
/*    void* heapPtr = NULL;*/
/*    heapPtr = malloc(size);*/
/*}*/
