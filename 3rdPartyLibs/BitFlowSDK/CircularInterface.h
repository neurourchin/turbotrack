#pragma once
#include "BufferInterface.h"
#include "BiApi.h"

namespace BufferAcquisition
{
    /**
     * \class BufferAcquisition::CircularInterface
     * 
     * \brief Acquire images into a circular buffer using a BitFlow frame grabber.
     *
     * An interface to acquire images continuously in a circular buffer. In a circular
     * acquisition continues indefinitely, until explicitly stopped.
     *
     * \see BufferAcquisition::BufferInterface
     * \see BufferAcquisition::SequenceInterface
     */
    class BFDLL CircularInterface : public BufferInterface
    {
    public:
	    // create instance
	    CircularInterface (BFVOID);

	    // create instance and open board.
	    CircularInterface (const BFU32 brdNumber);
	
	    // create instance, open and setup board.
	    CircularInterface (const BFU32 brdNumber, const BFU32 numBuffers, const BFU32 errorMode, const BFU32 options);

	    // create instance, open and setup the board with the buffers aligned
	    // on a specified alignment boundary.
	    CircularInterface (const BFU32 brdNumber, const BFU32 numBuffers, const BFU32 errorMode, const BFU32 options, const BFSIZET alignment);
	
	    ~CircularInterface (BFVOID);

	    // Sets up the board for circular acquisition.
	    BFVOID setup (const BFU32 numBuffers, const BFU32 errorMode, const BFU32 options);

	    // Sets up the board for circular acquisition aligning each buffer
	    // on a specified alignment boundary.
	    BFVOID setup (const BFU32 numBuffers, const BFU32 errorMode, const BFU32 options, const BFSIZET alignment);

	    // Sets up the board for sequence acquisition.
	    BFVOID setup (PBFU32 *const pMemArray, const BFU32 numBuffers, const BFU32 errorMode, const BFU32 options); 

	    // Frees resources allocated by setup.
	    BFVOID cleanup (BFVOID); 
	
	    // Issue circular commands.
	    BFVOID cirControl (const BFU32 command, const BFU32 options);
	
	    // Wait for error.
	    BFU32 cirErrorWait (BFVOID) const;

	    // Returns error from the error stack
	    BFRC getCirError (BFVOID);

	    // Returns when a frame has been DMAed into memory.
	    BFU32 waitDoneFrame (const BFU32 timeout, const PBiCirHandle CirHandle) const;

	    // Set status of a buffer to BIAVAILABLE or BIHOLD
	    BFU32 setBufferStatus (BiCirHandle &cirHandle, const BFU32 status);

	    // Set status of a buffer to BIAVAILABLE or BIHOLD
	    BFU32 setBufferStatus (const BFU32 bufferNumber, const BFU32 status);

	    // Returns the status of a buffer
	    BFU32 getBufferStatus (BiCirHandle const& cirHandle) const;

	    // Returns the status of the buffer
	    BFU32 getBufferStatus (const BFU32 bufferNumber) const;

	    // SMS - in the future
	    //BFVOID setNextBufferForAcq(BFU32 bufferNumber);
	    //BFVOID addAdditionalBuffers(BFU32 numBuffers);

    };

    /** 
     * @example CircClassExample.cpp
     * This is an example of how to use the CircularInterface class.
     */

    /**
     * @example CircHoldSimple.cpp
     * This console application demonstrates the holding of buffers.
     */
}
