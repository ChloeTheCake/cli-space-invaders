#include "../include/render.h"

void renderPlayer(struct game* game) {
    mvaddstr(game->player.posY, game->player.posX, "_/|\\_");
}

void renderEnemies(struct game* game) {
    if (game->hostile.enemies.first != NULL && game->hostile.enemies.last != NULL) {
        Node* currentNode = game->hostile.enemies.first;

        while(1) {
            mvaddstr(((struct enemy*)currentNode->data)->posY, ((struct enemy*)currentNode->data)->posX, "*");
            if (currentNode == game->hostile.enemies.last) {
                break;
            }
            currentNode = currentNode->next;
        }
    }

}



void renderProjectiles(struct game* game) {
    if (game->player.projectiles.first != NULL && game->player.projectiles.last != NULL) {
        Node* currentNode = game->player.projectiles.first;

        while(1) {
            mvaddstr(((struct projectile*)currentNode->data)->posY, ((struct projectile*)currentNode->data)->posX, "+");
            if (currentNode == game->player.projectiles.last) {
                break;
            }
            currentNode = currentNode->next;
        }
    }
}
