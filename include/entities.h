#pragma once

struct game;
#include "util.h"

struct projectile {
    int posX;
    int posY;
    int dmg;
    int speed;
};

struct player {
    int health;
    int dirX;
    int posX;
    int posY;
    // NodeContainer projectiles;
    DynamicArray projectiles;
};

struct enemy {
    int posX;
    int posY;
    int length;
    bool alive;
    /*enum enemyType enemyType;*/
};

struct hostile {
    DynamicArray enemies;
    DynamicArray enemyProjectiles;
};

// Here be the barriers, I figured they're entities too

struct barrier {
    int health; // max of 4?
    int posX;
    int posY;
};

void spawnEnemiesOnNewscreen(struct game* game);

