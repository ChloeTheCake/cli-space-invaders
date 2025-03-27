struct projectile {
    int posX;
    int posY;
    int dmg;
    int speed;
    int isHostile; // I could use +/- speed to determine this if I wanted, it'd
                   // bundle direction, speed, and whether it's an enemy into one
};

typedef struct node {
    struct node* next;
    struct projectile data;
} NODE;

/*struct nodeContainer {*/
/*    NODE* first;*/
/*    NODE* last;*/
/*};*/


NODE* spawnProjectile(int posX, int posY, int dmg, int speed);
void addProjectileToList(NODE* proj);
struct projectile* getListIndex(int index, NODE* lastNode);
void removeAtIndex(int index);
