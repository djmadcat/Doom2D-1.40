#include "sound.h"

unsigned short sfreq = 11025;

snd_drv_f snd_drv = __none_drv;

short S_play(snd_t *s, short c, unsigned r, short v) {
    return 0;
}

void S_stop(short c) {
}

void S_setrate(short c, unsigned r) {
}

void S_setvolume(short c, int v) {
}

static void getsample(void) {
}

static void playblk(void) {
}

static void playnext(void) {
}

void S_startmusic(void) {
}

void S_stopmusic(void) {
}

static void mapdma(void) {
}

static void timeproc(void) {
}

void S_init(void) {
}

void S_done(void) {
}

short S_detect(void) {
    return 0;
}

char *S_getinfo(void) {
    return "";
}
