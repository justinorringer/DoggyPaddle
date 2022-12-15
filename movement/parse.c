#include <gb/gb.h>
#include <stdlib.h>

#include "movement.h"
#include "../data/data.h"
#include "../internal/internal.h"

// Reads in the data for enemies and obstacles
Enemy* read_enemy(UINT8 level, UINT8 *enemy_num) {
    EnemyData *data;
    UINT8 enemy_data_count;
    
    get_level_data(level, &data, &enemy_data_count);

    Enemy* enemies = calloc(enemy_data_count, sizeof(Enemy));
    
    for (UINT8 i = 0; i < enemy_data_count; i++) {
        init_enemy(&enemies[i], data[i].sprite_size, data[i].sprite_id, data[i].x, data[i].y, data[i].movement_type);
        (*enemy_num)++;
    }

    return enemies;
}

void clear_enemy(Enemy **enemies, UINT8 id) {
    (*enemies)[id].active = 0;
}

void empty_enemy(Enemy **enemies, UINT8 enemy_data_count) {
    for (UINT8 i = 0; i < enemy_data_count; i++) {
        clear_enemy(enemies, i);
    }
}