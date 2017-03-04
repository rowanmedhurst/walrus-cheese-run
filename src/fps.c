//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <include/lib/ce/graphx.h>

#include "fps.h"
//---------------------------------------------------------------------------//
uint8_t FPS = 0;
uint8_t framecount = 0;
//---------------------------------------------------------------------------//
void fps_init(void)
{
    timer_Control = TIMER2_ENABLE | TIMER2_32K | TIMER2_UP;
    timer_2_Counter = 0;
}
//---------------------------------------------------------------------------//
void submit_end_of_frame(void)
{
    framecount++;

    if (timer_2_Counter >= 32768)
    {
        timer_2_Counter -= 32768;
        FPS = framecount;
        framecount = 0;
    }
}
//---------------------------------------------------------------------------//
void print_fps(void)
{
    gfx_SetTextXY(0, 0);
    gfx_PrintInt(FPS, 3);
}
//---------------------------------------------------------------------------//
