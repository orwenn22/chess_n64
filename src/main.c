#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>

#include "Board.h"
#include "debug.h"

sprite_t *chess_tileset;
joypad_buttons_t pressed_buttons_state;
joypad_inputs_t inputs_state;

int main(void) {
    display_init( RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE );
    dfs_init( DFS_DEFAULT_LOCATION );
    rdpq_init();
    joypad_init();
    timer_init();
    debug_initialize();

    int fp = dfs_open("/chess_sprite.sprite");
    size_t sprite_size = dfs_size(fp);
    chess_tileset = malloc(sprite_size);
    dfs_read(chess_tileset, 1, sprite_size, fp);
    dfs_close(fp);

    Board *board = MakeBoard();

    while(1) {
        /* Update input state*/
        joypad_poll();
        inputs_state = joypad_get_inputs(JOYPAD_PORT_1);
        pressed_buttons_state = joypad_get_buttons_pressed(JOYPAD_PORT_1);

        UpdateBoard(board);

        // DRAW
        surface_t *disp = display_get();
        graphics_fill_screen( disp, 0x11111111 );

        /* Enable transparent sprite display instead of solid color fill */
        rdpq_set_mode_copy(true);

        /* Attach RDP to display; pass NULL as Z-buffer since we don't need it */
        rdpq_attach( disp, NULL );

        DrawBoard(board);


        /* Inform the RDP we are finished drawing and that any pending operations should be flushed */
        rdpq_detach_wait();

        /* Force backbuffer flip */
        display_show(disp);
    }

    return 0;
}