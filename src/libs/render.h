#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

#define VGA_ADDR         0xA0000
#define SCREEN_HEIGHT    200
#define SCREEN_WIDTH     320
#define FULL_SCREEN      64000

#define TILE_DIMENSIONS  8
#define MAP_HEIGHT       25
#define MAP_WIDTH        40
#define FULL_MAP         1000

#define TILE             15
#define BLACK            0

#define TETROMINO_HEIGHT 32
#define TETROMINO_WIDTH  4

#define VGA ((uint8_t (*)[SCREEN_WIDTH])VGA_ADDR)

#define TETROMINO_BIT(t, x, y) (((t) >> ((y) * 4 + (x))) & 1)
#define SCREEN_POS(x, y) ((y) * SCREEN_WIDTH + (x))

static uint8_t heights[MAP_WIDTH] = {0};
static uint8_t dead_zone          = 0;

static void tetromino_draw(uint8_t x, uint8_t y, uint16_t tetromino) {
    for (uint8_t y1 = 0; y1 < TETROMINO_HEIGHT; y1++) {
        for (uint8_t x1 = 0; x1 < TETROMINO_WIDTH; x1++) {
            if (TETROMINO_BIT(tetromino, x1, y1 / 8) == 1) {
                uint16_t tile_x = x * TILE_DIMENSIONS;
                uint16_t tile_y = y * TILE_DIMENSIONS;
                uint16_t pos    = x1 * TILE_DIMENSIONS + SCREEN_POS(tile_x, tile_y);

                __builtin_memset(VGA[y1] + pos, TILE, TILE_DIMENSIONS);
            }
        }
    }
}

static void clear_screen(void) {
    uint16_t save_zone  = dead_zone * SCREEN_WIDTH;
    uint16_t clear_zone = FULL_SCREEN - save_zone;
    __builtin_memset(VGA, BLACK, clear_zone);
}

#endif // RENDER_H