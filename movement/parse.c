#include <gb/gb.h>
#include <stdlib.h>

#include "movement.h"

// Reads in the data for enemies and obstacles
Enemy* read_enemy(EnemyData *data, UINT8 enemy_data_count, UINT8 *enemy_num, UINT8 latest_id) {
    Enemy* enemies = calloc(enemy_data_count, sizeof(Enemy));

    UINT8 id_set[4] = { 0, 0, 0, 0 };

    latest_id++;
    
    for (UINT8 i = 0; i < enemy_data_count; i++) { 
        if (data[i].sprite_size == 0) {
            id_set[0] = latest_id;
            id_set[1] = 0;
            id_set[2] = 0;
            id_set[3] = 0;

            latest_id++;

        }
        else {
            id_set[0] = latest_id;
            id_set[1] = latest_id + 1;
            id_set[2] = latest_id + 2;
            id_set[3] = latest_id + 3;

            latest_id += 4;
        }

        init_enemy(&enemies[i], data[i].sprite_size, id_set, data[i].sprite_id, data[i].x, data[i].y, data[i].movement_type);
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