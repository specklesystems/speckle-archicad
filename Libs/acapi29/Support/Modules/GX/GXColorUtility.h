// *****************************************************************************
// File:			GXColorUtility.hpp
//
// Description:
//
// Project:			ARCHICAD
//
// Namespace:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef GXCOLORUTILITY_HPP
#define GXCOLORUTILITY_HPP


#if defined (macintosh)


inline UInt32 GXGetRedOf (UInt32 pixelValue)
{
	return (pixelValue & 0x0000FF00) >> 8;
}

inline UInt32 GXGetGreenOf (UInt32 pixelValue)
{
	return (pixelValue & 0x00FF0000) >> 16;
}

inline UInt32 GXGetBlueOf (UInt32 pixelValue)
{
	return (pixelValue & 0xFF000000) >> 24;
}

inline UInt32 GXMakeColorWith (UInt32 redX255, UInt32 greenX255, UInt32 blueX255)
{
	return	((GS::Min<UInt32> (blueX255,	0x0000FFFFul)	<< 16)	& 0xFF000000ul) |
			((GS::Min<UInt32> (greenX255,	0x0000FFFFul)	<< 8)	& 0x00FF0000ul) |
			((GS::Min<UInt32> (redX255,		0x0000FFFFul)	<< 0)	& 0x0000FF00ul);
}

inline bool GXIsSameColor (UInt32 color1, UInt32 color2)
{
	return	(color1 & 0xFFFFFF00) == (color2 & 0xFFFFFF00);
}

#else

inline UInt32 GXGetRedOf (UInt32 pixelValue)
{
	return (pixelValue & 0x00FF0000) >> 16;
}

inline UInt32 GXGetGreenOf (UInt32 pixelValue)
{
	return (pixelValue & 0x0000FF00) >> 8;
}

inline UInt32 GXGetBlueOf (UInt32 pixelValue)
{
	return pixelValue & 0x000000FF;
}

inline UInt32 GXMakeColorWith (UInt32 redX255, UInt32 greenX255, UInt32 blueX255)
{
	return	((GS::Min<UInt32> (blueX255,	0x0000FFFFul)	>> 8)	& 0x000000FFul) |
			((GS::Min<UInt32> (greenX255,	0x0000FFFFul)	>> 0)	& 0x0000FF00ul) |
			((GS::Min<UInt32> (redX255,		0x0000FFFFul)	<< 8)	& 0x00FF0000ul);
}

inline bool GXIsSameColor (UInt32 color1, UInt32 color2)
{
	return	(color1 & 0x00FFFFFF) == (color2 & 0x00FFFFFF);
}

#endif

inline UInt32 GXMakeColorWithBackground (	UInt32 redX255, UInt32 greenX255, UInt32 blueX255,
											UInt32 bgRed, UInt32 bgGreen, UInt32 bgBlue)
{
	if (redX255 < (bgRed << 8)) {
		// (3 * bgRed + red) / 4...
		return GXMakeColorWith (((((bgRed	<< 8)	<< 2) - (bgRed		<< 8))	+ redX255)		>> 2,
								((((bgGreen	<< 8)	<< 2) - (bgGreen	<< 8))	+ greenX255)	>> 2,
								((((bgBlue	<< 8)	<< 2) - (bgBlue		<< 8))	+ blueX255)		>> 2);
	} else {
		// (31 * red + bgRed) / 32
		return GXMakeColorWith ((((redX255		<< 6) - redX255)	+ (bgRed	<< 8))	>> 6,
								(((greenX255	<< 6) - greenX255)	+ (bgGreen	<< 8))	>> 6,
								(((blueX255		<< 6) - blueX255)	+ (bgBlue	<< 8))	>> 6);
	}
}

#endif
