#include <gb/gb.h>
#include <stdbool.h>

// consts
#define I_FRAMES (UINT8)60 // invincibility frames
#define BS_FRAMES (UINT8)30 // boundary sound frames

#define OPENING_LEVEL (UINT8)0
#define POOL_LEVEL (UINT8)1
#define OCEAN_LEVEL (UINT8)2

#define DEFAULT_HP (UINT8)3;

// game state
typedef struct {
    bool    game_over;
    UINT16  sys_time_i;
    UINT16  sys_time_bs;
    UINT8   joypad;

    UINT8   level;
    UINT16  scrolled;
} GameState;

// levels
void changeLevel(UINT8 level);

// scrolling
extern bool scroll(UINT8 player_x, UINT16 x_mod, UINT8 y_mod, UINT16 *scrolled);

// life
extern void init_hp();
extern void inc_hp();
extern void dec_hp();
extern bool is_player_dead();
extern UINT8 get_hp();

// frames
bool is_grace_period_over(UINT8 n_grace_frames, UINT16 time, UINT16 prev_time);