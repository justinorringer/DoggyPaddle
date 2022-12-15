#include <gb/gb.h>

#include "../data/pool_data.h"

// Reads in the data for enemies and obstacles
void read_enemy(Enemy **enemies, EnemyData *data, UINT8 enemy_data_count, UINT8 *enemy_num, UINT8 latest_id);

void clear_enemy(Enemy **enemies, UINT8 id);

void empty_enemy(Enemy **enemies);