#include <stddef.h>
#include "player.h"
#include "game.h"
#include "libs/keyb.h"

byte p_immortal = 0;
byte p_fly = 0;

int PL_JUMP = 10;
int PL_RUN = 8;

player_t pl1;
player_t pl2;

static void *spr[27 * 2];
static void *wpn[11][6];
static int wytab[] = { -1, -2, -1, 0 };

int PL_actions(int n) {
    int result = 0;
    player_t *p;

    if (n == 0) {
        p = &pl1;
    } else if (n == 1) {
        p = &pl2;
    } else {
        return 0;
    }

    if (g_bot && n == 1) {
        //if (dword_45520) {
        //    result = (*(int (__cdecl **)(int, player_t *))(*(_DWORD *)dword_45520 + 4))(dword_45520, p);
        //} else {
        //    result = 0;
        //}
    } else {
        result = 0;
        if (keys[p->kl]) {
            result |= PLA_LEFT;
        }
        if (keys[p->kr]) {
            result |= PLA_RIGHT;
        }
        if (keys[p->ku]) {
            result |= PLA_UP;
        }
        if (keys[p->kd]) {
            result |= PLA_DOWN;
        }
        if (keys[p->kf]) {
            result |= PLA_FIRE;
        }
        if (keys[p->kj]) {
            result |= PLA_JUMP;
        }
        if (keys[p->kp]) {
            result |= PLA_PRESS;
        }
        if (keys[p->kwl]) {
            result |= PLA_PREV_WEAPON;
        }
        if (keys[p->kwr]) {
            result |= PLA_NEXT_WEAPON;
        }
    }

    return result;
}

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

void PL_act(player_t *p, int actions) {
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
