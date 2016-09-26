#include "BiApi.h"

#include "BFException.hpp"

#include <vector>

/**
 * \namespace CXPReg
 *
 * \brief Class library for CoaXPress camera register access.
 */

/**
 * \class CXPReg::Device
 *
 * \brief Interface to access and modify registers on a CoaXPress camera.
 *
 * The CXPReg::Device class provides an independent interface to CoaXPres registers,
 * as exposed by BitFlow frame grabbers. This may be used simultaneously with the
 * \ref BufferAcquisition classes, or completely independently.
 * \ref BufferAcquisition::BufferInterface implements its own CXP register methods.
 */

namespace CXPReg
{
    // Class to access the CXP camera register of a device on a specified BitFlow board.
    class BFDLL Device
    {
    public:
        Device (BFVOID);
        ~Device (BFVOID);

        // Open a board with the given index.
        BFVOID open (const BFU32 boardNumber);
        
        // Open a board with the given switch setting and connector index.
        BFVOID openSWConnector (const BFU32 Switch, const BFU32 Connector);

        // Close the currently open board, if any.
        BFVOID close (BFVOID);

	    // Returns if a board is open or not.
	    BFBOOL isOpen (BFVOID) const;

        // Returns whether or not the open board is a CXP board or not. If not,
        // than the CXP register functions will fail.
        BFBOOL isCxp (BFVOID) const;

        // Return the opened board number. Returns ~BFU32(0), if the board isn't open, or wasn't
        // opened with a board number (see getBoardSWConnector).
        BFU32 getBoardNumber (BFVOID) const;
    
        // Retrieve the opened board switch and connector. Retrieves ~BFU32(0), if the board isn't
        // open, or wasn't opened with openSWConnector (see getBoardNumber).
        BFVOID getBoardSWConnector (BFU32 &Switch, BFU32 &Connector) const;

        // Read the value of the CXP register at the given address.
        BFU32 readReg (const BFU32 address) const;
        BFU32 readReg (const BFU32 link, const BFU32 address) const;
        
        // Write the value of the CXP register at the given address.
        BFVOID writeReg (const BFU32 address, const BFU32 value);
        BFVOID writeReg (const BFU32 link, const BFU32 address, const BFU32 value);
        
        // Read the values from a sequence of CoaXPress registers, returning
        // the length of data read. Store as much of the output data as can be
        // in the dataOut buffer, dropping any data that won't fit. In the variants
        // using std::vector, the vector will be resized to fit at least the size
        // of bytesToRead.
        BFSIZET readData (const BFU32 address, const BFU32 bytesToRead, std::vector<BFU8> &dataOut) const;
        BFSIZET readData (const BFU32 address, const BFU32 bytesToRead, BFU8 *const dataOut, const BFSIZET dataOutSize) const;
        BFSIZET readData (const BFU32 link, const BFU32 address, const BFU32 bytesToRead, std::vector<BFU8> &dataOut) const;
        BFSIZET readData (const BFU32 link, const BFU32 address, const BFU32 bytesToRead, BFU8 *const dataOut, const BFSIZET dataOutSize) const;

        // Write data to a sequence of CoaXPress registers.
        BFVOID writeData (const BFU32 address, std::vector<BFU8> const& dataIn);
        BFVOID writeData (const BFU32 address, const BFU8 *const dataIn, const BFSIZET dataInSize);
        BFVOID writeData (const BFU32 link, const BFU32 address, std::vector<BFU8> const& dataIn);
        BFVOID writeData (const BFU32 link, const BFU32 address, const BFU8 *const dataIn, const BFSIZET dataInSize);

    private:
        struct PrivateData;
        PrivateData &m_pd;

        // Device is non-copyable.
        Device (Device const&);
        Device& operator= (Device const&);
    };
}
