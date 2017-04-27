# Build from sources (In Progress)

## Environment

* Target platform: DOS
* Compiler (C/C++): Watcom C/C++ Compiler 10.5
* Compiler (ASM): Borland Turbo Assembler 5 (or simply TASM5)
* DOS/4G extender which is included with the Watcom C compiler (as DOS/4GW)


## Prepare environment

* Target OS: [DOSBox 0.74](http://www.dosbox.com/download.php?main=1), an open source DOS emulator for BeOS, Linux, Mac OS X, OS/2, and Windows
* Compiler (C/C++): [Open Watcom C/C++ 1.9](http://www.openwatcom.org/download.php) or [Open Watcom C/C++ 2.0](https://sourceforge.net/projects/openwatcom/files/current-build/)

### macOS

#### Run DOSBox

Install `DOSBox.app` to `/Applications` directory.

Assume that the root folder for experiments is `/Volumes/Development/Games/Doom2D`.

Create directory for DOSBox mount drive on the host OS.
```
mkdir -p /Volumes/Development/Games/Doom2D/develop_drive
```

Create DOSBox configuration file `/Volumes/Development/Games/Doom2D/develop.conf` with content:
```
[dos]
xms=true
ems=true
umb=true
keyboardlayout=866

[autoexec]
@ECHO OFF
MOUNT C "/Volumes/Development/Games/Doom2D/develop_drive" -freesize 1024
C:
```
See [DOSBox wiki about MOUNT command](https://www.dosbox.com/wiki/MOUNT).

Run DOSBox with config.
```
open -a DOSBox --args -conf /Volumes/Development/Games/Doom2D/develop.conf
```

#### Install Open Watcom compiler

Download [Open Watcom C/C++ compiler 1.9 for DOS](http://ftp.openwatcom.org/install/open-watcom-c-dos-1.9.exe).

On host-machine:
```
\curl -SL -O http://ftp.openwatcom.org/install/open-watcom-c-dos-1.9.exe -o /Volumes/Development/Games/Doom2D/develop_drive/wc_1_9.exe
```

On guest-machine:
```
> C:
> WC_1_9.EXE
```

Choose `Full installation`.<br/>
Choose `Let you make the modifications later`.<br/>
Choose `Create file` for CONFIG.SYS and for AUTOEXEC.BAT (installer has a bug, you must choose this option).

Remove `CONFIG.SYS` and `AUTOEXEC.BAT` files as unused:
```
> DEL CONFIG.SYS
> DEL AUTOEXEC.BAT
```

Copy `/Volumes/Development/Games/Doom2D/develop_drive/WATCOM/AUTOEXEC.DOS` content to `[autoexec]` section of `develop.conf` file right between `MOUNT C ...` and `C:` lines.

#### Known problems

Buggy encoding in DOSBox or Watcom compiler, or both.


# See also

* [32bit DOS Development with Open Watcom](http://tuttlem.github.io/2015/10/04/32bit-dos-development-with-open-watcom.html)
* [Tutorial: How to compile pcasm example codes on DosBox](https://forum.nasm.us/index.php?topic=1319.0)
