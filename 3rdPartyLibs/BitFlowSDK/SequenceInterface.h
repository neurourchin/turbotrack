#pragma once
#include "BufferInterface.h"
#include "BiApi.h"

namespace BufferAcquisition
{
    /**
     * \class BufferAcquisition::SequenceInterface
     * 
     * \brief Acquire a sequence of images using a BitFlow frame grabber.
     *
     * An interface to acquire a fixed-length buffer sequences. In a sequence acquisition,
     * each buffer is acquired once, at which point acquisition automatically stops.
     *
     * \see BufferAcquisition::BufferInterface
     * \see BufferAcquisition::CircularInterface
     */
    class BFDLL SequenceInterface : public BufferInterface
    {
    public:
	    // create instance
	    SequenceInterface (BFVOID);

	    // create instance and open board
	    SequenceInterface (const BFU32 brdNumber);
	
	    // create instance and open and setup board.
	    SequenceInterface (const BFU32 brdNumber, const BFU32 numBuffers, const BFU32 options);

	    // create instance, open and setup the board with the buffers aligned
	    // on a specified alignment boundary.
	    SequenceInterface (const BFU32 brdNumber, const BFU32 numBuffers, const BFU32 options, const BFSIZET alignment);
	
	    ~SequenceInterface (BFVOID);
		
	    // Sets up the board for sequence acquisition.
	    BFVOID setup (const BFU32 numBuffers, const BFU32 options);

	    // Sets up the board for sequence acquisition aligning each buffer
	    // on a specified alignment boundary.
	    BFVOID setup (const BFU32 numBuffers, const BFU32 options, const BFSIZET alignment);
 
	    // Sets up the board for sequence acquisition.
	    BFVOID setup (PBFU32 *const pMemArray, const BFU32 numBuffers, const BFU32 options);
	
	    // Frees resources allocated by setup.
	    BFVOID cleanup (BFVOID);
	
	    // Change default acquisition settings.
	    BFVOID setSettings (const BFU32 startFrame, const BFU32 numFrames, const BFU32 skipFrames);
	
	    // Wait for sequence to be acquired. 
	    BFU32 seqWaitDone (const BFU32 timeout) const;
	
	    // Issue sequence commands.
	    BFVOID seqControl (const BFU32 command, const BFU32 options);
	
	    // Wait for error.
	    BFU32 seqErrorWait (BFVOID) const;
	
	    // Returns error from error stack.
	    BFU32 getSeqError (BFVOID);
	
	    // Returns the current frame being acquired.
	    BFU32 getCurFrameAcquired (BFVOID) const;
	
	    // Returns when a frame has been DMAed into memory.
	    BFU32 waitDoneFrame (const BFU32 timeout) const;
	
	    // Returns info about a buffer.
	    BiSeqInfo getBufferInfo (const BFU32 bufferNumber) const;
	
	    // Clears buffer information for all buffers.
	    BFVOID clearBufferInfo (BFVOID);
    };

    /** 
     * @example BiSimplePlusPlus.cpp
     * This is an example of how to use the SequenceInterface class.
     */
}
