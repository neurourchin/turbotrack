//
// Creation:    Gn2TabError.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Gn2 Error Handler Definitions
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__Gn2TABERROR__)
#define __Gn2TABERROR__

#include "Gn2Type.h"
#include "BFTabError.h"
#include "BFTabConfig.h"

//
// Gn2 Error Return Codes
//

#define GN2_ERROR_ZERO (FF_GN2 << BF_ERROR_FAMILY_SHIFT)

typedef enum _Gn2RC_Enum
{
    GN2_OK = 0,					    // Operation succeeded.
	GN2_ERROR_START = GN2_ERROR_ZERO,
    GN2_BAD_NEWS,					// Operation failed.
    GN2_DUMMY_BAD,               // DPMPeek error.
    GN2_BAD_FREQ,					// Illegal clock frequency.
    GN2_CON_FREQ_BAD,				// ConFreq error.
    GN2_BAD_GPOUT,					// Illegal GPOut value.
    GN2_CON_GPOUT_BAD,				// ConGPOut error.
	GN2_BAD_CON_PARAM,				// Bad parameter to control functions.
	GN2_BAD_TRIGAQ,					// Illegal TrigAq setting. 
    GN2_CON_TRIG_AQ_BAD,			// ConTrigAq error.
    GN2_BAD_VSTOP,					// Illegal VMode selection. 
    GN2_BAD_HSTOP,					// Illegal HMode selection. 
    GN2_CON_VMODE_BAD,				// ConVMode error.
    GN2_CON_HMODE_BAD,				// ConHMode error.
	GN2_AQSETUP_FAIL,				// AqSetup failed.
	GN2_BAD_STOP,				    // Error stopping DMA and/or acquistion.
	GN2_AQ_NOT_SETUP,			    // Board not setup for acquistion.
	GN2_BAD_AQ_CMD,				    // Board not ready for Aq command issued.
	GN2_AQSTRT_TIMEOUT,			    // Timeout waiting for acquisition to start.
	GN2_AQEND_TIMEOUT,			    // Timeout waiting for acquisition to end.
	GN2_BAD_WAIT,				    // Cannot wait for acquire to end when board is in this state.
	GN2_BAD_CNF,					// Error extracting information from camera configuration.
	GN2_BAD_FRM_SIZE,				// Invalid frame size, too big or small
	GN2_HCTAB_X16,					// Pixel clock divided by 16 is not supported by Gn2AqFrameSize
	GN2_BAD_VCTAB,					// Couldn't find a valid VStart segment 0
	GN2_BAD_HCTAB,					// Couldn't find a valid HStart segment 0 or 1 and/or HStop
	GN2_CAM_SUPPORT,				// Cam file is not supported for changing of the frame size
	GN2_BAD_INQ_PARAM,			    // Bad parameter to inquire function.
    GN2_BAD_STRUCT,				    // Error in size of camera strucuture.
	GN2_BAD_CNF_FILE,			    // Error reading configuration file.
	GN2_INCOMP,					    // This configuration file is incompatible with this board.
	GN2_BAD_CNFG,				    // Error parsing camera configuration (bfml) file
    GN2_NO_CNFDIR_REG_KEY,			// Cnf Dir path key missing.
	GN2_BAD_PATH,				    // Error building file path.
	GN2_UNKOWN_REV,					// Board/camera revision unkown
	GN2_BRD_NOT_COMP,				// Camera file not compatible with this model board.
	GN2_UNKOWN_COMP,				// Camera file compatibility is unkown.
	GN2_TIMEOUT,					// Timeout wait for command.
	GN2_DUMMY_ERR,					// Gn2Dummy Error
	GN2_BAD_IRP_STOP,			    // Error canceling interrupt signalling IRPs.
	GN2_BAD_AQ_STOP,				// Timeout waiting for acquisition to stop.
	GN2_BAD_FIFO_RESET,				// Could not reset FIFO overflow.
	GN2_BAD_ROI,					// Error calculating QTAB for ROI.
	GN2_BAD_MODEL,				    // Error building QTAB from model parameters.
	GN2_DMA_ACTIVE_ERR,				// Gn2DMAActive Error
	GN2_DMA_START_ERR,				// Gn2DMAStart Error
	GN2_DMA_STOP_ERR,				// Gn2DMAStop Error
	GN2_DMA_ACTIVE,					// DMA is already active.
	GN2_DMA_START_BAD,				// DMAStart error.
	GN2_DMA_START_TIMEOUT,			// DMA start timeout.
	GN2_DMA_STOP_BAD,				// DMAStop error.
	GN2_DMA_STOP_TIMEOUT,			// DMA stop timeout.
	GN2_DMA_STUCK,					// Gn2 DMA engine hung.
	GN2_DMA_START_NULL,				// Quad start address BFNULL.
	GN2_BAD_FIRMWARE,				// Error downloading camera file requested firmware.
	GN2_BAD_DISP_BIT_DEPTH,			// This pixel depth not support for display.
	GN2_SLAVE_FW_MISMATCH,			// Requested slave firmware does not match master's firmware.
	GN2_RLE_TOO_SMALL,				// The CTab change requested will not fit in the RLE CTab.
	GN2_NOT_RLE_BOARD,				// RLE CTab Command issued to a non-RLE board.
	GN2_RLE_NO_SUPPORT,				// Function not supported on RLE boards.
	GN2_TS_NOT_SUPPORTED,			// Board does not support NTG
	GN2_TS_EXP_OUT_OF_RANGE,		// NTG parameters are out of range of NTG
	GN2_TS_EXP_GT_LF,				// The exposure period is longer than the line/frame period
	GN2_TS_UNKNOWN_MODE,			// NTG Trigger mode is unknown
	GN2_TS_PROG_ERROR,				// Error programming the TS 
	GN2_ENCDIV_NOT_SUPPORTED,		// Board does not support the encoder divider
	GN2_ENCDIV_OUT_OF_RANGE,		// The request encoder divider scale factor is too big
	GN2_ENCDIV_UNKNOWN_CLK,			// The request clock frequency is not supported the encoder divder
	GN2_NOT_IN_QS_MODE,				// The driver is not in quick switch mode
	GN2_CXP_CANT_SET_SPEED,			// Error setting CXP download speed
	GN2_CXP_POWER_ERROR,			// Error powering link
	GN2_BAD_TRIG_CONNECT,			// System does not know what type of trigger to connect
	GN2_BFML_INIT_ERROR,			// Error initializing BFML system
	GN2_BFML_UNKNOWN_FORMAT,		// BFML file contains unknown format or type
	GN2_BFML_UNKNOWN_SPEED,			// BFML file contains unknown CXP Link Speed
	GN2_TS_TABLE_EXCEEDED,			// Timing Sequence exceeds table capacity
	GN2_BAD_CAMERA_LINK_ID,			// Camera link IDs are not correct
	GN2_NOT_ENOUGH_LINKS,			// This VFG does not have the requested number of working links
	GN2_TOO_MANY_FRAMES,			// Sequence size is too big (too many frames)
	GN2_NOT_ENOUGH_PHYS,			// This Cyton does not have enough physical links for this camera
	GN2_WRONG_BFML_TYPE,			// The BFML file attached is for the wrong type of camera
	GN2_MISSING_CL_INI_FILE,		// The CL Front end INI file can not be found
	GN2_ERROR_PROG_CL_FE,			// Error programming the CL front end
	GN2_BAD_CL_INI_FILE,			// CL front end INI file contains bad values
	GN2_ERROR_END
} Gn2RC_Enum;

// Message truncation point:    _______12345678901234567890123456______________________________          


#define GN2_ERROR_ENTRIES	(GN2_ERROR_END - GN2_ERROR_START) 

#endif

