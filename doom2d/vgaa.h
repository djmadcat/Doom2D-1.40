#ifndef DOOM2D_VGAA_H
#define DOOM2D_VGAA_H

#include "glob.h"
#include "libs/vga.h"

void V_manspr(int x, int y, vgaimg_t *i, char c);

void V_manspr2(int x, int y, vgaimg_t *i, char c);

void V_remap_rect(int x, int w, int y, int h, byte *m);

void V_maptoscr(int x, int w, int y, int h, void *m);

#endif //DOOM2D_VGAA_H
