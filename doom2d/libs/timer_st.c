#include "timer.h"

typedef void (* timer_f)();

void def_timeproc(void);


volatile int timer;

timer_f time_proc = def_timeproc;


void def_timeproc(void) {
}

void T_set_timeproc(int f, timer_f *p) {
}

void T_init(void) {
}

void T_done(void) {
}
