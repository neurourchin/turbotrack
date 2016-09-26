/***************************************************************************
*
* Gn2Config.h
*
* Definitions of data structures to support configuration of Gn2 system
*
* Copyright (C) 2002 by BitFlow, Inc.  All Rights Reserved.
*
* 05/29/02	rbs		Cloned from R2Config.h.
*
***************************************************************************/

#if !defined(__Gn2CONFIG__) && !defined(KernelOS)
#define __Gn2CONFIG__

#include "Gn2Type.h"
#include "BFEntTrans.h"


// header signature 
#define Gn2CNF_NREGS			132


/*
* Camera description defines
*/
#define Gn2CNF_FORM_LINEFORMAT_MASK		0x00000007
#define Gn2CNF_FORM_NONINTERLACED		0x00000001
#define Gn2CNF_FORM_DATAFORMAT_MASK		0x00000070
#define Gn2CNF_FORM_BI_SERIAL			0x00000010	// two serial pixels
#define Gn2CNF_FORM_TRY_SERIAL			0x00000020	// three serial pixels
#define Gn2CNF_FORM_QUAD_SERIAL			0x00000040	// four serial pixels


#endif // __Gn2CONFIG__
