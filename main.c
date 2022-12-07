#include <gb/gb.h>
#include <stdbool.h>

#include "tiles/pool.h"
#include "tiles/german.h"
#include "tiles/ocean.h"
#include "maps/pool_map.h"

void init();
void checkInput();
void updateSwitches();
bool collisionCheck(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2);

UINT8 player[2];

void main() {

	init();
	
	while(1) {
		checkInput();				// Check for user input (and act on it)
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting memory
	}
	
}

void init() {
	
	DISPLAY_ON;						// Turn on the display
	set_bkg_data(0, 11, poolTiles);	// Load 23 tiles into background memory
	
	set_bkg_tiles(0, 0, poolMapWidth, poolMapHeight, poolMap); 

    set_sprite_data(0, 1, oceanTiles);

    set_sprite_tile(0, 0);

    player[0] = 32;
	player[1] = 16;

    move_sprite(0, player[0], player[1]);
}

void updateSwitches() {
	
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
	
}

void checkInput() {
    int tempX = player[0];
    int tempY = player[1];

	if (joypad() & J_B) {
		
    }
	
	// UP
	if (joypad() & J_UP) {
			
		tempY = tempY - 1;
		
	}

	// DOWN
	if (joypad() & J_DOWN) {
			
		tempY++;
		
	}

	// LEFT
	if (joypad() & J_LEFT) {
		
		tempX = tempX - 1;
		
	}	
	
	// RIGHT
	if (joypad() & J_RIGHT) {
		
		tempX++;
		
	}

    // Is the player colliding with the left wall?
	if(collisionCheck(tempX, tempY, 8, 8, 0, 32, 32, 144) == true) {
		// no op
	}

    else {
        player[0] = tempX;
        player[1] = tempY;
        move_sprite(0, player[0], player[1]);
	}
}

// Check if two rectangles from x1,y1, and extending out h1, h2, 
// overlap with another, x2,y2, and extending out w2, h2
bool collisionCheck(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2) {
	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		return true;
	} else {
		return false;
	}

}