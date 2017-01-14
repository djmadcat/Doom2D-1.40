#ifndef DOOM2D_DOS_BP_H
#define DOOM2D_DOS_BP_H

#ifndef _MAX_PATH
#define _MAX_PATH   144 /* maximum length of full pathname */
#endif

#define _MAX_DRIVE   3  /* maximum length of drive component */
#define _MAX_DIR    130 /* maximum length of path component */
#define _MAX_FNAME   9  /* maximum length of file name component */
#define _MAX_EXT     5  /* maximum length of extension component */
#ifndef _MAX_NAME
#define _MAX_NAME    13  /* maximum length of file name (with extension) */
#endif

#ifndef O_BINARY
#define O_BINARY 0x0
#endif

//int stricmp(const char *s1, const char *s2);
#define stricmp(a, b) strcasecmp(a, b)

//int strnicmp(const char *s1, const char *s2, size_t len);
#define strnicmp(a, b, l) strncasecmp(a, b, l)

// int memicmp(const void *s1, const void *s2, size_t len);
#define memicmp(a, b, l) strncasecmp(a, b, l)

void _splitpath(const char *__path, char *__drive, char *__dir, char *__fname, char *__ext);

long filelength(int __handle);

#define tell(fd) lseek(fd, 0, SEEK_CUR)

#endif //DOOM2D_DOS_BP_H
