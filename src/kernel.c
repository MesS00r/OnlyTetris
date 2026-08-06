#include <stdint.h>
#include <libs/render.h>
#include <libs/sys_lib.h>
#include <generated/tetrominoes.h>

__attribute__((section(".main")))
void _main(void) {
    uint8_t i = 0;

    while (1) {
        wait_frame();
        clear_screen();

        tetromino_draw(MAP_WIDTH  / 2 - 2,
                       MAP_HEIGHT / 2 - 2,
                       tetrominoes[0][i]
                      );

        VGA[1][1] = TILE_COLOR;

        if (i >= TURN_NUM)                 i = 0;
        else if (wait_ticks(PIT_FREQ / 2)) i++;

    }
    __asm__ volatile("hlt\njmp .");
}