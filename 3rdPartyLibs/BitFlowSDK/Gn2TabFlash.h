//
// Creation:    Gn2TabFlash.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Gn2 Flash Register Id Definitons
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__Gn2TABFLASH__)
#define __Gn2TABFLASH__

// Flash Filter Flags for Gn2

typedef enum _Gn2FlashFilter
{
	CytonFlash70	= 0x00000001,			// Cyton with FPGA 70.
	CytonFlash110	= 0x00000002,			// Cyton with FPGA 110
	AxionFlash1XE	= 0x00000004,			// Axion 1XE
	AxionFlash2XE	= 0x00000008,			// Axion 2XE
	AxionFlash2XB	= 0x00000010,			// Axion 2XB
	AxionFlash4XB	= 0x00000020,			// Axion 4XB
} Gn2FlashFilter;

//
// Flash file Id codes for all Gn2 devices.
// these must be in the same order as the FlashEntry calls.
//

typedef enum _Gn2FlashId
{	
	FLASH_CTN70MUX = 0,
	FLASH_CTN110MUX,
	FLASH_AXN1XEMUX,
	FLASH_AXN2XEMUX,
	FLASH_AXN2XBMUX,
	FLASH_AXN4XBMUX,

	FLASH_COUNT_GN2								// Number of flash file types. 
} Gn2FlashId;

#endif
