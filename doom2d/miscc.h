#ifndef DOOM2D_MISCC_H
#define DOOM2D_MISCC_H

#include "glob.h"
#include "view.h"

enum {
    Z_HITWALL = 1,
    Z_HITCEIL = 2,
    Z_HITLAND = 4,
    Z_FALLOUT = 8,
    Z_INWATER = 16,
    Z_HITWATER = 32,
    Z_HITAIR = 64,
    Z_BLOCK = 128
};

int Z_sign(int a);

int Z_dec(int a, int b);

void *Z_getspr(const char *n, int s, int d, char *dir);

void *Z_getsnd(char *n);

int Z_sound(void *s, int v);

void Z_initst(void);

void Z_putbfch(int c);

void Z_putsfch(int c);

void Z_gotoxy(int x, int y);

void Z_printbf(const char *s, ...);

void Z_printsf(const char *s, ...);

void Z_drawspr(int x, int y, void *p, char d);

void Z_clrst(void);

void Z_drawstlives(char n);

void Z_drawstkeys(byte k);

void Z_drawstair(int a);

void Z_drawstprcnt(int y, int n);

void Z_drawstnum(int n);

void Z_drawstwpn(int n, int a);

void Z_drawmanspr(int x, int y, void *p, char d, byte color);

int Z_canstand(int x, int y, int r);

int Z_hitceil(int x, int y, int r, int h);

int Z_canfit(int x, int y, int r, int h);

int Z_inlift(int x, int y, int r, int h);

int Z_isblocked(int x, int y, int r, int h, int xv);

int Z_istrapped(int x, int y, int r, int h);

void Z_set_speed(obj_t *o, int s);

int Z_inwater(int x, int y, int r, int h);

int Z_getacid(int x, int y, int r, int h);

int Z_canbreathe(int x, int y, int r, int h);

int Z_overlap(obj_t *a, obj_t *b);

int Z_cansee(int x, int y, int xd, int yd);

int Z_look(obj_t *a, obj_t *b, int d);

int Z_moveobj(obj_t *p);

void Z_splash(obj_t *p, int n);

#endif //DOOM2D_MISCC_H
