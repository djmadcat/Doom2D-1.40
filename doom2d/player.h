#ifndef DOOM2D_PLAYER_H
#define DOOM2D_PLAYER_H

#include "glob.h"
#include "view.h"

typedef struct {
    obj_t o;
    int looky;
    int st;
    int s;
    int life;
    int armor;
    int hit;
    int hito;
    int pain;
    int air;
    int invl;
    int suit;
    char d;
    // keys: up, down, left, right, fire, jump, ?, ?, ?
    byte ku, kd, kl, kr, kf, kj, kwl, kwr, kp;
    // statistics?
    int frag, ammo, shel, rock, cell, fuel, kills, secrets;
    byte fire, cwpn, csnd;
    byte amul;
    word wpns;
    char wpn;
    byte f;
    byte drawst;
    byte color;
    int id;
    byte keys;
    char lives;
} player_t;

void PL_savegame(int h);

void PL_loadgame(int h);

int PL_isdead(player_t *p);

void PL_init(void);

void PL_alloc(void);

void PL_restore(player_t *p);

void PL_reset(void);

void PL_spawn(player_t *p, int x, int y, char d);

int PL_hit(player_t *p, int d, int o, int t);

obj_t *PL_item_pos(player_t *p);

void PL_unknown_proc(player_t *p);

void PL_damage(player_t *p);

void PL_cry(player_t *p);

void PL_act(player_t *p);

void PL_draw(player_t *p);

void *PL_getspr(int s, int d);

void bfg_fly(int x, int y, int o);

void PL_drawst(player_t *p);

extern player_t pl1;
extern player_t pl2;

#endif //DOOM2D_PLAYER_H
