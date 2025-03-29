#pragma once

// include deps
#include <pthread.h>
#include <stdbool.h>
#include <ncurses.h>

// Custom header deps
// #include "projectile.h"
#include "util.h"
#include "player.h"
#include "enemy.h"

// All the custom stuff
typedef struct config {
    unsigned int scrWidth;
    unsigned int scrHeight;
} Config;

struct proc {
    pthread_t projectileTid;
    pthread_t playerTid;
    pthread_t enemiesTid;
    /*pthread_t*/
};

struct player {
    int health;
    int dirX;
    int posX;
    NodeContainer projectiles;
};

/*enum enemyType {*/
/*};*/

struct enemy {
    int posX;
    int posY;
    bool alive;
    /*enum enemyType enemyType;*/
};

struct hostile {
    NodeContainer enemies;
    NodeContainer enemyProjectiles;
};

struct game {
    struct config config;
    struct proc proc;
    WINDOW* win;

    struct player player;
    struct hostile hostile;
    //struct nodeContainer projectiles;

    bool shouldExit;
};
