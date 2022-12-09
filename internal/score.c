#include <gb/gb.h>
#include <stdbool.h>

#include "../tiles/text.h"

#define DIGIT_INDEX (UINT8)9

UINT16 score = 0;

void update_display();

void init_score() {
    set_win_data(8, 10, textTiles);
    update_display();
    SHOW_WIN;
}

void inc_score() {
    score++;
    update_display();
}

UINT16 get_score() {
    return score;
}

void reset_score() {
    score = 0;
}

void update_display() {
    UINT8 score_digits[5] = {0,0,0,0,0};
    UINT16 score_copy = score;
    for (UINT8 i = 0; i < 5; i++) {
        score_digits[i] = score_copy % 10;
        score_copy /= 10;
    }

    set_win_tile_xy(4, 7, score_digits[4]);
    set_win_tile_xy(5, 7, score_digits[3]);
    set_win_tile_xy(6, 7, score_digits[2]);
    set_win_tile_xy(7, 7, score_digits[1]);
    set_win_tile_xy(8, 7, score_digits[0]);
}