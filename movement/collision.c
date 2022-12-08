#include <gb/gb.h>
#include <stdbool.h>

// Check if two rectangles from x1,y1, and extending out w1, h2, 
// overlap with another, x2,y2, and extending out w2, h2
bool collision_check(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2) {
	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		return true;
	} else {
		return false;
	}
}