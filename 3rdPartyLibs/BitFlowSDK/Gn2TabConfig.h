//
// Creation:    Gn2TabConfig.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Gn2 Device Configuration Definitons
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__Gn2TABCONFIG__)
#define __Gn2TABCONFIG__

#include "Gn2Type.h"

// InfoHi
#define BF_PCI_KBN_NUM_CFGS		0xF000			// Number of configuration spaces
#define BF_PCI_KBN_DRCT_DWNLD	0x0800			// Set to 1 for direct download
#define BF_PCI_KBN_INFO_SRC		0x0010			// Source of INFOLO and INFOHI (1 = downloader, 0 = registry)
#define BF_PCI_KBN_IP_MASK		0x000f			// Custom MUX tag number bit mask.
#define BF_PCI_KBN_IP_SHIFT		0				// Custom MUX tag number shift count.

// SubVenderID

//  Options Information Record.

typedef struct _Gn2OpsRec
{
	BFBOOL	Slave;								// True for Slave VFGs on Karbon
	BFBOOL	NoDownload;							// True if board should not be downloaoded
	BFBOOL	DirectDownload;						// True if board support direct download (no NIOS downloader)
	BFU32	DoBlockWrite;
	BFU32	MUX;								// MUX tag number.
	BFU32	DCC;								// DCC tag number.
} Gn2OpsRec, *Gn2OpsPtr;

// Useful macro to pull the device specific options out of the VFO record.

#define GetGn2Ops(pVFO)	(pVFO == BFNULL || (pVFO->Family & FF_GN2) == 0 ? BFNULL : (Gn2OpsPtr)&pVFO->OpSpace[0])

#endif
