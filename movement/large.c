#include <gb/gb.h>
#include "movement.h"

// This will be used for bosses and the character

// x and y are in tiles
void move_large(Large *large, UINT16 x, UINT8 y) {
    large->x = x;
    large->y = y;

    move_sprite(large->id[0], large->x, large->y);
    move_sprite(large->id[1], large->x, large->y + 8);
    move_sprite(large->id[2], large->x + 8, large->y);
    move_sprite(large->id[3], large->x + 8, large->y + 8);
}

// Initializes the large entity
void init_large(Large *large, UBYTE *id, UBYTE *sprite_id, UINT16 x, UINT8 y) {
    large->id[0] = id[0];
    large->id[1] = id[1];
    large->id[2] = id[2];
    large->id[3] = id[3];
    large->x = x;
    large->y = y;
    large->width = 16;
    large->height = 16;

    set_sprite_tile(large->id[0], sprite_id[0]);
    set_sprite_tile(large->id[1], sprite_id[1]);
    set_sprite_tile(large->id[2], sprite_id[2]);
    set_sprite_tile(large->id[3], sprite_id[3]);

    move_large(large, large->x, large->y);
}
