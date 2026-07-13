#include <stdint.h>

#define VESA_ADDR     0x7B00
#define SCREEN_HEIGHT 480
#define SCREEN_WIDHT  640
#define FULL_SCREEN   307200

typedef enum {
    BLACK, BLUE, GREEN, CYAN,
    RED, MAGENTA, BROWN, LIGHT_GREY,
    DARK_GREY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
    LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE
} VESA_16C;

static uint8_t *vesa;

static void vesa_init() { vesa = *(uint8_t **)VESA_ADDR; }
static void vesa_set_pix(uint32_t index, VESA_16C color) { vesa[index] = color; }
