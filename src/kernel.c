#include <stdint.h>
#include <libs/render.h>
#include <libs/sys_lib.h>
#include <generated/tetrominoes.h>

__attribute__((section(".main")))
void _main(void) {
    while (1) {
        wait_frame();
        clear_screen();
    
        tetromino_draw(10, 10, tetrominoes[3]);

        VGA[0][0] = TILE;
    }
    __asm__ volatile("hlt\njmp .");
}