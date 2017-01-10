#ifndef DOOM2D_SOUND_H
#define DOOM2D_SOUND_H

#include "snddrv.h"

typedef struct {
    // length (in bytes)
    unsigned long len;
    // frequency (in Hz)
    unsigned long rate;
    // loop start position from data start (in bytes)
    unsigned long lstart;
    // loop length (in bytes)
    unsigned long llen;
} snd_t;

short S_play(snd_t *s, short c, unsigned r, short v);

void S_stop(short c);

void S_setrate(short c, unsigned r);

void S_setvolume(short c, int v);

void S_startmusic(void);

void S_stopmusic(void);

void S_init(void);

void S_done(void);

short S_detect(void);

char *S_getinfo(void);

extern snd_drv_f snd_drv;

extern unsigned short sfreq;

#endif //DOOM2D_SOUND_H
