/***************************************************************************
*
* BFIODef.h
*
* BFDiskIO API
* 
* Types and defines for BFIO library
*
* Copyright (C) 2002 by BitFlow, Inc.  All Rights Reserved.
*
* 10/22/2002	sms		created
*
***************************************************************************/

#if !defined(__BFIODEF__)
    #define __BFIODEF__

#include <BFType.h>

#ifdef __cplusplus
extern "C" {
#endif

// Error Codes
typedef struct _BFIOErrors
{
	int		ErrorCode;
	char	FailureDescription[256];

}BFIOErrors;

extern BFIOErrors BFIOErrorTable[];

typedef enum _DiskIOErr
{
	BF_ER_START = 7000,

	BF_CANCEL,				                // The cancel button was pressed
	BF_ER_AVI_WRITE_SINGLE,	                // Use BFIOWriteMultiple to write an AVI file.
	BF_ER_AVI_READ_SINGLE,                  // Use BFIOReadMultiple to read an AVI file.
	BF_ER_FILE_NAME,		                // No file name given
	BF_ER_BUF_POINTER,		                // Invalid buffer pointer
	BF_ER_NUM_BUFFERS,		                // Invalid number of buffers
	BF_ER_XSIZE,			                // Invalid XSize, not greater than zero
	BF_ER_YSIZE,			                // Inavlid YSize, not greater than zero
	BF_ER_BITDEPTH_UNKNOWN,                 // Bit depth must be 8, 10, 12, 14, 16, 24 or 32
	BF_ER_BITDEPTH_SWAPRGB,	                // Invalid bit depth for swap rgb option
	BF_ER_PACK24_BITDEPTH,	                // Must start with 32 bit data to use the 32TO24BIT option
	BF_ER_BMP_BIT_DEPTH,	                // Invalid bit depth for bmp
	BF_ER_BMP_OPEN_FILE,	                // Failed opening bmp file
	BF_ER_BMP_FILE_HEADER,	                // Failed writing bmp header to file
	BF_ER_BMP_DATA_WRITE,	                // Failed writing image data to bmp file
	BF_ER_BMP_DATA_READ,	                // Failed reading image data from bmp file.
	BF_ER_OPEN_FILE,		                // Could not open file from open dialog
	BF_ER_DATA_READ,		                // Error reading header from file in open dialog
	BF_ER_LOW_MEM,			                // Failed allocating memory.
	BF_ER_TIF_TAG,			                // Tif tag not supported
	BF_ER_TIF_BIT_DEPTH,	                // Invalid tif bit depth
	BF_ER_TIF_OPEN_FILE,	                // Failed opening tif file
	BF_ER_TIF_FILE_HEADER,	                // Failed writing tif header to file
	BF_ER_TIF_DATA_WRITE,	                // Failed writing image data to tif file
	BF_ER_TIF_DATA_READ,	                // Failed reading image data from tif file.
	BF_ER_RAW_OPEN_FILE,	                // Failed opening raw file
	BF_ER_RAW_DATA_WRITE,	                // Failed writing image data to raw file
	BF_ER_RAW_DATA_READ,	                // Failed reading image data from raw  file.
	BF_ER_AVI_BIT_DEPTH,	                // Invalid bit depth for avi
	BF_ER_AVI_OPEN_FILE,	                // Failed opening avi file
	BF_ER_AVI_DATA_WRITE,	                // Failed writing image data to the avi stream
	BF_ER_AVI_DATA_READ,	                // Failed reading image data from avi file.
	BF_ER_CREATE_STREAM,	                // Error creating AVI stream.
	BF_ER_SAVE_OPTIONS,		                // Error with dialog box save options
	BF_ER_COMPRESS_STREAM,	                // Error with compressing the stream.
	BF_ER_AVI_HEADER,		                // Error putting AVI header in the stream.
	BF_ER_FILE_FORMAT,		                // Invalid file format. Please use bmp, tiff, raw or avi 
	BF_ER_NUMBER_OF_FRAMES,	                // Number of frames asked for exceeds the number of frames the AVI file
	BF_ER_NO_DECOMPRESS,	                // Decompressing image to dimensions outside of maximum limit.
	BF_ER_RAW_READ_PARAMS,	                // Can not read image info such as XSize, YSize or bit depth from raw data
	BF_ER_RAW_OPEN_TEXTFILE,                // Failed to open the text file to write raw image file information.
	BF_ER_RAW_TEXT_WRITE,	                // Failed to write the data to the raw text file.
	BF_ER_FILE_EXISTS,		                // The file exists and the OVERWRITEFILE option is not being used.

    BF_ER_INVALID_PARAMS_STRUCT,            // The provided PBFIOParams structure pointer is null or invalid.
    BF_ER_INVALID_FILE_NAME_EXTENSION,      // The extension of the provided file name is not recognized.
    BF_ER_INVALID_IMAGE_FILE,               // The specified image file exists, but is corrupt or otherwise invalid.
    BF_ER_UNKNOWN_SENSOR_PATTERN,           // The specified sensor pattern code is not in BFIOParams_SensorPattern.
    BF_ER_INCOMPATIBLE_BIT_DEPTH,           // The specified bit-depth is not compatible with the image file bit-depth.

    BF_ER_DNG_SILENT,                       // The DNG SDK failed with an error the user shouldn't see.
    BF_ER_DNG_CANCELED,                     // The DNG SDK operation exited because it was canceled.
    BF_ER_DNG_MATRIX_ER,                    // The DNG SDK failed because of a matrix math error.
    BF_ER_DNG_DATA_READ,                    // The DNG SDK was unable to read the file data.
    BF_ER_DNG_DATA_WRITE,                   // The DNG SDK was unable to write the file data.
    BF_ER_DNG_PREMATURE_EOF,                // The DNG SDK reached the EOF prematurely.
    BF_ER_DNG_FILE_CORRUPT,                 // The image file is corrupted, and cannot be accessed.
    BF_ER_DNG_IMAGE_TOO_BIG,                // The image is too big to be handled.
    BF_ER_DNG_DNG_VERSION,                  // The DNG standard version of the file is not supported.
    BF_ER_UNKNOWN_DNG_SDK_ERROR,            // The DNG SDK returned an unknown error.

    BF_ER_UNKNOWN_COMPRESSION_FORMAT,       // The compression format is unknown to the library.
    BF_ER_UNSUPPORTED_COMPRESSION_FORMAT,   // The compression format is unsupported for the file type.
    BF_ER_UNSUPPORTED_COMPRESSION_LEVEL,    // The compression level is not supported.

    BF_ER_UNKNOWN_EXCEPTION,                // Caught an unknown exception.
    BF_ER_UNKNOWN_ERROR_CODE,               // The error code provided is not a BFDiskIO error return code.
    BF_ER_BAD_BUFFER_LENGTH,                // The buffer length argument was a null pointer, or indicated zero length.
	BF_ER_CANT_UPACK,						// Unpack option used for pixel depth that does not support packing/upacking.
	BF_ER_END
	
}DiskIOErr;

// Write option defines
#define SWAPRGB			2
#define PACK32TO24BIT	4
#define BOTTOM_UP		8
#define OVERWRITEFILE	16
#define AFPDF16FILES	32
#define AFPDF128FILES	64
#define AFPDF1024FILES	128
#define TWOXMODE		256
#define UNPACKPIXELS	512
#define UNPACKPIXELS_NO_SWAP 1024

// Sensor pattern enumeration.
typedef enum _BFIOParams_SensorPattern
{
    // Data has no encoded data (default).
    BFIO_Literal        = 0x00,
    // Plain gray sensor.
    BFIO_Monochrome     = BFIO_Literal,

    // Bayer sensors.
    BFIO_BayerGRBG      = 0x10,
    BFIO_BayerRGGB      = 0x11,
    BFIO_BayerBGGR      = 0x12,
    BFIO_BayerGBRG      = 0x13
} BFIOParams_SensorPattern;

// Codes used to specify the image thumbnail dimensions.
typedef enum _BFIOParams_ThumbnailDimensionFlags
{
    // Use the default size.
    BFIO_DefaultThumbnailSize = 0u,

    // Output a minimal (1x1), uncompressed thumbnail. Thumbnails are standard mandated for DNG images and,
    // this ensures a valid file that will open in standard editors, without incurring any rendering overhead.
    BFIO_EmptyThumbnail       = ~0u
} BFIOParams_ThumbnailDimensionFlags;

// Time-zone constants.
typedef enum _BFIOParams_TimeZoneConstants
{
    BFIO_TimeZone_UTC = 0,
    BFIO_TimeZone_Max = 15 * 60,
    BFIO_TimeZone_Min = -BFIO_TimeZone_Max
} BFIOParams_TimeZoneConstants;

// Date-time structure. Considered NULL, if Year == 0.
typedef struct _BFIOParams_DateTime
{
    // Date.
    BFU32 Year;     // BCE, 1970.
    BFU32 Month;    // 1-12 for January to December.
    BFU32 Day;      // Day of the Month.

    // Time.
    BFU32 Hour;     // 0-23
    BFU32 Minute;   // 0-59
    BFU32 Second;   // 0-59

    // Time zone offset from GMT in minutes (+/-).
    BFS32 TimeZoneOffset;
} BFIOParams_DateTime;

// Available compression formats. All are lossless.
typedef enum _BFIOParams_Compression
{
    BFIO_Uncompressed   = 0,
    BFIO_LZW            = 1,    // Prefer when compressing TIFF
    BFIO_JPEG           = 2,    // Only valid option to compress DNG
    BFIO_Deflate        = 3,
    BFIO_PackBits       = 4
} BFIOParams_Compression;

// The _BFIOParams struct used by the BFIO*Ex methods. Do not create on the stack.
// Retrieve a new instance with BFIOMakeExParams, and free using BFIOFreeExParams.
typedef struct _BFIOParams
{
    //// Private data for internal use only. Do not modify.
    void *pd;

    //// Composite parameters, using no prefix.
    BFIOParams_SensorPattern        sensorPattern;

    // Date, time and time zone information. If all values are set to zero, the value is considered null;
    // BFIOWriteSingleEx will query the system time, in this case.
    BFIOParams_DateTime             dateTime;

    // Size of the larger thumbnail dimension. See BFIOParams_ThumbnailDimensionFlags.
    BFU32                           thumbnailMaxDimension;

    // The kind of image compression used. DNG supports only Uncompressed and lossless JPEG; TIFF supports all encodings.
    BFIOParams_Compression          compression;

    // When writing a JPEG image, this should be a value in the range of -1 U [0, 12] (worst to best), where -1 is the
    // default value. This value cannot be read from an image, and ignored for JPEG compression in a TIFF or DNG
    // file, which always use lossless JPEG compression.
    BFS32                           compressionLevel;

    // Disable generation of the DNG raw image digest (MD5 sum). This can dramatically improve file generation
    // performance, but the written data will be less easily verified.
    BFBOOL                          disableRawDigest;
    
    //// EXIF parameters, using the "exif_" prefix.

    // String parameters. Null-pointer, for no data.
    const BFCHAR                    *exif_imageDescription;
    const BFCHAR                    *exif_make;
    const BFCHAR                    *exif_model;
    const BFCHAR                    *exif_artist;
    const BFCHAR                    *exif_copyright;
    const BFCHAR                    *exif_copyright2;
    const BFCHAR                    *exif_userComment;

    // Integer parameters. Set to -1, for no data.
    BFS32                           exif_subjectDistanceRange;
    BFS32                           exif_imageNumber;
} *PBFIOParams;

#ifdef __cplusplus
}
#endif

#endif /* __BFIODEF__ */