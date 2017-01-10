#ifndef DOOM2D_SNDDRV_H
#define DOOM2D_SNDDRV_H

enum {
    // silence
    SDRV_NONE = 0,

    // Adlib: 6 bits
    SDRV_ADLIB,

    // Covox Speech Thing: 8 bits
    SDRV_COVOX,

    // snd_port = номер LPT(1-4)
    // PC Speaker: 1 bit
    SDRV_PC1,
    // PC Speaker: 8 bits (or 7?)
    SDRV_PC8,
    // Sound Blaster: 8 bits, DMA
    SDRV_SB,

    // snd_port (usually 0x220)
    // snd_iqr (usually 7 or 5)
    // sorry, but DMA only 1 for now
    // Sound Blaster: 8 bits, without DMA (slower)
    //SDRV_SBNODMA,
    // Sound Blaster 16/AWE32: 16 bits, DMA
    SDRV_SB16,

    // end
    SDRV__END
};

typedef void (* snd_drv_f)(void);

void __none_drv(void);
void __adlib_drv(void);
void __covox_drv(void);
void __pc1_drv(void);
void __pc8_drv(void);
void __sb_drv(void);
//void __sbnodma_drv(void);
void __sb16_drv(void);

extern snd_drv_f snd_drv_tab[];

#endif //DOOM2D_SNDDRV_H
