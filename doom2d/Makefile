#		*Translator Definitions*
CC = wcc386
CFLAGS = -zq -w3 -d1 -s -olrt -3s -j
LD = wlink
LDFLAGS = \
  system dos4g \
  debug all \
  op stack=16K

COMPILE_CMD = $(CC) $(CFLAGS) -fo=$@ $[*


#		*Implicit Rules*

.c.obj:
  $(COMPILE_CMD)


#		*List Macros*

TARGET = doom2d
TARGET_EXE = $(TARGET).exe
TARGET_LNK = $(TARGET).lnk
OBJS = \
  terminal.obj \
  palette.obj \
  main.obj \
  player.obj \
#  dots.obj \
#  smoke.obj \
#  weapons.obj \
#  items.obj \
#  monster.obj \
#  switch.obj \
#  fx.obj \
#  bmap.obj \
#  view.obj \
  menu.obj \
  game.obj \
  files.obj \
  config.obj \
  error.obj \
  memory.obj \
#  vga2.obj
#  a8.obj
  misca.obj \
#  miscc.obj
  keyb.obj \
  harderr.obj \
  timer.obj \
  sound.obj \
  vga.obj


#		*Explicit Rules*

all: target_archive

clean: target_clean

target_archive: target target_lnk_remove objs_remove

target: $(OBJS) target_lnk_compile target_compile

target_clean: target_remove target_lnk_remove objs_remove

target_compile:
  $(LD) @$(TARGET_LNK)

target_remove:
  @del $(TARGET_EXE)

target_lnk_compile: target_lnk_remove
  @echo "$(LDFLAGS)" >> $(TARGET_LNK)
  @echo "name $(TARGET_EXE)" >> $(TARGET_LNK)
  @for %i in ($(OBJS)) do @echo "file %i" >> $(TARGET_LNK)

target_lnk_remove:
  @del $(TARGET_LNK)

objs_remove:
  @del *.obj
  @del *.err


#		*Individual File Dependencies*

misca.obj : misca_st.c
  $(COMPILE_CMD)

keyb.obj : libs/keyb_st.c
  $(COMPILE_CMD)

harderr.obj : libs/hderr_st.c
  $(COMPILE_CMD)

timer.obj : libs/timer_st.c
  $(COMPILE_CMD)

sound.obj : libs/sound_st.c
  $(COMPILE_CMD)

vga.obj : libs/vga_st.c
  $(COMPILE_CMD)
