// Contact person: KiP

#ifndef FILL_PATTERN_DRAWING_PROCESSES_HPP
#define FILL_PATTERN_DRAWING_PROCESSES_HPP

#pragma once

// from Geometry
#include "IrregularPolygon2DClassDefinition.hpp"

// from Pattern
#include "PatternExport.h"


namespace GX
{
namespace Pattern
{

class PATTERN_DLL_EXPORT FillPatternPrimitivesDrawer
{
public:
	virtual ~FillPatternPrimitivesDrawer ();

	virtual bool		CanDrawLine () const = 0;
	virtual GSErrCode	DrawLine (const Coord& begC, const Coord& endC) = 0;

	virtual bool		CanDrawArc () const = 0;
	virtual GSErrCode	DrawArc (const GenArc& genArc) = 0;

	virtual bool		CanDrawPolygon () const = 0;
	virtual GSErrCode	DrawPolygon /*Fill+Frame*/ (const Geometry::IrregularPolygon2D& polygon, double percent) = 0;

	virtual bool		CanDrawImage () const = 0;
	virtual GSErrCode	DrawImage (const Coord& topLeft, const Coord& topRight, const Coord& bottomLeft, const Coord& bottomRight) = 0;

	virtual bool		ShouldContinue ();		// TODO szukseg van erre ?
	virtual bool		CanClip () const = 0;	// TODO szukseg van erre ?

	virtual GSErrCode	DrawPolygon2DData (const Geometry::Polygon2DData& polygon, double percent);	//TODO ezt meg kell szuntetni
};

}
}

#endif
