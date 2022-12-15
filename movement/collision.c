#include <gb/gb.h>
#include <stdbool.h>

#include "movement.h"

// Check if two rectangles from x1,y1, and extending out w1, h2, 
// overlap with another, x2,y2, and extending out w2, h2
bool collision_check(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2) {
	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		return true;
	} else {
		return false;
	}
}

bool player_collision_with_screen(UINT8 x, UINT8 y, UINT8 player_size, UINT8 tile_size){
	if(
		// left wall
		collision_check(x, y, player_size, player_size, 8, 16, 0, 144)
		// right wall
		|| collision_check(x, y, player_size, player_size, 160+tile_size, 0, 0, 144+8+tile_size)
		// ceiling
		|| collision_check(x, y, player_size, player_size, 0, 8+tile_size, 160+tile_size, 0)
		// floor
		|| collision_check(x, y, player_size, player_size, 0, 144-8, 160+tile_size, 0)
	)
	{
		return true;
	}
	
	return false;
}

bool player_collision_with_obstacles(UINT8 x, UINT8 y, UINT8 player_size, Obstacle *obstacles, UINT8 obstacle_count){
	for(UINT8 i = 0; i < obstacle_count; i++){
		if(
			collision_check(x, y, player_size, player_size, obstacles[i].x, obstacles[i].y, obstacles[i].width, obstacles[i].height)
		){
			return true;
		}
	}
	
	return false;
}

bool player_collision_with_enemies(UINT8 x, UINT8 y, UINT8 player_size, Enemy *enemies, UINT8 enemy_count){
	for(UINT8 i = 0; i < enemy_count; i++){
		if (enemies[i].active == 0) { continue; }

		UINT8 enemy_x;
		UINT8 enemy_y;
		UINT8 width;
		UINT8 height;

		if (enemies[i].sprite_size == 0) { // small
			enemy_x = enemies[i].small.x;
			enemy_y = enemies[i].small.y;
			width = enemies[i].small.width;
			height = enemies[i].small.height;
		} else { // large
			enemy_x = enemies[i].large.x;
			enemy_y = enemies[i].large.y;
			width = enemies[i].large.width;
			height = enemies[i].large.height;
		}

		if(
			collision_check(x, y, player_size, player_size, enemy_x, enemy_y, width, height)
		){
			return true;
		}
	}
	
	return false;
}
