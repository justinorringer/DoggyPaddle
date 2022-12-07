#include <gb/gb.h>
#include <stdbool.h>

#include "tiles/pool.h"
#include "tiles/german.h"
#include "tiles/ocean.h"
#include "maps/pool_map.h"
#include "sounds/sounds.h"

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
	// display
	DISPLAY_ON;

	// sound
	initSound();

	set_bkg_data(0, 11, poolTiles);	
	set_bkg_tiles(0, 0, poolMapWidth, poolMapHeight, poolMap); 

    set_sprite_data(0, 1, oceanTiles);
    set_sprite_tile(0, 0);

    player[0] = 8;
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

	if (joypad() & J_A) {
		
    }

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

	UINT8 tileSize = 8; // px

	if(
		// left wall (pool boundary)
		collisionCheck(tempX, tempY, tileSize, tileSize, 0, 32, 32, 144)
		// left wall 2 (left of screen, not pool boundary)
		|| collisionCheck(tempX, tempY, tileSize, tileSize, 8, 16, 0, 32)
		// right wall
		|| collisionCheck(tempX, tempY, tileSize, tileSize, 160+tileSize, 0, 0, 144+8+tileSize)
		// ceiling
		|| collisionCheck(tempX, tempY, tileSize, tileSize, 0, 8+tileSize, 160+tileSize, 0)
		// floor
		|| collisionCheck(tempX, tempY, tileSize, tileSize, 0, 144+8+tileSize, 160+tileSize, 0)
	) 
	{
		playSound(CHANNEL_1, boundaryHit);
	}

    else {
        player[0] = tempX;
        player[1] = tempY;
        move_sprite(0, player[0], player[1]);
	}
}

// Check if two rectangles from x1,y1, and extending out w1, h2, 
// overlap with another, x2,y2, and extending out w2, h2
bool collisionCheck(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2) {
	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		return true;
	} else {
		return false;
	}

}