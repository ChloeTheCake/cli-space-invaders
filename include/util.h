struct projectile {
    int posX;
    int posY;
    int dmg;
    int speed;
};

typedef struct node {
    struct node* next;
    struct projectile data;
} NODE;

struct nodeContainer {
    NODE* first;
    NODE* last;
};


void spawnProjectile(struct nodeContainer* nodeCon, struct projectile proj);
void addProjectileToList(struct nodeContainer* nodeCon, NODE* node);
struct projectile* getListIndex(int index);
/*void removeAtIndex(int index);*/
