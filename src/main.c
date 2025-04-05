#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// #include "../include/enemy.h"

// C doesn't come with true or false out of the box, only 1 or 0, so usually
// they'd be defined here but curses.h come with those already
/*#define     false                   0*/
/*#define     true                    1*/

// Function definitions go here so main can be at the top
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

        procUserControl(&game); // right now this is rendering changes
        update(&game);
        render(&game);
        // usleep(20000);
        usleep(60000);
    }
    


    removeAllNodes(&game.player.projectiles);
    endwin();
    return 0;
}

// ##################################################################

void render(struct game* game) {
    erase();
    renderPlayer(game);
    renderBarriers(game);
    renderEnemies(game);
    renderProjectiles(game);
}

void update(struct game* game) {
    updatePlayerState(game);
    updateProjectileState(game);
    checkIfPlayerProjectileHitBarrier(game);
    // checkIfProjectilesHitEnemy(game);
    removeProjectilesOutOfBounds(game);
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
        spawnProjectile(&game->player.projectiles, proj);
    }

    game->player.posX += game->player.dirX;
}

