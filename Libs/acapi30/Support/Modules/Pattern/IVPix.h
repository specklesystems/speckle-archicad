/****************************************************************************/
/*																			*/
/*						Type swapping function prototypes 					*/
/*																			*/
/****************************************************************************/

#ifndef	IVPIX_H
#define	IVPIX_H

#pragma once

#include "GSPix.h"
#include "PatternExport.h"


PATTERN_DLL_EXPORT
void	IVGS_RGBColor (GS::PlatformSign inplatform, GS_RGBColor *rgb);


PATTERN_DLL_EXPORT
void	IVGS_RGBColor (GS::PlatformSign inplatform, GS::PlatformSign toplatform, GS_RGBColor *rgb);


#endif
