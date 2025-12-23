/*==========================================================================**
**								GSUtilsDefs.h								**
**																			**
**							COMMON CONSTANTS AND TYPES						**
**==========================================================================*/

#ifndef	_GSUtilsDefs_H_
#define	_GSUtilsDefs_H_

#pragma once

// from GSRoot
#include "Definitions.hpp"

/*================================	 CONSTANTS	============================*/

/* ---------------------------- Common status bit -------------------------	*/
/*	For general purposes													*/
#define		NORMAL			0x0000					//	0b0000000000000000

#define		COLMAX		65535.0
#define		COLMAXF		65535.0f
#define		COLMAXI		65535

/* --------------------------- Image Record Constants --------------------- */

#define		MAC_PICT_IMG		1
#define		MAC_PIXM_IMG		2
#define		WIN_PIXM_IMG		3
#define		IND_PIXM_IMG		4
#define		GSPIXMAP_IMG		5
#define		COMPRESS_IMG		6

#define		IMG_VERSION			1

/* ------------------------------------------------------------------------ */
#define		BIGREAL		1.0E35


enum {
		OK			= 0,					// Everything's allright, == NoError (it must be 0!)
		CANCEL		= -2222
};

#define		ENDOFFILE	-1010				// End of file, != OK, != ERROR	

#define		MAXPEN			255				// Maximal number of pens in ARCHICAD
#define		MINPEN			-1
#define		INITPEN			1006

/* ------------------------------------------------------------------------ */
#define		Pen_Invalid				-2		// Invalid pen (Fill background color only)
#define		Pen_Opaque				-1		// Opaque pen (Fill background color only)
#define		Pen_Transparent			0		// Transparent pen (Fill background color only)
#define		Pen_First				1		// First available pen 
#define		Pen_Last				MAXPEN	// Last available pen
#define		Pen_GridLine			1000	// Grid Color Pen @ ChangeColor ()
#define		Pen_Room				1001	// Room Cat Color @ ChangeColor
#define		Pen_Ghost				1002	// Ghost Story Color @ ChangeColor ()
#define		Pen_GhostHi				1003	// Ghost Story High Color @ ChangeColor ()
#define		Pen_GhostBkgHi			1016	// Ghost Background fill
#define		Pen_Black				1004	// Black @ ChangeColor ()
#define		Pen_White				1005	// White @ ChangeColor ()
#define		Pen_InitLast			INITPEN	// Initialize Last Pen @ G3Color ()
#define		Pen_PictObj				1007	// Only a control for ActivePen ()
#define		Pen_RGB					1008	// use RGB in ChangeColor proc (set by ChangeColorRGB)
#define		Pen_Blue				1009	// Blue @ ChangeColor () (PlotMaker only)
#define		Pen_Red					1010	// Red @ ChangeColor () (PlotMaker only)
#define		Pen_Template			1011	// Template color @ ChangeColor () (PlotMaker only)
#define		Pen_Background			1012	// Layout Window Background color @ ChangeColor () (PlotMaker only)
#define		Pen_NonPrintableArea	1013	// Layout NonPrintable Area color @ ChangeColor () (PlotMaker only)
#define		Pen_DrawingFrame		1014	// Drawind Frame color
#define		Pen_DrawingClipFrame	1015	// Clipping Drawing Frame color
#define		Pen_NumberingGridText	1016	// Pen for drawing grid numbering text
#define		Pen_Custom				1017
#define		Pen_NoOutline			1018

#define		Skin_Invalid					-1		// Invalid skin
#define		Priority_Invalid				4150	// Invalid priority (lower than minimum, same as UndefPriorityMin in W2BUti.h)

/* ----------------- COMMON ERROR AND WARNING MESSAGES -------------------- */

#define		ERMISBINSECT	-6000	// Missing binary section

/*==================================   TYPES	============================*/

typedef		unsigned short	STATW;
typedef		UInt32	STATL;

#define		HAS_ONLY_FLAGS(status, flags)			(((status) & (~(flags))) == 0)
#define		HAS_ALL_FLAGS(status, flags)			(((status) & (flags)) == (flags))
#define		HAS_ANY_FLAGS(status, flags)			(((status) & (flags)) != 0)
#define		SET_FLAGS(status, flags)				((status) |= (flags))
#define		CLR_FLAGS(status, flags)				((status) &= (~(flags)))
#define		SET_OR_CLR_FLAGS(status, flags, set)	((set) ? SET_FLAGS(status, flags) : CLR_FLAGS(status, flags))

typedef struct RGBfloat {
	float	f_red, f_green, f_blue;
} RGBfloat;

typedef struct IMAGEREC {
	Int32		imgtype;
	Int32		version;
	Int32		destimg;
	Int32		lenimg;
	GSHandle	aimage;
	char		mimeType[256];
} IMAGEREC;

typedef GSIndex GSAttributeIndex;		// used for GSModeler attributes


#endif
