#ifndef INCLUDED__BITFLOW_INC__B_F_RESOLVE_GEN_T_L__H
#define INCLUDED__BITFLOW_INC__B_F_RESOLVE_GEN_T_L__H

/* FILE:        BFResolveGenTL.h
 * DATE:        8/27/2015
 * AUTHOR:      Jeremy Greene
 * COMPANY:     BitFlow, Inc.
 * COPYRIGHT:   Copyright (C) 2015, BitFlow, Inc.
 * DESCRIPTION: Include the contemporaneous release of the GenTL standard header file, or
 *              whichever version is specified by the BF_RESOLVE_GENTL_H_VERSION macro.
 */

#if !defined(BF_RESOLVE_GENTL_H_VERSION)
#   define BF_RESOLVE_GENTL_H_VERSION (0x00010005)
#endif

#if   BF_RESOLVE_GENTL_H_VERSION == 0x00010005
#   include <TLI/GenTL_v1_5.h>
#elif BF_RESOLVE_GENTL_H_VERSION == 0x00010004
#   include <TLI/GenTL_v1_4.h>
#elif BF_RESOLVE_GENTL_H_VERSION == 0x00010003
#   include <TLI/GenTL_v1_3.h>
#elif BF_RESOLVE_GENTL_H_VERSION == 0x00010002
#   include <TLI/GenTL_v1_2.h>
#elif BF_RESOLVE_GENTL_H_VERSION == 0x00010001
#   include <TLI/GenTL_v1_1.h>
#elif BF_RESOLVE_GENTL_H_VERSION == 0x00010000
#   include <TLI/GenTL_v1_0.h>
#elif BF_RESOLVE_GENTL_H_VERSION == 0xFFFFFFFF
#   include <TLI/GenTL.h>
#elif BF_RESOLVE_GENTL_H_VERSION == 0
#   // NoOp.
#else
#   error BF_RESOLVE_GENTL_H_VERSION an unsupported GenTL header file release.
#endif

#endif // INCLUDED__BITFLOW_INC__B_F_RESOLVE_GEN_T_L__H
