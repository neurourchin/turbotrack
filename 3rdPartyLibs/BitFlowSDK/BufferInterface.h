#pragma once
#include "BiApi.h"
#include "BFException.hpp"

#include <string>
#include <vector>

/*! \mainpage Buffer Interface Class Library
 *
 * \section intro_sec Overview
 *
 * The Buffer Interface Class Library provides a C++ wrapper around the
 * BitFlow's C based BufferAcquisition API for sequence and circular image acquisition.
 * There are several advantages to using the Buffer Interface class library
 * over the BufferAcquisition API. Some of the advantages are:
 *	-# Fewer method/function calls to accomplish sequence or circular capture.
 *	-# No need to call cleanup methods/functions.
 *	-# Fewer method/function parameters.
 *	-# Improved error handling by throwing exceptions.
 *
 * This document provides class informatation on the sequence and circular
 * acquistion classes, along with examples of how to use the classes to
 * acquire from Bitflow's extensive line of framegrabbers.
 *
 * \subsection bufin_sec BufferAcquisition
 *
 * The primary component of Buffer Interface library is the \ref BufferAcquisition::BufferInterface class, and
 * its two child classes:
 *  -# \ref BufferAcquisition::SequenceInterface - An interface to acquire a fixed-length buffer sequences.
 *   Each buffer is acquired once, at which point acquisition automatically stops.
 *  -# \ref BufferAcquisition::CircularInterface - An interface to acquire images continuously in a circular
 *   buffer. Acquisition continues indefinitely, until explicitly stopped.
 *
 * \subsection control_sec Control Interfaces
 *
 * To facilitate control of cameras, two additional libraries are provided:
 *  -# CLComm - An interface to the Camera Link serial port library. This wraps both the standard \ref CLAllSerial.h
 *   interface, and the \ref BFSerial.h library, which provides various useful extensions to the core library.
 *  -# CXPReg - An interface to CoaXPress camera register space. The CXP registry may also be controled using
 *   the cxp* methods of the \ref BufferAcquisition::BufferInterface class.
 */

/**
 * \namespace BufferAcquisition
 *
 * \brief Class library for BitFlow frame grabber acquisition.
 */
namespace BufferAcquisition
{
    /**
     * \class BufferAcquisition::BufferInterface
     *
     * \brief Base class for buffered acquisition using a BitFlow frame grabber.
     *
     * The BufferInterface class provides the common functionality
     * used by the Sequence and Circular Interface classes.
     *
     * \see BufferAcquisition::SequenceInterface
     * \see BufferAcquisition::CircularInterface
     */
    class BFDLL BufferInterface
    {
    public:
        // Forward declaration of the dependent Properties class. See: BufferInterfaceProperties.h
        class Properties;

        // Constructor
	    BufferInterface (BFVOID);

        // Destructor
	    virtual ~BufferInterface (BFVOID);

        // Return the number of boards installed on this system.
        static BFU32 boardCount (BFVOID);

	    // Opens board for acquisition.
	    BFVOID open (const BFU32 brdNumber);

	    // Opens board for acquisition with specified options
	    BFVOID open (const BFU32 brdNumber, const BFU32 options);

	    // Opens board for acquisition and loads the camera file given.
	    BFVOID open (const BFU32 brdNumber, std::string const& camFileName);
	    BFVOID open (const BFU32 brdNumber, const BFCHAR *const camFileName);
	
	    // Opens board for acquisition and loads the camera file given with specified options.
	    BFVOID open (const BFU32 brdNumber, std::string const& camFileName, const BFU32 options);
	    BFVOID open (const BFU32 brdNumber, const BFCHAR *const camFileName, const BFU32 options);

        // Opens board for acquisition given the specified switch and connector.
        BFVOID openSWConnector (const BFU32 Switch, const BFU32 Connector);

        // Opens board for acquisition given the specified switch and connector.
        BFVOID openSWConnector (const BFU32 Switch, const BFU32 Connector, const BFU32 options);
	
	    // Closes board resources.
	    BFVOID close (BFVOID);
        
	    /**
	     * Returns the board handle. This will be useful when using other
	     * BitFlow APIs.
	     * @return Returns the board handle.
	     */
	    inline Bd getBoardHandle (BFVOID) const
        {
            return m_hBoard;
        }

        // Return the opened board number. Returns ~BFU32(0), if the board isn't open, or wasn't
        // opened with a board number (see getBoardSWConnector).
        BFU32 getBoardNumber (BFVOID) const;
    
        // Retrieve the opened board switch and connector. Retrieves ~BFU32(0), if the board isn't
        // open, or wasn't opened with openSWConnector (see getBoardNumber).
        BFVOID getBoardSWConnector (BFU32 &Switch, BFU32 &Connector);

        // Retrieve a list of modes supported by the current camera file, returning the number
        // of modes determined. R64 and older board models to not support multi-mode camera files,
        // and no modes will be returned for that case.
        BFSIZET enumerateCameraModes (std::vector<std::string> &modes, std::vector<std::string> &descriptions = std::vector<std::string>()) const;
        BFBOOL enumerateCameraMode (const BFSIZET index, BFCHAR *const modeBuf, BFSIZET *const pModeSize, BFCHAR *const descBuf, BFSIZET *const pDescSize) const;
    
        // Get the current camera mode's name. R64 and older board models do not support camera modes.
        std::string getCameraMode (BFVOID) const;
        BFBOOL getCameraMode (BFCHAR *const modeBuf, BFSIZET *const pModeSize) const;

        // Set the current camera mode to that named. R64 and older board models do not support camera modes.
        BFVOID setCameraMode (std::string const& modeName);
        BFVOID setCameraMode (const BFCHAR *const modeName);
    
        // Set the size of the acquired frame.
        BFVOID setAcqFrameSize (const BFU32 XSize, const BFU32 YSize);

        // Set the Region Of Interest (ROI) of the acquired frame.
        BFVOID setAcqROI (const BFU32 XOffset, const BFU32 YOffset, const BFU32 XSize, const BFU32 YSize);

        // Connect or disconnect the external hardware trigger circuitry.
        BFVOID setExTriggerConnect (const CiTrigSelect trigger = CiTrigA, const BFU32 state = BFExTrigConnect);
    
        // Programs the New Timing Generator (NTG).
        BFVOID setExposureControl (const BFDOUBLE ExposurePeriod, const BFDOUBLE LineFramePeriod, const BFU32 TriggerMode, const BFBOOL AssertedHigh, const BFU32 OutputSignal);
    
        // Retrieve the current configuration of the New Timing Generator (NTG).
        BFVOID getExposureControl (BFDOUBLE &ExposurePeriod, BFDOUBLE &LineFramePeriod, BFU32 &TriggerMode, BFBOOL &AssertedHigh, BFU32 &OutputSignal) const;

	    // Returns a pointer to the array of pointers to the buffers.
	    PBFU32* getBufferArrayPointers (BFVOID);
	    const PBFU32* getBufferArrayPointers (BFVOID) const;
	
	    // Returns information about the board and camera file.
	    BFU32 getBrdInfo (const BFU32 brdInqVar) const;
	
	    // Returns the number of frames that have been captured.
	    BFU32 getNumFramesCaptured (BFVOID) const;
	
	    // Returns the number of frames that where missed during acquisition.
	    BFU32 getNumFramesMissed (BFVOID) const;
	
	    // If returns TRUE <=> a start command has been issued.
	    BFBOOL getStartAcqFlag (BFVOID) const;
	
	    // If returns TRUE <=> a stop command has been issued.
	    BFBOOL getStopAcqFlag (BFVOID) const;
	
	    // If returns TRUE <=> an abort command has been issued.
	    BFBOOL getAbortAcqFlag (BFVOID) const;
	
	    // If returns TRUE <=> a pause command has been issued.
	    BFBOOL getPauseAcqFlag (BFVOID) const;
	
	    // If returns TRUE <=> instance cleanup has occured.
	    BFBOOL getCleanupAcqFlag (BFVOID) const;

	    // Returns the major version of the Bi API.
	    static BFU32 getMajorVersion (BFVOID);
	
	    // Returns the minor version of the Bi API.
	    static BFU32 getMinorVersion (BFVOID);

	    // Sets the hardware trigger mode
	    BFVOID setTriggerMode (const BFU32 triggerMode = BiTrigFreeRun, const BFU32 trigPolarity = BiTrigAssertedHigh);
	
	    // Returns the current hardware trigger mode of the board.
	    BFU32 getTriggerMode (BFVOID) const;
	
	    // Returns the current hardware trigger polarity.
	    BFU32 getTriggerPolarity (BFVOID) const;
	
	    // Issues a software trigger.
	    BFVOID issueSoftwareTrigger (const BFU32 trigMode = BiTrigAssertTrigA);
	
	    // Displays dialog describing error
	    BFU32 showError (const BFU32 errorNum) const;

	    // Write a single buffer to disk.
	    BFVOID writeBuffer (PBFCHAR fileName, const BFSIZET fileNameSize, const BFU32 bufferNumber, const BFU32 options) const;
        BFVOID writeBuffer (std::string const& fileName, const BFU32 bufferNumber, const BFU32 options) const;

	    // Write a sequence of buffers to disk. 
	    BFVOID writeSeqBuffer (PBFCHAR fileName, const BFSIZET fileNameSize, const BFU32 firstBufNumber, const BFU32 numBufs, const BFU32 Options) const;
	    BFVOID writeSeqBuffer (std::string const& fileName, const BFU32 firstBufNumber, const BFU32 numBufs, const BFU32 Options) const;

	    // read a sequence of files into memory.
	    BFVOID readSeqFile (std::string const& fileName, const BFU32 firstBufNumber, const BFU32 numBufs);
	    BFVOID readSeqFile (const BFCHAR *const fileName, const BFU32 firstBufNumber, const BFU32 numBufs);

	    // Clears all buffers memory
	    BFVOID clearBuffers (BFVOID);

	    // Returns the error text for a specific error number
        std::string getErrorText (const BFU32 errorNumber) const;
	    BFVOID getErrorText (const BFU32 errorNumber, PBFCHAR errorText, const PBFU32 errorTextSize) const;

	    // Returns the number of buffers software is behind the hardware DMA engine.
	    BFU32 getBufferQueueSize (BFVOID) const;
	
	    // Set Buffer acquisition timeout.
	    BFVOID setTimeout (const BFU32 TimeoutValue);

	    // Loads a camera file for the board to use.
	    BFVOID loadCamFile (std::string const& camFileName);
	    BFVOID loadCamFile (const BFCHAR *const camFileName);

	    // Unloads a camera file loaded by the loadCamFile method.
	    BFVOID unloadCamFile (BFVOID);

        //// CoaXPress Register Accessors and Modifiers

        // Read the value of a single CoaXPress register.
        BFU32 cxpReadReg (const BFU32 address) const;
        BFU32 cxpReadReg (const BFU32 link, const BFU32 address) const;

        // Write the value of a single CoaXPress register.
        BFVOID cxpWriteReg (const BFU32 address, const BFU32 value);
        BFVOID cxpWriteReg (const BFU32 link, const BFU32 address, const BFU32 value);

        // Read the values from a sequence of CoaXPress registers, returning
        // the length of data read. Store as much of the output data as can be
        // in the dataOut buffer, dropping any data that won't fit. In the variants
        // using std::vector, the vector will be resized to fit at least the size
        // of bytesToRead.
        BFSIZET cxpReadData (const BFU32 address, const BFU32 bytesToRead, std::vector<BFU8> &dataOut) const;
        BFSIZET cxpReadData (const BFU32 address, const BFU32 bytesToRead, BFU8 *const dataOut, const BFSIZET dataOutSize) const;
        BFSIZET cxpReadData (const BFU32 link, const BFU32 address, const BFU32 bytesToRead, std::vector<BFU8> &dataOut) const;
        BFSIZET cxpReadData (const BFU32 link, const BFU32 address, const BFU32 bytesToRead, BFU8 *const dataOut, const BFSIZET dataOutSize) const;

        // Write data to a sequence of CoaXPress registers.
        BFVOID cxpWriteData (const BFU32 address, std::vector<BFU8> const& dataIn);
        BFVOID cxpWriteData (const BFU32 address, const BFU8 *const dataIn, const BFSIZET dataInSize);
        BFVOID cxpWriteData (const BFU32 link, const BFU32 address, std::vector<BFU8> const& dataIn);
        BFVOID cxpWriteData (const BFU32 link, const BFU32 address, const BFU8 *const dataIn, const BFSIZET dataInSize);

        //// BitFlow Frame Grabber Register Methods

        // Retrieve the name of the frame grabber register at the given index.
        std::string bfRegName (const BFU32 RegId) const;
        BFVOID bfRegName (const BFU32 RegId, PBFCHAR nameBuf, const BFSIZET nameBufSize) const;
    
        // Return the index of the given frame grabber register name, or REG_UNDEFINED,
        // if there is no register with that name.
        BFU32 bfRegId (std::string const& regName) const;
        BFU32 bfRegId (const BFCHAR *const regName) const;

        // Peek the value at the given frame grabber register index.
        BFU32 bfRegPeek (const BFU32 RegId) const;
    
        // Poke the value at the given frame grabber register index.
        BFVOID bfRegPoke (const BFU32 RegId, const BFU32 Value);

	    // Returns if the board is open or not
	    BFBOOL isBoardOpen (BFVOID) const;

	    // Returns if the board is setup or not
	    BFBOOL isBoardSetup (BFVOID) const;

        // Retrieve a reference to the BufferInterface::Properties.
        BufferInterface::Properties const& properties (void) const;

    protected:
	    /** Handle to the opened board */
	    Bd m_hBoard;
	
	    /** Bi info structure */		
	    mutable BIBA m_BufferArray;	

	    /** A pointer to a loaded camera file */
	    PBFCNF m_pCam;

	    BFBOOL isMemAssigned;
	    BFBOOL isMemAllocated;
	    BFBOOL isSetup;
	    BFBOOL isOpen;

    private:
        // Private data members.
        struct PrivateData;
        PrivateData &m_pd;

        // BufferInterface is non-copyable.
        BufferInterface (BufferInterface const&);
        BufferInterface& operator= (BufferInterface const&);
    };
}
