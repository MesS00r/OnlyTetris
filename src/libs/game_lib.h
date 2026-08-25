#ifndef GAME_LIB_H
#define GAME_LIB_H

#include <libs/macros_types.h>
#include <stdint.h>

static const uint8_t height_lut[] = {
    0, 1, 2, 2, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4
};

static struct Heights heights[MAP_WIDTH] = {0};

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

static void add_height(struct Tetromino tetromino, uint8_t x, uint8_t y) {
    uint8_t width  = TETROMINO_WIDTH(tetromino.hitbox);
    uint8_t bits4  = tetromino.mask & 0x0F;
    uint16_t trans = 0;

    #pragma GCC unroll 4
    for (uint8_t i = 0; i < TETROMINO_DIMENSIONS; i++) {
        trans |= (bits4 << (4 * i));
    }
 
    for (uint8_t i = 0; i < width; i++) {
        uint8_t line          = MASK_LINE(trans, i);
        uint8_t gx            = x + i;

        if (y <= 0) {
            flags.is_dead = 1;
            return;
        }

        uint8_t offset        = MAP_HEIGHT - y - 1;
        uint32_t shifted_line = (uint32_t)line << offset;

        if (heights[gx].mask & shifted_line) {
            flags.is_dead = 1;
            return;
        }

        heights[gx].mask |= shifted_line;

        uint8_t new_height = MAP_HEIGHT - y;
        if (new_height > heights[gx].num) {
            heights[gx].num  = MAP_HEIGHT - y;
        }
    }
}

#endif // GAME_LIB_H