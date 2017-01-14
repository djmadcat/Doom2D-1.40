#ifndef DOOM2D_DOTS_H
#define DOOM2D_DOTS_H

#include "glob.h"

void DOT_savegame(int h);

void DOT_loadgame(int h);

void DOT_init(void);

void DOT_alloc(void);

void DOT_act(void);

void DOT_draw(void);

void DOT_add(int x, int y, char xv, char yv, byte c, byte t);

void DOT_blood(int x, int y, int xv, int yv, int n);

void DOT_spark(int x, int y, int xv, int yv, int n);

void DOT_water(int x, int y, int xv, int yv, int n, int c);

#endif //DOOM2D_DOTS_H