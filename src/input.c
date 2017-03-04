//---------------------------------------------------------------------------//
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <intce.h>
#include <include/lib/ce/keypadc.h>
#include "input.h"
//---------------------------------------------------------------------------//
KC_keys_t KEYS;
//---------------------------------------------------------------------------//
void init_keydata(KC_keydata_t *key)
{
    key->down = false;
    key->handled = true;
}
//---------------------------------------------------------------------------//
void init_keys_data(KC_keys_t *keys)
{
    init_keydata(&keys->_8);
    init_keydata(&keys->_9);
    init_keydata(&keys->_2nd);
    init_keydata(&keys->enter);
    init_keydata(&keys->up);
    init_keydata(&keys->down);
    init_keydata(&keys->clear);
}
//---------------------------------------------------------------------------//
void clear_keys(void)
{
    handle(&KEYS._8);
    handle(&KEYS._9);
    handle(&KEYS._2nd);
    handle(&KEYS.enter);
    handle(&KEYS.up);
    handle(&KEYS.down);
    handle(&KEYS.clear);
}
//---------------------------------------------------------------------------//
bool handle(KC_keydata_t *keydata)
{
    if (keydata->handled == false)  // new keydown event
    {
        keydata->handled = true;
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------//
void set_keydata(KC_keydata_t *keydata, bool down)
{
    if (down == false)
    {
        keydata->down = false;
    }
    else
    {
        if (!keydata->down) {
            keydata->handled = false;
        }
        keydata->down = true;
    }
}
//---------------------------------------------------------------------------//
void interrupt isr_keyboard(void)
{
    kb_key_t key;

    key = kb_Data[kb_group_1];
    set_keydata(&KEYS._2nd, key & kb_2nd);

    key = kb_Data[kb_group_4];
    set_keydata(&KEYS._8, key & kb_8);

    key = kb_Data[kb_group_5];
    set_keydata(&KEYS._9, key & kb_9);

    key = kb_Data[kb_group_6];
    set_keydata(&KEYS.enter, key & kb_Enter);
    set_keydata(&KEYS.clear, key & kb_Clear);

    key = kb_Data[kb_group_7];
    set_keydata(&KEYS.up, key & kb_Up);
    set_keydata(&KEYS.down, key & kb_Down);

    // Must acknowledge that the interrupt occured to clear the flag
    int_Acknowledge = INT_KEYBOARD;
    // Acknowledge in the keypad controller (Not technically required because interrupt controller handles signal)
    kb_IntAcknowledge = KB_DATA_CHANGED;
}
//---------------------------------------------------------------------------//
void initialise_interrupts(void)
{
    int_Initialize();
    int_SetVector(KEYBOARD_IVECT, isr_keyboard);
    int_LatchConfig = int_EnableConfig = INT_KEYBOARD;
    kb_EnableInt = KB_DATA_CHANGED;
    kb_SetMode(MODE_3_CONTINUOUS);
    int_Enable();
}
//---------------------------------------------------------------------------//
void pulldown_interrupts(void)
{
    int_Reset();
    kb_Reset();
}
//---------------------------------------------------------------------------//
