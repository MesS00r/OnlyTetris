#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

#define VGA_ADDR        0xA0000
#define SCREEN_HEIGHT   200
#define SCREEN_WIDTH    320
#define FULL_SCREEN     64000

#define TILE_DIMENSIONS 8
#define MAP_HEIGHT      25
#define MAP_WIDTH       40
#define FULL_MAP        1000

#define BASE_MASK       0x0101010101010101ULL
#define TILE_COLOR      15
#define BLACK           0

#define TETROMINO_REAL_HEIGHT 32
#define TETROMINO_DIMENSIONS  4
#define TETROMINO_HALF_DIMS   2

#define VGA ((uint8_t (*)[SCREEN_WIDTH])VGA_ADDR)

#define TETROMINO_BIT(t, x, y) (((t) >> ((y) * 4 + (x))) & 1)
#define TETROMINO_LINE(t, n)   (((t) >> ((n) * 4)) & 0x0F)

#define TETROMINO_WIDTH(h)     ((h) >> 4)
#define TETROMINO_HEIGHT(h)    ((h) & 0x0F)

#define SCREEN_POS(x, y)       ((y) * SCREEN_WIDTH + (x))

static uint8_t dead_zone = 0;
static const uint64_t tetromino_tile_lut[] = { 0, TILE_COLOR * BASE_MASK };

static void tetromino_draw(uint8_t x, uint8_t y, const uint16_t tetromino) {
    if (tetromino == 0) return;

    uint8_t combiner_rows = tetromino          |
                            (tetromino >> 4)   |
                            (tetromino >> 8)   |
                            (tetromino >> 12);

    uint8_t offset_x = __builtin_ctz(combiner_rows);
    uint8_t offset_y = __builtin_ctz(tetromino) / 4;

    uint16_t tetromino_x = x * TILE_DIMENSIONS;
    uint16_t tetromino_y = y * TILE_DIMENSIONS;

    for (uint8_t y1 = 0; y1 < TETROMINO_REAL_HEIGHT; y1++) {
        uint8_t line_idx = y1 / TILE_DIMENSIONS + offset_y;

        uint8_t mask  = TETROMINO_LINE(tetromino, line_idx) >> offset_x;
        uint64_t *out = (uint64_t *)&VGA[y1 + tetromino_y][tetromino_x];

        for (uint8_t i = 0; i < 4; i++) {
            out[i] = tetromino_tile_lut[(mask >> i) & 1];
        }
    }
}

static void clear_screen(void) {
    uint16_t save_zone  = dead_zone * SCREEN_WIDTH;
    uint16_t clear_zone = FULL_SCREEN - save_zone;

    __builtin_memset(VGA, BLACK, clear_zone);
}

#endif // RENDER_H