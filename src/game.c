#include <pthread.h>
#include <stdbool.h>
#include <ncurses.h>

// #include "../include/entities.h"
struct game;
#include "../include/game.h"

// Custom header deps

void createNewGame(struct game* game) {
    game->player.health = 100;
    game->player.dirX = 0;
    game->player.posX = 1; // center this sometime?????
    game->player.posY = getmaxy(game->win) - 4;
    game->player.projectiles.first = NULL;
    game->player.projectiles.last = NULL;
    game->hostile.enemies.first = NULL;
    game->hostile.enemies.last = NULL;
    game->hostile.enemyProjectiles.first = NULL;
    game->hostile.enemyProjectiles.last = NULL;
    createBarriers(game);

    spawnEnemiesOnNewscreen(game);
}

void createBarriers(struct game* game) {
    for(int i = 0; i < TOTAL_BARRIERS; i++) {
        int winWidth = getmaxx(game->win);
        int barrierOccupyWidth = winWidth * 0.5; // BARRIER_OCCUPIES_WINPERCENT;
        int leftPadding = (winWidth - barrierOccupyWidth) / 2;


        game->barriers[i].posX = leftPadding + ((barrierOccupyWidth / TOTAL_BARRIERS) * i);
        game->barriers[i].posY = getmaxy(game->win) - 10;
        game->barriers[i].health = 4;
    }
}
