//---------------------------------------------------------------------------//
#ifndef input_h
#define input_h
//---------------------------------------------------------------------------//
typedef struct KC_keydata
{
    bool down;
    bool handled;
} KC_keydata_t;
//---------------------------------------------------------------------------//
typedef struct KC_keys
{
    KC_keydata_t _8;
    KC_keydata_t _9;
    KC_keydata_t _2nd;
    KC_keydata_t enter;
    KC_keydata_t up;
    KC_keydata_t down;
    KC_keydata_t clear;
} KC_keys_t;

//---------------------------------------------------------------------------//
void initialise_interrupts(void);
void pulldown_interrupts(void);
void init_keys_data(KC_keys_t *keys);
void set_keydata(KC_keydata_t *keydata, bool down);
bool handle(KC_keydata_t *keydata);
void clear_keys(void);
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
#endif