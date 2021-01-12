/*******************************************************************/
/*                                                                 */
/*                      ADOBE CONFIDENTIAL                         */
/*                   _ _ _ _ _ _ _ _ _ _ _ _ _                     */
/*                                                                 */
/* Copyright 2007 Adobe Systems Incorporated                       */
/* All Rights Reserved.                                            */
/*                                                                 */
/* NOTICE:  All information contained herein is, and remains the   */
/* property of Adobe Systems Incorporated and its suppliers, if    */
/* any.  The intellectual and technical concepts contained         */
/* herein are proprietary to Adobe Systems Incorporated and its    */
/* suppliers and may be covered by U.S. and Foreign Patents,       */
/* patents in process, and are protected by trade secret or        */
/* copyright law.  Dissemination of this information or            */
/* reproduction of this material is strictly forbidden unless      */
/* prior written permission is obtained from Adobe Systems         */
/* Incorporated.                                                   */
/*                                                                 */
/*******************************************************************/

/*
	Esso_Halftone.h
*/

#pragma once

#ifndef Esso_Halftone_H
#define Esso_Halftone_H

typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned short		u_int16;
typedef unsigned long		u_long;
typedef short int			int16;
#define PF_TABLE_BITS	12
#define PF_TABLE_SZ_16	4096

#define PF_DEEP_COLOR_AWARE 1	// make sure we get 16bpc pixels; 
								// AE_Effect.h checks for this.

#include "AEConfig.h"

#ifdef AE_OS_WIN
	typedef unsigned short PixelType;
	#include <Windows.h>
#endif

#include "entry.h"
#include "AE_Effect.h"
#include "AE_EffectCB.h"
#include "AE_Macros.h"
#include "Param_Utils.h"
#include "AE_EffectCBSuites.h"
#include "String_Utils.h"
#include "AE_GeneralPlug.h"
#include "AEFX_ChannelDepthTpl.h"
#include "AEGP_SuiteHandler.h"
#include "Esso_Halftone_Strings.h"




/* Versioning information */

#define	MAJOR_VERSION	1
#define	MINOR_VERSION	0
#define	BUG_VERSION		0
#define	STAGE_VERSION	PF_Stage_DEVELOP
#define	BUILD_VERSION	1


/* Parameter defaults */

#define	Esso_Halftone_SPACE_MIN		0
#define	Esso_Halftone_SPACE_MAX		1000
#define	Esso_Halftone_SPACE_DFLT	0

#define Esso_Halftone_SIZE_MIN        1
#define Esso_Halftone_SIZE_MAX        1000
#define Esso_Halftone_SIZE_DFLT        15

#define Esso_Halftone_CONT_MIN        -255
#define Esso_Halftone_CONT_MAX        255
#define Esso_Halftone_CONT_DFLT        0

#define Esso_Halftone_QUANT_MIN        1
#define Esso_Halftone_QUANT_MAX        128
#define Esso_Halftone_QUANT_DFLT        1


enum {
	Esso_Halftone_INPUT = 0,
    Esso_Halftone_SHAPE,
    Esso_Halftone_COLOR,
    Esso_Halftone_SIZE,
	Esso_Halftone_SPACE,
    Esso_Halftone_QUANT,
    Esso_Halftone_CONT,
	Esso_Halftone_INVERT,
    Esso_Halftone_ALPHA,
    Esso_Halftone_MASK,
	Esso_Halftone_NUM_PARAMS
};




enum {
	SHAPE_DISK_ID = 1,
    COLOR_DISK_ID,
	SIZE_DISK_ID,
    SPACE_DISK_ID,
    QUANT_DISK_ID,
    CONT_DISK_ID,
    INVET_DISK_ID,
    ALPHA_DISK_ID,
    MASK_DISK_ID,
};

typedef struct GainInfo{
    A_long Shape;
	PF_FpLong	Space;
    A_long    Quant;
    PF_FpLong    Contrast;
    PF_FpLong    Size;
    PF_Pixel pcolor;
    A_long Invert;
    A_long Mask;
    A_long Alpha;
    A_long greythreshold;
    A_FpLong dif;
    PF_LayerDef in_lay;
    PF_LayerDef out_lay;
} GainInfo, *GainInfoP, **GainInfoH;


extern "C" {

	DllExport
	PF_Err
	EffectMain(
		PF_Cmd			cmd,
		PF_InData		*in_data,
		PF_OutData		*out_data,
		PF_ParamDef		*params[],
		PF_LayerDef		*output,
		void			*extra);

}

enum {

    Esso_Halftone_CIRCLE =1 ,
    Esso_Halftone_BOX,
    Esso_Halftone_TRIANGLE,
    Esso_Halftone_DIAMOND,
    Esso_Halftone_MAZE,
     Esso_Halftone_RANDOM,
    Esso_Halftone_SHAPE_NUM_CHOICES
};

#endif // Esso_Halftone_H
