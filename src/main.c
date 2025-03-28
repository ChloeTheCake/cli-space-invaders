#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>

// MY OWN HEADERS AHA!!!
#include "../include/util.h"

// C doesn't come with true or false out of the box, only 1 or 0, so usually
// they'd be defined here but curses.h come with those already
/*#define     false                   0*/
/*#define     true                    1*/

#define     DEFAULT_SCR_WIDTH       30
#define     DEFAULT_SCR_HEIGHT      25


// I define a struct with typedef to give it a custom type...
typedef struct config {
    unsigned int scrWidth;
    unsigned int scrHeight;
} Config; // ... And name it here

struct proc {
    pthread_t projectileTid;
    pthread_t playerTid;
    pthread_t enemiesTid;
    /*pthread_t*/
};

struct player {
    int health;
    int dirX;
    int posX;

};

struct game {
    struct config config;
    struct proc proc;

    struct player player;
    struct node* projectiles;

    bool shouldExit;
};

// Function definitions go here so main can be at the top
Config promptConfig();
void procUserControl(WINDOW* win, struct game* game);
void update(struct game* game);
void render(WINDOW* win, struct game* game);


// ##################################################################
int main() {
    WINDOW* win = initscr();
    keypad(win, true);
    nodelay(win, true);

    struct game game;
    game.player.health = 100;
    game.player.dirX = 0;
    game.player.posX = 0; // center this sometime?????

    game.shouldExit = false;
    while(!game.shouldExit) {
        procUserControl(win, &game); // right now this is rendering changes
        // game.projectiles = spawnProjectile(1, 1, 1, 1);
        update(&game);
        render(win, &game);

        /*modifyValuesOnUserInput*/
        /*RenderChanges*/

        usleep(10000);
    }
    


    endwin();
    return 0;
}

// ##################################################################

void render(WINDOW* win, struct game* game) {
    int bottom = getmaxy(win) - 4;

    if (game->projectiles != NULL) {
        NODE* first = game->projectiles->next;
        NODE* currentNode = game->projectiles->next;

        erase();
        while(currentNode != first) {
            mvaddstr(currentNode->data.posY, currentNode->data.posX, "|");

            currentNode = currentNode->next;
        }
    }
    mvaddstr(bottom, game->player.posX, "_/|\\_");
}

void update(struct game* game) {
    if(game->projectiles == NULL) {
        return;
    }

    NODE* first = game->projectiles->next;
    NODE* currentNode = game->projectiles->next;

    while(currentNode != first) {
        currentNode->data.posY -= currentNode->data.speed;

        currentNode = currentNode->next;
    }

}



void procUserControl(WINDOW* win, struct game* game) {
    int keyPressed = wgetch(win);
    int bottom = getmaxy(win) - 4;

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
        game->projectiles = spawnProjectile(game->player.posX, bottom - 2, 1, 1);
        // shoot some shit
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

