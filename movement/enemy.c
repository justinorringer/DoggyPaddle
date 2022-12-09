#include <gb/gb.h>

#include "movement.h"

void init_enemy(Enemy *enemy, UINT8 sprite_size, UBYTE *sprite_id, UINT16 x, UINT8 y, UINT8 movement_type) {
    enemy->sprite_size = sprite_size;
    if (sprite_size == 1) { // Large
        init_large(&enemy->large, sprite_id, x, y);
    } else {
        init_small(&(enemy->small), sprite_id[0], x, y);
    }

    enemy->movement_type = movement_type;
}

void move_enemy(Enemy *enemy, UINT16 x, UINT8 y) {
    if (enemy->active == 0) {
        return;
    }

    if (enemy->sprite_size == 1) { // Large
        move_large(&enemy->large, x, y);
    } else {
        move_small(&enemy->small, x, y);
    }
}

// This function is based on the movement_type field
void move_enemy_preset(Enemy *enemy) {
    if (enemy->active == 0) {
        return;
    }
    
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

void render_enemy(Enemy *enemy, UINT8 id) {
    enemy->active = 1;

    // small
    if (enemy->sprite_size == 0) {
        render_small(&(enemy->small), id);   
    }
    // beeg
    else {
        // render_large(&(enemy->large), id);
    }
}

UINT8* get_next_enemy_id(Enemy *enemy, UINT8 *current_id) {
    UINT8 res[4];
    // small
    if (enemy->sprite_size == 0) {
        *current_id = *current_id + 1;
        res[0] = *current_id;
        return res;
    }
    // beeg
    else {
        UINT8 id = *current_id;
        *current_id = *current_id + 4;
        res[0]=id;
        res[1]=id+1;
        res[2]=id+2;
        res[3]=id+3;
        
        return res;
    }
}