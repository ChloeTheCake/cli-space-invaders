#include "../include/enemy.h"
#include "../include/game.h"

// 11x5 enemies with one space between them so 22x5
void spawnEnemiesOnNewscreen(struct game* game) {
    int remainingSpace = 0;
    int rightWall = getmaxx(game->win);
    if(isEven(rightWall)) {
        remainingSpace = (rightWall - 22) / 2;
    }
    else {
        remainingSpace = (rightWall - 23) / 2;
    }

    for(int i = 0; i < 5; i++) { // Columns
        for(int j = 0; j < 22; j++) { // Rows
            if(!isEven(j)) {
                continue;
            }

            struct enemy enemyTemplate;
            enemyTemplate.alive = true;
            enemyTemplate.posX = j + remainingSpace; // left right
            enemyTemplate.posY = i + 2;

            addNodeToGenericList(&game->hostile.enemies, &enemyTemplate, sizeof(struct enemy));
        }
    }
}
