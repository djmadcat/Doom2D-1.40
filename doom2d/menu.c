#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "libs/sound.h"
#include "libs/timer.h"
#include "files.h"
#include "palette.h"
#include "libs/vga.h"
#include "game.h"
#include "config.h"
#include "miscc.h"
#include "switch.h"
#include "error.h"
#include "memory.h"
#include "libs/keyb.h"
#include "vgaa.h"

#define QSND_NUM 14

static byte panim[] =
    "BBDDAACCDDAA"
    "BBDDAACCDDAA"
    "BBDDAACCDDAA"
    "EEEE"
    "EFEFEFEFEFEFEFEFEFEFE"
    "EEEE";
static byte *panimp = panim;

// player colors
#define PCOLORN 10
byte pcolortab[PCOLORN] = {
    0x18, 0x20, 0x40, 0x58, 0x60, 0x70, 0x80, 0xB0, 0xC0, 0xD0
};
int p1color = 5, p2color = 4;

// save name buffer
static char ibuf[24];
// user input mode?
static byte input = 0;
// save name cursor index
static int icur;

// menu type
enum {
    MENU,
    MSG
};

// menu command (item)
enum {
    CANCEL,
    NEWGAME,
    LOADGAME,
    SAVEGAME,
    OPTIONS,
    QUITGAME,
    QUIT,
    ENDGAME,
    ENDGM,
    PLR1,
    PLR2,
    COOP,
    DM,
    BOT,
    VOLUME,
    GAMMA,
    LOAD,
    SAVE,
    PLCOLOR,
    PLCEND,
    MUSIC,
    INTERP,
    // sound volume minus
    SVOLM,
    // sound volume plus
    SVOLP,
    // music volume minus
    MVOLM,
    // music volume plus
    MVOLP,
    // gamma volume minus
    GAMMAM,
    // gamma volume plus
    GAMMAP,
    PL1CM,
    PL1CP,
    PL2CM,
    PL2CP
};

static int qsnd[QSND_NUM];

static char *main_txt[] = {
    "НОВАЯ ИГРА", "СТАРАЯ ИГРА", "СОХРАНИТЬ ИГРУ", "РАЗНОЕ", "ВЫХОД"
}, *opt_txt[] = {
    "НАЧАТЬ ЗАНОВО", "ГРОМКОСТЬ", "ЯРКОСТЬ", "МУЗЫКА", "ИНТЕРПОЛЯЦИЯ:"
}, *ngplr_txt[] = {
    "ОДИН ИГРОК", "ДВА ИГРОКА"
}, *ngdm_txt[] = {
    "COOPERATIVE", "DEATHMATCH", "BOTMATCH"
}, *vol_txt[] = {
    "ЗВУК", "МУЗЫКА"
}, *plcolor_txt[] = {
    "ПЕРВЫЙ", "ВТОРОЙ"
}, *gamma_txt[] = {
    ""
};

static byte main_typ[] = {
    NEWGAME, LOADGAME, SAVEGAME, OPTIONS, QUITGAME
}, ngplr_typ[] = {
    PLR1, PLR2
}, ngdm_typ[] = {
    COOP, DM, BOT
}, opt_typ[] = {
    ENDGAME, VOLUME, GAMMA, MUSIC, INTERP
}, quit_typ[] = {
    QUIT, CANCEL
}, endgm_typ[] = {
    ENDGM, CANCEL
}, vol_typ[] = {
    SVOLM, MVOLM
}, plcolor_typ[] = {
    PL1CM, PL2CM
}, gamma_typ[] = {
    GAMMAM
}, load_typ[] = {
    LOAD, LOAD, LOAD, LOAD, LOAD, LOAD, LOAD
}, save_typ[] = {
    SAVE, SAVE, SAVE, SAVE, SAVE, SAVE, SAVE
};

static menu_t main_mnu = {
    MENU, 5, 0, 80, "МЕНЮ", main_txt, main_typ
}, opt_mnu = {
    MENU, 5, 0, 75, "РАЗНОЕ", opt_txt, opt_typ
}, ngplr_mnu = {
    MENU, 2, 0, 90, "НОВАЯ ИГРА", ngplr_txt, ngplr_typ
}, ngdm_mnu = {
    MENU, 2, 0, 90, "ТИП ИГРЫ", ngdm_txt, ngdm_typ
}, vol_mnu = {
    MENU, 2, 0, 40, "ГРОМКОСТЬ", vol_txt, vol_typ
}, plcolor_mnu = {
    MENU, 2, 0, 90, "ЦВЕТ", plcolor_txt, plcolor_typ
}, gamma_mnu = {
    MENU, 1, 0, 85, "ЯРКОСТЬ", gamma_txt, gamma_typ
}, load_mnu = {
    MENU, 7, 0, 85, "ЗАГРУЗИТЬ ИГРУ", NULL, load_typ
}, save_mnu = {
    MENU, 7, 0, 85, "СОХРАНИТЬ ИГРУ", NULL, save_typ
}, quit1_msg = {
    MSG, 0, 0, 0, "ВЫ ДУМАЕТЕ, ОТСЮДА ТАК ПРОСТО ВЫЙТИ?", NULL, quit_typ
}, quit2_msg = {
    MSG, 0, 0, 0, "ХОРОШЕНЬКО ПОДУМАЙТЕ ПЕРЕД ТЕМ КАК ВЫЙТИ", NULL, quit_typ
}, quit3_msg = {
    MSG, 0, 0, 0, "У ВАС ЧТО, КОНЧИЛИСЬ ПАТРОНЫ?", NULL, quit_typ
}, endgm_msg = {
    MSG, 0, 0, 0, "НАЧАТЬ ЭТОТ УРОВЕНЬ ЗАНОВО?", NULL, endgm_typ
};

static menu_t *qmsg[3] = { &quit1_msg, &quit2_msg, &quit3_msg };

static menu_t *mnu = NULL;

static byte gm_redraw = 0;
static int gm_tm = 0;

static void *csnd1, *csnd2;
static void *msnd1, *msnd2, *msnd3, *msnd4, *msnd5, *msnd6;
static int movsndt = 0;

static vgaimg_t *msklh[2];
static vgaimg_t *mbarl, *mbarm, *mbarr, *mbaro;
static vgaimg_t *mslotl, *mslotm, *mslotr;

int lastkey = 0;
// pressed keys buffer (used for cheats)
static byte cbuf[32];

byte keychar[2][128] = {{
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0,
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\r', 0, 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', 0, 0, '\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
}, {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0,
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\r', 0, 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', 0, 0, '\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
}/*, {
    0, 0, '!', '\"', '#', '$', '%', ':', '&', '*', '(', ')', '_', '+', 0, 0,
    'Й', 'Ц', 'У', 'К', 'Е', 'Н', 'Г', 'Ш', 'Щ', 'З', 'Х', 'Ъ', '\r', 0, 'Ф', 'Ы',
    'В', 'А', 'П', 'Р', 'О', 'Л', 'Д', 'Ж', 'Э', 0, 0, 0, 'Я', 'Ч', 'С', 'М',
    'И', 'Т', 'Ь', 'Б', 'Ю', '?', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
}*/};

static snd_t *voc = NULL;
static int voc_ch = 0;

void GMV_stop(void) {
    if (voc) {
        if (voc_ch) {
            S_stop(voc_ch);
            voc_ch = 0;
        }
        free(voc);
        voc = NULL;
    }
}

void GMV_say(const char *nm) {
    int r;
    int len;
    snd_t *p;
    byte *d;

    if ((r = F_findres(nm)) == -1) {
        return;
    }
    if (!(p = malloc((len = F_getreslen(r)) + 16))) {
        return;
    }
    p->len = len;
    p->rate = 11000;
    p->lstart = p->llen = 0;
    GMV_stop();
    F_loadres(r, p + 1, 0, len);
    for (d = (byte *) (p + 1); len; --len, ++d) {
        *d ^= 128;
    }
    voc = p;
    voc_ch = S_play(voc, -1, 1024, 255);
}

void G_code(void) {
    void *s;

    s = csnd2;
    if (memcmp(cbuf + 32 - 5, "\x17\x20\x20\x10\x20", 5) == 0) {
        // "IDDQD" – kill players
        PL_hit(&pl1, 400, 0, HIT_SOME);
        if (_2pl) {
            PL_hit(&pl2, 400, 0, HIT_SOME);
        }
        s = csnd1;
    } else if (memcmp(cbuf + 32 - 4, "\x14\x1E\x31\x25", 4) == 0) {
        // "TANK" – full life and full armor
        pl1.life = pl1.armor = 200;
        pl1.drawst |= PL_DRAWARMOR | PL_DRAWLIFE;
        if (_2pl) {
            pl2.life = pl2.armor = 200;
            pl2.drawst |= PL_DRAWARMOR | PL_DRAWLIFE;
        }
    } else if (memcmp(cbuf + 32 - 8, "\x30\x16\x26\x26\x21\x13\x18\x22", 8) == 0) {
        // "BULLFROG" – 2x higher jump
        PL_JUMP = (PL_JUMP == 10) ? 20 : 10;
    } else if (memcmp(cbuf + 32 - 8, "\x21\x18\x13\x32\x16\x26\x1E\x02", 8) == 0) {
        // "FORMULA1" – 3x faster run
        PL_RUN = (PL_RUN == 8) ? 24 : 8;
    } else if (memcmp(cbuf + 32 - 5, "\x13\x1E\x32\x30\x18", 5) == 0) {
        // "RAMBO" – max ammo, all weapons, all keys
        pl1.ammo = pl1.shel = pl1.rock = pl1.cell = pl1.fuel = 30000;
        pl1.wpns = 0x7FF;
        pl1.drawst |= PL_DRAWWPN | PL_DRAWKEYS;
        pl1.keys = 0x70;
        if (_2pl) {
            pl2.ammo = pl2.shel = pl2.rock = pl2.cell = pl1.fuel = 30000;
            pl2.wpns = 0x7FF;
            pl2.drawst |= PL_DRAWWPN | PL_DRAWKEYS;
            pl2.keys = 0x70;
        }
    } else if (memcmp(cbuf + 32 - 5, "\x16\x24\x23\x14\x11", 5) == 0) {
        // "UJHTW" (ГОРЕЦ) – god mode
        p_immortal = !p_immortal;
    } else if (memcmp(cbuf + 32 - 9, "\x33\x14\x25\x1F\x10\x24\x23\x14\x25", 9) == 0) {
        // ",TKSQJHTK" (БЕЛЫЙОРЕЛ) – fly mode
        p_fly = !p_fly;
    } else if (memcmp(cbuf + 32 - 6, "\x2E\x30\x2F\x2E\x30\x2F", 6) == 0) {
        // "CBVCBV" (СИМСИМ) – open all doors
        SW_cheat_open();
    } else if (memcmp(cbuf + 32 - 7, "\x22\x18\x18\x20\x30\x15\x12", 7) == 0) {
        // "GOODBYE" – exit?
        g_exit = 1;
    } else if (memcmp(cbuf + 32 - 9, "\x22\x24\x17\x14\x25\x15\x21", 7) == 0) {
        // "GJITKYF" (ПОШЕЛНА) XX – goto level (map) number
        if (cbuf[30] >= 2 && cbuf[30] <= 11 && cbuf[31] >= 2 && cbuf[31] <= 11) {
            g_map = (cbuf[30] == 11) ? 0 : (cbuf[30] - 1) * 10;
            g_map += (cbuf[31] == 11) ? 0 : (cbuf[31] - 1);
            G_start();
        }
    } else {
        return;
    }
    memset(cbuf, 0, 32);
    Z_sound(s, 128);
}

void GM_set(menu_t *m) {
    mnu = m;
    gm_redraw = 1;
    if (g_st == GS_GAME) {
        V_setrect(0, 320, 0, 200);
        V_clr(0, 320, 0, 200, 0);
        if (_2pl) {
            V_setrect(200, 120, 0, 200);
            w_o = 0;
            Z_clrst();
            w_o = 100;
            Z_clrst();
        } else {
            V_setrect(200, 120, 0, 100);
            w_o = 0;
            Z_clrst();
        }
        pl1.drawst = pl2.drawst = 0xFF;
        V_setrect(0, 320, 0, 200);
    }
}

void GM_command(int c) {
    switch (c) {
        case CANCEL:
            GM_set(NULL);
            break;
        case INTERP:
            s_interp = !s_interp;
            GM_set(mnu);
            break;
        case MUSIC:
            F_freemus();
            F_nextmus(g_music);
            F_loadmus(g_music);
            S_startmusic();
            GM_set(mnu);
            break;
        case NEWGAME:
            GMV_say("_NEWGAME");
            GM_set(&ngplr_mnu);
            break;
        case PLR2:
            GMV_say("_2PLAYER");
            GM_set(&ngdm_mnu);
            break;
        case PLR1:
            GMV_say("_1PLAYER");
            ngdm_mnu.cur = 0;
        case COOP:
        case DM:
        case BOT:
            if (c == COOP) {
                GMV_say("_COOP");
            } else if (c == DM) {
                GMV_say("_DM");
            }
            if (c != PLR1) {
                GM_set(&plcolor_mnu);
                break;
            }
        case PLCEND:
            _2pl = ngplr_mnu.cur;
            w_ht = ngplr_mnu.cur ? 98 : 198;
            g_dm = ngdm_mnu.cur != 0;
            g_bot = ngdm_mnu.cur == 2;
            g_map = (_warp) ? _warp : 1;
            PL_reset();
            if (_2pl) {
                pl1.color = pcolortab[p1color];
                pl2.color = pcolortab[p2color];
            } else {
                pl1.color = 0x70;
            }
            G_start();
            GM_set(NULL);
            break;
        case OPTIONS:
            GMV_say("_RAZNOE");
            GM_set(&opt_mnu);
            break;
        case LOADGAME:
            GMV_say("_OLDGAME");
            F_getsavnames();
            GM_set(&load_mnu);
            break;
        case SAVEGAME:
            if (g_st != GS_GAME) {
                break;
            }
            GMV_say("_SAVEGAM");
            F_getsavnames();
            GM_set(&save_mnu);
            break;
        case SAVE:
            input = 1;
            memcpy(ibuf, savname[save_mnu.cur], 24);
            icur = strlen(ibuf);
            GM_set(mnu);
            break;
        case LOAD:
            if (!savok[load_mnu.cur]) {
                break;
            }
            load_game(load_mnu.cur);
            GM_set(NULL);
            break;
        case VOLUME:
            GMV_say("_VOLUME");
            GM_set(&vol_mnu);
            break;
        case GAMMA:
            GMV_say("_GAMMA");
            GM_set(&gamma_mnu);
            break;
        case QUITGAME:
            GMV_say((rand() & 1) ? "_EXIT1" : "_EXIT2");
            GM_set(qmsg[d2random(3)]);
            break;
        case ENDGAME:
            if (g_st != GS_GAME) {
                break;
            }
            GMV_say("_RESTART");
            GM_set(&endgm_msg);
            break;
        case QUIT:
            F_freemus();
            GMV_stop();
            for (c = (Z_sound(M_lock(qsnd[d2random(QSND_NUM)]), 256) + 9) << 16, timer = 0; timer < c;) {
            }
            ERR_quit();
            break;
        case ENDGM:
            PL_reset();
            G_start();
            GM_set(NULL);
            break;
        case PL1CM:
            if (--p1color < 0) {
                p1color = PCOLORN - 1;
            }
            break;
        case PL1CP:
            if (++p1color >= PCOLORN) {
                p1color = 0;
            }
            break;
        case PL2CM:
            if (--p2color < 0) {
                p2color = PCOLORN - 1;
            }
            break;
        case PL2CP:
            if (++p2color >= PCOLORN) {
                p2color = 0;
            }
            break;
        case SVOLM:
            if ((snd_vol -= 8) < 0) {
                snd_vol = 0;
            }
            break;
        case SVOLP:
            if ((snd_vol += 8) > 128) {
                snd_vol = 128;
            }
            break;
        case MVOLM:
            if ((mus_vol -= 8) < 0) {
                mus_vol = 0;
            }
            break;
        case MVOLP:
            if ((mus_vol += 8) > 128) {
                mus_vol = 128;
            }
            break;
        case GAMMAM:
            setgamma(gamma - 1);
            break;
        case GAMMAP:
            setgamma(gamma + 1);
            break;
    }
}

static void shot(void) {
    FILE *h;
    static int num = 1;
    char fn[13];

    sprintf(fn, "shot%04d.vga", num);
    h = fopen(fn, "wb");
    fwrite("VGAED2", 7, 1, h);
    fwrite(std_pal, 768, 1, h);
    fwrite("scr\0\x40\1\xC8\0\0\0\0\0", 12, 1, h);
    fwrite((void *) 0xA0000, V_SCR_WIDTH * V_SCR_HEIGHT, 1, h);
    fwrite("", 1, 1, h);
    fclose(h);
    ++num;
}

int GM_act(void) {
    byte c;

    if (mnu == &plcolor_mnu) {
        if (*(++panimp) == 0) {
            panimp = panim;
        }
        GM_set(mnu);
    }
    if (movsndt > 0) {
        --movsndt;
    } else {
        movsndt = 0;
    }
    if (g_st == GS_TITLE) {
        if (!mnu) {
            if (lastkey) {
                GM_set(&main_mnu);
                Z_sound(msnd3, 128);
                lastkey = 0;
                return 1;
            }
        }
    }
    if (input) {
        switch (lastkey) {
            case 0x1C:
            case 0x9C:
                F_savegame(save_mnu.cur, ibuf);
                input = 0;
                GM_set(NULL);
                break;
            case 1:
                input = 0;
                GM_set(mnu);
                break;
            case 0x0E:
                if (icur) {
                    ibuf[--icur] = 0;
                    GM_set(mnu);
                }
                break;
            default:
                if (icur >= 23) {
                    break;
                }
                c = keychar[(keys[0x2A] || keys[0x36]) ? 1 : 0][lastkey];
                if (!c) {
                    break;
                }
                ibuf[icur] = c;
                ibuf[++icur] = 0;
                GM_set(mnu);
        }
    } else {
        switch (lastkey) {
            case 1:
                if (!mnu) {
                    GM_set(&main_mnu);
                    Z_sound(msnd3, 128);
                } else {
                    GM_set(NULL);
                    Z_sound(msnd4, 128);
                }
                break;
            case 0x57:
                if (mnu) {
                    break;
                }
                Z_sound(msnd3, 128);
                GMV_say("_GAMMA");
                GM_set(&gamma_mnu);
                break;
            case 0x3E:
                if (mnu) {
                    break;
                }
                Z_sound(msnd3, 128);
                GMV_say("_VOLUME");
                GM_set(&vol_mnu);
                break;
            case 0x3C:
                if (mnu) {
                    break;
                }
                if (g_st != GS_GAME) {
                    break;
                }
                Z_sound(msnd3, 128);
                F_getsavnames();
                GM_set(&save_mnu);
                break;
            case 0x3D:
                if (mnu) {
                    break;
                }
                Z_sound(msnd3, 128);
                F_getsavnames();
                GM_set(&load_mnu);
                break;
            case 0x44:
                if (mnu) {
                    break;
                }
                Z_sound(msnd3, 128);
                GM_command(QUITGAME);
                break;
            case 0x48:
            case 0xC8:
                if (!mnu) {
                    break;
                }
                if (mnu->type != MENU) {
                    break;
                }
                if (--mnu->cur < 0) {
                    mnu->cur = mnu->n - 1;
                }
                GM_set(mnu);
                Z_sound(msnd1, 128);
                break;
            case 0x50:
            case 0xD0:
            case 0x4C:
                if (!mnu) {
                    break;
                }
                if (mnu->type != MENU) {
                    break;
                }
                if (++mnu->cur >= mnu->n) {
                    mnu->cur = 0;
                }
                GM_set(mnu);
                Z_sound(msnd1, 128);
                break;
            case 0x4B:
            case 0x4D:
            case 0xCB:
            case 0xCD:
                if (!mnu) {
                    break;
                }
                if (mnu->type != MENU) {
                    break;
                }
                if (mnu->t[mnu->cur] < SVOLM) {
                    break;
                }
                GM_command(mnu->t[mnu->cur] + ((lastkey == 0x4B || lastkey == 0xCB) ? 0 : 1));
                GM_set(mnu);
                if (!movsndt) {
                    movsndt = Z_sound((lastkey == 0x4B || lastkey == 0xCB) ? msnd5 : msnd6, 255);
                }
                break;
            case 0x1C:
            case 0x39:
            case 0x9C:
                if (!mnu) {
                    break;
                }
                if (mnu->type != MENU) {
                    break;
                }
                if (mnu->t[mnu->cur] >= PL1CM) {
                    Z_sound(msnd2, 128);
                    GM_command(PLCEND);
                    break;
                }
                if (mnu->t[mnu->cur] >= SVOLM) {
                    break;
                }
                Z_sound(msnd2, 128);
                GM_command(mnu->t[mnu->cur]);
                break;
            case 0x15:
                if (!mnu) {
                    break;
                }
                if (mnu->type != MSG) {
                    break;
                }
                Z_sound(msnd3, 128);
                GM_command(mnu->t[0]);
                break;
            case 0x31:
                if (!mnu) {
                    break;
                }
                if (mnu->type != MSG) {
                    break;
                }
                Z_sound(msnd4, 128);
                GM_command(mnu->t[1]);
                break;
            case 0x3B:
                if (shot_vga) {
                    shot();
                    Z_sound(msnd4, 128);
                }
                break;
        }
    }
    lastkey = 0;
    return ((mnu) ? 1 : 0);
}

void G_keyf(int k, int pressed) {
    int i;

    if (pressed) {
        lastkey = k;
        if (!_2pl || cheat) {
            for (i = 0; i < 31; ++i) {
                cbuf[i] = cbuf[i + 1];
            }
            cbuf[31] = k;
        }
    }
}

void GM_init(void) {
    int i;
    static char nm[QSND_NUM][6] = {
        "CYBSIT", "KNTDTH", "MNPAIN", "PEPAIN", "SLOP", "MANSIT", "BOSPN", "VILACT",
        "PLFALL", "BGACT", "BGDTH2", "POPAIN", "SGTATK", "VILDTH"
    };
    char s[8];

    s[0] = 'D';
    s[1] = 'S';
    for (i = 0; i < QSND_NUM; ++i) {
        memcpy(s + 2, nm[i], 6);
        qsnd[i] = F_getresid(s);
    }

    csnd1 = Z_getsnd("HAHA1");
    csnd2 = Z_getsnd("RADIO");
    msnd1 = Z_getsnd("PSTOP");
    msnd2 = Z_getsnd("PISTOL");
    msnd3 = Z_getsnd("SWTCHN");
    msnd4 = Z_getsnd("SWTCHX");
    msnd5 = Z_getsnd("SUDI");
    msnd6 = Z_getsnd("TUDI");
    msklh[0] = M_lock(F_getresid("M_SKULL1"));
    msklh[1] = M_lock(F_getresid("M_SKULL2"));
    mbarl = M_lock(F_getresid("M_THERML"));
    mbarm = M_lock(F_getresid("M_THERMM"));
    mbarr = M_lock(F_getresid("M_THERMR"));
    mbaro = M_lock(F_getresid("M_THERMO"));
    mslotl = M_lock(F_getresid("M_LSLEFT"));
    mslotm = M_lock(F_getresid("M_LSCNTR"));
    mslotr = M_lock(F_getresid("M_LSRGHT"));
    K_setkeyproc(G_keyf);
}

int GM_draw(void) {
    int i, j, k, y;
    vgaimg_t *pi;
    vgaimg_t *wi;
    int wx, wy;

    ++gm_tm;
    V_setrect(0, 320, 0, 200);
    if (!mnu && !gm_redraw) {
        return 0;
    }
    gm_redraw = 0;
    if (!mnu) {
        return 1;
    }
    if (mnu->type == MENU) {
        y = (200 - mnu->n * 16 - 20) / 2;
        Z_gotoxy(mnu->x, y - 10);
        Z_printbf(mnu->ttl);
        for (i = 0; i < mnu->n; ++i) {
            if (mnu->t[i] == LOAD || mnu->t[i] == SAVE) {
                V_spr(mnu->x, j = y + i * 16 + 29, mslotl);
                for (k = 8; k < 184; k += 8) {
                    V_spr(mnu->x + k, j, mslotm);
                }
                V_spr(mnu->x + 184, j, mslotr);
                Z_gotoxy(mnu->x + 4, j - 8);
                if (input && i == save_mnu.cur) {
                    Z_printsf("%s_", ibuf);
                } else {
                    Z_printsf("%s", savname[i]);
                }
            } else {
                Z_gotoxy(mnu->x + ((mnu->t[i] >= SVOLM) ? ((mnu->t[i] >= PL1CM) ? 50 : 152) : 0), y + i * 16 + 20);
                Z_printbf(mnu->m[i]);
            }
            if (mnu->t[i] == MUSIC) {
                Z_printbf(" '%.8s'", g_music);
            } else if (mnu->t[i] == INTERP) {
                Z_printbf("%s", s_interp ? "ВКЛ" : "ВЫКЛ");
            } else if (mnu->t[i] >= PL1CM) {
                pi = PL_getspr(*panimp, 0, &wi, &wx, &wy);
                V_spr(mnu->x + ((mnu->t[i] == PL1CM) ? 15 : 35) + wx, (y + i * 16 + 20 + 14) + wy, wi);
                V_manspr(mnu->x + ((mnu->t[i] == PL1CM) ? 15 : 35), y + i * 16 + 20 + 14,
                    pi,
                    pcolortab[(mnu->t[i] == PL1CM) ? p1color : p2color]
                );
            } else if (mnu->t[i] >= SVOLM) {
                V_spr(mnu->x, j = y + i * 16 + 20, mbarl);
                for (k = 8; k < 144; k += 8) {
                    V_spr(mnu->x + k, j, mbarm);
                }
                V_spr(mnu->x + 144, j, mbarr);
                switch (mnu->t[i]) {
                    case SVOLM:
                        k = snd_vol;
                        break;
                    case MVOLM:
                        k = mus_vol;
                        break;
                    case GAMMAM:
                        k = gamma << 5;
                        break;
                }
                V_spr(mnu->x + 8 + k, j, mbaro);
            }
        }
        V_spr(mnu->x - 25, y + mnu->cur * 16 + 20 - 8, msklh[(gm_tm / 6) & 1]);
    } else {
        Z_gotoxy((320 - strlen(mnu->ttl) * 7) / 2, 90);
        Z_printsf(mnu->ttl);
        Z_gotoxy(136, 100);
        Z_printsf("(Y/N)");
    }
    return 1;
}
