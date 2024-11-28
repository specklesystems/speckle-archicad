// Contact person : KiP

#ifndef VECTORFILLDRAWERUTILS_HPP
#define VECTORFILLDRAWERUTILS_HPP

#pragma once

// Pattern
#include "PatternExport.h"

// from Geometry
#include "IrregularPolygon2DClassDefinition.hpp"


namespace GX
{
namespace Pattern
{

class PATTERN_DLL_EXPORT PgonRep
{
public:
	class PATTERN_DLL_EXPORT Vertex
	{
	public:
		Vertex () {}
		~Vertex () {}

		const Coord&	GetCoord () const { return coord; }
		const Vertex*	GetNextVertex () const { return nextVertex; }
		const Vertex*	GetPrevVertex () const { return prevVertex; }

		void SetCoord (const Coord& coord) { this->coord = coord; }
		void SetNextVertex (const Vertex* nextVertex) { this->nextVertex = nextVertex; }
		void SetPrevVertex (const Vertex* prevVertex) { this->prevVertex = prevVertex; }

	private:
		Coord coord;
		const Vertex* nextVertex;
		const Vertex* prevVertex;
	};

	PgonRep (const Geometry::IrregularPolygon2D& polygon);
	~PgonRep ();
	
	UInt32			GetCountourNum () const { return contourNum; }
	const Vertex*	GetContourBegin (UIndex contourIdx) const { return contourBegins[contourIdx]; }
	bool			IsContourBegin (const Vertex* vertex, UIndex contourIdx) const { return vertex == contourBegins[contourIdx]; }

	UInt32			GetVertexNum () const { return vertexNum; }
	const Vertex&	GetVertex (UIndex vertexIdx) const { return vertices[vertexIdx]; }
	Vertex&			GetVertex (UIndex vertexIdx) { return vertices[vertexIdx]; }

private:
	UInt32 contourNum;
	Vertex** contourBegins;
	UInt32 vertexNum;
	Vertex* vertices;

	inline void AllocateMemory ();
	inline void FreeMemory ();
	inline void SetVertices (const Geometry::IrregularPolygon2D& polygon);
	inline void SetVertex (const Coord& coord, UIndex actPgonRepIdx, UIndex nextPgonRepIdx);
};


struct PATTERN_DLL_EXPORT HorizontalSector
{
	double begX;
	double endX;
};


class PATTERN_DLL_EXPORT PgonHorizontalLineIntersectionCalculator
{
public:
	PgonHorizontalLineIntersectionCalculator (const PgonRep& pgon, double horizontalLineY = 0.0);
	~PgonHorizontalLineIntersectionCalculator ();

	const GS::Array<HorizontalSector>& GetInsidePolygonParts () const;

	void SetHorizontalLineY (double horizontalLineY);

private:
	class Impl;
	Impl& impl;
};

}
}

#endif