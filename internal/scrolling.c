#include <gb/gb.h>
#include <stdbool.h>

// ~40% of the screen width
UINT8 gameplay_x = 55;

// pass in sprites to move them with the background
bool scroll(UINT8 player_x, UINT8 x_mod, UINT8 y_mod, UINT8 *level_left, UINT8 *scrolled) {
    if (x_mod <= 0) {
        return false;
    }
    
    if (player_x < gameplay_x) {
        return false;
    }

    if (*level_left <= 0) {
        return false;
    }

    // decrement level_left by x_mod
    *level_left = *level_left - x_mod;
    *scrolled = *scrolled + x_mod;

    scroll_bkg(x_mod, y_mod);

    return true;
}
