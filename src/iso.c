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
void draw_isomap(int x, int y)
{
    int row, col, pixelx, pixely, rowmul_21;
    bool clipy, clipx;
    gfx_image_t *tile;

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
			
			tile = tile_img[map_data[rowmul_21+col]];

			if (clipx || clipy)
    			gfx_TransparentSprite(tile, pixelx-x, pixely-y);
    		else
    			fast_isotile_blit_noclip(tile, pixelx-x, pixely-y);
		}
	}
}
//---------------------------------------------------------------------------//
