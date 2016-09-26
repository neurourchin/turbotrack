//
// Creation:    Gn2Type.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Gn2 Driver Public Type Definitions
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__Gn2TYPE__)
    #define __Gn2TYPE__

    #if !defined(__BFTYPE__)
        #include "BFType.h"
    #endif


	#if !defined(Gn2C)
        #define Gn2C	BFC
    #endif

	#if !defined(Gn2DLL)
		#define Gn2DLL	BFDLL
	#endif 
	
    #if !defined(Gn2CAPI)
        #define Gn2CAPI	BFCAPI
    #endif

    typedef Bd			Gn2;				// Gn2 board handle.

    typedef BFRC		Gn2RC, *Gn2RC_Ptr;	// Gn2 return code.    

	typedef PBFCNF		PGn2CAM;			// Configuration specific type for Gn2 cameras.

#endif

