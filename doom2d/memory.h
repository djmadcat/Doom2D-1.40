#ifndef DOOM2D_MEMORY_H
#define DOOM2D_MEMORY_H

void M_startup(void);

void M_shutdown(void);

void *M_lock(int h);

void M_unlock(void *p);

#endif //DOOM2D_MEMORY_H
