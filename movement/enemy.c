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
void move_enemy_preset(Enemy *enemy, UINT8 off_frame) {
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
        case LEFT_SLOW:
            if (off_frame) {
                x -= 1;
            }
            break;
        case LEFT_FAST:
            x -= 1;
            break;
        case RIGHT_SLOW:
            if (off_frame) {
                x += 1;
            }
            break;
        case RIGHT_FAST:
            x += 1;
            break;
        case UP_SLOW:
            if (off_frame) {
                y -= 1;
            }
            break;
        default:
            return;
            break;
    }

    move_enemy(enemy, x, y);

}

void render_enemy(Enemy *enemy, UINT8 *id) {
    enemy->active = 1;

    // small
    if (enemy->sprite_size == 0) {
        render_small(&(enemy->small), id[0]);   
    }
    // beeg
    else {
        render_large(&(enemy->large), id);
    }
}

void hide_enemy(Enemy *enemy) {
    enemy->active = 0;

    // small
    if (enemy->sprite_size == 0) {
        hide_small(&(enemy->small));
    }
    // beeg
    else {
        hide_large(&(enemy->large));
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

UINT8 is_active(Enemy *enemy) {
    if (enemy->active == 1) {
        return 1;
    }
    return 0;
}

UINT8 has_spawned(Enemy *enemy) {
    if (enemy->active == 1 || enemy->active == 2) {
        return 1;
    }
    return 0;
}

UINT8 is_dead(Enemy *enemy) {
    if (enemy->active == 2) {
        return 1;
    }
    return 0;
}
