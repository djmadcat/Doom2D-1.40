#ifndef DOOM2D_SWITCH_H
#define DOOM2D_SWITCH_H

#include "view.h"
#include "glob.h"

void SW_savegame(int h);

void SW_loadgame(int h);

int SW_load(int h);

void SW_alloc(void);

void SW_init(void);

void Z_water_trap(obj_t *o);

void Z_untrap(byte t);

void SW_act(void);

void SW_cheat_open(void);

int SW_press(int x, int y, int r, int h, byte t, int o);

#endif //DOOM2D_SWITCH_H
