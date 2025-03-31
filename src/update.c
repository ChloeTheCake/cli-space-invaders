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

void checkIfProjectilesHitEnemy(struct game* game) {
    // NOTE: All the diff, posDiff shit is because basically the position of a projectile is
    // one xy value, but an enemy could be multiple long, but yet it also only holds a position
    // of one xy value... AND a length, which is used in these instances to basically check over
    // the whole length of the enemies xy it ACTUALLY occupies

    // First we start iterating over all the enemies...
    if (game->hostile.enemies.first != NULL && game->hostile.enemies.last != NULL) {
        Node* currentEnemyNode = game->hostile.enemies.first;
        while(1) {
            // ...And for each enemy we iterate over all the projectiles, checking their position
            if (game->player.projectiles.first != NULL && game->player.projectiles.last != NULL) {
                Node* currentProjectileNode = game->player.projectiles.first;
                // I'm making this into a for loop to track the index
                // while(1) {
                for(int i = 0; true; i++) {
                    int posDiff = ((struct enemy*)currentEnemyNode->data)->length; // - 1

                    // This just checks across the length of the enemy
                    for(int index = 0; i < posDiff; index++) {
                        if (((struct projectile*)currentProjectileNode->data)->posY
                                != ((struct enemy*)currentEnemyNode->data)->posY) {
                            continue;
                        }
                        // in this case we hit the enemy
                        if (((struct projectile*)currentProjectileNode->data)->posX
                                == ((struct enemy*)currentEnemyNode->data)->posX + i) {
                            // removeEnemyFromWindow(index);
                            removeAtIndex(&game->hostile.enemies, index);
                        }
                        else {
                            assert(false);
                        }
                    }

                    // Break from iterating over projectiles
                    if (currentProjectileNode == game->player.projectiles.last) {
                        break;
                    }
                    currentProjectileNode = currentProjectileNode->next;
                }
            }

            // Break from iterating over all enemies
            if (currentEnemyNode == game->hostile.enemies.last) {
                break;
            }
            currentEnemyNode = currentEnemyNode->next;
        }
    }
}
