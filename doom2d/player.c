#include <stddef.h>
#include "player.h"

player_t pl1;
player_t pl2;

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

void *PL_getspr(int s, int d) {
    return NULL;
}

static void chk_bfg(player_t *p, int x, int y) {
}

void bfg_fly(int x, int y, int o) {
}

void PL_drawst(player_t *p) {
}
