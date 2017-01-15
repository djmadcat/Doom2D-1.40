#ifndef DOOM2D_GAME_H
#define DOOM2D_GAME_H

#include "player.h"

void G_savegame(int h);

void G_loadgame(int h);

int G_load(int h);

void G_start(void);

void G_init(void);

void G_act(void);

void G_draw(void);

void G_respawn_player(player_t *p);

extern byte _2pl;
extern byte g_dm;
extern byte g_exit;
extern byte _warp;
extern dword g_time;

extern int dm_pnum;
extern int dm_pl1p, dm_pl2p;
extern pos_t dm_pos[100];

extern void *ltn[2][2];
extern int lt_time, lt_type, lt_side, lt_ypos, lt_force;

#endif //DOOM2D_GAME_H
