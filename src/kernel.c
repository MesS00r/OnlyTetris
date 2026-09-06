#include <libs/game_lib.h>
#include <libs/render.h>
#include <libs/sys_lib.h>
#include <generated/tetrominoes.h>
#include <libs/macros_types.h>

#include <stdint.h>

#define DEBUG 1

__attribute__((section(".main")))
void _main(void) {
    uint8_t coord_y = 0;
    uint8_t coord_x = 0;
    uint8_t turn    = 0;
    uint8_t rand    = random_byte() % 7;
    uint8_t is_fall = 0;

    while (1) {
        wait_frame();

        uint16_t tetromino = tetrominoes[rand][turn];
        uint8_t hitbox     = tetromino_hitboxes[rand][turn];

        tetromino_draw(coord_x, coord_y, tetromino);

#if DEBUG
        if (flags.is_dead) {
            VGA[1][1] = 4;
        }
#endif

        if (coord_y >= DEAD_HEIGHT(hitbox & 0x0F)) {
            is_fall = 1;
        }

        if (is_fall) {
            tetromino_clear(coord_x, coord_y);

            rand    = random_byte() % 7;
            coord_y = 0;
            is_fall = 0;
        }
#if DEBUG
        else if (wait_ticks(PIT_FREQ / 4)) {
            tetromino_clear(coord_x, coord_y);

            coord_y++;
        }
#else
        else if (wait_ticks(PIT_FREQ)) {
            tetromino_clear(coord_x, coord_y);
            
            coord_y++;
        }
#endif
    }
    __asm__ volatile("hlt\njmp .");
}