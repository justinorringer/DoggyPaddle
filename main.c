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

	UINT8 tile_size = 8; // px
	UINT8 player_size = 16; // px

	UINT8 temp_x = player.x + x_mod;
	UINT8 temp_y = player.y + y_mod;

	// push the pool boundary
	UINT8 pool_boundary = 32;
	if (scrolled > pool_boundary) {
		pool_boundary = 0;
	}
	else {
		pool_boundary = pool_boundary - scrolled;
	}

	// obstacle boundaries
	if (
		// left wall (pool boundary)
		collision_check(temp_x, temp_y, player_size, player_size, 0, 48, pool_boundary, 144)
	)
	{
		play_sound(boundary_hit);
		return;
	}

	// screen boundaries
	if(player_collision_with_screen(temp_x, temp_y, player_size, tile_size))
	{
		play_sound(boundary_hit);
		return;
	}

	// health check
	// if (is_player_dead())
	// {
		
	// }
	

	if (scroll(player.x + x_mod, x_mod, 0, &level_left, &scrolled) == true) {
		move_large(&player, temp_x - x_mod, temp_y);
	}
    else {
		move_large(&player, temp_x, temp_y);
	}
}