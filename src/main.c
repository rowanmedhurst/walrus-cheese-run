//---------------------------------------------------------------------------//
/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* C CE Graphics library */
//#include <lib/ce/graphx.h>
#include <include/lib/ce/graphx.h>

/* CE Keypad C Library */
#include <include/lib/ce/keypadc.h>

/* custom includes */
#include "main.h"
#include "frontend.h"
#include "input.h"
//---------------------------------------------------------------------------//
extern KC_keys_t KEYS;
uint8_t draw_buffer = 1;
//---------------------------------------------------------------------------//
void main(void)
{
    initialise_interrupts();

	gfx_Begin(gfx_8bpp);
	gfx_SetDrawBuffer();

	//----
	srand(rtc_Time());
    init_keys_data(&KEYS);
    main_menu();

	gfx_End();
    pulldown_interrupts();

	prgm_CleanUp();
}
//---------------------------------------------------------------------------//
void present(void)
{
    gfx_SwapDraw();

    if (draw_buffer == 0) draw_buffer = 1;
    else draw_buffer = 0;
}
//---------------------------------------------------------------------------//
uint8_t get_draw_buffer(void)
{
    return draw_buffer;
}
//---------------------------------------------------------------------------//
