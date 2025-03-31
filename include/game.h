#pragma once

// include deps
#include <pthread.h>
#include <stdbool.h>
#include <ncurses.h>

// Custom header deps
#include "entities.h"

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


struct game {
    struct config config;
    struct proc proc;
    WINDOW* win;

    int level;
    struct player player;
    struct hostile hostile;
    //struct nodeContainer projectiles;

    bool shouldExit;
};

// Fuctions

void createNewGame(struct game* game);







