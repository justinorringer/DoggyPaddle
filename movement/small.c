#include <gb/gb.h>

void init_small(UINT8 sprite_id, UINT8 x, UINT8 y){
    set_sprite_tile(sprite_id, sprite_id);
    move_sprite(sprite_id, x, y);
}