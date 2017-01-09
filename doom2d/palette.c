#include "palette.h"
#include "libs/vga.h"

int gamma = 0;

byte std_pal[256][3];
byte main_pal[256][3];
byte mixmap[256][256];
byte clrmap[256 * 12];
byte bright[256];
byte gamcor[5][64];

void setgamma(int g) {
    int t;

    if (g > 4) {
        g = 4;
    }
    if (g < 0) {
        g = 0;
    }
    gamma = g;
    for (t = 0; t < 256; ++t) {
        std_pal[t][0] = gamcor[gamma][main_pal[t][0]];
        std_pal[t][1] = gamcor[gamma][main_pal[t][1]];
        std_pal[t][2] = gamcor[gamma][main_pal[t][2]];
    }
    VP_setall(std_pal);
}
