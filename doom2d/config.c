#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "config.h"
#include "files.h"
#include "error.h"
#include "dos_bp.h"
#include "terminal.h"
#include "palette.h"
#include "player.h"
#include "libs/sound.h"
#include "libs/vga.h"
#include "monster.h"
#include "game.h"

enum {
    NONE,
    BYTE,
    WORD,
    DWORD,
    STRING,
    SW_ON,
    SW_OFF,
    FILES
};

int mem_chk_sz = 0;
byte fastdraw = 0;

byte cheat = 0;
byte shot_vga = 0;
int snd_card = 0;

char cd_path[128] = "";

char cfg_file[128] = "DEFAULT.CFG";

static cfg_t cfg[] = {
    { "file", NULL, NULL, FILES, 0 },
    { "cheat", NULL, &cheat, SW_ON, 0 },
    { "vga", NULL, &shot_vga, SW_ON, 0 },
    { "waitrr", "wait_retrace", &vp_waitrr, SW_ON, 0 },
    { "nowaitrr", NULL, &vp_waitrr, SW_OFF, 0 },
    { "rate", "sound_rate", &sfreq, WORD, 0 },
    { NULL, "sound_card", &snd_card, DWORD, 0 },
    { NULL, "sound_port", &snd_port, WORD, 0 },
    { NULL, "sound_dma", &snd_dma, WORD, 0 },
    { NULL, "sound_irq", &snd_irq, WORD, 0 },
    { "sndvol", "sound_volume", &snd_vol, WORD, 0 },
    { "musvol", "music_volume", &mus_vol, WORD, 0 },
    { "interp", "sound_interp", &s_interp, SW_ON, 0 },
    { "nointerp", NULL, &s_interp, SW_OFF, 0 },
    { NULL, "sky", &w_horiz, SW_ON, 0 },
    { "fast", "fast_draw", &fastdraw, SW_ON, 0 },
    { "mon", NULL, &nomon, SW_OFF, 0 },
    { "gamma", "gamma", &gamma, DWORD, 0 },
    { "warp", NULL, &_warp, BYTE, 0 },
    { "memchk", "mem_check", &mem_chk_sz, DWORD, 0 },
    { NULL, "pl1_left", &pl1.kl, BYTE, 0 },
    { NULL, "pl1_right", &pl1.kr, BYTE, 0 },
    { NULL, "pl1_up", &pl1.ku, BYTE, 0 },
    { NULL, "pl1_down", &pl1.kd, BYTE, 0 },
    { NULL, "pl1_jump", &pl1.kj, BYTE, 0 },
    { NULL, "pl1_fire", &pl1.kf, BYTE, 0 },
    { NULL, "pl1_next", &pl1.kwr, BYTE, 0 },
    { NULL, "pl1_prev", &pl1.kwl, BYTE, 0 },
    { NULL, "pl1_use", &pl1.kp, BYTE, 0 },
    { NULL, "pl2_left", &pl2.kl, BYTE, 0 },
    { NULL, "pl2_right", &pl2.kr, BYTE, 0 },
    { NULL, "pl2_up", &pl2.ku, BYTE, 0 },
    { NULL, "pl2_down", &pl2.kd, BYTE, 0 },
    { NULL, "pl2_jump", &pl2.kj, BYTE, 0 },
    { NULL, "pl2_fire", &pl2.kf, BYTE, 0 },
    { NULL, "pl2_next", &pl2.kwr, BYTE, 0 },
    { NULL, "pl2_prev", &pl2.kwl, BYTE, 0 },
    { NULL, "pl2_use", &pl2.kp, BYTE, 0 },
    { "config", NULL, cfg_file, STRING, 0 },
    { NULL, "cd_path", cd_path, STRING, 0 },
    { NULL, NULL, NULL, NONE, 0 }
};

static char buf[256];

void CFG_args(void) {
    int j;
    dword n;
    char *s;

    logo("CFG_args: проверка командной строки\n");
    for (s = strtok(getcmd(buf), " \r\n\t"); s; s = strtok(NULL, " \r\n\t")) {
        next:
        if (*s == '/' || *s == '-') {
            ++s;
        }
        for (j = 0; cfg[j].t; ++j) {
            if (cfg[j].par) {
                if (stricmp(s, cfg[j].par) == 0) {
                    switch (cfg[j].t) {
                        case BYTE:
                            n = strtol(s = strtok(NULL, " \r\n\t"), NULL, 0);
                            *((byte *) cfg[j].p) = (byte) n;
                            break;
                        case WORD:
                            n = strtol(s = strtok(NULL, " \r\n\t"), NULL, 0);
                            *((word *) cfg[j].p) = (word) n;
                            break;
                        case DWORD:
                            n = strtol(s = strtok(NULL, " \r\n\t"), NULL, 0);
                            *((dword *) cfg[j].p) = n;
                            break;
                        case STRING:
                            strcpy((char *) cfg[j].p, s = strtok(NULL, " \r\n\t"));
                            break;
                        case SW_ON:
                            *((byte *) cfg[j].p) = TRUE;
                            if (cfg[j + 1].t == SW_OFF && cfg[j + 1].p == cfg[j].p) {
                                cfg[j + 1].o = 1;
                            }
                            if (j > 0) {
                                if (cfg[j - 1].t == SW_OFF && cfg[j - 1].p == cfg[j].p) {
                                    cfg[j - 1].o = 1;
                                }
                            }
                            break;
                        case SW_OFF:
                            *((byte *) cfg[j].p) = FALSE;
                            if (cfg[j + 1].t == SW_ON && cfg[j + 1].p == cfg[j].p) {
                                cfg[j + 1].o = 1;
                            }
                            if (j > 0) {
                                if (cfg[j - 1].t == SW_ON && cfg[j - 1].p == cfg[j].p) {
                                    cfg[j - 1].o = 1;
                                }
                            }
                            break;
                        case FILES:
                            for (s = strtok(NULL, " \r\n\t"); s; s = strtok(NULL, " \r\n\t")) {
                                if (*s == '/' || *s == '-') {
                                    goto next;
                                }
                                F_addwad(s);
                            }
                            break;
                        default:
                            ERR_failinit("!!! Неизвестный тип в cfg !!!");
                    }
                    cfg[j].o = 1;
                    break;
                }
            }
        }
    }
}

void CFG_load(void) {
    int j, h;
    dword n;
    char s[128];
    char *p1, *p2;

    logo("CFG_load: загрузка конфигурации из %s\n", cfg_file);
    if ((h = open(cfg_file, O_RDONLY | O_BINARY)) == -1) {
        perror("Cannot open file");
        return;
    }
    while (!eof(h)) {
        F_readstr(h, s, 127);
        if (*s == ';' || s[1] == ';') {
            continue;
        } // comment
        if (!(p1 = strtok(s, "\r\n\t =;"))) {
            continue;
        }
        if (!(p2 = strtok(NULL, "\r\n\t =;"))) {
            continue;
        }
        for (j = 0; cfg[j].t; ++j) {
            if (cfg[j].cfg && !cfg[j].o) {
                if (stricmp(p1, cfg[j].cfg) == 0) {
                    switch (cfg[j].t) {
                        case BYTE:
                            n = strtol(p2, NULL, 0);
                            *((byte *) cfg[j].p) = (byte) n;
                            break;
                        case WORD:
                            n = strtol(p2, NULL, 0);
                            *((word *) cfg[j].p) = (word) n;
                            break;
                        case DWORD:
                            n = strtol(p2, NULL, 0);
                            *((dword *) cfg[j].p) = n;
                            break;
                        case STRING:
                            strcpy((char *) cfg[j].p, p2);
                            break;
                        case SW_ON:
                        case SW_OFF:
                            if (stricmp(p2, "ON") == 0) {
                                *((byte *) cfg[j].p) = TRUE;
                                break;
                            }
                            if (stricmp(p2, "OFF") == 0) {
                                *((byte *) cfg[j].p) = FALSE;
                                break;
                            }
                            *((byte *) cfg[j].p) = strtol(p2, NULL, 0);
                            break;
                        case FILES:
                            break;
                        default:
                            ERR_failinit("!!! Неизвестный тип в cfg !!!");
                    }
                    break;
                }
            }
        }
    }
    close(h);
}

void CFG_save(void) {
    char s[140], str[140];
    char *p;
    FILE *h, *oh;

    remove("CONFIG.ZZZ");
    if (rename(cfg_file, "CONFIG.ZZZ")) {
        return;
    }
    if (!(h = fopen("CONFIG.ZZZ", "rt"))) {
        rename("CONFIG.ZZZ", cfg_file);
        return;
    }
    if (!(oh = fopen(cfg_file, "wt"))) {
        fclose(h);
        rename("CONFIG.ZZZ", cfg_file);
        return;
    }
    for (;;) {
        if (!fgets(s, 128, h)) {
            break;
        }
        strcpy(str, s);
        if (!(p = strtok(str, "\r\n\t =;"))) {
            fprintf(oh, "%s", s);
            continue;
        }
        if (stricmp(p, "sound_volume") == 0)
            sprintf(s, "sound_volume=%d\n", snd_vol);
        else if (stricmp(p, "music_volume") == 0)
            sprintf(s, "music_volume=%d\n", mus_vol);
        else if (stricmp(p, "gamma") == 0)
            sprintf(s, "gamma=%d\n", gamma);
        else if (stricmp(p, "sound_interp") == 0)
            sprintf(s, "sound_interp=%s\n", s_interp ? "on" : "off");
        fprintf(oh, "%s", s);
    }
    fclose(oh);
    fclose(h);
    remove("CONFIG.ZZZ");
}
