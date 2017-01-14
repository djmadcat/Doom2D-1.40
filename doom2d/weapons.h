#ifndef DOOM2D_WEAPONS_H
#define DOOM2D_WEAPONS_H

void WP_savegame(int h);

void WP_loadgame(int h);

void WP_alloc(void);

void WP_init(void);

void WP_act(void);

void WP_draw(void);

void WP_gun(int x, int y, int xd, int yd, int o, int v);

void WP_punch(int x, int y, int d, int own);

int WP_chainsaw(int x, int y, int d, int own);

void WP_rocket(int x, int y, int xd, int yd, int o);

void WP_revf(int x, int y, int xd, int yd, int o, int t);

void WP_plasma(int x, int y, int xd, int yd, int o);

void WP_ball1(int x, int y, int xd, int yd, int o);

void WP_ball2(int x, int y, int xd, int yd, int o);

void WP_ball7(int x, int y, int xd, int yd, int o);

void WP_aplasma(int x, int y, int xd, int yd, int o);

void WP_manfire(int x, int y, int xd, int yd, int o);

void WP_bfgshot(int x, int y, int xd, int yd, int o);

void WP_bfghit(int x, int y, int o);

void WP_pistol(int x, int y, int xd, int yd, int o);

void WP_mgun(int x, int y, int xd, int yd, int o);

void WP_shotgun(int x, int y, int xd, int yd, int o);

void WP_dshotgun(int x, int y, int xd, int yd, int o);

void WP_ognemet(int x, int y, int xd, int yd, int xv, int yv, int o);

#endif //DOOM2D_WEAPONS_H
