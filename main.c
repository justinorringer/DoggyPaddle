#include <gb/gb.h>
#include <stdbool.h>

#include "tiles/pool.h"
#include "tiles/ocean.h"
#include "tiles/sprites.h"
#include "tiles/text.h"
#include "maps/map.h"
#include "maps/text.h"
#include "sounds/sounds.h"
#include "movement/movement.h"
#include "internal/internal.h"

void init();
void check_input();
void update_switches();
void check_game_state();
void restart_game();
void player_hit(UINT16 time);

Large player;
GameState game_state;

// TODO: we can probably move these into GameState? or some default config struct
UINT8 level_left = 30 * 8 - 160;
UINT8 scrolled = 0;

void main() {

	init();
	
	while(1) {
		check_input();				// Check for user input (and act on it)
		update_switches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		check_game_state();
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting memory, waits 1 frame

		if(game_state.game_over) { break; }
	}

	restart_game();
}

void init() {
	game_state.game_over = false;
	game_state.sys_time_i = UINT16_MAX - I_FRAMES;
	game_state.sys_time_bs = UINT16_MAX - BS_FRAMES;
	
	DISPLAY_ON;

	set_bkg_data(0, 11, poolTiles);
	set_bkg_tiles(0, 0, mapWidth, mapHeight, map); 

	set_sprite_data(0, 13, spriteTiles);
	UINT8 sprite_ids[] = {0, 1, 2, 3};
    init_large(&player, sprite_ids, 16, 16, 16, 16);
	// dog bowls
	init_small(0x09, 20, 144);
	init_small(0x0B, 30, 144);
	init_small(0x0C, 40, 144);

	// sample bone
	init_small(0x08, 100, 100);

	init_sound();
	init_hp();
	init_score();
}

void update_switches() {
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}

void check_input() {
    game_state.joypad = joypad();
	
	UINT8 x_mod = 0;
	UINT8 y_mod = 0;
	

	if (game_state.joypad & J_A) {

	}

	if (game_state.joypad & J_B) {
		
    }
	
	// UP
	if (game_state.joypad & J_UP) {
		y_mod = y_mod - 1;
		
	}

	// DOWN
	if (game_state.joypad & J_DOWN) {
		y_mod++;
		
	}

	// LEFT
	if (game_state.joypad & J_LEFT) {
		x_mod = x_mod - 1;
		
	}	
	
	// RIGHT
	if (game_state.joypad & J_RIGHT) {
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

	UINT16 time = sys_time;
	// obstacle boundaries
	if (
		// left wall (pool boundary)
		collision_check(temp_x, temp_y, player_size, player_size, 0, 48, pool_boundary, 144)
	)
	{
		player_hit(time);
		return;
	}

	// screen boundaries
	if(	player_collision_with_screen(temp_x, temp_y, player_size, tile_size))
	{
		if (is_grace_period_over(BS_FRAMES, time, game_state.sys_time_bs)) {
			play_sound(boundary_hit);
			game_state.sys_time_bs = sys_time;
		}
		return;
	}

	// collide with bone
	if (collision_check(temp_x, temp_y, player_size, player_size, 100, 100, 20, 20)) {
		// add to score
		inc_score();
		// remove bone sprite
		hide_sprite(player.sprite_id[0]);

		play_sound(bone_collect);
	}

	if (scroll(player.x + x_mod, x_mod, 0, &level_left, &scrolled) == true) {
		move_large(&player, temp_x - x_mod, temp_y);
		scroll_sprite(0x08, -1 * x_mod, 0);
	}
    else {
		move_large(&player, temp_x, temp_y);
	}
}

// check if invincibility frames ran out, and take damage if yes
void player_hit(UINT16 time){
	UINT8 bowls[3] = {0x09, 0x0B, 0x0C};

	if (is_grace_period_over(I_FRAMES, time, game_state.sys_time_i)) {
		// invinibility ran out, player takes damage
		dec_hp();
		hide_sprite(bowls[get_hp()]);
		play_sound(boundary_hit);
		game_state.sys_time_i = time;
	}
}

void check_game_state(){
	if (is_player_dead()) {
		game_state.game_over = true;
		play_sound(death);
		delay(1000);

		SHOW_WIN;
		set_win_data(11, 8, textTiles);
		// TODO: make this not hard coded lmao
		set_win_tile_xy(3, 9, 0x13);  // 
		set_win_tile_xy(4, 9, 0x0B);  // G
		set_win_tile_xy(5, 9, 0x0C);  // A
		set_win_tile_xy(6, 9, 0x0D);  // M
		set_win_tile_xy(7, 9, 0x0E);  // E
		set_win_tile_xy(8, 9, 0x13);  // 
		set_win_tile_xy(9, 9, 0x11);  // O
		set_win_tile_xy(10, 9, 0x10); // V
		set_win_tile_xy(11, 9, 0x0E); // E
		set_win_tile_xy(12, 9, 0x12); // R

		delay(1000);
	}
}

// lazy way to restart game, will reload the rom
void restart_game(){
	while (1) {
		if (joypad())
		{
			reset();
		}
		
	}
}
