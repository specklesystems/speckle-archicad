// Contact person : NN

#ifndef DASHEDLINEDRAWER_HPP
#define DASHEDLINEDRAWER_HPP

#pragma once

#include "Polyline2DClassDefinition.hpp"

// from Pattern
#include "PatternExport.h"
#include "LineTypeDefinitions.hpp"


namespace GX {
namespace Pattern {

class IDashedLinePattern;
class LinePatternPrimitivesDrawer;

class PATTERN_DLL_EXPORT DashedLineDrawer
{
public:
	static void DrawLine		(const Coord&					begC,
								 const Coord&					endC,
								 double							scale,
								 double							tolerance,
								 const Box2DData*				drawBox,
								 const IDashedLinePattern&		pattern,
								 LinePatternPrimitivesDrawer*	drawLine);
	
	static void DrawPolyLine	(const Geometry::Polyline2D&	polyline,
								 double							scale,
								 double							tolerance,
								 const Box2DData*				drawBox,
								 PolyLinePerSegmentDrawMode		perSegmentDrawMode,
								 const IDashedLinePattern&		pattern,
								 LinePatternPrimitivesDrawer*	drawLine);

	static void DrawArc			(const Coord&					origo,
								 const Coord&					begC,
								 double							angle,
								 double							scale,
								 double							tolerance,
								 const Box2DData*				drawBox,
								 const IDashedLinePattern&		pattern,
								 LinePatternPrimitivesDrawer*	drawLine);

	static void DrawLineSample	(const Coord&					begC,
								 const Coord&					endC,
								 double							scale,
								 double							tolerance,
								 const Box2DData*				drawBox,
								 const IDashedLinePattern&		pattern,
								 LinePatternPrimitivesDrawer*	drawLine);
};

}
}

#endif
