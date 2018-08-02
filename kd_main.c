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

// KD_MAIN.C
/*
=============================================================================

							KEEN DREAMS

					An Id Software production

=============================================================================
*/

#include <SDL.h> // crashes on Mac if we don't include this file here..
#include "string.h"

#include "kd_def.h"
#include "syscode.h"
#pragma hdrstop

/*
=============================================================================

						 LOCAL CONSTANTS

=============================================================================
*/

/*
=============================================================================

						 GLOBAL VARIABLES

=============================================================================
*/

char		str[80],str2[20];
boolean		singlestep,jumpcheat,godmode,tedlevel;
word		tedlevelnum;
int			tickrate = 70;
boolean		fullscreen = false;
boolean		fixedAspectRatio = true;
boolean		useOpengl = true;
int			displaySx,displaySy;

/*
=============================================================================

						 LOCAL VARIABLES

=============================================================================
*/

void	DebugMemory (void);
void	TestSprites(void);
short	DebugKeys (void);
void	ShutdownId (void);
void	Quit (char *error);
void	InitGame (void);

//===========================================================================

#if FRILLS

/*
==================
=
= DebugMemory
=
==================
*/

void DebugMemory (void)
{
	VW_FixRefreshBuffer ();
	US_CenterWindow (16,7);

	US_CPrint ("Memory Usage");
	US_CPrint ("------------");
	US_Print ("Total     :");
	US_PrintUnsigned (mminfo.mainmem/1024);
	US_Print ("k\nFree      :");
	US_PrintUnsigned (MM_UnusedMemory()/1024);
	US_Print ("k\nWith purge:");
	US_PrintUnsigned (MM_TotalFree()/1024);
	US_Print ("k\n");
	VW_UpdateScreen();
	IN_Ack ();
#if GRMODE == EGAGR
	MM_ShowMemory ();
#endif
}

/*
===================
=
= TestSprites
=
===================
*/

#define DISPWIDTH	110
#define	TEXTWIDTH   40
void TestSprites(void)
{
	int hx,hy,sprite,oldsprite,bottomy,topx,shift;
	spritetabletype far *spr;
	spritetype _seg	*block;
	unsigned	mem,scan;


	VW_FixRefreshBuffer ();
	US_CenterWindow (30,17);

	US_CPrint ("Sprite Test");
	US_CPrint ("-----------");

	hy=PrintY;
	hx=(PrintX+56)&(~7);
	topx = hx+TEXTWIDTH;

	US_Print ("Chunk:\nWidth:\nHeight:\nOrgx:\nOrgy:\nXl:\nYl:\nXh:\nYh:\n"
			  "Shifts:\nMem:\n");

	bottomy = PrintY;

	sprite = STARTSPRITES;
	shift = 0;

	do
	{
		if (sprite>=STARTTILE8)
			sprite = STARTTILE8-1;
		else if (sprite<STARTSPRITES)
			sprite = STARTSPRITES;

		spr = &spritetable[sprite-STARTSPRITES];
		block = (spritetype _seg *)grsegs[sprite];

		VWB_Bar (hx,hy,TEXTWIDTH,bottomy-hy,WHITE);

		PrintX=hx;
		PrintY=hy;
		US_PrintUnsigned (sprite);US_Print ("\n");PrintX=hx;
		US_PrintUnsigned (spr->width);US_Print ("\n");PrintX=hx;
		US_PrintUnsigned (spr->height);US_Print ("\n");PrintX=hx;
		US_PrintSigned (spr->orgx);US_Print ("\n");PrintX=hx;
		US_PrintSigned (spr->orgy);US_Print ("\n");PrintX=hx;
		US_PrintSigned (spr->xl);US_Print ("\n");PrintX=hx;
		US_PrintSigned (spr->yl);US_Print ("\n");PrintX=hx;
		US_PrintSigned (spr->xh);US_Print ("\n");PrintX=hx;
		US_PrintSigned (spr->yh);US_Print ("\n");PrintX=hx;
		US_PrintSigned (spr->shifts);US_Print ("\n");PrintX=hx;
		if (!block)
		{
			US_Print ("-----");
		}
		else
		{
			mem = block->sourceoffset[3]+5*block->planesize[3];
			mem = (mem+15)&(~15);		// round to paragraphs
			US_PrintUnsigned (mem);
		}

		oldsprite = sprite;
		do
		{
		//
		// draw the current shift, then wait for key
		//
			VWB_Bar(topx,hy,DISPWIDTH,bottomy-hy,WHITE);
			if (block)
			{
				PrintX = topx;
				PrintY = hy;
				US_Print ("Shift:");
				US_PrintUnsigned (shift);
				US_Print ("\n");
				VWB_DrawSprite (topx+16+shift*2,PrintY,sprite);
			}

			VW_UpdateScreen();

			scan = IN_WaitForKey ();

			switch (scan)
			{
			case sc_UpArrow:
				sprite++;
				break;
			case sc_DownArrow:
				sprite--;
				break;
			case sc_LeftArrow:
				if (--shift == -1)
					shift = 3;
				break;
			case sc_RightArrow:
				if (++shift == 4)
					shift = 0;
				break;
			case sc_Escape:
				return;
			}

		} while (sprite == oldsprite);

  } while (1);


}

#endif


/*
================
=
= DebugKeys
=
================
*/
short DebugKeys (void)
{
	boolean esc;
	int level;

#if FRILLS
	if (Keyboard[0x12] && ingame)	// DEBUG: end + 'E' to quit level
	{
		if (tedlevel)
			TEDDeath();
		playstate = levelcomplete;
	}
#endif

	if (Keyboard[0x22] && ingame)		// G = god mode
	{
		VW_FixRefreshBuffer ();
		US_CenterWindow (12,2);
		if (godmode)
		  US_PrintCentered ("God mode OFF");
		else
		  US_PrintCentered ("God mode ON");
		VW_UpdateScreen();
		IN_Ack();
		godmode ^= 1;
		return 1;
	}
	else if (Keyboard[0x17])			// I = item cheat
	{
		VW_FixRefreshBuffer ();
		US_CenterWindow (12,3);
		US_PrintCentered ("Free items!");
		gamestate.boobusbombs=99;
		gamestate.flowerpowers=99;
		gamestate.keys=99;
		VW_UpdateScreen();
		IN_Ack ();
		return 1;
	}
	else if (Keyboard[0x24])			// J = jump cheat
	{
		jumpcheat^=1;
		VW_FixRefreshBuffer ();
		US_CenterWindow (18,3);
		if (jumpcheat)
			US_PrintCentered ("Jump cheat ON");
		else
			US_PrintCentered ("Jump cheat OFF");
		VW_UpdateScreen();
		IN_Ack ();
		return 1;
	}
#if FRILLS
	else if (Keyboard[0x32])			// M = memory info
	{
		DebugMemory();
		return 1;
	}
#endif
	else if (Keyboard[0x19])			// P = pause with no screen disruptioon
	{
		IN_Ack();
	}
	else if (Keyboard[0x1f] && ingame)	// S = slow motion
	{
		singlestep^=1;
		VW_FixRefreshBuffer ();
		US_CenterWindow (18,3);
		if (singlestep)
			US_PrintCentered ("Slow motion ON");
		else
			US_PrintCentered ("Slow motion OFF");
		VW_UpdateScreen();
		IN_Ack ();
		return 1;
	}
#if FRILLS
	else if (Keyboard[0x14])			// T = sprite test
	{
		TestSprites();
		return 1;
	}
#endif
	else if (Keyboard[0x11] && ingame)	// W = warp to level
	{
		VW_FixRefreshBuffer ();
		US_CenterWindow(26,3);
		PrintY+=6;
		US_Print("  Warp to which level(0-16):");
		VW_UpdateScreen();
		esc = !US_LineInput (px,py,str,NULL,true,2,0);
		if (!esc)
		{
			level = atoi (str);
			if (level>=0 && level<=16)
			{
				gamestate.mapon = level;
				playstate = warptolevel;
			}
		}
		return 1;
	}
	return 0;
}

//===========================================================================

/*
==========================
=
= ShutdownId
=
= Shuts down all ID_?? managers
=
==========================
*/

void ShutdownId (void)
{
  US_Shutdown ();
  SD_Shutdown ();
  IN_Shutdown ();
  RF_Shutdown ();
  VW_Shutdown ();
  CA_Shutdown ();
  MM_Shutdown ();
}

//===========================================================================

/*
==========================
=
= Quit
=
==========================
*/

void Quit (char *error)
{
  ShutdownId ();
  if (error && *error)
  {
	//clrscr(); // mstodo : clear screen
	puts(error);
	puts("\n");
	exit(1);
  }
	exit (0);
}

//===========================================================================

/*
==========================
=
= InitGame
=
= Load a few things right away
=
==========================
*/

#if 0
#include "piracy.h"
#endif

void InitGame (void)
{
	short i;

	MM_Startup ();


#if 0
	// Handle piracy screen...
	//
	movedata(FP_SEG(PIRACY),(unsigned)PIRACY,0xb800,displayofs,4000);
	while ((bioskey(0)>>8) != sc_Return);
#endif


#if GRMODE == EGAGR
	if (mminfo.mainmem < 335l*1024)
	{
		// mstodo : clear screen
		//clrscr();			// we can't include CONIO because of a name conflict
		puts ("There is not enough memory available to play the game reliably.  You can");
		puts ("play anyway, but an out of memory condition will eventually pop up.  The");
		puts ("correct solution is to unload some TSRs or rename your CONFIG.SYS and");
		puts ("AUTOEXEC.BAT to free up more memory.\n");
		puts ("Do you want to (Q)uit, or (C)ontinue?");
		i = getc (stdin); // mstodo : waits for enter..
		if ( i != 'c' )
			Quit ("");
	}
#endif

	//US_TextScreen();

	SYS_Init (tickrate, displaySx, displaySy, fullscreen, fixedAspectRatio, useOpengl);

	VW_Startup ();
	RF_Startup ();
	IN_Startup ();
	SD_Startup ();
	US_Startup ();

	//US_UpdateTextScreen();

	CA_Startup ();
	US_Setup ();

//
// load in and lock down some basic chunks
//

	CA_ClearMarks ();

	CA_MarkGrChunk(STARTFONT);
	CA_MarkGrChunk(STARTFONTM);
	CA_MarkGrChunk(STARTTILE8);
	CA_MarkGrChunk(STARTTILE8M);
	for (i=KEEN_LUMP_START;i<=KEEN_LUMP_END;i++)
		CA_MarkGrChunk(i);

	CA_CacheMarks (NULL, 0);

	MM_SetLock (&grsegs[STARTFONT],true);
	MM_SetLock (&grsegs[STARTFONTM],true);
	MM_SetLock (&grsegs[STARTTILE8],true);
	MM_SetLock (&grsegs[STARTTILE8M],true);
	for (i=KEEN_LUMP_START;i<=KEEN_LUMP_END;i++)
		MM_SetLock (&grsegs[i],true);

	CA_LoadAllSounds ();

	fontcolor = WHITE;

	//US_FinishTextScreen();

	VW_SetScreenMode (GRMODE);
	VW_ClearVideo (BLACK);
}



//===========================================================================

/*
==========================
=
= main
=
==========================
*/

int _argc;
char ** _argv;

int main (int argc, char ** argv)
{
	char * ParmStrings[] = {
		"NOMAPDICT", "MAPDICT", "MAPHEAD", "MAPDATA",
		"NOEGADICT", "EGADICT", "EGAHEAD", "EGADATA",
		"TICKRATE", "TICKFPS",
		"FULLSCREEN", "DISPLAY",
		"STRETCH", "NOGL",
		NULL
	};
	int i;
	boolean help = false;

	_argc = argc;
	_argv = argv;
	
	if (_argc >= 2 && _stricmp(_argv[1], "/VER") == 0)
	{
		printf("\nKeen Dreams version 1.93 (Rev 1)\n");
		printf("developed for use with 100%% IBM compatibles\n");
		printf("that have 640K memory, DOS version 3.3 or later,\n");
		printf("and an EGA or VGA display adapter.\n");
		printf("Copyright 1991-1993 Softdisk Publishing.\n");
		printf("Commander Keen is a trademark of Id Software.\n");
		exit(0);
	}

	if (_argc >= 2 && _stricmp(_argv[1], "/?") == 0)
		help = true;

	{
		printf("\nKeen Dreams version 1.93\n");
		printf("Copyright 1991-1993 Softdisk Publishing.\n\n");
		printf("Type KDREAMS from the DOS prompt to run.\n\n");
		//printf("KDREAMS /COMP for SVGA compatibility mode\n");
		//printf("KDREAMS /NODR stops program hang with the drive still on\n");
		//printf("KDREAMS /NOAL disables AdLib and Sound Blaster detection\n");
		//printf("KDREAMS /NOSB disables Sound Blaster detection\n");
		printf("KDREAMS /NOJOYS ignores joystick\n");
		printf("KDREAMS /NOMOUSE ignores mouse\n");
		//printf("KDREAMS /HIDDENCARD overrides video card detection\n");
		printf("KDREAMS /%s use zero-compression EGADICT\n", ParmStrings[4]);
		printf("KDREAMS /%s <file> override EGADICT. Default is %s\n", ParmStrings[5], fn_egadict);
		printf("KDREAMS /%s <file> override EGAHEAD. Default is %s\n", ParmStrings[6], fn_egahead);
		printf("KDREAMS /%s <file> override EGADATA. Default is %s\n", ParmStrings[7], fn_egadata);
		printf("KDREAMS /%s use zero-compression MAPDICT\n", ParmStrings[0]);
		printf("KDREAMS /%s <file> override MAPDICT. Default is %s\n", ParmStrings[1], fn_mapdict);
		printf("KDREAMS /%s <file> override MAPHEAD. Default is %s\n", ParmStrings[2], fn_maphead);
		printf("KDREAMS /%s <file> override MAPDATA. Default is %s\n", ParmStrings[3], fn_mapdata);
		printf("KDREAMS /%s sets the logic tick rate. Default is %d\n", ParmStrings[8], tickrate);
		printf("KDREAMS /%s sync logic tick rate to FPS. Increases smoothness.\n", ParmStrings[9]);
		printf("KDREAMS /%s use a fullscreen video mode.\n", ParmStrings[10]);
		printf("KDREAMS /%s <width> <height> sets display resolution.\n", ParmStrings[11]);
		printf("KDREAMS /%s stretch image. don't maintain original 4:3 aspect ratio.\n", ParmStrings[12]);
		printf("KDREAMS /%s use software renderer instead of OpenGL.\n", ParmStrings[13]);
		printf("KDREAMS /VER  for version and compatibility information\n");
		printf("KDREAMS /? for this help information\n");
		if (help)
			exit(0);
	}

	for (i = 1; i < _argc; ++i)
	{
		int p = US_CheckParm(_argv[i], ParmStrings);

		// map

		if (p == 0)
			fn_mapdict = (char*)-1;
		if (p == 1)
			fn_mapdict = _argv[++i];
		if (p == 2)
			fn_maphead = _argv[++i];
		if (p == 3)
			fn_mapdata = _argv[++i];

		// ega

		if (p == 4)
			fn_egadict = (char*)-1;
		if (p == 5)
			fn_egadict = _argv[++i];
		if (p == 6)
			fn_egahead = _argv[++i];
		if (p == 7)
			fn_egadata = _argv[++i];

		// tickrate

		if (p == 8)
			tickrate = atoi(_argv[++i]);
		if (p == 9)
			tickfps = true;

		// graphics

		if (p == 10)
			fullscreen = true;
		if (p == 11)
		{
			displaySx = atoi(_argv[++i]);
			displaySy = atoi(_argv[++i]);
		}
		if (p == 12)
			fixedAspectRatio = false;
		if (p == 13)
			useOpengl = false;
	}

	//textcolor(7); // mstodo
	//textbackground(0);

	InitGame();

	DemoLoop();					// DemoLoop calls Quit when everything is done
	Quit("Demo loop exited???");
	
	return -1;
}

