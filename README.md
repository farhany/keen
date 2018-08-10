[![Patreon](https://cloud.githubusercontent.com/assets/8225057/5990484/70413560-a9ab-11e4-8942-1a63607c0b00.png)](https://www.patreon.com/marcelsmit)
<br>:heart:

# Commander Keen in Keen Dreams

This repository contains the source for Commander Keen in Keen Dreams.  It is released under the GNU GPLv2+.  See LICENSE for more details.

The release of the source code does not affect the licensing of the game data files, which you must still legally acquire.  This includes the static data included in this repository for your convenience.  However, you are permitted to link and distribute that data for the purposes of compatibility with the original game.

## Compiling

This port requires SDL 1.x to compile.  If you're on Linux, use apt-get or whatever package manager you use.  On MacOS, I'd recommend getting SDL through brew (brew install sdl).  Once you got your dependencies sorted, run cmake to generate a makefile or project files for your favorite IDE.

The code was converted from the original code targeting Borland C++ 2.0, to modern C++ compilers.  The code has been demonstrated to compile and work on Windows using Visual Studio 2013, Linux using Ubuntu and MacOS High Sierra.

There is some data that must be compiled into the binary.  This data is located in the static directory.  The CMake file provided will automatically take care of this through a custom pre-build step.

## Running

Make sure to get a copy of the game somewhere.  I've tested it with the 1.13 shareware version of the game and it runs fine.  Extract the game files to a folder named 'game'.  The makefile will automatically try to run the generated executable, and look for data files inside the 'game' folder, so be sure to use this name.  Otherwise, copy the compile executable to the data folder and run it from there.

## Credits

This release was made possible by a crowdfunding effort.  It is brought to you by Javier M. Chavez and Chuck Naaden with additional support from:

* Dave Allen
* Kirill Illenseer
* Michael Jurich
* Tom Laermans
* Jeremy Newman
* Braden Obrzut
* Evan Ramos
* Sam Schultz
* Matt Stath
* Ian Williams
* Steven Zakulec
* et al

### EGA/CGA Version

Version 1.00 can be built for either EGA or CGA by changing a constant.  All later versions are specific to one mode.  The constant is `GRMODE` in ID_HEADS.H and ID_ASM.EQU.  Finally ensure that the proper static data files are being linked.  KDREDICT.OBJ/KDREHEAD.OBJ for EGA and KDRCDICT.OBJ/KDRCHEAD.OBJ for CGA.

## Revision History

> A little confusing because revisions have proceeded in three different sequences, the regular (EGA) version, the CGA version, and the shareware version.  At present, 1.05 is the latest CGA version, 1.93 is the latest EGA version, and 1.20 is the latest shareware version.  Also, some versions with suffixed letters have been used when text and other items changed without recompilation of the program itself.

* 1.00 (not numbered): Original release.
* 1.01: Version used on Tiger Software marketing deal.
* 1.01-360: Specially adapted version to fit on 360K disk for Tiger Software marketing deal.
* 1.01S: (mistakenly labeled 1.01): Shareware version.
* 1.02: Registered version.
* 1.03: Registered version (re-mastered edition).
* 1.04: CGA version.
* 1.05: Re-master of CGA version without Gamer's Edge references.

*New CGA versions should be numbered 1.06 through 1.12*

* 1.13: Shareware version (re-mastered edition).
* 1.20: Re-master of shareware version without Gamer's Edge references.

*New shareware versions should be numbered 1.21 through 1.90*

* 1.91: Version for Prodigy Download Superstore.
* 1.92 [rev 0] : Version for Good Times. The shell is not on this version.
* 1.93 [rev 1] : Version for catalog.  Uses DocView Shell instead of old GE shell.  Copyrights updated to "1991-1993" with Softdisk Publishing instead of Softdisk, Inc., to suit our present guidelines.  Otherwise the same as Good Times version.

*New EGA versions should be numbered 1.94 and up.*
