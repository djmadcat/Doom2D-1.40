#include <stddef.h>
#include "miscc.h"

byte z_dot = 0;

int Z_sign(int a) {
    return 0;
}

int Z_dec(int a, int b) {
    return 0;
}

void *Z_getspr(const char *n, int s, int d, char *dir) {
    return NULL;
}

void *Z_getsnd(char *n) {
    return NULL;
}

int Z_sound(void *s, int v) {
    return 0;
}

void Z_initst(void) {
}

void Z_putbfch(int c) {
}

void Z_putsfch(int c) {
}

void Z_gotoxy(int x, int y) {
}

void Z_printbf(const char *s, ...) {
}

void Z_printsf(const char *s, ...) {
}

void Z_drawspr(int x, int y, void *p, char d) {
}

void Z_clrst(void) {
}

void Z_drawstlives(char n) {
}

void Z_drawstkeys(byte k) {
}

void Z_drawstair(int a) {
}

void Z_drawstprcnt(int y, int n) {
}

void Z_drawstnum(int n) {
}

void Z_drawstwpn(int n, int a) {
}

void Z_drawmanspr(int x, int y, void *p, char d, byte color) {
}

int Z_canstand(int x, int y, int r) {
    return 0;
}

int Z_hitceil(int x, int y, int r, int h) {
    return 0;
}

int Z_canfit(int x, int y, int r, int h) {
    return 0;
}

int Z_inlift(int x, int y, int r, int h) {
    return 0;
}

int Z_isblocked(int x, int y, int r, int h, int xv) {
    return 0;
}

int Z_istrapped(int x, int y, int r, int h) {
    return 0;
}

void Z_set_speed(obj_t *o, int s) {
}

int Z_inwater(int x, int y, int r, int h) {
    return 0;
}

int Z_getacid(int x, int y, int r, int h) {
    return 0;
}

int Z_canbreathe(int x, int y, int r, int h) {
    return 0;
}

int Z_overlap(obj_t *a, obj_t *b) {
    return 0;
}

int Z_cansee(int x, int y, int xd, int yd) {
    return 0;
}

int Z_look(obj_t *a, obj_t *b, int d) {
    return 0;
}

int Z_moveobj(obj_t *p) {
    return 0;
}

void Z_splash(obj_t *p, int n) {
}
