#pragma once

// Include deps
#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>

#include "util.h"

// ALL STRUCTS
struct projectile {
    int posX;
    int posY;
    int dmg;
    int speed;
};

/*typedef struct node {*/
/*    struct node* next;*/
/*    struct projectile data;*/
/*} NODE;*/
/**/
/*struct nodeContainer {*/
/*    NODE* first;*/
/*    NODE* last;*/
/*};*/

// ALL FUNCTIONS
void spawnProjectile(NodeContainer* nodeCon, struct projectile proj);
/*void addProjectileToList(struct nodeContainer* nodeCon, NODE* node);*/
/*void freeAllNodes(struct nodeContainer* nodeCon);*/
/*void removeAtIndex(struct nodeContainer* nodeCon, int index);*/
