// *****************************************************************************
//
// Utility function(s) for Polygon2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	MA
//
// *****************************************************************************

#ifndef GEOMETRY_POLYGON2DUTILS_HPP
#define GEOMETRY_POLYGON2DUTILS_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Point2D.hpp"
#include "GenArc2DData.h"
#include "Sector2DData.h"
#include "Point2DData.h"
#include "Poly2DTypes.hpp"


struct Circle;

namespace Geometry {

class GEOMETRY_DLL_EXPORT Polygon2DCanonization {
	struct MyPair;
public:
	static void CanonizePolyByRotationAndSwap (const GS::Array<Coord>& irrVertices, const GS::Array<UIndex>& irrContourEnds, Geometry::Polygon2D& poly);
};

GEOMETRY_DLL_EXPORT
GenArc	ProjectPolygon2DToCircle (const Polygon2D& polygon, const Geometry::Circle2D& projectionCircle);


template<typename PolyType>
void	GetExtremePointsOfPolys (const GS::Array<PolyType> polys, const Vector2D& direction, GS::Array<Point2D>& minima, GS::Array<Point2D>& maxima)
{
	typedef typename PolyType::ConstVertexIterator ConstVertexIterator;
	typedef typename PolyType::ConstEdgeIterator ConstEdgeIterator;

	GS::Array<Point2D> possibleExtremePoints;

	GenArc arc;
	Sector dummySector;
	for (const PolyType& poly : polys) {
		for (ConstVertexIterator vertexIt = poly.BeginVertex (); vertexIt != poly.EndVertex (); ++vertexIt) {
			possibleExtremePoints.Push (vertexIt->GetCoord ());
		}
		for (ConstEdgeIterator edgeIt = poly.BeginEdge (); edgeIt != poly.EndEdge (); ++edgeIt) {
			if (!edgeIt->IsStraight ()) {
				edgeIt->GetSector (dummySector, arc);
				GS::Array<Point2D> arcExtremePointsInDirection;
				GetTangentPointsByDirection (arc, direction, arcExtremePointsInDirection);
				possibleExtremePoints.Append (arcExtremePointsInDirection);
			}
		}
	}
	
	GetExtremePointsOfPointSetByDir (possibleExtremePoints, direction, minima, maxima);
}

template<typename PolyType>
void ResetPolyVertexIds (PolyType& poly, const typename PolyType::VertexUserDataType& newUserData)
{
	for (typename PolyType::ConstVertexIterator vertexIt = poly.BeginVertex (); vertexIt != poly.EndVertex (); ++vertexIt) {
		poly.SetVertexUserData (vertexIt, newUserData);
	}
}

template<typename PolyType>
void ResetMultiPolyVertexIds (GS::Array<PolyType>& polies, const typename PolyType::VertexUserDataType& newUserData)
{
	for (PolyType& poly : polies) {
		ResetPolyVertexIds (poly, newUserData);
	}
}

template<typename PolyType>
void ResetPolyEdgeIds (PolyType& poly, const typename PolyType::EdgeUserDataType& newUserData)
{
	for (typename PolyType::ConstEdgeIterator edgeIt = poly.BeginEdge (); edgeIt != poly.EndEdge (); ++edgeIt) {
		poly.SetEdgeUserData (edgeIt, newUserData);
	}
}

template<typename PolyType>
void ResetMultiPolyEdgeIds (GS::Array<PolyType>& polies, const typename PolyType::EdgeUserDataType& newUserData)
{
	for (PolyType& poly : polies) {
		ResetPolyEdgeIds (poly, newUserData);
	}
}

} // namespace Geometry

#endif