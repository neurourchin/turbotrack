//
// Creation:    Gn2Def.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Gn2 Public Definitions
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__Gn2DEF__)
#define __Gn2DEF__

#include "BFDef.h"

// Sizes

#define Gn2CTAB_MAXADDR		(128 * 1024)

// General Purpose Output Pins

typedef enum _Gn2GPOutPin
{
    Gn2GPOut0	= BFGPOut0,
    Gn2GPOut1	= BFGPOut1,
    Gn2GPOut2	= BFGPOut2,
    Gn2GPOut3	= BFGPOut3,
    Gn2GPOut4	= BFGPOut4,
    Gn2GPOut5	= BFGPOut5,
    Gn2GPOut6	= BFGPOut6,
    Gn2GPOut7	= BFGPOut7,
    Gn2GPOut8	= BFGPOut8,
    Gn2GPOut9	= BFGPOut9,
    Gn2GPOut10	= BFGPOut10,
    Gn2GPOut11	= BFGPOut11,
} Gn2GPOutPin, *Gn2GPOutPinPtr;




// ctabs

typedef enum _Gn2CTabControl
{
    Gn2CTab				= BFCTab,
    Gn2HCTab			= BFHCTab,
    Gn2VCTab			= BFVCTab,
    Gn2HCTabHStart		= BFHCTab0,
    Gn2HCTabHReset		= BFHCTab1,
    Gn2HCTabENHLoad		= BFHCTab2,
    Gn2HCTabReserved	= BFHCTab3,
    Gn2HCTabGPH0		= BFHCTab4,
    Gn2HCTabGPH1		= BFHCTab5,
    Gn2HCTabGPH2		= BFHCTab6,
    Gn2HCTabGPH3		= BFHCTab7,
    Gn2VCTabVStart		= BFVCTab0,
    Gn2VCTabVReset		= BFVCTab1,
    Gn2VCTabENVLoad		= BFVCTab2,
    Gn2VCTabIRQ			= BFVCTab3,
    Gn2VCTabGPV0		= BFVCTab4, 
    Gn2VCTabGPV1		= BFVCTab5,
    Gn2VCTabGPV2		= BFVCTab6,
    Gn2VCTabGPV3		= BFVCTab7,
} Gn2CTabControl, *Gn2CTabControlPtr;

#endif

