#include <stddef.h>
#include "player.h"

byte p_immortal = 0;
byte p_fly = 0;

int PL_JUMP = 10;
int PL_RUN = 8;

player_t pl1;
player_t pl2;

static void *spr[27 * 2];
static void *wpn[11][6];
static int wytab[] = { -1, -2, -1, 0 };

void PL_savegame(int h) {
}

void PL_loadgame(int h) {
}

static int nonz(int a) {
    return 0;
}

static int firediry(player_t *p) {
    return 0;
}

static void fire(player_t *p) {
}

static void chgwpn(player_t *p) {
}

static void jump(player_t *p, int st) {
}

int PL_isdead(player_t *p) {
    return 0;
}

void PL_init(void) {
}

void PL_alloc(void) {
}

void PL_restore(player_t *p) {
}

void PL_reset(void) {
}

void PL_spawn(player_t *p, int x, int y, char d) {
}

int PL_hit(player_t *p, int d, int o, int t) {
    return 0;
}

obj_t *PL_item_pos(player_t *p) {
    return NULL;
}

void PL_unknown_proc(player_t *p) {
}

void PL_damage(player_t *p) {
}

void PL_cry(player_t *p) {
}

int PL_give(player_t *p, int t) {
    return 0;
}

void PL_act(player_t *p) {
}

static int standspr(player_t *p) {
    return 0;
}

static int wpnspr(player_t *p) {
    return 0;
}

void PL_draw(player_t *p) {
}

vgaimg_t *PL_getspr(int s, int d, vgaimg_t **i, int *wx, int *wy) {
    if (s > 'D') {
        // fire
        // EF - wait/shot
        *i = wpn[5][s == 'F'];
        *wx = 0;
        *wy = 0;
    } else {
        // walk
        *i = (vgaimg_t *)wpn[5][0];
        *wx = d ? 2 : -2;
        *wy = 1 + wytab[s - 'A'];
    }

    return spr[(s - 'A') * 2 + d];
}

static void chk_bfg(player_t *p, int x, int y) {
}

void bfg_fly(int x, int y, int o) {
}

void PL_drawst(player_t *p) {
}
