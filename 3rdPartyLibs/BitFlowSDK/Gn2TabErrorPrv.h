//
// Creation:    Gn2TabErrorPrv.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Gn2 Error Table Private Definitons
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__Gn2TABERRORPRV__)
#define __Gn2TABERRORPRV__

#if !defined(__BFTABERRORPRV__)
#include "BFTabErrorPrv.h"
#endif

// Global Data

extern ErrorRec			Gn2Errors[];			// Table of Gn2 error records.
extern BFU32			Gn2ErrorRecords;		// Number of error records in Gn2Errors.

#endif

