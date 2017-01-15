#ifndef DOOM2D_MONSTER_H
#define DOOM2D_MONSTER_H

#include "glob.h"
#include "view.h"

#define MAXMN 200

enum {
    MN_NONE,
    MN_DEMON,
    MN_IMP,
    MN_ZOMBY,
    MN_SERG,
    MN_CYBER,
    MN_CGUN,
    MN_BARON,
    MN_KNIGHT,
    MN_CACO,
    MN_SOUL,
    MN_PAIN,
    MN_SPIDER,
    MN_BSP,
    MN_MANCUB,
    MN_SKEL,
    MN_VILE,
    MN_FISH,
    MN_BARREL,
    MN_ROBO,
    MN_MAN,
    MN__LAST,
    MN_PL_DEAD = 100,
    MN_PL_MESS
};

typedef struct {
    obj_t o;
    byte t, d, st, ftime;
    int fobj;
    int s;
    char *ap;
    int aim, life, pain, ac, tx, ty, ammo;
    short atm;
} mn_t;

typedef struct {
    int r, h, l, mp, rv, jv, sp, minp;
} mnsz_t;

void MN_savegame(int h);

void MN_loadgame(int h);

void MN_alloc(void);

void MN_init(void);

int MN_spawn(int x, int y, byte d, int t);

int MN_spawn_deadpl(obj_t *o, byte c, int t);

int Z_getobjpos(int i, obj_t *o);

void MN_act(void);

void MN_mark(void);

void MN_draw(void);

int Z_gunhit(int x, int y, int o, int xv, int yv);

int Z_hit(obj_t *o, int d, int own, int t);

void MN_killedp(void);

int Z_hitobj(int obj, int d, int own, int t);

void Z_explode(int x, int y, int rad, int own);

void Z_bfg9000(int x, int y, int own);

int Z_chktrap(int t, int d, int o, int ht);

void Z_teleobj(int o, int x, int y);

mn_t *MN_get(int i);

#endif //DOOM2D_MONSTER_H
