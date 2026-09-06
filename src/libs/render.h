#ifndef RENDER_H
#define RENDER_H

#include <libs/macros_types.h>
#include <stdint.h>

static void tetromino_draw(uint8_t x, uint8_t y, const uint16_t tetromino) {
    uint16_t tetromino_x = x * TILE_DIMENSIONS;
    uint16_t tetromino_y = y * TILE_DIMENSIONS;

    for (uint8_t y1 = 0; y1 < TETROMINO_REAL_HEIGHT; y1++) {
        uint8_t mask  = MASK_LINE(tetromino, y1 >> TILE_DIMS_OFFSET);
        uint64_t *out = (uint64_t *)&VGA[y1 + tetromino_y][tetromino_x];

        #pragma GCC unroll 4
        for (uint8_t i = 0; i < TETROMINO_DIMENSIONS; i++) {
            if (NUM_BIT(mask, i)) {
                out[i] = TILE_COLOR * BASE_MASK;
            }
        }
    }
}

static void tetromino_clear(uint8_t x, uint8_t y) {
    uint16_t tetromino_x = x * TILE_DIMENSIONS;
    uint16_t tetromino_y = y * TILE_DIMENSIONS;

    for (uint8_t y1 = 0; y1 < TETROMINO_REAL_HEIGHT; y1++) {
        uint64_t *out = (uint64_t *)&VGA[y1 + tetromino_y][tetromino_x];

        #pragma GCC unroll 4
        for (uint8_t i = 0; i < TETROMINO_DIMENSIONS; i++) {
            if (out[i] != 0) {
                out[i] = BLACK;
            }
        }
    }
}

// static inline void clear_screen(void) {
//     __builtin_bzero(VGA, FULL_SCREEN);
// }

#endif // RENDER_H