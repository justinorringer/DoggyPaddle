#include <gb/gb.h>
#include <stdbool.h>

// consts
#define I_FRAMES (UINT8)60 // invincibility frames
#define BS_FRAMES (UINT8)30 // boundary sound frames

// game state
typedef struct {
    bool    game_over;
    UINT16  sys_time_i;
    UINT16  sys_time_bs;
    UINT8   joypad;
} GameState;

// scrolling
extern bool scroll(UINT8 player_x, UINT8 x_mod, UINT8 y_mod, UINT8 *level_left, UINT8 *scrolled);

// life
extern void init_hp();
extern void inc_hp();
extern void dec_hp();
extern bool is_player_dead();
extern UINT8 get_hp();

// frames
bool is_grace_period_over(UINT8 n_grace_frames, UINT16 time, UINT16 prev_time);