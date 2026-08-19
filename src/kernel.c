#include "libs/game_lib.h"
#include <stdint.h>
#include <libs/render.h>
#include <libs/sys_lib.h>
#include <generated/tetrominoes.h>

#define DEBUG 1

__attribute__((section(".main")))
void _main(void) {
    struct Tetromino tetromino = {
        .mask   = tetrominoes[0][0],
        .hitbox = tetromino_hitboxes[0][0]
    };

    uint8_t coord_y = 0;
    uint8_t rand    = random_byte() % 7;

    while (1) {
        wait_frame();
        clear_screen();

        tetromino.mask   = tetrominoes[rand][0];
        tetromino.hitbox = tetromino_hitboxes[rand][0];

        tetromino_draw(0, coord_y, tetromino.mask);

        if (coord_y >= DEAD_HEIGHT(tetromino.hitbox)) {
            add_height(tetromino);
            
            dead_zone += DEAD_HEIGHT(tetromino.hitbox);
            rand      = random_byte() % 7;
            coord_y   = 0;
        }
#if DEBUG
        else if (wait_ticks(PIT_FREQ / 4)) coord_y++;
#else
        else if (wait_ticks(PIT_FREQ)) coord_y++;
#endif
    }
    __asm__ volatile("hlt\njmp .");
}