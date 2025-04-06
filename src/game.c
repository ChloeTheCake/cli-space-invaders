#include <pthread.h>
#include <stdbool.h>
#include <ncurses.h>

// struct game;
#include "../include/game.h"

void createNewGame(struct game* game) {
    game->player.health = 100;
    game->player.dirX = 0;
    game->player.posX = 1; // center this sometime?????
    game->player.posY = getmaxy(game->win) - 4;
    game->player.projectiles = initDynamicArray(sizeof(struct projectile));
    game->hostile.enemies = initDynamicArray(sizeof(struct enemy));
    game->hostile.enemyProjectiles = initDynamicArray(sizeof(struct projectile));

    createBarriers(game);
    spawnEnemiesOnNewscreen(game);
}

