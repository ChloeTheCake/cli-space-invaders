#pragma once

#include "game.h"

// Functions
void renderPlayer(struct game* game);
void renderEnemies(DynamicArray* dynArray);
void renderProjectiles(DynamicArray* dynArray);
void renderBarriers(struct game* game);
