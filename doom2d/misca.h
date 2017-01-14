#ifndef DOOM2D_MISC_H
#define DOOM2D_MISC_H

#include "glob.h"

void gotoxy(int x, int y);

int wherex(void);

int wherey(void);

void textmode(void);

void putcn(char c, char a, short n);

void cputstr(const char *s);

void cputch(char c);

void randomize(void);

void K_slow(void);

void K_fast(void);

dword dpmi_memavl(void);

#endif //DOOM2D_MISC_H
