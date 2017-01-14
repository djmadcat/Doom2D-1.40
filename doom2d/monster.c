#include <stddef.h>
#include "monster.h"

void MN_savegame(int h) {
}

void MN_loadgame(int h) {
}

void MN_alloc(void) {
}

void MN_init(void) {
}

static void setst(int i, int st) {
}

int MN_spawn(int x, int y, byte d, int t) {
    return 0;
}

int MN_spawn_deadpl(obj_t *o, byte c, int t) {
    return 0;
}

static int isfriend(int a, int b) {
    return 0;
}

static int MN_findnewprey(int i) {
    return 0;
}

int Z_getobjpos(int i, obj_t *o) {
    return 0;
}

static void *wakeupsnd(int t) {
    return NULL;
}

static void *dthsnd(int t) {
    return NULL;
}

static int canshoot(int t) {
    return 0;
}

static int shoot(int i, obj_t *o, int n) {
    return 0;
}

static int kick(int i, obj_t *o) {
    return 0;
}

static int iscorpse(obj_t *o, int n) {
    return 0;
}

void MN_act(void) {
}

void MN_mark(void) {
}

void MN_draw(void) {
}

static int MN_hit(int n, int d, int o, int t) {
    return 0;
}

static void goodsnd(void) {
}

int Z_gunhit(int x, int y, int o, int xv, int yv) {
    return 0;
}

void MN_killedp(void) {
}

int Z_hitobj(int obj, int d, int own, int t) {
    return 0;
}

void Z_explode(int x, int y, int rad, int own) {
}

void Z_bfg9000(int x, int y, int own) {
}

int Z_chktrap(int t, int d, int o, int ht) {
    return 0;
}

void Z_teleobj(int o, int x, int y) {
}

void MN_warning(int l, int t, int r, int b) {
}

mn_t *MN_get(int i) {
    return NULL;
}
