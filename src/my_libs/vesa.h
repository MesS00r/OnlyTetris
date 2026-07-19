#ifndef VESA_H
#define VESA_H

#include <stdint.h>
#include <generated/vesa_consts.h>

static uint8_t *vesa;

static void vesa_init() { vesa = *(uint8_t **)VESA_ADDR; }
static void vesa_set_pix(uint32_t index, VESA_16C color) { vesa[index] = color; }

#endif // VESA_H