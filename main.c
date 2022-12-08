#include <gb/gb.h>
#include <stdbool.h>

#include "tiles/pool.h"
#include "tiles/ocean.h"
#include "tiles/sprites.h"
#include "maps/map.h"
#include "sounds/sounds.h"
#include "movement/movement.h"
#include "internal/internal.h"

void init();
void checkInput();
void updateSwitches();

Large player;

UINT8 level_left = 30 * 8 - 160;
UINT8 scrolled = 0;

void main() {

	init();
	
	while(1) {
		checkInput();				// Check for user input (and act on it)
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting memory
	}
	
}

void init() {
	
	DISPLAY_ON;

	set_bkg_data(0, 11, poolTiles);
	set_bkg_tiles(0, 0, mapWidth, mapHeight, map); 

	set_sprite_data(0, 11, spriteTiles);
	UINT8 sprite_ids[] = {0, 1, 2, 3};
    init_large(&player, sprite_ids, 16, 16, 16, 16);

	init_sound();
	init_hp();
}

void updateSwitches() {
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}

void checkInput() {
    UINT8 x_mod = 0;
	UINT8 y_mod = 0;

	if (joypad() & J_A) {
		
    }

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

	UINT8 tileSize = 8; // px
	UINT8 playerSize = 16; // px

	UINT8 tempX = player.x + x_mod;
	UINT8 tempY = player.y + y_mod;

	// push the pool boundary
	UINT8 poolBoundary = 32;
	if (scrolled > poolBoundary) {
		poolBoundary = 0;
	}
	else {
		poolBoundary = poolBoundary - scrolled;
	}

	// obstacle boundaries
	if (
		// left wall (pool boundary)
		collision_check(tempX, tempY, playerSize, playerSize, 0, 48, poolBoundary, 144)
	)
	{
		play_sound(CHANNEL_1, boundaryHit);
		return;
	}

	// screen boundaries
	if(
		// left wall (left of screen, not pool boundary)
		collision_check(tempX, tempY, playerSize, playerSize, 8, 16, 0, 144)
		// right wall
		|| collision_check(tempX, tempY, playerSize, playerSize, 160+tileSize, 0, 0, 144+8+tileSize)
		// ceiling
		|| collision_check(tempX, tempY, playerSize, playerSize, 0, 8+tileSize, 160+tileSize, 0)
		// floor
		|| collision_check(tempX, tempY, playerSize, playerSize, 0, 144-8, 160+tileSize, 0)
	) 
	{
		play_sound(CHANNEL_1, boundaryHit);
		return;
	}

	if (scroll(player.x + x_mod, x_mod, 0, &level_left, &scrolled) == true) {
		move_large(&player, tempX - x_mod, tempY);
	}
    else {
		move_large(&player, tempX, tempY);
	}
}