#include <stdint.h>
#include <my_libs/libs_c/vga_enums.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

uint8_t vga_color_rgb(uint8_t r, uint8_t g, uint8_t b);

void _kernel(void) {
    uint8_t *vga = (uint8_t *)0xA0000;

    for (uint32_t i = 0; i < 10000; i++) {
        vga[i] = vga_color_rgb(123, 54, 78);
    }

    for (uint32_t i = 10000; i < 20000; i++) {
        vga[i] = RED;
    }
}