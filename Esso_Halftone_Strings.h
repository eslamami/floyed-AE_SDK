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

#pragma once

typedef enum {
	StrID_NONE, 
	StrID_Name,
	StrID_Description,
    StrID_Shape_Param_Name,
    StrID_Color_Param_Name,
    StrID_Size_Param_Name,
	StrID_Space_Param_Name,
    StrID_Quant_Param_Name,
    StrID_Cont_Param_Name,
    StrID_Invert_Param_Name,
    StrID_ALPHA_Param_Name,
    StrID_Mask_Param_Name,
    StrID_ShapeModes_Param_Name,
	StrID_NUMTYPES
} StrIDType;
