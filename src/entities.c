#include <stdbool.h>
#include <ncurses.h>

#include "../include/entities.h"
#include "../include/game.h"

// 11x5 enemies with one space between them so 22x5
void spawnEnemiesOnNewscreen(struct game* game) {
    int leftPadding = 0;
    //int enemyOccupyWidth = ENEMY_WIDTH * ENEMY_PADDING;
    int enemyOccupyHeight = ENEMY_HEIGHT;
    int rightWall = getmaxx(game->win);

    if(isEven(rightWall)) {
        leftPadding = (rightWall - ENEMY_OCCUPIES_WIDTH) / 2;
    }
    else {
        leftPadding = (rightWall - (ENEMY_OCCUPIES_WIDTH + 1)) / 2;
    }

    for(int i = 0; i < enemyOccupyHeight; i++) { // Columns
        for(int j = 0; j < ENEMY_OCCUPIES_WIDTH; j++) { // Rows
            if((j % ENEMY_PADDING) != 0) {
                continue;
            }

            struct enemy enemyTemplate;
            enemyTemplate.alive = true;
            enemyTemplate.posX = j + leftPadding; // left right
            enemyTemplate.posY = i + 2;
            enemyTemplate.length = 1;

            pushToDynArray(&game->hostile.enemies, &enemyTemplate);
        }
    }
}

void createBarriers(struct game* game) {
    for(int i = 0; i < TOTAL_BARRIERS; i++) {
        int winWidth = getmaxx(game->win);
        int barrierOccupyWidth = winWidth * BARRIER_OCCUPIES_WINPERCENT;
        int leftPadding = (winWidth - barrierOccupyWidth) / 2;
        int barrierPadding = (barrierOccupyWidth / (TOTAL_BARRIERS - 1)) - 2;
        // the - 2 is to get to the middle of the barrier which has a width of 4
        // the -1 is because there are X barriers but X-1 spaces between

        game->barriers[i].posX = leftPadding + (barrierPadding * i);
        game->barriers[i].posY = getmaxy(game->win) - BARRIER_RAISED_BY;
        game->barriers[i].health = BARRIER_MAX_HEALTH;
    }
}

