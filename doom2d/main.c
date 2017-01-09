#include <stdlib.h>
#include "palette.h"
#include "player.h"
#include "misca.h"
#include "terminal.h"
#include "files.h"
#include "config.h"
#include "memory.h"
#include "game.h"
#include "menu.h"
#include "error.h"
#include "libs/keyb.h"
#include "libs/timer.h"
#include "libs/sound.h"
#include "libs/harderr.h"
#include "libs/vga.h"

int mem_chk_sz = 0;
byte fastdraw = 0;

int harderr_handler(int f, int d, int e) {
    if (!(keys[1] || keys[0x44])) {
        return HARDERR_RETRY;
    }
    if (keys[1]) {
        return HARDERR_FAIL;
    }
    close_all();
    return HARDERR_ABORT;
}

int main(void) {
    int i;

    pl1.ku = 0x48;
    pl1.kd = 0x50;
    pl1.kl = 0x4B;
    pl1.kr = 0x4D;
    pl1.kf = 0xB8;
    pl1.kj = 0x9D;
    pl1.kwl = 0x47;
    pl1.kwr = 0x49;
    pl1.kp = 0x36;
    pl1.id = -1;

    pl2.ku = 0x11;
    pl2.kd = 0x1F;
    pl2.kl = 0x1E;
    pl2.kr = 0x20;
    pl2.kf = 0x3A;
    pl2.kj = 0x0F;
    pl2.kwl = 0x10;
    pl2.kwr = 0x12;
    pl2.kp = 0x2A;
    pl2.id = -2;

    textmode();
    gotoxy(1, 2);
    randomize();

    F_startup();
    F_addwad("DOOM2D.WAD");
    CFG_args();
    CFG_load();
    F_initwads();
    F_set_snddrv();
    if (mem_chk_sz) {
        logo("** захапывается %dK памяти...", mem_chk_sz);
        logo("%s\n", (malloc(mem_chk_sz << 10)) ? "OK" : "ОШИБКА");
    }
    M_startup();
    F_allocres();
    F_loadres(F_getresid("PLAYPAL"), main_pal, 0, sizeof(main_pal));
    for (i = 0; i < sizeof(bright); ++i) {
        bright[i] = ((int) main_pal[i][0] + main_pal[i][1] + main_pal[i][2]) * 8 / (63 * 3);
    }
    F_loadres(F_getresid("MIXMAP"), mixmap, 0, sizeof(mixmap));
    F_loadres(F_getresid("COLORMAP"), clrmap, 0, sizeof(clrmap));
    G_init();
    logo("  свободно DPMI-памяти: %uK\n", dpmi_memavl() >> 10);
    logo("K_init: настройка клавиатуры\n");
    K_slow();
    K_init();
    logo("T_init: настройка таймера\n");
    T_init();
    logo("S_init: настройка звука\n");
    S_init();
    logo("V_init: настройка видео\n");
    if (V_init() != 0) {
        ERR_failinit("Не могу установить видеорежим VGA");
    }
    setgamma(gamma);
    V_setscr(scrbuf);
    harderr_inst(harderr_handler);
    GM_init();
    F_loadmus("MENU");
    S_startmusic();

    for (;;) {
        timer = 0;
        G_act();
        if (fastdraw) {
            G_act();
        }
        G_draw();
        if (fastdraw) {
            while (timer < 0x1FFFE) {
            }
        } else {
            while (timer < 0xFFFF) {
            }
        }
    }

    return 0;
}
