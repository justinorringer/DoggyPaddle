#include <gb/gb.h>

#ifndef DATA
#define DATA

typedef struct {
    UBYTE sprite_id[4];
    UINT16 x; // in tiles so it doesn't overflow
    UINT8 y; // in tiles so it doesn't overflow
    UINT8 sprite_size;
    UINT8 movement_type;
} EnemyData;

UINT8 enemy_data_count = 1;
extern EnemyData enemy_data[1];

#endif