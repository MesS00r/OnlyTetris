#include <libs/game_lib.h>
#include <libs/render.h>
#include <libs/sys_lib.h>
#include <generated/tetrominoes.h>
#include <libs/macros.h>

#include <stdint.h>

__attribute__((section(".main")))
void _main(void) {
    uint8_t coord_x = 0;
    uint8_t cooed_y = 0;
    uint8_t turn    = 0;
    uint8_t rand    = 3;

    uint16_t tetromino = tetrominoes[rand][turn];
    uint8_t hitbox     = tetromino_hitboxes[rand][turn];
    tetromino_draw(coord_x, cooed_y, tetromino);

    while (TRUE) {
        while (wait_ticks(PIT_FREQ / 2));

        if (is_dead) {
            VGA[1][1] = 4;
        }

        

    }

    __asm__ volatile("hlt\njmp .");
}