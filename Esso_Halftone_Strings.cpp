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

#include "Esso_Halftone.h"

typedef struct {
	A_u_long	index;
	A_char		str[256];
} TableString;



TableString		g_strs[StrID_NUMTYPES] = {
	StrID_NONE,						"",
	StrID_Name,						"esso Sizes",
	StrID_Description,				"An tasty empty (skeletal, if you will) effect sample,\r for your modifying pleasure.\rCopyright 2007 Adobe Systems Incorporated.",
    StrID_Shape_Param_Name,     "Shape",
    StrID_Color_Param_Name,     "Color",
    StrID_Size_Param_Name,      "Size",
    StrID_Space_Param_Name,     "Space",
    StrID_Quant_Param_Name,     "Roughen",
    StrID_Cont_Param_Name,     "Contrast",
    StrID_Invert_Param_Name,    "Invert",
    StrID_ALPHA_Param_Name,     "Alpha",
    StrID_Mask_Param_Name,      "Reveal Original",
    StrID_ShapeModes_Param_Name,          "Circle|Square|Triangle|Daimond|Maze|Random",

    
};



char	*GetStringPtr(int strNum)
{
	return g_strs[strNum].str;
}
	
