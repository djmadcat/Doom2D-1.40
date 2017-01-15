#ifndef DOOM2D_CONFIG_H
#define DOOM2D_CONFIG_H

#include "glob.h"

typedef struct {
    char *par;
    char *cfg;
    void *p;
    byte t, o;
} cfg_t;

void CFG_args(void);

void CFG_load(void);

void CFG_save(void);

extern int mem_chk_sz;
extern byte fastdraw;

extern int snd_card;

#endif //DOOM2D_CONFIG_H
