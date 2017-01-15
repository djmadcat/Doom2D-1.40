#include "game.h"

byte _2pl = 0;
byte g_dm = 0;
byte g_exit = 0;
byte _warp = 0;
dword g_time;

int dm_pnum;
int dm_pl1p, dm_pl2p;
pos_t dm_pos[100];

void *ltn[2][2];
int lt_time, lt_type, lt_side, lt_ypos, lt_force;

static void set_trans(int st) {
}

void G_savegame(int h) {
}

void G_loadgame(int h) {
}

int G_load(int h) {
    return 0;
}

static void load_game(int n) {
}

void G_start(void) {
}

void G_init(void) {
}

int G_beg_video(void) {
    return 0;
}

int G_end_video(void) {
    return 0;
}

void G_act(void) {
}

static void drawview(player_t *p) {
}

static int get_pu_st(int t) {
    return 0;
}

static void pl_info(player_t *p, int y) {
}

void G_draw(void) {
}

void G_respawn_player(player_t *p) {
}
