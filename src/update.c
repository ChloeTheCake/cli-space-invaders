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
    if (game->player.projectiles.first == NULL || game->player.projectiles.last == NULL) {
        return;
    }

    Node* currentNode = game->player.projectiles.first;
    for(int index = 0; currentNode != NULL; index++) {
        if (((struct projectile*)currentNode->data)->posY > -2) {
            currentNode = currentNode->next;
            continue;
        }
        else {
            currentNode = removeAtIndex(&game->player.projectiles, index);
        }
    }
}

// For the record this function is totally shit and needs rebuilt!
void checkIfProjectilesHitEnemy(struct game* game) {
    if (game->player.projectiles.first == NULL || game->player.projectiles.last == NULL) {
        return;
    }
    if (game->hostile.enemies.first == NULL || game->hostile.enemies.last == NULL) {
        return;
    }

    Node* currentProjectileNode = game->player.projectiles.first;
    // start interating over projectiles
    for(int projIndex; currentProjectileNode != NULL; projIndex++) {
        // Start iterating over enemies
        Node* currentEnemyNode = game->hostile.enemies.first;
        for(int enemyIndex; currentEnemyNode != NULL; enemyIndex++) {
            if (((struct projectile*)currentProjectileNode->data)->posY
                    != ((struct enemy*)currentEnemyNode->data)->posY) {
                currentEnemyNode = currentEnemyNode->next;
                continue;
            }
            // check if it's to the left or right of an enemy, where the right of an
            // enemy is it's position + it's length
            if (((struct projectile*)currentProjectileNode->data)->posX
                    < ((struct enemy*)currentEnemyNode->data)->posX
                    || ((struct projectile*)currentProjectileNode->data)->posX
                    > ((struct enemy*)currentEnemyNode->data)->posX
                    + ((struct enemy*)currentEnemyNode->data)->length) {
                currentEnemyNode = currentEnemyNode->next;
                continue;
            }
            // Else we know it's a hit
            currentEnemyNode = removeAtIndex(&game->hostile.enemies, enemyIndex);
            currentProjectileNode = removeAtIndex(&game->player.projectiles, projIndex);
        }
        currentProjectileNode = currentProjectileNode->next;
    }
}

// Lets make this a better version of the one above JFC (post: it was)
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

