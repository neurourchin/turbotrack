/***************************************************************************
*
* FILE: BFIOApi.h
*
* PURPOSE: Public interface into Disk IO dll
*
* LEGAL THINGS:
*
* Copyright (C) 2002 by BitFlow, Inc.  All Rights Reserved.
*
* REVISION HISTORY:
*
* 10/23/2002	sms - created
*
***************************************************************************/


#ifndef __BFIOAPI__
#define __BFIOAPI__

#include "BFDef.h"
#include "BFIODef.h"

#ifdef __cplusplus
extern "C" {
#endif

// Dialog to specify a file name to save
BFDLL BFU32 BFCAPI BFIOSaveDlg(BFBOOL SingleFrame, char* FileName, BFSIZET FileNameSize);

// write a single file to disk
BFDLL BFU32	BFCAPI BFIOWriteSingle(char* FileName, PBFU32 pBuffer, 
									 BFU32 XSize, BFU32 YSize, 
									 BFU32 BitDepth, BFU32 Options);

// write a sequence of files to disk
BFDLL BFU32	BFCAPI BFIOWriteMultiple(char* FileName, PBFU32 *pBufArray,
					BFU32 StartNum,	BFU32 XSize, BFU32 YSize, 
					BFU32 BitDepth,	BFU32 NumBuffers, BFU32 Options);

// read a single file from disk
BFDLL BFU32	BFCAPI BFIOReadSingle(char* FileName, PBFU32 pBuffer, 
							        BFU32 XSize, BFU32 YSize, BFU32 BitDepth);

// read a sequence of files from disk
BFDLL BFU32	BFCAPI BFIOReadMultiple(char* FileName, PBFU32 *pBufArray,
									  BFU32 XSize, BFU32 YSize, BFU32 BitDepth,
									  BFU32 NumBuffers, BFU32 AVIStartFrame);

// read the parameter info from a file on disk
BFDLL BFU32 BFCAPI BFIOReadParameters(char* FileName, PBFU32 XSize, PBFU32 YSize, 
									  PBFU32 BitDepth, PBFU32 NumFrames);

// Retrieve a new BFIOFileParams object.
BFDLL PBFIOParams BFCAPI    BFIOMakeExParams        ( BFVOID );

// Set the BFIOParams object to the "default" state.
BFDLL BFU32 BFCAPI          BFIOClearExParams       ( PBFIOParams Params );

// Free private data associated with the BFIOFileParams instance. Call once, when done using the BFIOFileParams instance.
BFDLL BFU32 BFCAPI          BFIOFreeExParams        ( PBFIOParams Params );

// Write a single 
BFDLL BFU32 BFCAPI          BFIOWriteSingleEx       ( char* FileName
                                                    , PBFU32 pBuffer
                                                    , BFU32 XSize
                                                    , BFU32 YSize
                                                    , BFU32 BitDepth
                                                    , BFU32 Options
                                                    , PBFIOParams Params );

/* Method to retrieve the basic parameters for an input image file. Any read parameter (pXSize, pYSize, pBitDepth,
 * pNumFrames, and params) may be provided as null if unrequired, and hence are optional. */
BFDLL BFU32 BFCAPI          BFIOReadParametersEx    ( char* FileName
                                                    , PBFU32 pXSize
                                                    , PBFU32 pYSize
                                                    , PBFU32 pBitDepth
                                                    , PBFU32 pNumFrames
                                                    , PBFIOParams Params );

BFDLL BFU32 BFCAPI          BFIOReadSingleEx        ( char* FileName, PBFU32 pBuffer
                                                    , BFU32 XSize
                                                    , BFU32 YSize
                                                    , BFU32 BitDepth
                                                    , PBFIOParams Params );

// Dialog to retreive a file 
BFDLL BFU32	BFCAPI BFIOOpenDlg(char* FileName, BFSIZET FileNameSize);

// Show error code details in a dialog box
BFDLL BFU32 BFCAPI BFIOErrorShow( BFU32 ErrorCode);

/* BFIOErrorGetMes -- Retrieve the error text associated with a BFIO error code.
 *  ErrorCode       -- The BFIO error code. If the provided value isn't in the
 *                     DiskIOErr table, we fail and return BF_ER_UNKNOWN_ERROR_CODE.
 *  Message         -- Pointer to the output string buffer. May be provided as a
 *                     null pointer, to retrieve just the pMessageBufSize. Message
 *                     is filled as completely as possible, even if shorter than
 *                     the total message length
 *  pMessageBufSize -- Pointer to the message buffer size. On input, this should
 *                     be the size of the Message buffer (if Message is non-null).
 *                     On output, this is set to the total size of the error message,
 *                     including the null terminator.
 *  Returns         -- BF_OK, BF_ER_UNKNOWN_ERROR_CODE, BF_ER_BAD_BUFFER_LENGTH
 */
BFDLL BFU32 BFCAPI BFCAPI BFIOErrorGetMes(BFU32 ErrorCode, PBFCHAR Message, PBFU32 pMessageBufSize);

// Return the dll version
BFDLL BFRC BFCAPI BFIOVersion(PBFU32 pMajorVersion,PBFU32 pMinorVersion);

#ifdef __cplusplus
}
#endif

#endif /* __BFIOAPI__ */
