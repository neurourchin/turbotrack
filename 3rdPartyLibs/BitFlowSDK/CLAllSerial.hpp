#include <BFSerial.h>
#include <clallserial.h>

#include <BFException.hpp>

#include <string>
#include <vector>

/**
 * \namespace CLComm
 *
 * \brief Class library for the Camera Link serial port API.
 */
namespace CLComm
{
    /**
     * \class CLComm::CLAllSerial
     *
     * \brief Wrapper around the Camera Link serial port API.
     *
     * Both the \ref CLAllSerial.h and \ref BFSerial.h interfaces are exposed, although the BitFlow serial
     * functions will only be operable for ports on BitFlow boards.
     */
    class BFDLL CLAllSerial
    {
    public:
        CLAllSerial (BFVOID);
        ~CLAllSerial (BFVOID);
       
        // Converts an error code to error text which can be displayed in a dialog box or in the standard I/O window.
        static std::string getErrorText (const CLINT32 ErrorCode);
        static BFBOOL getErrorText (const CLINT32 ErrorCode, BFCHAR *const hBuf, BFSIZET *const pSize);

        // Returns the number of Camera Link serial ports in this machine that are supported by clallserial.dll.
        static CLUINT32 getNumPorts (BFVOID);

        // Provides information about the port specified by the serial index.
        static BFVOID getPortInfo (const CLUINT32 SerialIndex, std::string &ManufacturerName, std::string &PortID, CLUINT32 &Version);
        static BFBOOL getPortInfo (const CLUINT32 SerialIndex, BFCHAR *const ManufacturerName, BFSIZET *const pManNameSize, BFCHAR *const PortID, BFSIZET *const pPortIdSize, CLUINT32 &Version);

        // Retrieve the version of the loaded BFS library.
        static BFVOID bfsVersion (CLUINT32 &majorVersionRef, CLUINT32 &minorVersionRef);

        // Initializes the device referred to by serialIndex. Only CL boards are considered a serial device. If the underlying
        // CLSerial device is not a BitFlow device, the BFSerial extensions will not be enabled, and hasBFSerial will return false.
        BFVOID serialInit (const CLUINT32 SerialIndex);
       
        // Alternate initializer, initializing from a BitFlow board index, rather than from the
        // CLSerial port index, which may or may not directly correspond.
        BFVOID bfSerialInit (const CLUINT32 BoardIndex);
        
        // Alternate initializer, initializing from a BitFlow board swith and connector, rather than from the
        // CLSerial port index, which may or may not directly correspond.
        BFVOID bfSWConnectorSerialInit (const CLUINT32 Switch, const CLUINT32 Connector);

        // Closes the serial device and cleans up resources associated with it. Does nothing, if the device is not Initialized.
        BFVOID serialClose (BFVOID);

        // Return whether or not a port has been initialized.
        BFBOOL hasInit (BFVOID) const;

        // Return whether or not the opened port supports the BitFlow CLSerial extensions.
        BFBOOL hasBFSerial (BFVOID) const;

        // Retrieve the serial index initialized, or ~CLUINT32(0), if not open or not initialized by the serial index.
        CLUINT32 getSerialIndex (void) const;

        // Retrieve the BitFlow board number initialized, or ~CLUINT32(0), if not open or not initialized by the BitFlow board nubmer.
        CLUINT32 getBoardNumber (void) const;
        
        // Retrieve the BitFlow Switch and Connector initialized, or ~CLUINT32(0), if not open or not initialized by Switch and Connector.
        void getSWConnector (CLUINT32 &Switch, CLUINT32 &Connector) const;

        // This method writes a string of characters to the serial device, returning the number of bytes written.
        CLUINT32 serialWrite (std::string const& Message, const CLUINT32 SerialTimeout);

        // This method writes data to the serial device, returning the number of bytes written.
        CLUINT32 serialWrite (std::vector<CLINT8> const& Buffer, const CLUINT32 SerialTimeout);
        CLUINT32 serialWrite (const CLINT8 *const Buffer, const BFSIZET BufferLen, const CLUINT32 SerialTimeout);

        // Reads data from the serial device.
        std::string serialRead (const CLUINT32 NumBytesToRead, const CLUINT32 SerialTimeout);

        // Reads data from the serial device, returning the number of bytes read.
        CLUINT32 serialRead (std::vector<CLINT8> &Buffer, const CLUINT32 ReadLen, const CLUINT32 SerialTimeout) const;
        CLUINT32 serialRead (CLINT8 *const Buffer, const CLUINT32 BufferSize, const CLUINT32 SerialTimeout) const;

        // Discards any bytes that are available in the input buffer.
        BFVOID flushPort (BFVOID);

        // Returns the number of bytes that are received, but not yet read out of the the serial device.
        CLUINT32 getNumBytesAvail (BFVOID) const;

        // Returns the valid baud rates of the interface.
        CLUINT32 getSupportedBaudRates (BFVOID) const;

        // Sets the Baud Rate for the serial port.
        BFVOID setBaudRate (const CLUINT32 BaudRate);

        // Set the BF CLSerial settings.
        BFVOID bfSerialSettings (const CLUINT32 BaudRate, const DataBits dataBits, const Parity parity, const StopBits stopBits);
        
        // Reads data from the serial device. This method will wait efficiently for data to become
        // available on the port, then return that length of data. No more than <paramref name="MaxBytesToRead"/>
        // will be read at a time, but the length read may be less than that.
        std::string bfSerialRead (const CLUINT32 MaxBytesToRead) const;

        // Reads data from the serial device. This method will wait efficiently for data to become
        // available on the port, then return that length of data. Returns the number of bytes read.
        CLUINT32 bfSerialRead (std::vector<BFCHAR> &Buffer, const CLUINT32 MaxBytesToRead) const;
        CLUINT32 bfSerialRead (PBFCHAR Buffer, const CLUINT32 MaxBytesToRead) const;

        // Cancel the active call to clBFSerialRead.
        BFVOID bfSerialCancelRead (BFVOID);
        
        // Return the current baud-rate of the CLSerial port.
        CLUINT32 bfGetBaudRate (BFVOID) const;

    private:
        struct PrivateData;
        PrivateData &m_pd;

        // The class is non-copyable.
        CLAllSerial (CLAllSerial const&);
        CLAllSerial& operator= (CLAllSerial const&);
    };
    
    /**
     * \class CLComm::BFCLException
     *
     * \brief Exception thrown for \ref CLAllSerial.h and \ref BFSerial.h API errors.
     *
     * Possible \ref CLAllSerial.h errors are:
     *  - \ref CL_ERR_NO_ERR
     *  - \ref CL_ERR_BUFFER_TOO_SMALL
     *  - \ref CL_ERR_MANU_DOES_NOT_EXIST
     *  - \ref CL_ERR_PORT_IN_USE
     *  - \ref CL_ERR_TIMEOUT
     *  - \ref CL_ERR_INVALID_INDEX
     *  - \ref CL_ERR_INVALID_REFERENCE
     *  - \ref CL_ERR_ERROR_NOT_FOUND
     *  - \ref CL_ERR_BAUD_RATE_NOT_SUPPORTED
     *  - \ref CL_ERR_OUT_OF_MEMORY
     *  - \ref CL_ERR_REGISTRY_KEY_NOT_FOUND
     *  - \ref CL_ERR_INVALID_PTR
     *  - \ref CL_ERR_UNABLE_TO_LOAD_DLL
     *  - \ref CL_ERR_FUNCTION_NOT_FOUND
     *
     * Possible \ref BFSerial.h errors are:
     *  - \ref BFCL_ERROR_SERNOTFOUND
     *  - \ref BFCL_ERROR_BRDNOTFOUND
     *  - \ref BFCL_ERROR_BRDOPEN
     *  - \ref BFCL_ERROR_THRE
     *  - \ref BFCL_ERROR_TEMT
     *  - \ref BFCL_ERROR_FIFO_EN
     *  - \ref BFCL_ERROR_RCVRFIFO
     *  - \ref BFCL_ERROR_BAUDRATE
     *  - \ref BFCL_ERROR_DATABITS
     *  - \ref BFCL_ERROR_PARITY
     *  - \ref BFCL_ERROR_15STOP5DATA
     *  - \ref BFCL_ERROR_2STOP5DATA
     *  - \ref BFCL_ERROR_STOPBITS
     *  - \ref BFCL_ERROR_NOSIGNAL
     *  - \ref BFCL_ERROR_NOSTRUC
     *  - \ref BFCL_ERROR_NULLPTR
     *  - \ref BFCL_ERROR_BYTES_AVAIL
     *  - \ref BFCL_ERROR_FLUSH_PORT
     *  - \ref BFCL_ERROR_DATA_IN
     */
    class BFDLL BFCLException : public BFExceptionBase
    {
    public:
        // Throw a BFCLException, if errorCode isn't CL_ERR_NO_ERR.
        static BFVOID check (const CLINT32 errorCode);

        // No error constructor.
        BFCLException (void);

        // Error constructor.
        BFCLException (const CLINT32 number);
        
        // Copy constructors.
        BFCLException (BFCLException const& to_copy);
        BFCLException (BFCLException &&to_take);

        // Copy operator.
        BFCLException& operator= (BFCLException const& to_copy);
        BFCLException& operator= (BFCLException &&to_take);
    };
}
