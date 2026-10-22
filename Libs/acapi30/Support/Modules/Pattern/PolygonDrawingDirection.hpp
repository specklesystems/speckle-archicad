/****************************************************************
 *  Description:	PolygonDrawingDirection	interface			*
 *																*
 *	Module:			Pattern										*
 *	Namespace:													*
 *  Contact person:	KiP											*
 ****************************************************************/

#ifndef POLYGONDRAWINGDIRECTION_HPP
#define POLYGONDRAWINGDIRECTION_HPP

#pragma once

// Pattern
#include "PatternExport.h"

// Geometry
#include "Polygon2DClassDefinition.hpp"
#include "IrregularPolygon2DClassDefinition.hpp"


class PATTERN_DLL_EXPORT IPolygonDrawingDirection
{
public:
	virtual ~IPolygonDrawingDirection ();

	virtual bool IsDefaultDrawingDirection (const Geometry::Polygon2D& polygon, const Geometry::Polygon2D::ConstContourIterator& contourIter) const = 0;
	virtual bool IsDefaultDrawingDirection (const Geometry::IrregularPolygon2D& polygon, const Geometry::IrregularPolygon2D::ConstContourIterator& contourIter) const = 0;
};

#endif
