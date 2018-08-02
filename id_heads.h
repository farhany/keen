/* Keen Dreams Source Code
 * Copyright (C) 2014 Javier M. Chavez
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

// ID_GLOB.H

#pragma once

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef WIN32
	#include <io.h>
#else
	#include <unistd.h>
#endif

#include <stdint.h>

#define SUPER_SMOOTH_SCROLLING 1

#define _seg
#define far
#define near
#define huge
#define MK_FP(x, y) (((byte*)x) + (y))
#define FP_SEG(x) (x)
#ifndef WIN32
	#include <assert.h>
	#define O_BINARY 0
	#define _open open
	#define _close close
	#define _read read
	#define _write write
	#define _lseek lseek
	static int _filelength(int file)
	{
		struct stat s;
		fstat(file, &s);
		return s.st_size;
	}
	#define _stricmp strcasecmp
	#define strcpy_s(dst, dstSize, src) strcpy(dst, src)
	#define sprintf_s(dst, dstSize, fmt, ...) sprintf(dst, fmt, __VA_ARGS__)
	static char * _ltoa(long v, char * s, int radix)
	{
		assert(radix == 10);
		sprintf(s, "%d", (int)v);
		return s;
	}
	#define _ultoa(v, s, radix) _ltoa((long)v, s, radix)
#endif

extern int _argc;
extern char ** _argv;

#define __ID_GLOB__

#define	EXTENSION	"KDR"

#include "graphkdr.h"
#include "audiokdr.h"

#define	TEXTGR	0
#define	CGAGR	1
#define	EGAGR	2
#define	VGAGR	3

#define GRMODE	EGAGR

#if GRMODE == EGAGR
#define GREXT	"EGA"
#endif

//#define PROFILE

//
//	ID Engine
//	Types.h - Generic types, #defines, etc.
//	v1.0d1
//

#ifndef	__TYPES__
#define	__TYPES__

typedef	enum {false,true}		booleanValues;
typedef	unsigned	char		boolean;
typedef	unsigned	char		byte;
typedef	uint16_t				word;
typedef	uint32_t				longword;
typedef	byte *					Ptr;

typedef	struct
		{
			int	x,y;
		} Point;
typedef	struct
		{
			Point	ul,lr;
		} Rect;

#define	nil	((void *)0)

#endif

#include "id_mm.h"
#include "id_ca.h"
#include "id_vw.h"
#include "id_rf.h"
#include "id_in.h"
#include "id_sd.h"
#include "id_us.h"



