#include <gb/gb.h>

// This will be used for bosses and the character
struct Large {
    UBYTE sprite_id[4];
    UINT8 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
};

typedef struct Large Large;

void move_large(Large *large, UINT8 x, UINT8 y) {
    large->x = x;
    large->y = y;

    move_sprite(large->sprite_id[0], large->x, large->y);
    move_sprite(large->sprite_id[1], large->x, large->y + 8);
    move_sprite(large->sprite_id[2], large->x + 8, large->y);
    move_sprite(large->sprite_id[3], large->x + 8, large->y + 8);
}

void init_large(Large *large, UBYTE *sprite_ids, UINT8 x, UINT8 y, UINT8 width, UINT8 height) {
    large->sprite_id[0] = sprite_ids[0];
    large->sprite_id[1] = sprite_ids[1];
    large->sprite_id[2] = sprite_ids[2];
    large->sprite_id[3] = sprite_ids[3];
    large->x = x;
    large->y = y;
    large->width = width;
    large->height = height;

    set_sprite_tile(large->sprite_id[0], large->sprite_id[0]);
    set_sprite_tile(large->sprite_id[1], large->sprite_id[1]);
    set_sprite_tile(large->sprite_id[2], large->sprite_id[2]);
    set_sprite_tile(large->sprite_id[3], large->sprite_id[3]);

    move_large(large, large->x, large->y);
}
