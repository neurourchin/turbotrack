//
// Creation:    Gn2EntryKrn.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Gn2 Kernel Level DriverEntry Definitions
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__Gn2ENTRYKRN__)
#define __Gn2ENTRYKRN__

#if !defined(__BFSYSTEM__)
#include "BFSystem.h"
#endif

#if !defined(__Gn2TYPE__)
#include "Gn2Type.h"
#endif

//
// Global Functions
//

Gn2RC Gn2C Gn2Build(Gn2 Board, DrvStates State);

#endif


