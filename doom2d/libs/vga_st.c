#include "vga.h"

unsigned char scrbuf[V_SCR_WIDTH * V_SCR_HEIGHT];

unsigned char *scra;
short scrw, scrh, scrx, scry;

short V_init(void) {
    return 0;
}

void V_done(void) {
}

void V_dot(short x, short y, unsigned char color) {
}

void V_pic(short x, short y, vgaimg_t *i) {
}

void V_spr1color(short x, short y, vgaimg_t *i, unsigned char color) {
}

void V_spr(short x, short y, vgaimg_t *i) {
}

void V_sprf(short x, short y, vgaimg_t *i, spr_f f) {
}

void V_spr2(short x, short y, vgaimg_t *i) {
}

void V_clr(short x, short w, short y, short h, unsigned char color) {
}

void V_wait(void) {
}

void VP_getall(void *p) {
}

void VP_setall(void *p) {
}

void VP_set(void *p, short f, short n) {
}

void VP_fill(char r, char g, char b) {
}

void VP_tocolor(void *p, char r, char g, char b, char n, char s) {
}

void VP_topal(void *p, void *p2, char n, char s) {
}

void VM_spr(short x, short y, short sx, short sy, vgaimg_t *i) {
}

void V_setrect(short x, short w, short y, short h) {
}

void V_setscr(void *p) {
}

void V_copytoscr(short x, short w, short y, short h) {
}
