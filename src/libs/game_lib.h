#ifndef GAME_LIB_H
#define GAME_LIB_H

#include <libs/macros.h>
#include <stdint.h>

static uint8_t is_dead = FALSE;

static uint8_t check_collision(
    uint8_t x, uint8_t y,
    const uint16_t tetromino
) {
    for(uint8_t i = 0; i < TETROMINO_DIMENSIONS; i++) {
        uint8_t line   = MASK_LINE(tetromino, i);
        uint8_t next_y = y + i;

        if (!line) continue;

        for (uint8_t j = 0; j < TETROMINO_DIMENSIONS; j++) {
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

                if (VGA[pixel_y][pixel_x] != BLACK) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

static void clear_line(void) {
    for (int16_t row = MAP_HEIGHT - 1; row >= 0; row--) {
        uint8_t is_line_full = TRUE;
        uint16_t check_y     = row * TILE_DIMENSIONS;

        for (uint16_t i = 0; i < SCREEN_WIDTH; i += TILE_DIMENSIONS) {
            if (VGA[check_y][i] == BLACK) {
                is_line_full = FALSE;
                break;
            }
        }
    
        if (!is_line_full) continue;

        uint8_t *dest          = (uint8_t *)VGA + (check_y + TILE_DIMENSIONS) * SCREEN_WIDTH - 1;
        uint8_t *src           = (uint8_t *)VGA + check_y * 320 - 1;
        uint32_t bytes_to_move = check_y * 320;

        while (bytes_to_move--) {
            *dest-- = *src--;
        }

        __builtin_memset(VGA, BLACK, TILE_DIMENSIONS * SCREEN_WIDTH);

        row++;
    }
}

#endif // GAME_LIB_H