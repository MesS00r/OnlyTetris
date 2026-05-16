#include <stdint.h>
#include <my_libs/vga_colors.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

__attribute__((section(".main")))
void _main(void) {
    uint8_t *vga = (uint8_t *)0xA0000;

    for (uint32_t i = 0; i < 10000; i++) {
        vga[i] = RED;
    }

    __asm__("hlt\njmp .");
}