#ifndef DOOM2D_BMAP_H
#define DOOM2D_BMAP_H

#include "glob.h"
#include "view.h"

#define BM_WALL        1
#define BM_PLR1        2
#define BM_PLR2        4
#define BM_MONSTER     8

void BM_mark(obj_t *o, byte f);

extern byte bmap[FLDH / 4][FLDW / 4];
extern byte fld_need_remap;

#endif //DOOM2D_BMAP_H
