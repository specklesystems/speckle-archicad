// *****************************************************************************
//
//                                Class Bitmap
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGBITMAP_HPP
#define QGBITMAP_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "GSRoot.hpp"
#include "QGBase.hpp"

// ============================== Class Bitmap =================================

namespace QG {

class QG_DLL_EXPORT Bitmap {

private:
	Bitmap (const Bitmap&);
	Bitmap& operator=(const Bitmap&);

public:
	enum BitmapType	{ btUnknown = -1, btARGB8888 = 0, bt_RGB8888 = 1, btARGBPreMult8888 = 2, bt_RGB555 = 3 };
	enum BitmapEndian { beDefault = -1, beLittle = 0, beBig = 1 };

protected:
	USize			bmWidth;
	USize			bmHeight;
	USize			bmRowBytes;
	BitmapType		bmType;

	UChar*			bmData;
	BitmapEndian	bmEndian;
	bool			detachedData;


public:
	Bitmap (USize inbmWidth, USize inbmHeight, BitmapType inbmType = btARGB8888);
	Bitmap (USize inbmWidth, USize inbmHeight, BitmapType inbmType, UChar* inbmData, USize inbmRowBytes, BitmapEndian inbmEndian = beDefault);
	~Bitmap ();

	inline USize GetWidth (void) const
	{
		return bmWidth;
	};
	inline USize GetHeight (void) const
	{
		return bmHeight;
	};
	inline BitmapType GetType (void) const
	{
		return bmType;
	};
	inline USize GetRowBytes (void) const
	{
		return bmRowBytes;
	};
	inline UChar* GetDataRef (void) const	// dataref always contains beDefault endian data
	{
		return bmData;
	};
	inline BitmapEndian GetEndian (void) const
	{
		return bmEndian;
	};
	inline void DetachData (void)
	{
		detachedData = true;
	};
	void SwapBytes (void);

};

}	// namespace QG
// ______________________________ Class Bitmap _________________________________

#endif	// QGBITMAP_HPP
