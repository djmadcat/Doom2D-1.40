#include "player.h"

#ifndef DOOM2D_GAME_H
#define DOOM2D_GAME_H

void G_savegame(int h);

void G_loadgame(int h);

int G_load(int h);

void G_start(void);

void G_init(void);

void G_act(void);

void G_draw(void);

void G_respawn_player(player_t *p);

#endif //DOOM2D_GAME_H
