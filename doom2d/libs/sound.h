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

// sound volume (0–128)
extern short snd_vol;
// music volume (0–128)
extern short mus_vol;
// sound interpolation (0 – disabled, else enabled)
// better quality, but slower if enabled
extern char s_interp;

extern unsigned short snd_port;
extern unsigned short snd_dma;
extern unsigned short snd_irq;

extern unsigned short sfreq;

#endif //DOOM2D_SOUND_H
