#ifndef DOOM2D_MAP_H
#define DOOM2D_MAP_H

typedef struct {
    // identifier ("Doom2D\x1A")
    char id[8];
    // version
    short ver;
} map_header_t;

typedef struct {
    short t;                // тип блока
    short st;               // подтип (метод упаковки, например)
    // если не используется, то должен быть 0
    // (для будущей совместимости)
    int sz;                 // размер (сколько байт после этой структуры)
} map_block_t;

enum {
    MB_COMMENT = -1,
    MB_END = 0,
    MB_WALLNAMES,
    MB_BACK,
    MB_WTYPE,
    MB_FRONT,
    MB_THING,
    MB_SWITCH,
    MB_MUSIC,
    MB_SKY,
    MB_SWITCH2,
    MB__UNKNOWN
};

#endif //DOOM2D_MAP_H
