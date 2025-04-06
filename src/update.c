#include "../include/update.h"
#include <assert.h>

void updatePlayerState(struct game* game) {
    game->player.posX += game->player.dirX;

}

void updateProjectileState(DynamicArray* dynArray) {
    if (dynArray->tag != ARR_OK) {
        return;
    }

    for(int i = 0; i < dynArray->size; i++) {
        ((struct projectile*)dynArray->contents.data)[i].posY += ((struct projectile*)dynArray->contents.data)[i].speed;
    }
}

void removeProjectilesOutOfBounds(DynamicArray* projs) {
    if (projs->tag != ARR_OK) {
        return;
    }

    for(int i = 0; i < projs->size; i++) {
        if (((struct projectile*)projs->contents.data)[i].posY > -2) {
            continue;
        }
        removeFromArray(projs, i);
    }
}

void checkIfProjectilesHitEnemy(DynamicArray* projs, DynamicArray* enemies) {
    if (projs->tag != ARR_OK || enemies->tag != ARR_OK) {
        return;
    }

    for(int projIndex = 0; projIndex < projs->size; projIndex++) {
        for(int enemyIndex = 0; enemyIndex < enemies->size; enemyIndex++) {
            if (((struct projectile*)projs->contents.data)[projIndex].posY
                    != ((struct enemy*)enemies->contents.data)[enemyIndex].posY) {
                continue;
            }
            if (((struct projectile*)projs->contents.data)[projIndex].posX
                    < ((struct enemy*)enemies->contents.data)[enemyIndex].posX
                    || ((struct projectile*)projs->contents.data)[projIndex].posX
                    > ((struct enemy*)enemies->contents.data)[enemyIndex].posX
                    + ((struct enemy*)enemies->contents.data)[enemyIndex].length) {
                continue;
            }
            removeFromArray(enemies, enemyIndex);
            removeFromArray(projs, projIndex);
            projIndex--;
            break;
        }
    }
}

void checkIfPlayerProjectileHitBarrier(DynamicArray* projs, struct barrier barriers[]) {
    if (projs->tag != ARR_OK) {
        return;
    }

    for(int i = 0; i < TOTAL_BARRIERS; i++) {
        if (barriers[i].health <= 0) {
            continue;
        }

        for(int projIndex = 0; projIndex < projs->size; projIndex++) {
            if (((struct projectile*)projs->contents.data)[projIndex].posY != barriers[i].posY) {
                continue;
            }
            if (((struct projectile*)projs->contents.data)[projIndex].posX < barriers[i].posX
                    || ((struct projectile*)projs->contents.data)[projIndex].posX > barriers[i].posX + BARRIER_WIDTH) {
                continue;
            }
            removeFromArray(projs, projIndex);
            projIndex--;
        }
    }
}

