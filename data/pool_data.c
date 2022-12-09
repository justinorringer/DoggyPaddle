#include <gb/gb.h>

struct EnemyData {
    UBYTE sprite_id[4];
    UINT8 x; // in tiles so it doesn't overflow
    UINT8 y; // in tiles so it doesn't overflow
    UINT8 sprite_size;
    UINT8 movement_type;
};

typedef struct EnemyData EnemyData;

EnemyData enemy_data[1] = {
    { { 10, 0, 0, 0 }, 300, 100, 0, 1 },
};