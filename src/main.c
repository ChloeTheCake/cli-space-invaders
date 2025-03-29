#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>

// MY OWN HEADERS AHA!!!
#include "../include/game.h"
#include "../include/projectile.h"
#include "../include/update.h"
#include "../include/render.h"
#include "../include/util.h"

// C doesn't come with true or false out of the box, only 1 or 0, so usually
// they'd be defined here but curses.h come with those already
/*#define     false                   0*/
/*#define     true                    1*/

#define     DEFAULT_SCR_WIDTH       30
#define     DEFAULT_SCR_HEIGHT      25


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
    game.player.health = 100;
    game.player.dirX = 0;
    game.player.posX = 0; // center this sometime?????
    game.player.projectiles.first = NULL;
    game.player.projectiles.last = NULL;
    keypad(game.win, true);
    nodelay(game.win, true);
    curs_set(false);

    game.shouldExit = false;
    while(!game.shouldExit) {
        // Every frame this shall loop

        procUserControl(&game); // right now this is rendering changes
        update(&game);
        render(&game);
        usleep(50000);
    }
    


    removeAllNodes(&game.player.projectiles);
    endwin();
    return 0;
}

// ##################################################################

void render(struct game* game) {
    erase();
    renderPlayer(game);
    renderProjectiles(game);
}

void update(struct game* game) {
    updatePlayerState(game);
    updateProjectileState(game);
    removeProjectilesOutOfBounds(game);
}



void procUserControl(struct game* game) {
    int keyPressed = wgetch(game->win);
    int bottom = getmaxy(game->win) - 4;

    if (keyPressed == 'q') {
        game->shouldExit = true;
    }
    if (keyPressed == ERR) {
        game->player.dirX = 0;
    }
    if (keyPressed == KEY_LEFT) {
        game->player.dirX = -2;
    }
    if (keyPressed == KEY_RIGHT) {
        game->player.dirX = 2;
    }
    if (keyPressed == KEY_UP) {
        struct projectile proj;
        proj.dmg = 1;
        proj.speed = -2;
        proj.posY = getmaxy(game->win) - 4;
        proj.posX = game->player.posX;
        spawnProjectile(&game->player.projectiles, proj);
    }

    game->player.posX += game->player.dirX;
}

void playerShootsProjectile() {

}













// This function just promts the user for config options
Config promptConfig() {
    // create two variables, a Config (struct config), and an
    // array of chars (literally just a byte) to store input into
    Config conf;
    char buff[16];

    // Prompt user input then try to get it from stdin, store into buff, and only read stdin to
    // the size of buff. I then check for NULL in case the read fails and force the program to
    // abort with assert if that is the case
    printf("What would you like your screen width to be in characters?\n(DEFAULT for defaults)\n=> ");
    if (fgets(buff, sizeof(buff), stdin) == NULL) {
        printf("Couldn't read input");
        assert(false);
    }

    // atoi turn a string (char array) into number or 0 if it cannot do so
    // so if it fails I check for 'DEFAULT' and if that's not the same assert
    unsigned int width = atoi(buff);
    if (width <= 0) {
        if (strncmp(buff, "DEFAULT", 7) == 0) {
            width = DEFAULT_SCR_WIDTH;
        }
        printf("Invalid input, use only numbers or 'DEFAULT'... Read: %d", width);
        assert(false);
    }

    printf("What would you like your screen height to be in characters?\n(DEFAULT for defaults)\n=> ");
    if (fgets(buff, sizeof(buff), stdin) == NULL) {
        printf("Couldn't read input");
        assert(false);
    }

    unsigned int height = atoi(buff);
    if (height <= 0) {
        if (strncmp(buff, "DEFAULT", 7) == 0) {
            height = DEFAULT_SCR_HEIGHT;
        }
        printf("Invalid input, use only numbers or 'DEFAULT'... Read: %d", height);
        assert(false);
    }

    // Set the values
    conf.scrWidth = width;
    conf.scrHeight = height;

    // Return config
    return conf;
}

