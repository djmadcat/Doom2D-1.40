#ifndef DOOM2D_MUSIC_H
#define DOOM2D_MUSIC_H

#include "glob.h"

// note
typedef struct {
    // note (24 – normal, lower – pitch down, upper – pitch up)
    byte n;
    // instrument (sample number)
    byte i;
    // volume (0 – 127)
    byte v;
    // duration
    byte d;
} dmv_t;

typedef struct {
    // identifier (['D', 'M', 'M', '\0'])
    char id[4];
    // version (0x0)
    byte ver;
    byte pat;
    word psz;
} dmm_t;

// instrument
typedef struct {
    // ?
    byte t;
    // name
    char n[13];
    // ?
    word r;
} dmi_t;

extern byte seq[255];
extern byte seqn;
extern dmv_t *pat;
dword *patp;
extern dmi_t **dmi;
// instruments count
extern int inum;

#endif //DOOM2D_MUSIC_H
