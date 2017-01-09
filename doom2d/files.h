#include "glob.h"

#ifndef DOOM2D_FILES_H
#define DOOM2D_FILES_H

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

#endif //DOOM2D_FILES_H
