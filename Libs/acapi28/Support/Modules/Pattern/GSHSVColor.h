/*==========================================================================**
**									GSUtils.h								**
**																			**
**					CONSTANTS, TYPES AND PROTOTYPES FOR GSUtils				**
**==========================================================================*/

/*
	Copyright (c) 1995-2024 by Graphisoft SUA_ChgCopyrightYear_PrevToNextYear_DONOTDELETETHISCOMMENT
	All rights reserved.
	Any part of the GDL import library kit (including this file) may be used
	for any purpose only under a separate written permission.

	GRAPHISOFT SE
	H-1031 Budapest, Zahony u. 7.
	Phone: 36.1/437-3000
	E-mail: archicadapi@graphisoft.com
*/

#ifndef	GSHSVColor_H
#define	GSHSVColor_H

#pragma once

#include	"PatternExport.h"
#include	"GSPix.h"

/*---------------------------------------------------------------------------*/

struct GS_HSVColor {
	unsigned short			hue;						/*Fraction of circle, red at 0*/
	unsigned short			saturation;					/*0-1, 0 for gray, 1 for pure color*/
	unsigned short			value;						/*0-1, 0 for black, 1 for max intensity*/
};

PATTERN_DLL_EXPORT
void	ConvRGB2HSV(const GS_RGBColor& rgbColor, GS_HSVColor& hsvColor);

PATTERN_DLL_EXPORT
void	ConvHSV2RGB(const GS_HSVColor& hsvColor, GS_RGBColor& rgbColor);

namespace Experimental {	// this new algorithm is obtained from the internet, because the old algorithm doesn't work properly in some situations (roundtrip conversion yields different result from the input) 
							// the implementation difference between two algorithms is hard to spot (so it cannot be easily corrected) and immediate replacement of the old algorithm could lead to errors,
							// so we put the new algorithm to the experimental namespace for a while => in the future the old algorithm should be deleted
PATTERN_DLL_EXPORT
void	ConvHSV2RGB (const GS_HSVColor& hsvColor, GS_RGBColor& rgbColor);

}

PATTERN_DLL_EXPORT
Gfx::Color	DesaturateColor (const Gfx::Color& color, double saturationModifier);


#endif //GSHSVColor_H
