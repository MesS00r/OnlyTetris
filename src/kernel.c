#include <stdint.h>
#include <libs/render.h>
#include <libs/sys_lib.h>
#include <generated/tetrominoes.h>

__attribute__((section(".main")))
void _main(void) {
    uint8_t count  = 0;
    uint8_t count1 = 0;

    while (1) {
        wait_frame();
        clear_screen();
    
        count1 = (count / 15) % 7;
        tetromino_draw(MAP_WIDTH  / 2 - 2,
                       MAP_HEIGHT / 2 - 2,
                       tetrominoes[count1]
                      );

        VGA[0][0] = TILE;

        if (count >= 255)count = 0;
        else count++;
    }
    __asm__ volatile("hlt\njmp .");
}