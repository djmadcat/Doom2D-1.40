#include <unistd.h>
#include <stdlib.h>
#include "smoke.h"
#include "miscc.h"
#include "dos_bp.h"
#include "fx.h"
#include "libs/vga.h"
#include "smoka.h"
#include "monster.h"
#include "game.h"

#define MAXSR 20

#define SMSN 10
#define FLSN 8

static smoke_t sm[MAXSMOK];
static int sr_r;
static int sxr[MAXSR], syr[MAXSR];
static int lsm;

static void *spr[SMSN];
static void *fspr[FLSN];
static void *burnsnd;
static int burntm = 0;

void SMK_savegame(int h) {
    int i;
    int n;

    for (i = n = 0; i < MAXSMOK; ++i) {
        if (sm[i].t) {
            ++n;
        }
    }
    write(h, &n, 4);
    for (i = 0; i < MAXSMOK; ++i) {
        if (sm[i].t) {
            write(h, &sm[i], sizeof(sm[0]));
        }
    }
}

void SMK_loadgame(int h) {
    int n;

    read(h, &n, 4);
    read(h, sm, n * sizeof(sm[0]));
}

void SMK_init(void) {
    int i;

    for (i = 0; i < MAXSMOK; ++i) {
        sm[i].t = 0;
    }
    lsm = 0;
    burntm = 0;
}

void SMK_alloc(void) {
    int i;

    burnsnd = Z_getsnd("BURN");
    for (i = 0; i < SMSN; ++i) {
        spr[i] = Z_getspr("SMOK", i, 0, NULL);
    }
    for (i = 0; i < FLSN; ++i) {
        fspr[i] = Z_getspr("FLAM", i, 0, NULL);
    }
    for (i = 0; i < MAXSR; ++i) {
        sxr[i] = d2random(256 * 2 + 1) - 256;
        syr[i] = d2random(256 * 2 + 1) - 256;
    }
    sr_r = 0;
}

static void inclast(void) {
    if (++lsm >= MAXSMOK) {
        lsm = 0;
    }
}

void SMK_act(void) {
    int i;
    int ox, oy;
    static obj_t o;

    if (burntm) {
        --burntm;
    }
    for (i = 0; i < MAXSMOK; ++i) {
        if (sm[i].t) {
            if (sm[i].s) {
                ox = sm[i].x;
                oy = sm[i].y;
                sm[i].xv = Z_dec(sm[i].xv, 20);
                sm[i].yv = Z_dec(sm[i].yv, 20);
                sm[i].x += sm[i].xv / 2;
                sm[i].y += sm[i].yv / 2;
                if (!Z_canfit(sm[i].x >> 8, (sm[i].y >> 8) + 3, 3, 7)) {
                    sm[i].x = ox;
                    sm[i].y = oy;
                } else if (Z_inwater(sm[i].x >> 8, (sm[i].y >> 8) + 3, 3, 7)) {
                    sm[i].x = ox;
                    sm[i].y = oy;
                }
                ox = sm[i].x;
                oy = sm[i].y;
                sm[i].x += sm[i].xv / 2;
                sm[i].y += sm[i].yv / 2;
                if (!Z_canfit(sm[i].x >> 8, (sm[i].y >> 8) + 3, 3, 7)) {
                    sm[i].x = ox;
                    sm[i].y = oy;
                } else if (Z_inwater(sm[i].x >> 8, (sm[i].y >> 8) + 3, 3, 7)) {
                    sm[i].x = ox;
                    sm[i].y = oy;
                }
                if (sm[i].o != -3) {
                    o.x = sm[i].x >> 8;
                    o.y = sm[i].y >> 8;
                    o.xv = sm[i].xv >> 10;
                    o.yv = sm[i].yv >> 10;
                    o.vx = o.vy = 0;
                    if (!(g_time & 3)) {
                        Z_hit(&o, 1, sm[i].o, HIT_FLAME);
                    }
                }
            } else {
                ox = sm[i].x;
                oy = sm[i].y;
                sm[i].xv = Z_dec(sm[i].xv, 20);
                sm[i].yv = Z_dec(sm[i].yv, 20);
                sm[i].x += sm[i].xv;
                sm[i].y += sm[i].yv;
                if (!Z_canfit(sm[i].x >> 8, (sm[i].y >> 8) + 3, 3, 7)) {
                    sm[i].x = ox;
                    sm[i].y = oy;
                } else if (Z_inwater(sm[i].x >> 8, (sm[i].y >> 8) + 3, 3, 7)) {
                    sm[i].x = ox;
                    sm[i].y = oy;
                }
            }
            --sm[i].t;
        }
    }
}

void SMK_draw(void) {
    int i;
    int s;

    for (i = 0; i < MAXSMOK; ++i) {
        if (sm[i].t) {
            switch (sm[i].s) {
                case 0:
                    if ((s = sm[i].t) >= (SMSN - 1) * 3) {
                        s = 0;
                    } else {
                        s = SMSN - 1 - s / 3;
                    }
                    V_sprf((sm[i].x >> 8) - w_x + 100, (sm[i].y >> 8) - w_y + HT / 2 + 1 + w_o, spr[s], smoke_sprf);
                    break;
                case 1:
                    if ((s = sm[i].t) >= (FLSN - 1)) {
                        s = 0;
                    } else {
                        s = FLSN - 1 - s;
                    }
                    V_sprf((sm[i].x >> 8) - w_x + 100, (sm[i].y >> 8) - w_y + HT / 2 + 1 + w_o, fspr[s], flame_sprf);
                    break;
            }
        }
    }
}

void SMK_add(int x, int y, int xv, int yv, byte t, byte s, short o) {
    int i;

    if (!Z_canfit(x >> 8, (y >> 8) + 3, 3, 7)) {
        return;
    }
    if (Z_inwater(x >> 8, (y >> 8) + 3, 3, 7)) {
        FX_bubble(x >> 8, y >> 8, xv, yv, 1);
        return;
    }
    i = lsm;
    sm[i].x = x;
    sm[i].y = y;
    sm[i].xv = xv;
    sm[i].yv = yv;
    sm[i].t = t;
    sm[i].s = s;
    sm[i].o = o;
    inclast();
}

void SMK_gas(int x0, int y0, int xr, int yr, int xv, int yv, int k) {
    int i, x, y;
    static int sxv, syv;

    xv = -xv;
    yv = -yv;
    sxv = xv * k;
    syv = yv * k;
    k = max(abs(xv), abs(yv));
    if (!k) {
        return;
    }
    for (i = 0; i <= k; i += 3) {
        x = ((xv * i / k + x0) << 8) + sxr[sr_r] * xr;
        y = ((yv * i / k + y0) << 8) + syr[sr_r] * yr;
        if (++sr_r >= MAXSR) {
            sr_r = 0;
        }
        SMK_add(x, y, sxv, syv, SMSN * 3, 0, -3);
    }
}

void SMK_flame(int x0, int y0, int ox, int oy, int xr, int yr, int xv, int yv, int k, int o) {
    int i, x, y;
    static int sxv, syv;

    sxv = xv * k;
    syv = yv * k;
    xv = xv - (ox << 8);
    yv = yv - (oy << 8);
    k = max(abs(xv), abs(yv));
    if (!k) {
        return;
    }
    if (!burntm) {
        burntm = Z_sound(burnsnd, 128);
    }
    for (i = 0; i <= k; i += 200) {
        x = xv * i / k + (x0 << 8) + sxr[sr_r] * xr;
        y = yv * i / k + (y0 << 8) + syr[sr_r] * yr;
        if (++sr_r >= MAXSR) {
            sr_r = 0;
        }
        SMK_add(x, y, sxv, syv, FLSN, 1, o);
    }
}
