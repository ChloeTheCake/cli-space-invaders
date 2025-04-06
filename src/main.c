#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>

// MY OWN HEADERS AHA!!!
#include "../include/game.h"
#include "../include/update.h"
#include "../include/render.h"
#include "../include/util.h"
#include "../include/config.h"

Config promptConfig();
void procUserControl(struct game* game);
void update(struct game* game);
void render(struct game* game);


// ##################################################################
int main() {

    // Set all the defaults and init everything, probably should pull this into
    // it's own function at some point...
    struct game game;
    game.win = initscr();
    createNewGame(&game);
    keypad(game.win, true);
    nodelay(game.win, true);
    curs_set(false);

    game.shouldExit = false;
    while(!game.shouldExit) {
        // Every frame this shall loop

        procUserControl(&game); // right now this is rendering changes (Let this be
                                // a lesson that comments get bugs, this hasn't been true forever)
        update(&game);
        render(&game);
        usleep(20000);
    }

    free(game.player.projectiles.contents.data);
    free(game.hostile.enemies.contents.data);
    endwin();
    return 0;
}

// ##################################################################

void render(struct game* game) {
    erase();
    renderPlayer(game);
    renderBarriers(game);
    renderEnemies(&game->hostile.enemies);
    renderProjectiles(&game->player.projectiles);
}

void update(struct game* game) {
    updatePlayerState(game);
    // updateProjectileState(game);
    updateProjectileState(&game->player.projectiles);
    checkIfPlayerProjectileHitBarrier(&game->player.projectiles, game->barriers);
    checkIfProjectilesHitEnemy(&game->player.projectiles, &game->hostile.enemies);
    removeProjectilesOutOfBounds(&game->player.projectiles);
}



void procUserControl(struct game* game) {
    int keyPressed = wgetch(game->win);

    if (keyPressed == 'q') {
        game->shouldExit = true;
    }
    if (keyPressed == ERR) {
        game->player.dirX = 0;
    }
    if (keyPressed == KEY_LEFT) {
        game->player.dirX = -PLAYER_SPEED;
    }
    if (keyPressed == KEY_RIGHT) {
        game->player.dirX = PLAYER_SPEED;
    }
    if (keyPressed == KEY_UP) {
        struct projectile proj;
        proj.dmg = 1;
        proj.speed = -PROJECTILE_SPEED;
        proj.posY = getmaxy(game->win) - 4; // 4 is an offset so it's not at the very bottom
        proj.posX = game->player.posX + SPACE_TO_PLAYER_CENTER;
        pushToDynArray(&game->player.projectiles, &proj);
    }

    game->player.posX += game->player.dirX;
}

