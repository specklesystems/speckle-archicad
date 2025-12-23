// *********************************************************************************************************************
//
// PreDeclaration of Polygon2D, MultiPolygon2D, IrregularPolygon2D, MultiIrregularPolygon2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA
//
// *********************************************************************************************************************
#if !defined (POLY2DTYPES_HPP_)
#define POLY2DTYPES_HPP_

#pragma once

namespace Geometry {
	class PolyId;

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData> class CustomPolygon2D;
	typedef CustomPolygon2D<PolyId, PolyId, PolyId, PolyId> Polygon2D;

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData> class CustomMultiPolygon2D;
	typedef CustomMultiPolygon2D<PolyId, PolyId, PolyId, PolyId> MultiPolygon2D;

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData> class CustomIrregularPolygon2D;
	typedef CustomIrregularPolygon2D<PolyId, PolyId, PolyId, PolyId> IrregularPolygon2D;

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData> class CustomMultiIrregularPolygon2D;
	typedef CustomMultiIrregularPolygon2D<PolyId, PolyId, PolyId, PolyId> MultiIrregularPolygon2D;

	template <class VertexUserData, class EdgeUserData, class PolygonUserData> class CustomPolyline2D;
	typedef CustomPolyline2D <PolyId, PolyId, PolyId> Polyline2D;

	template <class VertexUserData, class EdgeUserData, class PolygonUserData> class CustomMultiPolyline2D;
	typedef CustomMultiPolyline2D <PolyId, PolyId, PolyId> MultiPolyline2D;
}

#endif		/* POLY2DTYPES_HPP_ */
