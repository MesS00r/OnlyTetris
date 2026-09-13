#include <libs/game_lib.h>
#include <libs/render.h>
#include <libs/sys_lib.h>
#include <generated/tetrominoes.h>
#include <libs/macros.h>

#include <stdint.h>

static inline void clear_screen(void) {
    __builtin_memset(VGA, BLACK, FULL_SCREEN);
}

__attribute__((section(".main")))
void _main(void) {
    restart:

        ;
        uint8_t coord_x = 0;
        uint8_t coord_y = 0;
        uint8_t turn    = 0;
        uint8_t rand    = 0;

        is_dead = 0;
        clear_screen();

        while (!is_dead) {
            wait_frame();

            uint16_t tetromino = tetrominoes[rand][turn];
            tetromino_clear(coord_x, coord_y, tetromino);

            uint8_t hit_down = 0;
            if (wait_ticks(PIT_FREQ / 2)) {
                coord_y++;

                if (check_collision(coord_x, coord_y, tetromino)) {
                    coord_y--;
                    hit_down = 1;
                }
            }

            if (!hit_down) {
                uint8_t next_x    = coord_x;
                uint8_t next_turn = turn;
                uint8_t next_y    = coord_y;

                switch (get_key()) {
                    case KEY_SPACE: next_y++;                        break;
                    case KEY_W:     next_turn = (next_turn + 1) & 3; break;
                    case KEY_A:     next_x--;                        break;
                    case KEY_D:     next_x++;                        break;
                }

                uint16_t test_tetromino = tetrominoes[rand][next_turn];
             
                if (!check_collision(next_x, next_y, test_tetromino)) {
                    coord_x   = next_x;
                    coord_y   = next_y;
                    turn      = next_turn;
                    tetromino = test_tetromino;
                } else if (next_y > coord_y) {
                    hit_down = 1;
                }
            }

            if (hit_down) {
                tetromino_draw(coord_x, coord_y, tetromino);
                        
                if (coord_y <= 0) {
                    is_dead = 1;
                    break;
                }

                clear_line();

                coord_x = 0; 
                coord_y = 0;
                turn    = 0;
                rand    = (rand + 1) % 7;
                
                continue; 
            }

            tetromino_draw(coord_x, coord_y, tetromino);
        }

    while (get_key() == KEY_ERR) {
        goto restart;
    }

    __asm__ volatile("hlt\njmp .");
}