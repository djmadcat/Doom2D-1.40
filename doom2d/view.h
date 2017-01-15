#ifndef DOOM2D_VIEW_H
#define DOOM2D_VIEW_H

#include "glob.h"

typedef struct {
    // coordinates
    int x;
    int y;
    // velocity
    int xv;
    int yv;
    //
    int vx;
    int vy;
    // radius
    int r;
    // height
    int h;
} obj_t;

typedef struct {
    int x;
    int y;
    byte d;
} pos_t;

#define MAXWAL 256

// game field width in blocks
#define FLDW 100
// game field height in blocks
#define FLDH 100
// block width in pixels
#define CELW 8
// block height in pixels
#define CELH 8

#pragma pack(1)
typedef struct {
    char n[8];
    char t;
} wall_t;
#pragma pack()

void W_savegame(int h);

void W_loadgame(int h);

void W_adjust(void);

void W_draw(void);

void W_init(void);

void W_act(void);

int W_load(int h);

#endif //DOOM2D_VIEW_H
