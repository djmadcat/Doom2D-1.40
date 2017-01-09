#ifndef DOOM2D_VGA_H
#define DOOM2D_VGA_H

typedef struct {
    // width
    unsigned short w;
    // height
    unsigned short h;
    // center offset x
    short sx;
    // center offset y
    short sy;
} vgaimg_t;

typedef void (* spr_f)(void);

// switch to "VGA 320x200, 256 colors" mode
// return 0 if OK
short V_init(void);

// switch to textmode
void V_done(void);

// draw dot
void V_dot(short x, short y, unsigned char color);

// draw picture `i`
void V_pic(short x, short y, vgaimg_t *i);

// draw sprite `i` overlayed? by color (suitable for shadows)
void V_spr1color(short x, short y, vgaimg_t *i, unsigned char color);

// draw sprite `i`
void V_spr(short x, short y, vgaimg_t *i);

// draw sprite with function
// AL – color
// EDI – screen
// !!! store all registers except EAX
// !!! EDI must be moved by one pixel to the right (INC EDI or STOSB)
void V_sprf(short x, short y, vgaimg_t *i, spr_f f);

// draw sprite `i` upside-down?
void V_spr2(short x, short y, vgaimg_t *i);

// clear rect `(x, y, w, h)` with `color`
void V_clr(short x, short w, short y, short h, unsigned char color);

// wait for the return of the blanked scanning beam (retrace, flyback)
void V_wait(void);

// get current palette to `p`
void VP_getall(void *p);

// set current palette to `p`
void VP_setall(void *p);

// set n colors starts from f from p array
void VP_set(void *p, short f, short n);

// fill current palette with color
void VP_fill(char r, char g, char b);

// bring palette p closer to (r, g, b) color on s/n
// result is in pal_tmp
void VP_tocolor(void *p, char r, char g, char b, char n, char s);

// bring palette p closer to palette p2 on s/n
// result is in pal_tmp
void VP_topal(void *p, void *p2, char n, char s);

// draw sprite i sized to (sx, sy)
void VM_spr(short x, short y, short sx, short sy, vgaimg_t *i);

// set output rect
void V_setrect(short x, short w, short y, short h);

// set screen buffer address
// NULL – real screen
void V_setscr(void *p);

// copy rect to screen
void V_copytoscr(short x, short w, short y, short h);

// virtual screen
extern unsigned char scrbuf[64000];

#endif //DOOM2D_VGA_H
