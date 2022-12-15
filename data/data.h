#include <gb/gb.h>

#ifndef DATA
#define DATA

#define POOL_ENEMY_DATA_COUNT (UINT8)4
#define OCEAN_ENEMY_DATA_COUNT (UINT8)6

typedef struct EnemyData {
    UBYTE sprite_id[4];
    UINT16 x; // in tiles so it doesn't overflow
    UINT8 y; // in tiles so it doesn't overflow
    UINT8 sprite_size;
    UINT8 movement_type;
} EnemyData;

extern EnemyData pool_enemy_data[POOL_ENEMY_DATA_COUNT];
extern EnemyData ocean_enemy_data[OCEAN_ENEMY_DATA_COUNT];

#endif