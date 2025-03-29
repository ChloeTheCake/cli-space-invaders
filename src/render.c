#include "../include/render.h"

void renderPlayer(struct game* game) {
    int bottom = getmaxy(game->win) - 4;
    mvaddstr(bottom, game->player.posX, "_/|\\_");
}

void renderProjectiles(struct game* game) {
    if (game->player.projectiles.first != NULL && game->player.projectiles.last != NULL) {
        Node* currentNode = game->player.projectiles.first;

        while(1) {
            mvaddstr(((struct projectile*)currentNode->data)->posY, ((struct projectile*)currentNode->data)->posX + 2, "+");
            if (currentNode == game->player.projectiles.last) {
                break;
            }
            currentNode = currentNode->next;
        }
    }
}
