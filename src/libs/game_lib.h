#ifndef GAME_LIB_H
#define GAME_LIB_H

#include <libs/macros.h>
#include <stdint.h>

static const uint8_t height_lut[] = {
    0, 1, 2, 2, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4
};

static uint8_t is_dead = FALSE;

static uint8_t random_byte(void) {
    static uint16_t rng = 0xACE1;

    uint16_t bit = ((rng >> 0) ^
                    (rng >> 2) ^
                    (rng >> 3) ^
                    (rng >> 5)
                   ) & 1;

    rng = (rng >> 1) | (bit << 15);
    return rng & 0xFF;
}

static uint8_t check_collision(
    uint8_t x, uint8_t y,
    const uint16_t tetromino,
    const uint8_t hitbox
) {
    uint8_t height = TETROMINO_HEIGHT(hitbox);
    uint8_t width  = TETROMINO_WIDTH(hitbox);

    for(uint8_t i = 0; i < height; i++) {
        uint8_t line   = MASK_LINE(tetromino, i);
        uint8_t next_y = y + 1 + i;

        if (!line) continue;

        for (uint8_t j = 0; j < width; j++) {
            if (NUM_BIT_REVERSE(line, j)) {
                uint8_t gx = x + j;

                if (gx >= MAP_WIDTH) {
                    return TRUE;
                }
                if (next_y >= MAP_HEIGHT) {
                    return TRUE;
                }

                uint8_t pixel_x = gx * TILE_DIMENSIONS;
                uint8_t pixel_y = next_y * TILE_DIMENSIONS;

                if (VGA[pixel_y][pixel_x] != 0) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

#endif // GAME_LIB_H