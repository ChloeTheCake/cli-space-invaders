#pragma once

// include deps
#include <pthread.h>
#include <ncurses.h>

// Custom header deps
#include "projectile.h"

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

};

struct game {
    struct config config;
    struct proc proc;
    WINDOW* win;

    struct player player;
    struct nodeContainer projectiles;

    bool shouldExit;
};
