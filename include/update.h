#pragma once

#define    MAX_ITERS    216

#include "game.h"
#include "projectile.h"
#include "util.h"

// Functions
void updatePlayerState(struct game* game);
void updateProjectileState(struct game* game);
void removeProjectilesOutOfBounds(struct game* game);

void checkIfProjectilesHitEnemy(struct game* game);
//void removeEnemyFromWindow();
