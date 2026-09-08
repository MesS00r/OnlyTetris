#ifndef SYS_LIB_H
#define SYS_LIB_H

#include <libs/macros.h>
#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "dN"(port));
    return result;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "dN"(port));
}

static uint16_t pit_read_counter(void) {
    uint16_t low  = inb(PIT_CHANNEL0_PORT);
    uint16_t high = inb(PIT_CHANNEL0_PORT);
    
    outb(PIT_COMMAND_PORT, 0x00);
    return (high << 8) | low;
}

// static void wait_frame(void) {
//     uint16_t start = pit_read_counter();

//     while((uint16_t)(start - pit_read_counter()) < PIT_FREQ / TARGET_FPS);
// }

static uint8_t wait_ticks(uint32_t ticks)  {
    static uint16_t timer = 0;
    static uint32_t acc   = 0;

    if (timer == 0) { timer = pit_read_counter(); }

    uint16_t current = pit_read_counter();
    uint16_t delta   = (uint16_t)(timer - current);

    timer = current;
    acc += delta;

    if (acc >= ticks) { acc -= ticks; return TRUE; }
    else              { return FALSE; }
}

static uint8_t get_key(void) {
    if (!(inb(STATUS_PORT) & STATUS_FULL)) {
        return KEY_ERR;
    }

    uint8_t code = inb(DATA_PORT);

    if (code & 0x80) {
        return KEY_ERR;
    }

    switch (code) {
    case KEY_SPACE_CODE: return KEY_SPACE;
    case KEY_W_CODE:     return KEY_W;
    case KEY_A_CODE:     return KEY_A;
    case KEY_D_CODE:     return KEY_D;
    default:             return KEY_ERR;
    }
}

#endif // SYS_LIB_H