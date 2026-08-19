#ifndef GAME_LIB_H
#define GAME_LIB_H

#include <stdint.h>
#include <libs/render.h>

struct Tetromino {
    uint16_t mask;
    uint8_t hitbox;
};

static const uint8_t height_lut[] = {
    0, 1, 2, 2, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4
};

static uint8_t heights[MAP_WIDTH] = {0};
static uint8_t dead_zone          = 0;

static uint8_t random_byte() {
    static uint16_t rng = 0xACE1;

    uint16_t bit = ((rng >> 0) ^
                    (rng >> 2) ^
                    (rng >> 3) ^
                    (rng >> 5)
                   ) & 1;

    rng = (rng >> 1) | (bit << 15);
    return rng & 0xFF;
}

static uint16_t transpose(uint16_t mask) {
    uint16_t trans = 0;
    trans = (mask ^ (mask >> 3)) & 0x1111;
    mask  = mask ^ trans ^ (trans << 3);
    trans = (mask ^ (mask >> 6)) & 0x0303;
    mask  = mask ^ trans ^ (trans << 6);
    return mask;
}

static void add_height(struct Tetromino tetromino) {
    uint8_t width  = TETROMINO_WIDTH(tetromino.hitbox);
    uint16_t trans = transpose(tetromino.mask);
 
    for (uint8_t i = 0; i < width; i++) {
        uint8_t line = TETROMINO_LINE(trans, i);

        heights[i] += height_lut[line & 0x0F];
    }
}

#endif // GAME_LIB_H