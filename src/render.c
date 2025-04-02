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

void renderBarriers(struct game* game) {
    for(int i = 0; i < TOTAL_BARRIERS; i++) {
        for(int j = 0; j < game->barriers[i].health; j++) {
            // goes from barrier posY upward, so bottom left # is the true position
            mvaddstr(game->barriers[i].posY - j, game->barriers[i].posX, "#####");
        }
    }
}
