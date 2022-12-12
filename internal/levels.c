#include <gb/gb.h>
#include <stdbool.h>

#include "internal.h"

#include "../maps/map.h"
#include "../tiles/pool.h"
#include "../tiles/ocean.h"

#define OPENING_LEVEL (UINT8)0
#define POOL_LEVEL (UINT8)1
#define OCEAN_LEVEL (UINT8)2

void changeLevel(UINT8 level) {
    switch (level) {
        case POOL_LEVEL:
            set_bkg_data(0, 12, poolTiles);	// Load 11 tiles into background memory
            set_bkg_tiles(0, 0, mapWidth, mapHeight, map); 
            break;
        case OCEAN_LEVEL:
            set_bkg_data(0, 12, oceanTiles);	// Load 11 tiles into background memory
            break;
    }
}

// if the is_end_of_map returns true 
// (MAP DISTANCE has been reached), change the level
bool checkLevelChange(UINT8 *level, UINT16 *scrolled) {
    if (is_end_of_map(*scrolled)) {
        switch (*level) {
            case POOL_LEVEL:
                changeLevel(OCEAN_LEVEL);
                *level = OCEAN_LEVEL;
                break;
            case OCEAN_LEVEL:
                // here, we could take them to the end of the game
                return false;
                break;
        }

        // reset level and scrolled values
        *scrolled = 0;
        return true;
    }
    return false;
}