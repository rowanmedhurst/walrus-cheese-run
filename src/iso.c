//---------------------------------------------------------------------------//
// Isotile render functionality
// - this file is hardcoded for 32x15 tiles and 21x92 map
//---------------------------------------------------------------------------//
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <string.h>
#include <include/lib/ce/graphx.h>

#include "iso.h"
#include "gfx/isogfx.h"
//---------------------------------------------------------------------------//
extern uint8_t map_data[];
//---------------------------------------------------------------------------//
static const gfx_image_t *tile_img[] = {
    grass0, grass1, grass2, grass3, sand0, sand1, concrete
};
//---------------------------------------------------------------------------//
/*void fast_isotile_blit_noclip(gfx_image_t* data, unsigned x, uint8_t y)
{
    uint8_t *dst = &gfx_vbuffer[y][x];
    uint8_t *src = &data->data;

    dst += 14; src += 14;
    memcpy(dst, src, 4);
    dst += 318; src += 30;
    memcpy(dst, src, 8);
    dst += 318; src += 30;
    memcpy(dst, src, 12);
    dst += 318; src += 30;
    memcpy(dst, src, 16);
    dst += 318; src += 30;
    memcpy(dst, src, 20);
    dst += 318; src += 30;
    memcpy(dst, src, 24);
    dst += 318; src += 30;
    memcpy(dst, src, 28);

    dst += 318; src += 30;
    memcpy(dst, src, 32);

    dst += 322; src += 34;
    memcpy(dst, src, 28);
    dst += 322; src += 34;
    memcpy(dst, src, 24);
    dst += 322; src += 34;
    memcpy(dst, src, 20);
    dst += 322; src += 34;
    memcpy(dst, src, 16);
    dst += 322; src += 34;
    memcpy(dst, src, 12);
    dst += 322; src += 34;
    memcpy(dst, src, 8);
    dst += 322; src += 34;
    memcpy(dst, src, 4);
}*/
//---------------------------------------------------------------------------//
void draw_isomap(int x, int y)
{
    int pixely = 0;
    int pixelx = 0;
    int row, col, pixelx_subx, pixely_suby;
    unsigned int rowmul_21 = 0;
    bool odd, clipy, clipx;
    gfx_image_t *tile;
    
    for (row = 0; row < 92; row++)
    {
        pixely_suby = pixely-y;
        pixely += 8;
        if (pixely_suby+15 <= 0 || pixely_suby >= 240) continue;
        rowmul_21 = row * 21;
        
        if (pixely_suby >= 0 && pixely_suby <= 225)
           clipy = false;
        else
           clipy = true;
       
        odd = row & 1;
        for (pixelx = col = 0; col < 21; col++)
        {
            if (odd)
                pixelx_subx = pixelx-x+16;
            else
                pixelx_subx = pixelx-x;
            
            pixelx += 32;
            if (pixelx_subx >= 320 || pixelx_subx+32 <= 0) continue;

            if (pixelx_subx < 0 || pixelx_subx > 288)
                clipx = true;
            else
                clipx = false;
            
            tile = tile_img[map_data[rowmul_21+col]];
            
            if (clipx || clipy)
                gfx_TransparentSprite(tile, pixelx_subx, pixely_suby);
            else
                fast_isotile_blit_noclip(tile, pixelx_subx, pixely_suby);
        }
    }
}
//---------------------------------------------------------------------------//
