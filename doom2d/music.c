#include "music.h"
#include <stddef.h>

byte seq[255];
byte seqn;
dmv_t *pat = NULL;
dword *patp;
dmi_t **dmi;
int inum = 0;
