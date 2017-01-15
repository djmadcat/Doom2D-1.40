#ifndef DOOM2D_SWITCH_H
#define DOOM2D_SWITCH_H

#include "view.h"
#include "glob.h"

#define MAXSW 100

enum {
    SW_NONE,
    SW_EXIT,
    SW_EXITS,
    SW_OPENDOOR,
    SW_SHUTDOOR,
    SW_SHUTTRAP,
    SW_DOOR,
    SW_DOOR5,
    SW_PRESS,
    SW_TELE,
    SW_SECRET,
    SW_LIFTUP,
    SW_LIFTDOWN,
    SW_TRAP,
    SW_LIFT
};

typedef struct {
    byte x, y;
    byte t, tm;
    byte a, b, c, d;
    byte f;
} sw_t;

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
