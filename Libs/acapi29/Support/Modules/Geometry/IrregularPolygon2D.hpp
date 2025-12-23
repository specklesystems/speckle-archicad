// *****************************************************************************
//
// Declaration of IrregularPolygon2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA, RJ
//
// *****************************************************************************

#ifndef GEOMETRY_IRREGULARPOLYGON2D_HPP_
#define GEOMETRY_IRREGULARPOLYGON2D_HPP_

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes ----------------------------------------------------------------
#include "IrregularPolygon2DClassDefinition.hpp"

#include "Polyline2DClassDefinition.hpp"

namespace Geometry {

#if defined (DEBUVERS)
#define DEBUVERS_POLY2D
#endif

#if defined(DEBUVERS_POLY2D)
#define DBCHECKIRREGULARINDEX(idx, minIdx, maxIdx) DBASSERT ((idx) >= (minIdx) && (idx) <= (maxIdx))
#else
#define DBCHECKIRREGULARINDEX(idx, minIdx, maxIdx)
#endif

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const ContourUserData& CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetPolyContourUserData () const
{
	return poly->GetContourUserDataByIdx (index);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetVertexNum () const
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	return to - from;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetVertexIterator (UIndex vertexIdx) const -> ConstVertexIterator
{
	if (poly == nullptr) {
		DBBREAK ();
		throw GeometryLogicErrorException ("Invalid polygon in CustomIrregularPolygon2D::Contour::GetVertexIterator!", __FILE__, __LINE__);
	}
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	DBCHECKIRREGULARINDEX(vertexIdx, poly->polygon->GetVertexBeginIdxInContour (index), poly->polygon->GetVertexEndIdxInContour (index));

	ConstPolyVertexInPolyState<CustomIrregularPolygon2D, VertexUserData> item (poly, from, to, vertexIdx);
	return CustomIrregularPolygon2D::ConstVertexIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EnumerateVertex () const -> ConstVertexIterator
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetVertexIterator (from);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::BeginVertex () const -> ConstVertexIterator
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetVertexIterator (from);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EndVertex () const -> ConstVertexIterator
{
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	return GetVertexIterator (to);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetEdgeNum () const
{
	UIndex from = poly->polygon->GetEdgeBeginIdxInContour (index);
	UIndex to = poly->polygon->GetEdgeEndIdxInContour (index);
	return to - from;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetEdgeIterator (UIndex edgeIdx) const -> ConstEdgeIterator
{
	if (poly == nullptr) {
		DBBREAK ();
		throw GeometryLogicErrorException ("Invalid polygon in CustomIrregularPolygon2D::Contour::GetEdgeIterator!!", __FILE__, __LINE__);
	}
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	DBCHECKIRREGULARINDEX(edgeIdx, poly->polygon->GetVertexBeginIdxInContour (index), poly->polygon->GetVertexEndIdxInContour (index));

	ConstPolyEdgeInPolyState<CustomIrregularPolygon2D, EdgeUserData> item (poly, from, to, edgeIdx);
	return ConstEdgeIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EnumerateEdge () const -> ConstEdgeIterator
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetEdgeIterator (from);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::BeginEdge () const -> ConstEdgeIterator
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetEdgeIterator (from);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EndEdge	() const -> ConstEdgeIterator
{
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	return GetEdgeIterator (to);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetBeginVertex (const ConstEdgeIterator& edgeIterator) const -> ConstVertexIterator
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == poly->polygon);
	return GetVertexIterator (poly->polygon->GetBeginVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetEndVertex (const ConstEdgeIterator& edgeIterator) const -> ConstVertexIterator
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == poly->polygon);
	return GetVertexIterator (poly->polygon->GetEndVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetNextEdge (const ConstVertexIterator& vertexIterator) const -> ConstEdgeIterator
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == poly->polygon);
	return GetEdgeIterator (poly->polygon->GetNextEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetPrevEdge (const ConstVertexIterator& vertexIterator) const -> ConstEdgeIterator
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == poly->polygon);
	return GetEdgeIterator (poly->polygon->GetPrevEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomIrregularPolygon2D (const GS::SharedPtr<CorePolygon2DType>& polygon2D) : polygon (polygon2D)
{
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::SharedPtr<CorePolygon2DType>& polygon) -> CustomIrregularPolygon2D
{
	if (polygon == nullptr) {
		DBBREAK ();
		return CustomIrregularPolygon2D ();
	}

	if (polygon->IsEmpty ()) {
		return CustomIrregularPolygon2D ();
	}

	return CustomIrregularPolygon2D (polygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray) -> MultiIrregularPolygon2DType
{
	if (polygonArray.GetSize () == 0) {
		return MultiIrregularPolygon2DType ();
	}

	MultiIrregularPolygon2DType result;
	for (UIndex idx = 0; idx < polygonArray.GetSize (); idx++) {
		if (polygonArray[idx]->IsEmpty ()) {
			DBBREAK ();
			continue;
		}
		CustomIrregularPolygon2D tmpPolygon (polygonArray[idx]);
		result.Push (tmpPolygon);
	}

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CreateResult (typename CorePolygon2DType::PolygonResult polyResult, 
																												const GS::SharedPtr<CorePolygon2DType>& newPolygon) const -> CustomIrregularPolygon2D
{
	CustomIrregularPolygon2D result;
	switch (polyResult) {
		case CorePolygon2DType::NewPolygons:
			result.polygon = newPolygon;
			break;
		case CorePolygon2DType::ResultSameAsThis:
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			result.polygon = new CorePolygon2DType (*polygon);
#else
			result.polygon = polygon;
#endif
			break;
		case CorePolygon2DType::EmptyPolygon:
			break;
		default:
			DBBREAK ();
			break;
	}

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CreateResult (typename CorePolygon2DType::PolygonResult polyResult, 
																												const CustomIrregularPolygon2D* firstParam, 
																												const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray) const -> MultiIrregularPolygon2DType
{
	MultiIrregularPolygon2DType result;
	switch (polyResult) {
	case CorePolygon2DType::NewPolygons:
		result = CustomIrregularPolygon2D::Create (polygonArray);
		break;
	case CorePolygon2DType::ResultSameAsThis:
		{
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (*polygon);
			result.Push (newPolygon);
#else
			result.Push (polygon);
#endif
		}
		break;
	case CorePolygon2DType::ResultSameAsFirstParameter:
		DBASSERT (firstParam != nullptr);
		if (firstParam != nullptr) {
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (*(firstParam->polygon));
			result.Push (newPolygon);
#else
			result.Push (firstParam->polygon);
#endif
		}
		break;
	case CorePolygon2DType::ResultThisAndParameter:
		{
			DBASSERT (firstParam != nullptr);
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			GS::SharedPtr<CorePolygon2DType> newPolygon1 = new CorePolygon2DType (*polygon);
			result.Push (newPolygon1);
			if (firstParam != nullptr) {
				GS::SharedPtr<CorePolygon2DType> newPolygon2 = new CorePolygon2DType (*(firstParam->polygon));
				result.Push (newPolygon2);
			}
#else
			result.Push (polygon);
			if (firstParam != nullptr) {
				result.Push (firstParam->polygon);
			}
#endif
		}
		break;
	case CorePolygon2DType::EmptyPolygon:
		break;
	default:
		DBBREAK ();
		break;
	}

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetResult (typename CorePolygon2DType::PolygonResult polyResult, const GS::SharedPtr<CorePolygon2DType>& newPoly)
{
	switch (polyResult) {
		case CorePolygon2DType::NewPolygons:
			polygon = newPoly;
			break;
		case CorePolygon2DType::ResultSameAsThis:
			{
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
				GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (*polygon);
				polygon = newPolygon;
#endif
			}
			break;
		case CorePolygon2DType::ResultSameAsFirstParameter:
			DBBREAK ();
			break;
		case CorePolygon2DType::ResultThisAndParameter:
			DBBREAK ();
			break;
		case CorePolygon2DType::EmptyPolygon:
			polygon = new CorePolygon2DType (*polygon, true);
			break;
		default:
			DBBREAK ();
			break;
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyOnWrite ()
{
	if (polygon == nullptr)
		throw GeometryIllegalArgumentException ("Polygon can't be nullptr!!!", __FILE__, __LINE__);
	if (polygon->GetRefCount() > 1)
		polygon = new CorePolygon2DType (*polygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetFlags (GS::UInt32 polyFlags /*PolyFlags*/) -> typename CorePolygon2DType::Flags
{
	typename CorePolygon2DType::Flags flags;

	CheckPolyFlags (polyFlags);
	DBASSERT (!((PolyFlags_Force64BitPrecision & polyFlags) && (PolyFlags_NoForce64BitPrecision & polyFlags)));

	if (PolyFlags_IsSameDirEdgeLegal & polyFlags)
		flags.isSameDirEdgeLegal = true;
	if (PolyFlags_NoSameDirEdgeLegal & polyFlags)
		flags.isSameDirEdgeLegal = false;

	if (PolyFlags_Force64BitPrecision & polyFlags)
		flags.force64BitPrecision = true;

	if (PolyFlags_NoForce64BitPrecision & polyFlags)
		flags.force64BitPrecision = false;

	if (PolyFlags_IsVertexUserData & polyFlags)
		flags.isVertexUserData = true;
	if (PolyFlags_NoVertexUserData & polyFlags)
		flags.isVertexUserData = false;
	if (PolyFlags_IsEdgeUserData & polyFlags)
		flags.isEdgeUserData = true;
	if (PolyFlags_NoEdgeUserData & polyFlags)
		flags.isEdgeUserData = false;
	if (PolyFlags_IsContourUserData & polyFlags)
		flags.isContourUserData = true;
	if (PolyFlags_NoContourUserData & polyFlags)
		flags.isContourUserData = false;
	if (PolyFlags_IsPolygonUserData & polyFlags)
		flags.isPolygonUserData = true;
	if (PolyFlags_NoPolygonUserData & polyFlags)
		flags.isPolygonUserData = false;

	return flags;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomIrregularPolygon2D ()
{
	typename CorePolygon2DType::Flags flags;
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
	polygon = new CorePolygon2DType (flags);
#else
	polygon = new CorePolygon2DType (flags);
#endif
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomIrregularPolygon2D (const CustomIrregularPolygon2D& source)
{
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
	polygon = new CorePolygon2DType (*source.polygon);
#else
	polygon = source.polygon;
#endif
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomIrregularPolygon2D (const Polygon2DType& poly)
{
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
	polygon = new CorePolygon2DType (*poly.polygon);
#else
	polygon = poly.polygon;
#endif
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomIrregularPolygon2D (const Box2DData& box)
{
	typename CorePolygon2DType::Flags flags;
	polygon = new CorePolygon2DType (flags, box);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomIrregularPolygon2D (const Circle2D& circ)
{
	typename CorePolygon2DType::Flags flags;
	polygon = new CorePolygon2DType (flags, circ);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomIrregularPolygon2D (const Ellipse& ell, ArcDivParams arcDivParams)
{
	typename CorePolygon2DType::Flags flags;
	polygon = new CorePolygon2DType (flags, ell, arcDivParams);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomIrregularPolygon2D (GS::UInt32 flags /*PolyFlags*/)
{
	polygon = new CorePolygon2DType (GetFlags (flags));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomIrregularPolygon2D (GS::UInt32 flags /*PolyFlags*/, const Box2DData& box)
{
	polygon = new CorePolygon2DType (GetFlags (flags), box);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::~CustomIrregularPolygon2D ()
{
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const ContourDescriptionArray& contourDescrArray) -> CustomIrregularPolygon2D
{
	typename CorePolygon2DType::Flags flags;
	GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (flags, contourDescrArray);
	return CustomIrregularPolygon2D::Create (newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const Polyline2DType& polyline) -> CustomIrregularPolygon2D
{

	GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (*polyline.polyline);
	return CustomIrregularPolygon2D::Create (newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																										  const ContourDescriptionArray& contourDescrArray) -> CustomIrregularPolygon2D
{
	GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (GetFlags (flags), contourDescrArray);
	return CustomIrregularPolygon2D::Create (newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const Point2D* coords, 
																										  USize nValuableCoords, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		typename CorePolygon2DType::Flags flags;
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (flags, coords, nValuableCoords, nullptr /*arcs*/, 0 /*nValuableArcs*/, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return CustomIrregularPolygon2D ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																										  const Point2D* coords, 
																										  USize nValuableCoords, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	CustomIrregularPolygon2D result;

	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (GetFlags (flags), coords, nValuableCoords, nullptr /*arcs*/, 0 /*nValuableArcs*/, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const Point2D* coords, 
																										  USize nValuableCoords,
																										  const PolyArcRec* arcs,
																										  USize nArcs,
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		typename CorePolygon2DType::Flags flags;
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (flags, coords, nValuableCoords, arcs, nArcs, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return CustomIrregularPolygon2D ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																										  const Point2D* coords, 
																										  USize nValuableCoords, 
																										  const PolyArcRec* arcs, 
																										  USize nArcs, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (GetFlags (flags), coords, nValuableCoords, arcs, nArcs, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return CustomIrregularPolygon2D ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const Point2D* coords, 
																										  USize nValuableCoords, 
																										  const PolyArcRec* arcs, 
																										  USize nValuableArcs, 
																										  const UIndex* contourEnds, 
																										  USize nContours, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	DBASSERT ((nValuableCoords == 0 && nContours == 0) || (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr));

	if (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr) {
		typename CorePolygon2DType::Flags flags;
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (flags, coords, nValuableCoords, arcs, nValuableArcs, contourEnds, nContours, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return CustomIrregularPolygon2D ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																										  const Point2D* coords, 
																										  USize nValuableCoords, 
																										  const PolyArcRec* arcs, 
																										  USize nValuableArcs, 
																										  const UIndex* contourEnds, 
																										  USize nContours, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	DBASSERT ((nValuableCoords == 0 && nContours == 0) || (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr));

	if (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr) {
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (GetFlags (flags), coords, nValuableCoords, arcs, nValuableArcs, contourEnds, nContours, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return CustomIrregularPolygon2D ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<Point2D>& coordList, 
																										  const GS::Array<PolyArcRec>& arcList, 
																										  const GS::Array<UIndex>& contourEndList, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	DBASSERT ((coordList.IsEmpty () && contourEndList.IsEmpty ()) || (!coordList.IsEmpty () && !contourEndList.IsEmpty ()));

	if (!coordList.IsEmpty () && !contourEndList.IsEmpty ()) {
		typename CorePolygon2DType::Flags flags;
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (flags, coordList, arcList, contourEndList, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return CustomIrregularPolygon2D ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																										  const GS::Array<Point2D>& coordList, 
																										  const GS::Array<PolyArcRec>& arcList, 
																										  const GS::Array<UIndex>& contourEndList, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	DBASSERT ((coordList.IsEmpty () && contourEndList.IsEmpty ()) || (!coordList.IsEmpty () && !contourEndList.IsEmpty ()));

	if (!coordList.IsEmpty () && !contourEndList.IsEmpty ()) {
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (GetFlags (flags), coordList, arcList, contourEndList, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return CustomIrregularPolygon2D ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<Point2D>& coordList, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	if (!coordList.IsEmpty ()) {
		GS::ArrayFB<PolyArcRec, 4> arcList;
		GS::ArrayFB<UIndex, 4> contourEndList;
		typename CorePolygon2DType::Flags flags;
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (flags, coordList, arcList, contourEndList, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return CustomIrregularPolygon2D ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																										  const GS::Array<Point2D>& coordList, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	if (!coordList.IsEmpty ()) {
		GS::ArrayFB<PolyArcRec, 4> arcList;
		GS::ArrayFB<UIndex, 4> contourEndList;
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType  (GetFlags (flags), coordList, arcList, contourEndList, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return CustomIrregularPolygon2D ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<Point2D>& coordList, 
																										  const GS::Array<PolyArcRec>& arcList, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	if (!coordList.IsEmpty ()) {
		GS::ArrayFB<UIndex, 4> contourEndList;
		typename CorePolygon2DType::Flags flags;
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (flags, coordList, arcList, contourEndList, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return CustomIrregularPolygon2D ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																										  const GS::Array<Point2D>& coordList, 
																										  const GS::Array<PolyArcRec>& arcList, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomIrregularPolygon2D
{
	if (!coordList.IsEmpty ()) {
		GS::ArrayFB<UIndex, 4> contourEndList;
		GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (GetFlags (flags), coordList, arcList, contourEndList, createFlags);
		return CustomIrregularPolygon2D::Create (newPolygon);
	}

	return CustomIrregularPolygon2D ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConvertToContourDescriptionArray () const -> ContourDescriptionArray
{
	ContourDescriptionArray contourDescrArray;
	polygon->Convert (contourDescrArray);
	return contourDescrArray;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConvertToPolylines () const -> MultiPolyline2DType
{
	return Polyline2DType::Create (*this);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConvertToPolyline (ConstContourIterator contourIterator) const -> Polyline2DType
{
	return Polyline2DType::Create (*this, contourIterator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
template <class VertexUserDataSrc, class EdgeUserDataSrc, class ContourUserDataSrc, class PolygonUserDataSrc>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConvertFromIrregularPolygon2D (
	const CustomIrregularPolygon2D<VertexUserDataSrc, EdgeUserDataSrc, ContourUserDataSrc, PolygonUserDataSrc>& fromPolygon,
	Poly2DUserDataConverter<VertexUserDataSrc, EdgeUserDataSrc, ContourUserDataSrc, PolygonUserDataSrc,
	VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>* converter /*= nullptr*/) -> CustomIrregularPolygon2D
{
	CustomIrregularPolygon2D result;
	result.CopyOnWrite ();
	CorePolygon2D<VertexUserDataSrc, EdgeUserDataSrc, ContourUserDataSrc, PolygonUserDataSrc>::ConvertFromCorePolygon2D (*result.polygon, *fromPolygon.polygon, converter);
	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonData (Point2D* coords, 
																												   USize& nValuableCoords, 
																												   PolyArcRec* arcs, 
																												   USize& nValuableArcs, 
																												   UIndex* contourEnds, 
																												   USize& nContours, 
																												   const GS::Array<ConstContourIterator>& reversedContours, 
																												   GS::UInt32 createFlags /*PolyCreateFlags*/) const
{
	GS::ArrayFB<UIndex, 4> reversedContourIndices;
	for (typename GS::Array <ConstContourIterator>::ConstIterator contourIter = reversedContours.Enumerate (); contourIter != nullptr; ++contourIter) {
		reversedContourIndices.Push (contourIter->GetItem ().GetIndex ());
	}
	polygon->CopyPolygonData (coords, nValuableCoords, arcs, nValuableArcs, contourEnds, nContours, reversedContourIndices, createFlags);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonData (GS::Array<Point2D>& coords, 
																												   GS::Array<PolyArcRec>& arcs,
																												   GS::Array<UIndex>& contourEnds,
																												   const GS::Array<ConstContourIterator>& reversedContours,
																												   GS::UInt32 createFlags /*PolyCreateFlags*/) const
{
	GS::ArrayFB<UIndex, 4> reversedContourIndices;
	for (typename GS::Array<ConstContourIterator>::ConstIterator contourIter = reversedContours.Enumerate (); contourIter != nullptr; ++contourIter) {
		reversedContourIndices.Push (contourIter->GetItem ().GetIndex ());
	}
	polygon->CopyPolygonData (coords, arcs, contourEnds, reversedContourIndices, createFlags);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AllocateAndCopyPolygonData (Point2D** coords, 
																														   USize& nValuableCoords, 
																														   PolyArcRec** arcs, 
																														   USize& nValuableArcs, 
																														   UIndex** contourEnds, 
																														   USize& nContours, 
																														   GS::UInt32 createFlags /*PolyCreateFlags*/) const
{
	DBASSERT (coords != nullptr && contourEnds != nullptr && (polygon->nArcs == 0 || arcs != nullptr));

	if (coords == nullptr || contourEnds == nullptr || (polygon->nArcs > 0 && arcs == nullptr))
		throw GeometryIllegalArgumentException ("Error in CustomIrregularPolygon2D::AllocateAndCopyPolygonData!!!", __FILE__, __LINE__);

	GS::ArrayFB<UIndex, 4> reversedContourIndices;

	polygon->CopyPolygonData (nullptr, nValuableCoords, nullptr, nValuableArcs, nullptr, nContours, reversedContourIndices, createFlags);

	if (IsEmpty ())
		return;

	USize coordOffset = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 1 : 0;
	*coords			= reinterpret_cast<Point2D*>(BMAllocatePtr ((nValuableCoords + coordOffset) * sizeof (Point2D), ALLOCATE_CLEAR, 0));

	if (arcs != nullptr) {
		USize arcOffset = (PolyCreateFlags_DummyArcAtIdxZero & createFlags) ? 1 : 0;
		*arcs			= reinterpret_cast<PolyArcRec*>(BMAllocatePtr ((nValuableArcs + arcOffset) * sizeof (PolyArcRec), ALLOCATE_CLEAR, 0));
	}

	USize contourEndOffset = (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags) ? 1 : 0;
	*contourEnds	= reinterpret_cast<UIndex*>(BMAllocatePtr ((nContours + contourEndOffset) * sizeof (UIndex), ALLOCATE_CLEAR, 0));

	polygon->CopyPolygonData ((coords != nullptr) ? *coords : nullptr, nValuableCoords, (arcs != nullptr) ? *arcs : nullptr, nValuableArcs,
		(contourEnds != nullptr) ? *contourEnds : nullptr, nContours, reversedContourIndices, createFlags);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator= (const CustomIrregularPolygon2D& source) -> CustomIrregularPolygon2D&
{
	if (this == &source)
		return *this;

	if (polygon != source.polygon)
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
		polygon = new CorePolygon2DType (*source.polygon);
#else
		polygon = source.polygon;
#endif
	return *this;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator== (const CustomIrregularPolygon2D& rightOp) const
{
	return polygon->Compare (*rightOp.polygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator!= (const CustomIrregularPolygon2D& rightOp) const
{
	return !operator== (rightOp);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSameDirEdgeLegal () const
{
	return polygon->GetSameDirEdgeLegal ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetForce64BitPrecision () const
{
	return polygon->GetForce64BitPrecision ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetPolyFlags (GS::UInt32 polyFlags /*PolyFlags*/)
{
	CheckPolyFlags (polyFlags);
	
	if (PolyFlags_IsVertexUserData & polyFlags && !polygon->flags.isVertexUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsVertexUserData (true);
	}
	if (PolyFlags_NoVertexUserData & polyFlags && polygon->flags.isVertexUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsVertexUserData (false);
	}
	if (PolyFlags_IsEdgeUserData & polyFlags && !polygon->flags.isEdgeUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsEdgeUserData (true);
	}
	if (PolyFlags_NoEdgeUserData & polyFlags && polygon->flags.isEdgeUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsEdgeUserData (false);
	}
	if (PolyFlags_IsContourUserData & polyFlags && !polygon->flags.isContourUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsContourUserData (true);
	}
	if (PolyFlags_NoContourUserData & polyFlags && polygon->flags.isContourUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsContourUserData (false);
	}
	if (PolyFlags_IsPolygonUserData & polyFlags && !polygon->flags.isPolygonUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsPolygonUserData (true);
	}
	if (PolyFlags_NoPolygonUserData & polyFlags && polygon->flags.isPolygonUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsPolygonUserData (false);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CheckPolyFlags (GS::UInt32 polyFlags /*PolyFlags*/)
{
#ifdef DEBUVERS
	DBASSERT (!((PolyFlags_IsSameDirEdgeLegal & polyFlags) && (PolyFlags_NoSameDirEdgeLegal & polyFlags)));
	//DBASSERT (!(PolyFlags_IsSameDirEdgeLegal & polyFlags));
	DBASSERT (!(PolyFlags_NoSameDirEdgeLegal & polyFlags));
	DBASSERT (!(PolyFlags_IsClosed & polyFlags));
	DBASSERT (!(PolyFlags_NoClosed & polyFlags));
	DBASSERT (!(PolyFlags_IsSameCoord & polyFlags));
	DBASSERT (!(PolyFlags_NoSameCoord & polyFlags));
	DBASSERT (!((PolyFlags_IsVertexUserData & polyFlags) && (PolyFlags_NoVertexUserData & polyFlags)));
	DBASSERT (!((PolyFlags_IsEdgeUserData & polyFlags) && (PolyFlags_NoEdgeUserData & polyFlags)));
	DBASSERT (!((PolyFlags_IsContourUserData & polyFlags) && (PolyFlags_NoContourUserData & polyFlags)));
	DBASSERT (!((PolyFlags_IsPolygonUserData & polyFlags) && (PolyFlags_NoPolygonUserData & polyFlags)));
#else
	UNUSED_PARAMETER (polyFlags);
#endif
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::UInt32	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPolyFlags () const //PolyFlags
{
	GS::UInt32 flags = 0;

	flags |= PolyFlags_IsSameDirEdgeLegal; //Ezt nem lehet kivulrol allitani

	if (polygon->GetIsVertexUserData ())
		flags |= PolyFlags_IsVertexUserData;
	else 
		flags |= PolyFlags_NoVertexUserData;

	if (polygon->GetIsEdgeUserData ())
		flags |= PolyFlags_IsEdgeUserData;
	else 
		flags |= PolyFlags_NoEdgeUserData;

	if (polygon->GetIsContourUserData ())
		flags |= PolyFlags_IsContourUserData;
	else 
		flags |= PolyFlags_NoContourUserData;

	if (polygon->GetIsPolygonUserData ())
		flags |= PolyFlags_IsPolygonUserData;
	else 
		flags |= PolyFlags_NoPolygonUserData;

	return flags;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexIterator (UIndex vertexIdx) const -> ConstVertexIterator
{
	DBCHECKIRREGULARINDEX(vertexIdx, 1, polygon->GetVertexNum () + 1);

	ConstPolyVertexInPolyState<CustomIrregularPolygon2D, VertexUserData> item (this, vertexIdx);
	return CustomIrregularPolygon2D::ConstVertexIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexIterator (const Point2D& coord) const -> ConstVertexIterator
{
	return GetVertexIterator(polygon->GetVertexIdx (coord));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateVertex () const -> ConstVertexIterator
{
	return GetVertexIterator(1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::BeginVertex () const -> ConstVertexIterator
{
	return GetVertexIterator (1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EndVertex	() const -> ConstVertexIterator
{
	return GetVertexIterator (polygon->GetVertexNum() + 1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateVertex (const VertexUserData& id) const -> ConstVertexIterator
{
	ConstPolyVertexInPolyState<CustomIrregularPolygon2D, VertexUserData> item (this, id);
	return CustomIrregularPolygon2D::ConstVertexIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeIterator (UIndex edgeIdx) const -> ConstEdgeIterator
{
	DBCHECKIRREGULARINDEX(edgeIdx, 1, polygon->GetEdgeNum () + 1);

	ConstPolyEdgeInPolyState<CustomIrregularPolygon2D, EdgeUserData> item (this, edgeIdx);
	return CustomIrregularPolygon2D::ConstEdgeIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateEdge () const -> ConstEdgeIterator
{
	return GetEdgeIterator (1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::BeginEdge () const -> ConstEdgeIterator
{
	return GetEdgeIterator (1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EndEdge () const -> ConstEdgeIterator
{
	return GetEdgeIterator (polygon->GetEdgeNum () + 1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateEdge (const EdgeUserData& id) const -> ConstEdgeIterator
{
	ConstPolyEdgeInPolyState<CustomIrregularPolygon2D, EdgeUserData> item (this, id);
	return CustomIrregularPolygon2D::ConstEdgeIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourIterator (UIndex contourIdx) const -> ConstContourIterator
{
	DBCHECKIRREGULARINDEX(contourIdx, 1, polygon->GetContourNum () + 1);

	Contour item (this, contourIdx);
	return CustomIrregularPolygon2D::ConstContourIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateContour () const -> ConstContourIterator
{
	return GetContourIterator(1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::BeginContour () const -> ConstContourIterator
{
	return GetContourIterator (1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EndContour () const -> ConstContourIterator
{
	return GetContourIterator (polygon->GetContourNum() + 1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateContour (const ContourUserData& id) const -> ConstContourIterator
{
	Contour item (this, id);
	return CustomIrregularPolygon2D::ConstContourIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateHoleContour () const -> ConstContourIterator
{
	Contour item (this, 2, polygon->GetContourNum(), 2);
	return CustomIrregularPolygon2D::ConstContourIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetPolyUserData (const PolygonUserData& polyId)
{
	CopyOnWrite ();
	polygon->SetUserData (&polyId);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const	PolygonUserData& CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPolyUserData () const
{
	return *polygon->GetUserData ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetVertexDefaultUserData (const VertexUserData& userData)
{
	CopyOnWrite ();
	polygon->SetVertexDefaultUserData (userData);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResetUserData ()
{
	CopyOnWrite ();
	polygon->ResetUserData ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const VertexUserData&	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexDefaultUserData () const
{
	return polygon->GetVertexDefaultUserData ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexNum () const
{
	return polygon->GetVertexNum ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertex (const ConstVertexIterator& vertexIterator) const -> Vertex
{
	Vertex vertex;
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	vertex.SetCoord (polygon->GetCoord (vertexIterator.GetItem ().GetIndex ()));
	vertex.SetPolyVertexUserData (*polygon->GetVertexUserData (vertexIterator.GetItem ().GetIndex ()));
	return vertex;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const Point2D&	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetCoord (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return polygon->GetCoord (vertexIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const VertexUserData&	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexUserData (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return *polygon->GetVertexUserData (vertexIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetVertexUserData (const ConstVertexIterator& vertexIterator, const VertexUserData& vertexId)
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	polygon->SetVertexUserData (vertexIterator.GetItem ().GetIndex (), &vertexId);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeDefaultUserData (const EdgeUserData& userData)
{
	CopyOnWrite ();
	polygon->SetEdgeDefaultUserData (userData);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const EdgeUserData&		CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeDefaultUserData () const
{
	return polygon->GetEdgeDefaultUserData ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeNum () const
{
	return polygon->GetEdgeNum ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdge (const ConstEdgeIterator& edgeIterator) const -> Edge
{
	Edge edge;
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	edge.SetArcAngle (polygon->GetArcAngle (edgeIterator.GetItem ().GetIndex ()));
	edge.SetPolyEdgeUserData (*polygon->GetEdgeUserData (edgeIterator.GetItem ().GetIndex ()));
	return edge;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSector (const ConstEdgeIterator& edgeIterator, Sector& sect, GenArc& genArc) const
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return polygon->GetSector (edgeIterator.GetItem ().GetIndex (), sect, genArc);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSector (const ConstEdgeIterator& edgeIterator, Point2D& begC, Point2D& endC, double& angle) const
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return polygon->GetSector (edgeIterator.GetItem ().GetIndex (), begC, endC, angle);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Optional<Sector>	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSector (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return polygon->GetSector (edgeIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Optional<GenArc>	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetArc (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return polygon->GetArc (edgeIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const EdgeUserData&		CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeUserData (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return *polygon->GetEdgeUserData (edgeIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeUserData (const ConstEdgeIterator& edgeIterator, const EdgeUserData& edgeId)
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	polygon->SetEdgeUserData (edgeIterator.GetItem ().GetIndex (), &edgeId);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetContourDefaultUserData (const ContourUserData& userData)
{
	CopyOnWrite ();
	polygon->SetContourDefaultUserData (userData);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const ContourUserData&	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourDefaultUserData () const
{
	return polygon->GetContourDefaultUserData ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourNum () const
{
	return polygon->GetContourNum ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContour (const ConstContourIterator& contourIterator) const -> CustomIrregularPolygon2D
{
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	CustomIrregularPolygon2D contour;
	contour.polygon = new CorePolygon2DType (*polygon, contourIterator.GetItem ().GetIndex (), false /*keepRegularized*/);
	return contour;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const ContourUserData&		CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourUserData (const ConstContourIterator& contourIterator) const
{
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	return *polygon->GetContourUserData (contourIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetContourUserData (const ConstContourIterator& contourIterator, const ContourUserData& contourId)
{
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	polygon->SetContourUserData (contourIterator.GetItem ().GetIndex (), &contourId);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetBeginVertex (const ConstEdgeIterator& edgeIterator) const -> ConstVertexIterator
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return GetVertexIterator (polygon->GetBeginVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEndVertex (const ConstEdgeIterator& edgeIterator) const -> ConstVertexIterator
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return GetVertexIterator (polygon->GetEndVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetNextEdge (const ConstVertexIterator& vertexIterator) const -> ConstEdgeIterator
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return GetEdgeIterator (polygon->GetNextEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPrevEdge (const ConstVertexIterator& vertexIterator) const -> ConstEdgeIterator
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return GetEdgeIterator (polygon->GetPrevEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsVertexInContour (UIndex contourIdx, UIndex vertexIdx) const
{
	if (vertexIdx < polygon->GetVertexBeginIdxInContour (contourIdx))
		return false;
	if (vertexIdx >= polygon->GetVertexEndIdxInContour (contourIdx))
		return false;

	return true;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsEdgeInContour (UIndex contourIdx, UIndex edgeIdx) const
{
	if (edgeIdx < polygon->GetEdgeBeginIdxInContour (contourIdx))
		return false;
	if (edgeIdx >= polygon->GetEdgeEndIdxInContour (contourIdx))
		return false;

	return true;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsEmpty () const
{
	return polygon->IsEmpty ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::HasArcs () const
{
	return polygon->nArcs > 0;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Clear ()
{
	CopyOnWrite ();
	polygon->Clear ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsABox () const
{
	return polygon->IsABox ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Optional<Circle2D>	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetMatchingCircle (void) const
{
	Circle2D circle;
	if (polygon->IsACircle (circle))
		return circle;
	else
		return GS::NoValue;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Regularize (PolyRegularizationMode mode /*= PolyRegularizationMode_Default*/) const -> MultiPolygon2DType
{
	if (polygon->status.isRegularized) {
		MultiPolygon2DType result;
		if (!IsEmpty ()) {
			CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> polyCopy (polygon);
			result.Push (polyCopy);
		}
		return result;
	}

	return Polygon2DType::Regularize (*this, mode);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Regularize (UIndex regularizationResultsMask,
																											  UIndex& regularizationResults,
																											  GS::Array<GS::Array<typename Polygon2DType::ConstContourIterator>>* reversedContours /*= nullptr*/)
	-> MultiPolygon2DType
{
	MultiPolygon2DType result;
	regularizationResults = 0;

	if (polygon->status.isRegularized) {
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> polyCopy (polygon);
		result.Push (polyCopy);
		return result;
	}

	// although this instance is the same before and after regularization its userData is replaced and restored
	// during the process so we need to make a copy if there are more references to it
	CopyOnWrite ();
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	GS::ArrayFB < GS::Array<UIndex>, 4 > reversedContourIdxs;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Regularize (polygonArray, regularizationResultsMask, regularizationResults,
		(reversedContours == nullptr) ? nullptr : &reversedContourIdxs);
	if (polyResult == CorePolygon2DType::ResultSameAsThis) {
		Polygon2DType poly (polygon);
		result.Push (poly);
		if (reversedContours != nullptr) {
			GS::ArrayFB <typename Polygon2DType::ConstContourIterator, 4> emptyRevContours;
			reversedContours->Push (emptyRevContours);
		}
	} else if (polyResult == CorePolygon2DType::EmptyPolygon) {
		Polygon2DType emptyPoly (new CorePolygon2DType (*polygon, true));
		result.Push (emptyPoly);
		if (reversedContours != nullptr) {
			GS::ArrayFB <typename Polygon2DType::ConstContourIterator, 4> emptyRevContours;
			reversedContours->Push (emptyRevContours);
		}
	} else {
		result = Polygon2DType::Create (polygonArray);
		if (reversedContours != nullptr) {
			for (UIndex polyIdx = 0; polyIdx < reversedContourIdxs.GetSize (); ++polyIdx) {
				GS::ArrayFB <typename Polygon2DType::ConstContourIterator, 4> revContoursCurrPoly;
				for (UIndex contourIdx = 0; contourIdx < reversedContourIdxs[polyIdx].GetSize (); ++contourIdx)
					revContoursCurrPoly.Push (result[polyIdx].GetContourIterator ((reversedContourIdxs[polyIdx])[contourIdx]));
				reversedContours->Push (revContoursCurrPoly);
			}
		}
	}

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Read (GS::IChannel& ic)
{
	typename CorePolygon2DType::Flags flags;
	polygon = new CorePolygon2DType (flags);
	return polygon->Read (ic);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Write (GS::OChannel& oc) const
{
	return polygon->Write (oc);
}


extern GEOMETRY_DLL_EXPORT const char*		XMLIrregular_Tag_IrregularPolygon2D;
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadXML	(GS::XMLIChannel& ic)
{
	GS::XMLITag tag (ic, XMLIrregular_Tag_IrregularPolygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		GS::ClassVersion currentClassVersion;
		ic.ReadXMLVersionAttr (currentClassVersion);
		//currentClassVersion.ReadXML (ic);
		DBASSERT (currentClassVersion == IrregularPolygon2DPrivate::classInfo.GetVersion ());
	}

	polygon = CorePolygon2DType::ReadXMLAndCreate (ic);
	if (polygon == nullptr)
		throw GeometryIllegalArgumentException ("Can't Read XML file!!!", __FILE__, __LINE__);

	return ic.GetErrorStatus () == GS::XMLIChannel::Ok ? NoError : Error;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteXML (GS::XMLOChannel& oc) const
{
	GSErrCode errCode = NoError;
	GS::XMLTag tag (oc, XMLIrregular_Tag_IrregularPolygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		oc.WriteXMLVersionAttr (IrregularPolygon2DPrivate::classInfo.GetVersion ());
		//GetClassVersion ().WriteXML (oc);
	}

	errCode = polygon->WriteXML (oc);
	if (errCode != NoError)
		return errCode;
	return oc.GetErrorStatus () == GS::XMLOChannel::Ok ? NoError : Error;
}


//Calculate
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const Box2DData&	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetBoundBox () const
{
	return polygon->GetBoundBox ();
}


// Returns the signed area of the Polygon
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double  CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcSignedArea () const
{
	return polygon->CalcArea ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
Point2D	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetCenter () const
{
	Box2DData polyBoundBox = polygon->GetBoundBox ();
	Point2D centerC  = Point2D ((polyBoundBox.xMin + polyBoundBox.xMax) / 2.0, (polyBoundBox.yMin + polyBoundBox.yMax) / 2.0);
	return centerC;
}


//Onatmetszo esetben (ahol amugy sincs ertelme koruljarasi iranyrol beszelni) a szamolt terulet egy resze negativ, masik resze pozitiv lesz,
//tehat az abszolut ertekben vett nagyobb teruletu reszek "gyoznek"
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::HasPositiveOrientation (const ConstContourIterator& contourIterator) const
{
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	return polygon->HasPositiveOrientation (contourIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcPerimeter () const
{
	return polygon->CalcPerimeter ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcContourPerimeter (const ConstContourIterator& contourIterator) const
{
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	return polygon->CalcPerimeter (contourIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcMaxVertexFillet (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return polygon->CalcMaxVertexFillet (vertexIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsCoordOnEdge (const Point2D& c, ConstEdgeIterator* edgeIt) const
{
	UIndex edgeIndex;
	bool result = polygon->IsCoordOnEdge (c, edgeIndex);
	if (edgeIt != nullptr) {
		if (result)
			*edgeIt = GetEdgeIterator (edgeIndex);
		else
			*edgeIt = ConstEdgeIterator ();
	}
	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DistanceFromPoint (const Point2D& c) const
{
	return polygon->DistanceFromPoint (c);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Point2D& point, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	return polygon->GetPosition (point, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Sector& sect, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	return polygon->GetPosition (sect, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GenArc& arc, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	return polygon->GetPosition (arc, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Box2DData& box, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	return polygon->GetPosition (box, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const CustomIrregularPolygon2D& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	return polygon->GetPosition (*poly.polygon, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	return polygon->GetPosition (*poly.polyline, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PGPositionExt	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentIn (Sector sector, GS::Array<Sector>* resSectors /*= nullptr*/) const
{
	return polygon->SegmentIn (sector, resSectors);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PGPositionExt	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentOut (Sector sector, GS::Array<Sector>* resSectors /*= nullptr*/) const
{
	return polygon->SegmentOut (sector, resSectors);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Intersect (const Point2D& c, const Vector2D& dir, GS::Array<Sector>* result) const
{
	return polygon->Intersect (c, dir, result);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::FixArray<Point2D, 4>	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetTransformedBoundBox (const TRANMAT& tr, const TRANMAT& invTr /*= Geometry::IdentityTranMat*/) const
{
	return polygon->GetTransformedBoundBox (tr, invTr);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Visit (ConstVertexVisitor &visitor) const
{
	polygon->Visit (visitor);
}


//Modify polygon
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveHoles ()
{
	GS::SharedPtr<CorePolygon2DType> result;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->RemoveHoles (result);
	SetResult (polyResult, result);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteHole (const ConstContourIterator& contourIterator)
{
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	polygon = polygon->DeleteHole (contourIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Move (Vector2D offset)
{
	CopyOnWrite ();
	polygon->Move (offset);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearVertexIds ()
{
	CopyOnWrite ();
	polygon->ClearVertexUserDatas ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MakeGoodOrientation ()
{
	CopyOnWrite ();
	polygon->UpdateOrientation ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearEdgeIds ()
{
	CopyOnWrite ();
	polygon->ClearEdgeUserDatas ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearContourIds ()
{
	CopyOnWrite ();
	polygon->ClearContourUserDatas ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RotateVerticeIndicesInContour (const ConstContourIterator& contourToRotate, const ConstVertexIterator& vertexToFirst)
{
	CopyOnWrite ();
	polygon->RotateVerticeIndicesInContour (contourToRotate.GetItem ().GetIndex (), vertexToFirst.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SwapContourOrder (const GS::Array<ConstContourIterator>& newContourOrder)
{
	CopyOnWrite ();

	GS::ArrayFB<UIndex, 4> newContourOrderInIdx;
	newContourOrderInIdx.SetCapacity (newContourOrder.GetSize ());
	for (UIndex i = 0; i < newContourOrder.GetSize (); ++i)
		newContourOrderInIdx.Push (newContourOrder[i].GetItem ().GetIndex ());

	polygon->SwapContourOrder (newContourOrderInIdx);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SortArcsByIndices ()
{
	CopyOnWrite ();
	polygon->SortArcsByIndices ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Stretch (	const Point2D& fixPoint,
									const Point2D& draggedPoint,
									const Vector2D& offsetAxisX,
									const Vector2D& offsetAxisY /*= Vector (0.0, 0.0)*/,
									const ArcDivParams& arcDivParams /*= ArcDivParams (0.0)*/)
{
	CopyOnWrite ();
	polygon->Stretch (fixPoint, draggedPoint, offsetAxisX, offsetAxisY, arcDivParams);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::TransformPreserveArcs (const TRANMAT& tran)
{
	CopyOnWrite ();

	polygon->TransformPreserveArcs (tran);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::TransformPreserveArcs (const CustomIrregularPolygon2D& filterWithPolygon, const TRANMAT& tran)
{
	CopyOnWrite ();
	bool isTransformedAll;
	polygon->TransformPreserveArcs (*filterWithPolygon.polygon, tran, isTransformedAll);
	return isTransformedAll;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::TransformPreserveArcs (const MultiIrregularPolygon2DType& filterWithPolygon, const TRANMAT& tran)
{
	CopyOnWrite ();
	bool isTransformedAll;
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> filterPolygonArray;
	filterWithPolygon.GetCorePolygon2DArray (filterPolygonArray);
	polygon->TransformPreserveArcs (filterPolygonArray, tran, isTransformedAll);
	return isTransformedAll;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::TransformHolePreserveArcs (const GS::Array<ConstContourIterator>& contourIterators, 
																															 const GS::Array<TRANMAT>& trans, 
																															 bool keepOriginals)
{
	CopyOnWrite ();

	GS::ArrayFB<UIndex, 4> contourIdxs;
	for (typename GS::ArrayFB <ConstContourIterator, 4>::ConstIterator contourIter = contourIterators.Enumerate (); contourIter != nullptr; ++contourIter) {
		contourIdxs.Push (contourIter->GetItem ().GetIndex ());
	}
	polygon->TransformHolePreserveArcs (contourIdxs, trans, keepOriginals);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentUp (const ArcDivParams& arcDivParams)
{
	CopyOnWrite ();

	polygon->SegmentUp (arcDivParams);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EliminateArcs ()
{
	CopyOnWrite ();

	polygon->EliminateArcs ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MoveVertex (const ConstVertexIterator& vertexIterator, const Point2D& newPosition)
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();

	polygon->MoveVertex (vertexIterator.GetItem ().GetIndex (), newPosition);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertVertex (const ConstEdgeIterator& edgeIterator, const Point2D& newPosition)
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();

	polygon->InsertVertex (edgeIterator.GetItem ().GetIndex (), newPosition);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertEdge (const ConstVertexIterator& vertexIterator)
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	UIndex vertexIndex = vertexIterator.GetItem ().GetIndex ();
	CopyOnWrite ();

	polygon->InsertEdge (vertexIndex);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertVertexOnPolygon (const Point2D& newPosition, 
																														 const ConstEdgeIterator& edgeIterator, 
																														 CustomIrregularPolygon2D& result, 
																														 ConstVertexIterator* vertexIterator /*= nullptr*/)
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();

	GS::SharedPtr<CorePolygon2DType> newPolygon;
	UIndex vertexIndex = 0;
	polygon->InsertVertexOnPolygon (newPosition, edgeIterator.GetItem ().GetIndex (), newPolygon, vertexIndex);
	result.polygon = newPolygon;
	if (vertexIterator != nullptr)
		*vertexIterator = result.GetVertexIterator (vertexIndex);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteVertex (const ConstVertexIterator& vertexIterator)
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();

	polygon->DeleteVertex (vertexIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeAngle (const ConstEdgeIterator& edgeIterator, double edgeAngle)
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();

	polygon->SetEdgeAngle (edgeIterator.GetItem ().GetIndex (), edgeAngle);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MoveVertices (const GS::Array<GS::Pair<ConstVertexIterator, Point2D>>& newVertexPositions)
{
	GS::HashTable<UIndex, Point2D> indexToCoordTable;
	for (const GS::Pair<ConstVertexIterator, Point2D>& vertexWithPosition : newVertexPositions) {
		DBASSERT (vertexWithPosition.first.GetTarget ()->polygon == polygon);
		UIndex vertexIndex = vertexWithPosition.first.GetItem ().GetIndex ();
		DBASSERT (!indexToCoordTable.ContainsKey (vertexIndex));
		indexToCoordTable.Add (vertexIndex, vertexWithPosition.second);
	}
	CopyOnWrite ();

	polygon->MoveVertices (indexToCoordTable);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdge (const ConstEdgeIterator& edgeIterator, const GS::Array<GenArc>& arcs, const ArcDivParams& arcDivParams)
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();

	polygon->ReplaceEdge (edgeIterator.GetItem ().GetIndex (), arcs, arcDivParams);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdge (const ConstEdgeIterator& edgeIterator, 
																											const GS::Array<double>& angles, 
																											const GS::Array<Point2D>& internalVerts)	
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();

	polygon->ReplaceEdge (edgeIterator.GetItem ().GetIndex (), angles, internalVerts);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AddHole (const CustomIrregularPolygon2D& poly, const ConstContourIterator& contourIterator)
{
	DBASSERT (contourIterator.GetTarget ()->polygon == poly.polygon);
	CopyOnWrite ();

	polygon->AddHole (*poly.polygon, contourIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveSameDirEdge ()
{
	CopyOnWrite ();
	polygon->RemoveSameDirEdge ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveZeroEdgesAndArcs (double minEdgeLength, double minArcAngle)
{
	CopyOnWrite ();
	polygon->RemoveZeroEdgesAndArcs (minEdgeLength, minArcAngle);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Visit (VertexVisitor &visitor)
{
	CopyOnWrite ();
	polygon->Visit (visitor);
}


//Create new polygons
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetContour (const ConstContourIterator& contourIterator, double offset) const -> CustomIrregularPolygon2D
{
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->OffsetContour (contourIterator.GetItem ().GetIndex (), offset, newPolygon);
	return CreateResult (polyResult, newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetEdge (const ConstEdgeIterator& edgeIterator, double offset) const -> CustomIrregularPolygon2D
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->OffsetEdge (edgeIterator.GetItem ().GetIndex (), offset, newPolygon);
	return CreateResult (polyResult, newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetMultipleEdges (const GS::Array<GS::Pair<ConstEdgeIterator, double>>& offsets) const 
	-> CustomIrregularPolygon2D
{
	GS::Array<GS::Pair<UIndex, double> > offsetIndices (offsets.GetSize ());
	for (UIndex i = 0; i < offsets.GetSize (); ++i) {
		DBASSERT (offsets[i].first.GetTarget ()->polygon == polygon);
		offsetIndices.Push (GS::Pair<UIndex, double> (offsets[i].first.GetItem ().GetIndex (), offsets[i].second));
	}
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->OffsetMultipleEdges (offsetIndices, newPolygon);
	return CreateResult (polyResult, newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetEdgeFixArea (const ConstEdgeIterator& edgeIterator, 
																													 const ConstVertexIterator& vertexIterator, 
																													 double offset, 
																													 double area) const -> CustomIrregularPolygon2D
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->OffsetEdgeFixArea (edgeIterator.GetItem ().GetIndex (), vertexIterator.GetItem ().GetIndex (), offset, area, newPolygon);
	return CreateResult (polyResult, newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletAllVertex (const double filletRadius) const -> CustomIrregularPolygon2D
{
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->FilletAllVertex (filletRadius, newPolygon);
	return CreateResult (polyResult, newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletVertex (const ConstVertexIterator& vertexIterator,
																												const double filletRadius) const -> CustomIrregularPolygon2D
{
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->FilletVertex (vertexIterator.GetItem ().GetIndex (), filletRadius, newPolygon);
	return CreateResult (polyResult, newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletVertexInContour (const ConstContourIterator& contourIterator,
																														 const double filletRadius) const -> CustomIrregularPolygon2D
{
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->FilletVertexInContour (contourIterator.GetItem ().GetIndex (), filletRadius, newPolygon);
	return CreateResult (polyResult, newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferAllVertex (const double chamferRadius) const -> CustomIrregularPolygon2D
{
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->ChamferAllVertex (chamferRadius, newPolygon);
	return CreateResult (polyResult, newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferVertex (const ConstVertexIterator& vertexIterator,
																												 const double chamferRadius) const -> CustomIrregularPolygon2D
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->ChamferVertex (vertexIterator.GetItem ().GetIndex (), chamferRadius, newPolygon);
	return CreateResult (polyResult, newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferVertexInContour (const ConstContourIterator& contourIterator,
																														  const double chamferRadius) const -> CustomIrregularPolygon2D
{
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->ChamferVertexInContour (contourIterator.GetItem ().GetIndex (), chamferRadius, newPolygon);
	return CreateResult (polyResult, newPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteEdge (const ConstEdgeIterator& edgeIterator, CustomIrregularPolygon2D& result) const
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	bool success = polygon->DeleteEdge (edgeIterator.GetItem ().GetIndex (), newPolygon);
	result.polygon = newPolygon;
	return success;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Unify (const CustomIrregularPolygon2D& poly) const -> MultiIrregularPolygon2DType
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Unify (*poly.polygon, polygonArray);
	return CreateResult (polyResult, &poly, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Intersect (const CustomIrregularPolygon2D& poly, 
																											 Boundary boundaries /*= Boundary_Closed*/,
																											 RelativePosition* relativePosition /*= nullptr*/,
																											 DetailedRelativePosition* detailed /*= nullptr*/) const -> MultiIrregularPolygon2DType
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>,4> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Intersect (*poly.polygon, polygonArray, boundaries, relativePosition, detailed);
	return CreateResult (polyResult, &poly, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Substract (const CustomIrregularPolygon2D& poly, 
																											 Boundary boundaries /*= Boundary_Closed*/, 
																											 RelativePosition* relativePosition /*= nullptr*/, 
																											 DetailedRelativePosition* detailed /*= nullptr*/) const -> MultiIrregularPolygon2DType
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Substract (*poly.polygon, polygonArray, boundaries, relativePosition, detailed);
	return CreateResult (polyResult, &poly, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Cut (const HalfPlane2DData& cutline, 
																									   bool* fullin /*= nullptr*/,
																									   GS::Int32* wrcode /*= nullptr*/,
																									   bool* degen /*= nullptr*/) const -> MultiIrregularPolygon2DType
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Cut (cutline, false /*regularizeResults*/, polygonArray, fullin, wrcode, degen);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Cut (const GS::Array<HalfPlane2DData>& cutlines, 
																									   bool* fullin /*= nullptr*/,
																									   GS::Int32* wrcode /*= nullptr*/,
																									   bool* degen /*= nullptr*/) const -> MultiIrregularPolygon2DType
{

	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Cut (cutlines, false /*regularizeResults*/, polygonArray, fullin, wrcode, degen);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Strip (const HalfPlane2DData& cutline1, 
																										 const HalfPlane2DData& cutline2, 
																										 GS::Int32* wrcode /*= nullptr*/) const -> MultiIrregularPolygon2DType
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Strip (cutline1, cutline2, false /*regularizeResults*/, polygonArray, wrcode);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Clip (const Box2DData& box, GS::Int32* wrcode /*= nullptr*/) const -> MultiIrregularPolygon2DType
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Clip (box, false /*regularizeResults*/, polygonArray, wrcode);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Sector& sector, Boundary cutBoundaries, SectorCreator& creator) const
{
	polygon->CutElem (sector, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const GenArc& genArc, Boundary cutBoundaries, GenArcCreator& creator) const
{
	polygon->CutElem (genArc, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Point2D& coord, Boundary cutBoundaries, PointCreator& creator) const
{
	polygon->CutElem (coord, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const BezierDetails& bezier, Boundary cutBoundaries, SplineCreator& creator) const
{
	polygon->CutElem (bezier, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const CustomIrregularPolygon2D& poly, Boundary cutBoundaries, IrregularPolygon2DCreatorType& creator) const
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4 > results;
	polygon->CutElem (poly.polygon, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> polygon (results[polyIdx]);
		creator.CreateIrregularPolygon2D (polygon);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Polyline2DType& poly, Boundary cutBoundaries, Polyline2DCreatorType& creator) const
{
	GS::ArrayFB<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>, 4 > results;
	polygon->CutElem (poly.polyline, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> polyline (results[polyIdx]);
		creator.CreatePolyline2D (polyline);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Sector& sector, Boundary cutBoundaries) const -> GS::Array<Sector>
{
	GS::Array<Sector> results;
	polygon->CutElem (sector, cutBoundaries, results);
	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const GenArc& genArc, Boundary cutBoundaries) const -> GS::Array<GenArc>
{
	GS::Array<GenArc> results;
	polygon->CutElem (genArc, cutBoundaries, results);
	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Point2D& coord, Boundary cutBoundaries) const -> GS::Array<Point2D>
{
	GS::Array<Point2D> results;
	polygon->CutElem (coord, cutBoundaries, results);
	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const BezierDetails& bezier, Boundary cutBoundaries) const ->GS::Array<BezierDetails>
{
	GS::Array<BezierDetails> results;
	polygon->CutElem (bezier, cutBoundaries, results);
	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const CustomIrregularPolygon2D& poly, Boundary cutBoundaries) const -> MultiIrregularPolygon2DType
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	polygon->CutElem (poly.polygon, cutBoundaries, polygonArray);
	return CustomIrregularPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Polyline2DType& poly, Boundary cutBoundaries) const -> MultiPolyline2DType
{
	MultiPolyline2DType results;
	GS::ArrayFB<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>, 4> polylineArray;
	polygon->CutElem (poly.polyline, cutBoundaries, polylineArray);
	for (typename GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>>::Iterator lineIter = polylineArray.Enumerate (); lineIter != nullptr; ++lineIter) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> tmpPolyline;
		tmpPolyline.polyline = *lineIter;
		results.Push (tmpPolyline);
	}

	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Array<Sector>	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IntersectElemBorderOnly (const Sector& sector) const
{
	GS::Array<Sector> res;
	polygon->IntersectElemBorderOnly (sector, res);
	return res;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Array<GenArc>	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IntersectElemBorderOnly (const GenArc& arc) const
{
	GS::Array<GenArc> res;
	polygon->IntersectElemBorderOnly (arc, res);
	return res;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Sector& sector, Boundary cutBoundaries, SectorCreator& creator) const
{
	polygon->ElemPolyDifference (sector, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const GenArc& genArc, Boundary cutBoundaries, GenArcCreator& creator) const
{
	polygon->ElemPolyDifference (genArc, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Point2D& coord, Boundary cutBoundaries, PointCreator& creator) const
{
	polygon->ElemPolyDifference (coord, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const BezierDetails& bezier, Boundary cutBoundaries, SplineCreator& creator) const
{
	polygon->ElemPolyDifference (bezier, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const CustomIrregularPolygon2D& poly, 
																													  Boundary cutBoundaries, 
																													  IrregularPolygon2DCreatorType& creator) const
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> results;
	polygon->ElemPolyDifference (poly.polygon, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> polygon (results[polyIdx]);
		creator.CreateIrregularPolygon2D (polygon);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Polyline2DType& poly, Boundary cutBoundaries, Polyline2DCreatorType& creator) const
{
	GS::ArrayFB<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>, 4> results;
	polygon->ElemPolyDifference (poly.polyline, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> polyline (results[polyIdx]);
		creator.CreatePolyline2D (polyline);
	}

}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Sector& sector, Boundary cutBoundaries) const -> GS::Array<Sector>
{
	GS::Array<Sector> results;
	polygon->ElemPolyDifference (sector, cutBoundaries, results);
	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const GenArc& genArc, Boundary cutBoundaries) const -> GS::Array<GenArc>
{
	GS::Array<GenArc> results;
	polygon->ElemPolyDifference (genArc, cutBoundaries, results);
	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Point2D& coord, Boundary cutBoundaries) const -> GS::Array<Point2D>
{
	GS::Array<Point2D> results;
	polygon->ElemPolyDifference (coord, cutBoundaries, results);
	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const BezierDetails& bezier, Boundary cutBoundaries) const -> GS::Array<BezierDetails>
{
	GS::Array<BezierDetails> results;
	polygon->ElemPolyDifference (bezier, cutBoundaries, results);
	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const CustomIrregularPolygon2D& poly,
																													  Boundary cutBoundaries) const -> MultiIrregularPolygon2DType
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	polygon->ElemPolyDifference (poly.polygon, cutBoundaries, polygonArray);
	return CustomIrregularPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Polyline2DType& poly, Boundary cutBoundaries) const -> MultiPolyline2DType
{
	MultiPolyline2DType results;
	GS::ArrayFB<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >, 4 > polylineArray;
	polygon->ElemPolyDifference (poly.polyline, cutBoundaries, polylineArray);
	for (typename GS::ArrayFB<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>, 4>::Iterator lineIter = polylineArray.Enumerate (); lineIter != nullptr; ++lineIter) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> tmpPolyline;
		tmpPolyline.polyline = *lineIter;
		results.Push (tmpPolyline);
	}

	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Array<Sector>	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDiffBorderOnly (const Sector& sector) const
{
	GS::Array<Sector> res;
	polygon->ElemPolyDiffBorderOnly (sector, res);
	return res;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Array<GenArc>	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDiffBorderOnly (const GenArc& arc) const
{
	GS::Array<GenArc> res;
	polygon->ElemPolyDiffBorderOnly (arc, res);
	return res;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const Sector& sector, Boundary cutBoundaries) const
{
	return polygon->ElemXPolygon (sector, cutBoundaries);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const GenArc& genArc, Boundary cutBoundaries) const
{
	return polygon->ElemXPolygon (genArc, cutBoundaries);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const Point2D& coord, Boundary cutBoundaries) const
{
	return polygon->ElemXPolygon (coord, cutBoundaries);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const BezierDetails& bezier, Boundary cutBoundaries) const
{
	return polygon->ElemXPolygon (bezier, cutBoundaries);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const CustomIrregularPolygon2D& poly, Boundary cutBoundaries, bool& touching) const
{
	return polygon->ElemXPolygon (poly.polygon, cutBoundaries, touching);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const Polyline2DType& poly, Boundary cutBoundaries) const
{
	return polygon->ElemXPolygon (poly.polyline, cutBoundaries);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CreateCommonEdgeSections (CustomIrregularPolygon2D& poly1, CustomIrregularPolygon2D& poly2)
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>,4> result;
	bool changed = CorePolygon2DType::CreateCommonEdgeSections (*poly1.polygon, *poly2.polygon, false, result);
	if (changed && DBVERIFY (result.GetSize () == 2)) {
		poly1.polygon = result [0];
		poly2.polygon = result [1];
	}
	return changed;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertCommonXLineOnPolygon (double x, const EdgeSplitControl& cntrl)
{
	bool changed;
	polygon->InsertCommonXLineOnPolygon (x, changed, cntrl);
	return changed;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertCommonYLineOnPolygon (double y, const EdgeSplitControl& cntrl)
{
	bool changed;
	polygon->InsertCommonYLineOnPolygon (y, changed, cntrl);
	return changed;
}


// Debug
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Dump3DGDL (Geometry::Plane * thePlane /*= nullptr*/, GS::OChannel& oc /*= dbChannel*/) const
{
	polygon->Dump3DGDL (thePlane, oc); 
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Print	(GS::OChannel& oc) const
{
	return polygon->Print (oc);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PrintDebug () const
{
	return polygon->PrintDebug ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PrintDebugXML () const
{
	return polygon->PrintDebugXML ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Check (PolyCheckFlags checkFlags, double coordUpperRange) const
{
	return polygon->Check (checkFlags, nullptr, coordUpperRange);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PolyRepairResult	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CheckAndRepair (PolyCheckFlags checkFlags, double coordUpperRange)
{
	PolyCheckFlags errorType;
	PolyRepairResult result;
	result.succeeded = true;
	result.modified = false;

	while (!polygon->Check (checkFlags, &errorType, coordUpperRange)) {
		if ((errorType & checkFlags) == 0) {
			result.succeeded = false;
			return result;
		} else {
			CopyOnWrite ();
			PolyRepairResult resultTemp = polygon->Repair (errorType);
			result.modified = (result.modified || resultTemp.modified);
			if (!resultTemp.succeeded) {
				result.succeeded = false;
				return result;
			}
		}
	}

	return result;
}


//********************************************************************************************************
//************************************** CustomMultiIrregularPolygon2D ***********************************
//********************************************************************************************************
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomMultiIrregularPolygon2D (std::initializer_list<PolyType> items) :
	GS::ArrayFB<PolyType, 4> (items)
{
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomMultiIrregularPolygon2D (const CustomMultiPolygon2DType& polys)
{
	for (typename CustomMultiPolygon2DType::ConstIterator it2 = polys.Enumerate (); it2 != nullptr; ++it2)
		this->Push (PolyType (*it2));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::~CustomMultiIrregularPolygon2D ()
{
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator= (const CustomMultiIrregularPolygon2D& other) -> CustomMultiIrregularPolygon2D&
{
	return static_cast<CustomMultiIrregularPolygon2D&> (GS::ArrayFB<PolyType, 4>::operator= (other));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Unify (PolyHoleHandling holeHandling /*= ReturnHoles*/)
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> corePolygonArray;
	GetCorePolygon2DArray (corePolygonArray);
	this->Clear (true);
	CorePolygon2DType::Unify (corePolygonArray, holeHandling);
	PushCorePolygon2DArray (corePolygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentUp (const ArcDivParams& arcDivParams)
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> corePolygonArray;
	GetCorePolygon2DArray (corePolygonArray);
	this->Clear (true);
	GS::SharedPtr<CorePolygon2DType> firstParam;
	for (UIndex polyIdx = 0; polyIdx < corePolygonArray.GetSize (); polyIdx++) {
		GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4 > result;
		typename CorePolygon2DType::PolygonResult polyResult = corePolygonArray[polyIdx]->SegmentUp (arcDivParams, result);
		PushResults (polyResult, corePolygonArray[polyIdx], firstParam, result);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran)
{
	bool isPreserveArc = Geometry::TMIsPreserveArc (tran);
	if (isPreserveArc) {
		for (UIndex idx = 0; idx < this->GetSize(); idx++) {
			this->Get(idx).TransformPreserveArcs (tran);
		}
	} else {
		GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> corePolygonArray;
		GetCorePolygon2DArray (corePolygonArray);
		this->Clear ();
		GS::SharedPtr<CorePolygon2DType> firstParam;
		for (UIndex polyIdx = 0; polyIdx < corePolygonArray.GetSize (); polyIdx++) {
			GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> result;
			typename CorePolygon2DType::PolygonResult polyResult = corePolygonArray[polyIdx]->Transform (arcDivParams, tran, result);
			PushResults (polyResult, corePolygonArray[polyIdx], firstParam, result);
		}
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Read (GS::IChannel& ic)
{
	NULL_REF_CHECK (ic);

	this->Clear ();

	GS::InputFrame frame (ic, MultiIrregularPolygon2DPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize = 0;
	GSErrCode errorCode = ic.Read (newSize);
	if (errorCode == NoError)
		this->SetSize (newSize);

	for (UIndex i = 0; i < newSize && errorCode == NoError; i++)
		errorCode = this->Get (i).Read (ic);

	return errorCode;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Write (GS::OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, MultiIrregularPolygon2DPrivate::classInfo);

	GSErrCode errorCode = oc.Write (this->GetSize ());

	for (UIndex i = 0; i < this->GetSize () && errorCode == NoError; i++)
		errorCode = this->Get (i).Write (oc);

	return errorCode;
}


extern	GEOMETRY_DLL_EXPORT const char*		XMLMultiIrregular_Tag_MultiPolygon2D;
extern	GEOMETRY_DLL_EXPORT const char*		XMLMultiIrregular_Attr_PolyNum;

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadXML	(GS::XMLIChannel& ic)
{
	GSErrCode errCode = NoError;
	GS::XMLITag tagMultiPolygon2D (ic, XMLMultiIrregular_Tag_MultiPolygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		GS::ClassVersion currentClassVersion;
		ic.ReadXMLVersionAttr (currentClassVersion);
		//currentClassVersion.ReadXML (ic);
		DBASSERT (currentClassVersion == MultiIrregularPolygon2DPrivate::classInfo.GetVersion ());
	}

	USize newSize = 0;
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLMultiIrregular_Attr_PolyNum, newSize);

	GS::UniString tokenName;
	while (tagMultiPolygon2D.IsNextChildStartTag (tokenName) && (errCode == NoError)) {
		PolyType newPoly;
		errCode = newPoly.ReadXML (ic);
		this->Push (newPoly);
	}

	DBASSERT (newSize == this->GetSize ());

	if (errCode != NoError)
		return errCode;
	return ic.GetErrorStatus () == GS::XMLIChannel::Ok ? NoError : Error;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteXML (GS::XMLOChannel& oc) const
{
	GSErrCode errCode = NoError;
	GS::XMLTag tagMultiPolygon2D (oc, XMLMultiIrregular_Tag_MultiPolygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		oc.WriteXMLVersionAttr (MultiIrregularPolygon2DPrivate::classInfo.GetVersion ());
		//GetClassVersion ().WriteXML (oc);
	}

	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLMultiIrregular_Attr_PolyNum, this->GetSize ());

	for (UIndex idx = 0; idx < this->GetSize() && errCode == NoError; idx++) {
		errCode = this->Get (idx).WriteXML (oc);
	}

	if (errCode != NoError)
		return errCode;
	return oc.GetErrorStatus () == GS::XMLOChannel::Ok ? NoError : Error;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
Box2DData	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetBoundBox () const
{
	Box2DData box;
	if (this->GetSize () == 0) {
		DBBREAK (); 
		return box;
	}
	else if (this->GetSize () == 1)
		return this->Get (0).GetBoundBox ();

	box = this->Get (0).GetBoundBox ();
	for (UIndex idx = 1; idx < this->GetSize(); idx++) {
		const Box2DData& elemBox = this->Get (idx).GetBoundBox ();
		UnionBox (&elemBox, &box);
	}
	return box;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcSignedArea () const 
{
	double area = 0.0;

	for (UIndex idx = 0; idx < this->GetSize (); idx++) {
		area += this->Get (idx).CalcSignedArea ();
	}
	return area;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Point2D& point, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>,4 > polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, point, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Sector& sect, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, sect, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GenArc& arc, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, arc, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Box2DData& box, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, box, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const PolyType& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, *poly.polygon, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Polyline2DType& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2DType>, 4> polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, *poly.polyline, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Substract (const CustomMultiIrregularPolygon2D& poly1,
																												  const CustomMultiIrregularPolygon2D& poly2,
																												  bool* changed /*= nullptr*/) -> CustomMultiIrregularPolygon2D
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> poly1CorePolygonArray;
	poly1.GetCorePolygon2DArray (poly1CorePolygonArray);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> poly2CorePolygonArray;
	poly2.GetCorePolygon2DArray (poly2CorePolygonArray);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> resultCorePolygonArray = CorePolygon2DType::Substract (poly1CorePolygonArray,
																									   poly2CorePolygonArray,
																									   changed);

	CustomMultiIrregularPolygon2D result;
	result.PushCorePolygon2DArray (resultCorePolygonArray);
	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Intersect (const CustomMultiIrregularPolygon2D& poly1,
																												  const CustomMultiIrregularPolygon2D& poly2) -> CustomMultiIrregularPolygon2D
{
	CustomMultiIrregularPolygon2D result;

	for (GS::UInt32 i = 0; i < poly2.GetSize (); i++) {
		GS::UInt32	oldSize = poly1.GetSize ();
		for (GS::UInt32 j = 0; j < oldSize; j++) {
			CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>		result1;
			RelativePosition	relativePosition;
			result1 = poly1[j].Intersect (poly2[i], Boundary_Closed, &relativePosition);
			result.Insert (result.GetSize (), result1.Begin ());
		}
	}

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetCorePolygon2DArray (GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray) const
{
	for (UIndex idx = 0; idx < this->GetSize (); idx++) {
		polygonArray.Push (this->Get (idx).polygon);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PushCorePolygon2DArray (const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray)
{
	for (UIndex idx = 0; idx < polygonArray.GetSize (); idx++) {
		PolyType poly2D;
		poly2D.polygon = polygonArray[idx];
		this->Push (poly2D);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PushResults (typename CorePolygon2DType::PolygonResult polyResult, 
																													const GS::SharedPtr<CorePolygon2DType>& thisPoly, 
																													const GS::SharedPtr<CorePolygon2DType>& firstParam,
																													const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray)
{
	switch (polyResult) {
		case CorePolygon2DType::NewPolygons:
			PushCorePolygon2DArray (polygonArray);
			break;
		case CorePolygon2DType::ResultSameAsThis:
			{
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
				GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (*thisPoly);
				this->Push (newPolygon);
#else
				this->Push (thisPoly);
#endif
			}
			break;
		case CorePolygon2DType::ResultSameAsFirstParameter:
			{
				DBASSERT (firstParam != nullptr);
				if (firstParam != nullptr) {
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
					GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (*firstParam);
					this->Push (newPolygon);
#else
					this->Push (firstParam);
#endif
				}
			}
			break;
		case CorePolygon2DType::ResultThisAndParameter:
			{
				DBASSERT (firstParam != nullptr);
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
				GS::SharedPtr<CorePolygon2DType> newPolygon1 = new CorePolygon2DType (*thisPoly);
				Push (newPolygon1);
				if (firstParam != nullptr) {
					GS::SharedPtr<CorePolygon2DType> newPolygon2 = new CorePolygon2DType (*firstParam);
					this->Push (newPolygon2);
				}
#else
				this->Push (thisPoly);
				if (firstParam != nullptr) {
					this->Push (firstParam);
				}
#endif
			}
			break;
		case CorePolygon2DType::EmptyPolygon:
			break;
		default:
			DBBREAK ();
			break;
	}
}

}		// namespace Geometry

#endif		/* GEOMETRY_IRREGULARPOLYGON2D_HPP_ */
