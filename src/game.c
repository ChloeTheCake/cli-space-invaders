#include <pthread.h>
#include <stdbool.h>
#include <ncurses.h>

#include "../include/game.h"
#include "../include/enemy.h"

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

    spawnEnemiesOnNewscreen(game);
}
