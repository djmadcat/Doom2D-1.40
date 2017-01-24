#ifndef DOOM2D_GAME_H
#define DOOM2D_GAME_H

#include "player.h"

enum {
    GS_TITLE,
    GS_GAME,
    GS_INTER,
    GS_DARKEN,
    GS_ENDANIM,
    GS_END2ANIM,
    GS_ENDSCR,
    GS_BVIDEO,
    GS_EVIDEO,
    GS_END3ANIM
};

void G_savegame(int h);

void G_loadgame(int h);

int G_load(int h);

void load_game(int n);

void G_start(void);

void G_init(void);

void G_act(void);

void G_draw(void);

void G_respawn_player(player_t *p);

extern byte _2pl;
extern byte g_dm;
extern byte g_bot;
extern byte g_st;
extern byte g_exit;
// next level (map) number
extern byte g_map;
// custom first level (map) number
extern byte _warp;
// current music name
extern char g_music[8];
extern dword g_time;

extern int dm_pnum;
extern int dm_pl1p, dm_pl2p;
extern pos_t dm_pos[100];

extern void *ltn[2][2];
extern int lt_time, lt_type, lt_side, lt_ypos, lt_force;

#endif //DOOM2D_GAME_H
