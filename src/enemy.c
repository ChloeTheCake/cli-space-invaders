#include <stdbool.h>
#include <ncurses.h>

#include "../include/util.h"
#include "../include/game.h"
#include "../include/enemy.h"
#include "../include/config.h"

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


            addNodeToGenericList(&game->hostile.enemies, &enemyTemplate, sizeof(struct enemy));
        }
    }
}
