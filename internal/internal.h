#include <gb/gb.h>
#include <stdbool.h>

#include "../data/data.h"

// consts
#define I_FRAMES (UINT8)60 // invincibility frames
#define BS_FRAMES (UINT8)30 // boundary sound frames

#define OPENING_LEVEL (UINT8)0
#define POOL_LEVEL (UINT8)1
#define OCEAN_LEVEL (UINT8)2

#define DEFAULT_HP (UINT8)3

#define MAP_DISTANCE (UINT16)960

// game state
typedef struct {
    bool    game_over;
    bool    off_frame; // using it for slow moving objects
    UINT16  sys_time_i;
    UINT16  sys_time_bs;
    UINT8   joypad;

    UINT8   level;
    UINT16  scrolled;
} GameState;

// levels
extern void changeLevel(UINT8 level);
extern bool checkLevelChange(UINT8 *level, UINT16 *scrolled);
extern void get_level_data(UINT8 level, EnemyData **enemy_data, UINT8 *enemy_data_count);

// scrolling
extern bool scroll(UINT8 player_x, UINT16 x_mod, UINT8 y_mod, UINT16 *scrolled);
extern bool is_end_of_map(UINT16 scrolled);

// life
extern void init_hp();
extern void inc_hp();
extern void dec_hp();
extern bool is_player_dead();
extern UINT8 get_hp();

// frames
bool is_grace_period_over(UINT8 n_grace_frames, UINT16 time, UINT16 prev_time);