#include "../include/update.h"
#include <assert.h>

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

// For the record this function is totally shit and needs rebuilt!
void checkIfProjectilesHitEnemy(struct game* game) {
    // NOTE: All the diff, posDiff shit is because basically the position of a projectile is
    // one xy value, but an enemy could be multiple long, but yet it also only holds a position
    // of one xy value... AND a length, which is used in these instances to basically check over
    // the whole length of the enemies xy it ACTUALLY occupies

    // start iterating over projectiles
    if (game->player.projectiles.first != NULL && game->player.projectiles.last != NULL) {
        Node* currentProjectileNode = game->player.projectiles.first;
        for(int projectileIndex = 0; true; projectileIndex++) {

            // start iterating over enemies per projectile
            if (game->hostile.enemies.first != NULL && game->hostile.enemies.last != NULL) {
                Node* currentEnemyNode = game->hostile.enemies.first;
                for(int enemyIndex = 0; true; enemyIndex++) {


                    //check if projectile and enemy occupy the same Y
                    if (((struct projectile*)currentProjectileNode->data)->posY
                            == ((struct enemy*)currentEnemyNode->data)->posY) {

                        int positionDiff = ((struct enemy*)currentEnemyNode->data)->length;

                        // For loop to check over the length of an enemy
                        for(int i = 0; i < positionDiff; i++) {

                            // inside the if (multi-line if ew)
                            // Check if the X is the same now
                            if (((struct projectile*)currentProjectileNode->data)->posX
                                    == ((struct enemy*)currentEnemyNode->data)->posX + i) {
                                // inside the second if (multi-line if ew)
                                // Set next BEFORE removing them

                                if (currentProjectileNode == game->player.projectiles.last) {
                                    removeAtIndex(&game->hostile.enemies, enemyIndex);
                                    removeAtIndex(&game->player.projectiles, projectileIndex);
                                    return;
                                }
                                else if (currentEnemyNode == game->hostile.enemies.last) {
                                    if (currentEnemyNode->next == NULL) {
                                        currentEnemyNode = game->hostile.enemies.first;
                                    }
                                    else {
                                        currentEnemyNode = currentEnemyNode->next;
                                    }
                                    currentProjectileNode = currentProjectileNode->next;

                                    removeAtIndex(&game->hostile.enemies, enemyIndex);
                                    removeAtIndex(&game->player.projectiles, projectileIndex);

                                    break;
                                    // continue;

                                }
                                else if (currentProjectileNode != game->player.projectiles.last 
                                        && currentEnemyNode != game->hostile.enemies.last) {
                                    currentEnemyNode = currentEnemyNode->next;
                                    currentProjectileNode = currentProjectileNode->next;

                                    removeAtIndex(&game->hostile.enemies, enemyIndex);
                                    removeAtIndex(&game->player.projectiles, projectileIndex);
                                    break;
                                    // continue;
                                }
                                else {
                                    assert(false);
                                }
                            }
                        }
                    }
                    if (currentEnemyNode == game->hostile.enemies.last) {
                        break;
                    }
                    else if (currentEnemyNode->next != NULL) {
                        currentEnemyNode = currentEnemyNode->next;
                    }
                    else {
                        assert(false);
                    }
                }
            }
            if (currentProjectileNode == game->player.projectiles.last) {
                break;
            }
            else if (currentProjectileNode->next != NULL) {
                currentProjectileNode = currentProjectileNode->next;
            }
            else {
                assert(false);
            }
        }
    }
}

// Lets make this a better version of the one above JFC
void checkIfPlayerProjectileHitBarrier(struct game* game) {
    int index = 0;
    if (game->player.projectiles.first == NULL || game->player.projectiles.last == NULL) {
        return;
    }

    // Iterate over all barriers
    for(int i = 0; i < TOTAL_BARRIERS; i++) {
        // Continue if the barrier is dead
        if (game->barriers[i].health == 0) {
            continue;
        }
        index = 0;
        Node *currentNode = game->player.projectiles.first;
        // Iterate over all projectiles
        for(; currentNode != NULL;) {

            if (((struct projectile*)currentNode->data)->posY != game->barriers[i].posY) {
                currentNode = currentNode->next;
                index++;
                continue;
            }
            if (((struct projectile*)currentNode->data)->posX < game->barriers[i].posX
                    || ((struct projectile*)currentNode->data)->posX > game->barriers[i].posX + BARRIER_WIDTH) {
                currentNode = currentNode->next;
                index++;
                continue;
            }
            currentNode = currentNode->next;
            removeAtIndex(&game->player.projectiles, index);
        }
    }









    // NEW
    // if (game->player.projectiles.first == NULL || game->player.projectiles.last == NULL) {
    //     return;
    // }
    //
    //
    //
    // // Loop over all barriers
    // for(int i = 0; i < TOTAL_BARRIERS; i++) {
    //     if (game->player.projectiles.first == NULL || game->player.projectiles.last == NULL) {
    //         return;
    //     }
    //     Node* currentNode = game->player.projectiles.first;
    //     // for loop for index tracking
    //     for(int index = 0; true; index++) {
    //         // continue early if projectile posX isn't within the barrier X bounds... per barrier
    //         if (((struct projectile*)currentNode->data)->posX < game->barriers[i].posX
    //                 || ((struct projectile*)currentNode->data)->posX > game->barriers[i].posX + BARRIER_WIDTH) {
    //             if (currentNode == game->player.projectiles.last) {
    //                 break;
    //             }
    //             currentNode = currentNode->next;
    //             continue;
    //         }
    //         if (((struct projectile*)currentNode->data)->posY != game->barriers[i].posY) {
    //             if (currentNode == game->player.projectiles.last) {
    //                 break;
    //             }
    //             currentNode = currentNode->next;
    //             continue;
    //         }
    //         // At this point the projectile occupies the same space as a barrier does... At least in theory
    //         if (currentNode == game->player.projectiles.last) {
    //             removeAtIndex(&game->player.projectiles, index);
    //             break;
    //         }
    //         else {
    //             currentNode = currentNode->next;
    //             removeAtIndex(&game->player.projectiles, index);
    //             // index--;
    //             continue;
    //         }
    //     }
    // }
}

