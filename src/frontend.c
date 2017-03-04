//---------------------------------------------------------------------------//
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <include/lib/ce/graphx.h>

#include "frontend.h"
#include "main.h"
#include "game.h"
#include "input.h"
#include "gfx/isogfx.h"
//---------------------------------------------------------------------------//
const char title_txt[] = "WALRUS CHEESE RUN";
const char run_txt[] = "play";
const char credits_txt[] = "credits";
const char quit_txt[] = "quit";
//---------------------------------------------------------------------------//
uint8_t menu_item = 0;
extern KC_keys_t KEYS;
//---------------------------------------------------------------------------//
void main_menu(void)
{
    gfx_SetPalette(isogfx_pal, sizeof(isogfx_pal), 0);
    gfx_SetTransparentColor(0);

    do
    {
        print_mainmenu();

        if (handle(&KEYS.down))
        {
            if (menu_item < 2) menu_item++;
        }
        if (handle(&KEYS.up))
        {
            if (menu_item > 0) menu_item--;
        }
        if (handle(&KEYS.clear))
        {
            return;
        }
        if (handle(&KEYS._2nd) || handle(&KEYS.enter))
        {
            if (menu_item == 0) {
                game_loop();
            }
            else if (menu_item == 1) {
                credits();
            }
            else if (menu_item == 2) {
                return;
            }
        }
    }
    while (1);
}
//---------------------------------------------------------------------------//
void print_mainmenu(void)
{
    gfx_FillScreen(67);
    gfx_SetTextFGColor(22);
    gfx_SetTextBGColor(21);

    gfx_SetTextXY(80, 60);
    gfx_PrintString(title_txt);

    gfx_SetTextXY(80, 130);
    gfx_PrintString(menu_item == 0 ? "- " : "");
    gfx_PrintString(run_txt);
    gfx_PrintString(menu_item == 0 ? " -" : "");

    gfx_SetTextXY(80, 150);
    gfx_PrintString(menu_item == 1 ? "- " : "");
    gfx_PrintString(credits_txt);
    gfx_PrintString(menu_item == 1 ? " -" : "");

    gfx_SetTextXY(80, 170);
    gfx_PrintString(menu_item == 2 ? "- " : "");
    gfx_PrintString(quit_txt);
    gfx_PrintString(menu_item == 2 ? " -" : "");

    present();
}
//---------------------------------------------------------------------------//
void credits(void)
{
    gfx_FillScreen(67);

    gfx_SetTextXY(45, 110);
    gfx_PrintString("CREDITS");

    gfx_SetTextXY(150, 35);
    gfx_PrintString("DESIGN+CODE");
    gfx_SetTextXY(150, 55);
    gfx_PrintString("kotu");

    gfx_SetTextXY(150, 90);
    gfx_PrintString("GRAPHICS");
    gfx_SetTextXY(150, 110);
    gfx_PrintString("kotu");
    gfx_SetTextXY(150, 130);
    gfx_PrintString("dj omnimaga");
    gfx_SetTextXY(150, 150);
    gfx_PrintString("p2");

    gfx_SetTextXY(150, 185);
    gfx_PrintString("SPECIAL THANKS");
    gfx_SetTextXY(150, 205);
    gfx_PrintString("mateoconlechuga");
    present();

    while (1) {
        if (handle(&KEYS.clear))
        {
            clear_keys();
            return;
        }
    }
}
//---------------------------------------------------------------------------//
