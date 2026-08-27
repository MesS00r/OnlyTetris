#include <libs/game_lib.h>
#include <libs/render.h>
#include <libs/sys_lib.h>
#include <generated/tetrominoes.h>
#include <libs/macros_types.h>

#include <stdint.h>

#define DEBUG 1

__attribute__((section(".main")))
void _main(void) {
    uint8_t coord_y = 0;
    uint8_t coord_x = 0;
    uint8_t turn    = 0;
    uint8_t rand    = random_byte() % 7;
    uint8_t is_fall = 0;

    while (1) {
        wait_frame();
        clear_screen();

        uint16_t tetromino = tetrominoes[rand][turn];
        uint8_t hitbox     = tetromino_hitboxes[rand][turn];

        tetromino_draw(coord_x, coord_y, tetromino);
        heights_draw(heights);

#if DEBUG
        if (flags.is_dead) {
            VGA[1][1] = 4;
        }
#endif

        for (uint8_t i = 0; i < TETROMINO_WIDTH(hitbox); i++) {
            uint8_t t_height = TETROMINO_HEIGHT(hitbox);
            uint8_t total    = t_height + heights[coord_x + i].num;

            if (coord_y >= DEAD_HEIGHT(total)) {
                is_fall = 1;
                break;
            }
        }

        if (is_fall) {
            add_height(tetrominoes[rand][(turn + 1) & 3],
                       hitbox,
                       coord_x,
                       coord_y
                      );
            
            rand    = random_byte() % 7;
            coord_y = 0;
            is_fall = 0;
        }
#if DEBUG
        else if (wait_ticks(PIT_FREQ / 4)) coord_y++;
#else
        else if (wait_ticks(PIT_FREQ)) coord_y++;
#endif
    }
    __asm__ volatile("hlt\njmp .");
}