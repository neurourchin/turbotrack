#pragma once

#include <BFType.h>

#include <string>

/**
 * \class BFExceptionBase
 * \brief Base class of all BitFlow exception classes.
 */
class BFDLL BFExceptionBase
{
public:
    // Non-error constructor.
    BFExceptionBase (void);

    // Copy constructors.
    BFExceptionBase (BFExceptionBase const& to_copy);
    BFExceptionBase (BFExceptionBase &&to_take);

    // Destructor.
    virtual ~BFExceptionBase (void);
    
    // Copy operator.
    BFExceptionBase& operator= (BFExceptionBase const& to_copy);
    BFExceptionBase& operator= (BFExceptionBase &&to_take);

	// Returns an text based message of an error that has occured. The default implementation
    // invokes the std::string getErrorText method, internally, but will not throw an exception.
	virtual BFU32 getErrorText (PBFCHAR ErrorText, PBFU32 ErrorTextSize) const;
    
    // Return the error text as a std::string. Throws a BFException on any error.
    virtual std::string getErrorText (void) const;

	// Returns the error number of the error that occured.
	virtual BFU32 getErrorNumber (void) const;

    // Display a dialog box for this exception.
    virtual BFU32 showErrorMsg (void) const;

protected:
    // Error constructor.
    BFExceptionBase (const BFU32 number, std::string const& message);
    BFExceptionBase (const BFU32 number, std::string &&message);

private:
    struct PrivateData;
    PrivateData *m_pd;
};

/**
 * \typedef BFException
 * \brief typedef of \ref BFExceptionBase.
 */
typedef BFExceptionBase BFException;

/**
 * \class BFCiException
 *
 * \brief Exception thrown when a BitFlow SDK error occurs.
 *
 * \note This is based upon the BF/CiApi error stack, not the BiApi error stack.
 *
 * \see BFRC_Enum
 */
class BFDLL BFCiException : public BFExceptionBase
{
public:
    // Throw a BFCiException for the error if the error isn't BF_OK.
    static void check (Bd hBoard, const BFU32 error);

    // Return the Bi error message for given board and code.
    static std::string getErrorText (Bd hBoard, const BFU32 error);
    
    // Non-error constructor.
    BFCiException (void);
    
    // Error constructors.
    BFCiException (Bd hBoard, const BFU32 error);

    // Copy constructors.
    BFCiException (BFCiException const& to_copy);
    BFCiException (BFCiException &&to_take);

    // Copy operator.
    BFCiException& operator= (BFCiException const& to_copy);
    BFCiException& operator= (BFCiException &&to_take);
};

/**
 * \class BiException
 *
 * \brief Exception thrown when a BitFlow SDK error occurs.
 *
 * \note This is based upon the BiApi error stack, not the BF/CiApi error stack.
 *
 * \see BIRC_Enum
 */
class BFDLL BiException : public BFExceptionBase
{
public:
    // Throw a BFException for the error if the error isn't BF_OK.
    static void check (Bd hBoard, const BFU32 error);

    // Return the BF/Ci error message for given board and code.
    static std::string getErrorText (Bd hBoard, const BFU32 error);
    
    // Non-error constructor.
    BiException (void);
    
    // Error constructors.
    BiException (Bd hBoard, const BFU32 error);

    // Copy constructors.
    BiException (BiException const& to_copy);
    BiException (BiException &&to_take);

    // Copy operator.
    BiException& operator= (BiException const& to_copy);
    BiException& operator= (BiException &&to_take);
    
    // Display a dialog box for this exception.
    virtual BFU32 showErrorMsg (void) const;
};
