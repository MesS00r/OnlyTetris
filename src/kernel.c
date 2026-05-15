#include <stdint.h>

__attribute__((section(".main")))
void _main(void) {
    uint8_t *vga = (uint8_t *)0xA0000;

    for (uint32_t i = 0; i < 10000; i++) {
        vga[i] = 4;
    }

    __asm__(
        "hlt\n"
        "jmp ."
    );
}