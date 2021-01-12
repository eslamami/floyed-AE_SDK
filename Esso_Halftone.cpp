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

/*	Esso_Halftone.cpp	

	This is a compiling husk of a project. Fill it in with interesting
	pixel processing code.
	
	Revision History

	Version		Change													Engineer	Date
	=======		======													========	======
	1.0			(seemed like a good idea at the time)					bbb			6/1/2002

	1.0			Okay, I'm leaving the version at 1.0,					bbb			2/15/2006
				for obvious reasons; you're going to 
				copy these files directly! This is the
				first XCode version, though.

	1.0			Let's simplify this barebones sample					zal			11/11/2010

	1.0			Added new entry point									zal			9/18/2017

*/




#include "Esso_Halftone.h"




static PF_Err 
About (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	
	suites.ANSICallbacksSuite1()->sprintf(	out_data->return_msg,
											"%s v%d.%d\r%s",
											STR(StrID_Name), 
											MAJOR_VERSION, 
											MINOR_VERSION, 
											STR(StrID_Description));
	return PF_Err_NONE;
}

static PF_Err 
GlobalSetup (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	out_data->my_version = PF_VERSION(	MAJOR_VERSION, 
										MINOR_VERSION,
										BUG_VERSION, 
										STAGE_VERSION, 
										BUILD_VERSION);

	out_data->out_flags =  PF_OutFlag_DEEP_COLOR_AWARE;	// just 16bpc, not 32bpc
	
	return PF_Err_NONE;
}

static PF_Err 
ParamsSetup (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err		err		= PF_Err_NONE;
	PF_ParamDef	def;	

         AEFX_CLR_STRUCT(def);
     PF_ADD_POPUP(STR(StrID_Shape_Param_Name),
                  Esso_Halftone_SHAPE_NUM_CHOICES-1 , 0,
                  STR(StrID_ShapeModes_Param_Name),
                  SHAPE_DISK_ID);
     
     AEFX_CLR_STRUCT(def);

     PF_ADD_COLOR(     STR(StrID_Color_Param_Name),
                     PF_HALF_CHAN8,
                     PF_MAX_CHAN8,
                     PF_MAX_CHAN8,
                     COLOR_DISK_ID);
     
     AEFX_CLR_STRUCT(def);

     PF_ADD_FLOAT_SLIDERX(    STR(StrID_Size_Param_Name),
                         Esso_Halftone_SIZE_MIN,
                         Esso_Halftone_SIZE_MAX,
                         Esso_Halftone_SIZE_MIN,
                         Esso_Halftone_SIZE_MAX,
                         Esso_Halftone_SIZE_DFLT,
                             PF_Precision_HUNDREDTHS,
                             0,
                             0,
                             SIZE_DISK_ID);
     
	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(	STR(StrID_Space_Param_Name), 
							Esso_Halftone_SPACE_MIN, 
							Esso_Halftone_SPACE_MAX, 
							Esso_Halftone_SPACE_MIN, 
							Esso_Halftone_SPACE_MAX, 
							Esso_Halftone_SPACE_DFLT,
							PF_Precision_HUNDREDTHS,
							0,
							0,
							SPACE_DISK_ID);
     
     AEFX_CLR_STRUCT(def);

     PF_ADD_FLOAT_SLIDERX(     STR(StrID_Quant_Param_Name),
                             Esso_Halftone_QUANT_MIN,
                             Esso_Halftone_QUANT_MAX,
                             Esso_Halftone_QUANT_MIN,
                             Esso_Halftone_QUANT_MAX,
                             Esso_Halftone_QUANT_DFLT,
                             PF_Precision_HUNDREDTHS,
                             0,
                             0,
                             QUANT_DISK_ID);
     
     AEFX_CLR_STRUCT(def);

     PF_ADD_FLOAT_SLIDERX(     STR(StrID_Cont_Param_Name),
                             Esso_Halftone_CONT_MIN,
                             Esso_Halftone_CONT_MAX,
                             Esso_Halftone_CONT_MIN,
                             Esso_Halftone_CONT_MAX,
                             Esso_Halftone_CONT_DFLT,
                             PF_Precision_HUNDREDTHS,
                             0,
                             0,
                             CONT_DISK_ID);
     
     
     

     
          AEFX_CLR_STRUCT(def);
     
     PF_ADD_CHECKBOXX(STR(StrID_Invert_Param_Name),
                      false,
                      PF_ParamFlag_NONE,
                      INVET_DISK_ID);
     
     AEFX_CLR_STRUCT(def);
     PF_ADD_PERCENT(STR(StrID_ALPHA_Param_Name), 100,  ALPHA_DISK_ID);
     
          AEFX_CLR_STRUCT(def);
     
     PF_ADD_CHECKBOXX(STR(StrID_Mask_Param_Name),
                      false,
                      PF_ParamFlag_NONE,
                      MASK_DISK_ID);


  


    
    
    
    
    
    
    

	
	out_data->num_params = Esso_Halftone_NUM_PARAMS;

	return err;
}









static PF_Err
MySimpleGainFunc16 (
	void		*refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err		err = PF_Err_NONE;

	GainInfo	*giP	= reinterpret_cast<GainInfo*>(refcon);
	PF_FpLong	tmp_space	= 0;
					
	if (giP){
		tmp_space = giP->Space * PF_MAX_CHAN16 / 100.0;
		if (tmp_space > PF_MAX_CHAN16){
			tmp_space = PF_MAX_CHAN16;
		};

		outP->alpha		=	inP->alpha;
		outP->red		=	MIN((inP->red	+ (A_u_char) tmp_space), PF_MAX_CHAN16);
		outP->green		=	MIN((inP->green	+ (A_u_char) tmp_space), PF_MAX_CHAN16);
		outP->blue		=	MIN((inP->blue	+ (A_u_char) tmp_space), PF_MAX_CHAN16);
	}

	return err;
}





PF_Pixel16 *sampleIntegral64(PF_EffectWorld &def, int x, int y){
  assert(PF_WORLD_IS_DEEP(&def));
  return (PF_Pixel16*)((char*)def.data +
    (y * def.rowbytes) +
    (x * sizeof(PF_Pixel16)));
}

A_long getgrey64(PF_Pixel16 *color ){
     A_long g ;
     g = (color->red * .3 )+ (color->green * .59) + (color->blue * .11) ;
     if(color->alpha < PF_MAX_CHAN16 ) g = color->alpha ;
     
     return g ;
}

void setgrey64(PF_Pixel16 *color , A_long g ){
     
     color->red          = g ;
     color->green          = g;
     color->blue          =  g;
}

A_long getValidGray64(A_long a_value){
    if(a_value < 0) return 0;
    if(a_value > PF_MAX_CHAN16) return PF_MAX_CHAN16;
    return a_value;
}



A_long contrasty64 (A_long g, A_FpLong val ){
     g = getValidGray64( g /128) ;
     A_FpLong factor = (259 * (val + 255)) / (255 * (259 - val)) ;
     A_long vg  = factor * (g   - 128) + 128 ;
    return ( getValidGray64(vg*128)) ;
 
}

PF_Pixel *sampleIntegral32(PF_EffectWorld &def, int x, int y){
  return (PF_Pixel*)((char*)def.data +
    (y * def.rowbytes) +
    (x * sizeof(PF_Pixel)));
}


A_long getgrey(PF_Pixel *color ){
     A_long g ;
     g = (color->red * .3 )+ (color->green * .59) + (color->blue * .11) ;
     if(color->alpha < PF_MAX_CHAN8 ) g = color->alpha ;
     
     return g ;
}

void setgrey(PF_Pixel *color , A_long g ){
     
     color->red          = g ;
     color->green          = g;
     color->blue          =  g;
}

A_long getValidGray(A_long a_value){
    if(a_value < 0) return 0;
    if(a_value > 255) return 255;
    return a_value;
}


A_long contrasty (A_long g, A_FpLong val ){
     
     A_FpLong factor = (259 * (val + 255)) / (255 * (259 - val)) ;
     A_long vg  = factor * (g   - 128) + 128 ;
    return ( getValidGray(vg)) ;
 
}


int index (A_long x , A_long y, A_long W){
     return x + y * W ;
}


static PF_Err
circlehalftone (
    void        *refcon,
    A_long        xL,
    A_long        yL,
    PF_Pixel8    *inP,
    PF_Pixel8    *outP)
{
    PF_Err        err = PF_Err_NONE;

    
    
    
         GainInfo    *giP    = reinterpret_cast<GainInfo*>(refcon);
         A_long    tmp_space    = 0;
         A_long    tmp_size    = 0;
         A_long    tmp_sizehalf    = 0;
     PF_Pixel8 pcol = {0,0,0,0};
     A_FpLong temp_grey  ;

    A_long xo = 0;
    A_long yo = 0;
    A_long xc = 0;
    A_long yc = 0;
     A_long rad = 0;
     A_long modintrval = 0 ;

     
    if (giP){
        tmp_size = giP->Size;
        tmp_space = giP->Space ;
        pcol =giP->pcolor;
        tmp_sizehalf = tmp_size/2 ;
         modintrval = tmp_size+tmp_space;

         

    }

    return err;
}
 

 

static PF_Err
circlehalftone64 (
void        *refcon,
A_long        xL,
A_long        yL,
PF_Pixel16    *inP,
PF_Pixel16    *outP)
{
    PF_Err        err = PF_Err_NONE;

    
    
    
         GainInfo    *giP    = reinterpret_cast<GainInfo*>(refcon);
         A_long    tmp_space    = 0;
         A_long    tmp_size    = 0;
         A_long    tmp_sizehalf    = 0;
     PF_Pixel8 pcol = {0,0,0,0};
         PF_Pixel16 pcol16 = {0,0,0,0};
     A_FpLong temp_grey  ;

    A_long xo = 0;
    A_long yo = 0;
    A_long xc = 0;
    A_long yc = 0;
     A_long rad = 0;
     A_long modintrval = 0 ;

     
    if (giP){
        tmp_size = giP->Size;
        tmp_space = giP->Space ;
        pcol =giP->pcolor;
        
        pcol16.red = getValidGray64(pcol.red *128);
        pcol16.green = getValidGray64(pcol.green *128);
        pcol16.blue = getValidGray64(pcol.blue *128);
        pcol16.alpha = getValidGray64(pcol.alpha *128);
        
        tmp_sizehalf = tmp_size/2 ;
         modintrval = tmp_size+tmp_space;

         
         //init all pixels
         outP->alpha     = 0;
         outP->red          = inP->red ;
         outP->green          = inP->green;
         outP->blue          =  inP->blue;
        

         

         
         
         
         
         
                  

        if( tmp_size != 0 &&
           (xL % modintrval) < tmp_size &&
           (yL % modintrval) < tmp_size
           ){
             // the origin
             xo = xL - (xL % modintrval) ;
             yo = yL - (yL % modintrval)  ;

            // the origied coordinates
            xc = xL- xo - tmp_sizehalf  ;
            yc = yL- yo - tmp_sizehalf  ;
           
             // the upper left center coord
             A_long xul = xL- xo  ;
             A_long yul = yL- yo   ;
            
             // sample the origin pixel
             PF_Pixel16 pix =  *sampleIntegral64(giP->in_lay, xo, yo);
            
             temp_grey =  getgrey64(&pix);



                    
             srand(temp_grey) ;
             A_long randy = rand() % 5+1 ;
             A_long printr = rand() % 100 + 1 ;
             if(giP->Shape != Esso_Halftone_RANDOM) randy = 0 ;
             
             temp_grey = contrasty64(temp_grey,giP->Contrast  ) ;
             
             temp_grey = round(temp_grey / giP->Quant) *giP->Quant ;
             
             // tmp_grey Ratio


             if(giP->Invert ){
                  temp_grey = ( PF_MAX_CHAN16 - temp_grey )/ PF_MAX_CHAN16 ;
                  
             }else{
                   temp_grey = temp_grey / PF_MAX_CHAN16 ;
             }

             
             // the raduis ratio from greyscale
                 rad =  (A_long)( tmp_sizehalf * temp_grey)   ;


                    A_FpLong fac = ((A_FpLong)(giP->Alpha) ) / 100  ;


            // printf("this is rad %d \n", rad) ;
             
             // prepasre the alpha
             A_u_short a = inP->alpha * temp_grey ;
             a = a  + ((PF_MAX_CHAN16 - a)* (1- fac) )  ;
             
                // draw a circle
            if ( (giP->Shape == Esso_Halftone_CIRCLE ||
                 randy == Esso_Halftone_CIRCLE) &&
                (xc*xc + yc*yc) <= (rad*rad) && rad!=0
                ){
                    outP->alpha     =  a  ;
                    outP->red        =  pcol16.red;
                    outP->green        = pcol16.green;
                    outP->blue        =  pcol16.blue;
                 
                 if(giP->Mask){
                      outP->alpha     = a  ;
                      outP->red        = inP->red;
                      outP->green        = inP->green;
                      outP->blue        =  inP->blue;
                              }
                      
                 if ((xc*xc + yc*yc) == (rad*rad)){
                      outP->alpha     = a/2;
                      outP->red        = pcol16.red;
                      outP->green        = pcol16.green;
                      outP->blue        =  pcol16.blue;
                      
                      if(giP->Mask){
                           outP->alpha     = a/2;
                           outP->red        = inP->red;
                           outP->green        = inP->green;
                           outP->blue        =  inP->blue;
                                   }
                 }

                    }
             
             // draw rectangle
             if ( (giP->Shape == Esso_Halftone_BOX ||
             randy == Esso_Halftone_BOX) &&
                 abs(xc) < rad &&
                  abs(yc) < rad
                 ){
                             outP->alpha     = a  ;
                             outP->red        = pcol16.red;
                             outP->green        = pcol16.green;
                             outP->blue        =  pcol16.blue;
                  
                  if(giP->Mask){
                       outP->alpha     = a  ;
                       outP->red        = inP->red;
                       outP->green        = inP->green;
                       outP->blue        =  inP->blue;
                               }
             }
                 
             
             
             
             
             // draw triangle
             if ( (giP->Shape == Esso_Halftone_TRIANGLE  ||
                   randy == Esso_Halftone_TRIANGLE ) &&
                             xul/2 <=  yul &&
                             yul -rad <= rad-xul/2 && rad!=0
                 ){
                              outP->alpha     = a    ;
                              outP->red        = pcol16.red;
                              outP->green        = pcol16.green;
                              outP->blue        =  pcol16.blue;
                  
                  if(giP->Mask){
                       outP->alpha     = a   ;
                       outP->red        = inP->red;
                       outP->green        = inP->green;
                       outP->blue        =  inP->blue;
                               }
                  
                  if(xul/2 ==  yul &&
                     yul -rad == rad-xul/2 ){
                       
                       outP->alpha     = a /2 ;

                       
                  }
                         }
             
             
                // draw Daimond

             if ( (giP->Shape == Esso_Halftone_DIAMOND  ||
                   randy == Esso_Halftone_DIAMOND ) &&
                  -xul < yul-rad &&
                 xul > yul-rad &&
                 xul-rad< yul &&
                 yul-rad < (rad*2)-xul && rad!=0
                 
                 ){
                              outP->alpha     = a   ;
                              outP->red        = pcol16.red;
                              outP->green        = pcol16.green;
                              outP->blue        =  pcol16.blue;
                  
                  if(giP->Mask){
                       outP->alpha     = a  ;
                       outP->red        = inP->red;
                       outP->green        = inP->green;
                       outP->blue        =  inP->blue;
                               }

                    }
             
             if (( giP->Shape == Esso_Halftone_DIAMOND  ||
                  randy == Esso_Halftone_DIAMOND ) &&
                  -xul == yul-rad &&
                 xul == yul-rad &&
                 xul-rad == yul &&
                 yul-rad == (rad*2)-xul
                 
                 ){
                  outP->alpha     = a/2 ;
                  outP->red        = pcol16.red;
                  outP->green        = pcol16.green;
                  outP->blue        =  pcol16.blue;
                  if(giP->Mask){
                       outP->alpha     = a/2;
                       outP->red        = inP->red;
                       outP->green        = inP->green;
                       outP->blue        =  inP->blue;
                               }
             }

             
             
             /// maze option
             A_FpLong lw = giP->Size /7 ;
             if (temp_grey >= .5 &&
                ( giP->Shape == Esso_Halftone_MAZE  ||
                 randy == Esso_Halftone_MAZE ) &&
                 yul-xul  < lw &&
                 yul-xul > -lw

                 ){
                              outP->alpha     = a    ;
                              outP->red        = pcol16.red;
                              outP->green        = pcol16.green;
                              outP->blue        =  pcol16.blue;
                  
                  if(giP->Mask){
                       outP->alpha     = a  ;
                       outP->red        = inP->red;
                       outP->green        = inP->green;
                       outP->blue        =  inP->blue;
                               }

                    }
             if ( temp_grey < .5 &&
                 (giP->Shape == Esso_Halftone_MAZE  ||
                 randy == Esso_Halftone_MAZE ) &&
                 yul-(tmp_size -xul)  < lw  &&
                 yul-(tmp_size -xul)  > -lw

                 ){
                              outP->alpha     = a   ;
                              outP->red        = pcol16.red;
                              outP->green        = pcol16.green;
                              outP->blue        =  pcol16.blue;
                  
                  if(giP->Mask){
                       outP->alpha     = a   ;
                       outP->red        = inP->red;
                       outP->green        = inP->green;
                       outP->blue        =  inP->blue;
                               }

                    }
             
             // random

             

        }


    }

    return err;
}
 








static PF_Err 
Render (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output
        ){
     
	PF_Err				err		= PF_Err_NONE;
	AEGP_SuiteHandler	suites(in_data->pica_basicP);



	/*	Put interesting code here. */
	GainInfo			giP;
	AEFX_CLR_STRUCT(giP);
	A_long				linesL	= 0;

	linesL 		= output->extent_hint.bottom - output->extent_hint.top;
     giP.Shape =  params[Esso_Halftone_SHAPE]->u.pd.value ;
     giP.Space 	= params[Esso_Halftone_SPACE]->u.fs_d.value* in_data->downsample_x.num / in_data->downsample_x.den ;
     giP.Size     = params[Esso_Halftone_SIZE]->u.fs_d.value * in_data->downsample_x.num / in_data->downsample_x.den ;
     giP.Contrast = params[Esso_Halftone_CONT]->u.fs_d.value;
     giP.Quant = params[Esso_Halftone_QUANT]->u.fs_d.value;
     
     giP.Alpha = FIX_2_FLOAT(params[Esso_Halftone_ALPHA]->u.fd.value) ;
     giP.pcolor     =  params[Esso_Halftone_COLOR]->u.cd.value ;
     giP.Invert =  params[Esso_Halftone_INVERT]->u.bd.value ;
     giP.Mask  =params[Esso_Halftone_MASK]->u.bd.value ;
     giP.in_lay = params[Esso_Halftone_INPUT]->u.ld ;

     giP.out_lay  = *output ;
     giP.greythreshold = 0 ;

            A_long fac = giP.Size ;
            

            
            A_long wid = giP.in_lay.width ;
            A_long hig = giP.in_lay.height ;

     if (!PF_WORLD_IS_DEEP(output)) {
     for (int yP = 1 ; yP < hig-1 ; yP++ ){
          for(int  xP = 1 ; xP< wid-1 ; xP++ ){
               
          PF_Pixel *myPixel = sampleIntegral32(  params[Esso_Halftone_INPUT]->u.ld  , xP , yP );
         PF_Pixel *myPixelout = sampleIntegral32( *output  , xP , yP );
               
               
                       PF_Pixel tmp ;
                       //Quantize all image
               
                       tmp.alpha     = myPixel->alpha ;
                       tmp.red          = round( fac * (myPixel->red )/ PF_MAX_CHAN8) *(PF_MAX_CHAN8/fac) ;
                       tmp.green          = round( fac * (myPixel->green) / PF_MAX_CHAN8) *(PF_MAX_CHAN8/fac);
                       tmp.blue          =  round( fac * (myPixel->blue) / PF_MAX_CHAN8) *(PF_MAX_CHAN8/fac) ;
               
                       A_FpShort errR = myPixel->red - tmp.red;
                       A_FpShort errG = myPixel->green - tmp.green;
                       A_FpShort  errB = myPixel->blue - tmp.blue;

               myPixelout->alpha     = tmp.alpha  ;
               myPixelout->red          = tmp.red   ;
               myPixelout->green          = tmp.green  ;
               myPixelout->blue          =  tmp.blue   ;
                       
                       
               /// read th epixels and add amount from the error to it
        PF_Pixel *myPixel1 = sampleIntegral32(  params[Esso_Halftone_INPUT]->u.ld  , xP + 1 , yP );
        PF_Pixel *myPixel1out = sampleIntegral32( *output  , xP + 1 , yP );
               myPixel1out->alpha = PF_MAX_CHAN8 ;
            myPixel1out->red = myPixel1->red + errR * 7/16.0  ;
            myPixel1out->green = myPixel1->green + errG * 7/16.0  ;
            myPixel1out->blue = myPixel1->blue + errB * 7/16.0  ;
            
                 
        PF_Pixel *myPixel2 = sampleIntegral32(  params[Esso_Halftone_INPUT]->u.ld  , xP - 1 , yP+1 );
        PF_Pixel *myPixel2out = sampleIntegral32(*output , xP - 1 , yP+1 );
                myPixel2out->alpha = PF_MAX_CHAN8 ;
            myPixel2out->red = myPixel2->red + errR * 3/16.0  ;
            myPixel2out->green = myPixel2->green + errG * 3/16.0  ;
            myPixel2out->blue =myPixel2->blue + errB * 3/16.0  ;
               

        PF_Pixel *myPixel3 = sampleIntegral32(  params[Esso_Halftone_INPUT]->u.ld  , xP, yP + 1 );
         PF_Pixel *myPixel3out = sampleIntegral32( *output  , xP, yP + 1 );
                 myPixel3out->alpha = PF_MAX_CHAN8 ;
            myPixel3out->red = myPixel3->red + errR * 5/16.0  ;
            myPixel3out->green =myPixel3->green + errG * 5/16.0 ;
            myPixel3out->blue = myPixel3->blue + errB * 5/16.0  ;

               
        PF_Pixel *myPixel4 = sampleIntegral32(  params[Esso_Halftone_INPUT]->u.ld  , xP + 1 , yP+1 );
         PF_Pixel *myPixel4out = sampleIntegral32( *output  , xP + 1 , yP+1 );
                 myPixel4out->alpha = PF_MAX_CHAN8 ;
            myPixel4out->red = myPixel4->red + errR * 1/16.0 ;
            myPixel4out->green = myPixel4->green + errG * 1/16.0  ;
            myPixel4out->blue = myPixel4->blue + errB * 1/16.0  ;
            }
     }
     
}
     
     
	if (PF_WORLD_IS_DEEP(output)){

		ERR(suites.Iterate16Suite1()->iterate(	in_data,
												0,								// progress base
												linesL,							// progress final
												&params[Esso_Halftone_INPUT]->u.ld,	// src
												NULL,							// area - null for all pixels
												(void*)&giP,					// refcon - your custom data pointer
												circlehalftone64,				// pixel function pointer
												output));
	}

	return err;
}


extern "C" DllExport
PF_Err PluginDataEntryFunction(
	PF_PluginDataPtr inPtr,
	PF_PluginDataCB inPluginDataCallBackPtr,
	SPBasicSuite* inSPBasicSuitePtr,
	const char* inHostName,
	const char* inHostVersion)
{
	PF_Err result = PF_Err_INVALID_CALLBACK;

	result = PF_REGISTER_EFFECT(
		inPtr,
		inPluginDataCallBackPtr,
		"Esso_Halftone", // Name
		"ADBE Esso_Halftone", // Match Name
		"Sample Plug-ins", // Category
		AE_RESERVED_INFO); // Reserved Info

	return result;
}


PF_Err
EffectMain(
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra)
{
	PF_Err		err = PF_Err_NONE;
	
	try {
		switch (cmd) {
			case PF_Cmd_ABOUT:

				err = About(in_data,
							out_data,
							params,
							output);
				break;
				
			case PF_Cmd_GLOBAL_SETUP:

				err = GlobalSetup(	in_data,
									out_data,
									params,
									output);
				break;
				
			case PF_Cmd_PARAMS_SETUP:

				err = ParamsSetup(	in_data,
									out_data,
									params,
									output);
				break;
				
			case PF_Cmd_RENDER:

				err = Render(	in_data,
								out_data,
								params,
								output);
				break;
		}
	}
	catch(PF_Err &thrown_err){
		err = thrown_err;
	}
	return err;
}

