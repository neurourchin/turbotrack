//
// Creation:    Gn2ApiPrv.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Kernel Driver API Gn2 Board Access Functions
//
// History:
//
// 05/06/02     rbs     Created file.
//

#ifndef __Gn2APIPRV__
#define __Gn2APIPRV__

#include "Gn2Info.h"

#ifdef __cplusplus
extern "C" {
#endif

// DMA

Gn2DLL BFBOOL	Gn2CAPI	Gn2DMAActive(Gn2 Board);
Gn2DLL Gn2RC	Gn2CAPI	Gn2DMAStart(Gn2 Board, BFU32 Timeout, PBFBOOL pTimedOut);
Gn2DLL Gn2RC	Gn2CAPI	Gn2DMAStop(Gn2 Board, BFU32 Timeout, PBFBOOL pTimedOut);


#if !defined(KernelOS)

// Board

Gn2DLL Gn2RC	    Gn2CAPI Gn2BoardInitialize(Gn2 Board, PGn2CAM pCam);  

// Miscellaneous

  
Gn2DLL Gn2RC		Gn2CAPI Gn2Camera2Board(Gn2 Board, PGn2CAM pCam);

#endif


#if defined(KernelOS)

// Kernel Only Functions

// Callback functions

Gn2DLL Gn2RC		Gn2EngineResetHook(Gn2 Board);
Gn2DLL BFU32		Gn2IntDetect(Gn2 Board);
Gn2DLL BFBOOL		Gn2IntReset(Gn2 Board, BFU32 Status);
Gn2DLL void			Gn2IntUpdate(Gn2 Board, BFU32 Status, BFU64 Stamp);
Gn2DLL BFU32		Gn2IntDetect(Gn2 Board);
Gn2DLL BFBOOL		Gn2IntReset(Gn2 Board, BFU32 Status);
Gn2DLL void			Gn2IntUpdate(Gn2 Board, BFU32 Status, BFU64 Stamp);
Gn2DLL Gn2RC		Gn2Kill(Gn2 Board);

// Individual Interrupt Reset Functions
BFVOID		Gn2ResetEOD(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetVAq(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetYAq(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetVStart(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetZStart(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetYStart(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetEncB(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetEncA(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetTrig(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetBMError(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetAELossOfSync(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetPCIEPktDropped(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetCXP(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetOthers(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetSerial(Bd Board, BFU32 IntType);
BFVOID		Gn2ResetCXPOffsets(Bd Board, BFU32 IntType);
#endif // KernelOS

#ifdef __cplusplus
}
#endif

#endif


