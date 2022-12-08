#include <gb/gb.h>

// collision
extern bool collision_check(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern bool player_collision_with_screen(int x, int y, int player_size, int tile_size);

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
