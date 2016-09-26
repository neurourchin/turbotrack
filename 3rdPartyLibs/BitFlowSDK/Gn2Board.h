//
// Creation:    Gn2Board.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Gn2 Board Definitions  
//
// History:
//
// 05/06/02     rbs     Created.
// 

#ifndef __Gn2BOARD__
#define __Gn2BOARD__ 

#include "BFSystem.h"
#include "BFDef.h"
#include "BFBoard.h"
#include "BFTabError.h"

// Sizes of various memory chunks.

#define GN2HCTABSIZE						BFGN2HCTABSIZE		// Number of horizontal CTab entries in CTab table.
#define GN2VCTABSIZE						BFGN2VCTABSIZE		// Number of vertical CTab entries in CTab table.
#define Gn2DPMSIZE							(128 * 1024)		// Size of the Gn2 DPM memory in bytes words. 
#define Gn2KBN2DDPMSIZE						(64 * 1024)			// Size of the Karbon 2 DPM memory in bytes words. 
#define Gn2KBN4DDPMSIZE						(64 * 1024)			// Size of the Karbon 4 DPM memory in bytes words. 	
#define Gn2KBN2FDPMSIZE						(128 * 1024)		// Size of the Karbon 2 DPM memory in bytes words. 
#define Gn2KBN4FDPMSIZE						(128 * 1024)		// Size of the Karbon 4 DPM memory in bytes words. 	

#define Gn2NEONDPMSIZE						(16 * 1024)			// Size of the Neon DPM memory in bytes words. 
#define Gn2ALTADPMSIZE						(16 * 1024)			// Size of the Alta DPM memory in bytes words. //NEEDSWORK, set actual size
#define Gn2NUMCTABCOLS						16
#define Gn2HCTABJUMP						0x2000
#define Gn2VCTABJUMP						0x8000
#define Gn2PCPHCI							0x08
#define Gn28BITLUTSIZE						0x100
#define Gn2NUMLUTBANKS						4
#define RLECTABHBASE						0					// location of first entry in horzonatal RLE CTABs
#define RLECTABVBASE						256					// location of first entry in vertical RLE CTABs
#define RLEHCTABSIZE						16					// number of entries in the horiztonal RLE CTab
#define RLEVCTABSIZE						16					// number of entries in the vertical RLE CTab
#define RLECTABRESETH						1 << 25				// bit in the Horiztonal RLE CTabs that causes a reset	
#define RLECTABRESETV						1 << 25				// bit in the Horiztonal RLE CTabs that causes a reset	

// Structures

// Entry record for a BitFlow board found in the system.

typedef BFENTRY Gn2ENTRY, *PGn2ENTRY;

// Gn2 interrupt signal.

#if !defined(KernelOS)

typedef BFSIGNAL Gn2SIGNAL, *PGn2SIGNAL;

#endif

#endif
