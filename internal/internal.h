#include <gb/gb.h>
#include <stdbool.h>

// scrolling
extern bool scroll(UINT8 player_x, UINT8 x_mod, UINT8 y_mod, UINT8 *level_left, UINT8 *scrolled);

// life
extern void init_hp();
extern void inc_hp();
extern void dec_hp();