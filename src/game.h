//---------------------------------------------------------------------------//
#ifndef game_H
#define game_H
//---------------------------------------------------------------------------//
void game_loop(void);


//---------------------------------------------------------------------------//
#define NUM_WALRII 40
//---------------------------------------------------------------------------//
typedef struct game_vars
{
    int mechl_x;
    int mechl_y;
    int mechr_x;
    int mechr_y;
    int walrii_x[NUM_WALRII];
    int walrii_y[NUM_WALRII];
    uint8_t walrii_dir[NUM_WALRII];
    bool walrii_blud[NUM_WALRII];
}
game_vars_t;


//---------------------------------------------------------------------------//
#endif