cmake_minimum_required(VERSION 3.6)
project(doom2d)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCE_FILES
        glob.h
        terminal.h terminal.c
        palette.h palette.c
        main.c
        player.h player.c
        view.h
        menu.h menu.c
        game.h game.c
        files.h files.c
        config.h config.c
        error.h error.c
        memory.h memory.c
        misca.h misca_st.c
        libs/keyb.h libs/keyb_st.c
        libs/harderr.h libs/hderr_st.c
        libs/timer.h libs/timer_st.c
        libs/sound.h libs/sound_st.c
        libs/vga.h libs/vga_st.c)

add_executable(doom2d ${SOURCE_FILES})
