#ifndef _HOME_MESS0R_DOCUMENTS_PROJECTS_ONLYTETRIS_SRC_GENERATED_TEXTURES_H
#define _HOME_MESS0R_DOCUMENTS_PROJECTS_ONLYTETRIS_SRC_GENERATED_TEXTURES_H

#include <stdint.h>
#include <generated/vesa_consts.h>

#define IMAGE_WIDHT         4
#define IMAGE_HEIGHT        56
#define IMAGE_PIXELS        224

#define TILE_DIMENSIONS     4
#define TILE_PIXELS         16
#define TILES_NUM           14

// * -------------------------------------------------------------------------------
// * TILE PALETTES
// * -------------------------------------------------------------------------------

enum TILE_BRICK_PALETTE  { COLOR0_0 = BLACK , COLOR0_1 = RED    };
enum TILE_GREEN_PALETTE  { COLOR1_0 = BLACK , COLOR1_1 = GREEN  };
enum TILE_BLUE_PALETTE   { COLOR2_0 = BLACK , COLOR2_1 = BLUE   };
enum TILE_YELLOW_PALETTE { COLOR3_0 = BLACK , COLOR3_1 = YELLOW };
enum TILE_NUMS_PALETTE   { COLOR4_0 = BLACK , COLOR4_1 = WHITE  };

// * -------------------------------------------------------------------------------
// * RGBY TILES
// * -------------------------------------------------------------------------------

static const uint8_t tile_brick[] = {
	COLOR0_1, COLOR0_1, COLOR0_0, COLOR0_1,
	COLOR0_0, COLOR0_0, COLOR0_0, COLOR0_0,
	COLOR0_1, COLOR0_0, COLOR0_1, COLOR0_1,
	COLOR0_0, COLOR0_0, COLOR0_0, COLOR0_0
};

static const uint8_t tile_green[] = {
	COLOR1_1, COLOR1_1, COLOR1_1, COLOR1_0,
	COLOR1_1, COLOR1_1, COLOR1_1, COLOR1_0,
	COLOR1_1, COLOR1_1, COLOR1_1, COLOR1_0,
	COLOR1_0, COLOR1_0, COLOR1_0, COLOR1_0
};

static const uint8_t tile_blue[] = {
	COLOR2_1, COLOR2_0, COLOR2_0, COLOR2_0,
	COLOR2_0, COLOR2_1, COLOR2_1, COLOR2_0,
	COLOR2_0, COLOR2_1, COLOR2_1, COLOR2_0,
	COLOR2_0, COLOR2_0, COLOR2_0, COLOR2_0
};

static const uint8_t tile_yellow[] = {
	COLOR3_1, COLOR3_1, COLOR3_1, COLOR3_0,
	COLOR3_1, COLOR3_1, COLOR3_0, COLOR3_0,
	COLOR3_1, COLOR3_0, COLOR3_0, COLOR3_0,
	COLOR3_0, COLOR3_0, COLOR3_0, COLOR3_0
};

// * -------------------------------------------------------------------------------
// * NUM TILES
// * -------------------------------------------------------------------------------

static const uint8_t tile_num0[] = {
	COLOR4_0, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_0, COLOR4_1, COLOR4_1,
	COLOR4_1, COLOR4_1, COLOR4_0, COLOR4_1,
	COLOR4_0, COLOR4_1, COLOR4_1, COLOR4_0
};

static const uint8_t tile_num1[] = {
	COLOR4_0, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_0, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_1
};

static const uint8_t tile_num2[] = {
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_0, COLOR4_0, COLOR4_0, COLOR4_1,
	COLOR4_0, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_1
};

static const uint8_t tile_num3[] = {
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_1,
	COLOR4_0, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_0, COLOR4_0, COLOR4_0, COLOR4_1,
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_0
};

static const uint8_t tile_num4[] = {
	COLOR4_0, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_0, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_1,
	COLOR4_0, COLOR4_0, COLOR4_1, COLOR4_0
};

static const uint8_t tile_num5[] = {
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_1,
	COLOR4_1, COLOR4_1, COLOR4_0, COLOR4_0,
	COLOR4_0, COLOR4_0, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_0
};

static const uint8_t tile_num6[] = {
	COLOR4_0, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_1, COLOR4_0, COLOR4_0,
	COLOR4_1, COLOR4_0, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_0
};

static const uint8_t tile_num7[] = {
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_1,
	COLOR4_1, COLOR4_0, COLOR4_0, COLOR4_1,
	COLOR4_0, COLOR4_0, COLOR4_1, COLOR4_0,
	COLOR4_0, COLOR4_0, COLOR4_1, COLOR4_0
};

static const uint8_t tile_num8[] = {
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_1,
	COLOR4_0, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_0, COLOR4_0, COLOR4_1,
	COLOR4_0, COLOR4_1, COLOR4_1, COLOR4_0
};

static const uint8_t tile_num9[] = {
	COLOR4_1, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_0, COLOR4_1, COLOR4_0,
	COLOR4_0, COLOR4_1, COLOR4_1, COLOR4_0,
	COLOR4_1, COLOR4_1, COLOR4_0, COLOR4_0
};


#endif // _HOME_MESS0R_DOCUMENTS_PROJECTS_ONLYTETRIS_SRC_GENERATED_TEXTURES_H