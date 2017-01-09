#include "glob.h"
#include "view.h"

#ifndef DOOM2D_PLAYER_H
#define DOOM2D_PLAYER_H

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

extern player_t pl1;
extern player_t pl2;

#endif //DOOM2D_PLAYER_H
