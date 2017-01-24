#ifndef DOOM2D_FILES_H
#define DOOM2D_FILES_H

#include "glob.h"
#include "map.h"

#define MAX_WADS 20
#define MAX_WAD 2000

typedef struct {
    int o;
    int l;
    char n[8];
} wad_t;

typedef struct {
    int o;
    int l;
    char n[8];
    int f;
} mwad_t;

void F_startup(void);

void F_getsavnames(void);

void F_savegame(int n, const char *s);

void F_loadgame(int n);

void F_set_snddrv(void);

void F_addwad(const char *fn);

void F_initwads(void);

void F_allocres(void);

void F_loadres(int r, void *p, dword o, dword l);

void F_saveres(int r, const void *p, dword o, dword l);

int F_getresid(const char *n);

int F_findres(const char *n);

void F_getresname(char *n, int r);

int F_getsprid(const char *n, int s, int d);

int F_getreslen(int r);

void F_nextmus(char *s);

void F_readstr(int h, char *s, int m);

void F_readstrz(int h, char *s, int m);

void F_loadmap(const char *n);

void F_freemus(void);

void F_loadmus(const char *n);

extern char savname[7][24];
extern char savok[7];

extern int d_start, d_end;
extern int m_start, m_end;
extern int s_start, s_end;

extern mwad_t wad[MAX_WAD];

extern map_block_t blk;

#endif //DOOM2D_FILES_H
