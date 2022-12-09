#include <gb/gb.h>
#include <stdbool.h>

#ifndef OBSTACLE_HEADER_GUARD
#define OBSTACLE_HEADER_GUARD

// obstacle
typedef struct {
    UINT8 id;
    UINT16 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
} Obstacle;

extern void init_obstacle(Obstacle *obstacle, UINT8 id, UINT16 x, UINT8 y, UINT8 width, UINT8 height);
extern void move_obstacle(Obstacle *obstacle, UINT16 x, UINT8 y);

#endif

#ifndef LARGE_HEADER_GUARD
#define LARGE_HEADER_GUARD

// large
typedef struct {
    UBYTE id[4];
    UBYTE sprite_id[4];
    UINT16 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
} Large;

extern void init_large(Large *large, UBYTE *sprite_id, UINT16 x, UINT8 y);
extern void move_large(Large *large, UINT16 x, UINT8 y);
extern void render_large(Large *large, UBYTE *id);

#endif

#ifndef SMALL_HEADER_GUARD
#define SMALL_HEADER_GUARD

// small
typedef struct {
    UBYTE id;
    UBYTE sprite_id;
    UINT16 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
} Small;

// sprite_id is the id in the sprite sheet
// id is the identifier for the tile
extern void init_small(Small *small, UINT8 sprite_id, UINT16 x, UINT8 y);
extern void move_small(Small *small, UINT16 x, UINT8 y);
extern void render_small(Small *small, UINT8 id);

#endif

#ifndef DATA
#define DATA

struct EnemyData {
    UBYTE sprite_id[4];
    UINT16 x; // in tiles so it doesn't overflow
    UINT8 y; // in tiles so it doesn't overflow
    UINT8 sprite_size;
    UINT8 movement_type;
};

typedef struct EnemyData EnemyData;

#endif

#ifndef ENEMY_HEADER_GUARD
#define ENEMY_HEADER_GUARD

// enemy
typedef struct Enemy{
    UINT8 sprite_size;
    Large large;
    Small small;
    UINT8 active;
    UINT8 movement_type;
} Enemy;

extern void init_enemy(Enemy *enemy, UINT8 sprite_size, UBYTE *sprite_id, UINT16 x, UINT8 y, UINT8 movement_type);
extern void move_enemy(Enemy *enemy, UINT16 x, UINT8 y);
extern void move_enemy_preset(Enemy *enemy);
extern void render_enemy(Enemy *enemy, UINT8 id);
extern UINT8* get_next_enemy_id(Enemy *enemy, UINT8 *current_id);

#endif

// collision
extern bool collision_check(UINT16 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT16 x2, UINT8 y2, UINT8 w2, UINT8 h2);
extern bool player_collision_with_screen(UINT16 x, UINT8 y, UINT8 player_size, UINT8 tile_size);
extern bool player_collision_with_obstacles(UINT16 x, UINT8 y, UINT8 player_size, Obstacle *obstacles, UINT8 obstacle_count);
extern bool player_collision_with_enemies(UINT16 x, UINT8 y, UINT8 player_size, Enemy *enemies, UINT8 enemy_count);
