#ifndef INCLUDED__B_F_G_T_L__UTIL__D_E_F__H
#define INCLUDED__B_F_G_T_L__UTIL__D_E_F__H

/* FILE:        BFGTLUtilDef.h
 * DATE:        4/27/2015
 * AUTHOR:      Jeremy Greene
 * COMPANY:     BitFlow, Inc.
 * COPYRIGHT:   Copyright (C) 2015, BitFlow, Inc.
 * DESCRIPTION: Definitions for the BitFlow GenTL interface, used to query and control GenICam device
 *              properties.
 */
 
#include "BFType.h"

typedef struct _BFGTLDev *BFGTLDev;
typedef BFGTLDev *PBFGTLDev;

typedef struct _BFGTLNode *BFGTLNode;
typedef BFGTLNode *PBFGTLNode;

//// Property enumerations.

typedef enum BFGTLNodeTypeEnum
{
    BFGTL_NODE_TYPE_UNKNOWN     = 0x0000,
    BFGTL_NODE_TYPE_VALUE       = 0x0001,
    BFGTL_NODE_TYPE_BASE        = 0x0002,
    BFGTL_NODE_TYPE_INTEGER     = 0x0003,
    BFGTL_NODE_TYPE_BOOLEAN     = 0x0004,
    BFGTL_NODE_TYPE_COMMAND     = 0x0005,
    BFGTL_NODE_TYPE_FLOAT       = 0x0006,
    BFGTL_NODE_TYPE_STRING      = 0x0007,
    BFGTL_NODE_TYPE_REGISTER    = 0x0008,
    BFGTL_NODE_TYPE_CATEGORY    = 0x0009,
    BFGTL_NODE_TYPE_ENUMERATION = 0x000A,
    BFGTL_NODE_TYPE_ENUM_ENTRY  = 0x000B,
    BFGTL_NODE_TYPE_PORT        = 0x000C,
} BFGTLNodeType;

typedef enum BFGTLDataTypeEnum
{
    BFGTL_TYPE_UNKNOWN          = 0x0000,

    // Fixed length types.
    
        // An untyped value, sizeof == 0. Simply write a nullptr  (see BFGTL_NODE_TYPE_COMMAND).
    BFGTL_TYPE_NONE             = 0x0001,
        // BFBOOL
    BFGTL_TYPE_BOOL             = 0x0002,
        // BFU32
    BFGTL_TYPE_UINT32           = 0x0003,
        // BFS64
    BFGTL_TYPE_INT64            = 0x0004,
        // BFDOUBLE
    BFGTL_TYPE_DOUBLE           = 0x0005,
        // BFSIZET
    BFGTL_TYPE_SIZET            = 0x0006,
    
    // Variable length types.
    
        // A raw byte array.
    BFGTL_TYPE_BYTE_ARRAY       = 0x1000,

        // An array of BFS64.
    BFGTL_TYPE_INT64_ARRAY      = 0x1001,

        // A null-terminated C style string.
    BFGTL_TYPE_CSTR             = 0x1002,

        // A table of null-terminated C style strings. Internal data layout is:
        //      { size_t strOffsets[]; char strData[]; }
        //  -- strOffsets: A null-terminated array of offsets, indicating the byte offset of
        //                 each string in the buffer.
        //  -- strData: An array of concatenated, null-terminated strings.
        //
        // Example code reading a cstr-table and printing all of its contents:
        //      size_t iSize;
        //      BFGTLNodeRead(hNode, BFGTL_NODE_FEATURE_NAMES, 0, &iSize);
        //      char *strTable = (char*)malloc(iSize);
        //      BFGTLNodeRead(hNode, BFGTL_NODE_FEATURE_NAMES, strTable, &iSize);
        //      size_t *strOffset = (size_t*)strTable;
        //      while (*strOffset)
        //          printf("%s\n", strTable + *strOffset++);
        //      free(strTable);
    BFGTL_TYPE_CSTR_TABLE       = 0x1003,
} BFGTLDataType;

typedef enum BFGTLAccessEnum
{
    BFGTL_ACCESS_UNKNOWN    = 0,

    BFGTL_ACCESS_NI         = 1,    // Not Implemented
    BFGTL_ACCESS_NA         = 2,    // Not Accessible
    BFGTL_ACCESS_RO         = 3,    // Read Only
    BFGTL_ACCESS_WO         = 4,    // Write Only
    BFGTL_ACCESS_RW         = 5     // Read/Write
} BFGTLAccess;

typedef enum BFGTLNodeFieldEnum
{
    // Common fields.

        // [Access:RO;Type:BFGTL_TYPE_UINT32] The node's BFGTLNodeType.
    BFGTL_NODE_TYPE             = 0x0000,

        // [Access:RO;Type:BFGTL_TYPE_UINT32] The node's BFGTLAccess.
    BFGTL_NODE_ACCESS           = 0x0001,

        // [Access:RO;Type:BFGTL_TYPE_CSTR] The node name string.
    BFGTL_NODE_NAME             = 0x0002,

        // [Access:RO;Type:BFGTL_TYPE_CSTR] The node display name string.
    BFGTL_NODE_DISPLAY_NAME     = 0x0003,

        // [Access:RO;Type:BFGTL_TYPE_CSTR] The node tool-tip string.
    BFGTL_NODE_TOOL_TIP         = 0x0004,

        // [Access:RO;Type:BFGTL_TYPE_CSTR] The node description string.
    BFGTL_NODE_DESCRIPTION      = 0x0005,

        // [Access:RW;Type:BFGTL_TYPE_BOOL] Whether or not to ignore cached data when reading a node value.
    BFGTL_NODE_IGNORE_CACHE     = 0x0100,

    // Variable fields.

        // [Access:variable;Type:variable] The node data value. (Integer, Command, Boolean, Float, String, Register, Enumeration, EnumEntry)
    BFGTL_NODE_VALUE            = 0x1000,

        // [Access:variable;Type:BFGTL_TYPE_CSTR] A string representation of the current node value. Accessibility will vary based on node access.
    BFGTL_NODE_VALUE_STR        = 0x1001,

        // [Access:RO;Type:variable] The node minimum value. (Integer, Float)
    BFGTL_NODE_MIN              = 0x1002,

        // [Access:RO;Type:variable] The node maximum value. (Integer, Float)
    BFGTL_NODE_MAX              = 0x1003,

        // [Access:RO;Type:variable] The node increment value. (Integer, Float)
    BFGTL_NODE_INC              = 0x1004,

        // [Access:RO;Type:BFGTL_TYPE_INT64] The maximum length of a string. (String)
    BFGTL_NODE_MAX_LENGTH       = 0x1005,

        // [Access:RO;Type:BFGTL_TYPE_INT64] The byte-address of a register. (Register)
    BFGTL_NODE_ADDRESS          = 0x1006,

        // [Access:RO;Type:BFGTL_TYPE_INT64] The byte-length of a register. (Register)
    BFGTL_NODE_LENGTH           = 0x1007,

        // [Access:RO;Type:BFGTL_TYPE_SIZET] The number of child features/entries. (Category, Enumeration)
    BFGTL_NODE_FEATURE_COUNT    = 0x1008,
        // Mime of BFGTL_NODE_FEATURE_COUNT
    BFGTL_NODE_ENTRY_COUNT      = BFGTL_NODE_FEATURE_COUNT,

        // [Access:RO;Type:BFGTL_TYPE_CSTR_TABLE] The names of all child features/entries. (Category, Enumeration)
    BFGTL_NODE_FEATURE_NAMES    = 0x1009,
        // Mime of BFGTL_NODE_FEATURE_NAMES
    BFGTL_NODE_ENTRY_NAMES      = BFGTL_NODE_FEATURE_NAMES,
    
        // [Access:variable;Type:BFGTL_TYPE_INT64_ARRAY] The integer values of all child entries. (Enumeration)
    BFGTL_NODE_ENTRY_VALUES     = 0x100A,

        // [Access:variable;Type:BFGTL_TYPE_CSTR] The names of the currently selected enumeration entry. (Enumeration, EnumEntry)
    BFGTL_NODE_ENTRY_NAME       = 0x100B,

        // [Access:RO;Type:BFGTL_TYPE_CSTR_TABLE] The symbolic representations of all child entries. (Enumeration)
    BFGTL_NODE_ENTRY_SYMBOLICS  = 0x100C,

        // [Access:variable;Type:BFGTL_TYPE_CSTR] The symbolic representation of the currently selected enumeration entry. (Enumeration, EnumEntry)
    BFGTL_NODE_SYMBOLIC         = 0x100D,
} BFGTLNodeField;

typedef enum BFGTLNodeInqPropEnum
{
    BFGTL_NODE_INQ_DATA_TYPE    = 0,    // BFGTLDataType of the a BFGTLNodeField
    BFGTL_NODE_INQ_ACCESS       = 1     // BFGTLAccess of the a BFGTLNodeField
} BFGTLNodeInqProp;

#endif // INCLUDED__B_F_G_T_L__UTIL__D_E_F__H
