#ifndef SYS_LIB_H
#define SYS_LIB_H

#include <stdint.h>

#define PIT_COMMAND_PORT  0x43
#define PIT_CHANNEL0_PORT 0x40
#define PIT_FREQ          1193182
#define TARGET_FPS        60

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "dN"(port));
    return result;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "dN"(port));
}

static uint16_t pit_read_counter(void) {
    outb(PIT_COMMAND_PORT, 0x00);
    uint16_t low  = inb(PIT_CHANNEL0_PORT);
    uint16_t high = inb(PIT_CHANNEL0_PORT);
    return (high << 8) | low;
}

static void wait_frame(void) {
    uint16_t start = pit_read_counter();
    while((uint16_t)(start - pit_read_counter()) < PIT_FREQ / TARGET_FPS);
}

#endif // SYS_LIB_H