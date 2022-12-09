#include <gb/gb.h>

#include "../maps/map.h"
#include "../tiles/pool.h"
#include "../tiles/ocean.h"

#define OPENING_LEVEL (UINT8)0
#define POOL_LEVEL (UINT8)1
#define OCEAN_LEVEL (UINT8)2

void changeLevel(UINT8 level) {
    switch (level) {
        case OPENING_LEVEL:
            set_bkg_data(0, 12, poolTiles);	// Load 11 tiles into background memory
            // set_bkg_tiles(0, 0, openingMapWidth, openingMapHeight, openingMap); 
            break;
        case POOL_LEVEL:
            set_bkg_data(0, 12, poolTiles);	// Load 11 tiles into background memory
            set_bkg_tiles(0, 0, mapWidth, mapHeight, map); 
            break;
        case OCEAN_LEVEL:
            set_bkg_data(0, 12, oceanTiles);	// Load 11 tiles into background memory
            set_bkg_tiles(0, 0, mapWidth, mapHeight, map); 
            break;
    }
}