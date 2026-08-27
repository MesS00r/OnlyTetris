#ifndef MACROS_TYPES_H
#define MACROS_TYPES_H

#include <stdint.h>

// ---------------------------------------------------------
// | MACROS
// ---------------------------------------------------------

#define VGA_ADDR              0xA0000
#define SCREEN_HEIGHT         200
#define SCREEN_WIDTH          320
#define FULL_SCREEN           64000

#define PIT_COMMAND_PORT      0x43
#define PIT_CHANNEL0_PORT     0x40
#define PIT_FREQ              1193182
#define TARGET_FPS            60

#define TILE_DIMENSIONS       8
#define TILE_DIMS_OFFSET      3
#define MAP_HEIGHT            25
#define MAP_WIDTH             40
#define FULL_MAP              1000

#define BASE_MASK             0x0101010101010101ULL
#define TILE_COLOR            15
#define BLACK                 0

#define TETROMINO_REAL_HEIGHT 32
#define TETROMINO_DIMENSIONS  4
#define TETROMINO_HALF_DIMS   2

#define VGA ((uint8_t (*)[SCREEN_WIDTH])VGA_ADDR)

#define MASK_LINE(m, i)      (((m) >> (((i) & 3) * 4)) & 0x0F)
#define NUM_BIT(n, i)        (((n) >> (i)) & 1)

#define TETROMINO_WIDTH(h)   ((h) >> 4)
#define TETROMINO_HEIGHT(h)  ((h) & 0x0F)

#define DEAD_HEIGHT(h)       (MAP_HEIGHT - (h))
#define SCREEN_POS(x, y)     ((y) * SCREEN_WIDTH + (x))

// ---------------------------------------------------------
// | TYPES
// ---------------------------------------------------------

struct Flags {
    unsigned char is_dead : 1;
};
static struct Flags flags;

struct Heights {
    unsigned int mask : 24;
    unsigned int num  : 8;
};

#endif // MACROS_TYPES_H