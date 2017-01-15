#include <stddef.h>
#include <unistd.h>
#include "dos_bp.h"

void _splitpath(const char *__path, char *__drive, char *__dir, char *__fname, char *__ext) {
}

char *getcmd(char *__buffer) {
    return NULL;
}

long filelength(int __handle) {
    return 0;
}

int eof(int __handle) {
    int result;
    int len;
    int pos;

    result = filelength(__handle);
    if (result != -1) {
        len = result;
        result = tell(__handle);
        if (result != -1) {
            pos = result;
            result = pos == len;
        }
    }
    return result;
}
