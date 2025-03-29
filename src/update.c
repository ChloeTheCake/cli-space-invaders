#include "../include/update.h"
#include "../include/projectile.h"

void updatePlayerState(struct game* game) {
    game->player.posX += game->player.dirX;

}

void updateProjectileState(struct game* game) {
    if (game->projectiles.first != NULL && game->projectiles.last != NULL) {
        NODE* currentNode = game->projectiles.first;

        while(1) {
            currentNode->data.posY += currentNode->data.speed;
            if (currentNode == game->projectiles.last) {
                break;
            }
            currentNode = currentNode->next;
        }
    }
}

void removeProjectilesOutOfBounds(struct game* game) {
    if (game->projectiles.first != NULL && game->projectiles.last != NULL) {
        NODE* currentNode = game->projectiles.first;

        for(int i = 0; i < MAX_ITERS; i++) {
            if (currentNode->data.posY < -2) { // ERROR IS HERE (Fixed but keep in mind this might break again)
                if (currentNode->next != NULL) {
                    currentNode = currentNode->next;
                }
                removeAtIndex(&game->projectiles, i);
            }


            if (currentNode->next == NULL || game->projectiles.first == NULL || game->projectiles.last == NULL) {
                return;
            }
            currentNode = currentNode->next;
        } // for loop ends
        assert(false); // if we hit max iters something might've gone wrong
    }
}
