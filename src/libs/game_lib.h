#ifndef GAME_LIB_H
#define GAME_LIB_H

#include <libs/macros_types.h>
#include <stdint.h>

static const uint8_t height_lut[] = {
    0, 1, 2, 2, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4
};

static uint8_t random_byte() {
    static uint16_t rng = 0xACE1;

    uint16_t bit = ((rng >> 0) ^
                    (rng >> 2) ^
                    (rng >> 3) ^
                    (rng >> 5)
                   ) & 1;

    rng = (rng >> 1) | (bit << 15);
    return rng & 0xFF;
}



#endif // GAME_LIB_H