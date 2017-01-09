#ifndef DOOM2D_KEYB_H
#define DOOM2D_KEYB_H

typedef void (* key_f)(int k, int pressed);

void K_init(void);

void K_done(void);

void def_key_proc(int k, int pressed);

void K_setkeyproc(key_f f);

key_f K_getkeyproc();

// Keys array
// non-zero – pressed
extern char volatile keys[256];

#endif //DOOM2D_KEYB_H
