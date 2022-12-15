#include <gb/gb.h>

#include "movement.h"

struct Enemy {
    UINT8 sprite_size;
    Large large;
    Small small;
    UINT8 active;
    UINT8 movement_type;
};

void init_enemy(Enemy *enemy, UINT8 sprite_size, UBYTE *id, UBYTE *sprite_id, UINT16 x, UINT8 y, UINT8 movement_type) {
    enemy->sprite_size = sprite_size;
    if (sprite_size == 1) { // Large
        init_large(&enemy->large, id, sprite_id, x, y);
    } else {
        init_small(&enemy->small, id[0], sprite_id[0], x, y);
    }

    enemy->movement_type = movement_type;
}

void move_enemy(Enemy *enemy, UINT16 x, UINT8 y) {
    if (enemy->sprite_size == 1) { // Large
        move_large(&enemy->large, x, y);
    } else {
        move_small(&enemy->small, x, y);
    }
}

// This function is based on the movement_type field
void move_enemy_preset(Enemy *enemy) {
    UINT16 x;
    UINT8 y;
    if (enemy->sprite_size == 1) { // Large
        x = enemy->large.x;
        y = enemy->large.y;
    } else {
        x = enemy->small.x;
        y = enemy->small.y;
    }
    switch (enemy->movement_type) {
        case 0: // No movement
            break;
        case 1: // Move left
            move_enemy(enemy, x - 1, y);
            break;
        case 2: // Move right
            move_enemy(enemy, x + 1, y);
            break;
        case 3: // Move up
            move_enemy(enemy, x, y - 1);
            break;
    }

}