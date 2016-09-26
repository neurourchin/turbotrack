/***************************************************************************
*
* FILE: BFErApi.h
*
* PURPOSE: Public interface to error dialog DLL
*
* LEGAL THINGS:
*
* Copyright (C) 1996 by BitFlow, Inc.  All Rights Reserved.
*
* REVISION HISTORY:
*
* 08/29/96	rjd - created
*
***************************************************************************/

#ifndef __BFERAPI__
#define __BFERAPI__

#include "BFDef.h"

#ifdef __cplusplus
extern "C" {
#endif

BFDLL BFBOOL BFCAPI DisplayAboutDialog(PBFCHAR AppName, PBFCHAR Purpose);
BFDLL BFBOOL BFCAPI DisplayErrorDialog(BFS32 ErrorCode, PBFCHAR ErrorSource, BFU32 ErrorLine, PBFCHAR ErrorMess, PBFUPTR pDisposition);
BFDLL BFBOOL BFCAPI BFEVersion(PBFU32 pMajorVersion, PBFU32 pMinorVersion);
BFDLL BFUPTR BFCAPI DoBrdOpenDialog(BFU32 Options, BFU32 FamilyFilter, PBFU32 pFamily, PBFU32 pBrdNum, PBFU32 pDoInit,PBFU32 pSerPortNum);
BFDLL BFBOOL BFCAPI WaitDialogOpen(PBFCHAR Msg, HWND *pHandle);
BFDLL BFBOOL BFCAPI WaitDialogClose(HWND Handle);
BFDLL BFBOOL BFCAPI DisplayQuestionDialog(PBFCHAR Question,PBFCHAR Answer,BFSIZET AnswerSize);
BFDLL BFBOOL BFCAPI OneTimeMessageDialog(PBFCHAR Message, PBFBOOL pNeverAgain);
BFDLL BFBOOL BFCAPI ProgressDailogClose(HWND Handle);
BFDLL BFBOOL BFCAPI ProgressDailogUpdate(HWND Handle, BFU32 Progress);
BFDLL BFBOOL BFCAPI ProgressDailogOpen(PBFCHAR Msg, BFU32 ProgessMax, HWND *pHandle);
BFDLL BFBOOL BFCAPI ChoiceDialog(PBFCHAR *ChoiceList, BFU32 NumChoices, BFU32 CurrentChoiceIndex, PBFCHAR Choice, BFSIZET ChoiceSize);

#ifdef __cplusplus
}
#endif

#endif
