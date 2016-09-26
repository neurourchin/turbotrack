//
// Creation:    Gn2Info.h
// Created:     May 28, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Gn2 Public Definitions
//
// History:
//
// 05/28/02     rbs     Created file.
//

#if !defined(__Gn2INFO__)
#define __Gn2INFO__

#if !defined(__BFSYSTEM)
#include "BFSystem.h"
#endif

#if !defined(__Gn2TYPE__)
#include "Gn2Type.h"
#endif

// Registry key paths.

#ifdef LINX_BUILD_TARGET
	#define CTN_ROOT						"System\\CurrentControlSet\\Services\\LinX\\Ginga"
	#define CTN_DEVICE						"GingaDev"

	#define CTN_FAMILY						"Ginga"
	#define CTN_TOKEN						"GINGADG"
	#define CTN_CONFIG_PATH					"GingaDGe"
	#define CTN_CAMFILE_EXT					".gdg"
	#define CTN_CAMFILE_FOLDER				"\\GingaDGe"

#else
	#define GN2_ROOT						"System\\CurrentControlSet\\Services\\BitFlow\\GN2"
	#define GN2_DEVICE						"GN2Dev"
	#define GN2_FAMILY						"GN2"
	#define GN2_TOKEN						"GN2"

	#define CTN_CONFIG_PATH					"CTN"
	#define CTN_CAMFILE_EXT					".bfml"
	#define CTN_CAMFILE_FOLDER				"\\CTN"

	#define AXN_CONFIG_PATH					"AXN"
	#define AXN_CAMFILE_EXT					".bfml"
	#define AXN_CAMFILE_FOLDER				"\\AXN"

#endif


// Standard Pseudo Device

#define CTN_PSEUDO_VENDOR_ID			BF_PCI_VEN_ID
#define CTN_PSEUDO_DEVICE_ID			0x7000
#define CTN_PSEUDO_SUB_VENDOR_ID		0x0000
#define CTN_PSEUDO_SUB_SYSTEM_ID		0x0000

// Alta-AN Psuedo Device
#define ALTA_PSEUDO_VENDOR_ID			BF_PCI_VEN_ID
#define ALTA_PSEUDO_DEVICE_ID			0x5000
#define ALTA_PSEUDO_SUB_VENDOR_ID		0x0000
#define ALTA_PSEUDO_SUB_SYSTEM_ID		0x0000
#define ALTA_PSEUDO_INFO_HI				0x1000
#define ALTA_PSEUDO_INFO_LO				0x0000

// Alta-CO Psuedo Device
#define ALTACO_PSEUDO_VENDOR_ID			BF_PCI_VEN_ID
#define ALTACO_PSEUDO_DEVICE_ID			0x6000
#define ALTACO_PSEUDO_SUB_VENDOR_ID		0x0000
#define ALTACO_PSEUDO_SUB_SYSTEM_ID		0x0000
#define ALTACO_PSEUDO_INFO_HI			0x1000
#define ALTACO_PSEUDO_INFO_LO			0x0000

// Karbon-CXP Psuedo Device
#define KCXP_PSEUDO_VENDOR_ID			BF_PCI_VEN_ID
#define KCXP_PSEUDO_DEVICE_ID			0x3001
#define KCXP_PSEUDO_SUB_VENDOR_ID		0x0000
#define KCXP_PSEUDO_SUB_SYSTEM_ID		0x0000
#define KCXP_PSEUDO_INFO_HI				0x0000
#define KCXP_PSEUDO_INFO_LO				0x0000

// Interrupt Flag Bits

#define GN2_INT_FLAG_CTAB				0x0001
#define GN2_INT_FLAG_OVSTEP				0x0002
#define GN2_INT_FLAG_HW					0x0004
#define GN2_INT_FLAG_TRIG				0x0008
#define GN2_INT_FLAG_SER				0x0010
#define GN2_INT_FLAG_QUAD				0x0020
#define GN2_INT_FLAG_EOF				0x0040
#define GN2_INT_FLAG_CXP				0x0080

#define GN2_INT_FLAG_GN2				0x1000
#define GN2_INT_FLAG_QL					0x2000
#define GN2_INT_FLAG_OTHERS				0x4000

#define GN2_INT_MASK_BOARD_INTS			0x0fff		// Mask for board interrupts that must be fully processed. 

// QTab Attributes

#define GN2_DMA_QUAD_LOCAL_ONCEONLY		BF_DMA_QUAD_LOCAL_ONCEONLY

// QTab Next Quad State Bits

#define GN2_DMA_QUAD_NEXT_HOST			BF_DMA_QUAD_NEXT_HOST
#define GN2_DMA_QUAD_NEXT_EOC			BF_DMA_QUAD_NEXT_EOC
#define GN2_DMA_QUAD_NEXT_INT			BF_DMA_QUAD_NEXT_INT
#define GN2_DMA_QUAD_NEXT_WRITE			BF_DMA_QUAD_NEXT_WRITE

// Maximum Number of Fields

#define GN2_NUMFIELDS					1

#if !defined(KernelOS)

// User level Gn2 information.

typedef struct _Gn2InfoUsr
{

	PBFVOID pCurQTab;				// void version of pointer to current (most recent write) QTAB
	PBFVOID pAqQTab;				// void version of pointer to AqSetup() allocated QTABS
	PBFVOID pCurAqSig;				// void version of pointer to current signal used for high level acquisition

} Gn2InfoUsr, *pGn2InfoUsr;

// Useful macros to get things out of the device info block.

#define GetGn2Info(BoardId) (BoardId == BFNULL ? BFNULL : ((pBFInfoUsr)BoardId)->pXXInfoUsr == BFNULL ? BFNULL : (pGn2InfoUsr)((pBFInfoUsr)BoardId)->pXXInfoUsr)

#endif

#if defined(KernelOS)

// Kernel level Gn2 information.

typedef struct _Gn2InfoKrn
{
    BFBOOL		BoardTest;			// Test flag read from the registry.
	BFBOOL		Stop00All;			// Set True to enable exit after driver builds R2Info.
} Gn2InfoKrn, *pGn2InfoKrn;


// Useful macros to get things out of the device info block.

#define GetGn2Info(BoardId) (BoardId == BFNULL ? BFNULL : ((pBFInfoKrn)BoardId)->pXXInfoKrn == BFNULL ? BFNULL : (pGn2InfoKrn)((pBFInfoKrn)BoardId)->pXXInfoKrn)

#endif

#endif
