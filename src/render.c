#include "../include/render.h"


void renderPlayer(struct game* game) {
    int bottom = getmaxy(game->win) - 4;
    mvaddstr(bottom, game->player.posX, "_/|\\_");
}

void renderProjectiles(struct game* game) {
    if (game->projectiles.first != NULL && game->projectiles.last != NULL) {
        NODE* currentNode = game->projectiles.first;

        while(1) {
            mvaddstr(currentNode->data.posY, currentNode->data.posX + 2, "+");
            if (currentNode == game->projectiles.last) {
                break;
            }
            currentNode = currentNode->next;
        }
    }
}
