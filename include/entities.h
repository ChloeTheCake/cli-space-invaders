#include "util.h"

struct player {
    int health;
    int dirX;
    int posX;
    NodeContainer projectiles;
};

/*enum enemyType {*/
/*};*/

struct enemy {
    int posX;
    int posY;
    int length;
    bool alive;
    /*enum enemyType enemyType;*/
};

struct hostile {
    NodeContainer enemies;
    NodeContainer enemyProjectiles;
};
