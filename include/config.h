// NOTE: Anything that is arithmatic should be placed at the end of the
// section to keep things looking clean, they should also be avoided but
// y'know how it is

// Blanket config for everything that is an entity, so the player and enemies.
// This section is subject to change like all things though
#define         ENTITY_SPEED                        2

// Projectile related configs
#define         SPACE_TO_PLAYER_CENTER              2
#define         PROJECTILE_SPEED                    1

// Entity config, so player, enemies, and barriers
// Enemies
#define         ENEMY_WIDTH                         11
#define         ENEMY_HEIGHT                        5
#define         ENEMY_PADDING                       3
#define         ENEMY_OCCUPIES_WIDTH                ENEMY_WIDTH * ENEMY_HEIGHT
// #define         ENEMY_OCCUPIES_WINPERCENT
// Player
#define         PLAYER_SPEED                        1
// Barriers
#define         TOTAL_BARRIERS                      3
#define         BARRIER_MAX_HEALTH                  4
#define         BARRIER_WIDTH                       4
#define         BARRIER_RAISED_BY                   10
#define         BARRIER_OCCUPIES_WINPERCENT         0.5
