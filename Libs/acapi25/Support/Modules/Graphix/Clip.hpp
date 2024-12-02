// *****************************************************************************
// File:			Clip.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef CLIP_HPP
#define CLIP_HPP

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"					// GRAPHIX_DLL_EXPORT
#include "Array.hpp"
#include "Rect.hpp"

// --- Class declarations ------------------------------------------------------

class GRAPHIX_DLL_EXPORT Clip
{
private:
	GS::ArrayFB<UInt32, 4>			polyPointsCount;
	GS::ArrayFB<GS::Point<float>, 4 >	points;
	GS::Rect<float>					clipBoundRect;
	bool							null;				// No clip is defined
	bool							isRect;

public:
	Clip ();
	void			Begin ();
	void			MoveTo (float x, float y);
	void			LineTo (float x, float y);
	void			End ();
	void			SetToRect (const GS::Rect<float>& rect);

	bool			IsRect () const;
	bool			IsEmpty () const;
	bool			IsNull () const;

	GS::Rect<float>	GetBoundRect () const;
	void			GetClipPolyData (GS::Array<GS::Point<float> >& points, GS::Array<UInt32>& polyPointsCount) const;
};

#endif
