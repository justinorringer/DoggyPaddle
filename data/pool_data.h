#include <gb/gb.h>

#ifndef DATA
#define DATA

#define ENEMY_DATA_COUNT (UINT8)3

typedef struct EnemyData{
    UBYTE sprite_id[4];
    UINT16 x; // in tiles so it doesn't overflow
    UINT8 y; // in tiles so it doesn't overflow
    UINT8 sprite_size;
    UINT8 movement_type;
} EnemyData;

extern EnemyData enemy_data[ENEMY_DATA_COUNT];

#endif