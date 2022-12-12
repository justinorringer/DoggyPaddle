#include <gb/gb.h>
#include <stdbool.h>

#include "../tiles/ocean.h"
#include "internal.h"

// ~40% of the screen width
UINT8 gameplay_x = 56;

// pass in sprites to move them with the background
bool scroll(UINT8 player_x, UINT16 x_mod, UINT8 y_mod, UINT16 *scrolled) {
    if (x_mod <= 0) {
        return false;
    }
    
    if (player_x < gameplay_x) {
        return false;
    }

    if (is_end_of_map(*scrolled)) {
        return false;
    }

    *scrolled = *scrolled + x_mod;

    scroll_bkg(x_mod, y_mod);

    return true;
}

// if the player has reached the end of the map, return true
bool is_end_of_map(UINT16 scrolled) {
    if (scrolled >= MAP_DISTANCE) {
        return true;
    }

    return false;
}