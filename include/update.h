#pragma once

#include "util.h"
#define    MAX_ITERS    216

#include "game.h"

// Functions
void updatePlayerState(struct game* game);
void updateProjectileState(DynamicArray* dynArray);
void removeProjectilesOutOfBounds(DynamicArray* projs);
void checkIfProjectilesHitEnemy(DynamicArray* projs, DynamicArray* enemies);
void checkIfPlayerProjectileHitBarrier(DynamicArray* projs, struct barrier barriers[]);
void moveEnemies(WINDOW* win, DynamicArray* enemies, int start, int end, int dirX, int dirY, bool shouldWrap);
