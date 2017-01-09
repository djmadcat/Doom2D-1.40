#include "terminal.h"
#include <stdarg.h>
#include <stdio.h>
#include "misca.h"

void logo(const char *s, ...) {
    va_list ap;
    int x, y;

    va_start(ap, s);
    vprintf(s, ap);
    va_end(ap);
    fflush(stdout);
    x = wherex();
    y = wherey();
    gotoxy(1, 1);
    putcn(' ', 0x4F, 80);
    gotoxy(31, 1);
    cputstr("Doom2D версия 1.40");
    gotoxy(x, y);
}

void logo_gas(int cur, int all) {
    int x, y, n, i;

    x = wherex();
    y = wherey();
    n = (78 - x) * cur / all + x;
    cputch('[');
    for (i = x; i < n; ++i) {
        cputch('.');
    }
    for (; i < 78; ++i) {
        cputch(' ');
    }
    cputch(']');
    gotoxy(x, y);
}
