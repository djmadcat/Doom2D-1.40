#include "glob.h"

#ifndef DOOM2D_PALETTE_H
#define DOOM2D_PALETTE_H

void setgamma(int g);

extern int gamma;

extern byte std_pal[256][3];
extern byte main_pal[256][3];
extern byte mixmap[256][256];
extern byte clrmap[256 * 12];
extern byte bright[256];

#endif //DOOM2D_PALETTE_H
