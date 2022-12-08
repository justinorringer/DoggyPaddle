#include <gb/gb.h>

typedef struct {
    UBYTE sprite_id[4];
    UINT8 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
} Large;

void init_large(Large *large, UBYTE *sprite_ids, UINT8 x, UINT8 y, UINT8 width, UINT8 height);
void move_large(Large *large, UINT8 x, UINT8 y);
