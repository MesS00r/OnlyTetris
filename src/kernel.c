#include <stdint.h>
#include <my_libs/vesa.h>

__attribute__((section(".main")))
void _main(void) {
    vesa_init();

    for (uint32_t i = 0; i < FULL_SCREEN; i++) {
        vesa_set_pix(i, i % 16);
    }

    __asm__("hlt\njmp .");
}