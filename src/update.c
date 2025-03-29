#include "../include/update.h"

void updatePlayerState(struct game* game) {
    game->player.posX += game->player.dirX;

}

void updateProjectileState(struct game* game) {
    if (game->player.projectiles.first != NULL && game->player.projectiles.last != NULL) {
        Node* currentNode = game->player.projectiles.first;

        while(1) {
            ((struct projectile*)currentNode->data)->posY += ((struct projectile*)currentNode->data)->speed;
            if (currentNode == game->player.projectiles.last) {
                break;
            }
            currentNode = currentNode->next;
        }
    }
}

void removeProjectilesOutOfBounds(struct game* game) {
    if (game->player.projectiles.first != NULL && game->player.projectiles.last != NULL) {
        Node* currentNode = game->player.projectiles.first;

        for(int i = 0; i < MAX_ITERS; i++) {
            if (((struct projectile*)currentNode->data)->posY < -2) { // ERROR IS HERE (Fixed but keep in mind this might break again)
                if (currentNode->next != NULL) {
                    currentNode = currentNode->next;
                }
                removeAtIndex(&game->player.projectiles, i);
            }


            if (currentNode->next == NULL || game->player.projectiles.first == NULL || game->player.projectiles.last == NULL) {
                return;
            }
            currentNode = currentNode->next;
        } // for loop ends
        assert(false); // if we hit max iters something might've gone wrong
    }
}
