#if !defined (GXIMAGESAVEOPTIONS_HPP)
#define GXIMAGESAVEOPTIONS_HPP

#pragma once

#include	"GXImageBaseExport.hpp"

// =============================================================================
//
// Image Save Options
//
// =============================================================================

namespace GX {

enum {
	PixelBits_BestDepth = 0,
	PixelBits_BlackAndWhite = 1,
	PixelBits_256Gray = 8,
	PixelBits_Millions = 24,		// default
	PixelBits_MillionsWithAlpha = 32,
	PixelBits_Float = 128
};

class GXIMAGEBASE_DLL_EXPORT ImageSaveOptions
{
private:
	Int32	pixelBits;		// 1=B&W, 8=256Gray, 24, 32=24+alpha. any other = default (24)
	Int32	intQuality;		// = quality [0.0, 1.0] * 10000 - used for jpeg only at the moment; default = 9000 (90%)

public:
	ImageSaveOptions ();

	ImageSaveOptions (Int32	inPixelBits);

	Int32	PixelBits (void) const {	return pixelBits; }
	void	SetPixelBits (Int32 inPixelBits);
	Int32	Quality (void) const {	return intQuality; }
	void	SetQuality (Int32 inQuality);

	static	ImageSaveOptions	GetLast ();
	static	void				SetLast (const ImageSaveOptions& last);
};


class GXIMAGEBASE_DLL_EXPORT ImageSaveOptionsMask
{
public:
	bool	pixelBits;		// true if changed in dialog
	bool	quality;		// true if changed in dialog

	ImageSaveOptionsMask () { pixelBits = false; quality = false; }
};


}	// namespace GX
#endif
