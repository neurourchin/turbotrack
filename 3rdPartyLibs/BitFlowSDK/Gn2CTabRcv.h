//
// Creation:    Gn2CTabRcv.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Gn2 CTab Receive From Dispatch 
//
// Dispatch handling function prototypes.
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__Gn2CTABRCV__)
#define __Gn2CTABRCV__

#if !defined(__BFSYSTEM__)
#include "BFSystem.h"
#endif

#if !defined(__Gn2CTABBTH__)
#include "Gn2CTabBth.h"
#endif

#if !defined(__BFMEMORYBTH__)
#include "BFMemoryBth.h"
#endif

//
// Global Functions
//

extern BFBOOL Gn2C Gn2DR_CTabPeek(PBFVOID Buf, Bd KernelId, PIRP Irp, BFU32 InSize, BFU32 OutSize);   
extern BFBOOL Gn2C Gn2DR_CTabPoke(PBFVOID Buf, Bd KernelId, PIRP Irp, BFU32 InSize, BFU32 OutSize);   
extern BFBOOL Gn2C Gn2DR_CTabRead(PBFVOID Buf, Bd KernelId, PIRP Irp, BFU32 InSize, BFU32 OutSize);   
extern BFBOOL Gn2C Gn2DR_CTabWrite(PBFVOID Buf, Bd KernelId, PIRP Irp, BFU32 InSize, BFU32 OutSize);   
extern BFBOOL Gn2C Gn2DR_CTabFill(PBFVOID Buf, Bd KernelId, PIRP Irp, BFU32 InSize, BFU32 OutSize);   
extern BFBOOL Gn2C Gn2DR_CTabRamp(PBFVOID Buf, Bd KernelId, PIRP Irp, BFU32 InSize, BFU32 OutSize);   

#endif

