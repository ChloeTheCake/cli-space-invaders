#include "../include/render.h"

void renderPlayer(struct game* game) {
    mvaddstr(game->player.posY, game->player.posX, "_/|\\_");
}

void renderEnemies(DynamicArray* dynArray) {
    if (dynArray->tag != ARR_OK) {
        return;
    }

    for(int i = 0; i < dynArray->size; i++) {
        mvaddstr(((struct enemy*)dynArray->contents.data)[i].posY, ((struct enemy*)dynArray->contents.data)[i].posX, "*");
    }
}

void renderProjectiles(DynamicArray* dynArray) {
    if (dynArray->tag != ARR_OK) {
        return;
    }

    for(int i = 0; i < dynArray->size; i++) {
        mvaddstr(((struct projectile*)dynArray->contents.data)[i].posY, ((struct projectile*)dynArray->contents.data)[i].posX, "+");
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

