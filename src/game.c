//---------------------------------------------------------------------------//
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <stdlib.h>
#include <math.h>
#include <include/lib/ce/graphx.h>

#include "game.h"
#include "main.h"
#include "iso.h"
#include "input.h"
#include "fps.h"
#include "gfx/isogfx.h"
//---------------------------------------------------------------------------//
game_vars_t GAME_VARS;
extern KC_keys_t KEYS;
//---------------------------------------------------------------------------//
void populate_map(void)
{
    int i;
    float d;

    // generate mech positions

    d = (rand() % 628) / 100.0f;

    GAME_VARS.mechr_x = 150 + 130 * sin(d);
    GAME_VARS.mechr_y = 390 + 130 * cos(d);

    d = (rand() % 628) / 100.0f;

    GAME_VARS.mechl_x = 510 + 130 * sin(d);
    GAME_VARS.mechl_y = 310 + 130 * cos(d);

    // generate walrii positions and orientations

    for (i = 0; i < NUM_WALRII; i++)
    {
        GAME_VARS.walrii_x[i] = (rand() % 632) + 28;
        GAME_VARS.walrii_y[i] = (rand() % 664) + 28;
        GAME_VARS.walrii_dir[i] = rand() % 1;
        GAME_VARS.walrii_blud[i] = false;
    }
}
//---------------------------------------------------------------------------//
void game_loop(void)
{
    int mapx = 168, mapy = 496;
    int truckx = 328, trucky = 717;
    int8_t truckdir = 0;
    uint8_t truckspeed = 0;
    int dx, dy, i;
    int score = 0;

    // randomly position walrii and mechs
    populate_map();


    // init framerate counter
    fps_init();

    //----
    do
    {
        // move truck

        if (truckdir == 0) {
            dy = 145 * truckspeed / 128;
            trucky -= dy;
        }
        else {
            dx = 205 * truckspeed / 128;
            dy = 205 * truckspeed / 256;
            if (truckdir == -1) truckx -= dx;
            else truckx += dx;
            trucky -= dy;
        }
        
        // splat walruses

        for (i = 0; i < NUM_WALRII; i++)
        {
            if (!GAME_VARS.walrii_blud[i])
            {
                dx = abs(truckx - GAME_VARS.walrii_x[i]);
                dy = abs(trucky - GAME_VARS.walrii_y[i]);
                if (dx < 20 && dy < 20)
                    GAME_VARS.walrii_blud[i] = true;
            }
        }

        // restrict truck's position to hard limits

        if (truckx < 16 + 13) { truckx = 16 + 13; truckdir = 0; }
        else if (truckx > 688 - 48 - 13) { truckx = 688 - 48 - 13; truckdir = 0; }

        if (trucky < 7 + 19) { // you have won!
            clear_keys();
            return;
        }

        // update camera position to keep truck in the screen

        if (trucky-19-mapy < 180) mapy -= 180 - (trucky-19-mapy);
        
        if (truckx-13-mapx < 100) mapx -= 100 - (truckx-13-mapx);
        else if (truckx-13-mapx > 170) mapx += (truckx-13-mapx) - 170;
        
        // restrict camera position to hard limits

        if (mapx < 16) mapx = 16;
        else if (mapx > 336) mapx = 336;

        if (mapy < 7) mapy = 7;


        // accelerate if not at top speed
        if (truckspeed < 4) {
            truckspeed++;
        }


        //render

        draw_isomap(mapx, mapy);
        gfx_TransparentSprite(statue, 336-mapx, 318-mapy);
        gfx_TransparentSprite(mechr, GAME_VARS.mechr_x-mapx, GAME_VARS.mechr_y-mapy);
        gfx_TransparentSprite(mechl, GAME_VARS.mechl_x-mapx, GAME_VARS.mechl_y-mapy);

        for (i = 0; i < NUM_WALRII; i++)
        {
            if (GAME_VARS.walrii_blud[i])
            {
                gfx_TransparentSprite(blood, GAME_VARS.walrii_x[i]-mapx, GAME_VARS.walrii_y[i]-mapy);
            }
            else
            {
                if (GAME_VARS.walrii_dir[i] == 0)
                    gfx_TransparentSprite(walrusl, GAME_VARS.walrii_x[i]-mapx, GAME_VARS.walrii_y[i]-mapy);
                else
                    gfx_TransparentSprite(walrusr, GAME_VARS.walrii_x[i]-mapx, GAME_VARS.walrii_y[i]-mapy);
            }
        }

        switch (truckdir)
        {
            case -1: gfx_TransparentSprite(truckl, truckx-13-mapx, trucky-19-mapy); break;
            case  0: gfx_TransparentSprite(truck, truckx-13-mapx, trucky-19-mapy); break;
            case  1: gfx_TransparentSprite(truckr, truckx-13-mapx, trucky-19-mapy); break;
        }
        submit_end_of_frame();
        print_fps();
        present();

        //handle keypresses
        if (handle(&KEYS._8) && truckdir>-1) {
            truckdir--;
        }
        if (handle(&KEYS._9) && truckdir<1) {
            truckdir++;
        }
        if (handle(&KEYS.clear)) {
            clear_keys();
            return;
        }
    }
    while(1);
}
//---------------------------------------------------------------------------//

