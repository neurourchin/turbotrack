//
// Creation:    BFCXPDef.h
// Created:     August 30, 2011
// Creator:     Reynold Dodson
//
// Copyright (C) 1993-2011 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Definitions for CXP interfaves
//
// Function prototypes for run time functions.
//
// History:
//
// 08/30/2011     rjd     Created file.
//

#if !defined(__BFCXPDEF__)
#define __BFCXPDEF__

// Constants
#define CXP_CNTRL_COM_MSG_CMD_READ			(0x00 << 24)
#define CXP_CNTRL_COM_MSG_CMD_WRITE			(0x01 << 24)
#define CXP_CNTRL_COM_MSG_CMD_RESET			(0xff << 24)

#define CXP_CNTRL_COM_MSG_REG_SIZE			4		// size of one read/write operation

#define CXP_CNTRL_COM_MSG_CMD_DEFAULT_CRC	0xdeadbeef
#define CXP_CNTRL_COM_MSG_RSP_TIMEOUT		300		// note that should be 200, but life isn't that simple
#define CXP_READ_CHUNK_RSP_TIMEOUT			1000

// 
#define CXP_SERDES_CONFIGURE_TIMEOUT		30000		

#define CXP_POWERUP_TIMEOUT					1000		


// CXP Errors
#define CXP_CNTRL_COM_MSG_ACK_FINAL_READ	0x00	// Final, command executed OK, reply data is appended (i.e. acknowledgement of read command).
#define CXP_CNTRL_COM_MSG_ACK_FINAL_WRITE	0x01	// Final, command executed OK, No reply data is appended (i.e. acknowledgement of write command).
#define CXP_CNTRL_COM_MSG_ACK_TENT			0x02	// Tentative, command execution in progress, signals Host to wait.
#define CXP_CNTRL_COM_MSG_ACK_FINAL_RESET	0x03	// Final, control channel reset executed OK.
#define CXP_CNTRL_COM_MSG_ACK_WAIT			0x04	// Wait ack
#define CXP_CNTRL_COM_MSG_ACK_BAD_ADDR		0x40	// Invalid address.
#define CXP_CNTRL_COM_MSG_ACK_BAD_DATA		0x41	// Invalid data for the address.
#define CXP_CNTRL_COM_MSG_ACK_BAD_OP_CODE	0x42	// Invalid control operation code.
#define CXP_CNTRL_COM_MSG_ACK_ADDR_IS_RO	0x43	// Write attempted to a read-only address.
#define CXP_CNTRL_COM_MSG_ACK_ADDR_IS_WO	0x44	// Read attempted from a write-only address.
#define CXP_CNTRL_COM_MSG_ACK_MSG_TOO_BIG	0x45	// Size field too large – command message (write) or acknowledgement message (read) would exceed packet size limit.
#define CXP_CNTRL_COM_MSG_ACK_SIZE_WRONG	0x46	// Incorrect size received, Message size is inconsistent with message size indication.
#define CXP_CNTRL_COM_MSG_ACK_BAD_CRC		0x80	// Failed CRC test in last received command.

// Possible Acks
#define CXP_CNTRL_COM_MSG_ACK_READ			0x0100	// Read Ack
#define CXP_CNTRL_COM_MSG_ACK_WRITE			0x0200	// Write Ack
#define CXP_CNTRL_COM_MSG_ACK_TENTATIVE		0x0400	// Tentative Ack
#define CXP_CNTRL_COM_MSG_ACK_RESET			0x0400	// Channel Reset Ack

// Maximum number of tentative ACKs before givinp up

#define MAX_TENT_ACKS						1000

// Stream Packet Data size (can be overwritten in camera file (Gn2) or register (KCXP)

#define STREAM_PACKET_DATA_SIZE				2048

// CXP Standard camera boot strap registers

// structure used to hold boot strap register informatoin
typedef struct _CXPBootRegRec
{
	PBFCHAR Name;
	BFU32	Address;
	BFU32	Group;
	BFU32	Support;
	BFU32	Access;
	BFU32	Size;
	BFU32	Interface;
} CXPBootRegRec, *CXPBootPtr;

enum _CXPGroup
{
	CXPGroupSupport,
	CXPGroupGenICam,
	CXPGroupCXP,
} CXPGroup;

enum _CXPSupport
{
	CXPSupportM,
} CXPSupport;

enum _CXPAccess
{
	CXPAccessRO,
	CXPAccessWO,
	CXPAccessRW,
} CXPAccess;

enum _CXPInterface
{
	CXPIInteger,
	CXPIString,
	CXPIEnumerate,
} CXPInterface;

// enum all registers (must match list below)
typedef enum _CXPBootRegList
{
	Standard,					
	Revision,					
	XmlManifestSize,			
	XmlManifestSelector,		
	XmlVersion,				
	XmlSchemaVersion,			
	XmlUrlAddress,			
	IidcPointer,				
	DeviceVendorName,			
	DeviceModelName,			
	DeviceManufacturerInfo,	
	DeviceVersion,			
	DeviceID,					
	DeviceUserID,				
	LinkReset,				
	DeviceLinkID,				
	MasterHostLinkID,			
	ControlPacketDataSize,	
	StreamPacketDataSize,		
	LinkConfig,				
	LinkConfigDefault,		
	TestMode,					
	TestErrorCountSelector,	
	TestErrorCount,		
	VendorSpace,
	NumCXPBootRegs
} CXPBootRegList;


static CXPBootRegRec CXPBootRegs[NumCXPBootRegs] = 
{
	"Standard",					0x00000000,	CXPGroupSupport,	CXPSupportM,	CXPAccessRO,	4,	CXPIInteger,
	"Revision",					0x00000004,	CXPGroupSupport,	CXPSupportM,	CXPAccessRO,	4,	CXPIInteger,
	"XmlManifestSize",			0x00000008,	CXPGroupSupport,	CXPSupportM,	CXPAccessRO,	4,	CXPIInteger,
	"XmlManifestSelector",		0x0000000C,	CXPGroupSupport,	CXPSupportM,	CXPAccessRW,	4,	CXPIInteger,
	"XmlVersion",				0x00000010,	CXPGroupSupport,	CXPSupportM,	CXPAccessRO,	4,	CXPIInteger,
	"XmlSchemaVersion",			0x00000014,	CXPGroupSupport,	CXPSupportM,	CXPAccessRO,	4,	CXPIInteger,
	"XmlUrlAddress",			0x00000018,	CXPGroupSupport,	CXPSupportM,	CXPAccessRO,	4,	CXPIInteger,
	"IidcPointer",				0x0000001C,	CXPGroupSupport,	CXPSupportM,	CXPAccessRO,	4,	CXPIInteger,
	"DeviceVendorName",			0x00002000,	CXPGroupGenICam,	CXPSupportM,	CXPAccessRO,	32,	CXPIString,
	"DeviceModelName",			0x00002020,	CXPGroupGenICam,	CXPSupportM,	CXPAccessRO,	32,	CXPIString,
	"DeviceManufacturerInfo",	0x00002040,	CXPGroupGenICam,	CXPSupportM,	CXPAccessRO,	48,	CXPIString,
	"DeviceVersion",			0x00002070,	CXPGroupGenICam,	CXPSupportM,	CXPAccessRO,	32,	CXPIString,
	"DeviceID",					0x000020B0,	CXPGroupGenICam,	CXPSupportM,	CXPAccessRO,	16,	CXPIString,
	"DeviceUserID",				0x000020C0,	CXPGroupGenICam,	CXPSupportM,	CXPAccessRW,	16,	CXPIString,
	"LinkReset",				0x00004000,	CXPGroupCXP,		CXPSupportM,	CXPAccessRW,	4,	CXPIInteger,
	"DeviceLinkID",				0x00004004,	CXPGroupCXP,		CXPSupportM,	CXPAccessRO,	4,	CXPIInteger,
	"MasterHostLinkID",			0x00004008,	CXPGroupCXP,		CXPSupportM,	CXPAccessRW,	4,	CXPIInteger,
	"ControlPacketDataSize",	0x0000400C,	CXPGroupCXP,		CXPSupportM,	CXPAccessRO,	4,	CXPIInteger,
	"StreamPacketDataSize",		0x00004010,	CXPGroupCXP,		CXPSupportM,	CXPAccessRW,	4,	CXPIInteger,
	"LinkConfig",				0x00004014,	CXPGroupCXP,		CXPSupportM,	CXPAccessRW,	4,	CXPIEnumerate,
	"LinkConfigDefault",		0x00004018,	CXPGroupCXP,		CXPSupportM,	CXPAccessRO,	4,	CXPIInteger,
	"TestMode",					0x0000401C,	CXPGroupCXP,		CXPSupportM,	CXPAccessRW,	4,	CXPIInteger,
	"TestErrorCountSelector",	0x00004020,	CXPGroupCXP,		CXPSupportM,	CXPAccessRW,	4,	CXPIInteger,
	"TestErrorCount",			0x00004024,	CXPGroupCXP,		CXPSupportM,	CXPAccessRW,	4,	CXPIInteger,
	"VendorSpace",				0x00006000,	CXPGroupCXP,		CXPSupportM,	CXPAccessRW,	0,	CXPIString,
};

// CXP link speed structure
typedef struct _CXPLinkSpeedRec
{
	PBFCHAR Name;
	BFU32	Value;
} CXPLinkSpeedRec, *CXPLinkSpeedPtr;

// list of supported speeds, must match list below
typedef enum _CXPLinkSpeedList
{
	CXPDefault,
	CXPSpeed125,
	CXPSpeed250,
	CXPSpeed3125,
	CXPSpeed500,
	CXPSpeed625,
	NumCXPLinkSpeeds
} CXPLinkSpeedList;

static CXPLinkSpeedRec CXPLinkSpeeds[NumCXPLinkSpeeds] = 
{
	"Default",  0x00,
	"1.25Ghz",	0x28,
	"2.50Ghz",	0x30,
	"3.125Ghz",	0x38,
	"5.00Ghz",	0x40,
	"6.25Ghz",	0x48,
};


#ifdef __cplusplus
extern "C" {
#endif
// non public functions


#ifdef __cplusplus
}
#endif

#endif