#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "dos_bp.h"
#include "files.h"
#include "terminal.h"
#include "error.h"
#include "config.h"
#include "libs/snddrv.h"
#include "libs/sound.h"
#include "music.h"
#include "map.h"
#include "game.h"
#include "items.h"
#include "switch.h"
#include "dots.h"
#include "smoke.h"
#include "fx.h"
#include "monster.h"
#include "weapons.h"

byte savname[7][24];
byte savok[7];

int d_start, d_end;
int m_start, m_end;
int s_start, s_end;

int wad_num;
mwad_t wad[MAX_WAD];

static char wads[MAX_WADS][_MAX_PATH];
static int wadh[MAX_WADS];

char f_drive[_MAX_DRIVE];
char f_dir[_MAX_DIR];
char f_name[_MAX_FNAME];
char f_ext[_MAX_EXT];
char f_path[_MAX_PATH];

map_block_t blk;

void F_startup(void) {
    logo("F_startup: настройка файловой системы\n");
    memset(wads, 0, sizeof(wads));
}

void F_getsavnames(void) {
    int i;
    int h;
    static char n[] = "SAVGAME0.DAT";
    short ver;

    for (i = 0; i < 7; ++i) {
        n[7] = i + '0';
        memset(savname[i], 0, 24);
        savok[i] = 0;
        if ((h = open(n, O_RDONLY | O_BINARY)) == -1) {
            continue;
        }
        read(h, savname[i], 24);
        ver = -1;
        read(h, &ver, 2);
        close(h);
        savname[i][23] = 0;
        savok[i] = (ver == 2) ? 1 : 0;
    }
}

void F_savegame(int n, const char *s) {
    int h;
    static char fn[] = "SAVGAME0.DAT";

    fn[7] = n + '0';
    if ((h = open(fn, O_BINARY | O_CREAT | O_RDWR | O_TRUNC, S_IREAD | S_IWRITE)) == -1) {
        return;
    }
    write(h, s, 24);
    write(h, "\2\0", 2);
    G_savegame(h);
    W_savegame(h);
    DOT_savegame(h);
    SMK_savegame(h);
    FX_savegame(h);
    IT_savegame(h);
    MN_savegame(h);
    PL_savegame(h);
    SW_savegame(h);
    WP_savegame(h);
    close(h);
}

void F_loadgame(int n) {
    int h;
    static char fn[] = "SAVGAME0.DAT";
    short ver;

    fn[7] = n + '0';
    if ((h = open(fn, O_BINARY | O_RDONLY)) == -1) {
        return;
    }
    lseek(h, 24, SEEK_SET);
    read(h, &ver, 2);
    if (ver != 2) {
        return;
    }
    G_loadgame(h);
    W_loadgame(h);
    DOT_loadgame(h);
    SMK_loadgame(h);
    FX_loadgame(h);
    IT_loadgame(h);
    MN_loadgame(h);
    PL_loadgame(h);
    SW_loadgame(h);
    WP_loadgame(h);
    close(h);
}

void F_set_snddrv(void) {
    snd_card = (snd_card >= SDRV__END) ? 0 : snd_card;
    logo("F_set_snddrv: звуковая карта #%d\n", snd_card);
    snd_drv = snd_drv_tab[snd_card];
    logo("  %s ", S_getinfo());
    if (snd_card) {
        logo("(%dГц)\n", (dword)sfreq);
    } else {
        logo("\n");
    }
}

void F_addwad(const char *fn) {
    int i;

    for (i = 0; i < MAX_WADS; ++i) {
        if (wads[i][0] == 0) {
            strcpy(wads[i], fn);
            return;
        }
    }
    ERR_failinit("Не могу добавить WAD %s", fn);
}

void F_initwads(void) {
    int i, j, k, h, p;
    char s[4];
    long n, o;
    wad_t w;

    logo("F_initwads: подключение WAD-файлов\n");
    for (i = 0; i < MAX_WAD; ++i) {
        wad[i].n[0] = 0;
    }

    // connect main/root wad ("DOOM2D.WAD")
    logo("  подключается %s\n", wads[0]);
    if ((wadh[0] = h = open(wads[0], O_RDWR | O_BINARY)) == -1) {
        ERR_failinit("Не могу открыть файл: %s", sys_errlist[errno]);
    }

    *s = 0;
    read(h, s, 4);
    if (strncmp(s, "IWAD", 4) != 0 && strncmp(s, "PWAD", 4) != 0) {
        ERR_failinit("Нет подписи IWAD или PWAD");
    }

    read(h, &n, 4);
    read(h, &o, 4);
    lseek(h, o, SEEK_SET);
    for (j = 0, p = 0; j < n; ++j) {
        read(h, &w, 16);
        if (p >= MAX_WAD) {
            ERR_failinit("Слишком много элементов WAD'а");
        }
        memcpy(wad[p].n, w.n, 8);
        wad[p].o = w.o;
        wad[p].l = w.l;
        wad[p].f = 0;
        ++p;
    }

    // connect any other wads
    for (i = 1; i < MAX_WADS; ++i) {
        if (wads[i][0] != 0) {
            logo("  подключается %s\n", wads[i]);
            if ((wadh[i] = h = open(wads[i], O_RDONLY | O_BINARY)) == -1) {
                ERR_failinit("Не могу открыть файл: %s", sys_errlist[errno]);
            }

            _splitpath(wads[i], f_drive, f_dir, f_name, f_ext);
            if (stricmp(f_ext, ".lmp") == 0) {
                for (k = 0; k < MAX_WAD; ++k) {
                    if (strnicmp(wad[k].n, f_name, 8) == 0) {
                        wad[k].o = 0L;
                        wad[k].l = filelength(h);
                        wad[k].f = i;
                        break;
                    }
                }
                if (k >= MAX_WAD) {
                    if (p >= MAX_WAD) {
                        ERR_failinit("Слишком много элементов WAD'а");
                    }
                    memset(wad[p].n, 0, 8);
                    strncpy(wad[p].n, f_name, 8);
                    wad[p].o = 0L;
                    wad[p].l = filelength(h);
                    wad[p].f = i;
                    ++p;
                }
                continue;
            }

            *s = 0;
            read(h, s, 4);
            if (strncmp(s, "IWAD", 4) != 0 && strncmp(s, "PWAD", 4) != 0) {
                ERR_failinit("Нет подписи IWAD или PWAD");
            }

            read(h, &n, 4);
            read(h, &o, 4);
            lseek(h, o, SEEK_SET);
            for (j = 0; j < n; ++j) {
                read(h, &w, 16);
                for (k = 0; k < MAX_WAD; ++k) {
                    if (strnicmp(wad[k].n, w.n, 8) == 0) {
                        wad[k].o = w.o;
                        wad[k].l = w.l;
                        wad[k].f = i;
                        break;
                    }
                }
                if (k >= MAX_WAD) {
                    if (p >= MAX_WAD) {
                        ERR_failinit("Слишком много элементов WAD'а");
                    }

                    memcpy(wad[p].n, w.n, 8);
                    wad[p].o = w.o;
                    wad[p].l = w.l;
                    wad[p].f = i;
                    ++p;
                }
            }
        }
    }

    wad_num = p;
}

void F_allocres(void) {
    d_start = F_getresid("D_START");
    d_end = F_getresid("D_END");
    m_start = F_getresid("M_START");
    m_end = F_getresid("M_END");
    s_start = F_getresid("S_START");
    s_end = F_getresid("S_END");
}

void F_loadres(int r, void *p, dword o, dword l) {
    int fh;
    off_t oo;

    oo = tell(fh = wadh[wad[r].f]);
    if (lseek(fh, wad[r].o + o, SEEK_SET) == -1L) {
        ERR_fatal("Ошибка при чтении файла");
    }
    if ((dword) read(fh, p, l) != l) {
        ERR_fatal("Ошибка при загрузке ресурса %.8s", wad[r].n);
    }
    lseek(fh, oo, SEEK_SET);
}

void F_saveres(int r, const void *p, dword o, dword l) {
    int fh;
    off_t oo;

    oo = tell(fh = wadh[wad[r].f]);
    if (lseek(fh, wad[r].o + o, SEEK_SET) == -1L) {
        ERR_fatal("Ошибка при чтении файла");
    }
    write(fh, p, l);
    lseek(fh, oo, SEEK_SET);
}

int F_getresid(const char *n) {
    int i;

    for (i = 0; i < wad_num; ++i) {
        if (strnicmp(wad[i].n, n, 8) == 0) {
            return i;
        }
    }
    ERR_fatal("F_getresid: ресурс %.8s не найден", n);
    return -1;
}

int F_findres(const char *n) {
    int i;

    for (i = 0; i < wad_num; ++i) {
        if (strnicmp(wad[i].n, n, 8) == 0) {
            return i;
        }
    }
    return -1;
}

void F_getresname(char *n, int r) {
    memcpy(n, wad[r].n, 8);
}

int F_getsprid(const char *n, int s, int d) {
    int i;
    byte a;
    byte b;

    s += 'A';
    d += '0';
    for (i = s_start + 1; i < s_end; ++i) {
        if (memicmp(wad[i].n, n, 4) == 0 && (wad[i].n[4] == s || wad[i].n[6] == s)) {
            if (wad[i].n[4] == s) {
                a = wad[i].n[5];
            } else {
                a = 0;
            }
            if (wad[i].n[6] == s) {
                b = wad[i].n[7];
            } else {
                b = 0;
            }
            if (a == '0') {
                return i;
            }
            if (b == '0') {
                return (i | 0x8000);
            }
            if (a == d) {
                return i;
            }
            if (b == d) {
                return (i | 0x8000);
            }
        }
    }
    ERR_fatal("F_getsprid: изображение %.4s%c%c не найдено", n, (byte) s, (byte) d);
    return -1;
}

int F_getreslen(int r) {
    return wad[r].l;
}

void F_nextmus(char *s) {
    int i;

    i = F_findres(s);
    if (i <= m_start || i >= m_end) {
        i = m_start;
    }
    for (++i;; ++i) {
        if (i >= m_end) {
            i = m_start + 1;
        }
        if (memicmp(wad[i].n, "DMI", 3) != 0) {
            break;
        }
    }
    memcpy(s, wad[i].n, 8);
}

// reads bytes from file until CR
void F_readstr(int h, char *s, int m) {
    int i;
    static char c;

    for (i = 0;;) {
        c = 13;
        read(h, &c, 1);
        if (c == 13) {
            break;
        }
        if (i < m) {
            s[i++] = c;
        }
    }
    s[i] = 0;
}

// reads bytes from file until NUL
void F_readstrz(int h, char *s, int m) {
    int i;
    static char c;

    for (i = 0;;) {
        c = 0;
        read(h, &c, 1);
        if (c == 0) {
            break;
        }
        if (i < m) {
            s[i++] = c;
        }
    }
    s[i] = 0;
}

void F_loadmap(const char *n) {
    int r, h;
    map_header_t hdr;
    int o;

    W_init();
    r = F_getresid(n);
    lseek(h = wadh[wad[r].f], wad[r].o, SEEK_SET);
    read(h, &hdr, sizeof(map_header_t));
    if (memcmp(hdr.id, "Doom2D\x1A", 8) != 0) {
        ERR_fatal("%.8s не является уровнем", n);
    }
    for (;;) {
        read(h, &blk, sizeof(map_block_t));
        if (blk.t == MB_END) {
            break;
        }
        if (blk.t == MB_COMMENT) {
            lseek(h, blk.sz, SEEK_CUR);
            continue;
        }
        o = tell(h) + blk.sz;
        if (!G_load(h)) {
            if (!W_load(h)) {
                if (!IT_load(h)) {
                    if (!SW_load(h)) {
                        ERR_fatal("Неизвестный блок %d(%d) в уровне %.8s", blk.t, blk.st, n);
                    }
                }
            }
        }
        lseek(h, o, SEEK_SET);
    }
}

void F_freemus(void) {
    int i;

    if (!pat) {
        return;
    }
    S_stopmusic();
    free(pat);
    free(patp);
    for (i = 0; i < inum; ++i) {
        if (dmi[i] != NULL) {
            free(dmi[i]);
        }
    }
    free(dmi);
    pat = NULL;
}

void F_loadmus(const char *n) {
    int r;
    int h;
    int i;
    int j;
    int o;
    dmm_t d;
    dmi_t di;

    if ((r = F_findres(n)) == -1) {
        return;
    }
    lseek(h = wadh[wad[r].f], wad[r].o, SEEK_SET);
    read(h, &d, sizeof(dmm_t));
    if (memcmp(d.id, "DMM", 4) != 0) {
        return;
    }
    if (!(pat = malloc(d.psz << 2))) {
        return;
    }
    read(h, pat, d.psz << 2);
    read(h, &seqn, 1);
    if (seqn) {
        read(h, seq, seqn);
    }
    inum = 0;
    read(h, &inum, 1);
    if (!(dmi = malloc(inum * 4))) {
        free(pat);
        pat = NULL;
        return;
    }
    if (!(patp = malloc((word) d.pat * 32))) {
        free(pat);
        free(dmi);
        pat = NULL;
        return;
    }
    for (i = 0; i < inum; ++i) {
        dmi[i] = NULL;
        read(h, &di, sizeof(dmi_t));
        o = tell(h);
        for (r = 0; r < 12; ++r) {
            if (di.n[r] == '.') {
                di.n[r] = 0;
            }
        }
        if ((r = F_findres(di.n)) == -1) {
            continue;
        }
        if (!(dmi[i] = malloc(wad[r].l + 8))) {
            continue;
        }
        memset(dmi[i], 0, 16);
        F_loadres(r, dmi[i], 0, 2);
        F_loadres(r, (int *) dmi[i] + 1, 2, 2);
        F_loadres(r, (int *) dmi[i] + 2, 4, 2);
        F_loadres(r, (int *) dmi[i] + 3, 6, 2);
        F_loadres(r, (int *) dmi[i] + 4, 8, wad[r].l - 8);
        lseek(h, o, SEEK_SET);
    }
    for (i = r = 0, j = (word) d.pat << 3; i < j; ++i) {
        patp[i] = r << 2;
        while (pat[r++].v != 0x80) {
        }
    }
}
