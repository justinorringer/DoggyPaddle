#include <gb/gb.h>

struct Small {
    UBYTE id;
    UINT16 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
};

typedef struct Small Small;

void init_small(Small *small, UINT8 id, UINT8 sprite_id, UINT16 x, UINT8 y){
    small->id = id;
    small->x = x;
    small->y = y;
    small->width = 8;
    small->height = 8;

    set_sprite_tile(id, sprite_id);
    move_sprite(id, x, y);
}

void move_small(Small *small, UINT16 x, UINT8 y) {
    small->x = x;
    small->y = y;

    move_sprite(small->id, small->x, small->y);
}