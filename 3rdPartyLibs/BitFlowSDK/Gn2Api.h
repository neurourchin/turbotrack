//
// Creation:    Gn2Api.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Gn2 API Generic Board Access Functions    
//
// History:
//
// 05/06/02     rbs     Created.
// 

#ifndef __Gn2API__
#define __Gn2API__

#include "BFDef.h"
#include "Gn2Type.h"
#include "Gn2Def.h"
#include "Gn2Board.h"
#include "Gn2TabError.h"
#include "Gn2Config.h"
#include "Gn2Info.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(KernelOS)

// System Open and Initialization
	
Gn2DLL Gn2RC	Gn2CAPI Gn2SysBoardFindByNum(BFU32 Number, PGn2ENTRY pEntry);
Gn2DLL Gn2RC	Gn2CAPI Gn2BrdOpen(PGn2ENTRY pEntry,Gn2 *pBoard, BFU32 Mode);
Gn2DLL Gn2RC	Gn2CAPI Gn2BrdOpenCam(PGn2ENTRY pEntry, Gn2 *pBoard, BFU32 Mode, PBFCHAR ForceCamFile);
Gn2DLL Gn2RC	Gn2CAPI Gn2BrdCamSel(Gn2 Board, BFU32 CamIndex, BFU32 Mode);
Gn2DLL Gn2RC	Gn2CAPI Gn2BrdCamSetCur(Gn2 pBoard, PGn2CAM pCam, BFU32 Mode);
Gn2DLL Gn2RC	Gn2CAPI Gn2BrdInquire(Gn2 Board, BFU32 Member, PBFU32 pVal);
Gn2DLL Gn2RC	Gn2CAPI Gn2BrdClose(Gn2 Board);
Gn2DLL Gn2RC	Gn2CAPI Gn2BrdAqTimeoutSet(Gn2 Board, BFU32 Timeout);
Gn2DLL Gn2RC	Gn2CAPI Gn2BrdAqSigGetCur(Gn2 Board, PBFVOID *pAqSig);
Gn2DLL Gn2RC	Gn2CAPI Gn2BrdAqSigSetCur(Gn2 pBoard, PBFVOID pAqSig);

Gn2DLL Gn2RC	Gn2CAPI Gn2BrdCamGetCur(Gn2 Board, PGn2CAM *pCam);
Gn2DLL Gn2RC	Gn2CAPI Gn2BrdCamGetFileName(Gn2 Board, BFU32 Num, PBFCHAR CamName, BFSIZET CamNameStLen);
Gn2DLL Gn2RC	Gn2CAPI Gn2BrdCamGetMMM(Gn2 Board,PBFCHAR Make, BFU32 MakeStrSize, PBFCHAR Model, BFU32 ModelStrSize, PBFCHAR Mode, BFU32 ModeStrSize);

Gn2DLL Gn2RC	Gn2CAPI Gn2DrvOpen(Gn2 *pBoard, BFU32 Mode);
Gn2DLL Gn2RC	Gn2CAPI Gn2DrvClose(Gn2 Board);

// Acquisition

Gn2DLL Gn2RC	Gn2CAPI Gn2AqSetup(Gn2 Board, PBFVOID pDest, BFU32  DestSize, BFS32 Stride,BFU32 DestType);
Gn2DLL Gn2RC	Gn2CAPI Gn2AqCommand(Gn2 Board,BFU32 Command, BFU32 Mode);
Gn2DLL Gn2RC	Gn2CAPI Gn2AqCleanUp(Gn2 Board);
Gn2DLL Gn2RC	Gn2CAPI Gn2AqWaitDone(Gn2 Board);
Gn2DLL Gn2RC	Gn2CAPI Gn2AqReengage(Gn2 Board);

Gn2DLL Gn2RC	Gn2CAPI Gn2AqFrameSize(Gn2 Board,BFU32 XSize,BFU32 YSize);
Gn2DLL Gn2RC	Gn2CAPI Gn2AqROISet(Gn2 Board, BFU32 XOffset, BFU32 YOffset, BFU32 XSize, BFU32 YSize);

// Camera Configuration

Gn2DLL Gn2RC	Gn2CAPI Gn2CamOpen(Gn2 Board, PBFCHAR CamName, PGn2CAM *pCam);
Gn2DLL Gn2RC	Gn2CAPI Gn2CamInquire(Gn2 Board,PGn2CAM pCam,BFU32 Member, PBFU32 pVal);
Gn2DLL Gn2RC	Gn2CAPI Gn2CamClose(Gn2 Board, PGn2CAM pCam);
Gn2DLL Gn2RC	Gn2CAPI Gn2CamAqTimeoutSet(Gn2 Board,PGn2CAM pCam, BFU32 Timeout);
Gn2DLL Gn2RC	Gn2CAPI Gn2CamModesEnum(Gn2 Board, PGn2CAM pCam, BFU32 Index, PBFCHAR ModeName, BFU32 ModeNameSize, PBFCHAR ModeComment, BFU32 ModeCommentSize);
Gn2DLL Gn2RC	Gn2CAPI Gn2CamModeGet(Gn2 Board, PBFCHAR ModeName, BFSIZET ModeNameSize);
Gn2DLL Gn2RC	Gn2CAPI Gn2CamModeSet(Gn2 Board, PGn2CAM pCam, PBFCHAR ModeName);

// Interrupt Signals

Gn2DLL Gn2RC	Gn2CAPI Gn2SignalCreate(Gn2 Board, BFU32 Type, PGn2SIGNAL pSignal);
Gn2DLL Gn2RC	Gn2CAPI Gn2SignalWait(Gn2 Board, PGn2SIGNAL pSignal, BFU32 TimeOut, PBFU32 pNumInts);
Gn2DLL Gn2RC	Gn2CAPI Gn2SignalNextWait(Gn2 Board, PGn2SIGNAL pSignal, BFU32 TimeOut);
Gn2DLL Gn2RC	Gn2CAPI Gn2SignalCancel(Gn2 Board, PGn2SIGNAL pSignal);
Gn2DLL Gn2RC	Gn2CAPI Gn2SignalQueueSize(Gn2 Board, PGn2SIGNAL pSignal, PBFU32 pNumInts);
Gn2DLL Gn2RC	Gn2CAPI Gn2SignalQueueClear(Gn2 Board, PGn2SIGNAL pSignal);
Gn2DLL Gn2RC	Gn2CAPI Gn2SignalFree(Gn2 Board, PGn2SIGNAL pSignal);

// Quad Table
Gn2DLL Gn2RC	Gn2CAPI Gn2QTabCreate(Gn2 Board,PGn2CAM pCam,PBFVOID pDest,BFU32 BufferSize,BFS32 Stride,VQTabHeadPtr pVirtQTabHead,BFU32 DestType,BFU32 Options);
Gn2DLL Gn2RC	Gn2CAPI	Gn2QTabFree(Gn2 Board,VQTabHeadPtr pVirtQTabHead);


// Mid Level Control

Gn2DLL Gn2RC	Gn2CAPI Gn2ConAqMode(Gn2 Board,BFU32 DestType);
Gn2DLL Gn2RC	Gn2CAPI Gn2LastLine(Gn2 Board,PBFU32 pCurLine);

// Miscellaneous

Gn2DLL Gn2RC	Gn2CAPI Gn2Shutdown(Gn2 Board);  

// Version Control

Gn2DLL Gn2RC	Gn2CAPI Gn2DVersion(PBFU32 pMajorVeraion,PBFU32 pMinorVersion);

#endif // !defined(KernelOS)

// Data Control

Gn2DLL Gn2RC	Gn2CAPI Gn2ConGPOutSet(Gn2 Board, BFU32 GPout, BFU32 Level); 
Gn2DLL Gn2RC	Gn2CAPI Gn2ConSwTrig(Gn2 Board, BFU32 AssertType); 

// Mid Level Control Functions

Gn2DLL Gn2RC	Gn2CAPI Gn2ConAqCommand(Gn2 Board,BFU32 Command);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConAqStatus(Gn2 Board,PBFU32 pStatus);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConInt(Gn2 Board,BFU32 IntType,BFU32 Action);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConNumFramesSet(Gn2 Board, BFU32 NumFrames);
Gn2DLL Gn2RC	Gn2CAPI Gn2DMAProgress(Gn2 Board, RQTabHeadPtr pRelQTabHead, PBFU32 pBytesAqed);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConDMACommand(Gn2 Board, BFU32 Command, BFU32 Mode);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConVTrigModeSet(Gn2 Board, BFU32 TrigMode, BFU32 TrigSelect, BFU32 TrigPolarity);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConVTrigModeGet(Gn2 Board, PBFU32 TrigMode, PBFU32 TrigSelect, PBFU32 TrigPolarity);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConHTrigModeSet(Gn2 Board, BFU32 EncMode, BFU32 EncPolarity, BFU32 EncSelect);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConHTrigModeGet(Gn2 Board, PBFU32 EncMode, PBFU32 EncPolarity, PBFU32 EncSelect);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConSwTrigStat(Gn2 Board, PBFU32 Status );
Gn2DLL Gn2RC	Gn2CAPI Gn2ConHwTrigStat(Gn2 Board, PBFU32 Status);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConExTrigStatus(Gn2 Board, PBFU32 Mode);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConExTrigConnect(Gn2 Board, BFU32 Mode);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConIntModeSet(Gn2 Board, BFU32 Mode);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConIntModeGet(Gn2 Board, PBFU32 Mode);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConGPOutGet(Gn2 Board, PBFU32 Value);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConExposureControlSet(Bd Board, BFDOUBLE ExposurePeriod, BFDOUBLE LineFramePeriod, BFU32 TriggerMode, BFBOOL AssertedHigh, BFU32 OutputSignal);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConExposureControlGet(Bd Board, PBFDOUBLE pExposurePeriod, PBFDOUBLE pLineFramePeriod, PBFU32 pTriggerMode, PBFBOOL pAssertedHigh, PBFU32 pOutputSignal);
Gn2DLL Gn2RC	Gn2CAPI Gn2EncoderDividerSet(Bd Board, BFDOUBLE ScaleFactor, BFBOOL ForceDC, BFBOOL OpenLoop, BFU32 ClockSelect);
Gn2DLL Gn2RC	Gn2CAPI Gn2EncoderDividerGet(Bd Board, PBFDOUBLE pScaleFactor, PBFBOOL pForceDC, PBFBOOL pOpenLoop, PBFU32 pClockSelect);
Gn2DLL Gn2RC	Gn2CAPI Gn2TSSequenceSet(Bd Board, TSListPtr TSList, BFU32 PreTrigCT0, BFU32 PreTrigCT1, BFU32 PreTrigCT2, BFU32 PreTrigCT3, BFU32 TriggerSrc);
Gn2DLL Gn2RC	Gn2CAPI Gn2TSSequenceGet(Bd Board, TSListPtr *TSList, PBFU32 pPreTrigCT0, PBFU32 pPreTrigCT1, PBFU32 pPreTrigCT2, PBFU32 pPreTrigCT3, PBFU32 pTriggerSrc);
Gn2DLL Gn2RC	Gn2CAPI Gn2TSSequenceFree(Bd Board, TSListPtr TSList);

Gn2DLL Gn2RC	Gn2CAPI Gn2ConEncoderInputSet(Gn2 Board, BFU32 Encoder, BFU32 EncSelect, BFU32 EncPolarity);
Gn2DLL Gn2RC	Gn2CAPI Gn2ConTriggerInputSet(Gn2 Board, BFU32 TrigSelect, BFU32 TrigPolarity);
// Quad Tables

Gn2DLL Gn2RC	Gn2CAPI Gn2QTabEngage(Bd Board, RQTabHeadPtr pRelQTabHead);
Gn2DLL Gn2RC	Gn2CAPI Gn2QTabChainLink(Bd Board, RQTabHeadPtrPtr ChainArray, BFU32 NumInChain);
Gn2DLL Gn2RC	Gn2CAPI Gn2QTabChainBreak(Bd Board, RQTabHeadPtrPtr ChainArray);
Gn2DLL Gn2RC	Gn2CAPI Gn2QTabChainEngage(Bd Board, RQTabHeadPtrPtr ChainArray, BFU32 FrameNum);
Gn2DLL Gn2RC	Gn2CAPI Gn2QTabChainProgress(Bd Board, RQTabHeadPtrPtr ChainArray, PBFU32 pFrameNum, PBFU32 pLineNum);

Gn2DLL Gn2RC	Gn2CAPI Gn2ChainSIPEnable(Bd Board, RQTabHeadPtrPtr ChainArray);
Gn2DLL Gn2RC	Gn2CAPI Gn2ChainSIPDisable(Bd Board, RQTabHeadPtrPtr ChainArray);



#ifdef __cplusplus
}
#endif

#endif


