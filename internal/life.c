#include <gb/gb.h>
#include <stdbool.h>

UINT8 hp = 0;
UINT8 default_base_hp = 3;

void init_hp(){
    hp = default_base_hp;
}

// increment HP
void inc_hp(){
    hp++;
}

// decrement HP
void dec_hp(){
    hp = hp - 1;
}

bool is_player_dead(){
    return hp == 0;
}