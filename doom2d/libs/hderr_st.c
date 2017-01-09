#include "harderr.h"

static harderr_f hptr;

void harderr_inst(harderr_f f) {
    hptr = f;
}
