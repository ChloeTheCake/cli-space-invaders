#pragma once

#define    MAX_ITERS    216

#include "game.h"

// Functions
void updatePlayerState(struct game* game);
void updateProjectileState(struct game* game);
void removeProjectilesOutOfBounds(struct game* game);

void checkIfProjectilesHitEnemy(struct game* game);
void checkIfPlayerProjectileHitBarrier(struct game* game);
//void removeEnemyFromWindow();
