#include <gb/gb.h>
#include "movement.h"

void init_small(Small *small, UINT8 sprite_id, UINT16 x, UINT8 y){
    small->sprite_id = sprite_id;
    small->x = x;
    small->y = y;
    small->width = 8;
    small->height = 8;
}

void move_small(Small *small, UINT16 x, UINT8 y) {
    small->x = x;
    small->y = y;

    move_sprite(small->id, small->x, small->y);
}

void render_small(Small *small, UINT8 id) {
    small->id = id;

    set_sprite_tile(id, small->sprite_id);
    move_sprite(id, small->x, small->y);
}