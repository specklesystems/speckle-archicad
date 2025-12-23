
// *****************************************************************************
//
//                                Class ConvertDimensions
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined VBUTILCONVERTDIMENSIONS_HPP
#define VBUTILCONVERTDIMENSIONS_HPP

// --------------------------------- Includes ----------------------------------

#include "Array.hpp"
#include "TEBase.hpp"

namespace VBUtil { class Font; }

// ============================== Class ConvertDimensions ==============================

namespace VBUtil {


class TE_DLL_EXPORT ConvertDimensions {

private:
	GS::Array <double>	mstDrawingScale;
	GS::Array <double>	mstWindowScale;
	GS::Array <double>	mstCustomFactor;

	double	mDrawingScale;
	double	mWindowScale;
	double	mCustomFactor;


	ConvertDimensions (const ConvertDimensions& source);			// forbidden
	ConvertDimensions& operator= (const ConvertDimensions& source);	// forbidden

public:
	ConvertDimensions (void);

	static	ConvertDimensions*	GetThreadLocalConvertDimensionsPtr (void);
	static	void				SetThreadLocalConvertDimensionsPtr (ConvertDimensions* cdPtr);

	inline void		SetActDrawingScale (double	actDrawingScale);
	inline void		SetActWindowScale (double	actWindowScale);
	inline void		SetCustomFactor (double	custFactor);

	inline void		StoreScales (void);
	inline void		RestoreScales (void);

	inline double	ModelUnit2Pixel (double dimensionInModelUnit, bool textIsFixed) const;
	inline double	CModelUnit2Pixel (double dimensionInModelUnit, bool textIsFixed) const;

	inline double	Pixel2ModelUnit (double pixelDimension, bool textIsFixed) const;
	inline double	CPixel2ModelUnit (double pixelDimension, bool textIsFixed) const;

	double	ModelUnit2TypoSize (const VBUtil::Font* font, bool textIsFixed) const;
	inline double	CModelUnit2TypoSize (const VBUtil::Font* font, bool textIsFixed) const;

	double	TypoSize2ModelUnit (const VBUtil::Font* font, double typoSize, bool textIsFixed) const;
	inline double	CTypoSize2ModelUnit (const VBUtil::Font* font, double typoSize, bool textIsFixed) const;

	inline double	GetActDrawingScale () const;
	inline double	GetActWindowScale () const;
	inline USize	GetStoreLevel () const;
};


class TE_DLL_EXPORT ConvertDimensionsGuard {
	ConvertDimensions		convertDimensions;
public:
	ConvertDimensionsGuard (void)
	{
		ConvertDimensions::SetThreadLocalConvertDimensionsPtr (&convertDimensions);
	}

	~ConvertDimensionsGuard (void)
	{
		ConvertDimensions::SetThreadLocalConvertDimensionsPtr (nullptr);
	}
};


inline void		ConvertDimensions::SetActDrawingScale (double	actDrawingScale)
{
	mDrawingScale = actDrawingScale;
}

inline void		ConvertDimensions::SetActWindowScale (double	actWindowScale)
{
	mWindowScale = actWindowScale;
}

inline void		ConvertDimensions::SetCustomFactor (double	custFactor)
{
	mCustomFactor = custFactor;
}

inline double	ConvertDimensions::ModelUnit2Pixel (double dimensionInModelUnit, bool textIsFixed) const
{
	double	c = textIsFixed ? mDrawingScale : 1.0;
	return (dimensionInModelUnit * c / mWindowScale);
}

inline double	ConvertDimensions::CModelUnit2Pixel (double dimensionInModelUnit, bool textIsFixed) const
{
	return (ModelUnit2Pixel (dimensionInModelUnit, textIsFixed) * mCustomFactor);
}

inline double	ConvertDimensions::Pixel2ModelUnit (double pixelDimension, bool textIsFixed) const
{
	double	c = textIsFixed ? mDrawingScale : 1.0;
	return (pixelDimension / c * mWindowScale);
}

inline double	ConvertDimensions::CPixel2ModelUnit (double pixelDimension, bool textIsFixed) const
{
	return (Pixel2ModelUnit (pixelDimension, textIsFixed) / mCustomFactor);
}

inline double	ConvertDimensions::CModelUnit2TypoSize (const VBUtil::Font* font, bool textIsFixed) const
{
	return (ModelUnit2TypoSize (font, textIsFixed) * mCustomFactor);
}

inline double	ConvertDimensions::CTypoSize2ModelUnit (const VBUtil::Font* font, double typoSize, bool textIsFixed) const
{
	return (TypoSize2ModelUnit (font, typoSize, textIsFixed) / mCustomFactor);
}

inline void		ConvertDimensions::StoreScales (void)
{
	mstDrawingScale.Push (mDrawingScale);
	mstWindowScale.Push (mWindowScale);
	mstCustomFactor.Push (mCustomFactor);

}

inline void		ConvertDimensions::RestoreScales (void)
{
	mDrawingScale = mstDrawingScale.Pop ();
	mWindowScale  = mstWindowScale.Pop ();
	mCustomFactor = mstCustomFactor.Pop ();
}


inline double	ConvertDimensions::GetActDrawingScale () const
{
	return mDrawingScale;
}


inline double	ConvertDimensions::GetActWindowScale () const
{
	return mWindowScale;
}


inline USize	ConvertDimensions::GetStoreLevel () const
{
	return mstDrawingScale.GetSize ();
}


}	// namespace VBUtil
// ______________________________ Class ConvertDimensions ______________________________

#endif
