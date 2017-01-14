#ifndef DOOM2D_SMOKE_H
#define DOOM2D_SMOKE_H

#include "glob.h"

void SMK_savegame(int h);

void SMK_loadgame(int h);

void SMK_init(void);

void SMK_alloc(void);

void SMK_act(void);

void SMK_draw(void);

void SMK_add(int x, int y, int xv, int yv, byte t, byte s, short o);

void SMK_gas(int x0, int y0, int xr, int yr, int xv, int yv, int k);

void SMK_flame(int x0, int y0, int ox, int oy, int xr, int yr, int xv, int yv, int k, int o);

#endif //DOOM2D_SMOKE_H
