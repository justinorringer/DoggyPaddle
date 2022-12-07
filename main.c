#include <gb/gb.h>
#include <stdbool.h>

#include "tiles/pool.h"
#include "tiles/ocean.h"
#include "tiles/german.h"
#include "maps/pool_map.h"

#include "large.h"
#include "scrolling.h"

void init();
void checkInput();
void updateSwitches();
bool collisionCheck(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2);

Large player;

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
    set_sprite_data(0, 4, germanTiles);

	UINT8 sprite_ids[] = {0, 1, 2, 3};

    init_large(&player, sprite_ids, 32, 16, 16, 16);
}

void updateSwitches() {
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}

void checkInput() {
    UINT8 x_mod = 0;
	UINT8 y_mod = 0;

	if (joypad() & J_B) {
		
    }
	
	// UP
	if (joypad() & J_UP) {
			
		y_mod = y_mod - 1;
		
	}

	// DOWN
	if (joypad() & J_DOWN) {
			
		y_mod++;
		
	}

	// LEFT
	if (joypad() & J_LEFT) {
		
		x_mod = x_mod - 1;
		
	}	
	
	// RIGHT
	if (joypad() & J_RIGHT) {
		
		x_mod++;
		
	}

	UINT8 tempX = player.x + x_mod;
	UINT8 tempY = player.y + y_mod;

    // Is the player colliding with the left wall?
	if(collisionCheck(tempX, tempY, 16, 16, 0, 32, 32, 144) == true) {
		return;
	}

	if (scroll(player.x + x_mod, x_mod, 0) == true) {
		move_large(&player, tempX - x_mod, tempY);
	}
    else {
		move_large(&player, tempX, tempY);
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