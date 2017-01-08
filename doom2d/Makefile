#		*Translator Definitions*
CC = wcc386
CFLAGS = -zq -w3 -d1 -s -olrt -3s -j
LD = wlink
LDFLAGS = \
  system dos4g \
  debug all \
	op stack=16K


#		*Implicit Rules*

.c.obj:
  $(CC) $(CFLAGS) $<


#		*List Macros*

EXECUTABLE = doom2d.exe
OBJS = \
  main.obj


#		*Explicit Rules*

all: target clean_objs

target: $(OBJS)
	$(LD) $(LDFLAGS) name $(EXECUTABLE) file {$(OBJS)}

clean_objs:
	del $(OBJS)

clean:
	del $(EXECUTABLE)
	del $(OBJS)


#		*Individual File Dependencies*

main.obj: main.c
