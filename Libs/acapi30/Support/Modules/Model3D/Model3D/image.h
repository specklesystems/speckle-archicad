/****************************************************************************/
/*																			*/
/*					GLOBAL CONSTANTS, TYPES AND MACROS FOR IMAGER			*/
/*																			*/
/****************************************************************************/

#ifndef _image_H_
#define _image_H_

#pragma once

#include 	"Channel.hpp"

#include	"GSUtilsDefs.h"


#include	"Model3D/LGHT.hpp"
#include	"Model3D/UMAT.hpp"
#include	"Model3D/UFIL.hpp"
#include	"Model3D/RTXT.hpp"

/*================================	CONSTANTS	============================*/

#define	FILLER_RATIO	0.25

/*
**	WARNING !!!
**		If you make any changes in material types contact to
**		:E:AC3Xinc.h
**		vv94.02.03
*/
#define	GENERAL_MATER	0		/* General material type					*/
#define	SIMPLE_MATER	1		/* Reduced parameter set material type		*/

#define	MATTE_MATER		2		/* Matte material type						*/
#define	METAL_MATER		3		/* Metal material type						*/
#define	PLASTIC_MATER	4		/* Plastic material type					*/

#define	GLASS_MATER		5		/* Glass material type						*/
#define	GLOWING_MATER	6		/* Glowing material type					*/

#define	CONST_MATER		7		/* Constant material type					*/
		/*sl970221*/

#define	FILLED_MATER	10		/* Additional value to material types		*/

#define	TEXTURE_MATER	20		/* Additional value to material types		*/

/* COLMAX --> GSUtilsDefs.h */
/* AMBMAX, DIFFMAX, SPECMAX, TRANSMAX --> IMPCMAX */
#define	IMPCMAX			100.0
#define	IMPCMAXF		100.0f
#define	IMPCMAXI		100

/* SHINMUL, EATTMUL, TATTMUL --> SHIATTMUL, in AttributeManager.hpp */

#define	SHIATTMUL	100.0

#define	SHINMAX			100
#define	TATTMAX			4
#define	TRANSP_MAX		99.0
#define	TRANSP_LIMIT	70.0
#define	TRANSP_MIDDLE	50.0
#define	TRANSP_SMALL	30.0

#define	FALLMUL			1.0

/*	For FMATs						material with texture with alpha channel*/
#define	ALPHA_MAT		0x0080				/*	0b0000000010000000	*/
/*	For FMATs							material with constant colour		*/
#define	CONST_MAT		0x0040				/*	0b0000000001000000	*/
/*	For FMATs							material emits light				*/
#define	EMITT_MAT		0x0020				/*	0b0000000000100000	*/
/*	For FMATs,ACTIVEPGONs (in RE.c)		transparent material				*/
#define	TRANS_MAT		0x0010				/*	0b0000000000010000	*/

#define	TRANSP_EPS		0.001
#define	TRANSP_EPS_PC	0.1			/* TRANSP_EPS * IMPCMAX */

#define	SUMMEDAREATABLE	0x8000		/* 0100000000000000 */	/* DELBIT ... !!!!	*/

#define	TEXMIRRORY		0x0800		/* 0000100000000000 */	/*	==> 256 in GDL	*/
#define	TEXMIRRORX		0x0400		/* 0000010000000000 */	/*	==> 128 in GDL	*/
#define	RANDOMSHIFT		0x0200		/* 0000001000000000 */	/*	==>  64 in GDL	*/

#define	SURFACEPATTERN	0x0100		/* 0000000100000000	*/	/*	==>  32 in GDL	*/
#define	AMBIENTPATTERN	0x0080		/* 0000000010000000	*/	/*	==>  16 in GDL	*/
#define	SPECULARPATTERN	0x0040		/* 0000000001000000	*/	/*	==>   8 in GDL	*/
#define	DIFFUSEPATTERN	0x0020		/* 0000000000100000	*/	/*	==>   4 in GDL	*/
#define	BUMPMAPPATTERN	0x0010		/* 0000000000010000 */	/*	==>   2 in GDL	*/
#define	TRANSPARPATTERN	0x0008		/* 0000000000001000	*/	/*	==>   1 in GDL	*/

#define	FILLRECTNATUR	0x0004		/* 0000000000000100 */	/*	==>   4 in GDL PICTURE	*/
#define	FITPICTNATUR	0x0002		/* 0000000000000010 */	/*	==>   2 in GDL PICTURE	*/
#define	USETEXALFA		0x0001		/* 0000000000000001 */	/*	==>   1 in GDL PICTURE & PIPG	*/

#define	TEXTURELINKMAT	0x1000	/* 0001000000000000 */

#define	TXTPROPERTYBITS	(TEXTURELINKMAT | TEXMIRRORY | TEXMIRRORX |	\
						 RANDOMSHIFT | SURFACEPATTERN |				\
						 AMBIENTPATTERN | SPECULARPATTERN |			\
						 DIFFUSEPATTERN | BUMPMAPPATTERN |			\
						 TRANSPARPATTERN | FILLRECTNATUR | FITPICTNATUR | USETEXALFA)

/*================================	   TYPES	============================*/

/* LGHT in LGHT.hpp */

/* RTXT in RTXT.hpp */

/* MATER, IMAGE_ATTRIBUTES, IMATTRSIZE in GDLAttributes.h and material.hpp */

/* UMAT in UMAT.hpp */

/* FMAT in FMAT.hpp */



struct UCOL {
	GS_RGBColor	urgb;
	short		upri;
};			/* 8 */

/*================================	  MACROS	============================*/


#endif
