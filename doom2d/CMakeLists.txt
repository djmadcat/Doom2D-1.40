cmake_minimum_required(VERSION 3.6)
project(doom2d)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCE_FILES
        glob.h
        dos_bp.h dos_bp.c
        terminal.h terminal.c
        palette.h palette.c
        main.c
        player.h player.c
        dots.h dots.c
        smoka.h smoka_st.c
        smoke.h smoke.c
        view.h view.c
        vgaa.h vgaa_st.c
        menu.h menu.c
        bot.h bot.c
        game.h game.c
        music.h music.c
        map.h
        things.h
        items.h items.c
        monster.h monster.c
        weapons.h weapons.c
        switch.h switch.c
        files.h files.c
        fx.h fx.c
        bmapa.h bmapa_st.c
        bmap.h bmap.c
        config.h config.c
        error.h error.c
        memory.h memory.c
        a8.h a8.c
        misca.h misca_st.c
        miscc.h miscc.c
        libs/keyb.h libs/keyb_st.c
        libs/harderr.h libs/hderr_st.c
        libs/timer.h libs/timer_st.c
        libs/snddrv.h libs/snddrv.c
        libs/sound.h libs/sound_st.c
        libs/vga.h libs/vga_st.c)

add_executable(doom2d ${SOURCE_FILES})
