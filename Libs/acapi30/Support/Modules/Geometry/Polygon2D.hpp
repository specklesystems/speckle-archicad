// *****************************************************************************
//
// Declaration of Polygon2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA, RJ
//
// *****************************************************************************

#ifndef GEOMETRY_POLYGON2D_HPP
#define GEOMETRY_POLYGON2D_HPP

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes ----------------------------------------------------------------
#include "Polygon2DClassDefinition.hpp"

#include "Polyline2DClassDefinition.hpp"
#include "ConvexHull2DCreator.h"

#include <float.h>

namespace Geometry {

#if defined (DEBUVERS)
#define DEBUVERS_POLY2D
#endif

#if defined(DEBUVERS_POLY2D)
#define DBCHECKPOLYGONINDEX(idx, minIdx, maxIdx) DBASSERT ((idx) >= (minIdx) && (idx) <= (maxIdx))
#else
#define DBCHECKPOLYGONINDEX(idx, minIdx, maxIdx)
#endif

//*******************************************************
// CustomPolygon2D::Contour class
//*******************************************************
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const ContourUserData&	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetPolyContourUserData () const
{
	return poly->GetContourUserDataByIdx (index);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetVertexNum () const
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	return to - from;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetVertexIterator (UIndex vertexIdx) const -> ConstVertexIterator
{
	if (poly == nullptr) {
		DBBREAK ();
		throw GeometryLogicErrorException ("Invalid polygon in CustomPolygon2D::Contour::GetVertexIterator!", __FILE__, __LINE__);
	}
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	DBCHECKPOLYGONINDEX(vertexIdx, poly->polygon->GetVertexBeginIdxInContour (index), poly->polygon->GetVertexEndIdxInContour (index));

	ConstPolyVertexInPolyState<CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>, VertexUserData> item (poly, from, to, vertexIdx);
	return CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EnumerateVertex () const -> ConstVertexIterator
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetVertexIterator (from);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::BeginVertex () const -> ConstVertexIterator
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetVertexIterator (from);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EndVertex	() const -> ConstVertexIterator
{
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	return GetVertexIterator (to);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetEdgeNum () const
{
	UIndex from = poly->polygon->GetEdgeBeginIdxInContour (index);
	UIndex to = poly->polygon->GetEdgeEndIdxInContour (index);
	return to - from;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetEdgeIterator (UIndex edgeIdx) const -> ConstEdgeIterator
{
	if (poly == nullptr) {
		DBBREAK ();
		throw GeometryLogicErrorException ("Invalid polygon in CustomPolygon2D::Contour::GetEdgeIterator!!", __FILE__, __LINE__);
	}
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	DBCHECKPOLYGONINDEX(edgeIdx, poly->polygon->GetVertexBeginIdxInContour (index), poly->polygon->GetVertexEndIdxInContour (index));

	ConstPolyEdgeInPolyState<CustomPolygon2D, EdgeUserData> item (poly, from, to, edgeIdx);
	return CustomPolygon2D::ConstEdgeIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EnumerateEdge () const -> ConstEdgeIterator
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetEdgeIterator (from);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::BeginEdge () const -> ConstEdgeIterator
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetEdgeIterator (from);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EndEdge () const -> ConstEdgeIterator
{
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	return GetEdgeIterator (to);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetBeginVertex (const ConstEdgeIterator& edgeIterator) const -> ConstVertexIterator
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == poly->polygon);
	return GetVertexIterator (poly->polygon->GetBeginVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetEndVertex (const ConstEdgeIterator& edgeIterator) const -> ConstVertexIterator
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == poly->polygon);
	return GetVertexIterator (poly->polygon->GetEndVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetNextEdge (const ConstVertexIterator& vertexIterator) const -> ConstEdgeIterator
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == poly->polygon);
	return GetEdgeIterator (poly->polygon->GetNextEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetPrevEdge (const ConstVertexIterator& vertexIterator) const -> ConstEdgeIterator
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == poly->polygon);
	return GetEdgeIterator (poly->polygon->GetPrevEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}


//*******************************************************
// CustomPolygon2D class
//*******************************************************
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (GS::SharedPtr<CorePolygon2DType> polygon2D) : polygon (polygon2D)
{
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray) -> MultiPolygon2DType
{
	MultiPolygon2DType result;
	if (polygonArray.GetSize() == 0) {
		return result;
	}

	UIndex idx;
	for(idx = 0; idx < polygonArray.GetSize(); idx++) {
		if (polygonArray[idx]->IsEmpty ()) {
			DBBREAK ();
			continue;
		}
		if (!polygonArray[idx]->status.isRegularized) {
			DBBREAK ();
			GS::Array<GS::SharedPtr<CorePolygon2DType>> regularizedPolygons;
			typename CorePolygon2DType::PolygonResult polyResult = polygonArray[idx]->Regularize (regularizedPolygons);
			switch (polyResult) {
			case CorePolygon2DType::NewPolygons:
				for(UIndex polyIdx = 0; polyIdx < regularizedPolygons.GetSize(); polyIdx++) {
					if (!regularizedPolygons [polyIdx]->status.isRegularized || regularizedPolygons [polyIdx]->IsEmpty ()) {
						DBBREAK ();
						continue;
					}
					CustomPolygon2D tmpPolygon (regularizedPolygons [polyIdx]);
					result.Push (tmpPolygon);
				}
				break;
			case CorePolygon2DType::ResultSameAsThis:
				{
					CustomPolygon2D tmpPolygon (polygonArray[idx]);
					result.Push (tmpPolygon);
				}
				break;
			case CorePolygon2DType::ResultSameAsFirstParameter:
				DBBREAK ();
				break;
			case CorePolygon2DType::ResultThisAndParameter:
				DBBREAK ();
				break;
			case CorePolygon2DType::EmptyPolygon:
				break;
			default:
				DBBREAK ();
				break;
			}
		} else {
			CustomPolygon2D tmpPolygon (polygonArray[idx]);
			result.Push (tmpPolygon);
		}
	}

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Regularize (const IrregularPolygon2DType&	irregularPolygon2D, 
																									 PolyRegularizationMode mode /*= PolyRegularizationMode_Default*/) -> MultiPolygon2DType
{
	MultiPolygon2DType result;
	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = irregularPolygon2D.polygon->Regularize (polygonArray, mode);
	if (polyResult == CorePolygon2DType::ResultSameAsThis) {
		CustomPolygon2D polygon (irregularPolygon2D.polygon);
		result.Push (polygon);
	} else if (polyResult == CorePolygon2DType::EmptyPolygon) {
	} else {
		result = CustomPolygon2D::Create (polygonArray);
	}

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CreateResult (typename CorePolygon2DType::PolygonResult polyResult, 
																									   const CustomPolygon2D * firstParam, 
																									   const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray) const -> MultiPolygon2DType
{
	MultiPolygon2DType result;
	DBASSERT (polygon->status.isRegularized);
	switch (polyResult) {
		case CorePolygon2DType::NewPolygons:
			result = CustomPolygon2D::Create (polygonArray);
			break;
		case CorePolygon2DType::ResultSameAsThis:
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			{
				GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (*polygon);
				result.Push (newPolygon);
			}
#else
			result.Push (polygon);
#endif
			break;
		case CorePolygon2DType::ResultSameAsFirstParameter:
			DBASSERT (firstParam != nullptr);
			if (firstParam != nullptr && firstParam->polygon->status.isRegularized && !firstParam->polygon->IsEmpty ()) {
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
				GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (*(firstParam->polygon));
				result.Push (newPolygon);
#else
				result.Push (firstParam->polygon);
#endif
			}
			break;
		case CorePolygon2DType::ResultThisAndParameter:
			DBASSERT (firstParam != nullptr);
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			{
				if (polygon->status.isRegularized && !polygon->IsEmpty ()) {
					GS::SharedPtr<CorePolygon2DType> newPolygon1 = new CorePolygon2DType (*polygon);
					result.Push (newPolygon1);
				}
				if (firstParam != nullptr && firstParam->polygon->status.isRegularized && !firstParam->polygon->IsEmpty ()) {
					GS::SharedPtr<CorePolygon2DType> newPolygon2 = new CorePolygon2DType (*(firstParam->polygon));
					result.Push (newPolygon2);
				}
			}
#else
			if (polygon->status.isRegularized && !polygon->IsEmpty ())
				result.Push (polygon);
			if (firstParam != nullptr && firstParam->polygon->status.isRegularized && !firstParam->polygon->IsEmpty ())
				result.Push (firstParam->polygon);
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
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetResult (typename CorePolygon2DType::PolygonResult polyResult, const GS::SharedPtr<CorePolygon2DType>& newPoly)
{
	DBASSERT (polygon->status.isRegularized);
	switch (polyResult) {
		case CorePolygon2DType::NewPolygons:
			polygon = newPoly;
			break;
		case CorePolygon2DType::ResultSameAsThis:
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			{
				GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (*polygon);
				polygon = newPolygon;
			}
#endif
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
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyOnWrite ()
{
	DBASSERT (polygon->status.isRegularized);
	if (polygon == nullptr)
		throw GeometryIllegalArgumentException ("Polygon can't be nullptr!!!", __FILE__, __LINE__);
	if (polygon->GetRefCount() > 1)
		polygon = new CorePolygon2DType (*polygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetFlags (GS::UInt32 polyFlags /*PolyFlags*/) -> typename CorePolygon2DType::Flags
{
	typename CorePolygon2DType::Flags flags;
	CheckPolyFlags (polyFlags);

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
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D ()
{
	typename CorePolygon2DType::Flags flags;
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
	polygon = new CorePolygon2DType (flags);
#else
	polygon = new CorePolygon2DType (flags);
#endif
	DBASSERT (polygon->status.isRegularized);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (const CustomPolygon2D& source)
{
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
	polygon = new CorePolygon2DType (*source.polygon);
#else
	polygon = source.polygon;
#endif
	DBASSERT (polygon->status.isRegularized);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (const Box2DData& box)
{
	typename CorePolygon2DType::Flags flags;
	polygon = new CorePolygon2DType (flags, box);
	if (!polygon->status.isRegularized) {
		polygon = new CorePolygon2DType (flags);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (const Circle2D& circ)
{
	typename CorePolygon2DType::Flags flags;
	polygon = new CorePolygon2DType (flags, circ);
	if (!polygon->status.isRegularized) {
		polygon = new CorePolygon2DType (flags);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (const Ellipse& ell, ArcDivParams arcDivParams)
{
	typename CorePolygon2DType::Flags flags;
	polygon = new CorePolygon2DType (flags, ell, arcDivParams);
	if (!polygon->status.isRegularized) {
		polygon = new CorePolygon2DType (flags);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (GS::UInt32 flags /*PolyFlags*/)
{
	polygon = new CorePolygon2DType (GetFlags (flags));
	DBASSERT (polygon->status.isRegularized);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (GS::UInt32 flags /*PolyFlags*/, const Box2DData& box)
{
	polygon = new CorePolygon2DType (GetFlags (flags), box);
	if (!polygon->status.isRegularized) {
		polygon = new CorePolygon2DType (GetFlags (flags));
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::~CustomPolygon2D ()
{
	DBASSERT (polygon == nullptr || polygon->status.isRegularized);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const ContourDescriptionArray& contourDescrArray) -> MultiPolygon2DType
{
	MultiPolygon2DType result;

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::Flags flags;
	CorePolygon2DType::Create (flags, contourDescrArray, polygonArray);
	result = CustomPolygon2D::Create (polygonArray);

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline) -> MultiPolygon2DType
{
	MultiPolygon2DType result;

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	CorePolygon2DType::Create (*polyline.polyline, polygonArray);
	result = CustomPolygon2D::Create (polygonArray);

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const IrregularPolygon2DType& irregularPolygon2D) -> MultiPolygon2DType
{
	if (irregularPolygon2D.polygon->status.isRegularized) {
		MultiPolygon2DType result;
		if (!irregularPolygon2D.polygon->IsEmpty ()) {
			CustomPolygon2D emptyPoly (irregularPolygon2D.polygon);
			result.Push (emptyPoly);
		}
		return result;
	}

	return Regularize (irregularPolygon2D);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const ContourDescriptionArray& contourDescrArray) -> MultiPolygon2DType
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	CorePolygon2DType::Create (GetFlags (flags), contourDescrArray, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const Point2D* coords, USize nValuableCoords, GS::UInt32 createFlags) -> MultiPolygon2DType
{
	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		typename CorePolygon2DType::Flags flags;
		CorePolygon2DType::Create (flags, coords, nValuableCoords, nullptr /*arcs*/, 0 /*nValuableArcs*/, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																								 const Point2D* coords, 
																								 USize nValuableCoords, 
																								 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolygon2DType
{
	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		CorePolygon2DType::Create (GetFlags (flags), coords, nValuableCoords, nullptr /*arcs*/, 0 /*nValuableArcs*/, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const Point2D* coords, 
																								 USize nValuableCoords, 
																								 const PolyArcRec* arcs, 
																								 USize nArcs, 
																								 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolygon2DType
{
	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		typename CorePolygon2DType::Flags flags;
		CorePolygon2DType::Create (flags, coords, nValuableCoords, arcs, nArcs, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																								 const Point2D* coords, 
																								 USize nValuableCoords, 
																								 const PolyArcRec* arcs, 
																								 USize nArcs, 
																								 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolygon2DType
{
	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		CorePolygon2DType::Create (GetFlags (flags), coords, nValuableCoords, arcs, nArcs, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const Point2D* coords, 
																								 USize nValuableCoords, 
																								 const PolyArcRec* arcs, 
																								 USize nValuableArcs, 
																								 const UIndex* contourEnds, 
																								 USize nContours, 
																								 GS::UInt32 createFlags /*PolyCreateFlags*/) ->MultiPolygon2DType
{
	DBASSERT ((nValuableCoords == 0 && nContours == 0) || (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr));

	if (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		typename CorePolygon2DType::Flags flags;
		CorePolygon2DType::Create (flags, coords, nValuableCoords, arcs, nValuableArcs, contourEnds, nContours, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																								 const Point2D* coords, 
																								 USize nValuableCoords, 
																								 const PolyArcRec* arcs, 
																								 USize nValuableArcs, 
																								 const UIndex* contourEnds, 
																								 USize nContours, 
																								 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolygon2DType
{
	DBASSERT ((nValuableCoords == 0 && nContours == 0) || (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr));

	if (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		CorePolygon2DType::Create (GetFlags (flags), coords, nValuableCoords, arcs, nValuableArcs, contourEnds, nContours, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<Point2D>& coordList, 
																								 const GS::Array<PolyArcRec>& arcList, 
																								 const GS::Array<UIndex>& contourEndList, 
																								 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolygon2DType
{
	DBASSERT ((coordList.IsEmpty () && contourEndList.IsEmpty ()) || (!coordList.IsEmpty () && !contourEndList.IsEmpty ()));

	if (!coordList.IsEmpty () && !contourEndList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		typename CorePolygon2DType::Flags flags;
		CorePolygon2DType::Create (flags, coordList, arcList, contourEndList, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																								 const GS::Array<Point2D>& coordList, 
																								 const GS::Array<PolyArcRec>& arcList, 
																								 const GS::Array<UIndex>& contourEndList, 
																								 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolygon2DType
{
	DBASSERT ((coordList.IsEmpty () && contourEndList.IsEmpty ()) || (!coordList.IsEmpty () && !contourEndList.IsEmpty ()));

	if (!coordList.IsEmpty () && !contourEndList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		CorePolygon2DType::Create (GetFlags (flags), coordList, arcList, contourEndList, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<Point2D>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolygon2DType
{
	if (!coordList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		GS::Array<PolyArcRec> arcList;
		GS::Array<UIndex> contourEndList;
		typename CorePolygon2DType::Flags flags;
		CorePolygon2DType::Create (flags, coordList, arcList, contourEndList, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																								 const GS::Array<Point2D>& coordList,
																								 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolygon2DType
{
	if (!coordList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		GS::Array<PolyArcRec> arcList;
		GS::Array<UIndex> contourEndList;
		CorePolygon2DType::Create (GetFlags (flags), coordList, arcList, contourEndList, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<Point2D>& coordList, 
																								 const GS::Array<PolyArcRec>& arcList, 
																								 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolygon2DType
{
	if (!coordList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		GS::Array<UIndex> contourEndList;
		typename CorePolygon2DType::Flags flags;
		CorePolygon2DType::Create (flags, coordList, arcList, contourEndList, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																								 const GS::Array<Point2D>& coordList, 
																								 const GS::Array<PolyArcRec>& arcList, 
																								 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolygon2DType
{
	MultiPolygon2DType result;

	if (!coordList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
		GS::Array<UIndex> contourEndList;
		CorePolygon2DType::Create (GetFlags (flags), coordList, arcList, contourEndList, createFlags, polygonArray);
		return CustomPolygon2D::Create (polygonArray);
	}

	return MultiPolygon2DType ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConvertToContourDescriptionArray () const -> ContourDescriptionArray
{
	ContourDescriptionArray contourDescrArray;
	DBASSERT (polygon->status.isRegularized);
	polygon->Convert (contourDescrArray);
	return contourDescrArray;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConvertToPolylines () const -> MultiPolyline2DType
{
	return Polyline2DType::template Create<ContourUserData> (*this);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConvertToPolyline (ConstContourIterator contourIterator) const -> Polyline2DType
{
	return Polyline2DType::Create (*this, contourIterator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
template <class VertexUserDataSrc, class EdgeUserDataSrc, class ContourUserDataSrc, class PolygonUserDataSrc>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConvertFromPolygon2D (
	const CustomPolygon2D<VertexUserDataSrc, EdgeUserDataSrc, ContourUserDataSrc, PolygonUserDataSrc>& fromPolygon,
	Poly2DUserDataConverter<VertexUserDataSrc, EdgeUserDataSrc, ContourUserDataSrc, PolygonUserDataSrc,
	VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>* converter /*= nullptr*/) -> CustomPolygon2D
{
	DBASSERT (fromPolygon.polygon->status.isRegularized);
	CustomPolygon2D result;
	CorePolygon2D<VertexUserDataSrc, EdgeUserDataSrc, ContourUserDataSrc, PolygonUserDataSrc>::ConvertFromCorePolygon2D (*result.polygon, *fromPolygon.polygon, converter);
	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonData (Point2D* coords, USize& nValuableCoords, 
																										  PolyArcRec* arcs, USize& nValuableArcs, 
																										  UIndex* contourEnds, USize& nContours, 
																										  const GS::Array<ConstContourIterator>& reversedContours, 
																										  GS::UInt32 createFlags /*PolyCreateFlags*/) const
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<UIndex> reversedContourIndices;
	for (typename GS::Array <ConstContourIterator>::ConstIterator contourIter = reversedContours.Enumerate (); contourIter != nullptr; ++contourIter) {
		reversedContourIndices.Push (contourIter->GetItem ().GetIndex ());
	}
	polygon->CopyPolygonData (coords, nValuableCoords, arcs, nValuableArcs, contourEnds, nContours, reversedContourIndices, createFlags);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonData (GS::Array<Point2D>& coords, 
																									   GS::Array<PolyArcRec>& arcs, 
																									   GS::Array<UIndex>& contourEnds, 
																									   const GS::Array<ConstContourIterator>& reversedContours, 
																									   GS::UInt32 createFlags /*PolyCreateFlags*/) const
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<UIndex> reversedContourIndices;
	for (typename GS::Array <ConstContourIterator>::ConstIterator contourIter = reversedContours.Enumerate (); contourIter != nullptr; ++contourIter) {
		reversedContourIndices.Push (contourIter->GetItem ().GetIndex ());
	}
	polygon->CopyPolygonData (coords, arcs, contourEnds, reversedContourIndices, createFlags);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AllocateAndCopyPolygonData (Point2D** coords, USize& nValuableCoords, 
																													 PolyArcRec** arcs, USize& nValuableArcs, 
																													 UIndex** contourEnds, USize& nContours, 
																													 GS::UInt32 createFlags /*PolyCreateFlags*/) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (coords != nullptr && contourEnds != nullptr && (polygon->nArcs == 0 || arcs != nullptr));

	if (coords == nullptr || contourEnds == nullptr || (polygon->nArcs > 0 && arcs == nullptr))
		throw GeometryIllegalArgumentException ("Error in CustomPolygon2D::AllocateAndCopyPolygonData!!!", __FILE__, __LINE__);

	GS::Array<UIndex> reversedContourIndices;

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
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator= (const CustomPolygon2D& source) -> CustomPolygon2D&
{
	if (this == &source)
		return *this;

	DBASSERT (source.polygon->status.isRegularized);
	if (polygon != source.polygon)
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
		polygon = new CorePolygon2DType (*source.polygon);
#else
		polygon = source.polygon;
#endif
	return *this;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator== (const CustomPolygon2D& rightOp) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->Compare (*rightOp.polygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator!= (const CustomPolygon2D& rightOp) const
{
	return !operator== (rightOp);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetSameDirEdgeLegal (bool isSameDirEdgeLegal)
{
	DBASSERT (polygon->status.isRegularized);
	if (polygon->flags.isSameDirEdgeLegal != isSameDirEdgeLegal) {
		CopyOnWrite ();
		GS::Array<GS::SharedPtr<CorePolygon2DType>> result;
		typename CorePolygon2DType::PolygonResult polyResult = polygon->SetSameDirEdgeLegalAndRegularize (isSameDirEdgeLegal, result);
		switch (polyResult) {
		case CorePolygon2DType::NewPolygons:
			DBASSERT (result.GetSize () == 1);
			polygon = result[0];
			break;
		case CorePolygon2DType::ResultSameAsThis:
			break;
		case CorePolygon2DType::ResultSameAsFirstParameter:
		case CorePolygon2DType::ResultThisAndParameter:
		case CorePolygon2DType::EmptyPolygon:
		default:
			DBBREAK ();
			break;
		}
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetForce64BitPrecision (bool force64BitPrecision)
{
	DBASSERT (polygon->status.isRegularized);
	if (polygon->flags.force64BitPrecision != force64BitPrecision) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> result;
		typename CorePolygon2DType::PolygonResult polyResult = polygon->SetForce64BitPrecision (force64BitPrecision, result);
		switch (polyResult) {
		case CorePolygon2DType::NewPolygons:
			DBASSERT (result.GetSize () == 1);
			polygon = result[0];
			break;
		case CorePolygon2DType::ResultSameAsThis:
			break;
		case CorePolygon2DType::ResultSameAsFirstParameter:
		case CorePolygon2DType::ResultThisAndParameter:
		case CorePolygon2DType::EmptyPolygon:
		default:
			DBBREAK ();
			break;
		}
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSameDirEdgeLegal () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetSameDirEdgeLegal ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetForce64BitPrecision () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetForce64BitPrecision ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetPolyFlags (GS::UInt32 polyFlags /*PolyFlags*/)
{
	DBASSERT (polygon->status.isRegularized);
	CheckPolyFlags (polyFlags);
	DBASSERT (!((PolyFlags_Force64BitPrecision & polyFlags) && (PolyFlags_NoForce64BitPrecision & polyFlags)));

	if (PolyFlags_IsSameDirEdgeLegal & polyFlags && !polygon->flags.isSameDirEdgeLegal) {
		CopyOnWrite (); //Csak egyszer fog masolni
		SetSameDirEdgeLegal (true);
	}
	if (PolyFlags_NoSameDirEdgeLegal & polyFlags && polygon->flags.isSameDirEdgeLegal) {
		CopyOnWrite (); //Csak egyszer fog masolni
		SetSameDirEdgeLegal (false);
	}
	if (PolyFlags_Force64BitPrecision & polyFlags && !polygon->flags.force64BitPrecision) {
		CopyOnWrite (); //Csak egyszer fog masolni
		SetForce64BitPrecision (true);
	}
	if (PolyFlags_NoForce64BitPrecision & polyFlags && polygon->flags.force64BitPrecision) {
		CopyOnWrite (); //Csak egyszer fog masolni
		SetForce64BitPrecision (false);
	}
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
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CheckPolyFlags (GS::UInt32 polyFlags /*PolyFlags*/)
{
#ifdef DEBUVERS
	DBASSERT (!((PolyFlags_IsSameDirEdgeLegal & polyFlags) && (PolyFlags_NoSameDirEdgeLegal & polyFlags)));
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
GS::UInt32	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPolyFlags () const //PolyFlags
{
	DBASSERT (polygon->status.isRegularized);
	GS::UInt32 flags = 0;

	if (polygon->GetSameDirEdgeLegal ())
		flags |= PolyFlags_IsSameDirEdgeLegal;
	else 
		flags |= PolyFlags_NoSameDirEdgeLegal;

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
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexIterator (UIndex vertexIdx) const -> ConstVertexIterator
{
	DBASSERT (polygon->status.isRegularized);
	DBCHECKPOLYGONINDEX(vertexIdx, 1, polygon->GetVertexNum () + 1);

	ConstPolyVertexInPolyState<CustomPolygon2D, VertexUserData> item (this, vertexIdx);
	return CustomPolygon2D::ConstVertexIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexIterator (const Point2D& coord) const -> ConstVertexIterator
{
	DBASSERT (polygon->status.isRegularized);
	return GetVertexIterator(polygon->GetVertexIdx(coord));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateVertex () const -> ConstVertexIterator
{
	return GetVertexIterator(1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::BeginVertex () const -> ConstVertexIterator
{
	return GetVertexIterator (1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EndVertex	() const -> ConstVertexIterator
{
	DBASSERT (polygon->status.isRegularized);
	return GetVertexIterator (polygon->GetVertexNum() + 1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateVertex (const VertexUserData& id) const -> ConstVertexIterator
{
	ConstPolyVertexInPolyState<CustomPolygon2D, VertexUserData> item (this, id);
	return CustomPolygon2D::ConstVertexIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeIterator (UIndex edgeIdx) const -> ConstEdgeIterator
{
	DBASSERT (polygon->status.isRegularized);
	DBCHECKPOLYGONINDEX(edgeIdx, 1, polygon->GetEdgeNum () + 1);

	ConstPolyEdgeInPolyState<CustomPolygon2D, EdgeUserData> item (this, edgeIdx);
	return CustomPolygon2D::ConstEdgeIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateEdge () const -> ConstEdgeIterator
{
	return GetEdgeIterator (1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::BeginEdge () const -> ConstEdgeIterator
{
	return GetEdgeIterator (1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EndEdge () const -> ConstEdgeIterator
{
	DBASSERT (polygon->status.isRegularized);
	return GetEdgeIterator (polygon->GetEdgeNum() + 1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateEdge (const EdgeUserData& id) const -> ConstEdgeIterator
{
	ConstPolyEdgeInPolyState<CustomPolygon2D, EdgeUserData> item (this, id);
	return CustomPolygon2D::ConstEdgeIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourIterator (UIndex contourIdx) const -> ConstContourIterator
{
	DBASSERT (polygon->status.isRegularized);
	DBCHECKPOLYGONINDEX(contourIdx, 1, polygon->GetContourNum () + 1);

	Contour item (this, contourIdx);
	return CustomPolygon2D::ConstContourIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateContour () const -> ConstContourIterator
{
	return GetContourIterator(1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::BeginContour () const -> ConstContourIterator
{
	return GetContourIterator (1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EndContour	() const -> ConstContourIterator
{
	DBASSERT (polygon->status.isRegularized);
	return GetContourIterator (polygon->GetContourNum() + 1);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateContour (const ContourUserData& id) const -> ConstContourIterator
{
	Contour item (this, id);
	return CustomPolygon2D::ConstContourIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateHoleContour () const -> ConstContourIterator
{
	DBASSERT (polygon->status.isRegularized);
	Contour item (this, 2, polygon->GetContourNum() + 1, 2);
	return CustomPolygon2D::ConstContourIterator (item);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetPolyUserData (const PolygonUserData& polyId)
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->SetUserData (&polyId);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const PolygonUserData&	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPolyUserData () const
{
	DBASSERT (polygon->status.isRegularized);
	return *polygon->GetUserData ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetVertexDefaultUserData (const VertexUserData& userData)
{
	CopyOnWrite ();
	polygon->SetVertexDefaultUserData (userData);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResetUserData ()
{
	CopyOnWrite ();
	polygon->ResetUserData ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const VertexUserData&	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexDefaultUserData () const
{
	return polygon->GetVertexDefaultUserData ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexNum () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetVertexNum ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolyVertex<VertexUserData>	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertex (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	Vertex vertex;
	vertex.SetCoord (polygon->GetCoord (vertexIterator.GetItem ().GetIndex ()));
	vertex.SetPolyVertexUserData (*polygon->GetVertexUserData (vertexIterator.GetItem ().GetIndex ()));

	return vertex;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const Point2D&	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetCoord (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return polygon->GetCoord (vertexIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const VertexUserData&	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexUserData (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return *polygon->GetVertexUserData (vertexIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetVertexUserData (const ConstVertexIterator& vertexIterator, const VertexUserData& vertexId)
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	polygon->SetVertexUserData (vertexIterator.GetItem ().GetIndex (), &vertexId);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeDefaultUserData (const EdgeUserData& userData)
{
	CopyOnWrite ();
	polygon->SetEdgeDefaultUserData (userData);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const EdgeUserData&		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeDefaultUserData () const
{
	return polygon->GetEdgeDefaultUserData ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeNum () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetEdgeNum ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolyEdge<EdgeUserData>	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdge (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	Edge edge;
	edge.SetArcAngle(polygon->GetArcAngle (edgeIterator.GetItem ().GetIndex ()));
	edge.SetPolyEdgeUserData(*polygon->GetEdgeUserData (edgeIterator.GetItem ().GetIndex ()));

	return edge;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSector (const ConstEdgeIterator& edgeIterator, Sector& sect, GenArc& genArc) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return polygon->GetSector (edgeIterator.GetItem ().GetIndex (), sect, genArc);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSector (const ConstEdgeIterator& edgeIterator, Point2D& begC, Point2D& endC, double& angle) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return polygon->GetSector (edgeIterator.GetItem ().GetIndex (), begC, endC, angle);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Optional<Sector>	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSector (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return polygon->GetSector (edgeIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Optional<GenArc>	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetArc (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return polygon->GetArc (edgeIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const EdgeUserData&		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeUserData (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return *polygon->GetEdgeUserData (edgeIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeUserData (const ConstEdgeIterator& edgeIterator, const EdgeUserData& edgeId)
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	polygon->SetEdgeUserData (edgeIterator.GetItem ().GetIndex (), &edgeId);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetContourDefaultUserData (const ContourUserData& userData)
{
	CopyOnWrite ();
	polygon->SetContourDefaultUserData (userData);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const	ContourUserData& CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourDefaultUserData () const
{
	return polygon->GetContourDefaultUserData ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourNum () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetContourNum ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContour (const ConstContourIterator& contourIterator) const -> CustomPolygon2D
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	CustomPolygon2D contour;
	contour.polygon = new CorePolygon2DType (*polygon, contourIterator.GetItem ().GetIndex (), true /*keepRegularized*/);
	return contour;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const ContourUserData&	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourUserData (const ConstContourIterator& contourIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	return *polygon->GetContourUserData (contourIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetContourUserData (const ConstContourIterator& contourIterator, const ContourUserData& contourId)
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	polygon->SetContourUserData (contourIterator.GetItem ().GetIndex (), &contourId);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetBeginVertex (const ConstEdgeIterator& edgeIterator) const -> ConstVertexIterator
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return GetVertexIterator (polygon->GetBeginVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEndVertex (const ConstEdgeIterator& edgeIterator) const -> ConstVertexIterator
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return GetVertexIterator (polygon->GetEndVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetNextEdge (const ConstVertexIterator& vertexIterator) const -> ConstEdgeIterator
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return GetEdgeIterator (polygon->GetNextEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPrevEdge (const ConstVertexIterator& vertexIterator) const -> ConstEdgeIterator
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return GetEdgeIterator (polygon->GetPrevEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsVertexInContour (UIndex contourIdx, UIndex vertexIdx) const
{
	DBASSERT (polygon->status.isRegularized);
	if (vertexIdx < polygon->GetVertexBeginIdxInContour (contourIdx))
		return false;
	if (vertexIdx >= polygon->GetVertexEndIdxInContour (contourIdx))
		return false;

	return true;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsEdgeInContour (UIndex contourIdx, UIndex edgeIdx) const
{
	DBASSERT (polygon->status.isRegularized);
	if (edgeIdx < polygon->GetEdgeBeginIdxInContour (contourIdx))
		return false;
	if (edgeIdx >= polygon->GetEdgeEndIdxInContour (contourIdx))
		return false;

	return true;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsEmpty () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->IsEmpty ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::HasArcs () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->nArcs > 0;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Clear ()
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->Clear ();
	DBASSERT (polygon->status.isRegularized);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsABox () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->IsABox ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Optional<Circle2D> CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetMatchingCircle (void) const
{
	DBASSERT (polygon->status.isRegularized);
	Circle2D circle;
	if (polygon->IsACircle (circle))
		return circle;
	else
		return GS::NoValue;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Read (GS::IChannel& ic)
{
	DBASSERT (polygon->status.isRegularized);
	typename CorePolygon2DType::Flags flags;
	polygon = new CorePolygon2DType (flags);
	DBASSERT (polygon->status.isRegularized);
	return polygon->Read (ic);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Write (GS::OChannel& oc) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->Write (oc);
}


extern GEOMETRY_DLL_EXPORT const char*		XMLPolygon_Tag_Polygon2D;

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadXML (GS::XMLIChannel& ic)
{
	GS::XMLITag tag (ic, XMLPolygon_Tag_Polygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		GS::ClassVersion currentClassVersion;
		ic.ReadXMLVersionAttr (currentClassVersion);
		//currentClassVersion.ReadXML (ic);
		DBASSERT (currentClassVersion == Polygon2DPrivate::classInfo.GetVersion ());
	}

	GS::SharedPtr<CorePolygon2DType>  newPolygon 
		= CorePolygon2DType::ReadXMLAndCreate (ic);

	if (newPolygon == nullptr)
		throw GeometryIllegalArgumentException ("Can't Read XML file!!!", __FILE__, __LINE__);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> regularizedPolygons;
	typename CorePolygon2DType::PolygonResult polyResult = newPolygon->Regularize (regularizedPolygons);
	if (polyResult == CorePolygon2DType::ResultSameAsThis) {
		polygon = newPolygon;
	} else if (polyResult == CorePolygon2DType::EmptyPolygon) {
		polygon = new CorePolygon2DType (*newPolygon, true);
	} else {
		DBASSERT (regularizedPolygons.GetSize () <= 1);
		if (regularizedPolygons.GetSize () > 0)
			polygon = regularizedPolygons [0];
		else
			Clear ();
	}

	return ic.GetErrorStatus () == GS::XMLIChannel::Ok ? NoError : Error;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteXML (GS::XMLOChannel& oc) const
{
	DBASSERT (polygon->status.isRegularized);
	GSErrCode errCode = NoError;
	GS::XMLTag tag (oc, XMLPolygon_Tag_Polygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		oc.WriteXMLVersionAttr (Polygon2DPrivate::classInfo.GetVersion ());
		//GetClassVersion ().WriteXML (oc);
	}

	errCode = polygon->WriteXML (oc);
	if (errCode != NoError)
		return errCode;
	return oc.GetErrorStatus () == GS::XMLOChannel::Ok ? NoError : Error;
}


//Calculate
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const Box2DData&	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetBoundBox () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetBoundBox ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
Point2D	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetCenter () const
{
	DBASSERT (polygon->status.isRegularized);
	Box2DData polyBoundBox = polygon->GetBoundBox ();
	Point2D centerC  = Point2D ((polyBoundBox.xMin + polyBoundBox.xMax) / 2.0, (polyBoundBox.yMin + polyBoundBox.yMax) / 2.0);
	return centerC;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcArea () const
{
	return polygon->CalcArea ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcContourArea (const ConstContourIterator& contourIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	return polygon->CalcContourArea (contourIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::HasPositiveOrientation (const ConstContourIterator& contourIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	return polygon->HasPositiveOrientation (contourIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcPerimeter () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->CalcPerimeter ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcContourPerimeter (const ConstContourIterator& contourIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	return polygon->CalcPerimeter (contourIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Array<Point2D>	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcConvexHull (const ArcDivParams& arcDivParams) const
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<Point2D> convexHull;
	polygon->CalcConvexHull (arcDivParams, convexHull);
	return convexHull;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcMaxVertexFillet (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return polygon->CalcMaxVertexFillet (vertexIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsCoordOnEdge (const Point2D& c, ConstEdgeIterator* edgeIt) const
{
	DBASSERT (polygon->status.isRegularized);
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
double	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DistanceFromPoint (const Point2D& c) const
{
	return polygon->DistanceFromPoint (c);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Point2D& point, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (point, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Sector& sect, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (sect, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GenArc& arc, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (arc, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Box2DData& box, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (box, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const CustomPolygon2D& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (*poly.polygon, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Polyline2DType& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (*poly.polyline, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PGPositionExt	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentIn (Sector sector, GS::Array<Sector>* resSectors /*= nullptr*/) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->SegmentIn (sector, resSectors);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PGPositionExt	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentOut (Sector sector, GS::Array<Sector>* resSectors /*= nullptr*/) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->SegmentOut (sector, resSectors);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Intersect (const Point2D& c, const Vector2D& dir, GS::Array<Sector>* result) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->Intersect (c, dir, result);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::FixArray<Point2D, 4>	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetTransformedBoundBox (const TRANMAT& tr, const TRANMAT& invTr /*= Geometry::IdentityTranMat*/) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetTransformedBoundBox (tr, invTr);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Visit (ConstVertexVisitor &visitor) const
{
	DBASSERT (polygon->status.isRegularized);
	polygon->Visit (visitor);
}


//Modify polygon
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveHoles ()
{
	DBASSERT (polygon->status.isRegularized);
	GS::SharedPtr<CorePolygon2DType> result;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->RemoveHoles (result);
	SetResult (polyResult, result);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteHole (const ConstContourIterator& contourIterator)
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	DBASSERT (polygon->status.isRegularized);
	polygon = polygon->DeleteHole (contourIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Move (Vector2D offset)
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->Move (offset);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearVertexIds ()
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->ClearVertexUserDatas ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearEdgeIds ()
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->ClearEdgeUserDatas ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearContourIds ()
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->ClearContourUserDatas ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RotateVerticeIndicesInContour (const ConstContourIterator& contourToRotate, const ConstVertexIterator& vertexToFirst)
{
	DBASSERT (polygon->status.isRegularized);
	if (contourToRotate->BeginVertex () == vertexToFirst) {
		return;
	}
	
	CopyOnWrite ();
	polygon->RotateVerticeIndicesInContour (contourToRotate.GetItem ().GetIndex (), vertexToFirst.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SwapContourOrder (const GS::Array<ConstContourIterator>& newContourOrder)
{
	DBASSERT (polygon->status.isRegularized);
	if (newContourOrder.GetSize () < 2) {
		return;
	}
	bool inOrder = true;
	UInt32 i = 0;
	for (auto cIt = EnumerateContour (); cIt != nullptr && inOrder; ++cIt) {
		inOrder = cIt == newContourOrder [i++];
	}
	if (inOrder) {
		return;
	}

	CopyOnWrite ();

	GS::Array<UIndex> newContourOrderInIdx;
	newContourOrderInIdx.SetCapacity (newContourOrder.GetSize ());
	for (UIndex i = 0; i < newContourOrder.GetSize (); ++i)
		newContourOrderInIdx.Push (newContourOrder[i].GetItem ().GetIndex ());

	polygon->SwapContourOrder (newContourOrderInIdx);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SortArcsByIndices ()
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->SortArcsByIndices ();
}


// Create new polygons
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Transform (arcDivParams, tran, polygonArray);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (const CustomPolygon2D& filterWithPolygon,
																									const ArcDivParams& arcDivParams, 
																									const TRANMAT& tran, 
																									bool& isTransformedAll) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Transform (*filterWithPolygon.polygon, arcDivParams, tran, polygonArray, isTransformedAll);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (const MultiPolygon2DType& filterWithPolygon,
																									const ArcDivParams& arcDivParams, 
																									const TRANMAT& tran, 
																									bool& isTransformedAll) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	GS::Array<GS::SharedPtr<CorePolygon2DType>> filterPolygonArray;
	filterWithPolygon.GetCorePolygon2DArray (filterPolygonArray);
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Transform (filterPolygonArray, arcDivParams, tran, polygonArray, isTransformedAll);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentUp (const ArcDivParams& arcDivParams) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->SegmentUp (arcDivParams, polygonArray);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EliminateArcs () const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->EliminateArcs (polygonArray);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetContour (const ConstContourIterator& contourIterator, double offset) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->OffsetContour (contourIterator.GetItem ().GetIndex (), offset, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetEdge (const ConstEdgeIterator& edgeIterator, double offset) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->OffsetEdge (edgeIterator.GetItem ().GetIndex (), offset, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetEdgeFixArea (const ConstEdgeIterator& edgeIterator, 
																											const ConstVertexIterator& vertexIterator, 
																											double offset, 
																											double area) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->OffsetEdgeFixArea (edgeIterator.GetItem ().GetIndex (), vertexIterator.GetItem ().GetIndex (), offset, area, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MoveVertex (const ConstVertexIterator& vertexIterator, const Point2D& newPosition) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->MoveVertex (vertexIterator.GetItem ().GetIndex (), newPosition, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletAllVertex (const double filletRadius) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->FilletAllVertex (filletRadius, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletVertex (const ConstVertexIterator& vertexIterator, 
																									   const double filletRadius) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;	polygon->FilletVertex (vertexIterator.GetItem ().GetIndex (), filletRadius, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletVertexInContour (const ConstContourIterator& contourIterator, 
																												const double filletRadius) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->FilletVertexInContour (contourIterator.GetItem ().GetIndex (), filletRadius, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferAllVertex (const double chamferRadius) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->ChamferAllVertex (chamferRadius, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferVertex (const ConstVertexIterator& vertexIterator, 
																										const double chamferRadius) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->ChamferVertex (vertexIterator.GetItem ().GetIndex (), chamferRadius, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferVertexInContour (const ConstContourIterator& contourIterator, 
																												 const double chamferRadius) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->ChamferVertexInContour (contourIterator.GetItem ().GetIndex (), chamferRadius, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertVertex (const ConstEdgeIterator& edgeIterator, const Point2D& newPosition) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->InsertVertex (edgeIterator.GetItem ().GetIndex (), newPosition, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertVertexOnPolygon (const Point2D& newPosition, 
																												const ConstEdgeIterator& edgeIterator, 
																												ConstVertexIterator* vertexIterator /*= nullptr*/) const -> CustomPolygon2D
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	
	UIndex vertexIndex = 0;
	GS::SharedPtr<CorePolygon2DType> newPolygon;
	polygon->InsertVertexOnPolygon (newPosition, edgeIterator.GetItem ().GetIndex (), newPolygon, vertexIndex);
	CustomPolygon2D result;
	result.polygon = newPolygon;
	if (vertexIterator != nullptr)
		*vertexIterator = result.GetVertexIterator (vertexIndex);

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteVertex (const ConstVertexIterator& vertexIterator) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->DeleteVertex (vertexIterator.GetItem ().GetIndex (), polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MoveVertices (const GS::Array<GS::Pair<ConstVertexIterator, Point2D>>& newVertexPositions) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::HashTable<UIndex, Point2D> indexToCoordTable;
	for (const GS::Pair<ConstVertexIterator, Point2D>& vertexWithPosition : newVertexPositions) {
		DBASSERT (vertexWithPosition.first.GetTarget ()->polygon == polygon);
		UIndex vertexIndex = vertexWithPosition.first.GetItem ().GetIndex ();
		DBASSERT (!indexToCoordTable.ContainsKey (vertexIndex));
		indexToCoordTable.Add (vertexIndex, vertexWithPosition.second);
	}

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->MoveVertices (indexToCoordTable, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeAngle (const ConstEdgeIterator& edgeIterator, double edgeAngle) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->SetEdgeAngle (edgeIterator.GetItem ().GetIndex (), edgeAngle, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdge (const ConstEdgeIterator& edgeIterator, 
																									  const GS::Array<GenArc>& arcs, 
																									  const ArcDivParams& arcDivParams) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->ReplaceEdge (edgeIterator.GetItem ().GetIndex (), arcs, arcDivParams, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdge (const ConstEdgeIterator& edgeIterator, 
																									  const GS::Array<double>& angles, 
																									  const GS::Array<Point2D>& internalVerts) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->ReplaceEdge (edgeIterator.GetItem ().GetIndex (), angles, internalVerts, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteEdge (const ConstEdgeIterator& edgeIterator, MultiPolygon2DType& result) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	bool success = polygon->DeleteEdge (edgeIterator.GetItem ().GetIndex (), polygonArray);
	result = CustomPolygon2D::Create (polygonArray);
	return success;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AddHole (const CustomPolygon2D& poly, const ConstContourIterator& contourIterator) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == poly.polygon);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->AddHole (*poly.polygon, contourIterator.GetItem ().GetIndex (), polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Unify (const CustomPolygon2D& poly) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Unify (*poly.polygon, polygonArray);
	return CreateResult (polyResult, &poly, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Intersect (const CustomPolygon2D& poly, 
																									Boundary boundaries /*= Boundary_Closed*/, 
																									RelativePosition* relativePosition /*= nullptr*/, 
																									DetailedRelativePosition* detailed /*= nullptr*/) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Intersect (*poly.polygon, polygonArray, boundaries, relativePosition, detailed);
	return CreateResult (polyResult, &poly, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Substract (const CustomPolygon2D& poly, 
																									Boundary boundaries /*= Boundary_Closed*/, 
																									RelativePosition* relativePosition /*= nullptr*/, 
																									DetailedRelativePosition* detailed /*= nullptr*/) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Substract (*poly.polygon, polygonArray, boundaries, relativePosition, detailed);
	return CreateResult (polyResult, &poly, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Cut (const HalfPlane2DData& cutline, 
																							  bool* fullin /*= nullptr*/,
																							  GS::Int32* wrcode /*= nullptr*/,
																							  bool* degen /*= nullptr*/) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Cut (cutline, true /*regularizeResults*/, polygonArray, fullin, wrcode, degen);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Cut (const GS::Array<HalfPlane2DData>& cutlines, 
																							  bool* fullin /*= nullptr*/,
																							  GS::Int32* wrcode /*= nullptr*/,
																							  bool* degen /*= nullptr*/) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Cut (cutlines, true /*regularizeResults*/, polygonArray, fullin, wrcode, degen);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Strip (const HalfPlane2DData& cutline1, 
																								const HalfPlane2DData& cutline2, 
																								GS::Int32* wrcode /*= nullptr*/) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Strip (cutline1, cutline2, true /*regularizeResults*/, polygonArray, wrcode);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Clip (const Box2DData& box, GS::Int32* wrcode /*= nullptr*/) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	typename CorePolygon2DType::PolygonResult polyResult = polygon->Clip (box, true /*regularizeResults*/, polygonArray, wrcode);
	return CreateResult (polyResult, nullptr, polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Visit (VertexVisitor &visitor) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);

	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> irregularPolygon (*this);
	irregularPolygon.Visit (visitor);

	return Create (irregularPolygon);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Sector& sector, Boundary cutBoundaries, SectorCreator& creator) const
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (sector, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const GenArc& genArc, Boundary cutBoundaries, GenArcCreator& creator) const
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (genArc, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Point2D& coord, Boundary cutBoundaries, PointCreator& creator) const
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (coord, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const BezierDetails& bezier, Boundary cutBoundaries, SplineCreator& creator) const
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (bezier, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const CustomPolygon2D& poly, Boundary cutBoundaries, Polygon2DCreatorType& creator) const
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> results;
	polygon->CutElem (poly.polygon, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> polygon (results[polyIdx]);
		creator.CreatePolygon2D (polygon);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Polyline2DType& poly, Boundary cutBoundaries, Polyline2DCreatorType& creator) const
{
	GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>> results;
	polygon->CutElem (poly.polyline, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> polyline (results[polyIdx]);
		creator.CreatePolyline2D (polyline);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Sector& sector, Boundary cutBoundaries) const -> GS::Array<Sector>
{
	GS::Array<Sector> results;
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (sector, cutBoundaries, results);
	
	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const GenArc& genArc, Boundary cutBoundaries) const ->GS::Array<GenArc>
{
	GS::Array<GenArc> results;
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (genArc, cutBoundaries, results);

	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Point2D& coord, Boundary cutBoundaries) const -> GS::Array<Point2D>
{
	GS::Array<Point2D> results;
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (coord, cutBoundaries, results);

	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const BezierDetails& bezier, Boundary cutBoundaries) const -> GS::Array<BezierDetails>
{
	GS::Array<BezierDetails> results;
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (bezier, cutBoundaries, results);

	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const CustomPolygon2D& poly, Boundary cutBoundaries) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->CutElem (poly.polygon, cutBoundaries, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Polyline2DType& poly, Boundary cutBoundaries) const -> MultiPolyline2DType
{
	MultiPolyline2DType results;
	DBASSERT (polygon->status.isRegularized);
	GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>> polylineArray;
	polygon->CutElem (poly.polyline, cutBoundaries, polylineArray);
	for (typename GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>>::Iterator lineIter = polylineArray.Enumerate (); lineIter != nullptr; ++lineIter) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> tmpPolyline;
		tmpPolyline.polyline = *lineIter;
		results.Push (tmpPolyline);
	}

	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Array<Sector>	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IntersectElemBorderOnly (const Sector& sector) const
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<Sector> res;
	polygon->IntersectElemBorderOnly (sector, res);
	return res;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Array<GenArc>	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IntersectElemBorderOnly (const GenArc& arc) const
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<GenArc> res;
	polygon->IntersectElemBorderOnly (arc, res);
	return res;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Sector& sector, Boundary cutBoundaries, SectorCreator& creator) const
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (sector, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const GenArc& genArc, Boundary cutBoundaries, GenArcCreator& creator) const
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (genArc, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Point2D& coord, Boundary cutBoundaries, PointCreator& creator) const
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (coord, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const BezierDetails& bezier, Boundary cutBoundaries, SplineCreator& creator) const
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (bezier, cutBoundaries, creator);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const CustomPolygon2D& poly, Boundary cutBoundaries, Polygon2DCreatorType& creator) const
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> results;
	polygon->ElemPolyDifference (poly.polygon, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> polygon (results[polyIdx]);
		creator.CreatePolygon2D (polygon);
	}

}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Polyline2DType& poly, Boundary cutBoundaries, Polyline2DCreatorType& creator) const
{
	GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>> results;
	polygon->ElemPolyDifference (poly.polyline, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> polyline (results[polyIdx]);
		creator.CreatePolyline2D (polyline);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Sector& sector, Boundary cutBoundaries) const -> GS::Array<Sector>
{
	GS::Array<Sector> results;
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (sector, cutBoundaries, results);
	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const GenArc& genArc, Boundary cutBoundaries) const -> GS::Array<GenArc>
{
	GS::Array<GenArc> results;
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (genArc, cutBoundaries, results);

	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Point2D& coord, Boundary cutBoundaries) const -> GS::Array<Point2D>
{
	GS::Array<Point2D> results;
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (coord, cutBoundaries, results);

	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const BezierDetails& bezier, Boundary cutBoundaries) const -> GS::Array<BezierDetails>
{
	GS::Array<BezierDetails> results;
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (bezier, cutBoundaries, results);

	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const CustomPolygon2D& poly, Boundary cutBoundaries) const -> MultiPolygon2DType
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	polygon->ElemPolyDifference (poly.polygon, cutBoundaries, polygonArray);
	return CustomPolygon2D::Create (polygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Polyline2DType& poly, Boundary cutBoundaries) const -> MultiPolyline2DType
{
	MultiPolyline2DType results;
	DBASSERT (polygon->status.isRegularized);
	GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > > polylineArray;
	polygon->ElemPolyDifference (poly.polyline, cutBoundaries, polylineArray);
	for (typename GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >::Iterator lineIter = polylineArray.Enumerate (); lineIter != nullptr; ++lineIter) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> tmpPolyline;
		tmpPolyline.polyline = *lineIter;
		results.Push (tmpPolyline);
	}

	return results;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Array<Sector>	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDiffBorderOnly (const Sector& sector) const
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<Sector> res;
	polygon->ElemPolyDiffBorderOnly (sector, res);
	return res;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Array<GenArc>	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDiffBorderOnly (const GenArc& arc) const
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<GenArc> res;
	polygon->ElemPolyDiffBorderOnly (arc, res);
	return res;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const Sector& sector, Boundary cutBoundaries) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (sector, cutBoundaries);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const GenArc& genArc, Boundary cutBoundaries) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (genArc, cutBoundaries);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const Point2D& coord, Boundary cutBoundaries) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (coord, cutBoundaries);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const BezierDetails& bezier, Boundary cutBoundaries) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (bezier, cutBoundaries);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const CustomPolygon2D& poly, Boundary cutBoundaries, bool& touching) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (poly.polygon, cutBoundaries, touching);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const Polyline2DType& poly, Boundary cutBoundaries) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (poly.polyline, cutBoundaries);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CreateCommonEdgeSections (CustomPolygon2D& poly1, CustomPolygon2D& poly2)
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> result;
	bool changed = CorePolygon2DType::CreateCommonEdgeSections (*poly1.polygon, *poly2.polygon, true, result);
	if (changed && DBVERIFY (result.GetSize () == 2)) {
		poly1.polygon = result [0];
		poly2.polygon = result [1];
	}

	return changed;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
template<class EdgeUserDataComparator>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveSameDirEdgesWithSameEdgeUserData (CustomPolygon2D& poly, const EdgeUserDataComparator& comparator)
{
	DBASSERT (poly.polygon->status.isRegularized);
	poly.CopyOnWrite ();
	poly.polygon->RemoveSameDirEdgesOnlyWithSameUserData (comparator);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> result;
	typename CorePolygon2DType::PolygonResult polyResult = poly.polygon->Regularize (result);
	switch (polyResult) {
		case CorePolygon2DType::NewPolygons:
			DBASSERT (result.GetSize () == 1);
			poly.polygon = result[0];
			break;
		case CorePolygon2DType::ResultSameAsThis:
			break;
		case CorePolygon2DType::ResultSameAsFirstParameter:
		case CorePolygon2DType::ResultThisAndParameter:
		case CorePolygon2DType::EmptyPolygon:
		default:
			DBBREAK ();
			break;
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveSameDirEdgesWithSameEdgeUserData (CustomPolygon2D& poly)
{
	DBASSERT (poly.polygon->status.isRegularized);
	poly.CopyOnWrite ();
	poly.polygon->RemoveSameDirEdgesOnlyWithSameUserData ();

	GS::Array<GS::SharedPtr<CorePolygon2DType>> result;
	typename CorePolygon2DType::PolygonResult polyResult = poly.polygon->Regularize (result);
	switch (polyResult) {
		case CorePolygon2DType::NewPolygons:
			DBASSERT (result.GetSize () == 1);
			poly.polygon = result[0];
			break;
		case CorePolygon2DType::ResultSameAsThis:
			break;
		case CorePolygon2DType::ResultSameAsFirstParameter:
		case CorePolygon2DType::ResultThisAndParameter:
		case CorePolygon2DType::EmptyPolygon:
		default:
			DBBREAK ();
			break;
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertCommonXLineOnPolygon (double x, const EdgeSplitControl& cntrl)
{
	bool changed;
	polygon->InsertCommonXLineOnPolygon (x, changed, cntrl);
	return changed;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertCommonYLineOnPolygon (double y, const EdgeSplitControl& cntrl)
{
	bool changed;
	polygon->InsertCommonYLineOnPolygon (y, changed, cntrl);
	return changed;
}


// Debug
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Dump3DGDL (Geometry::Plane* thePlane /*= nullptr*/, GS::OChannel& oc /*= dbChannel*/) const
{
	polygon->Dump3DGDL (thePlane, oc);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
template <class Output>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Print (Output& oc) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->Print (oc);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PrintDebug () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->PrintDebug ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PrintDebugXML () const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->PrintDebugXML ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Check (PolyCheckFlags checkFlags, double coordUpperRange) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->Check (checkFlags, nullptr, coordUpperRange);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PolyRepairResult	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CheckAndRepair (PolyCheckFlags checkFlags, double coordUpperRange)
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


//***********************************************************************************************
//************************************** CustomMultiPolygon2D ***********************************
//***********************************************************************************************
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomMultiPolygon2D (const MultiIrregularPolygonType& polys)
{
	for (typename MultiIrregularPolygonType::ConstIterator it = polys.Enumerate (); it != nullptr; ++it) {
		IrregularPolygon2DType irregularPolygon2D = *it;
		CustomMultiPolygon2D tmp;
		tmp = PolyType::Create (irregularPolygon2D);

		for (typename CustomMultiPolygon2D::ConstIterator it2 = tmp.Enumerate (); it2 != nullptr; ++it2)
			this->Push (*it2);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomMultiPolygon2D (std::initializer_list<PolyType> items) :
	GS::Array<PolyType> (items)
{
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Unify (PolyHoleHandling holeHandling /*= ReturnHoles*/)
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> corePolygonArray;
	GetCorePolygon2DArray (corePolygonArray);
	this->Clear ();
	CorePolygon2DType::Unify (corePolygonArray, holeHandling);
	PushCorePolygon2DArray (corePolygonArray);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentUp (const ArcDivParams& arcDivParams)
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> corePolygonArray;
	GetCorePolygon2DArray (corePolygonArray);
	this->Clear ();
	GS::SharedPtr<CorePolygon2DType> firstParam;
	for (UIndex polyIdx = 0; polyIdx < corePolygonArray.GetSize (); polyIdx++) {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> result;
		typename CorePolygon2DType::PolygonResult polyResult = corePolygonArray[polyIdx]->SegmentUp (arcDivParams, result);
		PushResults (polyResult, corePolygonArray[polyIdx], firstParam, result);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran)
{
	if (tran.IsIdentity ()) {
		return;
	}

	bool isPreserveArc = Geometry::TMIsPreserveArc (tran);
	if (isPreserveArc) {
		MultiIrregularPolygonType irregularPolygons;
		for (UIndex idx = 0; idx < this->GetSize(); idx++) {
			CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> irregularPolygon (this->Get(idx));
			irregularPolygon.CopyOnWrite ();
			irregularPolygon.TransformPreserveArcs (tran);
			irregularPolygons.Push (irregularPolygon);
		}
		this->Clear ();
		for (typename MultiIrregularPolygonType::ConstIterator irrPolyIt = irregularPolygons.Enumerate (); irrPolyIt != nullptr; ++irrPolyIt) {
			CustomMultiPolygon2D regularizedPolygons = irrPolyIt->Regularize ();
			for (typename CustomMultiPolygon2D::ConstIterator polyIt = regularizedPolygons.Enumerate (); polyIt != nullptr; ++polyIt)
				this->Push (*polyIt);
		}

	} else {
		GS::Array<GS::SharedPtr<CorePolygon2DType>> corePolygonArray;
		GetCorePolygon2DArray (corePolygonArray);
		this->Clear ();
		GS::SharedPtr<CorePolygon2DType> firstParam;
		for (UIndex polyIdx = 0; polyIdx < corePolygonArray.GetSize (); polyIdx++) {
			GS::Array<GS::SharedPtr<CorePolygon2DType>> result;
			typename CorePolygon2DType::PolygonResult polyResult = corePolygonArray[polyIdx]->Transform (arcDivParams, tran, result);
			PushResults (polyResult, corePolygonArray[polyIdx], firstParam, result);
		}
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Read (GS::IChannel& ic)
{
	NULL_REF_CHECK (ic);

	this->Clear ();

	GS::InputFrame frame (ic, MultiPolygon2DPrivate::classInfo);
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
GSErrCode	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Write (GS::OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, MultiPolygon2DPrivate::classInfo);

	GSErrCode errorCode = oc.Write (this->GetSize ());

	for (UIndex i = 0; i < this->GetSize () && errorCode == NoError; i++)
		errorCode = this->Get (i).Write (oc);

	return errorCode;
}


extern	GEOMETRY_DLL_EXPORT const char*		XMLPolygon_Tag_MultiPolygon2D;
extern	GEOMETRY_DLL_EXPORT const char*		XMLPolygon_Attr_PolyNum;

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadXML	(GS::XMLIChannel& ic)
{
	GSErrCode errCode = NoError;
	GS::XMLITag tagMultiPolygon2D (ic, XMLPolygon_Tag_MultiPolygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		GS::ClassVersion currentClassVersion;
		ic.ReadXMLVersionAttr (currentClassVersion);
		//currentClassVersion.ReadXML (ic);
		DBASSERT (currentClassVersion == MultiPolygon2DPrivate::classInfo.GetVersion ());
	}

	USize newSize = 0;
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLPolygon_Attr_PolyNum, newSize);

	GS::UniString tokenName;
	while (tagMultiPolygon2D.IsNextChildStartTag (tokenName) && (errCode == NoError)) {
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> newPoly;
		errCode = newPoly.ReadXML (ic);
		this->Push (newPoly);
	}

	DBASSERT (newSize == this->GetSize ());

	if (errCode != NoError)
		return errCode;
	return ic.GetErrorStatus () == GS::XMLIChannel::Ok ? NoError : Error;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteXML (GS::XMLOChannel& oc) const
{
	GSErrCode errCode = NoError;
	GS::XMLTag tagMultiPolygon2D (oc, XMLPolygon_Tag_MultiPolygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		oc.WriteXMLVersionAttr (MultiPolygon2DPrivate::classInfo.GetVersion ());
		//GetClassVersion ().WriteXML (oc);
	}

	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLPolygon_Attr_PolyNum, this->GetSize ());

	for (UIndex idx = 0; idx < this->GetSize() && errCode == NoError; idx++) {
		errCode = this->Get (idx).WriteXML (oc);
	}

	if (errCode != NoError)
		return errCode;
	return oc.GetErrorStatus () == GS::XMLOChannel::Ok ? NoError : Error;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PopLargest () -> PolyType
{
	PolyType actPoly;
	if (this->GetSize () == 0) {
		return actPoly;
	}
	else if (this->GetSize () == 1) {
		actPoly = this->Get (0);
		this->Clear ();
		return actPoly;
	}

	double act, max	= -DBL_MAX;
	UIndex argmax	= 0;
	for (UIndex idx = 0; idx < this->GetSize (); idx++) {
		act = ((this->Get (idx)).CalcArea) ();
		DBASSERT (act >= 0.);
		if (max < act) {
			max = act;
			argmax = idx;
		}
	}
	actPoly = this->Get(argmax);
	this->Delete (argmax);
	return actPoly;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Int32	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetLargestIdx () const
{
	if (this->GetSize () == 0) {
		DBBREAK (); //lehet, hogy ez nem is hiba?
		return -1;
	}
	else if (this->GetSize () == 1) {
		return 0;
	}
	double largestArea = 0.0;
	UIndex largestIdx = 0;
	double currArea = 0.0;
	for (UIndex idx = 0; idx < this->GetSize (); idx++) {
		currArea = this->Get (idx).CalcArea ();
		if (currArea > largestArea) {
			largestArea = currArea;
			largestIdx = idx;
		}
	}
	return largestIdx;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
Box2DData	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetBoundBox () const
{
	Box2DData box;
	if (this->GetSize () == 0) {
		return box;
	}
	else if (this->GetSize() == 1)
		return this->Get (0).GetBoundBox ();

	box = this->Get (0).GetBoundBox ();
	for (UIndex idx = 1; idx < this->GetSize(); idx++) {
		const Box2DData& elemBox = this->Get (idx).GetBoundBox ();
		UnionBox (&elemBox, &box);
	}
	return box;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcArea () const
{
	double area = 0;

	for (UIndex idx = 0; idx < this->GetSize(); idx++) {
		area += this->Get (idx).CalcArea ();
	}
	return area;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Array<Point2D>	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcConvexHull (const ArcDivParams& arcDivParams) const
{
	GS::Array<Point2D> convexHull;
	ConvexHull2DCreator convexHullCreator;
	
	for (UIndex idx = 0; idx < this->GetSize (); ++idx) {
		const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& polygon = this->Get (idx);
		if (polygon.HasArcs ()) {
			CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpMultiPolygon = polygon.SegmentUp (arcDivParams);
			for (UIndex polygonIdx = 0; polygonIdx < tmpMultiPolygon.GetSize (); ++polygonIdx) {
				for (UIndex vertexIdx = 1; vertexIdx <= tmpMultiPolygon[polygonIdx].GetVertexNum (); ++vertexIdx) {
					convexHullCreator.AddPoint (tmpMultiPolygon[polygonIdx].GetVertexCoordByIdx (vertexIdx));
				}
			} 
		} else {
			for (UIndex vertexIdx = 1; vertexIdx <= polygon.GetVertexNum (); ++vertexIdx) {
				convexHullCreator.AddPoint (polygon.GetVertexCoordByIdx (vertexIdx));
			}
		}
	}

	GS::PagedArray<Point3D> convexHull3D = convexHullCreator.CalcConvexHull ();
	convexHull.Clear ();
	for (UIndex i = 0; i < convexHull3D.GetSize (); ++i) {
		convexHull.Push (Point2D (convexHull3D[i].x, convexHull3D[i].y));
	}

	return convexHull;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Point2D& point, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, point, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Sector& sect, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, sect, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GenArc& arc, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, arc, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Box2DData& box, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, box, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const PolyType& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, *poly.polygon, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const PolylineType& poly, 
																													   Boundary boundaries, 
																													   DetailedRelativePosition* detailed /*= nullptr*/) const
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2DType::GetPosition (polygonArray, *poly.polyline, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Substract (const CustomMultiPolygon2D& poly1,
																										 const CustomMultiPolygon2D& poly2, 
																										 bool* changed /*= nullptr*/) -> CustomMultiPolygon2D
{
	GS::Array<GS::SharedPtr<CorePolygon2DType>> poly1CorePolygonArray;
	poly1.GetCorePolygon2DArray (poly1CorePolygonArray);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> poly2CorePolygonArray;
	poly2.GetCorePolygon2DArray (poly2CorePolygonArray);

	GS::Array<GS::SharedPtr<CorePolygon2DType>> resultCorePolygonArray = CorePolygon2DType::Substract (poly1CorePolygonArray,
																									   poly2CorePolygonArray,
																									   changed);

	CustomMultiPolygon2D result;
	result.PushCorePolygon2DArray (resultCorePolygonArray);
	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
auto	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Intersect (const CustomMultiPolygon2D& poly1, const CustomMultiPolygon2D& poly2) -> CustomMultiPolygon2D
{
	CustomMultiPolygon2D result;
	for (GS::UInt32 i = 0; i < poly2.GetSize (); i++) {
		GS::UInt32	oldSize = poly1.GetSize ();
		for (GS::UInt32 j = 0; j < oldSize; j++) {
			CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>		result1;
			RelativePosition	relativePosition;
			result1 = poly1[j].Intersect (poly2[i], Boundary_Closed, &relativePosition);
			result.Insert (result.GetSize (), result1.Begin ());
		}
	}

	return result;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetCorePolygon2DArray (GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray) const
{
	for (UIndex idx = 0; idx < this->GetSize(); idx++) {
		polygonArray.Push (this->Get(idx).polygon);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PushCorePolygon2DArray (const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray)
{
	for (UIndex idx = 0; idx < polygonArray.GetSize(); idx++) {
		if (!polygonArray[idx]->IsEmpty ()) {
			CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> poly2D;
			poly2D.polygon = polygonArray[idx];
			this->Push (poly2D);
		}
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PushResults (typename CorePolygon2DType::PolygonResult polyResult, 
																										   const GS::SharedPtr<CorePolygon2DType>& thisPoly, 
																										   const GS::SharedPtr<CorePolygon2DType>& firstParam,
																										   const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray)
{
	switch (polyResult) {
		case CorePolygon2DType::NewPolygons:
			PushCorePolygon2DArray (polygonArray);
			break;
		case CorePolygon2DType::ResultSameAsThis:
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			{
				if (!thisPoly->IsEmpty ()) {
					GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (*thisPoly);
					this->Push (newPolygon);
				}
			}
#else
			if (!thisPoly->IsEmpty ())
				this->Push (thisPoly);
#endif
			break;
		case CorePolygon2DType::ResultSameAsFirstParameter:
			DBASSERT (firstParam != nullptr);
			if (firstParam != nullptr && !firstParam->IsEmpty ()) {
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
				{
					GS::SharedPtr<CorePolygon2DType> newPolygon = new CorePolygon2DType (*firstParam);
					this->Push (newPolygon);
				}
#else
				this->Push (firstParam);
#endif
			}
			break;
		case CorePolygon2DType::ResultThisAndParameter:
			DBASSERT (firstParam != nullptr);
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			{
				if (!thisPoly->IsEmpty ()) {
					GS::SharedPtr<CorePolygon2DType> newPolygon1 = new CorePolygon2DType (*thisPoly);
					this->Push (newPolygon1);
				}
				if (firstParam != nullptr && !firstParam->IsEmpty ()) {
					GS::SharedPtr<CorePolygon2DType> newPolygon2 = new CorePolygon2DType (*firstParam);
					this->Push (newPolygon2);
				}
			}
#else
			if (!thisPoly->IsEmpty ())
				this->Push (thisPoly);
			if (firstParam != nullptr && !firstParam->IsEmpty ())
				this->Push (firstParam);
#endif
			break;
		case CorePolygon2DType::EmptyPolygon:
			break;
		default:
			DBBREAK ();
			break;
	}
}

} //Geometry namespace

#endif //GEOMETRY_POLYGON2D_HPP
