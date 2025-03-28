#pragma once
#include <stdlib.h>
#include <assert.h>
#include "../include/util.h"
#include <ncurses.h>

// Woah globals
static NODE* last = NULL;
static NODE* first = NULL;

void spawnProjectile(struct nodeContainer* nodeCon, struct projectile proj) {
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->data.dmg = proj.dmg;
    node->data.speed = proj.speed;
    node->data.posX = proj.posX;
    node->data.posY = proj.posY;
    addProjectileToList(nodeCon, node);

}

void addProjectileToList(struct nodeContainer* nodeCon, NODE* node) {
    if(nodeCon->first == NULL && nodeCon->last == NULL) {
        nodeCon->first = node;
        nodeCon->last= node;
        nodeCon->last->next = NULL;
    }
    else if (nodeCon->first != NULL && nodeCon->last != NULL) {
        nodeCon->last->next = node;
        nodeCon->last = node;
        nodeCon->last->next = NULL;
    }
}
