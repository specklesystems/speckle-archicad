// *****************************************************************************
// Conversions between Polygon2DData and Polygon2D.
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// [SG compatible]
// *****************************************************************************
#if !defined (POLYGON2DDATACONV_H)
#define POLYGON2DDATACONV_H

#pragma once

#include "GeometricDefinitions.h"
#include "Poly2D.hpp"
#include "Polygon2D.hpp"
#include "Polyline2D.hpp"
#include "Polyline2DOperations.h"
#include "IrregularPolygon2D.hpp"
#include "Polygon2DData.h"

struct TRANMAT;


namespace GS {
	template<class T> class VAArray;
}


namespace Geometry {

template<class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CreateMultiPoly (CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& target,
					const typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ContourDescriptionArray& contours, UInt32 flags /*PolyFlags*/)
{
	try {
		target = CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (flags, contours);
	} catch (GeometryException&) {
		target.Clear ();
	}
}		// CreateMultiPoly


template<class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CreateMultiPoly (CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& target,
			const typename CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ContourDescriptionArray& contours, UInt32 flags /*PolyFlags*/)
{
	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmp =
		CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (flags, contours);

	target.Push (tmp);
}		// CreateMultiPoly

template<class VertexUserData, class EdgeUserData, class PolygonUserData>
void CreateMultiPL (CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& target,
	GS::Array<typename CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ContourDescription>& contours, UInt32 flags /*PolyFlags*/)
{
	for (UIndex i = 0; i < contours.GetSize (); ++i) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> tmp =
			CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (flags, contours [i]);
		target.Push (tmp);
	}
}		// CreateMultiPL

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UInt32 GetPolygon2DFlagsFromPolygon2DData (const Polygon2DData& source, UInt32& flags)
{
	UInt32 flagsLocal = 0;
	if (flags == PolyFlags_Default) {
		if (source.status.isSameDirEdgeLegal)
			flagsLocal |= PolyFlags_IsSameDirEdgeLegal;
		else
			flagsLocal |= PolyFlags_NoSameDirEdgeLegal;

		if (source.status.force64BitPrecision)
			flagsLocal |= PolyFlags_Force64BitPrecision;
		else
			flagsLocal |= PolyFlags_NoForce64BitPrecision;
	
		if (source.vertexInfos != nullptr && source.sizeOfVertexInfo == sizeof (VertexUserData))
			flagsLocal |= PolyFlags_IsVertexUserData;
		else
			flagsLocal |= PolyFlags_NoVertexUserData;

		if (source.inhEdgeInfos != nullptr && source.sizeOfInhEdgeInfo == sizeof (EdgeUserData))
			flagsLocal |= PolyFlags_IsEdgeUserData;
		else
			flagsLocal |= PolyFlags_NoEdgeUserData;

		if (source.contourInfos != nullptr && source.sizeOfContourInfo == sizeof (ContourUserData))
			flagsLocal |= PolyFlags_IsContourUserData;
		else
			flagsLocal |= PolyFlags_NoContourUserData;

		if (source.inhPolygonInfo != nullptr && source.sizeOfInhPolygonInfo == sizeof (PolygonUserData))
			flagsLocal |= PolyFlags_IsPolygonUserData;
		else
			flagsLocal |= PolyFlags_NoPolygonUserData;
	} else {
		// check if handles are existing
		if ((flags & PolyFlags_IsVertexUserData) && (source.vertexInfos == nullptr || source.sizeOfVertexInfo != sizeof (VertexUserData))) {
			DBBREAK ();
			flags ^= PolyFlags_IsVertexUserData;
			if ((flags & PolyFlags_NoVertexUserData) != 0)
				flags ^= PolyFlags_NoVertexUserData;
		}
		if ((flags & PolyFlags_IsEdgeUserData) && (source.inhEdgeInfos == nullptr || source.sizeOfInhEdgeInfo != sizeof (EdgeUserData))) {
			DBBREAK ();
			flags ^= PolyFlags_IsEdgeUserData;
			if ((flags & PolyFlags_NoEdgeUserData) != 0)
				flags ^= PolyFlags_NoEdgeUserData;
		}
		if ((flags & PolyFlags_IsContourUserData) && (source.contourInfos == nullptr || source.sizeOfContourInfo != sizeof (ContourUserData))) {
			DBBREAK ();
			flags ^= PolyFlags_IsContourUserData;
			if ((flags & PolyFlags_NoContourUserData) != 0)
				flags ^= PolyFlags_NoContourUserData;
		}
		if ((flags & PolyFlags_IsPolygonUserData) && (source.inhPolygonInfo == nullptr || source.sizeOfInhPolygonInfo != sizeof (PolygonUserData))) {
			DBBREAK ();
			flags ^= PolyFlags_IsPolygonUserData;
			if ((flags & PolyFlags_NoPolygonUserData) != 0)
				flags ^= PolyFlags_NoPolygonUserData;
		}
		flagsLocal = flags;
	}
	return flagsLocal;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UInt32 GetPolyline2DFlagsFromPolygon2DData (const Polygon2DData& source, UInt32& flags)
{
	UInt32 flagsLocal = 0;
	if (flags == PolyFlags_Default) {
		if (source.status.isSameDirEdgeLegal)
			flagsLocal |= PolyFlags_IsSameDirEdgeLegal;
		else
			flagsLocal |= PolyFlags_NoSameDirEdgeLegal;

		if (source.status.force64BitPrecision)
			flagsLocal |= PolyFlags_Force64BitPrecision;
		else
			flagsLocal |= PolyFlags_NoForce64BitPrecision;

		if (source.vertexInfos != nullptr && source.sizeOfVertexInfo == sizeof (VertexUserData))
			flagsLocal |= PolyFlags_IsVertexUserData;
		else
			flagsLocal |= PolyFlags_NoVertexUserData;

		if (source.inhEdgeInfos != nullptr && source.sizeOfInhEdgeInfo == sizeof (EdgeUserData))
			flagsLocal |= PolyFlags_IsEdgeUserData;
		else
			flagsLocal |= PolyFlags_NoEdgeUserData;

		if (source.inhPolygonInfo != nullptr && source.sizeOfInhPolygonInfo == sizeof (PolygonUserData))
			flagsLocal |= PolyFlags_IsPolygonUserData;
		else
			flagsLocal |= PolyFlags_NoPolygonUserData;
	} else {
		// check if handles are existing
		if ((flags & PolyFlags_IsVertexUserData) && (source.vertexInfos == nullptr || source.sizeOfVertexInfo != sizeof (VertexUserData))) {
			DBBREAK ();
			flags ^= PolyFlags_IsVertexUserData;
			if ((flags & PolyFlags_NoVertexUserData) != 0)
				flags ^= PolyFlags_NoVertexUserData;
		}
		if ((flags & PolyFlags_IsEdgeUserData) && (source.inhEdgeInfos == nullptr || source.sizeOfInhEdgeInfo != sizeof (EdgeUserData))) {
			DBBREAK ();
			flags ^= PolyFlags_IsEdgeUserData;
			if ((flags & PolyFlags_NoEdgeUserData) != 0)
				flags ^= PolyFlags_NoEdgeUserData;
		}
		if ((flags & PolyFlags_IsContourUserData) && (source.contourInfos == nullptr || source.sizeOfContourInfo != sizeof (ContourUserData))) {
			DBBREAK ();
			flags ^= PolyFlags_IsContourUserData;
			if ((flags & PolyFlags_NoContourUserData) != 0)
				flags ^= PolyFlags_NoContourUserData;
		}
		if ((flags & PolyFlags_IsPolygonUserData) && (source.inhPolygonInfo == nullptr || source.sizeOfInhPolygonInfo != sizeof (PolygonUserData))) {
			DBBREAK ();
			flags ^= PolyFlags_IsPolygonUserData;
			if ((flags & PolyFlags_NoPolygonUserData) != 0)
				flags ^= PolyFlags_NoPolygonUserData;
		}
		flagsLocal = flags;
	}
	return flagsLocal;
}

template <typename PolyType, typename MultiPolyType, class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void ConvertPolygon2DDataToPolygon2DUntyped (MultiPolyType& target, const Polygon2DData& source, UInt32 flags /*PolyFlags*/)
{
	target = MultiPolyType ();
	UInt32 flagsLocal = GetPolygon2DFlagsFromPolygon2DData<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (source, flags);

	const Point2D*			coords		= *source.vertices;
	const PolyArcRec*		arcs		= source.arcs != nullptr ? (*source.arcs) + 1 : nullptr;
	const UIndex*			spEnds		= *source.contourEnds;
	const ContourUserData*	contourIds	= (flagsLocal & PolyFlags_IsContourUserData) ? reinterpret_cast<const ContourUserData*> (*source.contourInfos) : nullptr;
	const VertexUserData*	vertIds		= (flagsLocal & PolyFlags_IsVertexUserData)	 ? reinterpret_cast<const VertexUserData*> (*source.vertexInfos)   : nullptr;
	const EdgeUserData*		edgeIds		= (flagsLocal & PolyFlags_IsEdgeUserData)	 ? reinterpret_cast<const EdgeUserData*> (*source.inhEdgeInfos)    : nullptr;
	typename PolyType::ContourDescriptionArray contours;
	typedef typename PolyType::ContourDescription PolyTypeContourDescription;
	typedef typename PolyType::Segment PolyTypeSegment;
	for (UIndex i = 1; i <= source.nContours; i++) {
		UIndex first = spEnds[i - 1] + 1;
		UIndex last = spEnds[i] - 1;		// uj polygonban nincs vertexduplazas
		contours.Push (PolyTypeContourDescription ());
		if (contourIds != nullptr)
			contours[i - 1].SetPolyContourUserData (contourIds[i]);
		for (UIndex j = first; j <= last; j++) {
			typename PolyType::Vertex vertex (coords[j]);
			if (vertIds != nullptr)
				vertex.SetPolyVertexUserData (vertIds[j]);
			double angle = 0.0;
			Int32 arcIndex = FindArc (arcs, source.nArcs, j);
			if (arcIndex >= 0)
				angle = arcs[arcIndex].arcAngle;
			typename PolyType::Edge edge (angle);
			if (edgeIds != nullptr)
				edge.SetPolyEdgeUserData (edgeIds[j]);
			contours[i - 1].GetSegmentListRef ().Push (PolyTypeSegment (vertex, edge));
		}
	}
	CreateMultiPoly (target, contours, flagsLocal);

	for (UIndex j = 0; j < target.GetSize (); j++) {
		if (flagsLocal & PolyFlags_IsPolygonUserData)
			target[j].SetPolyUserData (*reinterpret_cast<const PolygonUserData*> (*source.inhPolygonInfo));
		if (vertIds != nullptr && source.defaultVertexInfo != nullptr)
			target[j].SetVertexDefaultUserData (*reinterpret_cast<const VertexUserData*>(*source.defaultVertexInfo));
		if (edgeIds != nullptr && source.defaultInhEdgeInfo != nullptr)
			target[j].SetEdgeDefaultUserData (*reinterpret_cast<const EdgeUserData*>(*source.defaultInhEdgeInfo));
		if (contourIds != nullptr && source.defaultContourInfo != nullptr)
			target[j].SetContourDefaultUserData (*reinterpret_cast<const ContourUserData*>(*source.defaultContourInfo));
	}
}		// ConvertPolygon2DDataToPolygon2DUntyped

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void ConvertPolygon2DDataToPolyline2DUntyped (MultiPolyline2D& target, const Polygon2DData& source, UInt32 flags /*PolyFlags*/)
{
	target = MultiPolyline2D ();
	UInt32 flagsLocal = GetPolyline2DFlagsFromPolygon2DData<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (source, flags);

	const Point2D*			coords		= *source.vertices;
	const PolyArcRec*		arcs		= source.arcs != nullptr ? (*source.arcs) + 1 : nullptr;
	const UIndex*			spEnds		= *source.contourEnds;
	const ContourUserData*	contourIds	= (flagsLocal & PolyFlags_IsContourUserData) ? reinterpret_cast<const ContourUserData*> (*source.contourInfos) : nullptr;
	const VertexUserData*	vertIds		= (flagsLocal & PolyFlags_IsVertexUserData)	 ? reinterpret_cast<const VertexUserData*> (*source.vertexInfos)   : nullptr;
	const EdgeUserData*		edgeIds		= (flagsLocal & PolyFlags_IsEdgeUserData)	 ? reinterpret_cast<const EdgeUserData*> (*source.inhEdgeInfos)    : nullptr;
	GS::Array<Polyline2D::ContourDescription> contours;
	typedef Polyline2D::ContourDescription PolyTypeContourDescription;
	typedef Polyline2D::Segment PolyTypeSegment;
	for (UIndex i = 1; i <= source.nContours; i++) {
		bool closed = IsEqualCoord (coords[1], coords[spEnds[i]], EPS);
		UIndex first = spEnds[i - 1] + 1;
		UIndex last = closed ? spEnds[i] - 1 : spEnds[i];		// uj polygonban nincs vertexduplazas
		contours.Push (PolyTypeContourDescription ());
		if (contourIds != nullptr)
			contours[i - 1].SetPolyContourUserData (contourIds[i]);
		for (UIndex j = first; j <= last; j++) {
			Polyline2D::Vertex vertex (coords[j]);
			if (vertIds != nullptr)
				vertex.SetPolyVertexUserData (vertIds[j]);
			double angle = 0.0;
			Int32 arcIndex = FindArc (arcs, source.nArcs, j);
			if (arcIndex >= 0)
				angle = arcs[arcIndex].arcAngle;
			else if (j == last && !closed)
				angle = INF;  //zartnal ez nem kell
			typename Polyline2D::Edge edge (angle);
			if (edgeIds != nullptr)
				edge.SetPolyEdgeUserData (edgeIds[j]);
			contours[i - 1].GetSegmentListRef ().Push (PolyTypeSegment (vertex, edge));
		}
		if (closed)
			flagsLocal |= PolyFlags_IsClosed;
		else
			flagsLocal |= PolyFlags_NoClosed;
	}
	CreateMultiPL (target, contours, flagsLocal);

	for (UIndex j = 0; j < target.GetSize (); j++) {
		if (flagsLocal & PolyFlags_IsPolygonUserData)
			target[j].SetPolyUserData (*reinterpret_cast<const PolygonUserData*> (*source.inhPolygonInfo));
		if (vertIds != nullptr && source.defaultVertexInfo != nullptr)
			target[j].SetVertexDefaultUserData (*reinterpret_cast<const VertexUserData*>(*source.defaultVertexInfo));
		if (edgeIds != nullptr && source.defaultInhEdgeInfo != nullptr)
			target[j].SetEdgeDefaultUserData (*reinterpret_cast<const EdgeUserData*>(*source.defaultInhEdgeInfo));
//		if (contourIds != nullptr && source.defaultContourInfo != nullptr)
//			target[j].SetContourDefaultUserData (*reinterpret_cast<const ContourUserData*>(*source.defaultContourInfo));
	}
}		// ConvertPolygon2DDataToPolyline2DUntyped

GEOMETRY_DLL_EXPORT
void ConvertPolygon2DDataToPolygon2D (MultiPolygon2D& target, const Polygon2DData& source, UInt32 flags = PolyFlags_Default);


GEOMETRY_DLL_EXPORT
void ConvertPolygon2DDataToPolygon2D (IrregularPolygon2D& target, const Polygon2DData& source, UInt32 flags = PolyFlags_Default);

GEOMETRY_DLL_EXPORT
void ConvertPolygon2DDataToPolyline2D (Polyline2D& target, const Polygon2DData& source, UInt32 flags = PolyFlags_Default);


template <typename PolyType, class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void ConvertPolygon2DToPolygon2DDataUntyped (Polygon2DData& target, const PolyType& source)
{
	//DBCHECKCOREPOLY2DDATA (polygon);

	FreePolygon2DData (&target);
	InitPolygon2DData (&target);
	if (source.IsEmpty ())
		return;

	const UInt32 nVertex = source.GetVertexNum () + source.GetContourNum ();

	UInt32 polyFlags = source.GetPolyFlags ();
	bool hasVertexUserData = (polyFlags & PolyFlags_IsVertexUserData) > 0;
	bool hasEdgeUserData = (polyFlags & PolyFlags_IsEdgeUserData) > 0;
	bool hasContourUserData = (polyFlags & PolyFlags_IsContourUserData) > 0;
	bool hasPolygonUserData = (polyFlags & PolyFlags_IsPolygonUserData) > 0;

	try {
		target.vertices = reinterpret_cast<Point2D**> (BMXhAllClear ((nVertex + 1) * sizeof (Point2D)));
		target.nVertices = nVertex;
		target.nArcs = 0;
		//if (source.HasArcs ())		hogy kompatibilis legyek az eddigi Convert-tel! de szerintem nem jo igy!
			target.arcs = reinterpret_cast<PolyArcRec**> (BMXhAllClear ((target.nArcs + 1) * sizeof (PolyArcRec)));

		target.contourEnds = reinterpret_cast<UIndex**> (BMXhAllClear ((source.GetContourNum () + 1) * sizeof (UIndex)));
		target.nContours = source.GetContourNum ();

		target.sizeOfVertexInfo = hasVertexUserData ? sizeof (VertexUserData) : 0;
		if (hasVertexUserData) {
			target.vertexInfos = BMXhAllClear ((nVertex + 1) * target.sizeOfVertexInfo);
			target.defaultVertexInfo = BMXhAllClear (1 * target.sizeOfVertexInfo);
			const VertexUserData&	defaultVertexInfo = source.GetVertexDefaultUserData ();
			BNCopyMemory (*target.defaultVertexInfo, &defaultVertexInfo, target.sizeOfVertexInfo);
		}

		target.sizeOfInhEdgeInfo = hasEdgeUserData ? sizeof (EdgeUserData) : 0;
		if (hasEdgeUserData) {
			target.inhEdgeInfos = BMXhAllClear ((nVertex + 1) * target.sizeOfInhEdgeInfo);
			target.defaultInhEdgeInfo = BMXhAllClear (1 * target.sizeOfInhEdgeInfo);
			const EdgeUserData&	defaultEdgeInfo = source.GetEdgeDefaultUserData ();
			BNCopyMemory (*target.defaultInhEdgeInfo, &defaultEdgeInfo, target.sizeOfInhEdgeInfo);
		}

		target.sizeOfContourInfo = hasContourUserData ? sizeof (ContourUserData) : 0;
		if (hasContourUserData) {
			target.contourInfos = BMXhAllClear ((source.GetContourNum () + 1) * target.sizeOfContourInfo);
			target.defaultContourInfo = BMXhAllClear (1 * target.sizeOfContourInfo);
			const ContourUserData&	defaultContourInfo = source.GetContourDefaultUserData ();
			BNCopyMemory (*target.defaultContourInfo, &defaultContourInfo, target.sizeOfContourInfo);
		}
		
		target.sizeOfInhPolygonInfo = hasPolygonUserData ? sizeof (PolygonUserData) : 0;
		if (hasPolygonUserData) {
			target.inhPolygonInfo = BMXhAllClear (1 * target.sizeOfInhPolygonInfo);
			const PolygonUserData& polyData = source.GetPolyUserData ();
			BNCopyMemory (*target.inhPolygonInfo, &polyData, target.sizeOfInhPolygonInfo);
		}

	} catch (...) {
		FreePolygon2DData (&target);
		DBBREAK ();
		return;
	}

	(*target.vertices)[0] = Point2D (0.0, 0.0);
	(*target.contourEnds)[0] = 0;
	if (hasVertexUserData)
		(*target.vertexInfos)[0] = 0;
	if (hasEdgeUserData)
		(*target.inhEdgeInfos)[0] = 0;

	UIndex spIndex = 1;
	UInt32 index = 1;
	for (typename PolyType::ConstContourIterator contourIt = source.EnumerateContour (); contourIt != nullptr; ++contourIt, ++spIndex) {
		GS::Array<Point2D> contourCoords;
		contourCoords.SetSize (contourIt->GetVertexNum () + 1);

		GS::Array<PolyArcRec> contourArcs;

		GS::Array<VertexUserData> contourVertIds;
		if (hasVertexUserData)
			contourVertIds.SetSize (contourIt->GetVertexNum () + 1);
		
		GS::Array<EdgeUserData> contourEdgeIds;
		if (hasEdgeUserData)
			contourEdgeIds.SetSize (contourIt->GetVertexNum () + 1);

		UIndex ii = 0;
		for (typename PolyType::ConstVertexIterator vertIt = contourIt->EnumerateVertex (); vertIt != nullptr; ++vertIt, ++index, ++ii) {
			contourCoords[ii] = vertIt->GetCoord ();
			if (hasVertexUserData)
				contourVertIds[ii] = vertIt->GetPolyVertexUserData ();
			if (hasEdgeUserData)
				contourEdgeIds[ii] = source.GetNextEdge (vertIt)->GetPolyEdgeUserData ();

			if (!contourIt->GetNextEdge (vertIt)->IsStraight ()) {
				PolyArcRec arc;
				arc.begIndex = index;
				arc.endIndex = arc.begIndex + 1;
				arc.arcAngle = contourIt->GetNextEdge (vertIt)->GetArcAngle ();
				contourArcs.Push (arc);
			}
		}
		contourCoords[ii] = contourCoords[0];
		if (hasVertexUserData)
			contourVertIds[ii] = contourVertIds[0];
		if (hasEdgeUserData)
			contourEdgeIds[ii] = contourEdgeIds[0];
		++ii;
		(*target.contourEnds)[spIndex] = index;
		++index;

		for (UIndex i = 0; i < contourCoords.GetSize (); i++) {
			(*target.vertices)[index - ii + i] = contourCoords[i];
			if (hasVertexUserData)
				(reinterpret_cast<VertexUserData*> (*target.vertexInfos))[index - ii + i] = contourVertIds[i];
			if (hasEdgeUserData)
				(reinterpret_cast<EdgeUserData*> (*target.inhEdgeInfos))[index - ii + i] = contourEdgeIds[i];
		}

		if (target.arcs != nullptr && contourArcs.GetSize () > 0) {
			BMhSetSize ((GSHandle) target.arcs, ((target.nArcs + 1 + contourArcs.GetSize ()) * sizeof (PolyArcRec)));
			if (BMError () != NoError) {
				DBBREAK ();
				return;
			}
			for (UIndex i = 0; i < contourArcs.GetSize (); i++)
				(*target.arcs) [target.nArcs + 1 + i] = contourArcs[i];
			target.nArcs += contourArcs.GetSize ();
		}
		if (hasContourUserData)
			(reinterpret_cast<ContourUserData*> (*target.contourInfos))[spIndex] = contourIt->GetPolyContourUserData ();
	}
	target.status.isSameDirEdgeLegal = source.GetSameDirEdgeLegal ();
	target.status.force64BitPrecision = source.GetForce64BitPrecision ();
	ValidatePolygon2DData (&target);
}		// ConvertPolygon2DToPolygon2DDataUntyped

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void ConvertPolyline2DToPolygon2DDataUntyped (Polygon2DData& target, const Polyline2D& source)
{
	//DBCHECKCOREPOLY2DDATA (polygon);

	Geometry::FreePolygon2DData (&target);
	Geometry::InitPolygon2DData (&target);

	UInt32 nVertex = source.GetVertexNum ();
	if (source.GetClosed ())
		nVertex++;
	const UInt32 nArcs = 0 /*source.GetArcsNum ()*/;		//TODO

	UInt32 polyFlags = source.GetPolyFlags ();
	bool hasVertexUserData = (polyFlags & PolyFlags_IsVertexUserData) > 0;
	bool hasEdgeUserData = (polyFlags & PolyFlags_IsEdgeUserData) > 0;
	bool hasContourUserData = (polyFlags & PolyFlags_IsContourUserData) > 0;
	bool hasPolygonUserData = (polyFlags & PolyFlags_IsPolygonUserData) > 0;

	if (nVertex == 0) {
		return;
	}

	try {
		target.vertices = reinterpret_cast<Point2D**> (BMXhAllClear ((nVertex + 1) * sizeof (Point2D)));
		target.nVertices = nVertex;
		target.nArcs = nArcs;
		target.arcs = reinterpret_cast<PolyArcRec**> (BMXhAllClear ((target.nArcs + 1) * sizeof (PolyArcRec)));
		//Contours
		target.nContours = 1;
		target.contourEnds = reinterpret_cast<UIndex**> (BMXhAll ((1 + 1) * sizeof (UIndex)));
		(*target.contourEnds) [0] = 0;
		(*target.contourEnds) [1] = nVertex;

		target.sizeOfVertexInfo = hasVertexUserData ? sizeof (VertexUserData) : 0;
		if (hasVertexUserData) {
			target.vertexInfos = BMXhAllClear ((nVertex + 1) * target.sizeOfVertexInfo);
			target.defaultVertexInfo = BMXhAllClear (1 * target.sizeOfVertexInfo);
			const VertexUserData&	defaultVertexInfo = source.GetVertexDefaultUserData ();
			BNCopyMemory (*target.defaultVertexInfo, &defaultVertexInfo, target.sizeOfVertexInfo);
		}

		target.sizeOfInhEdgeInfo = hasEdgeUserData ? sizeof (EdgeUserData) : 0;
		if (hasEdgeUserData) {
			target.inhEdgeInfos = BMXhAllClear ((nVertex + 1) * target.sizeOfInhEdgeInfo);
			target.defaultInhEdgeInfo = BMXhAllClear (1 * target.sizeOfInhEdgeInfo);
			const EdgeUserData&	defaultEdgeInfo = source.GetEdgeDefaultUserData ();
			BNCopyMemory (*target.defaultInhEdgeInfo, &defaultEdgeInfo, target.sizeOfInhEdgeInfo);
		}

		target.sizeOfContourInfo = hasContourUserData ? sizeof (ContourUserData) : 0;
		if (hasContourUserData) {
			target.contourInfos = BMXhAllClear ((1 + 1) * target.sizeOfContourInfo);
			target.defaultContourInfo = BMXhAllClear (1 * target.sizeOfContourInfo);
//			const ContourUserData&	defaultContourInfo = source.GetContourDefaultUserData ();
//			BNCopyMemory (*target.defaultContourInfo, &defaultContourInfo, target.sizeOfContourInfo);
		}

		target.sizeOfInhPolygonInfo = hasPolygonUserData ? sizeof (PolygonUserData) : 0;
		if (hasPolygonUserData) {
			target.inhPolygonInfo = BMXhAllClear (1 * target.sizeOfInhPolygonInfo);
			const PolygonUserData& polyData = source.GetPolyUserData ();
			BNCopyMemory (*target.inhPolygonInfo, &polyData, target.sizeOfInhPolygonInfo);
		}

		target.status.isSameDirEdgeLegal = source.GetSameDirEdgeLegal ();

		GS::Array<Point2D> contourCoords;
		contourCoords.SetSize (nVertex);
		GS::Array<PolyArcRec> contourArcs;
		GS::Array<VertexUserData> contourVertIds;
		if (hasVertexUserData)
			contourVertIds.SetSize (nVertex);
		GS::Array<EdgeUserData> contourEdgeIds;
		if (hasEdgeUserData)
			contourEdgeIds.SetSize (nVertex);

		UIndex ii = 0;
		UInt32 index = 1;
		for (Polyline2D::ConstVertexIterator vertIt = source.EnumerateVertex (); vertIt != nullptr; ++vertIt, ++index, ++ii) {
			contourCoords[ii] = vertIt->GetCoord ();
			if (hasVertexUserData)
				contourVertIds[ii] = vertIt->GetPolyVertexUserData ();
			if ((ii != nVertex - 1) || source.GetClosed ()) {
				if (hasEdgeUserData)
					contourEdgeIds[ii] = source.GetNextEdge (vertIt)->GetPolyEdgeUserData ();
				if (!source.GetNextEdge (vertIt)->IsStraight ()) {
					PolyArcRec arc;
					arc.begIndex = index;
					arc.endIndex = arc.begIndex + 1;
					arc.arcAngle = source.GetNextEdge (vertIt)->GetArcAngle ();
					contourArcs.Push (arc);
				}
			}
		}
		if (source.GetClosed ()) {
			contourCoords[ii] = contourCoords[0];
			if (hasVertexUserData)
				contourVertIds[ii] = contourVertIds[0];
			if (hasEdgeUserData)
				contourEdgeIds[ii] = contourEdgeIds[0];
			++ii;
			++index;
		}
		for (UIndex i = 0; i < contourCoords.GetSize (); i++) {
			(*target.vertices)[index - ii + i] = contourCoords[i];
			if (hasVertexUserData)
				(reinterpret_cast<VertexUserData*> (*target.vertexInfos))[index - ii + i] = contourVertIds[i];
			if (hasEdgeUserData)
				(reinterpret_cast<EdgeUserData*> (*target.inhEdgeInfos))[index - ii + i] = contourEdgeIds[i];
		}

		if (target.arcs != nullptr && contourArcs.GetSize () > 0) {
			BMhSetSize ((GSHandle) target.arcs, ((target.nArcs + 1 + contourArcs.GetSize ()) * sizeof (PolyArcRec)));
			if (BMError () != NoError) {
				DBBREAK ();
				return;
			}
			for (UIndex i = 0; i < contourArcs.GetSize (); i++)
				(*target.arcs) [target.nArcs + 1 + i] = contourArcs[i];
			target.nArcs += contourArcs.GetSize ();
		}	
	} catch (...) {
		FreePolygon2DData (&target);
		DBBREAK ();
		return;
	}

	ValidatePolyLine2DData (&target);

//	DBCHECKPOLY2DDATA(polygon);

}		// ConvertPolyline2DToPolygon2DDataUntyped

GEOMETRY_DLL_EXPORT
void ConvertPolygon2DToPolygon2DData (Polygon2DData& target, const Polygon2D& source);


GEOMETRY_DLL_EXPORT
void ConvertPolygon2DToPolygon2DData (Polygon2DData& target, const IrregularPolygon2D& source);

GEOMETRY_DLL_EXPORT
void ConvertPolyline2DToPolygon2DData (Polygon2DData& target, const Polyline2D& source);

}	// namespace Geometry

#endif
