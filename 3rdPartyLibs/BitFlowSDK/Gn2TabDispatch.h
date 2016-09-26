//
// Creation:    Gn2TabDispatch.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved. 
//
// Description:
//
// Gn2 Driver Dispatcher
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__Gn2TABDISPATCH__)
#define __Gn2TABDISPATCH__

#if !defined(__R64TABDISPATCH__)
#include "R64TabDispatch.h"
#endif
//
// Driver IO Control Codes 
//

#define IOCTL_GN2_BASE							(IOCTL_R64_BASE + IOCTL_R64_ENTRIES)


#define IOCTL_GN2_DUMMY		          			CTL_CODE(DEVICE_TYPE_BF_GRABBER,  \
													IOCTL_GN2_BASE+0,\
													METHOD_BUFFERED,     \
													FILE_ANY_ACCESS)



#define IOCTL_GN2_ENTRIES						1

#endif

