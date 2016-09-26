//
// Creation:    Gn2System.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Gn2 driver library operating specific definitions.
//
// History:
//
// 05/06/02		rbs     Created file.
//

#if !defined(__Gn2SYSTEM__)
#define __Gn2SYSTEM__

#if defined(KernelLX) || defined(UserLX)
#include "Gn2SystemLX.h"
#endif

#if defined(KernelNT) || defined(UserNT)
#include "Gn2SystemNT.h"
#endif

#if defined(KernelPT) || defined(UserPT)
#include "Gn2SystemPT.h"
#endif

#endif




