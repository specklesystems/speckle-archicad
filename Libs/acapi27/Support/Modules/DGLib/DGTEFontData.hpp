// *****************************************************************************
// File:			DGTEFontData.hpp
//
// Description:		font data structure for rich text editing
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	FG
//
// SG compatible
// *****************************************************************************

#ifndef DGTEFONTDATA_HPP
#define DGTEFONTDATA_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Font.hpp"


// --- Class declarations ------------------------------------------------------


class DGTEFontData {
public:
	float			angle;					// Angle of base line from X-axis in radian
	TE::Font		font;
	bool			strikeOut;				// Strikeout flag (0 / 1)         (WIN only)
	UChar			charSet;				// Character set of the font      (WIN only)

	DGTEFontData ():
		angle (0.0),
		font (),
		strikeOut (false),
		charSet (0)
	{ };

	DGTEFontData (const DGTEFontData& source):
		angle (source.angle),
		font (source.font),
		strikeOut (source.strikeOut),
		charSet (source.charSet)
	{ };

	DGTEFontData& operator= (const DGTEFontData& source)
	{
		angle = source.angle;
		font = source.font;
		strikeOut = source.strikeOut;
		charSet = source.charSet;
		return *this;
	}
	
	GSErrCode	Store (GS::ObjectState& os) const
	{
		os.Add ("angle", angle);
		os.Add ("font", font);
		os.Add ("strikeOut", strikeOut);
		os.Add ("charSet", charSet);

		return NoError;
	}
};

#endif
