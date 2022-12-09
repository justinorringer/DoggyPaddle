#include <gb/gb.h>
#include <stdbool.h>

// Check if two rectangles from x1,y1, and extending out w1, h2, 
// overlap with another, x2,y2, and extending out w2, h2
bool collision_check(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		return true;
	} else {
		return false;
	}
}

bool player_collision_with_screen(int x, int y, int player_size, int tile_size){
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
