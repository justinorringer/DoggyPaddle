#include <gb/gb.h>
#include <stdbool.h>

#include "../tiles/ocean.h"
#include "internal.h"

// ~40% of the screen width
UINT8 gameplay_x = 56;

UINT16 map_distance = 120 * 8;

// pass in sprites to move them with the background
bool scroll(UINT8 player_x, UINT16 x_mod, UINT8 y_mod, UINT16 *scrolled) {
    if (x_mod <= 0) {
        return false;
    }
    
    if (player_x < gameplay_x) {
        return false;
    }

    if (*scrolled >= map_distance) {
        return false;
    }

    *scrolled = *scrolled + x_mod;

    scroll_bkg(x_mod, y_mod);

    return true;
}
