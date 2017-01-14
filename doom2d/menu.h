#ifndef DOOM2D_MENU_H
#define DOOM2D_MENU_H

#include "glob.h"

typedef struct {
    byte type;
    int n;
    int cur;
    int x;
    char *ttl;
    char **m;
    byte *t;
} menu_t;

void GMV_stop(void);

void GMV_say(const char *nm);

void G_code(void);

int GM_act(void);

void GM_init(void);

int GM_draw(void);

#endif //DOOM2D_MENU_H
