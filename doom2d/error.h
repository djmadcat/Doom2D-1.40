#ifndef DOOM2D_ERROR_H
#define DOOM2D_ERROR_H

void close_all(void);

void ERR_failinit(const char *s, ...);

void ERR_fatal(const char *s, ...);

void ERR_quit(void);

#endif //DOOM2D_ERROR_H
