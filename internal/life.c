#include <gb/gb.h>
#include <stdbool.h>
#include "internal.h"

UINT8 hp;

void init_hp(){
    hp = DEFAULT_HP;
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

UINT8 get_hp(){
    return hp;
}