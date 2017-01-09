#ifndef DOOM2D_HARDERR_H
#define DOOM2D_HARDERR_H

typedef int (* harderr_f)(int error, int drive, int flags);

enum {
    HARDERR_IGNORE = 0,
    HARDERR_RETRY,
    HARDERR_ABORT,
    HARDERR_FAIL
};

void harderr_inst(harderr_f f);

#endif //DOOM2D_HARDERR_H
