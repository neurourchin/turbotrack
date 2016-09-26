//
// Creation:    BFApiPrv.h
// Created:     April 9, 1996
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Kernel Driver API Generic Board Access Functions
//
// History:
//
// 04/09/96     rbs     Created file.
// 04/22/96     rbs     Added BFLane<things>.
// 08/30/00		rjd		Moved registry headers into own file.
//

#if !defined(__BFAPIPRV__)
#define __BFAPIPRV__

#include "BFType.h"
#include "BFDefPrv.h"
#include "BFUtilitiesBth.h"
#include "BFTimersBth.h"
#include "BFErrorBth.h"
#include "BFCatchAllBth.h"
#include "BFConfigBth.h"
#include "BFInfo.h"
#include "BFApi.h"
#include "BFFlashBth.h"
#include "BFTabConfig.h"
#include "BFQTabBth.h"
#include "BFSpeedsBth.h"
#include "BFInterruptBth.h"
#include "BFPrimitivesBth.h"
#include "BFRegistry.h"

#ifdef __cplusplus
extern "C" {
#endif

BFDLL BFU32			BFCAPI BFMemPeek(Bd Board, BFU32 ObjId, BFU32 WordOffset);
BFDLL BFRC			BFCAPI BFMemPoke(Bd Board, BFU32 ObjId, BFU32 WordOffset, BFU32 ObjValue);
BFDLL BFRC			BFCAPI BFMemRMW(Bd Board, BFU32 ObjId, BFU32 WordOffset, BFU32 ObjValue, BFU32 ObjMask);
BFDLL BFRC			BFCAPI BFMemFill(Bd Board, BFU32 ObjId, BFU32 WordOffset, BFU32 WordCount, BFU32 Value, BFU32 Mask);
BFDLL BFRC			BFCAPI BFMemRead(Bd Board, BFU32 ObjId, BFU32 WordOffset, BFU32 WordCount, BFU32 *Buffer, BFU32 Mask);
BFDLL BFRC			BFCAPI BFMemWrite(Bd Board, BFU32 ObjId, BFU32 WordOffset, BFU32 WordCount, BFU32 *Buffer, BFU32 Mask);
BFDLL BFRC			BFCAPI BFLaneRead(BFU8 DataSets, Bd Board, BFU32 AddrId, BFU32 DataId, BFU32 P_Mask, BFU8 P_Lanes, ...);  
BFDLL BFRC			BFCAPI BFLaneWrite(BFU8 DataSets, Bd Board, BFU32 AddrId, BFU32 DataId, BFU32 P_Mask, BFU8 P_Lanes, ...);  
BFDLL BFU32			BFCAPI BFLanePeek(Bd Board, BFU32 AddrId, BFU32 DataId, BFU32 LaneAddress, BFU32 P_Mask, BFU8 P_Lanes, BFU32 S_Mask);  
BFDLL BFRC			BFCAPI BFLanePoke(Bd Board, BFU32 AddrId, BFU32 DataId, BFU32 LaneAddress, BFU32 P_Mask, BFU8 P_Lanes, BFU32 S_Mask, BFU8 S_Lanes, BFU32 LaneValue);  

BFDLL void			BFCAPI BF_Write(BF_WriteArgsPtr Args);

// Flash 

BFDLL BFRC			BFCAPI BFFlashCreateSet(Bd Board);
BFDLL BFRC			BFCAPI BFFlashValidate(Bd Board, BFU32 FlashId, BFU32 LoadTag);
BFDLL BFRC			BFCAPI BFFlashDownload(Bd Board);
BFDLL BFRC			BFCAPI BFFlashDownloadForce(Bd Board, BFU32 Bank, PBFU32 Status, BFU32 StatusSize);
BFDLL BFRC			BFCAPI BFFlashGetSet(Bd Board, BFFlashTab *pFlashTable, PBFU32 pFlashEntries, BFBOOL Filter);
BFDLL BFRC			BFCAPI BFFlashSetSet(Bd Board, BFFlashTab FlashTable);
BFDLL BFRC			BFCAPI BFFlashFreeSet(Bd Board, BFFlashTab FlashTable);
BFDLL void			BFCAPI BFFlashGetOptions(Bd Board, BFFlashOpsPtr Ops);
BFDLL void			BFCAPI BFFlashSetOptions(Bd Board, BFFlashOpsPtr Ops);
BFDLL BitSetPtr		BFCAPI BFFlashReadBitSet(Bd Board, BFU32 FlashFamily, BFU32 FlashId, PBFCHAR FamilyFolder, PBFCHAR Name, BFU32 BitBytes, BFBOOL HeaderOnly);
BFDLL PBFCHAR		BFCAPI BFFishName(PBFCHAR FileName, PBFCHAR FishName, BFSIZET FishNameSize);
BFDLL PBFCHAR		BFCAPI BFFishRoot(PBFCHAR FileName, PBFCHAR RootName, BFSIZET RootNameSize);
BFDLL void			BFCAPI BFGetFlashPath(Bd Board, PBFCHAR FlashPath, BFSIZET FlashPathSize, PBFCHAR FamilyName, PBFCHAR FileName, PBFCHAR FileExt);
BFDLL BFRC			BFCAPI BFFlashDelayedFlash(Bd Board);

#if !defined(KernelOS)

// Signalling

BFDLL BFRC			BFCAPI BFSignalCreate(Bd Board,BFU32 Type, PBFSIGNAL pSignal);
BFDLL BFRC			BFCAPI BFSignalFree(Bd Board,PBFSIGNAL pSignal);
BFDLL BFRC			BFCAPI BFSignalWait(Bd Board,PBFSIGNAL pSignal, BFU32 TimeOut, PBFU32 pNumInts);
BFDLL BFRC			BFCAPI BFSignalWaitEx(Bd Board,PBFSIGNAL pSignal, BFU32 TimeOut, PBFU32 pNumInts, BFSignalTimeInfoPtr pTimeInfo);
BFDLL BFRC			BFCAPI BFSignalNextWait(Bd Board,PBFSIGNAL pSignal, BFU32 TimeOut);
BFDLL BFRC			BFCAPI BFSignalQueueSize(Bd Board,PBFSIGNAL pSignal,PBFU32 pNumInts);
BFDLL BFRC			BFCAPI BFSignalQueueClear(Bd Board,PBFSIGNAL pSignal);
BFDLL BFRC			BFCAPI BFSignalCancel(Bd Board,PBFSIGNAL pSignal);
BFDLL BFBOOL		BFCAPI BFSignalQueueInts(Bd Board,BFU32 Type,BFU32 NumToQueue);  
BFDLL BFRC			BFCAPI BFSignallingThreadCreate(Bd Board);
BFDLL BFRC			BFCAPI BFSignallingThreadDestroy(Bd Board);  
BFDLL BFRC			BFCAPI BFSignallingClear(Bd Board);  
BFDLL BFRC			BFCAPI BFSignalNameGet(Bd Board, BFU32 Type, PBFCHAR SignalName, BFU32 SignalNameSize);

BFDLL void			BFCAPI BFSetOtherDevices(Bd Board, BFU32 Latency);
BFDLL void			BFCAPI BFSetSnoopBit(Bd Board);

// Board 

typedef BFRC (*PBFCAMOPEN)(Bd Board, PBFCHAR CamName, PBFCNF *pCam);
typedef BFRC (*PBFBRDINIT)(Bd Board, PBFCNF pCam);
typedef BFRC (*PBFSHUTDOWN)(Bd Board);
typedef BFRC (*PBFCAM2BRD)(Bd Board, PBFCNF pCam);

BFDLL BFRC			BFCAPI BFSysBoardFindFamilies(BFU32 Family, BFDevicePtr *pDeviceList);
BFDLL BFRC			BFCAPI BFSysBoardFreeFamilies(BFDevicePtr DeviceList);
BFDLL BFRC			BFCAPI BFSysBoardFindByBusSlot(BFU32 Bus, BFU32 Slot, PBFENTRY pEntry, BFU32 Family);
BFDLL BFRC			BFCAPI BFSysBoardFindByNum(BFU32 Number, PBFENTRY pEntry, BFU32 Family);
BFDLL BFRC			BFCAPI BFBrdOpen(PBFENTRY pEntry, Bd *pBoard, BFU32 Mode, PBFCHAR FamilyKey, PBFVOID pXXInfo, PBFINTENABLE pIntEnable, PBFCAMOPEN pCamOpen, PBFBRDINIT pBoardInit, PBFSHUTDOWN pShutdown, PBFCHAR ForceCamFile);
BFDLL BFRC			BFCAPI BFBrdClose(Bd Board, PBFSHUTDOWN pShutdown);
BFDLL BFRC			BFCAPI BFBrdCamSel(Bd Board, BFU32 CamIndex, BFU32 Mode, PBFCAM2BRD pCam2Brd);
BFDLL BFRC			BFCAPI BFBrdCamSetCur(Bd Board, PBFCNF pCam, BFU32 Mode, PBFCAM2BRD pCam2Brd);
BFDLL BFRC			BFCAPI BFBrdCamGetCur(Bd Board, PBFCNF *pCam);
BFDLL BFRC			BFCAPI BFBrdCamGetFileName(Bd Board, BFU32 Num, PBFCHAR CamName, BFSIZET CamNameStLen);
BFDLL BFRC			BFCAPI BFBrdCamGetFileNameWithPath(Bd Board, BFU32 Num, PBFCHAR CamNameWithPath, BFSIZET CamNameWithPathStLen);

BFDLL BFRC			BFCAPI BFSysBoardFindSWConnector(BFU32 Switch, BFU32 Connector, PBFENTRY pEntry, BFU32 Family);

BFDLL BFRC			BFCAPI BFDriverOpen(Bd *pBoard, PBFENTRY pEntry, PBFVOID pXXInfo);

BFDLL BFRC			BFCAPI BFDrvOpen(Bd *pBoard);
BFDLL BFRC			BFCAPI BFDrvClose(Bd Board);

// Error

BFDLL BFRC			BFCAPI BFErrorMonitorConnect(Bd Board, PBFU32 pMonitorId);
BFDLL BFRC			BFCAPI BFErrorMonitorWait(Bd Board, BFU32 MonitorId, BFErrorInfoPtr pErr);
BFDLL BFRC			BFCAPI BFErrorMonitorDisconnect(Bd Board, BFU32 MonitorId);

// Catch All

BFDLL void			BFCAPI BF_DriverVersion(BF_DriverVersionArgsPtr Args);
BFDLL BFRC			BFCAPI BFFlashRequest(Bd Board,BFFlashPtr pFlashRequested);

#endif


// Error

BFDLL BFRC			BFCAPI BFErrorSetAll(Bd Board);
BFDLL BFRC			BFCAPI BFErrorFileAll(Bd Board);
BFDLL BFRC			BFCAPI BFErrorStackDepth(Bd Board, BFU32 Depth);
BFDLL BFRC			BFCAPI BFErrorEnableBreakKernel(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorDisableBreakKernel(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorSetPrv(Bd BoardId, BFRC TheRC, char *File, int Line);
BFDLL void			BFCAPI BFErrorMessage(Bd BoardId, char *Message, BFU32 Color);
BFDLL void			BFCAPI BFErrorMessageRed(Bd Board, const char *Format, ...);
BFDLL void			BFCAPI BFErrorMessageYellow(Bd Board, const char *Format, ...);
BFDLL void			BFCAPI BFErrorMessageBlue(Bd Board, const char *Format, ...);
BFDLL void			BFCAPI BFErrorShowMePrv(Bd BoardId, char *Message, int Thing, BFBOOL Hex);
BFDLL void			BFCAPI BFErrorWhereAmIPrv(Bd BoardId, char *File, int Line);

BFDLL void			BFCAPI BFRegTracePrv(Bd BoardId, BFBOOL Enable, PBFBOOL pOldState, char *File, int Line);
BFDLL void			BFCAPI BFTimeTracePrv(Bd BoardId, BFBOOL Enable, PBFBOOL pOldState, char *File, int Line);
BFDLL void			BFCAPI BFTimeDump(Bd BoardId);
BFDLL void			BFCAPI BFCallTracePrv(Bd BoardId, BFBOOL Enable, PBFBOOL pOldState, char *File, int Line);

// Configuration

BFDLL BFRC			BFCAPI BFStructSize(Bd Board,PBFCNFENTRY pEntry,PBFU32  pSize);
BFDLL BFRC			BFCAPI BFStructAlloc(Bd Board,BFU32  MaxSize,BFU32  MaxIds, PBFCNF *pBase);
BFDLL BFRC			BFCAPI BFStructFree(Bd Board,PBFCNF pBase);
BFDLL BFRC			BFCAPI BFStructItemAdd(Bd Board,PBFCNF pBase, BFU32 ID, BFSIZET DataSize,BFU32  Type,BFU32  Indx,PBFVOID pVal1,PBFVOID pVal2);
BFDLL BFRC			BFCAPI BFStructItemAddBlank(Bd Board,PBFCNF pBase, BFU32  ID, BFU32  DataSize,BFU32  Type,BFU32  Indx);
BFDLL BFRC			BFCAPI BFStructClear(Bd Board,PBFCNF pBase);

BFDLL BFRC			BFCAPI BFCnfTextRead(Bd Board,PBFCNFENTRY pEntry,PBFCNF pCam,PBFCHAR pBuf,BFU32 BufSize,PBFCHAR *pLastLine);
BFDLL BFRC			BFCAPI BFCnfTextWrite(Bd Board,PBFCNFENTRY pEntry,PBFCNF pCam,PBFCHAR pBuf,BFU32 BufSize);
BFDLL BFRC			BFCAPI BFCnfBinRead(Bd Board,PBFCNFENTRY pEntry,PBFCNF pCam,PBFU8 pBuf,BFSIZET BufSize,BFSIZET DataSize);
BFDLL BFRC			BFCAPI BFCnfBinWrite(Bd Board,PBFCNFENTRY pEntry,PBFCNF pCam,PBFU8 pBuf,PBFU32 pBufSize);

BFDLL void			BFCAPI BFCameraFree(Bd Board,PBFCNF pCam);

// Device Configuration 

BFDLL BFRC			BFCAPI BFParseCfgOps(Bd Board, VFOPtr pVFO);

BFDLL BFRC			BFCAPI BFReadCfgBus(Bd Board, BFU32 BusType, BFU32 Bus, BFU32 Slot, BFU32 Function, BFU32 Field, BFU32 Size, PBFVOID pValue, PBFBOOL pFound);
BFDLL BFRC			BFCAPI BFWriteCfgBus(Bd Board, BFU32 BusType, BFU32 Bus, BFU32 Slot, BFU32 Function, BFU32 Field, BFU32 Size, PBFVOID pValue);
BFDLL BFRC			BFCAPI BFGetCfgBusConfig(Bd Board, BFU32 BusType, BFU32 Bus, BFU32 Slot, BFU32 Function, pBFPCIConfig pConfig, PBFU32 pBytes, PBFBOOL pBusExists, PBFBOOL pSlotEmpty);
BFDLL BFRC			BFCAPI BFGetCfgBusVendor(Bd Board, BFU32 BusType, BFU32 Bus, BFU32 Slot, BFU32 Function, PBFU32 pVendorId);
BFDLL BFRC			BFCAPI BFGetCfgBusDevice(Bd Board, BFU32 BusType, BFU32 Bus, BFU32 Slot, BFU32 Function, PBFU32 pDeviceId);
BFDLL BFRC			BFCAPI BFGetCfgBusSubVendor(Bd Board, BFU32 BusType, BFU32 Bus, BFU32 Slot, BFU32 Function, PBFU32 pSubVendorId);
BFDLL BFRC			BFCAPI BFGetCfgBusSubSystem(Bd Board, BFU32 BusType, BFU32 Bus, BFU32 Slot, BFU32 Function, PBFU32 pSubSystemId);
BFDLL BFRC			BFCAPI BFGetCfgLinkWidthAndSpeed(Bd Board, BFU32 BusType, BFU32 Bus, BFU32 Slot, BFU32 Function, PBFU32 LinkWidth, PBFU32 LinkSpeed);
BFDLL BFRC			BFCAPI BFGetCfgBusVFO(Bd Board, BFU32 BusType, BFU32 Bus, BFU32 Slot, BFU32 Function, VFOPtr pVFO); 

BFDLL BFRC			BFCAPI BFReadCfgBoard(Bd Board, BFU32 Field, BFU32 Size, PBFVOID pValue);
BFDLL BFRC			BFCAPI BFWriteCfgBoard(Bd Board, BFU32 Field, BFU32 Size, PBFVOID pValue);
BFDLL BFRC			BFCAPI BFGetCfgBoardConfig(Bd Board, BFU32 BusType, BFU32 Bus, BFU32 Slot, BFU32 Function, pBFPCIConfig pConfig, PBFU32 pBytes);
BFDLL BFRC			BFCAPI BFGetCfgBoardVendor(Bd Board, PBFU32 pVendorId);
BFDLL BFRC			BFCAPI BFGetCfgBoardDevice(Bd Board, PBFU32 pDeviceId);
BFDLL BFRC			BFCAPI BFGetCfgBoardSubVendor(Bd Board, PBFU32 pSubVendorId);
BFDLL BFRC			BFCAPI BFGetCfgBoardSubSystem(Bd Board, PBFU32 pSubSystemId);
BFDLL BFRC			BFCAPI BFGetCfgBoardVFO(Bd Board, VFOPtr pVFO); 
BFDLL BFRC			BFCAPI BFUpdateBoardVFO(Bd Board); 

BFDLL BFRC			BFCAPI BFGetCfgDevices(Bd Board, BFU32 Vendors, BFU32 Families, BFBOOL Live, BFDevicePtr *pDeviceList);
BFDLL BFRC			BFCAPI BFGetCfgDevicesSorted(Bd Board, BFU32 Vendors, BFU32 Families, BFBOOL Live, BFDevicePtr *pDeviceList);
BFDLL BFRC			BFCAPI BFGetFamilyDevices(Bd Board, BFU32 Family, BFDevicePtr *pDeviceList);
BFDLL BFRC			BFCAPI BFFreeCfgDevices(Bd Board, BFDevicePtr DeviceList);

BFDLL BFRC			BFCAPI BFPCICfgSave(Bd Board);
BFDLL BFRC			BFCAPI BFPCICfgRestore(Bd Board);
BFDLL BFRC			BFCAPI BFPCICfgRestoreAll(Bd Board);
BFDLL BFRC			BFCAPI BFPCICfgSaveAll(Bd Board);


// DMA

BFDLL BFRC			BFCAPI BFQTabProgress(Bd Board, PQNumPtr PhysQTabNum, BFProgressPtr pProgress);

// QTAB Functions

BFDLL BFRC			BFCAPI BFVQTabCreateRoi(Bd Board,PBFVOID pDest,BFU32 BufferSize,BFS32 Stride,VQTabHeadPtr pVQTabHead,BFU32 LutBank,BFU32 LutMode,BFU32 AqEngine,BFU32 Options,BFU32 PelSize,BFU32 XSize,BFU32 YSize,BFU32 Format,PBFU32 QTMPRun,PBFU32 QTMPOffs,BFU32 NumParams,BFU32 DestX,BFU32 DestY,BFU32 DestDX,BFU32 DestDY);
BFDLL BFRC			BFCAPI BFVQTabCreate(Bd Board,PBFVOID pDest,BFU32 BufferSize,BFS32 Stride,VQTabHeadPtr pVQTabHead,BFU32 LutBank,BFU32 LutMode,BFU32 AqEngine,BFU32 Options,BFU32 PelSize,BFU32 XSize,BFU32 YSize,BFU32 Format,PBFU32 QTMPRun,PBFU32 QTMPOffs,BFU32 NumParams);
BFDLL BFRC			BFCAPI BFVQTabFree(Bd Board, VQTabHeadPtr pQTabHead);

BFDLL BFRC			BFCAPI BFPQTabCreate(Bd Board, VQTabHeadPtr pVQTabHead, BFModsPtr pMods);

BFDLL BFRC			BFCAPI BFPhysQTabCreate(Bd Board, RQTabHeadPtr pRelQTabHead, BFModsPtr pMods);
BFDLL BFRC			BFCAPI BFPhysQTabWrite(Bd Board, RQTabHeadPtr pRelQTabHead);
BFDLL BFRC			BFCAPI BFPhysQTabEngage(Bd Board, PQNumPtr PhysQTabNum, BFU32 FrameNum);
BFDLL BFRC			BFCAPI BFPhysQTabChainLink(Bd Board, RQTabHeadPtrPtr ChainArray, BFU32 NumInChain);
BFDLL BFRC			BFCAPI BFPhysQTabChainEnable(Bd Board, RQTabHeadPtr pRelQTabHead);
BFDLL BFRC			BFCAPI BFPhysQTabChainDisable(Bd Board, RQTabHeadPtr pRelQTabHead);
BFDLL BFRC			BFCAPI BFPhysQTabChainBreak(Bd Board, PQNumPtr PhysQTabNum);
BFDLL BFRC			BFCAPI BFPhysQTabGetAbsQuad(Bd Board, PQNumPtr HeadQTabNum, PQNumPtr PhysQTabNum, BFU32 QuadNumber, BFU32 QuadType, BFQuadInfoPtr pQuadInfo);
BFDLL BFRC			BFCAPI BFPhysQTabGetRelQuad(Bd Board, BFU32 HeadOffset, BFU32 FrameOffset, BFU32 QuadOffset, BFQuadInfoPtr pQuadInfo);
BFDLL BFRC			BFCAPI BFPhysQTabFree(Bd Board, RQTabHeadPtr pRelQTabHead);
BFDLL BFRC			BFCAPI BFPhysQTabFreeAll(Bd Board, BFBOOL JustMine);

// Interrupts

BFDLL BFRC			BFCAPI BFInterruptSimulate(Bd Board);  
BFDLL BFRC			BFCAPI BFSerIntInit(Bd Board);
BFDLL BFRC			BFCAPI BFSerIntGetInBuf(Bd Board, PBFU8 DestBuffer, BFU32 DestBufferSize, PBFU32 pNumRead);
BFDLL BFRC			BFCAPI BFSerIntGetInBufSize(Bd Board, PBFU32 pInBufSize);
BFDLL BFRC			BFCAPI BFSerIntFlushInBuf(Bd Board);

// Catch All

BFDLL BFRC			BFCAPI BFDoNothing(Bd Board);
BFDLL BFRC			BFCAPI BFGetInfo(Bd Board, BFInfoType Type, PBFVOID pInfo);
BFDLL BFRC			BFCAPI BFSetInfo(Bd Board, BFInfoType Type, BFU32 Info);
BFDLL BFRC			BFCAPI BFGetRegToId(Bd Board);
BFDLL BFRC			BFCAPI BFChangeFace(Bd Board, BFU32 Dev, BFU32 SubVen, BFU32 SubSys, BFU32 InfoHi, BFU32 InfoLo);
BFDLL BFRC			BFCAPI BFSetUARTMutex(Bd Board, PBFU32 pBusy);
BFDLL BFRC			BFCAPI BFResetUARTMutex(Bd Board);

// Performance Tests

BFDLL BFBOOL		BFCAPI BFSpeedTest(Bd Board, BFU32 TestNumber, BFSpeedsUsrPtr pSpeedsUsr, BFSpeedsKrnPtr pSpeedsKrn);
BFDLL BFRC			BFCAPI BFSpeeds(Bd Board, BFSpeedsUsrPtr pSpeedsUsr, BFSpeedsKrnPtr pSpeedsKrn);

BFDLL BFU64			BFCAPI BFSuperFineDelta(Bd Board, BFU64 t0, BFU64 t1, BFBOOL AbsValue);

// Pixel router
BFDLL BFRC			BFCAPI PixelRouterCreate(BFU32 Width, BFU32 ZoneX, BFU32 TapX, BFU32 ExtX, void **hPixelRouter);
BFDLL BFRC			BFCAPI PixelRouterCreateEx(BFU32 NumTaps, BFS32 Start[10], BFS32 Step[10], BFS32 TapSelRamArray[][10], BFS32 TapAddrSelRamArray[][10], void **hPixelRouter);
BFDLL void			BFCAPI PixelRouterDelete(void *hPixelRouter);
BFDLL BFRC			BFCAPI StartStepArrayBuild(BFU32 Width, BFU32 ZoneX, BFU32 TapX, BFU32 ExtX, BFS32 Start[10], BFS32 Step[10]);
BFDLL BFRC			BFCAPI PixelRouterToBoard(Bd hBoard, void *hPixelRouter, BFU32 CLMode, BFU32 CLChannels); 


#if defined(KernelOS)

// Interrupts

BFRC		BFInterruptMap(Bd Board);
NTSTATUS	BFInterruptConnect(Bd Board,BFBOOL bLatched);
void		BFInterruptDisconnect(Bd Board);
BOOLEAN		BFInterruptService(PKINTERRUPT pInterruptObject,PVOID Context);
VOID		BFInterruptDeferred(PKDPC pDpc,PDEVICE_OBJECT pDeviceObject,PIRP pIrpNotUsed,PVOID Context);
NTSTATUS	BFInterruptSignalHandler(Bd Board,PIRP pIrp);
void		BFInterruptCancelHandler(PDEVICE_OBJECT pDeviceObject,PIRP pIrp);
void		BFInterruptHooks(Bd Board);
BFBOOL		BFInterruptComplete(Bd Board);
BFBOOL		BFInterruptCancelAll(Bd Board);


// KeReadStateMutex is defined to KeReadStateMutant in ntddk.h and KeReadStateMutant is not exported. To get
// rid of warnings when using KeReadStateMutex, we export it here. Someday this may get messed up if MS ever 
// fixes this screwup.

NTKERNELAPI BOOLEAN KeReadStateMutant(IN PRKMUTEX Mutex);

// Catch All

void BFC	BF_DriverVersion(BF_DriverVersionArgsPtr Args);

#endif // KernelOS

#ifdef __cplusplus
}
#endif

#endif

