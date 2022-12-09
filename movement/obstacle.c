#include <gb/gb.h>

struct Obstacle {
    UINT8 id;
    UINT8 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
};

typedef struct Obstacle Obstacle;

void init_obstacle(Obstacle *obstacle, UINT8 id, UINT8 x, UINT8 y, UINT8 width, UINT8 height) {
    obstacle->id = id;
    obstacle->x = x;
    obstacle->y = y;
    obstacle->width = width;
    obstacle->height = height;
}

void move_obstacle(Obstacle *obstacle, UINT8 x, UINT8 y) {
    obstacle->x = x;
    obstacle->y = y;
}