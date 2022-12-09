#include <gb/gb.h>

#include "../data/pool_data.h"

// Reads in the data for enemies and obstacles
extern Enemy* read_enemy(EnemyData *data, UINT8 enemy_data_count, UINT8 *enemy_num);

extern void clear_enemy(Enemy **enemies, UINT8 id);

extern void empty_enemy(Enemy **enemies);