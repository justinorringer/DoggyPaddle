int HP;
int DEFAULT_BASE_HP = 3;

void init_hp(){
    HP = DEFAULT_BASE_HP;
}

// increment HP
void inc_hp(){
    HP++;
}

// decrement HP
void dec_hp(){
    HP = HP - 1;
}