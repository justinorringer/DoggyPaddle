#include <gb/gb.h>
#include <stdbool.h>

#include "../tiles/ocean.h"
#include "internal.h"

// ~40% of the screen width
UINT8 gameplay_x = 56;

UINT8 map_distance = 120;

// pass in sprites to move them with the background
bool scroll(UINT8 player_x, UINT16 x_mod, UINT8 y_mod, UINT8 *pixels_scrolled, UINT8 *tiles_scrolled) {
    if (x_mod <= 0) {
        return false;
    }
    
    if (player_x < gameplay_x) {
        return false;
    }

    if (*tiles_scrolled >= map_distance) {
        return false;
    }

    *pixels_scrolled = *pixels_scrolled + x_mod;

    if (*pixels_scrolled >= 8) {
        *pixels_scrolled = *pixels_scrolled - 8;
        *tiles_scrolled = *tiles_scrolled + 1;
    }

    scroll_bkg(x_mod, y_mod);

    return true;
}

void reset_scroll(UINT8 *pixels_scrolled, UINT8 *tiles_scrolled) {
    *pixels_scrolled = 0;
    *tiles_scrolled = 0;
}