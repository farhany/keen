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

// KD_DEMO.C

#include "kd_def.h"
#include "syscode.h"

#pragma	hdrstop

#define RLETAG	((unsigned short)0xABCD)

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


/*
=============================================================================

						 LOCAL VARIABLES

=============================================================================
*/

//===========================================================================

/*
=====================
=
= NewGame
=
= Set up new game to start from the beginning
=
=====================
*/

void NewGame (void)
{
	word	i;

	gamestate.worldx = 0;		// spawn keen at starting spot

	gamestate.mapon = 0;
	gamestate.score = 0;
	gamestate.nextextra = 20000;
	gamestate.lives = 3;
	gamestate.flowerpowers = gamestate.boobusbombs = 0;
	for (i = 0;i < GAMELEVELS;i++)
		gamestate.leveldone[i] = false;
}

//===========================================================================

/*
=====================
=
= WaitOrKey
=
=====================
*/

int WaitOrKey (int vbls)
{
	while (vbls--)
	{
		IN_ReadControl(0,&c);		// get player input
		if (LastScan || c.button0 || c.button1)
		{
			IN_ClearKeysDown ();
			return 1;
		}
		VW_WaitVBL(1);
	}
	return 0;
}

//===========================================================================

/*
=====================
=
= GameOver
=
=====================
*/

void
GameOver (void)
{
	VW_InitDoubleBuffer ();
	US_CenterWindow (16,3);

	US_PrintCentered("Game Over!");

	VW_UpdateScreen ();
	IN_ClearKeysDown ();
	IN_Ack ();

}


//===========================================================================

/*
==================
=
= StatusWindow
=
==================
*/

void StatusWindow (void)
{
	word	x;

	// DEBUG - make this look better

	US_CenterWindow(22,7);
	US_CPrint("Status Window");

	WindowX += 8;
	WindowW -= 8;
	WindowY += 20;
	WindowH -= 20;
	PrintX = WindowX;
	PrintY = WindowY;

	VWB_DrawTile8(PrintX,PrintY,26);
	VWB_DrawTile8(PrintX + 8,PrintY,27);
	PrintX += 24;
	US_PrintUnsigned(gamestate.lives);
	US_Print("\n");

	VWB_DrawTile8(PrintX,PrintY,32);
	VWB_DrawTile8(PrintX + 8,PrintY,33);
	VWB_DrawTile8(PrintX,PrintY + 8,34);
	VWB_DrawTile8(PrintX + 8,PrintY + 8,35);
	PrintX += 24;
	US_PrintUnsigned(gamestate.boobusbombs);
	US_Print("\n");

	WindowX += 50;
	WindowW -= 50;
	PrintX = WindowX;
	PrintY = WindowY;

	fontcolor = F_FIRSTCOLOR;
	US_Print("Next ");
	fontcolor = F_BLACK;
	x = PrintX;
	VWB_DrawTile8(PrintX,PrintY,26);
	VWB_DrawTile8(PrintX + 8,PrintY,27);
	PrintX += 24;
	US_PrintUnsigned(gamestate.nextextra);
	US_Print("\n");

	PrintX = x;
	VWB_DrawTile8(PrintX,PrintY,24);
	VWB_DrawTile8(PrintX + 8,PrintY,25);
	PrintX += 24;
	US_PrintUnsigned(gamestate.keys);
	US_Print("\n");

	// DEBUG - add flower powers (#36)

	VW_UpdateScreen();
	IN_Ack();
}

#if SAVELOAD_FIX

/*

NOTE !!

any additions to this list MUST be appended to the bottom of this list to ensure backward compatibility with older save games

*/

extern	statetype s_door;
extern	statetype s_doorraise;
extern	statetype s_flower1;
extern	statetype s_flower2;
extern	statetype s_flower3;
extern	statetype s_flower4;
extern	statetype s_flower5;
extern	statetype s_flower6;
extern	statetype s_poofto1;
extern	statetype s_poofto2;
extern	statetype s_poofto3;
extern	statetype s_poofto4;
extern	statetype s_pooffrom1;
extern	statetype s_pooffrom2;
extern	statetype s_pooffrom3;
extern	statetype s_pooffrom4;
extern	statetype s_pooffrom5;
extern	statetype s_pooffrom6;
extern	statetype s_pooffrom7;
extern	statetype s_bonus1;
extern	statetype s_bonus1;
extern	statetype s_broccowalk1;
extern	statetype s_broccowalk2;
extern	statetype s_broccowalk3;
extern	statetype s_broccowalk4;
extern	statetype s_broccosmash1;
extern	statetype s_broccosmash2;
extern	statetype s_broccosmash3;
extern	statetype s_broccosmash4;
extern	statetype s_broccosmash5;
extern	statetype s_broccosmash6;
extern	statetype s_broccosmash7;
extern	statetype s_broccosmash8;
extern	statetype s_broccosmash9;
extern	statetype s_tomatbounce;
extern	statetype s_tomatbounce2;
extern	statetype s_carrotwalk1;
extern	statetype s_carrotwalk2;
extern	statetype s_carrotwalk3;
extern	statetype s_carrotwalk4;
extern	statetype s_carrotleap;
extern	statetype s_asparwalk1;
extern	statetype s_asparwalk2;
extern	statetype s_asparwalk3;
extern	statetype s_asparwalk4;
extern	statetype s_grapewait;
extern	statetype s_grapefall;
extern	statetype s_grapesit;
extern	statetype s_graperise;
extern	statetype s_taterwalk1;
extern	statetype s_taterwalk2;
extern	statetype s_taterwalk3;
extern	statetype s_taterwalk4;
extern	statetype s_taterattack1;
extern	statetype s_taterattack2;
extern	statetype s_taterattack3;
extern	statetype s_cartroll1;
extern	statetype s_cartroll2;
extern	statetype s_frenchywalk1;
extern	statetype s_frenchywalk2;
extern	statetype s_frenchywalk3;
extern	statetype s_frenchywalk4;
extern	statetype s_frenchyrun1;
extern	statetype s_frenchyrun2;
extern	statetype s_frenchyrun3;
extern	statetype s_frenchyrun4;
extern	statetype s_frenchythrow1;
extern	statetype s_frenchythrow2;
extern	statetype s_frenchythrow3;
extern	statetype s_fry1;
extern	statetype s_fry2;
extern	statetype s_melonside;
extern	statetype s_melonsidespit;
extern	statetype s_melonsidespit2;
extern	statetype s_melondown;
extern	statetype s_melondownspit;
extern	statetype s_melondownspit2;
extern	statetype s_melonseed1;
extern	statetype s_melonseed2;
extern	statetype s_melonseedd1;
extern	statetype s_melonseedd2;
extern	statetype s_squasherwalk1;
extern	statetype s_squasherwalk2;
extern	statetype s_squasherjump1;
extern	statetype s_squasherjump2;
extern	statetype s_squasherwait;
extern	statetype s_apelwalk1;
extern	statetype s_apelwalk2;
extern	statetype s_apelwalk3;
extern	statetype s_apelclimb1;
extern	statetype s_apelclimb2;
extern	statetype s_apelslide1;
extern	statetype s_apelslide2;
extern	statetype s_apelslide3;
extern	statetype s_apelslide4;
extern	statetype s_apelfall;
extern statetype s_peabrainfly;
extern	statetype s_peabrainwalk1;
extern	statetype s_peabrainwalk2;
extern	statetype s_peabrainwalk3;
extern	statetype s_peabrainwalk4;
extern	statetype s_peapodwalk1;
extern	statetype s_peapodwalk2;
extern	statetype s_peapodwalk3;
extern	statetype s_peapodwalk4;
extern	statetype s_peapodspit1;
extern	statetype s_peapodspit2;
extern	statetype s_boobuswalk1;
extern	statetype s_boobuswalk2;
extern	statetype s_boobuswalk3;
extern	statetype s_boobuswalk4;
extern	statetype s_boobusjump;
extern	statetype s_deathwait1;
extern	statetype s_deathwait2;
extern	statetype s_deathwait3;
extern	statetype s_deathboom1;
extern	statetype s_deathboom2;
extern	statetype s_deathboom3;
extern	statetype s_deathboom4;
extern	statetype s_deathboom5;
extern	statetype s_deathboom6;
extern	statetype s_score; // not made extern
extern	statetype s_flowerpower1;
extern	statetype s_flowerpower2;
extern	statetype s_boobusbomb1;
extern	statetype s_boobusbomb2;
extern	statetype s_bombexplode;
extern	statetype s_bombexplode2;
extern	statetype s_bombexplode3;
extern	statetype s_bombexplode4;
extern	statetype s_bombexplode5;
extern	statetype s_bombexplode6;
extern	statetype s_powerblink1;
extern	statetype s_powerblink2;
extern	statetype s_worldkeen;
extern	statetype s_worldkeenwave1;
extern	statetype s_worldkeenwave2;
extern	statetype s_worldkeenwave3;
extern	statetype s_worldkeenwave4;
extern	statetype s_worldkeenwave5;
extern	statetype s_worldkeenwait;
extern	statetype s_worldkeensleep1;
extern	statetype s_worldkeensleep2;
extern	statetype s_worldwalk;
extern	statetype s_keenzee1;
extern	statetype s_keenzee2;
extern	statetype s_keenzee3;
extern	statetype s_keenzee4;
extern	statetype s_keenzee5;
extern	statetype	s_keenstand;
extern	statetype s_keenpauselook;
extern	statetype s_keenyawn1;
extern	statetype s_keenyawn2;
extern	statetype s_keenyawn3;
extern	statetype s_keenyawn4;
extern	statetype s_keenwait1;
extern	statetype s_keenwait2;
extern	statetype s_keenwait3;
extern	statetype s_keenwait4;
extern	statetype s_keenwait5;
extern	statetype s_keenwait6;
extern	statetype s_keenmoon1;
extern	statetype s_keenmoon2;
extern	statetype s_keenmoon3;
extern	statetype s_keengosleep1;
extern	statetype s_keengosleep2;
extern	statetype s_keensleep1;
extern	statetype s_keensleep2;
extern	statetype s_keendie1;
extern	statetype s_keendie2;
extern	statetype s_keendie3;
extern	statetype s_keendie4;
extern	statetype	s_keenlookup;
extern	statetype	s_keenduck;
extern	statetype	s_keendrop;
extern	statetype s_keenreach;
extern	statetype s_keenpole;
extern	statetype s_keenclimb1;
extern	statetype s_keenclimb2;
extern	statetype s_keenclimb3;
extern	statetype s_keenslide1;
extern	statetype s_keenslide2;
extern	statetype s_keenslide3;
extern	statetype s_keenslide4;
extern	statetype s_keenpolethrow1;
extern	statetype s_keenpolethrow2;
extern	statetype s_keenpolethrow3;
extern	statetype s_keenpolethrowup1;
extern	statetype s_keenpolethrowup2;
extern	statetype s_keenpolethrowup3;
extern	statetype s_keenpolethrowdown1;
extern	statetype s_keenpolethrowdown2;
extern	statetype s_keenpolethrowdown3;
extern	statetype	s_keenwalk1;
extern	statetype	s_keenwalk2;
extern	statetype	s_keenwalk3;
extern	statetype	s_keenwalk4;
extern	statetype	s_keenthrow1;
extern	statetype	s_keenthrow2;
extern	statetype	s_keenthrow3;
extern	statetype	s_keenthrow4;
extern	statetype	s_keenthrowup1;
extern	statetype	s_keenthrowup2;
extern	statetype	s_keenthrowup3;
extern	statetype	s_keendive1;
extern	statetype	s_keendive2;
extern	statetype	s_keendive3;
extern	statetype s_keenjumpup1;
extern	statetype s_keenjumpup2;
extern	statetype s_keenjumpup3;
extern	statetype s_keenjump1;
extern	statetype s_keenjump2;
extern	statetype s_keenjump3;
extern	statetype s_keenairthrow1;
extern	statetype s_keenairthrow2;
extern	statetype s_keenairthrow3;
extern	statetype s_keenairthrowup1;
extern	statetype s_keenairthrowup2;
extern	statetype s_keenairthrowup3;
extern	statetype s_keenairthrowdown1;
extern	statetype s_keenairthrowdown2;
extern	statetype s_keenairthrowdown3;
extern	statetype s_keengetup; // not made extern
extern	statetype s_keendie1;
extern	statetype s_doorraise;
extern	statetype s_bonus;
extern	statetype s_bonusrise;
extern	statetype s_broccosmash3;
extern	statetype s_broccosmash4;
extern	statetype s_grapefall;
extern	statetype s_taterattack2;
extern	statetype s_squasherjump2;
extern	statetype s_boobusdie;
extern	statetype s_deathwait1;
extern	statetype s_deathwait2;
extern	statetype s_deathwait3;
extern	statetype s_deathboom1;
extern	statetype s_deathboom2;

static statetype * statetypes[] =
{
	&s_door,
	&s_doorraise,
	&s_flower1,
	&s_flower2,
	&s_flower3,
	&s_flower4,
	&s_flower5,
	&s_flower6,
	&s_poofto1,
	&s_poofto2,
	&s_poofto3,
	&s_poofto4,
	&s_pooffrom1,
	&s_pooffrom2,
	&s_pooffrom3,
	&s_pooffrom4,
	&s_pooffrom5,
	&s_pooffrom6,
	&s_pooffrom7,
	//&s_bonus1,
	//&s_bonus1,
	&s_broccowalk1,
	&s_broccowalk2,
	&s_broccowalk3,
	&s_broccowalk4,
	&s_broccosmash1,
	&s_broccosmash2,
	&s_broccosmash3,
	&s_broccosmash4,
	&s_broccosmash5,
	&s_broccosmash6,
	&s_broccosmash7,
	&s_broccosmash8,
	&s_broccosmash9,
	&s_tomatbounce,
	&s_tomatbounce2,
	&s_carrotwalk1,
	&s_carrotwalk2,
	&s_carrotwalk3,
	&s_carrotwalk4,
	&s_carrotleap,
	&s_asparwalk1,
	&s_asparwalk2,
	&s_asparwalk3,
	&s_asparwalk4,
	&s_grapewait,
	&s_grapefall,
	&s_grapesit,
	&s_graperise,
	&s_taterwalk1,
	&s_taterwalk2,
	&s_taterwalk3,
	&s_taterwalk4,
	&s_taterattack1,
	&s_taterattack2,
	&s_taterattack3,
	&s_cartroll1,
	&s_cartroll2,
	&s_frenchywalk1,
	&s_frenchywalk2,
	&s_frenchywalk3,
	&s_frenchywalk4,
	&s_frenchyrun1,
	&s_frenchyrun2,
	&s_frenchyrun3,
	&s_frenchyrun4,
	&s_frenchythrow1,
	&s_frenchythrow2,
	&s_frenchythrow3,
	&s_fry1,
	&s_fry2,
	&s_melonside,
	&s_melonsidespit,
	&s_melonsidespit2,
	&s_melondown,
	&s_melondownspit,
	&s_melondownspit2,
	&s_melonseed1,
	&s_melonseed2,
	&s_melonseedd1,
	&s_melonseedd2,
	&s_squasherwalk1,
	&s_squasherwalk2,
	&s_squasherjump1,
	&s_squasherjump2,
	&s_squasherwait,
	&s_apelwalk1,
	&s_apelwalk2,
	&s_apelwalk3,
	&s_apelclimb1,
	&s_apelclimb2,
	&s_apelslide1,
	&s_apelslide2,
	&s_apelslide3,
	&s_apelslide4,
	&s_apelfall,
	&s_peabrainfly,
	&s_peabrainwalk1,
	&s_peabrainwalk2,
	&s_peabrainwalk3,
	&s_peabrainwalk4,
	&s_peapodwalk1,
	&s_peapodwalk2,
	&s_peapodwalk3,
	&s_peapodwalk4,
	&s_peapodspit1,
	&s_peapodspit2,
	&s_boobuswalk1,
	&s_boobuswalk2,
	&s_boobuswalk3,
	&s_boobuswalk4,
	&s_boobusjump,
	//&s_deathwait1,
	//&s_deathwait2,
	//&s_deathwait3,
	&s_deathboom1,
	&s_deathboom2,
	&s_deathboom3,
	&s_deathboom4,
	&s_deathboom5,
	&s_deathboom6,
	&s_score,
	&s_flowerpower1,
	&s_flowerpower2,
	&s_boobusbomb1,
	&s_boobusbomb2,
	&s_bombexplode,
	&s_bombexplode2,
	&s_bombexplode3,
	&s_bombexplode4,
	&s_bombexplode5,
	&s_bombexplode6,
	&s_powerblink1,
	&s_powerblink2,
	&s_worldkeen,
	&s_worldkeenwave1,
	&s_worldkeenwave2,
	&s_worldkeenwave3,
	&s_worldkeenwave4,
	&s_worldkeenwave5,
	&s_worldkeenwait,
	&s_worldkeensleep1,
	&s_worldkeensleep2,
	&s_worldwalk,
	&s_keenzee1,
	&s_keenzee2,
	&s_keenzee3,
	//&s_keenzee4,
	//&s_keenzee5,
	&s_keenstand,
	&s_keenpauselook,
	&s_keenyawn1,
	&s_keenyawn2,
	&s_keenyawn3,
	&s_keenyawn4,
	&s_keenwait1,
	&s_keenwait2,
	&s_keenwait3,
	&s_keenwait4,
	&s_keenwait5,
	&s_keenwait6,
	//&s_keenmoon1,
	//&s_keenmoon2,
	//&s_keenmoon3,
	&s_keengosleep1,
	&s_keengosleep2,
	&s_keensleep1,
	&s_keensleep2,
	&s_keendie1,
	&s_keendie2,
	&s_keendie3,
	//&s_keendie4,
	&s_keenlookup,
	&s_keenduck,
	&s_keendrop,
	//&s_keenreach,
	&s_keenpole,
	&s_keenclimb1,
	&s_keenclimb2,
	&s_keenclimb3,
	&s_keenslide1,
	&s_keenslide2,
	&s_keenslide3,
	&s_keenslide4,
	&s_keenpolethrow1,
	&s_keenpolethrow2,
	&s_keenpolethrow3,
	&s_keenpolethrowup1,
	&s_keenpolethrowup2,
	&s_keenpolethrowup3,
	&s_keenpolethrowdown1,
	&s_keenpolethrowdown2,
	&s_keenpolethrowdown3,
	&s_keenwalk1,
	&s_keenwalk2,
	&s_keenwalk3,
	&s_keenwalk4,
	&s_keenthrow1,
	&s_keenthrow2,
	&s_keenthrow3,
	&s_keenthrow4,
	&s_keenthrowup1,
	&s_keenthrowup2,
	&s_keenthrowup3,
	//&s_keendive1,
	//&s_keendive2,
	//&s_keendive3,
	&s_keenjumpup1,
	&s_keenjumpup2,
	&s_keenjumpup3,
	&s_keenjump1,
	&s_keenjump2,
	&s_keenjump3,
	&s_keenairthrow1,
	&s_keenairthrow2,
	&s_keenairthrow3,
	&s_keenairthrowup1,
	&s_keenairthrowup2,
	&s_keenairthrowup3,
	&s_keenairthrowdown1,
	&s_keenairthrowdown2,
	&s_keenairthrowdown3,
	&s_keengetup,
	&s_keendie1,
	&s_doorraise,
	&s_bonus,
	&s_bonusrise,
	&s_broccosmash3,
	&s_broccosmash4,
	&s_grapefall,
	&s_taterattack2,
	&s_squasherjump2,
	&s_boobusdie,
	//&s_deathwait1,
	//&s_deathwait2,
	//&s_deathwait3,
	&s_deathboom1,
	&s_deathboom2
};

#endif

boolean
SaveGame(int file)
{
	word	i,size,compressed,expanded;
	objtype	*o;
	memptr	bigbuffer;

	if (!CA_FarWrite(file,(void far *)&gamestate,sizeof(gamestate)))
		return(false);

	expanded = mapwidth * mapheight * 2;
	MM_GetPtr (&bigbuffer,expanded);

	for (i = 0;i < 3;i++)	// Write all three planes of the map
	{
//
// leave a word at start of compressed data for compressed length
//
		compressed = (word)CA_RLEWCompress ((unsigned short huge *)mapsegs[i]
			,expanded,((unsigned short huge *)bigbuffer)+1,RLETAG);

		*(unsigned short huge *)bigbuffer = compressed;

		if (!CA_FarWrite(file,(void far *)bigbuffer,compressed+2) )
		{
			MM_FreePtr (&bigbuffer);
			return(false);
		}
	}

	for (o = player;o;o = o->next)
	{
		int result;
		int statetypeidx = -1;
		
		// replace the statetype for this object with the index for the type in the statetype list
		// this is a fix for a save/load crash issue due to address layout randomization
		
		for (i = 0; i < sizeof(statetypes) / sizeof(statetype*); ++i)
			if (o->state == statetypes[i])
				statetypeidx = i;
		
		if (statetypeidx == -1)
			result = 0;
		else
		{
			statetype * restore = o->state;
			o->state = (statetype*)(size_t)statetypeidx;
			result = CA_FarWrite(file,(void far *)o,sizeof(objtype));
			o->state = restore;
		}
		
		if (!result)
		{
			MM_FreePtr (&bigbuffer);
			return(false);
		}
	}

	MM_FreePtr (&bigbuffer);
	return(true);
}


boolean
LoadGame(int file)
{
	word			i,j,size;
	objtype			*o;
	short int		orgx,orgy;
	objtype			*prev,*next,*followed;
	unsigned short	compressed,expanded;
	memptr			bigbuffer;

	if (!CA_FarRead(file,(void far *)&gamestate,sizeof(gamestate)))
		return(false);

// drop down a cache level and mark everything, so when the option screen
// is exited it will be cached

	ca_levelbit >>= 1;
	ca_levelnum--;

	SetupGameLevel (false);		// load in and cache the base old level
	titleptr[ca_levelnum] = levelnames[mapon];

	ca_levelbit <<= 1;
	ca_levelnum ++;

	expanded = mapwidth * mapheight * 2;
	MM_GetPtr (&bigbuffer,expanded);

	for (i = 0;i < 3;i++)	// Read all three planes of the map
	{
		if (!CA_FarRead(file,(void far *)&compressed,sizeof(compressed)) )
		{
			MM_FreePtr (&bigbuffer);
			return(false);
		}

		if (!CA_FarRead(file,(void far *)bigbuffer,compressed) )
		{
			MM_FreePtr (&bigbuffer);
			return(false);
		}

		CA_RLEWexpand ((unsigned short huge *)bigbuffer,
			(unsigned short huge *)mapsegs[i],compressed,RLETAG);
	}

	MM_FreePtr (&bigbuffer);

	// Read the object list back in - assumes at least one object in list

	InitObjArray ();
	new = player;
	prev = new->prev;
	next = new->next;
	if (!CA_FarRead(file,(void far *)new,sizeof(objtype)))
		return(false);
	new->prev = prev;
	new->next = next;
	new->state = statetypes[(size_t)new->state];
	new->needtoreact = true;
	new->sprite = NULL;
	new = scoreobj;
	while (true)
	{
		prev = new->prev;
		next = new->next;
		if (!CA_FarRead(file,(void far *)new,sizeof(objtype)))
			return(false);
		followed = new->next;
		new->prev = prev;
		new->next = next;
		new->state = statetypes[(size_t)new->state];
		new->needtoreact = true;
		new->sprite = NULL;

		// mstodo : need to safely restore state ptr. ASLR and different binaries will currently generate different save games..

		if (followed)
			GetNewObj (false);
		else
			break;
	}

	*((int32_t *)&(scoreobj->temp1)) = -1;		// force score to be updated
	scoreobj->temp3 = -1;			// and flower power
	scoreobj->temp4 = -1;			// and lives

	return(true);
}

void
ResetGame(void)
{
	NewGame ();

	ca_levelnum--;
	CA_ClearMarks();
	titleptr[ca_levelnum] = NULL;		// don't reload old level
	ca_levelnum++;
}

#if FRILLS
void
TEDDeath(void)
{
	ShutdownId();
	execlp("TED5.EXE","TED5.EXE","/LAUNCH","KDREAMS",NULL);
}
#endif

static boolean
MoveTitleTo(int offset)
{
	boolean		done;
	int			dir,
				chunk,
				move;
	longword	lasttime,delay;

	if (offset < originxglobal)
		dir = -1;
	else
		dir = +1;

	chunk = dir * PIXGLOBAL;

	done = false;
	delay = 1;
	while (!done)
	{
		lasttime = TimeCount;
		move = delay * chunk;
		if (chunk < 0)
			done = originxglobal + move <= offset;
		else
			done = originxglobal + move >= offset;
		if (!done)
		{
			RF_Scroll(move,0);
			RF_Refresh();
		}
		if (IN_IsUserInput())
			return(true);
		delay = TimeCount - lasttime;
	}
	if (originxglobal != offset)
	{
		RF_Scroll(offset - originxglobal,0);
		RF_Refresh();
	}
	return(false);
}

static boolean
Wait(longword time)
{
	time += TimeCount;
	while ((TimeCount < time) && (!IN_IsUserInput()))
	{
		if (!(TimeCount % MINTICS))
			RF_Refresh();
	}
	return(IN_IsUserInput());
}

static boolean
ShowText(int offset,WindowRec *wr,char *s)
{
	if (MoveTitleTo(offset))
		return(true);

	US_RestoreWindow(wr);
	US_CPrint(s);
	VW_UpdateScreen();

	if (Wait(TickBase * 5))
		return(true);

	US_RestoreWindow(wr);
	US_CPrint(s);
	VW_UpdateScreen();
	return(false);
}

/*
=====================
=
= DemoLoop
=
=====================
*/

void
DemoLoop (void)
{
	char		*s;
	word		move;
	longword	lasttime;
	char *FileName1;
	struct Shape FileShape1;
#if CREDITS
	char *FileName2;
	struct Shape FileShape2;
#endif
	//struct ffblk ffblk; // msfixme : file search
	WindowRec	mywin;
	int bufsave	= bufferofs;
	int dissave	= displayofs;


#if FRILLS
//
// check for launch from ted
//
	if (tedlevel)
	{
		NewGame();
		gamestate.mapon = tedlevelnum;
		GameLoop();
		TEDDeath();
	}
#endif

//
// demo loop
//
	US_SetLoadSaveHooks(LoadGame,SaveGame,ResetGame);
	restartgame = gd_Continue;

	//if (findfirst("KDREAMS.CMP", &ffblk, 0) == -1) // mstodo
	//	Quit("Couldn't find KDREAMS.CMP");

	while (true)
	{

		loadedgame = false;

		FileName1 = "TITLESCR.LBM";
		if (LoadLIBShape("KDREAMS.CMP", FileName1, &FileShape1))
			Quit("Can't load TITLE SCREEN");
#if CREDITS
		FileName2 = "CREDITS.LBM";
		if (LoadLIBShape("KDREAMS.CMP", FileName2, &FileShape2))
			Quit("Can't load CREDITS SCREEN");
#endif

		while (!restartgame && !loadedgame)
		{

			VW_InitDoubleBuffer();
			IN_ClearKeysDown();

			while (true)
			{
				VW_SetScreen(0, 0);
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&FileShape1, 0, 0);
				VW_ScreenToScreen (64*200,0,40,200);
				SYS_Present();

#if CREDITS
				if (IN_UserInput(TickBase * 8, false))
					break;
#else
				if (IN_UserInput(TickBase * 4, false))
					break;
#endif

#if CREDITS
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&FileShape2, 0, 0);
				VW_ScreenToScreen (64*200,0,40,200);

				if (IN_UserInput(TickBase * 7, false))
					break;
#else
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&FileShape1, 0, 0);
				VW_ScreenToScreen (64*200,0,40,200);
				SYS_Present();

				if (IN_UserInput(TickBase * 3, false))
					break;
#endif

				displayofs = 0;
				VWB_Bar(0,0,320,200,FIRSTCOLOR);
				US_DisplayHighScores(-1);
				SYS_Present();

				if (IN_UserInput(TickBase * 6, false))
					break;
			}

			// msnote : added IN_ClearKeysDown call here so we don't accidentally select things in the control panel
			//          after for instance pressing enter on the title screen
			IN_ClearKeysDown();

			bufferofs = bufsave;
			displayofs = dissave;

			VW_FixRefreshBuffer();
			US_ControlPanel ();
		}

		if (!loadedgame)
			NewGame();

		FreeShape(&FileShape1);
#if CREDITS
		FreeShape(&FileShape2);
#endif
		GameLoop();
	}
}
