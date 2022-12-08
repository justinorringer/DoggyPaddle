#include <gb/gb.h>

// collision
extern bool collision_check(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2);
extern bool player_collision_with_screen(UINT8 x, UINT8 y, UINT8 player_size, UINT8 tile_size);

// large
typedef struct {
    UBYTE sprite_id[4];
    UINT8 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
} Large;

extern void init_large(Large *large, UBYTE *sprite_ids, UINT8 x, UINT8 y, UINT8 width, UINT8 height);
extern void move_large(Large *large, UINT8 x, UINT8 y);
