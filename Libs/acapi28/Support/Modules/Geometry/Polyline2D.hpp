// *****************************************************************************
//
// Declaration of Polyline2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA, RJ
//
// *****************************************************************************

#ifndef GEOMETRY_POLYLINE2D_HPP
#define GEOMETRY_POLYLINE2D_HPP

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes ----------------------------------------------------------------
#include "Polyline2DClassDefinition.hpp"
#include "Polygon2DClassDefinition.hpp"
#include "IrregularPolygon2DClassDefinition.hpp"

namespace Geometry {

#ifdef CHECKED_VERSION
#define DEBUVERS_POLY2D
#endif

#if defined(DEBUVERS_POLY2D)
#define DBCHECKINDEX_POLY2D(idx, minIdx, maxIdx) DBASSERT ((idx) >= (minIdx) && (idx) <= (maxIdx))
#else
#define DBCHECKINDEX_POLY2D(idx, minIdx, maxIdx)
#endif


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (const GS::SharedPtr<CorePolyline2DType>& polyline2D) : polyline (polyline2D)
{
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const GS::Array<GS::SharedPtr<CorePolyline2DType>>& polylineArray) -> MultiPolyline2DType
{
	MultiPolyline2DType result;

	if (polylineArray.GetSize () == 0) {
		return result;
	}

	UIndex idx;
	for(idx = 0; idx < polylineArray.GetSize (); idx++) {
		if (polylineArray[idx]->IsEmpty ()) {
			DBBREAK ();
			continue;
		}
		CustomPolyline2D tmpPolyline (polylineArray[idx]);
		result.Push (tmpPolyline);
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CreateResult (typename CorePolyline2DType::PolylineResult polyResult,
																					   const GS::SharedPtr<CorePolyline2DType>& newPolyline) const -> CustomPolyline2D
{
	switch (polyResult) {
		case CorePolyline2DType::NewPolylines:
			return newPolyline;
		case CorePolyline2DType::ResultSameAsThis:
			return polyline;
		case CorePolyline2DType::EmptyPolyline:
			break;
		default:
			DBBREAK ();
			break;
	}

	return CustomPolyline2D ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CreateResult (typename CorePolyline2DType::PolylineResult polyResult,
																					   const GS::Array<GS::SharedPtr<CorePolyline2DType>>& polylineArray) const -> MultiPolyline2DType
{
	MultiPolyline2DType result;
	switch (polyResult) {
		case CorePolyline2DType::NewPolylines:
			return CustomPolyline2D::Create (polylineArray);
		case CorePolyline2DType::ResultSameAsThis:
			result.Push (polyline);
			break;
		case CorePolyline2DType::EmptyPolyline:
			break;
		default:
			DBBREAK ();
			break;
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyOnWrite ()
{
	if (polyline == nullptr)
		throw GeometryIllegalArgumentException ("Polyline can't be nullptr!!!", __FILE__, __LINE__);
	if (polyline->GetRefCount()> 1)
		polyline = new CorePolyline2DType (*polyline);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetFlags (GS::UInt32 polyFlags /*PolyFlags*/) -> typename CorePolyline2DType::Flags
{
	typename CorePolyline2DType::Flags flags;

	DBASSERT (!((PolyFlags_IsSameDirEdgeLegal & polyFlags) && (PolyFlags_NoSameDirEdgeLegal & polyFlags)));
	if (PolyFlags_IsSameDirEdgeLegal & polyFlags)
		flags.isSameDirEdgeLegal = true;
	if (PolyFlags_NoSameDirEdgeLegal & polyFlags)
		flags.isSameDirEdgeLegal = false;
	DBASSERT (!((PolyFlags_IsClosed & polyFlags) && (PolyFlags_NoClosed & polyFlags)));
	if (PolyFlags_IsClosed & polyFlags)
		flags.isClosed = true;
	if (PolyFlags_NoClosed & polyFlags)
		flags.isClosed = false;
	DBASSERT (!((PolyFlags_IsSameCoord & polyFlags) && (PolyFlags_NoSameCoord & polyFlags)));
	if (PolyFlags_IsSameCoord & polyFlags)
		flags.isSameCoord = true;
	if (PolyFlags_NoSameCoord & polyFlags)
		flags.isSameCoord = false;
	DBASSERT (!((PolyFlags_IsVertexUserData & polyFlags) && (PolyFlags_NoVertexUserData & polyFlags)));
	if (PolyFlags_IsVertexUserData & polyFlags)
		flags.isVertexUserData = true;
	if (PolyFlags_NoVertexUserData & polyFlags)
		flags.isVertexUserData = false;
	DBASSERT (!((PolyFlags_IsEdgeUserData & polyFlags) && (PolyFlags_NoEdgeUserData & polyFlags)));
	if (PolyFlags_IsEdgeUserData & polyFlags)
		flags.isEdgeUserData = true;
	if (PolyFlags_NoEdgeUserData & polyFlags)
		flags.isEdgeUserData = false;
	DBASSERT (!(PolyFlags_IsContourUserData & polyFlags));
	DBASSERT (!(PolyFlags_NoContourUserData & polyFlags));
	DBASSERT (!((PolyFlags_IsPolygonUserData & polyFlags) && (PolyFlags_NoPolygonUserData & polyFlags)));
	if (PolyFlags_IsPolygonUserData & polyFlags)
		flags.isPolygonUserData = true;
	if (PolyFlags_NoPolygonUserData & polyFlags)
		flags.isPolygonUserData = false;


	return flags;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D ()
{
	typename CorePolyline2DType::Flags flags;
	polyline = new CorePolyline2DType (flags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/)
{
	polyline = new CorePolyline2DType (GetFlags (flags));
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& source)
{
	polyline = source.polyline;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (const Polygon2DType<ContourUserData>& polygon, typename Polygon2DType<ContourUserData>::ConstContourIterator contourIterator)
{
 	polyline = new CorePolyline2DType (*polygon.polygon, contourIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (const IrregularPolygon2DType<ContourUserData>& polygon, typename IrregularPolygon2DType<ContourUserData>::ConstContourIterator contourIterator)
{
 	polyline = new CorePolyline2DType (*polygon.polygon, contourIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (const ContourDescription& contourDesc)
{
	typename CorePolyline2DType::Flags flags;
	if (contourDesc.GetSegmentList ().GetSize () == 0)
		polyline = new CorePolyline2DType (flags);
	else
		polyline = new CorePolyline2DType (flags, contourDesc);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const ContourDescription& contourDesc)
{
	if (contourDesc.GetSegmentList ().GetSize () == 0) {
		polyline = new CorePolyline2DType (GetFlags (flags));
	} else {
		polyline = new CorePolyline2DType (GetFlags (flags), contourDesc);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/)
{
	typename CorePolyline2DType::Flags flags;
	if (coordList.GetSize () == 0)
		polyline = new CorePolyline2DType (flags);
	else
		polyline = new CorePolyline2DType (flags, coordList, arcList, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/)
{
	if (coordList.GetSize () == 0) {
		polyline = new CorePolyline2DType (GetFlags (flags));
	} else {
		polyline = new CorePolyline2DType (GetFlags (flags), coordList, arcList, createFlags);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (const GS::Array<Point2D>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/)
{
	typename CorePolyline2DType::Flags flags;
	if (coordList.GetSize () == 0)
		polyline = new CorePolyline2DType (flags);
	else {
		GS::Array<PolyArcRec> arcList;
		polyline = new CorePolyline2DType (flags, coordList, arcList, createFlags);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Point2D>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/)
{
	if (coordList.GetSize () == 0) {
		polyline = new CorePolyline2DType (GetFlags (flags));
	} else {
		GS::Array<PolyArcRec> arcList;
		polyline = new CorePolyline2DType (GetFlags (flags), coordList, arcList, createFlags);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/)
{
	typename CorePolyline2DType::Flags flags;
	if (nValuableCoords == 0)
		polyline = new CorePolyline2DType (flags);
	else
		polyline = new CorePolyline2DType (flags, coords, nValuableCoords, arcs, nValuableArcs, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/)
{
	if (nValuableCoords == 0) {
		polyline = new CorePolyline2DType (GetFlags (flags));
	} else {
		polyline = new CorePolyline2DType (GetFlags (flags), coords, nValuableCoords, arcs, nValuableArcs, createFlags);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (const Point2D* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/)
{
	typename CorePolyline2DType::Flags flags;
	if (nValuableCoords == 0)
		polyline = new CorePolyline2DType (flags);
	else
		polyline = new CorePolyline2DType (flags, coords, nValuableCoords, nullptr /*arcs*/, 0 /*nValuableArcs*/, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const Point2D* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/)
{
	if (nValuableCoords == 0) {
		polyline = new CorePolyline2DType (GetFlags (flags));
	} else {
		polyline = new CorePolyline2DType (GetFlags (flags), coords, nValuableCoords, nullptr /*arcs*/, 0 /*nValuableArcs*/, createFlags);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (const GenArc genArc, const ArcDivParams& arcDivParams)
{
	typename CorePolyline2DType::Flags flags;
	polyline = new CorePolyline2DType (flags, genArc, arcDivParams);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const GenArc genArc, const ArcDivParams& arcDivParams)
{
	polyline = new CorePolyline2DType (GetFlags (flags), genArc, arcDivParams);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (const Box2DData& box)
{
	typename CorePolyline2DType::Flags flags;
	polyline = new CorePolyline2DType (flags, box);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const Box2DData& box)
{

	polyline = new CorePolyline2DType (GetFlags (flags), box);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::~CustomPolyline2D ()
{
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const ContourDescription& contourDesc) -> CustomPolyline2D
{
	return CustomPolyline2D (contourDesc);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const ContourDescription& contourDesc) -> CustomPolyline2D
{
	return CustomPolyline2D (flags, contourDesc);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const Point2D* coords,
																					 USize nValuableCoords,
																					 const PolyArcRec* arcs,
																					 USize nValuableArcs,
																					 GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomPolyline2D
{
	return CustomPolyline2D (coords, nValuableCoords, arcs, nValuableArcs, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/,
																					 const Point2D* coords,
																					 USize nValuableCoords,
																					 const PolyArcRec* arcs,
																					 USize nValuableArcs,
																					 GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomPolyline2D
{
	return CustomPolyline2D (flags, coords, nValuableCoords, arcs, nValuableArcs, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const Point2D* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomPolyline2D
{
	return CustomPolyline2D (coords, nValuableCoords, nullptr /*arcs*/, 0 /*nValuableArcs*/, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, 
																				 const Point2D* coords, 
																				 USize nValuableCoords, 
																				 GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomPolyline2D
{
	return CustomPolyline2D (flags, coords, nValuableCoords, nullptr /*arcs*/, 0 /*nValuableArcs*/, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const GS::Array<Point2D>& coordList,
																				 const GS::Array<PolyArcRec>& arcList,
																				 GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomPolyline2D
{
	return CustomPolyline2D (coordList, arcList, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/,
																				 const GS::Array<Point2D>& coordList,
																				 const GS::Array<PolyArcRec>& arcList,
																				 GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomPolyline2D
{
	return CustomPolyline2D (flags, coordList, arcList, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const GS::Array<Point2D>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomPolyline2D
{
	return CustomPolyline2D (coordList, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Point2D>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/) -> CustomPolyline2D
{
	return CustomPolyline2D (flags, coordList, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const GenArc genArc, const ArcDivParams& arcDivParams) -> CustomPolyline2D
{
	return CustomPolyline2D (genArc, arcDivParams);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const GenArc genArc, const ArcDivParams& arcDivParams) -> CustomPolyline2D
{
	return CustomPolyline2D (flags, genArc, arcDivParams);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const GS::Array<ContourDescription>& contourDesc) -> MultiPolyline2DType
{
	MultiPolyline2DType result;

	UIndex contourDescIdx = 0;
	for (contourDescIdx = 0; contourDescIdx < contourDesc.GetSize(); contourDescIdx++) {
		CustomPolyline2D tmpPolyline (contourDesc[contourDescIdx]);
		if (!tmpPolyline.IsEmpty ()) {
			result.Push (tmpPolyline);
		}
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<ContourDescription>& contourDesc) -> MultiPolyline2DType
{
	MultiPolyline2DType result;

	UIndex contourDescIdx = 0;
	for (contourDescIdx = 0; contourDescIdx < contourDesc.GetSize(); contourDescIdx++) {
		CustomPolyline2D tmpPolyline (flags, contourDesc[contourDescIdx]);
		if (!tmpPolyline.IsEmpty ()) {
			result.Push (tmpPolyline);
		}
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const Polygon2DType<ContourUserData>& polygon,
																				 typename Polygon2DType<ContourUserData>::ConstContourIterator contourIterator) -> CustomPolyline2D
{
	return CustomPolyline2D (polygon, contourIterator);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const Polygon2DType<ContourUserData>& polygon) -> MultiPolyline2DType
{
	MultiPolyline2DType result;

	for (typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator contourIterator = polygon.EnumerateContour (); contourIterator != nullptr; ++contourIterator) {
		CustomPolyline2D tmpPolyline (polygon, contourIterator);
		if (!tmpPolyline.IsEmpty ()) {
			result.Push (tmpPolyline);
		}
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const IrregularPolygon2DType<ContourUserData>& polygon) -> MultiPolyline2DType
{
	MultiPolyline2DType result;

	for (typename IrregularPolygon2DType<ContourUserData>::ConstContourIterator contourIterator = polygon.EnumerateContour (); contourIterator != nullptr; ++contourIterator) {
		CustomPolyline2D tmpPolyline (polygon, contourIterator);
		if (!tmpPolyline.IsEmpty ()) {
			result.Push (tmpPolyline);
		}
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const IrregularPolygon2DType<ContourUserData>& polygon,
																				 typename IrregularPolygon2DType<ContourUserData>::ConstContourIterator contourIterator) -> CustomPolyline2D
{
	return CustomPolyline2D (polygon, contourIterator);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const Point2D* coords,
																				 USize nValuableCoords,
																				 const PolyArcRec* arcs,
																				 USize nValuableArcs,
																				 const UIndex* contourEnds,
																				 USize nContours,
																				 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolyline2DType
{
	MultiPolyline2DType result;

	DBASSERT ((nValuableCoords == 0 && nContours == 0) || (nValuableCoords> 0 && coords != nullptr && nContours> 0 && contourEnds != nullptr));

	if (nValuableCoords> 0 && coords != nullptr && nContours> 0 && contourEnds != nullptr) {
		GS::Array<GS::SharedPtr<CorePolyline2DType>> polylineArray;
		typename CorePolyline2DType::Flags flags;
		CorePolyline2DType::Create (flags, coords, nValuableCoords, arcs, nValuableArcs, contourEnds, nContours, createFlags, polylineArray);
		UIndex idx;
		for(idx = 0; idx < polylineArray.GetSize(); idx++) {
			if (polylineArray[idx]->IsEmpty ()) {
				DBBREAK ();
				continue;
			}
			CustomPolyline2D tmpPolyline (polylineArray[idx]);
			result.Push (tmpPolyline);
		}
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/,
																				 const Point2D* coords,
																				 USize nValuableCoords,
																				 const PolyArcRec* arcs,
																				 USize nValuableArcs,
																				 const UIndex* contourEnds,
																				 USize nContours,
																				 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolyline2DType
{
	MultiPolyline2DType result;

	DBASSERT ((nValuableCoords == 0 && nContours == 0) || (nValuableCoords> 0 && coords != nullptr && nContours> 0 && contourEnds != nullptr));

	if (nValuableCoords> 0 && coords != nullptr && nContours> 0 && contourEnds != nullptr) {
		GS::Array<GS::SharedPtr<CorePolyline2DType>> polylineArray;
		CorePolyline2DType::Create (GetFlags (flags), coords, nValuableCoords, arcs, nValuableArcs, contourEnds, nContours, createFlags, polylineArray);
		UIndex idx;
		for(idx = 0; idx < polylineArray.GetSize(); idx++) {
			if (polylineArray[idx]->IsEmpty ()) {
				DBBREAK ();
				continue;
			}
			CustomPolyline2D tmpPolyline (polylineArray[idx]);
			result.Push (tmpPolyline);
		}
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (const GS::Array<Point2D>& coordList,
																				 const GS::Array<PolyArcRec>& arcList,
																				 const GS::Array<UIndex>& contourEndList,
																				 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolyline2DType
{
	MultiPolyline2DType result;

	DBASSERT ((coordList.IsEmpty () && contourEndList.IsEmpty ()) || (!coordList.IsEmpty () && !contourEndList.IsEmpty ()));

	if (!coordList.IsEmpty () && !contourEndList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolyline2DType>> polylineArray;
		typename CorePolyline2DType::Flags flags;
		CorePolyline2DType::Create (flags, coordList, arcList, contourEndList, createFlags, polylineArray);
		UIndex idx;
		for(idx = 0; idx < polylineArray.GetSize(); idx++) {
			if (polylineArray[idx]->IsEmpty ()) {
				DBBREAK ();
				continue;
			}
			CustomPolyline2D tmpPolyline (polylineArray[idx]);
			result.Push (tmpPolyline);
		}
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/,
																				 const GS::Array<Point2D>& coordList,
																				 const GS::Array<PolyArcRec>& arcList,
																				 const GS::Array<UIndex>& contourEndList,
																				 GS::UInt32 createFlags /*PolyCreateFlags*/) -> MultiPolyline2DType
{
	MultiPolyline2DType result;

	DBASSERT ((coordList.IsEmpty () && contourEndList.IsEmpty ()) || (!coordList.IsEmpty () && !contourEndList.IsEmpty ()));

	if (!coordList.IsEmpty () && !contourEndList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolyline2DType>> polylineArray;
		CorePolyline2DType::Create (GetFlags (flags), coordList, arcList, contourEndList, createFlags, polylineArray);
		UIndex idx;
		for(idx = 0; idx < polylineArray.GetSize(); idx++) {
			if (polylineArray[idx]->IsEmpty ()) {
				DBBREAK ();
				continue;
			}
			CustomPolyline2D tmpPolyline (polylineArray[idx]);
			result.Push (tmpPolyline);
		}
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ConvertToContourDescription () const -> ContourDescription
{
	ContourDescription contourDesc;
	polyline->Convert (contourDesc);
	return contourDesc;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ArcToNurbs ()
{
	polyline->ArcToNurbs ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ConvertToPolygon () const -> MultiPolygon2DType<ContourUserData>
{
	return Polygon2DType<ContourUserData>::Create (*this);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ConvertFromPolyline2D (const CustomPolyline2D<VertexUserData1, EdgeUserData1, PolygonUserData1>& fromPolyline) -> CustomPolyline2D
{
	CustomPolyline2D result;
	CorePolyline2D<VertexUserData1, EdgeUserData1, PolygonUserData1>::ConvertFromCorePolyline2D (*result.polyline, *fromPolyline.polyline);
	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyPolylineData (Point2D* coords,
																						   USize& nValuableCoords,
																						   PolyArcRec* arcs,
																						   USize& nValuableArcs,
																						   GS::Array<NurbsCurve2D>& nurbs,
																						   GS::UInt32 createFlags /*PolyCreateFlags*/) const
{
	polyline->CopyPolylineData (coords, nValuableCoords, arcs, nValuableArcs, nurbs, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyPolylineData (GS::Array<Point2D>& coords,
																						   GS::Array<PolyArcRec>& arcs,
																						   GS::Array<NurbsCurve2D>& nurbs,
																						   GS::UInt32 createFlags /*PolyCreateFlags*/) const
{
	polyline->CopyPolylineData (coords, arcs, nurbs, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::AllocateAndCopyPolylineData (Point2D** coords,
																									  USize& nValuableCoords,
																									  PolyArcRec** arcs,
																									  USize& nValuableArcs,
																									  GS::UInt32 createFlags /*PolyCreateFlags*/) const
{
	DBASSERT (coords != nullptr && (polyline->nArcs == 0 || arcs != nullptr));

	if (coords == nullptr || (polyline->nArcs> 0 && arcs == nullptr))
		throw GeometryIllegalArgumentException ("Error in Polyline2D::AllocateAndCopyPolylineData!!!", __FILE__, __LINE__);

	GS::Array<NurbsCurve2D> dummyNurbs;
	polyline->CopyPolylineData (nullptr, nValuableCoords, nullptr, nValuableArcs, dummyNurbs, createFlags);

	if (IsEmpty ())
		return;

	USize coordOffset = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 1 : 0;
	*coords	= reinterpret_cast<Point2D*>(BMAllocatePtr ((nValuableCoords + coordOffset) * sizeof (Point2D), ALLOCATE_CLEAR, 0));

	if (arcs != nullptr) {
		USize arcOffset = (PolyCreateFlags_DummyArcAtIdxZero & createFlags) ? 1 : 0;
		*arcs	= reinterpret_cast<PolyArcRec*>(BMAllocatePtr ((nValuableArcs + arcOffset) * sizeof (PolyArcRec), ALLOCATE_CLEAR, 0));
	}

	polyline->CopyPolylineData ((coords != nullptr) ? *coords : nullptr, nValuableCoords, (arcs != nullptr) ? *arcs : nullptr, nValuableArcs, dummyNurbs, createFlags);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::operator= (const CustomPolyline2D& source) -> CustomPolyline2D&
{
	if (this == &source)
		return *this;

	if (polyline != source.polyline)
		polyline = source.polyline;
	return *this;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::operator== (const CustomPolyline2D& rightOp) const
{
	return polyline->Compare (*rightOp.polyline);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::operator!= (const CustomPolyline2D& rightOp) const
{
	return !operator== (rightOp);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetSameDirEdgeLegal (bool isSameDirEdgeLegal)
{
	if (polyline->flags.isSameDirEdgeLegal != isSameDirEdgeLegal) {
		CopyOnWrite ();
		polyline->SetSameDirEdgeLegal (isSameDirEdgeLegal);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetSameDirEdgeLegal () const
{
	return polyline->GetSameDirEdgeLegal ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetPolyFlags (GS::UInt32 polyFlags /*PolyFlags*/)
{
	DBASSERT (!((PolyFlags_IsSameDirEdgeLegal & polyFlags) && (PolyFlags_NoSameDirEdgeLegal & polyFlags)));
	if (PolyFlags_IsSameDirEdgeLegal & polyFlags && !polyline->flags.isSameDirEdgeLegal) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetSameDirEdgeLegal (true);
	}
	if (PolyFlags_NoSameDirEdgeLegal & polyFlags && polyline->flags.isSameDirEdgeLegal) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetSameDirEdgeLegal (false);
	}
	DBASSERT (!((PolyFlags_IsClosed & polyFlags) && (PolyFlags_NoClosed & polyFlags)));
	if (PolyFlags_IsClosed & polyFlags && !polyline->flags.isClosed) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetClosed (true);
	}
	if (PolyFlags_NoClosed & polyFlags && polyline->flags.isClosed) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetClosed (false);
	}
	DBASSERT (!((PolyFlags_IsSameCoord & polyFlags) && (PolyFlags_NoSameCoord & polyFlags)));
	if (PolyFlags_IsSameCoord & polyFlags && !polyline->flags.isSameCoord) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetIsSameCoord (true);
	}
	if (PolyFlags_NoSameCoord & polyFlags && polyline->flags.isSameCoord) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetIsSameCoord (false);
	}
	DBASSERT (!((PolyFlags_IsVertexUserData & polyFlags) && (PolyFlags_NoVertexUserData & polyFlags)));
	if (PolyFlags_IsVertexUserData & polyFlags && !polyline->flags.isVertexUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetIsVertexUserData (true);
	}
	if (PolyFlags_NoVertexUserData & polyFlags && polyline->flags.isVertexUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetIsVertexUserData (false);
	}
	DBASSERT (!((PolyFlags_IsEdgeUserData & polyFlags) && (PolyFlags_NoEdgeUserData & polyFlags)));
	if (PolyFlags_IsEdgeUserData & polyFlags && !polyline->flags.isEdgeUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetIsEdgeUserData (true);
	}
	if (PolyFlags_NoEdgeUserData & polyFlags && polyline->flags.isEdgeUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetIsEdgeUserData (false);
	}
	DBASSERT (!(PolyFlags_IsContourUserData & polyFlags));
	DBASSERT (!(PolyFlags_NoContourUserData & polyFlags));
	DBASSERT (!((PolyFlags_IsPolygonUserData & polyFlags) && (PolyFlags_NoPolygonUserData & polyFlags)));
	if (PolyFlags_IsPolygonUserData & polyFlags && !polyline->flags.isPolygonUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetIsPolygonUserData (true);
	}
	if (PolyFlags_NoPolygonUserData & polyFlags && polyline->flags.isPolygonUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polyline->SetIsPolygonUserData (false);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::UInt32	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetPolyFlags () const //PolyFlags
{
	GS::UInt32 flags = 0;

	if (polyline->GetSameDirEdgeLegal ())
		flags |= PolyFlags_IsSameDirEdgeLegal;
	else 
		flags |= PolyFlags_NoSameDirEdgeLegal;

	if (polyline->GetClosed ())
		flags |= PolyFlags_IsClosed;
	else 
		flags |= PolyFlags_NoClosed;

	if (polyline->GetIsSameCoord ())
		flags |= PolyFlags_IsSameCoord;
	else 
		flags |= PolyFlags_NoSameCoord;

	if (polyline->GetIsVertexUserData ())
		flags |= PolyFlags_IsVertexUserData;
	else 
		flags |= PolyFlags_NoVertexUserData;

	if (polyline->GetIsEdgeUserData ())
		flags |= PolyFlags_IsEdgeUserData;
	else 
		flags |= PolyFlags_NoEdgeUserData;

	if (polyline->GetIsPolygonUserData ())
		flags |= PolyFlags_IsPolygonUserData;
	else 
		flags |= PolyFlags_NoPolygonUserData;

	return flags;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetClosed (bool isClosed)
{
	CopyOnWrite ();
	polyline->SetClosed (isClosed);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetClosed () const
{
	return polyline->GetClosed ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DetectAndSetClosed ()
{
	CopyOnWrite ();
	return polyline->DetectAndSetClosed ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetVertexIterator (UIndex vertexIdx) const -> ConstVertexIterator
{
	DBCHECKINDEX_POLY2D (vertexIdx, 1, polyline->GetVertexNum () + 1);

	ConstPolyVertexInPolyState<CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>, VertexUserData> item (this, vertexIdx);
	return CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ConstVertexIterator (item);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetVertexIterator (const Point2D& coord) const -> ConstVertexIterator
{
	return GetVertexIterator(polyline->GetVertexIdx (coord));
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::EnumerateVertex () const -> ConstVertexIterator
{
	return GetVertexIterator (1);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::BeginVertex () const -> ConstVertexIterator
{
	return GetVertexIterator (1);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::EndVertex	() const -> ConstVertexIterator
{
	return GetVertexIterator (polyline->GetVertexNum () + 1);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::EnumerateVertex (const VertexUserData& id) const -> ConstVertexIterator
{
	ConstPolyVertexInPolyState<CustomPolyline2D, VertexUserData> item (this, id);
	return CustomPolyline2D::ConstVertexIterator (item);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetEdgeIterator (UIndex edgeIdx) const -> ConstEdgeIterator
{
	DBCHECKINDEX_POLY2D (edgeIdx, 1, polyline->GetEdgeNum () + 1);

	ConstPolyEdgeInPolyState<CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>, EdgeUserData> item (this, edgeIdx);
	return CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ConstEdgeIterator (item);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::EnumerateEdge () const -> ConstEdgeIterator
{
	return GetEdgeIterator (1);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::BeginEdge () const -> ConstEdgeIterator
{
	return GetEdgeIterator (1);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::EndEdge () const -> ConstEdgeIterator
{
	return GetEdgeIterator (polyline->GetEdgeNum() + 1);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::EnumerateEdge (const EdgeUserData& id) const -> ConstEdgeIterator
{
	ConstPolyEdgeInPolyState<CustomPolyline2D, EdgeUserData> item (this, id);
	return CustomPolyline2D::ConstEdgeIterator (item);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ResetUserData ()
{
	CopyOnWrite ();
	polyline->ResetUserData ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetPolyUserData (const PolygonUserData& polyId)
{
	CopyOnWrite ();
	polyline->SetUserData (&polyId);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const PolygonUserData&	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetPolyUserData () const
{
	return *polyline->GetUserData ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetVertexDefaultUserData (const VertexUserData& userData)
{
	CopyOnWrite ();
	polyline->SetVertexDefaultUserData (userData);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const VertexUserData&	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetVertexDefaultUserData () const
{
	return polyline->GetVertexDefaultUserData ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
USize	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetVertexNum () const
{
	return polyline->GetVertexNum ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetVertex (const ConstVertexIterator& vertexIterator) const -> Vertex
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	Vertex vertex;
	vertex.SetCoord (polyline->GetCoord (vertexIterator.GetItem ().GetIndex ()));
	vertex.SetPolyVertexUserData (*polyline->GetVertexUserData (vertexIterator.GetItem ().GetIndex ()));
	return vertex;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const Point2D&	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetCoord (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	return polyline->GetCoord (vertexIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const VertexUserData&	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetVertexUserData (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	return *polyline->GetVertexUserData (vertexIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetVertexUserData (const ConstVertexIterator& vertexIterator, const VertexUserData& vertexId)
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	CopyOnWrite ();
	polyline->SetVertexUserData (vertexIterator.GetItem ().GetIndex (), &vertexId);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetEdgeDefaultUserData (const EdgeUserData& userData)
{
	CopyOnWrite ();
	polyline->SetEdgeDefaultUserData (userData);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const EdgeUserData&		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetEdgeDefaultUserData () const
{
	return polyline->GetEdgeDefaultUserData ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
USize	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetEdgeNum () const
{
	return polyline->GetEdgeNum ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetEdge (const ConstEdgeIterator& edgeIterator) const -> Edge
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	Edge edge;
	edge.SetArcAngle (polyline->GetArcAngle (edgeIterator.GetItem ().GetIndex ()));
	edge.SetPolyEdgeUserData (*polyline->GetEdgeUserData (edgeIterator.GetItem ().GetIndex ()));
	return edge;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetSector (const ConstEdgeIterator& edgeIterator, Sector& sect, GenArc& genArc) const
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	return polyline->GetSector (edgeIterator.GetItem ().GetIndex (), sect, genArc);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetSector (const ConstEdgeIterator& edgeIterator, Point2D& begC, Point2D& endC, double& angle) const
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	return polyline->GetSector (edgeIterator.GetItem ().GetIndex (), begC, endC, angle);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::Optional<Sector>	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetSector (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	return polyline->GetSector (edgeIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::Optional<GenArc>	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetArc (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	return polyline->GetArc (edgeIterator.GetItem ().GetIndex ());
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const EdgeUserData&		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetEdgeUserData (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	return *polyline->GetEdgeUserData (edgeIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetEdgeUserData (const ConstEdgeIterator& edgeIterator, const EdgeUserData& edgeId)
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	CopyOnWrite ();
	polyline->SetEdgeUserData (edgeIterator.GetItem ().GetIndex (), &edgeId);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ConstVertexIterator CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetBeginVertex (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	return GetVertexIterator (polyline->GetBeginVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ConstVertexIterator CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetEndVertex (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	return GetVertexIterator (polyline->GetEndVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ConstEdgeIterator CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetNextEdge (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	return GetEdgeIterator (polyline->GetNextEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ConstEdgeIterator CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetPrevEdge (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	return GetEdgeIterator (polyline->GetPrevEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::IsEmpty () const
{
	return polyline->IsEmpty ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::HasArcs () const
{
	return polyline->nArcs> 0;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Clear ()
{
	CopyOnWrite ();
	polyline->Clear ();
//	polyline = emptyPolyline;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::IsABox () const
{
	return polyline->IsABox ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Read (GS::IChannel& ic)
{
	typename CorePolyline2DType::Flags flags;
	polyline = new CorePolyline2DType (flags);
	return polyline->Read (ic);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Write (GS::OChannel& oc) const
{
	return polyline->Write (oc);
}

extern GEOMETRY_DLL_EXPORT const char*		XMLPolyline_Tag_Polyline2D;

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReadXML	(GS::XMLIChannel& ic)
{
	GS::XMLITag tag (ic, XMLPolyline_Tag_Polyline2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		GS::ClassVersion currentClassVersion;
		ic.ReadXMLVersionAttr (currentClassVersion);
		//currentClassVersion.ReadXML (ic);
		DBASSERT (currentClassVersion == Polyline2DPrivate::classInfo.GetVersion ());
	}

	polyline = CorePolyline2DType::ReadXMLAndCreate (ic);
	if (polyline == nullptr)
		throw GeometryIllegalArgumentException ("Can't Read XML file!!!", __FILE__, __LINE__);

	return ic.GetErrorStatus () == GS::XMLIChannel::Ok ? NoError : Error;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::WriteXML (GS::XMLOChannel& oc) const
{
	GSErrCode errCode = NoError;
	GS::XMLTag tag (oc, XMLPolyline_Tag_Polyline2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		oc.WriteXMLVersionAttr (Polyline2DPrivate::classInfo.GetVersion ());
		//GetClassVersion ().WriteXML (oc);
	}

	errCode = polyline->WriteXML (oc);
	if (errCode != NoError)
		return errCode;
	return oc.GetErrorStatus () == GS::XMLOChannel::Ok ? NoError : Error;
}

//Calculate
template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const Box2DData& CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetBoundBox () const
{
//	if (polyline->IsEmpty ())
//		return emptyPolyline->GetBoundBox ();
	return polyline->GetBoundBox ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
Point2D CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetCenter () const
{
	Box2DData polyBoundBox = polyline->GetBoundBox ();
	Point2D centerC  = Point2D ((polyBoundBox.xMin + polyBoundBox.xMax) / 2.0, (polyBoundBox.yMin + polyBoundBox.yMax) / 2.0);
	return centerC;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CalcArea () const 
{ 
	return polyline->CalcArea (); 
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::IsClockwise () const 
{ 
	return polyline->IsClockwise (); 
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CalcLength () const
{
	return polyline->CalcLength ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CalcMaxVertexFillet (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	return polyline->CalcMaxVertexFillet (vertexIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::IsCoordOnEdge (const Point2D& c, GS::Array<ConstEdgeIterator>* edges /* = nullptr*/) const
{
	GS::Array<UIndex> edgeIndexArray;
	bool result = polyline->IsCoordOnEdge (c, edgeIndexArray);
	if (edges != nullptr) {
		if (result) {
			edges->SetCapacity (edgeIndexArray.GetSize ());
			for (auto it = edgeIndexArray.Enumerate (); it != nullptr; ++it)
				edges->Push (GetEdgeIterator (*it));
		} else {
			*edges = GS::Array<ConstEdgeIterator> ();
		}
	}
	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::Array<GS::Pair<typename CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ConstEdgeIterator, Vector2D>> CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetTangentAtPoint (const Point2D& c) const
{
	GS::Array<GS::Pair<UIndex, Vector2D>> tangents = polyline->GetTangentAtPoint (c);

	GS::Array<GS::Pair<ConstEdgeIterator, Vector2D>> result (tangents.GetSize ());
	for (auto it = tangents.Enumerate (); it != nullptr; ++it)
		result.Push (GS::Pair<ConstEdgeIterator, Vector2D> (GetEdgeIterator ((*it).first), (*it).second));

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
Point2D CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetMiddlePoint () const
{
	return polyline->GetMiddlePoint ();
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::FixArray<Point2D, 4>	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetTransformedBoundBox (const TRANMAT& tr, const TRANMAT& invTr /*= Geometry::IdentityTranMat*/) const
{
	return polyline->GetTransformedBoundBox (tr, invTr);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DistanceFromPoint (const Point2D& co, ConstEdgeIterator* edgeItOfMin /*= nullptr*/, GS::Array<bool>* filter /*= nullptr*/) const
{
	UIndex edgeIndex = 0;
	const double dist = polyline->DistanceFromPoint (co, edgeIndex, filter);
	if (edgeItOfMin != nullptr && edgeIndex != 0)
		*edgeItOfMin = GetEdgeIterator (edgeIndex);
	return dist;
}

template<class VertexUserData, class EdgeUserData, class PolygonUserData>
double CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetTurningAngleAtVertex (const ConstVertexIterator & vertexIterator) const
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	return polyline->GetTurningAngleAtVertex (vertexIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Visit (ConstVertexVisitor &visitor) const
{
	polyline->Visit (visitor);
}

//Modify polyline
template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Move (Vector2D offset)
{
	CopyOnWrite ();
	polyline->Move (offset);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::TransformPreserveArcs (const TRANMAT& tran)
{
	CopyOnWrite ();
	polyline->TransformPreserveArcs (tran);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ClearVertexIds ()
{
	CopyOnWrite ();
	polyline->ClearVertexUserDatas ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ClearEdgeIds ()
{
	CopyOnWrite ();
	polyline->ClearEdgeUserDatas ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Reverse ()
{
	CopyOnWrite ();
	polyline->Reverse ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Stretch (	const Point2D& fixPoint,
																				const Point2D& draggedPoint,
																				const Vector2D& offsetAxisX,
																				const Vector2D& offsetAxisY /*= Vector (0.0, 0.0)*/,
																				const ArcDivParams& arcDivParams /*= ArcDivParams (0.0)*/)
{
	CopyOnWrite ();
	polyline->Stretch (fixPoint, draggedPoint, offsetAxisX, offsetAxisY, arcDivParams);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Append (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polylineToAppend)
{
	CopyOnWrite ();
	polyline->Append (*polylineToAppend.polyline);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Append (const Point2D& c, const bool atEnd /*= true*/)
{
	CopyOnWrite ();
	polyline->Append (c, atEnd);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Visit (VertexVisitor &visitor)
{
	CopyOnWrite ();
	polyline->Visit (visitor);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::RotateVerticeIndices (const ConstVertexIterator& vertexToFirst)
{
	CopyOnWrite ();
	polyline->RotateVerticeIndices (vertexToFirst.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SortArcsByIndices ()
{
	CopyOnWrite ();
	polyline->SortArcsByIndices ();
}


//Create new polylines
template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran) const -> CustomPolyline2D
{
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	typename CorePolyline2DType::PolylineResult polyResult = polyline->Transform (arcDivParams, tran, newPolyline);
	return CreateResult (polyResult, newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Transform (const Polygon2DType<ContourUserData>& filterWithPolygon,
																					const ArcDivParams& arcDivParams,
																					const TRANMAT& tran,
																					bool& isTransformedAll) const -> CustomPolyline2D
{
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	typename CorePolyline2DType::PolylineResult polyResult = polyline->Transform (*filterWithPolygon.polygon, arcDivParams, tran, newPolyline, isTransformedAll);
	return CreateResult (polyResult, newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Transform (const MultiPolygon2DType<ContourUserData>& filterWithPolygon,
																					const ArcDivParams& arcDivParams,
																					const TRANMAT& tran,
																					bool& isTransformedAll) const -> CustomPolyline2D
{
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>>> filterPolygonArray;
	filterWithPolygon.GetCorePolygon2DArray (filterPolygonArray);
	typename CorePolyline2DType::PolylineResult polyResult = polyline->Transform (filterPolygonArray, arcDivParams, tran, newPolyline, isTransformedAll);
	return CreateResult (polyResult, newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SegmentUp (const ArcDivParams& arcDivParams) const -> CustomPolyline2D
{
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	typename CorePolyline2DType::PolylineResult polyResult = polyline->SegmentUp (arcDivParams, newPolyline);
	return CreateResult (polyResult, newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::EliminateArcs () const -> CustomPolyline2D
{
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	typename CorePolyline2DType::PolylineResult polyResult = polyline->EliminateArcs (newPolyline);
	return CreateResult (polyResult, newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetReversed () const -> CustomPolyline2D
{
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->Reverse (newPolyline);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::OffsetAllEdge (double offset, double* newOffset) const -> CustomPolyline2D
{
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->OffsetAllEdge (offset, newPolyline, newOffset);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::OffsetEdge (const ConstEdgeIterator& edgeIterator, double offset) const -> CustomPolyline2D
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	typename CorePolyline2DType::PolylineResult polyResult = polyline->OffsetEdge (edgeIterator.GetItem ().GetIndex (), offset, newPolyline);
	return CreateResult (polyResult, newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::MoveVertex (const ConstVertexIterator& vertexIterator, const Point2D& newPosition) const -> CustomPolyline2D
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->MoveVertex (vertexIterator.GetItem ().GetIndex (), newPosition, newPolyline);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::FilletAllVertex (const double filletRadius) const -> CustomPolyline2D
{
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->FilletAllVertex (filletRadius, newPolyline);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::FilletVertex (const ConstVertexIterator& vertexIterator, const double filletRadius) const -> CustomPolyline2D
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->FilletVertex (vertexIterator.GetItem ().GetIndex (), filletRadius, newPolyline);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ChamferAllVertex (const double chamferRadius) const -> CustomPolyline2D
{
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->ChamferAllVertex (chamferRadius, newPolyline);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ChamferVertex (const ConstVertexIterator& vertexIterator, const double chamferRadius) const -> CustomPolyline2D
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->ChamferVertex (vertexIterator.GetItem ().GetIndex (), chamferRadius, newPolyline);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::InsertVertex (const ConstEdgeIterator& edgeIterator, const Point2D& newPosition) const -> CustomPolyline2D
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->InsertVertex (edgeIterator.GetItem ().GetIndex (), newPosition, newPolyline);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::InsertVertexOnPolyline (const Point2D& newPosition,
																								 const ConstEdgeIterator& edgeIterator,
																								 UIndex* vertexIndex /*= nullptr*/) const -> CustomPolyline2D
{
	CustomPolyline2D result;
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	UIndex vertInd = 0;
	polyline->InsertVertexOnPolyline (newPosition, edgeIterator.GetItem ().GetIndex (), newPolyline, vertInd);
	result.polyline = newPolyline;
	if (vertexIndex != nullptr)
		*vertexIndex = vertInd;

	return result;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DeleteVertex (const ConstVertexIterator& vertexIterator) const -> CustomPolyline2D
{
	DBASSERT (vertexIterator.GetTarget ()->polyline == polyline);
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->DeleteVertex (vertexIterator.GetItem ().GetIndex (), newPolyline);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetEdgeAngle (const ConstEdgeIterator& edgeIterator, double edgeAngle) const -> CustomPolyline2D
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->SetEdgeAngle (edgeIterator.GetItem ().GetIndex (), edgeAngle, newPolyline);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReplaceEdge (const ConstEdgeIterator& edgeIterator,
																					  const GenArc& genArc,
																					  const ArcDivParams& arcDivParams) const -> CustomPolyline2D
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->ReplaceEdge (edgeIterator.GetItem ().GetIndex (), genArc, arcDivParams, newPolyline);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DeleteEdge (const ConstEdgeIterator& edgeIterator, CustomPolyline2D& result) const
{
	DBASSERT (edgeIterator.GetTarget ()->polyline == polyline);
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	bool success = polyline->DeleteEdge (edgeIterator.GetItem ().GetIndex (), newPolyline);
	result.polyline = newPolyline;
	return success;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ShiftPolyline (double length, bool firstEdge) const -> CustomPolyline2D
{
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	polyline->ShiftPolyline (length, firstEdge, newPolyline);
	return CustomPolyline2D (newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CutAtVertices (const GS::Array<ConstVertexIterator>& vertexIteratorArray) const  -> MultiPolyline2DType
{
	GS::Array<UIndex> vertexIdxArray;
	for (UIndex i = 0; i < vertexIteratorArray.GetSize (); i++) {
		DBASSERT (vertexIteratorArray[i].GetTarget ()->polyline == polyline);
		vertexIdxArray.Push (vertexIteratorArray[i].GetItem ().GetIndex ());
	}
	GS::Array<GS::SharedPtr<CorePolyline2DType>> polylineArray;
	typename CorePolyline2DType::PolylineResult polyResult = polyline->CutAtVertices (vertexIdxArray, polylineArray);
	return CreateResult (polyResult, polylineArray);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Cut (const HalfPlane2DData& cutline, 
																			  bool* fullin /*= nullptr*/, 
																			  GS::Int32* wrcode /*= nullptr*/) const -> MultiPolyline2DType
{
	GS::Array<GS::SharedPtr<CorePolyline2DType>> polylineArray;
	typename CorePolyline2DType::PolylineResult polyResult = polyline->Cut (cutline, polylineArray, fullin, wrcode);
	return CreateResult (polyResult, polylineArray);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Strip (const HalfPlane2DData& cutline1, 
																				const HalfPlane2DData& cutline2, 
																				GS::Int32* wrcode /*= nullptr*/) const -> MultiPolyline2DType
{
	GS::Array<GS::SharedPtr<CorePolyline2DType>> polylineArray;
	typename CorePolyline2DType::PolylineResult polyResult = polyline->Strip (cutline1, cutline2, polylineArray, wrcode);
	return CreateResult (polyResult, polylineArray);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Clip (const Box2DData& box, GS::Int32* wrcode /*= nullptr*/) const -> MultiPolyline2DType
{
	GS::Array<GS::SharedPtr<CorePolyline2DType>> polylineArray;
	typename CorePolyline2DType::PolylineResult polyResult = polyline->Clip (box, polylineArray, wrcode);
	return CreateResult (polyResult, polylineArray);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
auto	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CutPiece (const CutParam& t1, const CutParam& t2) const -> CustomPolyline2D
{
	GS::SharedPtr<CorePolyline2DType> newPolyline;
	typename CorePolyline2DType::PolylineResult polyResult = polyline->CutPiece (t1, t2, newPolyline);
	return CreateResult (polyResult, newPolyline);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::Array<CutParam>		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CutPointToCutParam (const Point2D& cutPoint) const
{
	return polyline->CutPointToCutParam (cutPoint);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
Point2D		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CutParamToCutPoint (const CutParam& cutParam) const		
{
	return polyline->CutParamToCutPoint (cutParam);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CutParamToDistance (const CutParam& cutParam) const
{
	return polyline->CutParamToDistance (cutParam);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CutParam	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DistanceToCutParam (double distance) const
{
	return polyline->DistanceToCutParam (distance);
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylinePointPosition	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PointPosition (const Point2D& sidePoint) const
{
	typename CorePolyline2DType::PolylinePointPosition	pointposition = polyline->PointPosition (sidePoint);
	PolylinePointPosition retval;
	switch (pointposition) {
		case CorePolyline2DType::PointOnLeftSide:	retval = PointOnLeftSide; break;
		case CorePolyline2DType::PointOnPolyline:	retval = PointOnPolyline; break;
		case CorePolyline2DType::PointOnRightSide:
		default:
			retval = PointOnRightSide; break;
	};
	return retval;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template<class EdgeUserDataComparator>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::RemoveSameDirEdgesOnlyWithSameUserData (CustomPolyline2D& poly, const EdgeUserDataComparator& comparator)
{
	poly.CopyOnWrite ();
	poly.polyline->RemoveSameDirEdgesOnlyWithSameUserData (comparator);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::RemoveSameDirEdgesOnlyWithSameUserData (CustomPolyline2D& poly)
{
	poly.CopyOnWrite ();
	poly.polyline->RemoveSameDirEdgesOnlyWithSameUserData ();
}

// Debug
template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Print	(GS::OChannel& oc) const
{
	return polyline->Print (oc);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PrintDebug () const
{
	return polyline->PrintDebug ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PrintDebugXML () const
{
	return polyline->PrintDebugXML ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Check (PolyCheckFlags checkFlags, double coordUpperRange) const
{
	return polyline->Check (checkFlags, nullptr, coordUpperRange);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
PolyRepairResult	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CheckAndRepair (PolyCheckFlags checkFlags, double coordUpperRange)
{
	PolyCheckFlags errorType;
	PolyRepairResult result;
	result.succeeded = true;
	result.modified = false;

	while (!polyline->Check (checkFlags, &errorType, coordUpperRange)) {
		if ((errorType & checkFlags) == 0) {
			result.succeeded = false;
			return result;
		} else {
			CopyOnWrite ();
			PolyRepairResult resultTemp = polyline->Repair (errorType);
			result.modified = (result.modified || resultTemp.modified);
			if (!resultTemp.succeeded) {
				result.succeeded = false;
				return result;
			}
		}
	}

	return result;
}

} //namespace Geometry

//************************************** MultiPolyline2D ***********************************

namespace Geometry {


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SegmentUp (const ArcDivParams& arcDivParams)
{
	GS::Array<GS::SharedPtr<CorePolyline2DType>> corePolylineArray;
	GetCorePolyline2DArray (corePolylineArray);
	this->Clear ();
	GS::SharedPtr<CorePolyline2DType> firstParam;
	for (UIndex polyIdx = 0; polyIdx < corePolylineArray.GetSize (); polyIdx++) {
		GS::SharedPtr<CorePolyline2DType> result;
		typename CorePolyline2DType::PolylineResult polyResult = corePolylineArray[polyIdx]->SegmentUp (arcDivParams, result);
		PushResults (polyResult, corePolylineArray[polyIdx], result);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran)
{
	bool isPreserveArc = Geometry::TMIsPreserveArc (tran);
	if (isPreserveArc) {
		for (UIndex idx = 0; idx < this->GetSize(); idx++) {
			this->Get(idx).TransformPreserveArcs (tran);
		}
	} else {
		GS::Array<GS::SharedPtr<CorePolyline2DType>> corePolylineArray;
		GetCorePolyline2DArray (corePolylineArray);
		this->Clear ();
		GS::SharedPtr<CorePolyline2DType> firstParam;
		for (UIndex polyIdx = 0; polyIdx < corePolylineArray.GetSize (); polyIdx++) {
			GS::SharedPtr<CorePolyline2DType> result;
			typename CorePolyline2DType::PolylineResult polyResult = corePolylineArray[polyIdx]->Transform (arcDivParams, tran, result);
			PushResults (polyResult, corePolylineArray[polyIdx], result);
		}
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Read (GS::IChannel& ic)
{
	NULL_REF_CHECK (ic);

	this->Clear ();

	GS::InputFrame frame (ic, MultiPolyline2DPrivate::classInfo);
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

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Write (GS::OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, MultiPolyline2DPrivate::classInfo);

	GSErrCode errorCode = oc.Write (this->GetSize ());

	for (UIndex i = 0; i < this->GetSize () && errorCode == NoError; i++)
		errorCode = this->Get (i).Write (oc);

	return errorCode;
}

extern	GEOMETRY_DLL_EXPORT const char*		XMLPolyline_Tag_MultiPolyline2D;
extern	GEOMETRY_DLL_EXPORT const char*		XMLPolyline_Attr_PolyNum;

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReadXML	(GS::XMLIChannel& ic)
{
	GSErrCode errCode = NoError;
	GS::XMLITag tagMultiPolyline2D (ic, XMLPolyline_Tag_MultiPolyline2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		GS::ClassVersion currentClassVersion;
		ic.ReadXMLVersionAttr (currentClassVersion);
		//currentClassVersion.ReadXML (ic);
		DBASSERT (currentClassVersion == MultiPolyline2DPrivate::classInfo.GetVersion ());
	}

	USize newSize = 0;
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLPolyline_Attr_PolyNum, newSize);

	GS::UniString tokenName;
	while (tagMultiPolyline2D.IsNextChildStartTag (tokenName) && (errCode == NoError)) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> newPoly;
		errCode = newPoly.ReadXML (ic);
		this->Push (newPoly);
	}

	DBASSERT (newSize == this->GetSize ());

	if (errCode != NoError)
		return errCode;
	return ic.GetErrorStatus () == GS::XMLIChannel::Ok ? NoError : Error;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::WriteXML (GS::XMLOChannel& oc) const
{
	GSErrCode errCode = NoError;
	GS::XMLTag tagMultiPolyline2D (oc, XMLPolyline_Tag_MultiPolyline2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		oc.WriteXMLVersionAttr (MultiPolyline2DPrivate::classInfo.GetVersion ());
		//GetClassVersion ().WriteXML (oc);
	}

	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLPolyline_Attr_PolyNum, this->GetSize ());

	for (UIndex idx = 0; idx < this->GetSize() && errCode == NoError; idx++) {
		errCode = this->Get (idx).WriteXML (oc);
	}

	if (errCode != NoError)
		return errCode;
	return oc.GetErrorStatus () == GS::XMLOChannel::Ok ? NoError : Error;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PopLargest ()
{
	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> actPoly;
	if (this->GetSize () == 0) {
		DBBREAK (); //lehet, hogy ez nem is hiba? Ezt el kellene donteni nem?
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
		DBASSERT (act>= 0.);
		if (max < act) {
			max = act;
			argmax = idx;
		}
	}
	actPoly = this->Get(argmax);
	this->Delete (argmax);
	return actPoly;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
Box2DData CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetBoundBox () const
{
	Box2DData box;
	if (this->GetSize() == 0) {
		DBBREAK ();
		return box;
	}
	else if (this->GetSize() == 1)
		return this->Get (0).GetBoundBox ();

	box = this->Get (0).GetBoundBox ();
	for (UIndex idx = 1; idx < this->GetSize(); idx++) {
		Box2DData elemBox = this->Get (idx).GetBoundBox ();
		UnionBox (&elemBox, &box);
	}
	return box;
}
    
template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::~CustomMultiPolyline2D ()
{
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetCorePolyline2DArray (GS::Array<GS::SharedPtr<CorePolyline2DType>>& polylineArray) const
{
	for (UIndex idx = 0; idx < this->GetSize(); idx++) {
		polylineArray.Push (this->Get(idx).polyline);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PushResults ( typename CorePolyline2DType::PolylineResult polyResult,
	const GS::SharedPtr<CorePolyline2DType>& thisPoly,
	const GS::SharedPtr<CorePolyline2DType>& newPolyline)
{
	switch (polyResult) {
	case CorePolyline2DType::NewPolylines:
		this->Push (newPolyline);
		break;
	case CorePolyline2DType::ResultSameAsThis:
		this->Push (thisPoly);
		break;
	case CorePolyline2DType::EmptyPolyline:
		break;
	default:
		DBBREAK ();
		break;
	}
}

} //Geometry namespace

#endif //GEOMETRY_POLYLINE2D_HPP
