#include "keyb.h"

char volatile keys[256];

key_f key_proc = def_key_proc;

void K_init(void) {
}

void K_done(void) {
}

void def_key_proc(int k, int pressed) {
}

void K_setkeyproc(key_f f) {
    key_proc = f;
}

key_f K_getkeyproc() {
    return key_proc;
}
