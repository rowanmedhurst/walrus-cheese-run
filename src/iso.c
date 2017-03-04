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
void fast_isotile_blit_noclip(int x, int y, gfx_image_t* data)
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
}
//---------------------------------------------------------------------------//
void draw_isotile_noclip(int x, int y, int tile_idx)
{
    switch (tile_idx)
    {
    case 0: fast_isotile_blit_noclip(x, y, grass0); break;
    case 1: fast_isotile_blit_noclip(x, y, grass1); break;
    case 2: fast_isotile_blit_noclip(x, y, grass2); break;
    case 3: fast_isotile_blit_noclip(x, y, grass3); break;
    case 4: fast_isotile_blit_noclip(x, y, sand0); break;
    case 5: fast_isotile_blit_noclip(x, y, sand1); break;
    case 6: fast_isotile_blit_noclip(x, y, concrete); break;
    }
}
//---------------------------------------------------------------------------//
void draw_isotile_clipped(int x, int y, int tile_idx)
{
    switch (tile_idx)
    {
    case 0: gfx_TransparentSprite(grass0, x, y); break;
    case 1: gfx_TransparentSprite(grass1, x, y); break;
    case 2: gfx_TransparentSprite(grass2, x, y); break;
    case 3: gfx_TransparentSprite(grass3, x, y); break;
    case 4: gfx_TransparentSprite(sand0, x, y); break;
    case 5: gfx_TransparentSprite(sand1, x, y); break;
    case 6: gfx_TransparentSprite(concrete, x, y); break;
    }
}
//---------------------------------------------------------------------------//
void draw_isomap(int x, int y)
{
    int row, col, pixelx, pixely, rowmul_21;
    bool clipy, clipx;

	for (row = 0; row < 92; row++)
	{
		pixely = row * 8;
		if (pixely-y+15 <= 0) continue;
		if (pixely-y >= 240) continue;
		rowmul_21 = row * 21;

		clipy = true;
		if ((pixely-y >= 0) && (pixely-y <= 225)) clipy = false;

		for (col = 0; col < 21; col++)
		{
			pixelx = col * 32;
			if (row & 0x1) pixelx += 16;
			if (pixelx-x+32 <= 0) continue;
			if (pixelx-x >= 320) continue;

            clipx = false;
			if ((pixelx-x < 0) || (pixelx-x > 288)) clipx = true;

			if (clipx || clipy)
    			draw_isotile_clipped(pixelx-x, pixely-y, map_data[rowmul_21+col]);
    		else
    			draw_isotile_noclip(pixelx-x, pixely-y, map_data[rowmul_21+col]);
		}
	}
}
//---------------------------------------------------------------------------//
