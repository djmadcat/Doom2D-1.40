#ifndef DOOM2D_VIEW_H
#define DOOM2D_VIEW_H

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

void W_savegame(int h);

void W_loadgame(int h);

void W_adjust(void);

void W_draw(void);

void W_init(void);

void W_act(void);

int W_load(int h);

#endif //DOOM2D_VIEW_H
