#include <gb/gb.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tiles/pool.h"
#include "tiles/ocean.h"
#include "tiles/sprites.h"
#include "tiles/text.h"
#include "maps/map.h"
#include "maps/text.h"

#include "data/pool_data.h"

#include "sounds/sounds.h"
#include "movement/movement.h"
#include "movement/parse.h"
#include "internal/internal.h"


void init();
void check_input();
void update_switches();
void check_game_state();
void restart_game();
void player_hit(UINT16 time);
void spawn_enemies();
void inactive_enemies();

GameState game_state;
Large player;
Enemy* enemies;
UINT8 enemy_count;
Obstacle *obstacle;
UINT8 obstacle_count;

// keep track of sprite ids here, they should increment sequentially
UINT8 dog_id[] = {0, 1, 2, 3};
UINT8 bowl_id[] = {4, 5, 6};
UINT8 next_enemy_id = 7;

// consts for game
const UINT8 tile_size = 8; // px
const UINT8 player_size = 16; // px

void main() {

	init();
	
	while(1) {
		check_input();				// Check for user input (and act on it)
		inactive_enemies();
		spawn_enemies();
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
	game_state.scrolled = 0;
	game_state.level = POOL_LEVEL;

	DISPLAY_ON;

	changeLevel(POOL_LEVEL);

	set_sprite_data(0, 12, spriteTiles);
    init_large(&player, dog_id, 16, 16);
	render_large(&player, dog_id);

	// dog bowls
	Small s; // no need to save the bowls in an array
	init_small(&s, 0x09, 48, 144);
	render_small(&s, bowl_id[0]);
	
	init_small(&s, 0x09, 48+10, 144);
	render_small(&s, bowl_id[1]);
	
	init_small(&s, 0x09, 48+20, 144);
	render_small(&s, bowl_id[2]);
	
	enemies = read_enemy(enemy_data, ENEMY_DATA_COUNT, &enemy_count);

	init_sound();
	init_hp();
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

	UINT8 temp_x = player.x + x_mod;
	UINT8 temp_y = player.y + y_mod;

	UINT16 time = sys_time;
	// obstacle boundaries
	if (player_collision_with_enemies(temp_x, temp_y, player_size, enemies, enemy_count)) {
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
	

	if (scroll(player.x + x_mod, x_mod, 0, &game_state.scrolled)) {
		move_large(&player, temp_x - x_mod, temp_y);
		for (UINT8 i = 0; i < enemy_count; i++){
			Enemy *enemy = &enemies[i];

			if (has_spawned(enemy) == 0){ continue; }

			UINT8 enemy_x;
			UINT8 enemy_y;
			if (enemy->sprite_size == 0) {
				enemy_x = enemy->small.x;
				enemy_y = enemy->small.y;
			}
			else{
				enemy_x = enemy->large.x;
				enemy_y = enemy->large.y;
			}

			move_enemy(enemy, enemy_x - x_mod, enemy_y);
		}
	}
    else {
		move_large(&player, temp_x, temp_y);
	}
}

// check if invincibility frames ran out, and take damage if yes
void player_hit(UINT16 time){
	if (is_grace_period_over(I_FRAMES, time, game_state.sys_time_i)) {
		// invinibility ran out, player takes damage
		dec_hp();
		hide_sprite(bowl_id[get_hp()]);
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

	if (checkLevelChange(&(game_state.level), &(game_state.scrolled))) {
		delay(1000);
	}
}

void spawn_enemies(){
	for (UINT8 i = 0; i < enemy_count; i++){
		Enemy *enemy = &enemies[i];

		if (has_spawned(enemy) == 1){ continue; }

		UINT16 enemy_x;
		if (enemy->sprite_size == 0) {
			enemy_x = enemy->small.x;
		}
		else{
			enemy_x = enemy->large.x;
		}

		if (game_state.scrolled + 160 >= enemy_x) {
			render_enemy(enemy, 7+i);
			// render_enemy(enemy, get_next_enemy_id(enemy, &next_enemy_id));
		}
	}
}

void inactive_enemies(){
	for (UINT8 i = 0; i < enemy_count; i++) {
		Enemy *enemy = &enemies[i];

		if (is_active(enemy) == 1 && is_dead(enemy) == 1){ continue; }

		UINT16 enemy_x = enemy->small.x;
		UINT8 id = enemy->small.id;
		// UINT8 id[4] = {0, 0, 0, 0};
		// if (enemy->sprite_size == 0) {
		// 	enemy_x = enemy->small.x;
		// 	id[0] = enemy->small.id;
		// }
		// else{
		// 	enemy_x = enemy->large.x;
		// 	id[0] = enemy->large.id[0];
		// 	id[1] = enemy->large.id[1];
		// 	id[2] = enemy->large.id[2];
		// 	id[3] = enemy->large.id[3];
		// }

		if (game_state.scrolled < enemy_x && enemy_x < game_state.scrolled + 160) {
			continue;
		}
		
		// hide_enemy(enemy);
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