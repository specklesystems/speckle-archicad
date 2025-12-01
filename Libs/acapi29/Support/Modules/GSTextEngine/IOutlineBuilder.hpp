// *****************************************************************************
//
//                                Class IOutlineBuilder
//
// Module:			TextEngine
// Namespace:		TE
// Platform:		common
// Contact person:	KM FG
//
// SG compatible
//
// *****************************************************************************

// --------------------------------- Defines -----------------------------------

#if !defined IOUTLINEBUILDER_HPP
#define IOUTLINEBUILDER_HPP

// --------------------------------- Includes ----------------------------------

#include "ICharStyle.hpp"

// =========================== Class IOutlineBuilder ===========================

namespace TE {

class TE_DLL_EXPORT IOutlineBuilder
{

public:
	virtual		~IOutlineBuilder ();

	// types
	struct	PixCoord {
		double x;
		double y;

		PixCoord (void) : x (0.0), y (0.0) {};
		PixCoord (const PixCoord& rc) : x (rc.x), y (rc.y) {};
		PixCoord (double xD, double yD) { Set (xD, yD);	};
		void Set (double xD, double yD) { x = xD; y = yD;};

		PixCoord& operator = (const PixCoord& coord) { x = coord.x; y = coord.y; return *this; };
		PixCoord& operator += (const PixCoord& coord) {	x += coord.x; y += coord.y;	return *this;};
		PixCoord& operator -= (const PixCoord& coord) {	x -= coord.x; y -= coord.y;	return *this;};
		PixCoord& operator *= (double mul) { x *= mul; y *= mul; return *this; };
		PixCoord& operator /= (double div) { x /= div; y /= div; return *this; };
		PixCoord  operator + (const PixCoord& coord) const { return PixCoord (x + coord.x, y + coord.y);};
		PixCoord  operator - (const PixCoord& coord) const { return PixCoord (x - coord.x, y - coord.y);};
		PixCoord  operator * (double mul) const { return PixCoord (x * mul, y * mul); };
		PixCoord  operator / (double div) const { return PixCoord (x / div, y / div); };
	};

	// methods
	virtual Int32	BeginTextOutline () = 0;
	virtual Int32	BeginGlyph (const ICharStyle* iCharStyle) = 0;
	virtual Int32	AddContour (const PixCoord* points, Int32 numOfPoints) = 0;
	virtual Int32	EndPoly () = 0;
	virtual Int32	EndGlyph () = 0;
	virtual Int32	Underline (const ICharStyle* /* iCharStyle */, const PixCoord* /* points */, Int32 /* numOfPoints = 5 */) {return 0;}
	virtual Int32	StrikeOut (const ICharStyle* /* iCharStyle */, const PixCoord* /* points */, Int32 /* numOfPoints = 5 */) {return 0;}
	virtual Int32	EndTextOutline () = 0;

	virtual double	GetPlotScale () = 0;

};	// class IOutlineBuilder

}	// namespace TE

#endif	// #if !defined IOUTLINEBUILDER_HPP
