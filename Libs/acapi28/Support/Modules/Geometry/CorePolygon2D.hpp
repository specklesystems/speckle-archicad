// *****************************************************************************
//
// Declaration of CorePolygon2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA, RJ
//
// *****************************************************************************

#ifndef GEOMETRY_COREPOLYGON2D_HPP
#define GEOMETRY_COREPOLYGON2D_HPP

#pragma once

// --- Includes ----------------------------------------------------------------
#include "CorePolygon2DClassDefinition.hpp"
#include "ConvexHull2DCreator.h"
#include "Plane.hpp"
#include "Spline2DData.h"

#ifdef CHECKED_VERSION
#include "ThreadLocal.hpp"
#endif
#ifdef DEBUVERS_RJ
#include "ThreadSpecificStorage.hpp"
#endif

#include <map>

namespace Geometry {

#ifdef CHECKED_VERSION
#define DEBUVERS_POLY2D
#endif

#if defined(DEBUVERS_POLY2D)
#define DBCHECKINDEX_COREPOLY(idx, minIdx, maxIdx) DBASSERT ((idx) >= (minIdx) && (idx) <= (maxIdx))

#define DBCHECKCOREPOLY_CHECK DBASSERT (Check (PolyCheckFlags_All_Polygon, nullptr, MaxCoordValue ()))
#define DBCHECKCOREPOLY_CHECKRESULT for (UIndex polyIdx = 0; polyIdx < result.GetSize (); polyIdx++) {DBASSERT (result[polyIdx]->Check (PolyCheckFlags_All_Polygon, nullptr, MaxCoordValue ()));}
#define DBCHECKCOREPOLY_CHECKRESULT_SINGLE DBASSERT (result->Check (PolyCheckFlags_All_Polygon, nullptr, MaxCoordValue ()))
#define DBCHECKCOREPOLY_MEMORY
#define DBCHECKCOREPOLY_ONEREFTOTHIS DBASSERT (GetRefCount () <= 1)
#else
#define DBCHECKINDEX_COREPOLY(idx, minIdx, maxIdx)

#define DBCHECKCOREPOLY_CHECK
#define DBCHECKCOREPOLY_MEMORY
#define DBCHECKCOREPOLY_CHECKRESULT
#define DBCHECKCOREPOLY_CHECKRESULT_SINGLE
#define DBCHECKCOREPOLY_ONEREFTOTHIS
#endif


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InitInternalData (void)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	boundBox = Box2DData ();
	flags.Clear ();
	status.Clear ();
	status.isRegularized = true;

	defaultVertexData = VertexUserData ();
	defaultEdgeData = EdgeUserData ();
	defaultContourData = ContourUserData ();

	inhPolygonInfo.Clear (true);

	nVertices = 0;
	vertices.Clear (true);
	vertexInfos.Clear (true);

	nArcs = 0;
	arcs.Clear (true);
	inhEdgeInfos.Clear (true);

	nContours = 0;
	contourEnds.Clear (true);
	contourInfos.Clear (true);

	if (inhPolygonInfo.GetSize() == 0 && flags.isPolygonUserData) {
		inhPolygonInfo.SetSize (1);
	}

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FreeInternalData (void)

{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	DBASSERT_GUID (Check (PolyCheckFlags_All_Polygon, nullptr, MaxCoordValue ()), "{367802E8-A7D0-4FC4-B66E-8289E3E0A8D6}");
	try {
#ifdef CHECKED_VERSION
		nVertices = 0xcdcdcdcd;
		nArcs = 0xcdcdcdcd;
		nContours = 0xcdcdcdcd;
#else
		nVertices = 0;
		nArcs = 0;
		nContours = 0;
#endif

		vertices.Clear (true);
		arcs.Clear (true);
		contourEnds.Clear (true);

		vertexInfos.Clear (true);
		inhEdgeInfos.Clear (true);
		contourInfos.Clear (true);
		inhPolygonInfo.Clear(true);
	} catch (GS::GSException& e) {
		e.Print (dbChannel);
		throw;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AllocateInternalData (USize verticesNum, USize arcsNum, USize contoursNum, USize verticesCapacity /*= 0*/, USize arcsCapacity /*= 0*/, USize contoursCapacity /*= 0*/)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	try {
		ReallocateInternalData (verticesNum, arcsNum, contoursNum, verticesCapacity, arcsCapacity, contoursCapacity);

	} catch (GS::GSException& e) {
		e.Print (dbChannel);
		throw GS::OutOfMemoryException ("Error in CorePolygon2D::AllocateInternalData!!!", __FILE__, __LINE__);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReallocateInternalDataSizes (USize verticesNum, USize arcsNum, USize contoursNum, USize verticesCapacity, USize arcsCapacity, USize contoursCapacity)
{
#ifdef CHECKED_VERSION
	DBASSERT (verticesCapacity >= 1 && contoursCapacity >= 1);
	//Vagy csak memoriat allokalunk vagy legalabb egy vertex es egy contour-nak kell lenni
	DBASSERT ((verticesNum == 0 && arcsNum == 0 && contoursNum == 0) || (contoursNum >= 1 && verticesNum >=0));
#else
	UNUSED_PARAMETER (verticesNum);
	UNUSED_PARAMETER (arcsNum);
	UNUSED_PARAMETER (contoursNum);
#endif

	//Vertices
	if (vertices.GetSize () != verticesCapacity + 1) {
		//Vertices
		vertices.SetSize (verticesCapacity + 1);

		//VertexId
		if (flags.isVertexUserData) {
			if (vertexInfos.GetSize() == 0) {
				vertexInfos.SetSize (verticesCapacity + 1);
			} else {
				DBBREAK_STR ("Jo lenne elore tudni es nem reallocalni.");
				vertexInfos.SetSize (verticesCapacity + 1);
			}
		}

		//EdgeId
		if (flags.isEdgeUserData) {
			if (inhEdgeInfos.GetSize() == 0) {
				inhEdgeInfos.SetSize (verticesCapacity + 1);
			} else {
				DBBREAK_STR ("Jo lenne elore tudni es nem reallocalni.");
				inhEdgeInfos.SetSize (verticesCapacity + 1);
			}
		}
	}
	//Arcs
	if (arcs.GetSize () != arcsCapacity + 1) {
		arcs.SetSize (arcsCapacity + 1);
	}

	//Contours
	if (contourEnds.GetSize () != contoursCapacity + 1) {
		contourEnds.SetSize (contoursCapacity + 1);
		//ContourId
		if (flags.isContourUserData) {
			if (contourInfos.GetSize () == 0) {
				contourInfos.SetSize (contoursCapacity + 1);
			} else {
				DBBREAK_STR ("Jo lenne elore tudni es nem reallocalni.");
				contourInfos.SetSize (contoursCapacity + 1);
			}
		}
	}

	//PolyId
	if (flags.isPolygonUserData) {
		if (inhPolygonInfo.GetSize () == 0) {
			inhPolygonInfo.SetSize (1);
		}
	}

	if (!flags.isContourUserData)
		contourInfos.Clear (true);
	if (!flags.isEdgeUserData)
		inhEdgeInfos.Clear(true);
	if (!flags.isVertexUserData)
		vertexInfos.Clear (true);
	if (!flags.isPolygonUserData)
		inhPolygonInfo.Clear (true);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReallocateInternalData (USize verticesNum, USize arcsNum, USize contoursNum, USize verticesCapacity /*= 0*/, USize arcsCapacity /*= 0*/, USize contoursCapacity /*= 0*/)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	try {
		DBASSERT (((vertices.GetSize () == 0 || !flags.isVertexUserData) && vertexInfos.GetSize () == 0) || (flags.isVertexUserData && vertices.GetSize () == vertexInfos.GetSize ()));
		DBASSERT (((vertices.GetSize () == 0 || !flags.isEdgeUserData) && inhEdgeInfos.GetSize () == 0) || (flags.isEdgeUserData && vertices.GetSize () == inhEdgeInfos.GetSize ()));
		DBASSERT (((contourEnds.GetSize () == 0 || !flags.isContourUserData) && contourInfos.GetSize () == 0) || (flags.isContourUserData && contourEnds.GetSize () == contourInfos.GetSize ()));
		DBASSERT (nVertices == 0 || vertices.GetSize () > nVertices);
		DBASSERT (nArcs == 0 || arcs.GetSize () > nArcs);
		DBASSERT (nContours == 0 || contourEnds.GetSize () > nContours);

		verticesCapacity = GS::Max(verticesCapacity, verticesNum);
		arcsCapacity = GS::Max(arcsCapacity, arcsNum);
		contoursCapacity = GS::Max(contoursCapacity, contoursNum);

		if (verticesCapacity == 0 && arcsCapacity == 0 && contoursCapacity == 0) {
			//Felszabaditjuk a memoriat.
			FreeInternalData ();
			InitInternalData ();

			return;
		}

		ReallocateInternalDataSizes (verticesNum, arcsNum, contoursNum, verticesCapacity, arcsCapacity, contoursCapacity);

		nVertices = verticesNum;
		nArcs = arcsNum;
		nContours = contoursNum;
		if (contoursNum >= 1) {
			contourEnds[contoursNum] = verticesNum;
		}
	} catch (GS::GSException& e) {
		e.Print (dbChannel);
		throw GS::OutOfMemoryException ("Error in CorePolygon2D::ReallocateInternalData!!!", __FILE__, __LINE__);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalDataVertices (const Point2D* pCoords, GS::UInt32 createFlags)
{
	//coords
	if (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) //input starts with blank coord
		pCoords++;
	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		for (UIndex vertexIdx = contourEnds[contourIdx-1]+1; vertexIdx < contourEnds[contourIdx]; vertexIdx++, pCoords++)
			vertices[vertexIdx] = *pCoords;
		if (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) {
			vertices[contourEnds[contourIdx]] = *pCoords;
			pCoords++;
		} else
			vertices[contourEnds[contourIdx]] = vertices[contourEnds[contourIdx-1]+1];
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalDataVertices (const GS::Array<Point2D>& coordList, USize contourNum, GS::UInt32 createFlags)
{
	//coords
	UIndex coordIdx = 0;
	if (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) //input starts with blank coord
		coordIdx++;
	for (UIndex contourIdx = 1; contourIdx <= contourNum; contourIdx++) {
		for (UIndex vertexIdx = contourEnds[contourIdx-1]+1; vertexIdx < contourEnds[contourIdx]; vertexIdx++, coordIdx++)
			vertices[vertexIdx] = coordList[coordIdx];
		if (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) {
			vertices[contourEnds[contourIdx]] = coordList[coordIdx];
			coordIdx++;
		} else
			vertices[contourEnds[contourIdx]] = vertices[contourEnds[contourIdx-1]+1];
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalDataArcs (const PolyArcRec* pArcs, USize arcNum, GS::UInt32 createFlags)
{
	//arcs
	if (pArcs != nullptr && arcNum != 0 && PolyCreateFlags_DummyArcAtIdxZero & createFlags)
		pArcs++;
	for (UIndex arcIdx = 1; arcIdx <= arcNum; arcIdx++, pArcs++) {
		arcs[arcIdx] = *pArcs;

		if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) &&
			(PolyCreateFlags_IdxRefInArcFromZero & createFlags)) //first meaningful coord at index 0
			arcs[arcIdx].begIndex++;
		if (!(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) //indexing does not follow duplicated first coord at contour end
			arcs[arcIdx].begIndex = VertexIdx2InternalVertexIdx (arcs[arcIdx].begIndex);
		arcs[arcIdx].endIndex = arcs[arcIdx].begIndex + 1;
#ifdef CHECKED_VERSION
		for (UIndex contourIdx = 1; contourIdx < nContours; contourIdx++)
			DBASSERT (arcs[arcIdx].begIndex != contourEnds[contourIdx]);
#endif
		DBASSERT (arcs[arcIdx].begIndex < nVertices); //assert indicates wrong input => overindexing will happen when calculating bounding box
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalDataArcs (const GS::Array<PolyArcRec>& arcList, USize arcNum, GS::UInt32 createFlags)
{
	//arcs
	UIndex srcArcIdx = 0;
	if (PolyCreateFlags_DummyArcAtIdxZero & createFlags)
		srcArcIdx++;
	for (UIndex arcIdx = 1; arcIdx <= arcNum; arcIdx++, srcArcIdx++) {
		arcs[arcIdx] = arcList[srcArcIdx];

		if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) &&
			(PolyCreateFlags_IdxRefInArcFromZero & createFlags)) //first meaningful coord at index 0
			arcs[arcIdx].begIndex++;
		if (!(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) { //indexing does not follow duplicated first coord at contour end
			arcs[arcIdx].begIndex = VertexIdx2InternalVertexIdx (arcs[arcIdx].begIndex);
		}
		arcs[arcIdx].endIndex = arcs[arcIdx].begIndex + 1;
#ifdef CHECKED_VERSION
		for (UIndex contourIdx = 1; contourIdx < nContours; contourIdx++)
			DBASSERT (arcs[arcIdx].begIndex != contourEnds[contourIdx]);
#endif
		DBASSERT (arcs[arcIdx].begIndex < nVertices); //assert indicates wrong input => overindexing will happen when calculating bounding box
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalDataContours (const UIndex* pContourEnds, USize contourNum, GS::UInt32 createFlags)
{
	//contour ends
	if (pContourEnds == nullptr) {
		//this should be already done by AllocateInternalData
		nContours = 1;
		contourEnds[0] = 0;
		contourEnds[1] = nVertices;
	} else {
		if (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)
			pContourEnds++;
		for (UIndex contourIdx = 1; contourIdx <= nContours && contourIdx <= contourNum; contourIdx++, pContourEnds++) {
			contourEnds[contourIdx] = (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) ? *pContourEnds : *pContourEnds + contourIdx;
			if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) &&
				(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) //first meaningful coord at index 0
				contourEnds[contourIdx]++;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalDataContours (const GS::Array<UIndex>& contourEndList, USize contourNum, GS::UInt32 createFlags)
{
	//contour ends
	if (contourEndList.IsEmpty ()) {
		//this should be already done by AllocateInternalData
		nContours = 1;
		contourEnds[0] = 0;
		contourEnds[1] = nVertices;
	} else {
		UIndex srcContourIdx = 0;
		if (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)
			srcContourIdx++;
		for (UIndex contourIdx = 1; contourIdx <= contourNum; contourIdx++, srcContourIdx++) {
			contourEnds[contourIdx] = (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) ? contourEndList[srcContourIdx] : contourEndList[srcContourIdx]+contourIdx;
			if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) &&
				(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) //first meaningful coord at index 0
				contourEnds[contourIdx]++;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalData (const Point2D* pCoords, USize coordNum, const PolyArcRec* pArcs, USize arcNum, const UIndex* pContourEnds, USize contourNum, GS::UInt32 createFlags)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	DBASSERT (coordNum > 1 && pCoords != nullptr);
	DBASSERT ((arcNum == 0 && pArcs == nullptr) || (arcNum != 0 && pArcs != nullptr));
	DBASSERT ((coordNum == nVertices && (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) || (coordNum == nVertices - contourNum && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)));
	DBASSERT (arcNum == nArcs);
	DBASSERT ((contourNum >= 1 && pContourEnds != nullptr && pContourEnds[0] == 0 && (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)) ||
		(contourNum >= 1 && pContourEnds != nullptr && !(PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)) || (pContourEnds == nullptr || contourNum == 1));

	status.isRegularized = false;

	if ((coordNum != nVertices && coordNum != nVertices - contourNum) || arcNum != nArcs || nContours == 0)
		throw GeometryIllegalArgumentException ("Invalid number of Vertices, Arcs or Contours in CorePolygon2D::SetInternalData!", __FILE__, __LINE__);

	SetInternalDataContours (pContourEnds, contourNum, createFlags);

	SetInternalDataVertices (pCoords, createFlags);

	SetInternalDataArcs (pArcs, arcNum, createFlags);

	RemoveSmallArcs ();

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalData (const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	status.isRegularized = false;

	USize coordNum = coordList.GetSize ();
	if (PolyCreateFlags_DummyCoordAtIdxZero & createFlags)
		coordNum--;

	USize arcNum = arcList.GetSize ();
	if (arcNum > 0 && PolyCreateFlags_DummyArcAtIdxZero & createFlags)
		arcNum--;

	USize contourNum = contourEndList.GetSize ();
	if (contourNum > 0 && PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)
		contourNum--;
	else if (contourNum == 0)
		contourNum = 1;

	DBASSERT ((coordNum == nVertices && (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) || (coordNum == nVertices - contourNum && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)));
	DBASSERT (arcNum == nArcs);
	DBASSERT ((contourEndList.GetSize () >= 1 && contourEndList[0] == 0 && (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)) ||
		(contourEndList.GetSize () >= 1 && !(PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)) || contourEndList.IsEmpty ());

	if ((coordNum != nVertices && coordNum != nVertices - contourNum) || arcNum != nArcs || nContours == 0)
		throw GeometryIllegalArgumentException ("Invalid number of Vertices, Arcs or Contours in CorePolygon2D::SetInternalData!", __FILE__, __LINE__); //ha az allocate jol ment, ide nem lenne szabad jonni

	SetInternalDataContours (contourEndList, contourNum, createFlags);

	SetInternalDataVertices (coordList, contourNum, createFlags);

	SetInternalDataArcs (arcList, arcNum, createFlags);

	RemoveSmallArcs ();

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}


template <class VertexUserDataTarget, class EdgeUserDataTarget, class ContourUserDataTarget, class PolygonUserDataTarget>
template <class VertexUserDataSource, class EdgeUserDataSource, class ContourUserDataSource, class PolygonUserDataSource>
void CorePolygon2D<VertexUserDataTarget, EdgeUserDataTarget, ContourUserDataTarget, PolygonUserDataTarget>::CopyInternalDataFromWithUserData (const CorePolygon2D<VertexUserDataSource, EdgeUserDataSource, ContourUserDataSource, PolygonUserDataSource>& source,
																													  USize verticesCapacity,
																													  USize arcsCapacity,
																													  USize contoursCapacity,
																													  Poly2DUserDataConverter<VertexUserDataSource, EdgeUserDataSource, ContourUserDataSource, PolygonUserDataSource,
																													  VertexUserDataTarget, EdgeUserDataTarget, ContourUserDataTarget, PolygonUserDataTarget>* userDataConverter)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	if (source.IsEmpty ()) {
		Clear ();
		flags.isSameDirEdgeLegal	= source.flags.isSameDirEdgeLegal;
		flags.isVertexUserData		= source.flags.isVertexUserData;
		flags.isEdgeUserData		= source.flags.isEdgeUserData;
		flags.isContourUserData		= source.flags.isContourUserData;
		flags.isPolygonUserData		= source.flags.isPolygonUserData;
		flags.force64BitPrecision	= source.flags.force64BitPrecision;

		return;
	}

	flags.isSameDirEdgeLegal	= source.flags.isSameDirEdgeLegal;
	flags.isVertexUserData		= source.flags.isVertexUserData;
	flags.isEdgeUserData		= source.flags.isEdgeUserData;
	flags.isContourUserData		= source.flags.isContourUserData;
	flags.isPolygonUserData		= source.flags.isPolygonUserData;
	flags.force64BitPrecision	= source.flags.force64BitPrecision;
	status.isRegularized = source.status.isRegularized;
	AllocateInternalData (source.nVertices, source.nArcs, source.nContours, verticesCapacity, arcsCapacity, contoursCapacity);

	DBASSERT (source.nVertices == nVertices);
	for (UIndex vertexIdx = 1; vertexIdx <= nVertices && vertexIdx <= source.nVertices; vertexIdx++) {
		vertices[vertexIdx] = source.vertices[vertexIdx];
	}
	DBASSERT (source.nArcs == nArcs);
	for (UIndex arcIdx = 1; arcIdx <= nArcs && arcIdx <= source.nArcs; arcIdx++) {
		arcs[arcIdx] = source.arcs[arcIdx];
	}
	DBASSERT (source.nContours == nContours);
	for (UIndex contourIdx = 1; contourIdx <= nContours && contourIdx <= source.nContours; contourIdx++) {
		contourEnds[contourIdx] = source.contourEnds[contourIdx];
	}

	CopyInternalDataFromClearUserData ();

	//ContourId
	DBASSERT ((!flags.isPolygonUserData && inhPolygonInfo.GetSize () == 0) || (flags.isPolygonUserData && inhPolygonInfo.GetSize () != 0));
	if (flags.isPolygonUserData && inhPolygonInfo.GetSize () != 0) {

		PolygonUserDataTarget targetUserData;
		if (userDataConverter != nullptr && userDataConverter->ConvertPolygonUserData (source.inhPolygonInfo[0], targetUserData)) {
			inhPolygonInfo[0] = targetUserData;
		} else {
			inhPolygonInfo[0] = PolygonUserDataTarget ();
		}
	}

	if (userDataConverter != nullptr) {
		if (flags.isContourUserData) {
			ContourUserDataTarget targetUserData;
			if (DBVERIFY (contourInfos.GetSize () <= source.contourInfos.GetSize ())) {
				DBASSERT (contourInfos.GetSize () == source.contourInfos.GetSize ());
				for (UInt32 i = 0; i < contourInfos.GetSize (); ++i) {
					if (userDataConverter->ConvertContourUserData (source.contourInfos[i], targetUserData)) {
						contourInfos[i] = targetUserData;
					}
				}
			}
		}

		if (flags.isEdgeUserData) {
			EdgeUserDataTarget targetUserData;
			if (DBVERIFY (inhEdgeInfos.GetSize () <= source.inhEdgeInfos.GetSize ())) {
				DBASSERT (inhEdgeInfos.GetSize () == source.inhEdgeInfos.GetSize ());
				for (UInt32 i = 0; i < inhEdgeInfos.GetSize (); ++i) {
					if (userDataConverter->ConvertEdgeUserData (source.inhEdgeInfos[i], targetUserData)) {
						inhEdgeInfos[i] = targetUserData;
					}
				}
			}
		}

		if (flags.isVertexUserData) {
			VertexUserDataTarget targetUserData;
			if (DBVERIFY (vertexInfos.GetSize () <= source.vertexInfos.GetSize ())) {
				DBASSERT (vertexInfos.GetSize () == source.vertexInfos.GetSize ());
				for (UInt32 i = 0; i < vertexInfos.GetSize (); ++i) {
					if (userDataConverter->ConvertVertexUserData (source.vertexInfos[i], targetUserData)) {
						vertexInfos[i] = targetUserData;
					}
				}
			}
		}
	}


	boundBox = source.boundBox;

	if ((source.nVertices == verticesCapacity || verticesCapacity == 0) &&
		(source.nArcs == arcsCapacity || arcsCapacity == 0) &&
		(source.nContours == contoursCapacity || contoursCapacity == 0)) {
			DBASSERT_GUID (Check (PolyCheckFlags_All_Polygon, nullptr, MaxCoordValue ()), "{1776ABE9-697E-449C-B74E-A4C42C0CB425}");
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearUserDataPolyline (CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline)
{
	//VertexId
	DBASSERT ((!polyline.flags.isVertexUserData && polyline.vertexInfos.GetSize() == 0) || (polyline.flags.isVertexUserData && polyline.vertexInfos.GetSize() != 0));
	if (polyline.vertexInfos.GetSize() != 0 && polyline.flags.isVertexUserData) {
		ZeroInfo_Data <VertexUserData> (polyline.vertexInfos, 0, polyline.nVertices, polyline.defaultVertexData);
	}

	//EdgeId
	DBASSERT ((!polyline.flags.isEdgeUserData && polyline.inhEdgeInfos.GetSize() == 0) || (polyline.flags.isEdgeUserData && polyline.inhEdgeInfos.GetSize() != 0));
	if (polyline.inhEdgeInfos.GetSize() != 0 && polyline.flags.isEdgeUserData) {
		ZeroInfo_Data <EdgeUserData> (polyline.inhEdgeInfos, 0, polyline.nVertices, polyline.defaultEdgeData);
	}

	//ContourId -> polyId
	DBASSERT ((!polyline.flags.isPolygonUserData && polyline.inhPolygonInfo.GetSize() == 0) || (polyline.flags.isPolygonUserData && polyline.inhPolygonInfo.GetSize() != 0));
	if (polyline.flags.isPolygonUserData && polyline.inhPolygonInfo.GetSize() != 0) {
		polyline.inhPolygonInfo [0] = PolygonUserData ();
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyInternalDataFromClearUserData (void)
{
	//VertexId
	DBASSERT ((!flags.isVertexUserData && vertexInfos.GetSize () == 0) || (flags.isVertexUserData && vertexInfos.GetSize () != 0));
	if (flags.isVertexUserData && vertexInfos.GetSize () != 0) {
		ZeroInfo_Data <VertexUserData> (vertexInfos, 0, (nVertices + 1), defaultVertexData);
	}

	//EdgeId
	DBASSERT ((!flags.isEdgeUserData && inhEdgeInfos.GetSize () == 0) || (flags.isEdgeUserData && inhEdgeInfos.GetSize () != 0));
	if (flags.isEdgeUserData && inhEdgeInfos.GetSize () != 0) {
		ZeroInfo_Data <EdgeUserData> (inhEdgeInfos, 0, (nVertices + 1), defaultEdgeData);
	}

	//ContourId
	DBASSERT ((!flags.isContourUserData && contourInfos.GetSize () == 0) || (flags.isContourUserData && contourInfos.GetSize () != 0));
	if (flags.isContourUserData && contourInfos.GetSize () != 0) {
		ZeroInfo_Data <ContourUserData> (contourInfos, 0, (nContours + 1), defaultContourData);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyInternalDataFromUserData (const CorePolygon2D& source, UIndex fromVertex, UIndex begVertexIdx, USize newVerticesNum, UIndex fromContour, UIndex contourIdx, USize newContourNum)
{
	//VertexId
	DBASSERT ((!flags.isVertexUserData && vertexInfos.GetSize () == 0) || (flags.isVertexUserData && vertexInfos.GetSize () != 0));
	if (flags.isVertexUserData && vertexInfos.GetSize () != 0) {
		if (source.flags.isVertexUserData && source.vertexInfos.GetSize () != 0)
			CopyInfo_Data <VertexUserData> (vertexInfos, fromVertex, source.vertexInfos, begVertexIdx, newVerticesNum );
		else
			ZeroInfo_Data <VertexUserData> (vertexInfos, fromVertex, newVerticesNum , defaultVertexData);
	}

	//EdgeId
	DBASSERT ((!flags.isEdgeUserData && inhEdgeInfos.GetSize () == 0) || (flags.isEdgeUserData && inhEdgeInfos.GetSize () != 0));
	if (flags.isEdgeUserData && inhEdgeInfos.GetSize () != 0) {
		if (source.flags.isEdgeUserData && source.inhEdgeInfos.GetSize () != 0)
			CopyInfo_Data <EdgeUserData> (inhEdgeInfos, fromVertex, source.inhEdgeInfos, begVertexIdx, newVerticesNum);
		else
			ZeroInfo_Data <EdgeUserData> (inhEdgeInfos, fromVertex, newVerticesNum, defaultEdgeData);
	}

	//ContourId
	DBASSERT ((!flags.isContourUserData && contourInfos.GetSize () == 0) || (flags.isContourUserData && contourInfos.GetSize () != 0));
	if (flags.isContourUserData && contourInfos.GetSize () != 0) {
		if (source.flags.isContourUserData && source.contourInfos.GetSize () != 0)
			CopyInfo_Data <ContourUserData> (contourInfos, fromContour, source.contourInfos, contourIdx, newContourNum);
		else
			ZeroInfo_Data <ContourUserData> (contourInfos, fromContour, newContourNum, defaultContourData);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyInternalDataFrom (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, USize verticesCapacity, USize arcsCapacity, USize contoursCapacity)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	if (source.IsEmpty ()) {
		Clear ();
		CopyPolygonLevelDataFrom (source);

		return;
	}

	CopyPolygonLevelDataFrom (source);
	status = source.status;
	AllocateInternalData (source.nVertices, source.nArcs, source.nContours, verticesCapacity, arcsCapacity, contoursCapacity);

	DBASSERT (source.nVertices == nVertices);
	for (UIndex vertexIdx = 1; vertexIdx <= nVertices && vertexIdx <= source.nVertices; vertexIdx++) {
		vertices[vertexIdx] = source.vertices[vertexIdx];
	}
	DBASSERT (source.nArcs == nArcs);
	for (UIndex arcIdx = 1; arcIdx <= nArcs && arcIdx <= source.nArcs; arcIdx++) {
		arcs[arcIdx] = source.arcs[arcIdx];
	}
	RemoveSmallArcs ();
	DBASSERT (source.nContours == nContours);
	for (UIndex contourIdx = 1; contourIdx <= nContours && contourIdx <= source.nContours; contourIdx++) {
		contourEnds[contourIdx] = source.contourEnds[contourIdx];
	}

	CopyInternalDataFromUserData (source, 0 , 0, (nVertices + 1),  0, 0, (nContours + 1) );

	boundBox = source.boundBox;

	if ((source.nVertices == verticesCapacity || verticesCapacity == 0) &&
		(source.nArcs == arcsCapacity || arcsCapacity == 0) &&
		(source.nContours == contoursCapacity || contoursCapacity == 0)) {
		DBASSERT_GUID (Check (PolyCheckFlags_All_Polygon, nullptr, MaxCoordValue ()), "{1776ABE9-697E-449C-B74E-A4C42C0CB425}");
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyInternalDataFrom (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, UIndex contourIdx)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	UIndex begVertexIdx = source.GetInternalVertexBeginIdxInContour (contourIdx);
	UIndex endVertexIdx = source.GetInternalVertexEndIdxInContour (contourIdx);

	USize arcsNum = 0;
	if (source.nArcs != 0 && source.arcs.GetSize () > 1) {
		for (UIndex arcIdx = 1; arcIdx <= source.nArcs; arcIdx++) {
			if (source.arcs[arcIdx].begIndex >= begVertexIdx && source.arcs[arcIdx].begIndex < endVertexIdx)
				arcsNum++;
		}
	}

	CopyPolygonLevelDataFrom (source);
	AllocateInternalData (0, 0, 0, endVertexIdx - begVertexIdx + 1, arcsNum, 1);

	CopyInternalContourFrom (source, contourIdx);

	UpdateBoundingBox ();
	UpdateOrientation ();

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyInternalContourFrom (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, UIndex contourIdx)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	status.isRegularized = false;

	UIndex begVertexIdx = source.GetInternalVertexBeginIdxInContour (contourIdx);
	UIndex endVertexIdx = source.GetInternalVertexEndIdxInContour (contourIdx);

	USize newVerticesNum = endVertexIdx - begVertexIdx + 1;
	USize newArcsNum = 0;

	for (UIndex vertexIdx = nVertices + 1, sourceVertexIdx = begVertexIdx; vertexIdx <= nVertices + newVerticesNum && sourceVertexIdx <= endVertexIdx; vertexIdx++, sourceVertexIdx++) {
		vertices[vertexIdx] = source.vertices[sourceVertexIdx];
	}
	if (arcs.GetSize () > 1 && source.arcs.GetSize () > 1 && source.nArcs != 0) {
		UIndex actArcIdx = nArcs + 1;
		for (UIndex arcIdx = 1; arcIdx <= source.nArcs; arcIdx++) {
			if (source.arcs[arcIdx].begIndex >= begVertexIdx && source.arcs[arcIdx].begIndex < endVertexIdx) {
				arcs[actArcIdx].arcAngle = source.arcs[arcIdx].arcAngle;
				arcs[actArcIdx].begIndex = source.arcs[arcIdx].begIndex - begVertexIdx + 1 + nVertices;
				arcs[actArcIdx].endIndex = arcs[actArcIdx].begIndex + 1;
				actArcIdx++;
				newArcsNum++;
			}
		}
	}
	contourEnds[nContours + 1] = nVertices + newVerticesNum;

	CopyInternalDataFromUserData (source, nVertices + 1, begVertexIdx, newVerticesNum, nContours + 1, contourIdx, 1);

	nVertices += newVerticesNum;
	nArcs += newArcsNum;
	nContours++;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonLevelDataFrom (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	flags = source.flags;

	defaultVertexData = source.defaultVertexData;
	defaultEdgeData = source.defaultEdgeData;
	defaultContourData = source.defaultContourData;

	//PolyId
	if (flags.isPolygonUserData) {
		if (inhPolygonInfo.GetSize () == 0)
			inhPolygonInfo.SetSize (1);
		if (source.inhPolygonInfo.GetSize () != 0 && source.flags.isPolygonUserData)
			inhPolygonInfo [0] = source.inhPolygonInfo [0];
		else
			inhPolygonInfo [0] = PolygonUserData ();
	} else {
		inhPolygonInfo.Clear (true);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonLevelDataFrom (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& source)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	flags.Clear ();
	for (UIndex polyIdx = 0; polyIdx < source.GetSize (); polyIdx++) {
		if (!source[polyIdx]->flags.isSameDirEdgeLegal)
			flags.isSameDirEdgeLegal = false;
		if (!source[polyIdx]->flags.isVertexUserData)
			flags.isVertexUserData = false;
		if (!source[polyIdx]->flags.isEdgeUserData)
			flags.isEdgeUserData = false;
		if (!source[polyIdx]->flags.isContourUserData)
			flags.isContourUserData = false;
		if (!source[polyIdx]->flags.isPolygonUserData)
			flags.isPolygonUserData = false;
		if (source[polyIdx]->flags.force64BitPrecision)
			flags.force64BitPrecision = true;
	}

	//PolyId
	if (flags.isPolygonUserData) {
		if (inhPolygonInfo.GetSize () == 0)
			inhPolygonInfo.SetSize (1);
		if (source.GetSize () == 1 && source[0]->inhPolygonInfo.GetSize() != 0 && source[0]->flags.isPolygonUserData)
			inhPolygonInfo [0] = (source[0]->inhPolygonInfo)[0];
		else
			inhPolygonInfo [0] = PolygonUserData ();
	} else {
		inhPolygonInfo.Clear (true);
	}

	defaultVertexData = source[0]->defaultVertexData;
	defaultEdgeData = source[0]->defaultEdgeData;
	defaultContourData = source[0]->defaultContourData;
}

//template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
//void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonLevelDataFrom (const Polygon2DData& source)
//{
//	DBCHECKCOREPOLY_ONEREFTOTHIS;
//
//	flags.isSameDirEdgeLegal = source.status.isSameDirEdgeLegal;
//	flags.force64BitPrecision = source.status.force64BitPrecision;
//
//	//PolyId
//	if (flags.isPolygonUserData) {
//		if (inhPolygonInfo.GetSize() == 0)
//			inhPolygonInfo.SetSize (1);
//		if (source.inhPolygonInfo != nullptr && *source.inhPolygonInfo != nullptr)
//			inhPolygonInfo [0] = *(reinterpret_cast<const PolygonUserData*>(*source.inhPolygonInfo));
//		else
//			inhPolygonInfo [0] = PolygonUserData ();
//	} else {
//		inhPolygonInfo.Clear ();
//	}
//}

//template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
//void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonLevelDataTo (Polygon2DData& dest) const
//{
//	//PolyId
//	DBASSERT ((dest.sizeOfInhPolygonInfo == 0 && dest.inhPolygonInfo == nullptr) || (dest.sizeOfInhPolygonInfo != 0 && dest.inhPolygonInfo != nullptr));
//	if (dest.inhPolygonInfo != nullptr) {
//		BMKillHandle (&dest.inhPolygonInfo);
//	}
//	dest.sizeOfInhPolygonInfo = 0;
//	if (inhPolygonInfo.GetSize () != 0&& flags.isPolygonUserData) {
//		dest.sizeOfInhPolygonInfo = sizeof (PolygonUserData);
//		dest.inhPolygonInfo = BMAllocateHandle (dest.sizeOfInhPolygonInfo, ALLOCATE_CLEAR, 0);
//
//		BNCopyMemory (*dest.inhPolygonInfo, reinterpret_cast<const void*> (inhPolygonInfo.GetContent ()), sizeof (PolygonUserData));
//	}
//
//	dest.status.isSameDirEdgeLegal = flags.isSameDirEdgeLegal;
//	dest.status.force64BitPrecision = flags.force64BitPrecision;
//}
//
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::VertexIdx2InternalVertexIdx (UIndex vertexIdx) const
{
	if (vertexIdx <= 0) {
		DBBREAK ();
		return 0;
	}
	if (nContours <= 1) {
		DBASSERT (vertexIdx >= 1);
		DBASSERT (nContours == 1 && vertexIdx <= contourEnds [nContours]);
		return vertexIdx;
	}
	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);
		if (begVertexIdx <= vertexIdx && vertexIdx < endVertexIdx)
			return vertexIdx;
		vertexIdx++;
	}
	DBBREAK ();
	return nVertices;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InternalVertexIdx2VertexIdx (UIndex vertexIdx) const
{
	if (vertexIdx <= 0) {
		DBBREAK ();
		return 0;
	}
	if (nContours <= 1) {
		DBASSERT (vertexIdx >= 1);
		DBASSERT (nContours == 1 && vertexIdx <= contourEnds [nContours]);
		return vertexIdx;
	}
	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);
		if (begVertexIdx <= vertexIdx && vertexIdx < endVertexIdx)
			return vertexIdx - contourIdx + 1;
		if (vertexIdx == endVertexIdx) {
			DBBREAK ();
			return begVertexIdx - contourIdx + 1;
		}
	}
	DBBREAK ();
	return GetVertexNum ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AddOneVertex (const Point2D& coord, const VertexUserData* vertexInfo, const EdgeUserData* edgeInfo, const PolyArcRec* arc /*= nullptr*/)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	DBASSERT (vertices.GetSize () >= nVertices + 1);
	DBASSERT (arc == nullptr || (arcs.GetSize () > nArcs + 1));

	status.isRegularized = false;

	if (nVertices + 1 >= vertices.GetSize ())
		ReallocateInternalData (nVertices, nArcs, nContours, GS::Max (nVertices + 1, vertices.GetSize () - 1), GS::Max (arc == nullptr ? nArcs : nArcs + 1, arcs.GetSize () - 1), GS::Max (nContours, contourEnds.GetSize () - 1));

	USize vertexIdx = nVertices + 1;

	vertices [vertexIdx] = coord;

	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
		if (vertexInfo != nullptr) {
			vertexInfos [vertexIdx] = *vertexInfo;
		} else {
			vertexInfos [vertexIdx] = defaultVertexData;
		}
	}
	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
		if (edgeInfo != nullptr) {
			inhEdgeInfos [vertexIdx] = *edgeInfo;
		} else {
			inhEdgeInfos [vertexIdx] = defaultEdgeData;
		}
	}
	nVertices++;
	contourEnds[nContours]++;

	if (arc != nullptr) {
		nArcs++;
		arcs[nArcs].arcAngle = arc->arcAngle;
		arcs[nArcs].begIndex = vertexIdx;
		arcs[nArcs].endIndex = arcs[nArcs].begIndex + 1;
	}

	DBASSERT (contourEnds[nContours] == nVertices);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AddOneContour(const ContourUserData* contourInfo)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	DBASSERT (contourEnds.GetSize () >= nContours + 1);

	status.isRegularized = false;

	if (nContours + 1 >= contourEnds.GetSize ())
		ReallocateInternalData (nVertices, nArcs, nContours, GS::Max (nVertices, vertices.GetSize () - 1), GS::Max (nArcs, arcs.GetSize () - 1), GS::Max (nContours + 1, contourEnds.GetSize () - 1));

	USize contourIdx = nContours + 1;

	contourEnds [contourIdx] = contourEnds [nContours];
	if (flags.isContourUserData) {
		if (contourInfo != nullptr) {
			contourInfos [contourIdx] = *contourInfo;
		} else {
			contourInfos [contourIdx] = defaultContourData;
		}
	}
	nContours++;

	DBASSERT (contourEnds[nContours] == nVertices);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourIdxFromInternalVertexIdx (UIndex vertexIdx) const
{
	if (vertexIdx <= 0) {
		DBBREAK ();
		return 0;
	}
	if (nContours <= 1) {
		DBASSERT (vertexIdx >= 1);
		DBASSERT (nContours == 1 && vertexIdx <= contourEnds [nContours]);
		return 1;
	}
	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);
		if (begVertexIdx <= vertexIdx && vertexIdx < endVertexIdx)
			return contourIdx;
		// vertexIdx++;
	}
	DBBREAK ();
	return nContours;
}

//A contourhoz tartozo elso vertex internal indexet adja
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetInternalVertexBeginIdxInContour (UIndex contourIdx) const
{
	return (contourIdx > 1) ? contourEnds [contourIdx - 1] + 1 : 1;
}

//A contourhoz mar nem tartozo vertex internal indexet adja
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetInternalVertexEndIdxInContour (UIndex contourIdx) const
{
	return contourEnds [contourIdx];
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetInternalArcIdx (UIndex edgeIdx) const
{
	UIndex arcIdx = 0;
	if (arcs.GetSize () > 1 && nArcs > 0 && edgeIdx <= nVertices) {
		for (UIndex i = 1; i <= nArcs; ++i) {
			const PolyArcRec& arc = arcs[i];
			if (arc.begIndex == edgeIdx) {
				DBASSERT (arc.endIndex == edgeIdx + 1);
				arcIdx = i;
				break;
			}
		}
		if (arcIdx == 0 && edgeIdx == nVertices) {
			DBBREAK (); //Erre nem lenne szabad, hogy fusson
			arcIdx = GetInternalArcIdx (1);
		}
	}
	return arcIdx;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetNextVertexIndex (UIndex internalVertexIdx) const
{
	UIndex contourIdx = GetContourIdxFromInternalVertexIdx (internalVertexIdx);
	UIndex begContourIdx = GetInternalVertexBeginIdxInContour (contourIdx);
	UIndex endContourIdx = GetInternalVertexEndIdxInContour (contourIdx) - 1;
	DBASSERT (begContourIdx <= internalVertexIdx && internalVertexIdx <= endContourIdx);
	return (internalVertexIdx == endContourIdx) ? begContourIdx : internalVertexIdx + 1;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPrevVertexIndex (UIndex internalVertexIdx) const
{
	UIndex contourIdx = GetContourIdxFromInternalVertexIdx (internalVertexIdx);
	UIndex begContourIdx = GetInternalVertexBeginIdxInContour (contourIdx);
	UIndex endContourIdx = GetInternalVertexEndIdxInContour (contourIdx) - 1;
	DBASSERT (begContourIdx <= internalVertexIdx && internalVertexIdx <= endContourIdx);
	return (internalVertexIdx == begContourIdx) ? endContourIdx : internalVertexIdx - 1;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeAsCurve2DData (UIndex internalEdgeIdx, Curve2DData& edge) const
{
	Sector tmpSector;
	GenArc tmpGenArc;
	InitCurve2DData (&edge, Eps, Eps);
	bool isArc = false;
	if (GetSector (InternalVertexIdx2VertexIdx (internalEdgeIdx), tmpSector, tmpGenArc)) {
		edge.type = CURVE2D_GenArc;
		edge.genArc = tmpGenArc;
		isArc = true;
	} else {
		edge.type = CURVE2D_Sector;	// even it is a circle, but the isRevoriented flag is important!!!
		edge.sector = tmpSector;
	}
	return isArc;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeAngleInternal (UIndex internalEdgeIdx, double edgeAngle)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	status.isRegularized = false;
	flags.isSameDirEdgeLegal = true;	// ???

	UIndex arcInd = GetInternalArcIdx (internalEdgeIdx);
	if (arcInd != 0) {
		if (edgeAngle != 0.0)
			arcs[arcInd].arcAngle = edgeAngle;
		else {
			arcs.Delete (arcInd);
			nArcs--;
		}
	} else if (edgeAngle != 0.0) {
		PolyArcRec arc;
		arc.begIndex = internalEdgeIdx;
		arc.endIndex = internalEdgeIdx + 1;
		arc.arcAngle = edgeAngle;
		arcs.Push (arc);
		nArcs++;
	}
}

static inline bool JoinCircArcs (const Circle2D& c1, const Point2D& arcEndPoint1, const Circle2D& c2, const Point2D& arcEndPoint2, Point2D& commonArcEndPoint)
{
	Sector intersectionPoints;
	if (Geometry::XCircles (&c1, &c2, &intersectionPoints)) {
		const double sd1 =
			(arcEndPoint1 - intersectionPoints.c1).GetLength () +
			(arcEndPoint2 - intersectionPoints.c1).GetLength ();
		const double sd2 =
			(arcEndPoint1 - intersectionPoints.c2).GetLength () +
			(arcEndPoint2 - intersectionPoints.c2).GetLength ();

		if (fabs (sd1) < fabs (sd2)) {
			commonArcEndPoint = intersectionPoints.c1;
		} else {
			commonArcEndPoint = intersectionPoints.c2;
		}

		return true;
	}

	return false;
}


static inline bool JoinCircArcAndStraightEdge (const Circle2D& arcCircle, const Point2D& arcEndPoint, const Point2D& begP, const Point2D& endP, Point2D& commonArcEndPoint)
{
	Sector edgeLine, intersectionPoints;
	edgeLine.c1 = begP;
	edgeLine.c2 = endP;
	if (Geometry::XCircleLine (&arcCircle, &edgeLine, &intersectionPoints)) {
		const double sd1 =
			(arcEndPoint - intersectionPoints.c1).GetLength () +
			(endP - intersectionPoints.c1).GetLength ();
		const double sd2 =
			(arcEndPoint - intersectionPoints.c2).GetLength () +
			(endP - intersectionPoints.c2).GetLength ();

		if (fabs (sd1) < fabs (sd2)) {
			commonArcEndPoint = intersectionPoints.c1;
		} else {
			commonArcEndPoint = intersectionPoints.c2;
		}

		return true;
	}
	else {
		//If there is no intersection, then join by touching the circle by the edge
		Point2D origo = Geometry::MidPoint (begP, arcCircle.Origo ());
		Circle2D c (origo, (arcCircle.Origo () - origo).GetLength ());
		if (Geometry::XCircles (&c, &arcCircle, &intersectionPoints)) {
			const double sd1 =
				(arcEndPoint - intersectionPoints.c1).GetLength () +
				(endP - intersectionPoints.c1).GetLength ();
			const double sd2 =
				(arcEndPoint - intersectionPoints.c2).GetLength () +
				(endP - intersectionPoints.c2).GetLength ();

			if (fabs (sd1) < fabs (sd2)) {
				commonArcEndPoint = intersectionPoints.c1;
			} else {
				commonArcEndPoint = intersectionPoints.c2;
			}
			return true;
		}
	}

	return false;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdgeInternal (UIndex internalEdgeIdx, const GS::Array<GenArc>& genArcs, const ArcDivParams& arcDivParams)
{
	if (DBERROR (genArcs.IsEmpty ())) {
		return;
	}

	DBCHECKCOREPOLY_ONEREFTOTHIS;

	status.isRegularized = false;
	flags.isSameDirEdgeLegal = true;	// ???

	UIndex nextInternalVertexIdx = GetNextVertexIndex	(internalEdgeIdx);
	UIndex contourIdx = GetContourIdxFromInternalVertexIdx (internalEdgeIdx);


	GS::Array<Point2D> newPositions;
	GS::Array<Point2D> newArcCenters;
	GS::Array<bool>  newIsReflected;

	Point2D begC = genArcs.GetFirst ().GetBegC ();
	Point2D endC = genArcs.GetLast ().GetEndC ();

	const bool singleCircleArc = genArcs.GetSize () == 1 && !genArcs.GetFirst ().IsElliptic ();
	if (!singleCircleArc) {
		if (arcDivParams.preferArcsBasedSegmentation ) {
			Geometry::DivideEllArcToArcs (genArcs.GetFirst (), arcDivParams, newPositions, newArcCenters);
			newIsReflected.SetSize (newArcCenters.GetSize ());
			newIsReflected.Fill (genArcs.GetFirst ().IsReflected ());

			for (UIndex i = 1; i < genArcs.GetSize (); ++i) {
				GS::Array<Point2D> appendPositions;
				GS::Array<Point2D> appendArcCenters;
				GS::Array<bool>  appendIsReflected;
				Geometry::DivideEllArcToArcs (genArcs[i], arcDivParams, appendPositions, appendArcCenters);
				if (arcDivParams.preferSegmentedArcEnds) {
					//must find the common point:

					Circle2D c1 (newArcCenters.GetLast (), (newArcCenters.GetLast () - newPositions.GetLast ()).GetLength ());
					Circle2D c2 (appendArcCenters.GetFirst (), (appendArcCenters.GetFirst () - appendPositions.GetFirst ()).GetLength ());
					Point2D commonArcEndPoint;
					if (JoinCircArcs (c1, newPositions.GetLast (), c2, appendPositions.GetFirst (), commonArcEndPoint)) {
						newPositions.GetLast () = commonArcEndPoint;
						appendPositions.GetFirst () = commonArcEndPoint;
					}
				}
				DBASSERT (IsNear (newPositions.GetLast (), appendPositions.GetFirst ()));

				appendIsReflected.SetSize (appendArcCenters.GetSize ());
				appendIsReflected.Fill (genArcs[i].IsReflected ());

				newPositions.DeleteLast ();
				newPositions.Append (appendPositions);
				newArcCenters.Append (appendArcCenters);
				newIsReflected.Append (appendIsReflected);
			}

			if (arcDivParams.preferSegmentedArcEnds) {
				//potentially must snap the very begin and very end points of the circle arcs to match the previous and following edges of the polygon!

				const UIndex prevEdgeEndVertIndex = internalEdgeIdx;
				const UIndex prevEdgeBegVertIndex = GetPrevVertexIndex (prevEdgeEndVertIndex);
				const UIndex prevEdgeArcInd = GetInternalArcIdx (prevEdgeBegVertIndex);
				Circle2D circSegmentEnd (newArcCenters.GetFirst (), (newPositions.GetFirst () - newArcCenters.GetFirst ()).GetLength ());
				if (prevEdgeArcInd != 0) {
					//crossect the two circle
					const double prevEdgeArcAngle = arcs[prevEdgeArcInd].arcAngle;
					GenArc arcPrev = GenArc::CreateCircleArc (vertices[prevEdgeBegVertIndex], vertices[prevEdgeEndVertIndex], prevEdgeArcAngle);
					Circle2D c (arcPrev.GetOrigo (), (vertices[prevEdgeEndVertIndex] - arcPrev.GetOrigo ()).GetLength ());
					Point2D commonArcEndPoint;
					if (JoinCircArcs (c, vertices[prevEdgeEndVertIndex], circSegmentEnd, newPositions.GetFirst (), commonArcEndPoint)) {
						newPositions.GetFirst () = commonArcEndPoint;
					}
				}
				else {
					//crossect the edge-line and the circle
					Point2D commonArcEndPoint;
					if (JoinCircArcAndStraightEdge (
						circSegmentEnd, newPositions.GetFirst (),
						vertices[prevEdgeBegVertIndex], vertices[prevEdgeEndVertIndex],
						commonArcEndPoint)) {
						newPositions.GetFirst () = commonArcEndPoint;
					}
				}

				const UIndex nextEdgeBegVertIndex = nextInternalVertexIdx;
				const UIndex nextEdgeEndVertIndex = GetNextVertexIndex (nextEdgeBegVertIndex);
				const UIndex nextEdgeArcInd = GetInternalArcIdx (nextEdgeBegVertIndex);
				circSegmentEnd.SetOrigo (newArcCenters.GetLast ());
				circSegmentEnd.SetRadius ((newPositions.GetLast () - circSegmentEnd.Origo ()).GetLength ());
				if (nextEdgeArcInd != 0) {
					//crossect the two circle
					const double nextEdgeArcAngle = arcs[nextEdgeArcInd].arcAngle;
					GenArc arcNext = GenArc::CreateCircleArc (vertices[nextEdgeBegVertIndex], vertices[nextEdgeEndVertIndex], nextEdgeArcAngle);
					Circle2D c (arcNext.GetOrigo (), (vertices[nextEdgeBegVertIndex] - arcNext.GetOrigo ()).GetLength ());
					Point2D commonArcEndPoint;
					if (JoinCircArcs (c, vertices[nextEdgeBegVertIndex], circSegmentEnd, newPositions.GetLast (), commonArcEndPoint)) {
						newPositions.GetLast () = commonArcEndPoint;
					}
				} else {
					//crossect the edge-line and the circle
					Point2D commonArcEndPoint;
					if (JoinCircArcAndStraightEdge (
						circSegmentEnd, newPositions.GetLast (),
						vertices[nextEdgeEndVertIndex], vertices[nextEdgeBegVertIndex],
						commonArcEndPoint)) {
						newPositions.GetLast () = commonArcEndPoint;
					}
				}
			}
		}
		else {
			Geometry::DivideEllArcToCo (genArcs.GetFirst (), arcDivParams.maxDifference, newPositions);
			for (UIndex i = 1; i < genArcs.GetSize (); ++i) {
				GS::Array<Point2D> appendPositions;
				Geometry::DivideEllArcToCo (genArcs[i], arcDivParams.maxDifference, appendPositions);
				DBASSERT (IsNear (newPositions.GetLast (), appendPositions.GetFirst ()));

				newPositions.DeleteLast ();
				newPositions.Append (appendPositions);
			}
		}

		if (arcDivParams.preferSegmentedArcEnds && DBVERIFY (!newPositions.IsEmpty ())) {
			begC = newPositions.GetFirst ();
			endC = newPositions.GetLast ();
		}
	}

	vertices[internalEdgeIdx] = begC;
	if (internalEdgeIdx == GetInternalVertexBeginIdxInContour (contourIdx)) {
		vertices[GetInternalVertexEndIdxInContour (contourIdx)] = begC;
	}

	vertices[nextInternalVertexIdx] = endC;
	if (nextInternalVertexIdx == GetInternalVertexBeginIdxInContour (contourIdx)) {
		vertices[GetInternalVertexEndIdxInContour (contourIdx)] = endC;
	}

	const UIndex arcInd = GetInternalArcIdx (internalEdgeIdx);
	if (singleCircleArc) {
		const double edgeAngle = genArcs.GetFirst ().GetArcAngle ();

		if (arcInd != 0) {
			arcs[arcInd].arcAngle = edgeAngle;
		} else {
			PolyArcRec arc;
			arc.begIndex = internalEdgeIdx;
			arc.endIndex = internalEdgeIdx + 1;
			arc.arcAngle = edgeAngle;
			arcs.Push (arc);
			nArcs++;
		}
	} else {
		if (arcInd != 0) {
			arcs.Delete (arcInd);
			nArcs--;
		}

		const UIndex followerIndex = internalEdgeIdx + 1;

		const Int32 insNum = newPositions.GetSize () - 2;		/* First and last no nedded */
		for (Int32 i = insNum; i > 0; --i)
			vertices.Insert (followerIndex, newPositions [i]);

		for (UIndex arcIdx = 1; arcIdx <= nArcs; ++arcIdx) {
			PolyArcRec& arc = arcs[arcIdx];
			if (arc.begIndex >= internalEdgeIdx) {
				arc.begIndex   += insNum;
				arc.endIndex += insNum;
			}
		}

		if (arcDivParams.preferCircArcsOverStraightSegments && newArcCenters.GetSize () + 1 == newPositions.GetSize () &&
			DBVERIFY (newArcCenters.GetSize () == newIsReflected.GetSize ())) {
			for (Int32 i = 0; i <= insNum; ++i) {
				//new arcs made here!
				GenArc arc = GenArc::CreateCircleArc (newArcCenters[i], newPositions[i], newPositions[i + 1], newIsReflected[i]);
				const double ang = arc.GetArcAngle ();
				if (fabs (ang) > RadEps && !CanArcBeReplacedWithSegment (arc)) {
					PolyArcRec arc;
					arc.begIndex = internalEdgeIdx + i;
					arc.endIndex = internalEdgeIdx + i + 1;
					arc.arcAngle = ang;
					arcs.Push (arc);
					nArcs++;
				}
			}
		}

		for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
			if (contourEnds[contourIdx] >= internalEdgeIdx)
				contourEnds[contourIdx] += insNum;
		}

		if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
			vertexInfos.SetSize (nVertices + 1 + insNum);
			CopyInfo_Data <VertexUserData> (vertexInfos, (followerIndex + insNum), vertexInfos, followerIndex, (nVertices - followerIndex + 1));
			for (Int32 i = 0; i < insNum; ++i)
				vertexInfos[followerIndex + i] = defaultVertexData;
		}
		if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
			inhEdgeInfos.SetSize (nVertices + 1 + insNum);
			CopyInfo_Data <EdgeUserData> (inhEdgeInfos, (followerIndex + insNum), inhEdgeInfos, followerIndex, (nVertices - followerIndex + 1));
			for (Int32 i = 0; i < insNum; ++i)
				inhEdgeInfos[followerIndex + i] = inhEdgeInfos[internalEdgeIdx];
		}
		nVertices += insNum;
	}

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdgeInternal (UIndex internalEdgeIdx, const GS::Array<double>& angles, const GS::Array<Point2D>& internalVerts)
{
	if (DBERROR (internalVerts.IsEmpty ())) {
		return;
	}

	if (DBERROR (internalVerts.GetSize () + 1 != angles.GetSize ())) {
		return;
	}

	DBCHECKCOREPOLY_ONEREFTOTHIS;

	status.isRegularized = false;
	flags.isSameDirEdgeLegal = true;	// ???

	const UIndex arcInd = GetInternalArcIdx (internalEdgeIdx);

	if (arcInd != 0) {
		arcs.Delete (arcInd);
		nArcs--;
	}

	const UIndex followerIndex = internalEdgeIdx + 1;

	const Int32 insNum = internalVerts.GetSize ();		/* In internalVerts the First and Last is missing! */
	for (Int32 i = insNum; i > 0; --i)
		vertices.Insert (followerIndex, internalVerts[i-1]);

	for (UIndex arcIdx = 1; arcIdx <= nArcs; ++arcIdx) {
		PolyArcRec& arc = arcs[arcIdx];
		if (arc.begIndex >= internalEdgeIdx) {
			arc.begIndex += insNum;
			arc.endIndex += insNum;
		}
	}

	for (Int32 i = 0; i <= insNum; ++i) {
		const double ang = angles[i];
		if (fabs (ang) > RadEps) {
			Point2D dummyOrigin;
			if (ArcGetOrigo (&vertices[internalEdgeIdx + i], &vertices[internalEdgeIdx + i + 1], ang, &dummyOrigin)) {
				PolyArcRec arc;
				arc.begIndex = internalEdgeIdx + i;
				arc.endIndex = internalEdgeIdx + i + 1;
				arc.arcAngle = ang;
				arcs.Push (arc);
				nArcs++;
			}
		}
	}

	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		if (contourEnds[contourIdx] >= internalEdgeIdx)
			contourEnds[contourIdx] += insNum;
	}

	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
		vertexInfos.SetSize (nVertices + 1 + insNum);
		CopyInfo_Data <VertexUserData> (vertexInfos, (followerIndex + insNum), vertexInfos, followerIndex, (nVertices - followerIndex + 1));
		for (Int32 i = 0; i < insNum; ++i)
			vertexInfos[followerIndex + i] = defaultVertexData;
	}
	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
		inhEdgeInfos.SetSize (nVertices + 1 + insNum);
		CopyInfo_Data <EdgeUserData> (inhEdgeInfos, (followerIndex + insNum), inhEdgeInfos, followerIndex, (nVertices - followerIndex + 1));
		for (Int32 i = 0; i < insNum; ++i)
			inhEdgeInfos[followerIndex + i] = inhEdgeInfos[internalEdgeIdx];
	}
	nVertices += insNum;

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertVertexInternal (UIndex internalEdgeIdx, const Point2D& newPosition, bool keepArc /*= false*/, bool insArc /*= false*/)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	status.isRegularized = false;
	flags.isSameDirEdgeLegal = true;

	vertices.Insert (internalEdgeIdx + 1, newPosition);

	GS::Int32 insArcInd = -1;

	for (UIndex arcIdx = 1; arcIdx <= nArcs; ++arcIdx) {
		PolyArcRec& arc = arcs[arcIdx];
		if ((arc.begIndex == internalEdgeIdx) && !keepArc) {
			insArcInd = arcIdx;
		}
		if (arc.begIndex > internalEdgeIdx || ((arc.begIndex == internalEdgeIdx) && keepArc && insArc)) {
			++arc.begIndex;
			++arc.endIndex;
		}
	}

	if (insArcInd >= 0) {
	/* arcs handle insArcInd elemenek torlese */
		arcs.Delete (insArcInd);
		nArcs -= 1;
	}

	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		if (contourEnds [contourIdx] >= internalEdgeIdx)
			++contourEnds [contourIdx];
	}

	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
		vertexInfos.SetSize (nVertices + 1 + 1);
		CopyInfo_Data <VertexUserData> (vertexInfos, (internalEdgeIdx + 1), vertexInfos, internalEdgeIdx, (nVertices - internalEdgeIdx + 1));
		vertexInfos [internalEdgeIdx + 1] = defaultVertexData;
	}
	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
		inhEdgeInfos.SetSize (nVertices + 1 + 1);
		CopyInfo_Data <EdgeUserData> (inhEdgeInfos, (internalEdgeIdx + 1), inhEdgeInfos, internalEdgeIdx, (nVertices - internalEdgeIdx + 1));
	}
	++nVertices;

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}



template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertEdgeInternal (UIndex vertexInternalIndex)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	status.isRegularized = false;
	flags.isSameDirEdgeLegal = true;

	const Point2D newPosition (vertices[vertexInternalIndex]);			//the coordnates are copied, as the new edge is zero length
	vertices.Insert (vertexInternalIndex + 1, newPosition);

	for (UIndex arcIdx = 1; arcIdx <= nArcs; ++arcIdx) {
		PolyArcRec& arc = arcs[arcIdx];

		if (arc.begIndex >= vertexInternalIndex) {
			++arc.begIndex;
			++arc.endIndex;
		}
	}

	UIndex actContourIdx     = GetContourIdxFromInternalVertexIdx (vertexInternalIndex);
	UIndex actBeginVertexIdx = GetInternalVertexBeginIdxInContour (actContourIdx);

	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		if (contourEnds[contourIdx] >= vertexInternalIndex)
			++contourEnds[contourIdx];
	}

	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
		vertexInfos.SetSize (nVertices + 1 + 1);
		CopyInfo_Data <VertexUserData> (vertexInfos, (vertexInternalIndex + 1), vertexInfos, vertexInternalIndex, (nVertices - vertexInternalIndex + 1));
		//vertexInfos for the new vertex will be the copy of the one that has been split; just before the new vertex!
	}
	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
		inhEdgeInfos.SetSize (nVertices + 1 + 1);
		CopyInfo_Data <EdgeUserData> (inhEdgeInfos, (vertexInternalIndex + 1), inhEdgeInfos, vertexInternalIndex, (nVertices - vertexInternalIndex + 1));
		inhEdgeInfos[vertexInternalIndex] = defaultEdgeData; //new edge!
		if (vertexInternalIndex == actBeginVertexIdx)
			inhEdgeInfos[GetInternalVertexEndIdxInContour (actContourIdx)] = defaultEdgeData;
	}
	++nVertices;

	//no need to update the bbox, as the geometry did not chage; only zero length edges were inserted!!!

	DBCHECKCOREPOLY_CHECK;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteVertexFromInternalData (UIndex internalVertexIdx)
{
	status.isRegularized = false;

	vertices.Delete (internalVertexIdx);

	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
		vertexInfos.Delete (internalVertexIdx);
	}

	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
		inhEdgeInfos.Delete (internalVertexIdx);
	}

	nVertices -= 1;

	// offset contours
	for (UIndex i = 1; i <= nContours; i++) {
		if (contourEnds[i] >= internalVertexIdx)
			--contourEnds[i];
	}

	// offset arcs
	for (UIndex i = 1; i <= nArcs; i++) {
		if (arcs[i].begIndex == internalVertexIdx) {
			arcs.Delete (i);
			--i;
			--nArcs;
		} else if (arcs[i].begIndex > internalVertexIdx) {
			--arcs[i].begIndex;
			--arcs[i].endIndex;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FixingContours ()
{
	for (UIndex iContour = 1; iContour <= nContours; iContour++) {
		UIndex iFirstContourVertex = iContour == 1 ? 1 : contourEnds[iContour - 1] + 1;

		while (contourEnds[iContour] - iFirstContourVertex < 2 && contourEnds[iContour] >= iFirstContourVertex) {
			DeleteVertexFromInternalData (iFirstContourVertex);
		}
	}

	for (UIndex iContour = 1; iContour <= nContours; iContour++) {
		UIndex iFirstContourVertex = iContour == 1 ? 1 : contourEnds[iContour - 1] + 1;
		if (contourEnds[iContour] >= iFirstContourVertex)
			continue;

		contourEnds.Delete (iContour);
		if (flags.isContourUserData && contourInfos.GetSize () != 0) {
			contourInfos.Delete (iContour);
		}

		nContours--;
		iContour--;
	}

	// utolsok visszalinkelese
	GS::UInt32	firstVert = 1;
	for (GS::UInt32 j = 1; j <= nContours; j++) {
		GS::UInt32	lastVert = contourEnds[j];

		if (lastVert <= firstVert) {
			DBBREAK ();
			continue;
		}

		vertices[lastVert] = vertices[firstVert];
		if (vertexInfos.GetSize () != 0 && flags.isVertexUserData)
			vertexInfos [lastVert] = vertexInfos [firstVert];
		if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData)
			inhEdgeInfos [lastVert] = inhEdgeInfos [firstVert];

		firstVert = lastVert + 1;
	}

	if (nVertices <= 1) {
		status.Clear ();

		nVertices = 0;
		vertices.Clear (true);
		vertexInfos.Clear (true);

		nArcs = 0;
		arcs.Clear (true);
		inhEdgeInfos.Clear (true);;

		nContours = 0;
		contourEnds.Clear (true);
		contourInfos.Clear (true);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Int32 CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::LineLineToDeleteEdge (const Sector &prevEdgeLine, const Sector &nextEdgeLine, Point2D *result)
{
	GS::Int32 resultCount;
	//line-line:
	if (!Geometry::XLinesEps (prevEdgeLine, nextEdgeLine, result, 2 * Eps, 2 * Eps)) {
		resultCount = 0;
	} else {
		resultCount = 1;
		Sector tmpSect = Sector (prevEdgeLine.c2, *result);
		if (Geometry::InternalCoord (tmpSect, prevEdgeLine.c1, Geometry::Boundary_Closed))
			resultCount = 0;
		tmpSect = Sector (prevEdgeLine.c1, prevEdgeLine.c2);
		if (resultCount != 0 && Geometry::InternalCoord (tmpSect, *result, Geometry::Boundary_Closed))
			resultCount = 0;
		tmpSect = Sector (nextEdgeLine.c1, *result);
		if (resultCount != 0 && Geometry::InternalCoord (tmpSect, nextEdgeLine.c2, Geometry::Boundary_Closed))
			resultCount = 0;
		tmpSect = Sector (nextEdgeLine.c1, nextEdgeLine.c2);
		if (resultCount != 0 && Geometry::InternalCoord (tmpSect, *result, Geometry::Boundary_Closed))
			resultCount = 0;
	}
	return resultCount;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeArcToDeleteEdge (GS::Int32& arcInd, bool& isEdgeArc, GenArc& edgeArc, Point2D& edgeArcCentre, double& edgeArcViewAngle, UIndex edgeIdx, const Point2D& vertFromPt, const Point2D& vertFromTo) const
{
	arcInd = GetInternalArcIdx (edgeIdx);
	isEdgeArc        = (arcInd > 0);
	edgeArc          = (arcInd > 0) ? GenArc::CreateCircleArc (vertFromPt, vertFromTo, arcs[arcInd].arcAngle) : GenArc ();	// TODO use Set... functions
	edgeArcCentre    = edgeArc.GetOrigo ();
	edgeArcViewAngle = CalcRotFi (edgeArc.GetBegAng (), edgeArc.GetEndAng (), edgeArc.IsReflected ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonDeleteEdge (UIndex edgeIdx)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	bool success = true;

	/* initializing the variables */
	UIndex	contourIdx = GetContourIdxFromInternalVertexIdx (edgeIdx);
	UIndex	begContourIdx = 0;
	UIndex	endContourIdx = 0;

	if (edgeIdx <= nVertices) {
		begContourIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		endContourIdx = GetInternalVertexEndIdxInContour (contourIdx) - 1;
	} else {
		throw GeometryAlgorithmErrorException ("Invalid edgeidx, can not delete the edge!", __FILE__, __LINE__);
	}

	if (endContourIdx - begContourIdx < 3) {
		return false;
	}

	UIndex  nextEdgeIdx = (edgeIdx + 1 > endContourIdx) ? begContourIdx : edgeIdx + 1;
	UIndex  next2EdgeIdx = (nextEdgeIdx + 1 > endContourIdx) ? begContourIdx : nextEdgeIdx + 1;
	UIndex	prevEdgeIdx = (edgeIdx - 1 < begContourIdx) ? endContourIdx : edgeIdx - 1;
	Point2D	actVertPt;
	Point2D	prevVertPt;
	Point2D	nextVertPt;
	Point2D	next2VertPt;

	prevVertPt = vertices[prevEdgeIdx];
	actVertPt  = vertices[edgeIdx];
	nextVertPt = vertices[nextEdgeIdx];
	next2VertPt = vertices[next2EdgeIdx];

	GS::Int32	arcIndBeg, arcIndEnd;
	bool		isPrevEdgeArc, isNextEdgeArc;
	GenArc		prevEdgeArc, nextEdgeArc;
	Point2D		prevEdgeArcCentre, nextEdgeArcCentre;
	double		prevEdgeArcViewAngle, nextEdgeArcViewAngle;
	SetEdgeArcToDeleteEdge (arcIndBeg, isPrevEdgeArc, prevEdgeArc, prevEdgeArcCentre, prevEdgeArcViewAngle, prevEdgeIdx, prevVertPt, actVertPt);
	SetEdgeArcToDeleteEdge (arcIndEnd, isNextEdgeArc, nextEdgeArc, nextEdgeArcCentre, nextEdgeArcViewAngle, nextEdgeIdx, nextVertPt, next2VertPt);

	Sector	prevEdgeLine;
	Sector	nextEdgeLine;

	prevEdgeLine.c1 = prevVertPt;
	prevEdgeLine.c2 = actVertPt;
	nextEdgeLine.c1 = nextVertPt;
	nextEdgeLine.c2 = next2VertPt;

	double	newPrevEdgeArcViewAngle = 0.0;
	double	newNextEdgeArcViewAngle = 0.0;
	Sector	sector;
	GS::Int32	resultCount = 0;
	Point2D	resultCoord;

	if (isPrevEdgeArc && isNextEdgeArc) {
		//circle-circle
		Circle2D c1 (prevEdgeArcCentre, Geometry::Dist (prevEdgeArcCentre, prevVertPt));
		Circle2D c2 (nextEdgeArcCentre, Geometry::Dist (nextEdgeArcCentre, nextVertPt));

		if (!Geometry::XCircles (&c1, &c2, &sector))
			resultCount = 0;
		else
			resultCount = 2;

	} else if (!isPrevEdgeArc && !isNextEdgeArc) {
		resultCount = LineLineToDeleteEdge (prevEdgeLine, nextEdgeLine, &sector.c1);
	} else if (isPrevEdgeArc) {
		//circle-line:
		Circle2D c (prevEdgeArcCentre, Geometry::Dist (prevEdgeArcCentre, prevVertPt));
		resultCount = Geometry::XCircleLineEps (&c, &nextEdgeLine, &sector, 2 * Eps);
	} else {
		//line-circle:
		Circle2D c (nextEdgeArcCentre, Geometry::Dist (nextEdgeArcCentre, nextVertPt));
		resultCount = Geometry::XCircleLineEps (&c, &prevEdgeLine, &sector, 2 * Eps);
	}

	if (resultCount == 2 || resultCount == 3) {
		Point2D actBegPt = actVertPt;
		Point2D actEndPt = nextVertPt;
		double tempDist1 = Dist (sector.c1, actBegPt) + Dist (sector.c1, actEndPt);
		double tempDist2 = Dist (sector.c2, actBegPt) + Dist (sector.c2, actEndPt);
		if (tempDist1 < tempDist2)
			resultCoord = sector.c1;
		else
			resultCoord = sector.c2;
	} else if (resultCount == 1) {
		resultCoord = sector.c1;
	} else {
		return false;
	}

	if (isPrevEdgeArc)
		GetViewAngle (
		&prevEdgeArcCentre,
		&prevVertPt,
		&resultCoord,
		prevEdgeArcViewAngle,
		1,
		&newPrevEdgeArcViewAngle);

	if (isNextEdgeArc)
		GetViewAngle (
		&nextEdgeArcCentre,
		&resultCoord,
		&next2VertPt,
		nextEdgeArcViewAngle,
		1,
		&newNextEdgeArcViewAngle);

	if (isPrevEdgeArc)
		arcs[arcIndBeg].arcAngle = newPrevEdgeArcViewAngle;
	if (isNextEdgeArc)
		arcs[arcIndEnd].arcAngle = newNextEdgeArcViewAngle;
	vertices[nextEdgeIdx] = resultCoord;
	DeleteVertexFromInternalData (edgeIdx);

	vertices [endContourIdx] = vertices [begContourIdx];
	if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
		vertexInfos [endContourIdx] = vertexInfos [begContourIdx];
	}
	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
		inhEdgeInfos [endContourIdx] = inhEdgeInfos [begContourIdx];
	}

	return success;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertVertexSplitArc (UIndex internalEdgeIdx, const Point2D& newPosition)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	for (UIndex i = 1; i <= nArcs; ++i) {
		if (arcs[i].begIndex == internalEdgeIdx) {
			arcs.Insert (i, arcs[i]);
			++nArcs;
			++i;
			++arcs[i].begIndex;
			++arcs[i].endIndex;
		} else if (arcs[i].begIndex > internalEdgeIdx) {
			++arcs[i].begIndex;
			++arcs[i].endIndex;
		}
	}

	/* vertices handle insIndex elemenek insertalasa */
	vertices.Insert (internalEdgeIdx + 1, newPosition);
	if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
		/* vertexInfos handle insIndex elemenek insertalasa */
		vertexInfos.SetSize (nVertices + 2);
		CopyInfo_Data <VertexUserData> (vertexInfos, (internalEdgeIdx + 2), vertexInfos, (internalEdgeIdx + 1), (nVertices - internalEdgeIdx));
		vertexInfos [internalEdgeIdx + 1] = defaultVertexData;
	}
	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
		/* inhEdgeInfos handle insIndex elemenek insertalasa */
		inhEdgeInfos.SetSize (nVertices + 2);
		CopyInfo_Data <EdgeUserData> (inhEdgeInfos, (internalEdgeIdx + 2), inhEdgeInfos, (internalEdgeIdx + 1), (nVertices - internalEdgeIdx));
		inhEdgeInfos [internalEdgeIdx + 1] = inhEdgeInfos [internalEdgeIdx] /*defaultEdgeData*/;
	}

	++nVertices;
	UIndex contIdx = GetContourIdxFromInternalVertexIdx (internalEdgeIdx);
	for (UIndex i = contIdx; i <= nContours; ++i)
		++contourEnds[i];
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OrientInternalDData (void)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	// using reportMask (example for orientation, bit0):
	// bit0 = 0 as input: if the orientation was incorrect during validation, bit0 = 1 as output
	// bit0 = 1 as input: just checking, returns NoError if the orientation was incorrect, otherwise bit0 = 0 as output

	bool						isOrientationGood;

	/* checking the right orientation for all contour */
	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		double	area = CalcContourArea (contourIdx);

		if (contourIdx == 1)
			isOrientationGood = area >= 0.0;	/* a konturnak pozitiv, a lyukaknak negativ koruljarasuaknak kell lennie */
		else
			isOrientationGood = area <= 0.0;
		// if must revert
		if (!isOrientationGood) {
			DBASSERT (status.isRegularized == false);

			UIndex	iBegContour = (contourIdx > 1) ? (contourEnds[contourIdx - 1] + 1) : 1;
			UIndex	iEndContour = contourEnds[contourIdx];
			UIndex	tmpInd;

			Point2D ptChange;
			VertexUserData vtChange;
			EdgeUserData   etChange;
			for (UIndex iVertex = iBegContour; iVertex <= iBegContour + (iEndContour - iBegContour) / 2; iVertex++) {

				// revert vertices
				ptChange = vertices[iVertex];
				vertices[iVertex] = vertices[iBegContour + iEndContour - iVertex];
				vertices[iBegContour + iEndContour - iVertex] = ptChange;
				// revert additional data
				if (vertexInfos.GetSize () != 0) {
					vtChange = vertexInfos[iVertex];
					vertexInfos[iVertex] = vertexInfos[iBegContour + iEndContour - iVertex];
					vertexInfos[iBegContour + iEndContour - iVertex] = vtChange;
				}
				if (inhEdgeInfos.GetSize () != 0) {
					if (iVertex == iBegContour + (iEndContour - iBegContour) / 2) {	// RJ #16960
						inhEdgeInfos[iEndContour] = inhEdgeInfos[iBegContour];
					} else {
						etChange = inhEdgeInfos[iVertex];
						inhEdgeInfos[iVertex] = inhEdgeInfos[iBegContour + iEndContour - iVertex - 1];
						inhEdgeInfos[iBegContour + iEndContour - iVertex - 1] = etChange;
					}
				}
			}

			//revert arcs
			for (UIndex iArc = 1; iArc <= nArcs; iArc++) {
				tmpInd = arcs[iArc].begIndex;
				if (tmpInd >= iBegContour && tmpInd < iEndContour) {
					if (tmpInd != iEndContour - 1) {
						arcs[iArc].begIndex = iEndContour + iBegContour - tmpInd - 1;
						arcs[iArc].endIndex = iEndContour + iBegContour - tmpInd;
					} else {
						arcs[iArc].begIndex = iBegContour;
						arcs[iArc].endIndex = iBegContour + 1;
					}
					arcs[iArc].arcAngle = -arcs[iArc].arcAngle;
				}
			}
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CheckOrientInternalData (void) const
{
	bool isOrientationGood = true;

	/* checking the right orientation for all contour */
	for (UIndex contourIdx = 1; contourIdx <= nContours && isOrientationGood; contourIdx++) {
		double	area = CalcContourArea (contourIdx);

		if (contourIdx == 1)
			isOrientationGood = area > -SmallEps;	/* a konturnak pozitiv, a lyukaknak negativ koruljarasuaknak kell lennie */
		else
			isOrientationGood = area < SmallEps;

		if (!isOrientationGood)
			break;
	}

	return isOrientationGood;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
Box2DData CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcBoundBox (void) const
{
	Box2DData tmpBoundBox;

	// if empty polygon
	if (nContours < 1) {
		return tmpBoundBox;
	}

	// go through only the main contour vertices when regularized
	UIndex	nConsideredVertices = (status.isRegularized) ? contourEnds[1] : nVertices;
	for (UIndex iVertex = 1; iVertex <= nConsideredVertices; iVertex++) {
		tmpBoundBox.xMin = MIN (tmpBoundBox.xMin, vertices[iVertex].x);
		tmpBoundBox.yMin = MIN (tmpBoundBox.yMin, vertices[iVertex].y);
		tmpBoundBox.xMax = MAX (tmpBoundBox.xMax, vertices[iVertex].x);
		tmpBoundBox.yMax = MAX (tmpBoundBox.yMax, vertices[iVertex].y);
	}

	// go through only the main contour arcs when regularized
	for (UIndex iArc = 1; iArc <= nArcs; iArc++) {
		if (arcs[iArc].begIndex <= nConsideredVertices) {
			const Point2D&	ptBeg = vertices[arcs[iArc].begIndex];
			const Point2D&	ptEnd = vertices[arcs[iArc].endIndex];
			Point2D	ptCenter;
			if (Geometry::ArcGetOrigo (&ptBeg, &ptEnd, arcs[iArc].arcAngle, &ptCenter)) {
				double	angBeg = Geometry::ComputeFi (ptCenter, ptBeg);
				double	angEnd = Geometry::ComputeFi (ptCenter, ptEnd);
				double	radius = (ptCenter - ptBeg).GetLength ();
				/* if back-oriented */
				if (arcs[iArc].arcAngle < 0.0) {
					GS::Swap (angBeg, angEnd);
				}
				if (Geometry::IsInsideAngle (angBeg, angEnd, 0.0)) {
					tmpBoundBox.xMax = MAX (tmpBoundBox.xMax, ptCenter.x + radius);
				}
				if (Geometry::IsInsideAngle (angBeg, angEnd, PI / 2.0)) {
					tmpBoundBox.yMax = MAX (tmpBoundBox.yMax, ptCenter.y + radius);
				}
				if (Geometry::IsInsideAngle (angBeg, angEnd, PI)) {
					tmpBoundBox.xMin = MIN (tmpBoundBox.xMin, ptCenter.x - radius);
				}
				if (Geometry::IsInsideAngle (angBeg, angEnd, 3.0 * PI / 2.0)) {
					tmpBoundBox.yMin = MIN (tmpBoundBox.yMin, ptCenter.y - radius);
				}
			}
		}
	}
	return tmpBoundBox;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::UpdateBoundingBox (void)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	boundBox = CalcBoundBox ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::UpdateOrientation (void)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	OrientInternalDData ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CanIrregular (bool& reverseOrient) const
{
	if (nVertices == 0)
		return false;

	if (nArcs > 0 || nContours > 1)
		return true;

	Point2D innerPoint = Point2D (0.0, 0.0);
	for (UIndex coordIdx = 1; coordIdx < nVertices; coordIdx++) {
		innerPoint.x += vertices[coordIdx].x;
		innerPoint.y += vertices[coordIdx].y;
	}
	innerPoint.x /= nVertices - 1;
	innerPoint.y /= nVertices - 1;

	Geometry::Vector2d firstVertexVector = vertices[1] - innerPoint;
	bool relAngleToFirstVertexChanged = false;

	double crossProduct = 0.0;
	Geometry::Vector2d prevVertexVector;
	Geometry::Vector2d nextVertexVector = firstVertexVector;
	bool positive = true;
	for (UIndex coordIdx = 2; coordIdx <= nVertices; coordIdx++) {
		prevVertexVector = nextVertexVector;
		nextVertexVector = vertices[coordIdx] - innerPoint;
		crossProduct = prevVertexVector ^ nextVertexVector;
		if (fabs (crossProduct) < EPS)
			return true;
		if (coordIdx == 2) {
			positive = crossProduct > 0.0;
			continue;
		}

		if (positive != (crossProduct > 0.0))
			return true;

		if (coordIdx == nVertices)
			continue;

		if (((firstVertexVector ^ nextVertexVector) > 0.0) != positive) {
			relAngleToFirstVertexChanged = true;
		} else {
			if (relAngleToFirstVertexChanged)
				return true;
		}
	}

	reverseOrient = !positive;
	return false;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::HasShortEdges () const
{
	for (UIndex iContour = 1; iContour <= nContours; iContour++) {
		for (GS::UInt32 i = iContour == 1 ? 1 : contourEnds[iContour - 1] + 1; i < contourEnds[iContour]; i++) {
			if (Dist (vertices[i], vertices[i + 1]) < Eps) {
				return true;
			}
		}
	}
	return false;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult  CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Regularize (GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result, PolyRegularizationMode mode) const
{
	GSErr errorCode = NoError;

	if (status.isRegularized)
		return ResultSameAsThis;

	if (this->IsEmpty ()) {
		status.isRegularized = true;
		return ResultSameAsThis;
	}

	if (nVertices <= 2)
		return EmptyPolygon;

	//DBCHECKCOREPOLY_ONEREFTOTHIS; //tobb hivatkozas is lehet egy CorePolygon2D-re regularizalaskor. Ez egy majdnem const method, csak az isRegularized-et modositja es ez elvileg nem okozhat gondot, ha megvaltozik.

	bool canIrragular;
	bool reverseOrient;
	canIrragular = CanIrregular (reverseOrient);
	if (!canIrragular && flags.isSameDirEdgeLegal && !HasShortEdges ()) {
		if (!reverseOrient) {
			status.isRegularized = true;
			return ResultSameAsThis;
		}

		GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
		tmpPoly->OrientInternalDData ();
		tmpPoly->status.isRegularized = true;

		result.Push (tmpPoly);

		DBCHECKCOREPOLY_CHECKRESULT;
		return NewPolygons;
	}

	//A bounding box-nak updatelve kell lenni

	Geometry::PGRelPolyPosExt	pgstatus = UnknownStatus;
	Geometry::PGPOLYEXT			polyExt1;

	//Jelenleg ugy regularizalunk csak, hogy az elso kontour a fo kontour a tobbi a lyuk. De a PG figyeli a koruljarast es abbol donti el, hogy mi a lyuk es mi nem
	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > clonedPolygon;
	if (!CheckOrientInternalData ()) {
		clonedPolygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
		clonedPolygon->UpdateOrientation ();

		clonedPolygon->MakePolyExt (polyExt1);
	} else {
		MakePolyExt (polyExt1);
	}

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyMakeRegular2Ext (&polyExt1, &resPolyExt, true, nullptr /*breaker*/, KeepMainContour, &pgstatus, mode);
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::Regularize", __FILE__, __LINE__);
	DBASSERT (pgstatus != UnknownStatus);
	if (pgstatus == PolysEqual) {
		DBCHECKCOREPOLY_CHECK;
		DBASSERT (result.GetSize () == 0);

		if (HasShortEdges ()) {
			if (clonedPolygon == nullptr) {
				clonedPolygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
			}
			clonedPolygon->RemoveZeroEdgesAndArcs (Eps, Eps);
			clonedPolygon->UpdateOrientation ();
			clonedPolygon->MakePolyExt (polyExt1);
			errorCode = Geometry::PGPolyMakeRegular2Ext (&polyExt1, &resPolyExt, true, nullptr /*breaker*/, KeepMainContour);
			ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::Regularize", __FILE__, __LINE__);
		} else if (clonedPolygon != nullptr) {
			clonedPolygon->status.isRegularized = true;
			result.Push (clonedPolygon);
			return NewPolygons;
		} else {
			status.isRegularized = true;
			return ResultSameAsThis;
		}
	}

	for (UIndex polyIdx = 0; polyIdx < result.GetSize (); polyIdx++)
		result[polyIdx]->RemoveSmallArcs ();

	for (typename GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >::Iterator it = result.Enumerate (); it != nullptr; ++it)
		(*it)->status.isRegularized = true;

	DBCHECKCOREPOLY_CHECKRESULT;
	return (result.GetSize () > 0) ? NewPolygons : EmptyPolygon;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetIdsForRegularizationResultsOneNullVertex (const PolyId& edgeId, bool& thisContourRev, const UIndex& vertexIdx, const UIndex& contourIdx, const UIndex& polyIdx, GS::Array<UIndex>& revContourIdxsCurrPoly, const CorePolygon2D<PolyId, PolyId, PolyId, PolyId>& polygonCopy, const GS::Array<GS::SharedPtr<CorePolygon2D<PolyId, PolyId, PolyId, PolyId> > >& result1) const
{
	// both begin and end vertices are new (both Ids are NullId)
	UIndex origArcIdx = GetInternalArcIdx (edgeId.Get ());
	UIndex resArcIdx = result1[polyIdx]->GetInternalArcIdx (vertexIdx);
	DBASSERT ((origArcIdx > 0 && resArcIdx > 0) || (origArcIdx == 0 && resArcIdx == 0));
	// if the edge had a non-zero angle
	if (origArcIdx > 0) {
		// if the angle flipped: it is reversed
		if (polygonCopy.arcs[origArcIdx].arcAngle * result1[polyIdx]->arcs[resArcIdx].arcAngle < 0.0) {
			if (!revContourIdxsCurrPoly.Contains (contourIdx) && thisContourRev)
				revContourIdxsCurrPoly.Push (contourIdx);
		} else {
			if (!revContourIdxsCurrPoly.Contains (contourIdx))
				thisContourRev = false;
		}
	} else { // otherwise check the begin to end edge directions
		Vector2D origEdgeVector = polygonCopy.vertices[edgeId.Get () + 1] - polygonCopy.vertices[edgeId.Get ()];
		Vector2D resEdgeVector = result1[polyIdx]->vertices[vertexIdx+1] - result1[polyIdx]->vertices[vertexIdx];
		if (origEdgeVector * resEdgeVector < 0.0) {
			if (!revContourIdxsCurrPoly.Contains (contourIdx) && thisContourRev)
				revContourIdxsCurrPoly.Push (contourIdx);
		} else {
			if (!revContourIdxsCurrPoly.Contains (contourIdx))
				thisContourRev = false;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetIdsForRegularizationResultsOneContour (GS::Array<UIndex>& vertexIds, GS::Array<UIndex>& edgeIds, UIndex& vertexIdx, UIndex& contourIdx, UIndex& polyIdx, GS::Array<UIndex>& revContourIdxsCurrPoly, UIndex& regularizationResults /*PolyRegularizationFlags*/, const CorePolygon2D<PolyId, PolyId, PolyId, PolyId>& polygonCopy, const GS::Array<GS::SharedPtr<CorePolygon2D<PolyId, PolyId, PolyId, PolyId> > >& result1) const
{
	bool thisContourRev = true;
	for (; vertexIdx < result1[polyIdx]->contourEnds[contourIdx]; ++vertexIdx) {
		if ((result1[polyIdx]->vertexInfos)[vertexIdx] == NullPolyId) {
			regularizationResults |= PolyRegularizationFlags_NewVertex;
			regularizationResults |= PolyRegularizationFlags_WasIrregular;
		} else {
			vertexIds.Push ((result1[polyIdx]->vertexInfos)[vertexIdx].Get ());
		}
		// to our current knowledge regularization cannot create new edges
		PolyId edgeId = (result1[polyIdx]->inhEdgeInfos)[vertexIdx];
		DBASSERT (edgeId != NullPolyId);
		if (edgeId == NullPolyId) {
			regularizationResults |= PolyRegularizationFlags_NewEdge;
			regularizationResults |= PolyRegularizationFlags_WasIrregular;
		} else {
			PolyId edgeBegId = (result1[polyIdx]->vertexInfos)[vertexIdx];
			PolyId edgeEndId = (result1[polyIdx]->vertexInfos)[vertexIdx+1];
			if (!(edgeBegId == edgeId && (edgeEndId.Get () == (edgeId.Get () + 1) ||
				((edgeId.Get () + 1 == result1[polyIdx]->contourEnds[contourIdx]) &&
				(edgeEndId.Get () == result1[polyIdx]->contourEnds[contourIdx-1]+1))))) {
					regularizationResults |= PolyRegularizationFlags_WasIrregular;
					if (edgeEndId != NullPolyId) {
						if (edgeEndId.Get () <= edgeId.Get ()) {
							if (polygonCopy.contourEnds.Contains (edgeId.Get () + 1)) {
								UIndex origContourIdx = polygonCopy.contourEnds.FindFirst (edgeId.Get () + 1);
								if (edgeEndId.Get () != polygonCopy.contourEnds[origContourIdx-1]+1) {
									if (!revContourIdxsCurrPoly.Contains (contourIdx) && thisContourRev)
										revContourIdxsCurrPoly.Push (contourIdx);
								} else {
									if (!revContourIdxsCurrPoly.Contains (contourIdx))
										thisContourRev = false;
								}
							} else {
								if (!revContourIdxsCurrPoly.Contains (contourIdx) && thisContourRev)
									revContourIdxsCurrPoly.Push (contourIdx);
							}
						} else {
							if (!revContourIdxsCurrPoly.Contains (contourIdx))
								thisContourRev = false;
						}
					} else {
						if (edgeBegId != NullPolyId) {
							if (edgeBegId.Get () > edgeId.Get ()) {
								if (!revContourIdxsCurrPoly.Contains (contourIdx) && thisContourRev)
									revContourIdxsCurrPoly.Push (contourIdx);
							} else {
								if (polygonCopy.contourEnds.Contains (edgeId.Get () + 1)) {
									UIndex origContourIdx = polygonCopy.contourEnds.FindFirst (edgeId.Get () + 1);
									if (edgeBegId.Get () == polygonCopy.contourEnds[origContourIdx-1]+1) {
										if (!revContourIdxsCurrPoly.Contains (contourIdx) && thisContourRev)
											revContourIdxsCurrPoly.Push (contourIdx);
									} else {
										if (!revContourIdxsCurrPoly.Contains (contourIdx))
											thisContourRev = false;
									}
								} else {
									if (!revContourIdxsCurrPoly.Contains (contourIdx))
										thisContourRev = false;
								}
							}
						} else {
							SetIdsForRegularizationResultsOneNullVertex (edgeId, thisContourRev, vertexIdx, contourIdx, polyIdx, revContourIdxsCurrPoly, polygonCopy, result1);
						}
					}
			}
			edgeIds.Push (edgeId.Get ());
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetIdsForRegularizationResults (GS::Array<UIndex>& vertexIds, GS::Array<UIndex>& edgeIds, GS::Array<UIndex>& contourIds, UIndex& regularizationResults /*PolyRegularizationFlags*/, GS::Array< GS::Array<UIndex> >* reversedContourIdxs, const CorePolygon2D<PolyId, PolyId, PolyId, PolyId>& polygonCopy, const GS::Array<GS::SharedPtr<CorePolygon2D<PolyId, PolyId, PolyId, PolyId> > >& result1) const
{
	UIndex vertexIdx, contourIdx;
	for (UIndex polyIdx = 0; polyIdx < result1.GetSize (); ++polyIdx) {
		GS::ArrayFB<UIndex, 6> revContourIdxsCurrPoly;
		vertexIdx = 1;
		for (contourIdx = 1; contourIdx <= result1[polyIdx]->nContours; ++contourIdx) {
			if ((result1[polyIdx]->contourInfos)[contourIdx] == NullPolyId) {
				regularizationResults |= PolyRegularizationFlags_NewContour;
				regularizationResults |= PolyRegularizationFlags_WasIrregular;
			} else {
				contourIds.Push ((result1[polyIdx]->contourInfos)[contourIdx].Get ());
			}
			SetIdsForRegularizationResultsOneContour (vertexIds, edgeIds, vertexIdx, contourIdx, polyIdx, revContourIdxsCurrPoly, regularizationResults, polygonCopy, result1);
			++vertexIdx;
			if (revContourIdxsCurrPoly.Contains (contourIdx))
				regularizationResults |= PolyRegularizationFlags_ReversedContour;
		}
		if (reversedContourIdxs != nullptr)
			reversedContourIdxs->Push (revContourIdxsCurrPoly);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetRegularizationResults (UIndex regularizationResultsMask /*PolyRegularizationFlags*/, UIndex& regularizationResults /*PolyRegularizationFlags*/, GS::Array< GS::Array<UIndex> >* reversedContourIdxs, const CorePolygon2D<PolyId, PolyId, PolyId, PolyId>& polygonCopy, const GS::Array<GS::SharedPtr<CorePolygon2D<PolyId, PolyId, PolyId, PolyId> > >& result1) const
{
	UIndex vertexIdx, contourIdx;
	bool onlyIrregularity = (regularizationResultsMask == PolyRegularizationFlags_WasIrregular);

	if (result1.GetSize () != 1 || result1[0]->nContours != nContours || result1[0]->nVertices != nVertices || result1[0]->nArcs != nArcs)
		regularizationResults |= PolyRegularizationFlags_WasIrregular;

	if (!onlyIrregularity || !(regularizationResults & PolyRegularizationFlags_WasIrregular)) {
		GS::ArrayFB<UIndex, 6> vertexIds;
		GS::ArrayFB<UIndex, 6> edgeIds;
		GS::ArrayFB<UIndex, 6> contourIds;

		SetIdsForRegularizationResults (vertexIds, edgeIds, contourIds, regularizationResults, reversedContourIdxs, polygonCopy, result1);
		vertexIdx = 1;
		for (contourIdx = 1; contourIdx <= nContours; ++contourIdx) {
			if (!contourIds.Contains (contourIdx)) {
				regularizationResults |= PolyRegularizationFlags_LostContour;
			} else if (contourIds.Count (contourIdx) > 1) {
				regularizationResults |= PolyRegularizationFlags_SplitContour;
			}
			for (; vertexIdx < contourEnds[contourIdx]; ++vertexIdx) {
				if (!vertexIds.Contains (vertexIdx)) {
					regularizationResults |= PolyRegularizationFlags_LostVertex;
				}
				if (!edgeIds.Contains (vertexIdx)) {
					regularizationResults |= PolyRegularizationFlags_LostEdge;
				} else if (edgeIds.Count (vertexIdx) > 1) {
					regularizationResults |= PolyRegularizationFlags_SplitEdge;
				}
			}
			++vertexIdx;
		}
		if ((regularizationResults & PolyRegularizationFlags_WasIrregular) &&
			!(regularizationResults & PolyRegularizationFlags_NewVertex) && !(regularizationResults & PolyRegularizationFlags_NewEdge) &&
			!(regularizationResults & PolyRegularizationFlags_NewContour) && !(regularizationResults & PolyRegularizationFlags_LostVertex) &&
			!(regularizationResults & PolyRegularizationFlags_LostEdge) && !(regularizationResults & PolyRegularizationFlags_LostContour) &&
			!(regularizationResults & PolyRegularizationFlags_SplitEdge) && !(regularizationResults & PolyRegularizationFlags_SplitContour) &&
			(regularizationResults & PolyRegularizationFlags_ReversedContour))
			regularizationResults |= PolyRegularizationFlags_OnlyReversed;
		// mask the output flags
		regularizationResults &= regularizationResultsMask;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CreateRegularizationResult (const CorePolygon2D<PolyId, PolyId, PolyId, PolyId>& polygonCopy, const GS::Array<GS::SharedPtr<CorePolygon2D<PolyId, PolyId, PolyId, PolyId> > >& result1, GS::Array<GS::SharedPtr<CorePolygon2D> >& result) const
{
	result.Clear (true);
	UIndex contourIdx = 0;
	UIndex vertexIdx = 1;
	for (UIndex polyIdx = 0; polyIdx < result1.GetSize (); ++polyIdx) {
		GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (flags);	/* Ez mr altalnos polygon (templates */
		CorePolygon2D<PolyId, PolyId, PolyId, PolyId> poppedPoly = (*result1[polyIdx]);			/* Ez polyId-s polygon */
		poppedPoly.SetIsVertexUserData (false);
		poppedPoly.SetIsEdgeUserData (false);
		poppedPoly.SetIsContourUserData (false);
		tmpPoly->template CopyInternalDataFromWithUserData<PolyId, PolyId, PolyId, PolyId> (poppedPoly, 0, 0, 0, nullptr);	/* Itt copyzzuk t nem PolyId-s polygonna !!!! */
		if (flags.isVertexUserData)
			tmpPoly->vertexInfos.SetSize (result1[polyIdx]->vertexInfos.GetSize ());
		if (flags.isEdgeUserData)
			tmpPoly->inhEdgeInfos.SetSize (result1[polyIdx]->inhEdgeInfos.GetSize ());
		if (flags.isContourUserData)
			tmpPoly->contourInfos.SetSize (result1[polyIdx]->contourInfos.GetSize ());
		if (flags.isPolygonUserData)
			tmpPoly->inhPolygonInfo.SetSize (result1[polyIdx]->inhPolygonInfo.GetSize ());

		vertexIdx = 1;
		tmpPoly->flags /*result[polyIdx]->flags*/ = flags;
		for (contourIdx = 1; contourIdx <= result1[polyIdx]->nContours; ++contourIdx) {
			if (!flags.isContourUserData)
				(tmpPoly->contourInfos).Clear (true);
			else if ((result1[polyIdx]->contourInfos)[contourIdx] != NullPolyId)
				tmpPoly->contourInfos[contourIdx] = (contourInfos) [(result1[polyIdx]->contourInfos)[contourIdx].Get ()];
			if (!flags.isVertexUserData)
				(tmpPoly->vertexInfos).Clear (true);
			if (!flags.isEdgeUserData)
				(tmpPoly->inhEdgeInfos).Clear (true);
			for (; vertexIdx < result1[polyIdx]->contourEnds[contourIdx]; ++vertexIdx) {
				if (result1[polyIdx]->vertexInfos.GetSize() != 0  && tmpPoly->vertexInfos.GetSize () != 0 && (result1[polyIdx]->vertexInfos)[vertexIdx] != NullPolyId)
					tmpPoly->vertexInfos[vertexIdx] = (vertexInfos) [(result1[polyIdx]->vertexInfos)[vertexIdx].Get ()];
				if (result1[polyIdx]->inhEdgeInfos.GetSize() != 0 && tmpPoly->inhEdgeInfos.GetSize () != 0 && (result1[polyIdx]->inhEdgeInfos)[vertexIdx] != NullPolyId)
					tmpPoly->inhEdgeInfos[vertexIdx] = (inhEdgeInfos) [(result1[polyIdx]->inhEdgeInfos)[vertexIdx].Get ()];
			}
			if (result1[polyIdx]->vertexInfos.GetSize() != 0  && tmpPoly->vertexInfos.GetSize () != 0 && (result1[polyIdx]->vertexInfos)[vertexIdx] != NullPolyId)
				tmpPoly->vertexInfos[vertexIdx] = (vertexInfos) [(result1[polyIdx]->vertexInfos)[vertexIdx].Get ()];
			if (result1[polyIdx]->inhEdgeInfos.GetSize() != 0 && tmpPoly->inhEdgeInfos.GetSize () != 0 && (result1[polyIdx]->inhEdgeInfos)[vertexIdx] != NullPolyId)
				tmpPoly->inhEdgeInfos[vertexIdx] = (inhEdgeInfos) [(result1[polyIdx]->inhEdgeInfos)[vertexIdx].Get ()];
			++vertexIdx;
		}
		if (flags.isPolygonUserData)
			if (result1[polyIdx]->inhPolygonInfo[0] == polygonCopy.inhPolygonInfo[0])
				tmpPoly->inhPolygonInfo[0] = inhPolygonInfo [0];
		result.Push (tmpPoly);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult  CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Regularize (GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result, UIndex regularizationResultsMask /*PolyRegularizationFlags*/, UIndex& regularizationResults /*PolyRegularizationFlags*/,
	GS::Array< GS::Array<UIndex> >* reversedContourIdxs /*= nullptr*/)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	DBASSERT (regularizationResultsMask != 0);
	if (regularizationResultsMask == 0 && reversedContourIdxs == nullptr) {
		return Regularize (result);
	}
	CorePolygon2D<PolyId, PolyId, PolyId, PolyId>::PolygonResult res;
	regularizationResults = 0;
	UIndex contourIdx = 0;
	UIndex vertexIdx = 1;

	// because userDataSize is const we have to make a copy
	GS::ArrayFB<GS::SharedPtr<CorePolygon2D<PolyId, PolyId, PolyId, PolyId> >, 6 > result1;
	typename CorePolygon2D<PolyId, PolyId, PolyId, PolyId>::Flags flagsCopy;
	flagsCopy.isSameDirEdgeLegal	= flags.isSameDirEdgeLegal;
	flagsCopy.isVertexUserData		= flags.isVertexUserData;
	flagsCopy.isEdgeUserData		= flags.isEdgeUserData;
	flagsCopy.isContourUserData		= flags.isContourUserData;
	flagsCopy.isPolygonUserData		= flags.isPolygonUserData;
	flagsCopy.force64BitPrecision	= flags.force64BitPrecision;
	CorePolygon2D<PolyId, PolyId, PolyId, PolyId> polygonCopy (flagsCopy);		/* Ez egy PolyId-s polygon !!!! */
	polygonCopy.template CopyInternalDataFromWithUserData<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this, 0, 0, 0, nullptr);
	polygonCopy.SetIsVertexUserData (true);
	polygonCopy.SetIsEdgeUserData (true);
	polygonCopy.SetIsContourUserData (true);

	for (contourIdx = 1; contourIdx <= nContours; ++contourIdx) {
		(polygonCopy.contourInfos)[contourIdx] = PolyId (contourIdx);
		for (; vertexIdx < polygonCopy.contourEnds[contourIdx]; ++vertexIdx) {
			(polygonCopy.vertexInfos)[vertexIdx] = PolyId (vertexIdx);
			(polygonCopy.inhEdgeInfos)[vertexIdx] = PolyId (vertexIdx);
		}

		(polygonCopy.vertexInfos)[vertexIdx] = PolyId (contourEnds[contourIdx-1]+1);
		(polygonCopy.inhEdgeInfos)[vertexIdx] = PolyId (contourEnds[contourIdx-1]+1);
		++vertexIdx;
	}

	res = polygonCopy.Regularize (result1);
	if (res == CorePolygon2D<PolyId, PolyId, PolyId, PolyId>::ResultSameAsThis)
		status.isRegularized = true; // regularis volt az eredeti polygon, de a Regularize () csak a polygonCopy-ban allitotta ezt be
	if (res != CorePolygon2D<PolyId, PolyId, PolyId, PolyId>::ResultSameAsThis) {
		SetRegularizationResults (regularizationResultsMask, regularizationResults, reversedContourIdxs, polygonCopy, result1);
		CreateRegularizationResult (polygonCopy, result1, result);
	}

	DBCHECKCOREPOLY_CHECKRESULT;
	return PolygonResult (Int32 (res));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalDataEdgeInfos (	const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& origPoly, USize verticesNum, GS::Int32 *inds, const GS::Array <const EdgeUserData*>&	customInhEdgeInfo)
{
	GS::Int32 nOriVert = origPoly.nVertices;
	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
		inhEdgeInfos [0] = defaultEdgeData;
		for (UIndex i = 1; i <= verticesNum; i++) {
			if (inds == nullptr || inds[i] == 0 || inds[i] > nOriVert) {
				inhEdgeInfos [i] = defaultEdgeData;
			} else if (inds[i] < 0) {
				if (customInhEdgeInfo.GetSize () > 0) {
					inhEdgeInfos [i] = *(customInhEdgeInfo [-(inds[i] + 1)]);
				} else {
					inhEdgeInfos [i] = defaultEdgeData;
				}
			} else {
				inhEdgeInfos [i] = origPoly.inhEdgeInfos [inds[i]];
			}
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalDataVertexInfos (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& origPoly, USize verticesNum, GS::Int32 *indc)
{
	GS::Int32 nOriVert = origPoly.nVertices;
	if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
		vertexInfos [0] = defaultVertexData;
		for (UIndex i = 1; i <= verticesNum; i++) {
			//A contour vegek indexei elmeletileg nem fordulhatnak elo es az nOriVert azutolso contour vegenek indexe, ezert vizsgalunk kissebbre,
			//de ezek nem ervenytelen indexek es ha minden jol megy, akkor megegyeznek a contour elejen levo ertekkel, ezert hasznalhatjuk ezeket az indexeket.
			DBASSERT (abs (indc[i]) < nOriVert);
			if (indc == nullptr || indc[i] == 0 || abs (indc[i]) > nOriVert) {
				vertexInfos [i] = defaultVertexData;
			} else if (indc[i] < 0) {
				vertexInfos [i] = origPoly.vertexInfos [(-indc[i])];
			} else {
				vertexInfos [i] = origPoly.vertexInfos [indc[i]];
			}
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalDataContourInfos (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& origPoly, USize contoursNum, GS::UInt32 *boends, GS::Int32 *inds)
{
	GS::Int32 nOriVert = origPoly.nVertices;
	if (contourInfos.GetSize() != 0 && flags.isContourUserData) {
		for (UIndex i = 1; i <= contoursNum; i++) {
			bool  onlyOneContour = true;
			GS::Int32 contourInd = -1;
			if (origPoly.nContours > 1) {
				for (GS::UInt32 j = boends[i - 1] + 1; j < boends[i]; j++) {
					if (inds != nullptr && inds[j] > 0 && inds[i] < nOriVert) {
						for (GS::Int32 k = 1; k <= GS::Int32 (origPoly.nContours); k++) {
							if (inds[j] <= (GS::Int32)origPoly.contourEnds[k]) {
								if (contourInd > 0 && contourInd != k)
									onlyOneContour = false;
								contourInd = k;
								break;
							}
						}
					}
				}
			} else {	/* Only one contour !*/
				contourInd = 1;
			}
			if (onlyOneContour && contourInd > 0)
				contourInfos [i] = origPoly.contourInfos [contourInd];
			else
				contourInfos [i] = defaultContourData;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetInternalData (	const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>&		origPoly,
										USize									contoursNum,
										GS::UInt32								*boends,
										USize									verticesNum,
										double									*coords,
										USize									arcsNum,
										PolyArcRec								*pArcs,
										const GS::Array <const EdgeUserData*>&	customInhEdgeInfo,
										GS::Int32								*inds,
										GS::Int32								*indc)
{
	status.isRegularized = false;

	UIndex	i;
	for (i = 1; i <= verticesNum; i++) {
		vertices[i].x = coords[2*i];
		vertices[i].y = coords[2*i + 1];
	}
	for (UIndex arcIdx = 1; arcIdx <= arcsNum; arcIdx++) {
		arcs[arcIdx] = pArcs[arcIdx - 1];
	}
	for (UIndex contourIdx = 1; contourIdx <= contoursNum; contourIdx++) {
		contourEnds[contourIdx] = boends [contourIdx];
	}

	SetInternalDataEdgeInfos (origPoly, verticesNum, inds, customInhEdgeInfo);

	SetInternalDataVertexInfos (origPoly, verticesNum, indc);

	for (UIndex iContour = 1; iContour <= nContours; iContour++) {
		UIndex iFirstContourVertex = iContour == 1 ? 1 : contourEnds[iContour - 1] + 1;
		UIndex iLastContourVertex = contourEnds[iContour];

		DBASSERT (Geometry::IsEqualCoord (vertices[iFirstContourVertex], vertices[iLastContourVertex], Eps));

		if (flags.isVertexUserData) {
			if (vertexInfos [iFirstContourVertex] != vertexInfos [iLastContourVertex]) {
				DBBREAK ();
				vertexInfos [iFirstContourVertex] = vertexInfos [iLastContourVertex];
			}
		}
		if (flags.isEdgeUserData) {
			if (inhEdgeInfos [iFirstContourVertex] != inhEdgeInfos [iLastContourVertex]) {
				DBBREAK ();
				inhEdgeInfos [iFirstContourVertex] =  inhEdgeInfos [iLastContourVertex];
			}
		}
	}

	SetInternalDataContourInfos (origPoly, contoursNum, boends, inds);

	RemoveSmallArcs ();

	UpdateBoundingBox ();
}		/* SetInternalData */


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutWithHalfPlanes (	const GS::Array<HalfPlane2DData>&			cutlines,		/* -> line params. 			*/
																bool										regularizeResults,
																GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >&	result, 		/* <- result polygons		*/
																bool*										fullin,			/* <- full inside 			*/
																GS::Int32* 									wrcode,			/* <- warning error code   	*/
																bool*										degen) const	/* <- one line result   	*/
{
	if (cutlines.GetSize () == 0) {
		DBBREAK ();
		return ResultSameAsThis;
	}

	bool dummyfullin;
	if (fullin == nullptr)
		fullin = &dummyfullin;

	GS::Int32 dummywrcode;
	if (wrcode == nullptr)
		wrcode = &dummywrcode;

	PolygonResult polyResult = NewPolygons;

	bool		forceOpen = false;		/* -> open polyline			*/

	GS::Int32		i;
	GS::Int32		ipa, ipb, ipc, ipr;
	GS::Int32		*parts;
	GS::UInt32		*pends;
	double		*pcoos;
	PolyArcRec	*parcs;
	GS::Int32		*pcind, *ppind;
	GS::Int32		jpa, jpb, jpc, jpr;
	GS::Int32		*cparts;
	GS::UInt32		*cpends;
	double		*cpcoos;
	PolyArcRec	*cparcs;
	GS::Int32		*cpcind, *cppind;
	GS::Int32		iipa, iipb, ipbb, ipcc;
	UIndex		iprr;
	GS::Int32		ipa1, ipa2, oends;
	UIndex		ocoos;
	UIndex		oarcs;
	short		pocw;

	*wrcode = 0;
	*fullin = false;

	ipa = 1;
	ipb = nContours;
	ipc = nVertices;
	ipr = nArcs;

	if (ipc < 1)
		return EmptyPolygon;

	parts = (GS::Int32 *) BMpAll (2*sizeof(GS::Int32));
	pends = (GS::UInt32 *) BMpAll ((ipb + 1) * sizeof(GS::UInt32));
	pcoos = (double *) BMpAll ((ipc + 1) * 2 * sizeof(double));
	parcs = (PolyArcRec *) BMpAll (ipr * sizeof(PolyArcRec));
	pcind = (GS::Int32 *) BMpAll ((ipc + 1) * sizeof(GS::Int32));
	ppind = (GS::Int32 *) BMpAll ((ipc + 1) * sizeof(GS::Int32));

	cparts = parts;
	cpends = pends;
	cpcoos = pcoos;
	cparcs = parcs;
	cpcind = pcind;
	cppind = ppind;

	if (parts == nullptr || pends == nullptr || pcoos == nullptr || parcs == nullptr || pcind == nullptr || ppind == nullptr) {
		BMpFree ((GSPtr)parts);
		BMpFree ((GSPtr)pends);
		BMpFree ((GSPtr)pcoos);
		BMpFree ((GSPtr)parcs);
		BMpFree ((GSPtr)pcind);
		BMpFree ((GSPtr)ppind);
		return EmptyPolygon;
	}

	parts[0] = 0;
	parts[1] = ipb;

	for (i = 0; i <= ipc; i++) {
		pcoos[2 * i]	= vertices[i].x;
		pcoos[2 * i+1]	= vertices[i].y;
		pcind[i]		= i;								/* RJ007 */
		ppind[i]		= i;								/* RJ019 */
	}

	pends[0] = 0;
	for (i = 1; i <= ipb; i++) {
		pends[i] = contourEnds[i];
		pcind[pends[i]] = pcind[pends[i-1] + 1];		/* RJ007 */
		ppind[pends[i]] = ppind[pends[i-1] + 1];		/* RJ019 */
	}

	for (i = 0; i < ipr; i++)								/* sm200 */
		parcs[i] = arcs[i+1];

	ipa1 = cparts [0] + 1;
	ipa2 = cparts [1];
	ipbb = ipa2 - ipa1 + 1;
	ipcc = cpends [ipa2] - cpends [ipa1 - 1];
	cpends [0] = 0;

	/* Makes the correct directions to the Polygons */
	pocw = CXCorrectPolyCCWArc (ipbb, cpends, ipcc, cpcoos, ipr, cparcs, cpcind, cppind);

	if (pocw != 0) {
		DBPRINTF("CXCorrectPolyCCW pocw: %d", pocw);
		BMpFree ((GSPtr)cparts);
		BMpFree ((GSPtr)cpends);
		BMpFree ((GSPtr)cpcoos);
		BMpFree ((GSPtr)cparcs);
		BMpFree ((GSPtr)cpcind);
		BMpFree ((GSPtr)cppind);
		return EmptyPolygon;
	}

	CutPolyRes ret = CUCutNumPoly ((short)cutlines.GetSize (), const_cast<HalfPlane2DData*> (cutlines.GetContent ()), ipa, parts, ipb, pends, ipc, pcoos, ipr, parcs, false, forceOpen, true, &(boundBox), true, pcind, ppind,
		&jpa, &cparts, &jpb, &cpends, &jpc, &cpcoos, &jpr, &cparcs, &cpcind, &cppind, fullin, wrcode, degen);

	if (DBVERIFY (ret != Failed)) {
		if (*fullin) {
			polyResult = ResultSameAsThis;
		} else {
			oends = 0;
			ocoos = 0;
			oarcs = 0;
			for (iipa = 1; iipa <= jpa; iipa++) {
				ipa1 = cparts [iipa - 1] + 1;
				ipa2 = cparts [iipa];
				ipbb = ipa2 - ipa1 + 1;
				ipcc = cpends [ipa2] - cpends [ipa1 - 1];
				cpends [oends] = 0;
				if ((ipbb <= 0) || (ipcc <= 0))
					break;
				for (iipb = 1; iipb <= ipbb; iipb++)
					cpends [oends + iipb] -= ocoos;

				for (iprr = 0; iprr < (jpr - oarcs); iprr++) {		/* RJ004 */
					if (((cparcs+oarcs+iprr)->begIndex >= ocoos) && ((cparcs+oarcs+iprr)->endIndex <= (ocoos+ipcc))) {
						(cparcs+oarcs+iprr)->begIndex -= ocoos;
						(cparcs+oarcs+iprr)->endIndex -= ocoos;
					} else
						break;
				}

				if (ret == NotEmpty) {
					GS::ArrayFB <const EdgeUserData*, 6>	customInhEdgeInfo;
					if ((GS::UInt32)cutlines[0].sizeOfInhEdgeInfo == sizeof(EdgeUserData) && flags.isEdgeUserData) {
						for (UIndex cutIdx = 0; cutIdx < cutlines.GetSize (); cutIdx++) {
							if ((GS::UInt32)cutlines [cutIdx].sizeOfInhEdgeInfo != sizeof(EdgeUserData)) {
								customInhEdgeInfo.Clear (true);
								break;
							}
							customInhEdgeInfo.Push ( reinterpret_cast<const EdgeUserData*> (cutlines [cutIdx].inhEdgeInfo));
						}
					}

					GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this, true);
					newPoly->CopyPolygonLevelDataFrom (*this);
					newPoly->AllocateInternalData (ipcc /*verticesNum*/, iprr/*arcsNum*/, ipbb/*contoursNum*/);

					newPoly->SetInternalData (*this,
						 					  ipbb, cpends + oends,
											  ipcc, cpcoos + 2*ocoos,
											  iprr, cparcs + oarcs,
											  customInhEdgeInfo,
											  cpcind + ocoos,
											  cppind + ocoos);

					if (!regularizeResults) {
						result.Push (newPoly);
					} else {
						GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > regularizedPolygons;
						if (newPoly->Regularize (regularizedPolygons) == ResultSameAsThis) {
							DBASSERT (regularizedPolygons.GetSize () == 0);
							result.Push (newPoly);
						} else {
							for (UIndex polyIdx = 0; polyIdx < regularizedPolygons.GetSize (); polyIdx++) {
								result.Push (regularizedPolygons[polyIdx]);
							}
						}
					}
				}

				/* for the next ipcc calculation */
				cpends [oends + ipbb] += ocoos;
				oends += ipbb;	/* oends == cparts [iipa] */
				ocoos += ipcc;
				oarcs += iprr;
			}
		}
	}

	BMpFree ((GSPtr)cparts);
	BMpFree ((GSPtr)cpends);
	BMpFree ((GSPtr)cpcoos);
	BMpFree ((GSPtr)cparcs);
	BMpFree ((GSPtr)cpcind);
	BMpFree ((GSPtr)cppind);

	DBCHECKCOREPOLY_CHECKRESULT;

	return ret == Failed ? EmptyPolygon : polyResult;
}


/*
static void CutSector  (const Sector&		sector,
						double				t1,
						double				t2,
						Sector&				result)
{
	Sector	result = sector;
	if (t1 > -1) {
		GetSectorCoord (t1, &sector, &result.c1);
		GetSectorCoord (t2, &sector, &result.c2);
	}
}



static void CutGenArc  (const GenArc&	genArc,
						double			t1,
						double			t2,
						GenArc& 		result)
{
	result = genArc;
	if (t1 > -1) {
		result.IsWhole () = fabs (t2 - t1 - 2 * PI) < Eps;
		if (t2 > 2 * PI)
			t2 -= 2 * PI;
		if (result.IsWhole ()) {
			result.GetBegAng () = 0.0;
			result.GetEndAng () = 0.0;
		} else {
			result.GetEndAng () = !genArc.IsReflected () ? AddAngle (genArc.GetBegAng (), t2) : SubAngle (genArc.GetBegAng (), t2);
			result.GetBegAng () = !genArc.IsReflected () ? AddAngle (genArc.GetBegAng (), t1) : SubAngle (genArc.GetBegAng (), t1);
		}
		ComputeEllipseCoord (&result, result.GetBegAng (), &result.GetBegC ());
		ComputeEllipseCoord (&result, result.GetEndAng (), &result.GetEndC ());
	}
}
*/

struct Store2DSectorData {
	PieceFunc*				StorePiece;
	const void*				userData;
};


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErr	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::StoreLine (Geometry::PGRESSECTOREXT* sectors, const Sector& newSector)
{
	Sector sector = newSector;
	Store2DSectorData* data = reinterpret_cast<Store2DSectorData*> (sectors->sectorsData);
	data->StorePiece (CURVE2D_Sector, &sector, nullptr, 0, nullptr, nullptr, nullptr, 0, nullptr, 0, nullptr, data->userData);
	return NoError;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CmpResult	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CmpDoubles (const void	*p1, const void	*p2)
{
	GS::Int32	ret = 0;

	if (*((double*) p1) > *((double*) p2))
		ret = 1;
	if (*((double*) p1) < *((double*) p2))
		ret = -1;
	return ret;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcSectionsForCutElem (const GenArc&		genArc,
										GS::Array<CutParam>&  hSect) const
{
	GSErrCode	err = NoError;
	GS::Int32	iSub, iVert, ix, nx;
	CutParam		t;
	/* -------------------------- calc sections */
	for (iSub = 1; iSub <= (GS::Int32) nContours && err == NoError; iSub++) {
		for (iVert = contourEnds[iSub - 1] + 1; iVert < (GS::Int32) contourEnds[iSub] && err == NoError; iVert++) {
			Sector		cutS;
			cutS.c1 = vertices[iVert];
			cutS.c2 = vertices[iVert + 1];

			UIndex cutArcInd = GetInternalArcIdx (iVert);
			double	cutArcAng = arcs[cutArcInd].arcAngle;
			GenArc	cutArc;
			if (cutArcInd > 0 && fabs (cutArcAng) > Eps)
				cutArc = SetGenArc (cutS.c1, cutS.c2, cutArcAng);

			Point2D		c4[4];		// section arc X ellips -> 4 pt

			if (cutArcInd == 0 || fabs (cutArcAng) < Eps) {
				nx = XGenArcSectorEps (&genArc, &cutS, reinterpret_cast<Sector*>(c4), Eps);
				if (nx == 2)
					c4[0] = c4[1];
				nx = (nx / 2) + (nx & 1);
			} else {
				nx = XGenArcs (&genArc, &cutArc, c4);		// itt lehet 4 metszespont
			}

			for (ix = 0; ix < nx && err == NoError; ix++)  {
				t = CalcElemParam (CURVE2D_GenArc, nullptr, &genArc, 0, nullptr, 0, nullptr, c4 + ix, 0, true /*onlyOnCurve*/);
				hSect.Push (t);
			}
		}
	}

	return err;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcSectionsForCutElem (GS::Int32			nCoords,
										const Point2D*		pCoords,
										const DirType*		pDirs,
										bool				closed,
										GS::Array<CutParam>&  hSect) const
{
	GS::Int32	iSub, iVert;
	CutParam		t;

	/* -------------------------- calc sections */
	GS::Array<double> h1;
	for (iSub = 1; iSub <= static_cast<GS::Int32> (nContours); iSub++) {
		for (iVert = contourEnds[iSub - 1] + 1; iVert < static_cast<GS::Int32> (contourEnds[iSub]); iVert++) {
			Sector		cutS;
			cutS.c1 = vertices[iVert];
			cutS.c2 = vertices[iVert + 1];

			UIndex cutArcInd = GetInternalArcIdx (iVert);
			double	cutArcAng = arcs[cutArcInd].arcAngle;
			GenArc	cutArc;
			if (cutArcInd > 0 && fabs (cutArcAng) > Eps)
				cutArc = SetGenArc (cutS.c1, cutS.c2, cutArcAng);

			if (cutArcInd == 0 || fabs (cutArcAng) < Eps)
				XSplineSector (nCoords, pCoords, pDirs, closed, &cutS, h1);
			else
				XSplineGenArc (nCoords, pCoords, pDirs, closed, &cutArc, h1);

			for (UIndex ix = 0; ix < h1.GetSize (); ix++)  {
				t.param = h1[ix];
				hSect.Push (t);
			}
			h1.SetSize (0);
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcSectionsForCutElem (Boundary cutBoundaries,
										const GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >&	polyline,
										GS::Array<CutParam>&  hSect) const
{
	const PolyArcRec*		pArcs = polyline->nArcs == 0 ? nullptr : polyline->arcs.GetContent () + 1;

	GSErrCode	err = NoError;
	GS::Int32	iSub, iVert, ix;
	CutParam	t;

	/* -------------------------- calc sections */
	for (iSub = 1; iSub <= (GS::Int32) nContours && err == NoError; iSub++) {
		for (iVert = contourEnds[iSub - 1] + 1; iVert < (GS::Int32) contourEnds[iSub] && err == NoError; iVert++) {
			Sector		cutS;
			cutS.c1 = vertices[iVert];
			cutS.c2 = vertices[iVert + 1];

			UIndex	cutArcInd = GetInternalArcIdx (iVert);
			double	cutArcAng = arcs[cutArcInd].arcAngle;
			GenArc	cutArc;
			if (cutArcInd > 0 && fabs (cutArcAng) > Eps)
				cutArc = SetGenArc (cutS.c1, cutS.c2, cutArcAng);

			Point2D		c4[4];		// section arc X ellips -> 4 pt

			for (GS::Int32 iPl = 1; iPl < static_cast<GS::Int32> (polyline->nVertices) && err == NoError; iPl++) {
				Sector		elemS;
				elemS.c1 = polyline->vertices[iPl];
				elemS.c2 = polyline->vertices[iPl + 1];
				UIndex elemArcInd = polyline->GetInternalArcIdx (iPl);
				double	elemArcAng = polyline->arcs[elemArcInd].arcAngle;
				GS::Int32 xx = 0;
				if (cutArcInd == 0 || fabs (cutArcAng) < Eps) {
					if (elemArcInd == 0 || fabs (elemArcAng) < Eps) {
						if (cutBoundaries == Boundary_Closed)
							xx = XSectorsOverLap (&cutS, &elemS, c4);
						else
							xx = XSectors (cutS, elemS, Boundary_Closed, c4);
					} else
						xx = XLineArc (&cutS, &elemS, elemArcAng, c4);
				} else {
					if (elemArcInd == 0 || fabs (elemArcAng) < Eps)
						xx = XLineArc (&elemS, &cutS, cutArcAng, c4);
					else
					{
						GenArc	elemArc;
						if (elemArcInd > 0 && fabs (elemArcAng) > Eps)
							elemArc = SetGenArc (elemS.c1, elemS.c2, elemArcAng);
						if (cutBoundaries == Boundary_Closed)
							xx = XArcsOverLap (&cutS, cutArcAng, &elemS, elemArcAng, c4);
						else
							xx = XGenArcs (&elemArc, &cutArc, c4);
					}
				}
				for (ix = 0; ix < xx && err == NoError; ix++)  {
					t = CalcElemParam (CURVE2D_PolyLine, nullptr, nullptr, polyline->nVertices, polyline->vertices.GetContent (),  polyline->nArcs, pArcs, c4 + ix, iPl, true /*onlyOnCurve*/);
					hSect.Push (t);
				}
			}
		}
	}
	return err;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElemInternal (	Boundary				cutBoundaries,	// means that a linepiece overlapping cutpoly Boundary is accepted or not (opened/closed)
										const Sector&			sector,
										PieceFunc*				StorePiece,		// call back for storing pieces
										const void*				userData,		// user data for call back func.
										bool					doDifference) const	// compute difference or section
{
	Geometry::PGPOLYEXT			pgpoly;
	MakePolyExt (pgpoly);
	if (sector.GetLength () < EPS) {

		PGPositionExt polyPointPos = PGPoint2DPosition (&pgpoly, &sector.c1, false);
		bool isValid = false;
		if (!doDifference) {
			// point inside -> element inside
			if (cutBoundaries == Boundary_Closed) {
				isValid = (polyPointPos != PGOutsidePoly);
			} else
				isValid = (polyPointPos == PGInsidePoly);
		} else {
			// point disjuct -> element disjunct
			if (cutBoundaries == Boundary_Closed) {
				isValid = (polyPointPos == PGOutsidePoly);
			} else
				isValid = (polyPointPos != PGInsidePoly);
		}
		if (isValid) {
			StorePiece (CURVE2D_Sector, const_cast<Sector*> (&sector), nullptr, 0, nullptr, nullptr, nullptr, 0, nullptr, 0, nullptr, userData);
		}
	} else {
		Geometry::PGRESSECTOREXT	newSectors;
		Store2DSectorData			data = {StorePiece, userData};
		newSectors.sectorsData = reinterpret_cast<GSPtr> (&data);
		newSectors.newSector = StoreLine;

		ResultSegmentPos::Et pos;
		if (doDifference) {
			pos = cutBoundaries == Boundary_Closed ? ResultSegmentPos::Outside : Geometry::ResultSegmentPos::OutsideOrOn;
		} else {
			pos = cutBoundaries == Boundary_Closed ? ResultSegmentPos::InsideOrOn : ResultSegmentPos::Inside;
		}
		Geometry::SectorInPoly (pgpoly, Geometry::WindingRulePos, sector, pos, &newSectors);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElemInternal (	Boundary				cutBoundaries,	// means that a linepiece overlapping cutpoly Boundary is accepted or not (opened/closed)
										const GenArc&			genArc,
										PieceFunc*				StorePiece,		// call back for storing pieces
										const void*				userData,		// user data for call back func.
										bool					doDifference) const	// compute difference or section
{
	bool					closed = true;
	double					tLen = 0.0;
	GSErrCode				err = NoError;

	if (genArc.IsWhole ()) {
		closed = true;
		tLen = 2.0 * PI;
	} else {
		closed = false;
		if (!genArc.IsReflected ())
			tLen = SubAngle (genArc.GetEndAng (), genArc.GetBegAng ());
		else
			tLen = SubAngle (genArc.GetBegAng (), genArc.GetEndAng ());
	}


	GS::ArrayFB<CutParam, 6> hSect;

	err = CalcSectionsForCutElem (genArc, hSect);
	if (doDifference) {
		if (!closed) {
			CutParam cutParam (0.0);
			hSect.Push (cutParam);
			cutParam.param = tLen;
			hSect.Push (cutParam);
		}
	}

	/* -------------------------- sort sect.params */
	if (err == NoError)
		GS::Sort (hSect.Begin (), hSect.End (), [] (const CutParam& p1, const CutParam& p2) -> bool {
				return p1.param <p2.param;
			});


	/* -------------------------- store pieces */
	RelativePosition	relPos;
	Point2D				cMid;
	GS::Int32			ix;
	if (hSect.GetSize () == 0 && err == NoError) {
		CutParam middle (tLen / 2.0);

		GetElemCoord (middle, CURVE2D_GenArc, nullptr, &genArc, 0, nullptr, nullptr, 0, nullptr, &cMid);
		relPos = GetPosition (cMid, cutBoundaries);

		bool isValid = false;
		if (!doDifference) {
			// point inside -> element inside
			isValid = IsOverlap (relPos);
		} else {
			// point disjuct -> element disjunct
			isValid = IsDisjunct (relPos);
		}

		if (isValid) {
			CutParam dummy (-2.0);
			MakePiece (CURVE2D_GenArc, nullptr, &genArc, 0, nullptr, nullptr, nullptr, 0, nullptr, dummy, dummy, StorePiece, userData);
		}

	} else {
		for (ix = -1; ix < (GS::Int32)hSect.GetSize () && err == NoError; ix++) {

			double		t1, t2, tMid;
			if (closed && ix == -1)
				continue;
			if (ix >= 0)
				t1 = hSect[ix].param;
			else
				t1 = 0.0;
			if (ix + 1 < (GS::Int32)hSect.GetSize ())
				t2 = hSect[ix + 1].param;
			else if (closed)
				t2 = tLen + hSect[0].param;
			else
				t2 = tLen;
			if (fabs (t2-t1) < Eps)
				continue;

			tMid = (t1 + t2) / 2.0;
			if (tMid > tLen && closed)		// ha nem closed, akkor vmi hiba miatt lehetne
				tMid -= tLen;

			CutParam middle (tMid);
			GetElemCoord (middle, CURVE2D_GenArc, nullptr, &genArc, 0, nullptr, nullptr, 0, nullptr, &cMid);

			relPos = GetPosition (cMid, cutBoundaries);

			bool isValid = false;
			if (!doDifference) {
				// point inside -> element inside
				isValid = IsOverlap (relPos);
			} else {
				// point disjuct -> element disjunct
				isValid = IsDisjunct (relPos);
			}

			if (isValid) {
				CutParam param1 (t1);
				CutParam param2 (t2);
				MakePiece (CURVE2D_GenArc, nullptr, &genArc, 0, nullptr, nullptr, nullptr, 0, nullptr, param1, param2, StorePiece, userData);
			}
		}
	}


	return;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElemInternal (	Boundary				cutBoundaries,	// means that a linepiece overlapping cutpoly Boundary is accepted or not (opened/closed)
										const Point2D&			coord,			// spline/polyLine/polygon
										PieceFunc*				StorePiece,		// call back for storing pieces
										const void*				userData,		// user data for call back func.
										bool					doDifference) const	// compute difference or section
{
	/* -------------------------- store pieces */
	RelativePosition	relPos;
	relPos = GetPosition (coord, cutBoundaries);

	bool isValid = false;
	if (!doDifference) {
		// point inside -> element inside
		isValid = IsOverlap (relPos);
	} else {
		// point disjuct -> element disjunct
		isValid = IsDisjunct (relPos);
	}

	if (isValid) {
		CutParam dummy (-2.0);
		MakePiece (CURVE2D_Point, nullptr, nullptr, 1, &coord, nullptr, nullptr, 0, nullptr, dummy, dummy, StorePiece, userData);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElemInternal (	Boundary				cutBoundaries,	// means that a linepiece overlapping cutpoly Boundary is accepted or not (opened/closed)
										const BezierDetails&	bezier,
										PieceFunc*				StorePiece,		// call back for storing pieces
										const void*				userData,		// user data for call back func.
										bool					doDifference) const	// compute difference or section
{
	bool			closed	= bezier.IsClosed ();
	const Point2D*	pCoords	= bezier.GetCoordsPtr ();
	const DirType*	pDirs	= bezier.GetDirsPtr ();
	GS::Int32		nCoords	= bezier.GetCoordsNum ();
	double			tLen	= closed ? nCoords : nCoords - 1;

	GS::ArrayFB<CutParam, 6> hSect;

	CalcSectionsForCutElem (nCoords, pCoords, pDirs, closed, hSect);

	if (doDifference) {
		if (!closed) {
			CutParam cutParam (0.0);
			hSect.Push (cutParam);
			cutParam.param = tLen;
			hSect.Push (cutParam);
		}
	}

	/* -------------------------- sort sect.params */
	GS::Sort (hSect.Begin (), hSect.End (), [] (const CutParam& p1, const CutParam& p2) -> bool {
		return p1.param < p2.param;
	});

	/* -------------------------- store pieces */
	RelativePosition	relPos;
	Point2D				cMid;
	GS::Int32			ix;
	if (hSect.IsEmpty ()) {
		CutParam middle (tLen / 2.0);

		GetElemCoord (middle, CURVE2D_Spline, nullptr, nullptr, nCoords, pCoords, pDirs, 0, nullptr, &cMid);
		relPos = GetPosition (cMid, cutBoundaries);

		bool isValid = false;
		if (!doDifference) {
			// point inside -> element inside
			isValid = IsOverlap (relPos);
		} else {
			// point disjuct -> element disjunct
			isValid = IsDisjunct (relPos);
		}

		if (isValid) {
			CutParam dummy (-2.0);
			MakePiece (CURVE2D_Spline, nullptr, nullptr, closed ? -nCoords : nCoords, pCoords, pDirs, nullptr, 0, nullptr, dummy, dummy, StorePiece, userData);
		}

	} else {
		for (ix = -1; ix < static_cast<GS::Int32> (hSect.GetSize ()); ix++) {
			double		t1, t2, tMid;
			if (closed && ix == -1)
				continue;
			if (ix >= 0)
				t1 = hSect[ix].param;
			else
				t1 = 0.0;
			if (ix + 1 < (GS::Int32)hSect.GetSize ())
				t2 = hSect[ix + 1].param;
			else if (closed)
				t2 = tLen + hSect[0].param;
			else
				t2 = tLen;
			if (fabs (t2-t1) < Eps)
				continue;

			tMid = (t1 + t2) / 2.0;
			if (tMid > tLen && closed)		// ha nem closed, akkor vmi hiba miatt lehetne
				tMid -= tLen;

			CutParam middle (tMid);
			GetElemCoord (middle, CURVE2D_Spline, nullptr, nullptr, nCoords, pCoords, pDirs, 0, nullptr, &cMid);

			relPos = GetPosition (cMid, cutBoundaries);

			bool isValid = false;
			if (!doDifference) {
				// point inside -> element inside
				isValid = IsOverlap (relPos);
			} else {
				// point disjuct -> element disjunct
				isValid = IsDisjunct (relPos);
			}

			if (isValid) {
				CutParam param1 (t1);
				CutParam param2 (t2);
				MakePiece (CURVE2D_Spline, nullptr, nullptr, closed ? -nCoords : nCoords, pCoords, pDirs, nullptr, 0, nullptr, param1, param2, StorePiece, userData);
			}
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElemInternal (	Boundary				cutBoundaries,	// means that a linepiece overlapping cutpoly Boundary is accepted or not (opened/closed)
	const GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >&	poly2D,			// polygon (alternative form)
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& poly2DResult,
	bool&					touching,
	bool					/*doDifference*/) const	// compute difference or section
{
	RelativePosition			relativePosition;
	DetailedRelativePosition	relativeDetailedPosition;
	CorePolygon2D::PolygonResult polygonResult = poly2D->Intersect (*this, poly2DResult, cutBoundaries, &relativePosition, &relativeDetailedPosition);

	//TODO Itt nem kellene lemasolni
	if (polygonResult == ResultSameAsThis) {
		poly2DResult.Push (new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*poly2D));
	} else if (polygonResult == ResultSameAsFirstParameter) {
		poly2DResult.Push (new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this));
	}

	touching = (relativePosition == RelativePosition_Overlap && relativeDetailedPosition == DetailedRelativePosition_Overlap_OnBoundary);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElemInternal (	Boundary				cutBoundaries,	// means that a linepiece overlapping cutpoly Boundary is accepted or not (opened/closed)
	const GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >&	polyline,			// polygon (alternative form)
	GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >& polylineResult,
	bool					doDifference) const	// compute difference or section
{
	if (polyline->IsEmpty ())
		return;

	const bool closed = IsEqualCoord (polyline->vertices[1], polyline->vertices[polyline->nVertices], Eps);
	const UIndex edgeNum = polyline->nVertices - 1;

	GS::Array<CutParam> hSect;

	/* -------------------------- calc sections */
	GSErrCode err = CalcSectionsForCutElem (cutBoundaries, polyline, hSect);
	if (err != NoError)
		return;

	/* -------------------------- sort sect.params */
	GS::Sort (hSect.Begin (), hSect.End (), [] (const CutParam& p1, const CutParam& p2) -> bool {
			if (p1.edgeIndex != p2.edgeIndex)
				return p1.edgeIndex < p2.edgeIndex;
			return p1.param < p2.param;
		});

	/* -------------------------- store pieces */
	if (hSect.GetSize () == 0) {
		CutParam middle;
		middle.edgeIndex = (edgeNum / 2 + 1);
		middle.param = ((edgeNum % 2) == 1) ? 0.5 : 0.0;

		Point2D cMid = polyline->CutParamToCutPoint (middle);
		RelativePosition relPos = GetPosition (cMid, cutBoundaries);

		bool isValid = false;
		if (!doDifference) {
			// point inside -> element inside
			isValid = IsOverlap (relPos);
		} else {
			// point disjuct -> element disjunct
			isValid = IsDisjunct (relPos);
		}

		if (isValid) {
			polylineResult.Push (polyline);
		}
	} else {
		for (Int32 ix = static_cast<GS::Int32>(hSect.GetSize ()) - 1; ix > 0; --ix) {
			if (fabs (hSect[ix - 1].ToOldStyleCutParam () - hSect[ix].ToOldStyleCutParam ()) < Eps)
				hSect.Delete (ix);
		}

		if (!closed) {
			GS::ArrayFB<UIndex, 6> indicesToDelete;
			for (Int32 ix = -1; ix < static_cast<GS::Int32>(hSect.GetSize ()) - 1; ++ix) {
				CutParam		t1, t2;
				bool prevIsValid = IsValidPiece (polyline, cutBoundaries, doDifference, hSect, ix, t1, t2);
				bool nextIsValid = IsValidPiece (polyline, cutBoundaries, doDifference, hSect, ix + 1, t1, t2);
				if (prevIsValid && nextIsValid) {
					if (hSect[ix + 1].IsEdgeBeg () || hSect[ix + 1].IsEdgeEnd ())
						indicesToDelete.Push (ix + 1);
				}
			}

			for (Int32 ix = static_cast<GS::Int32>(indicesToDelete.GetSize ()) - 1; ix >= 0; --ix) {
				hSect.Delete (indicesToDelete[ix]);
			}
		}

		for (Int32 ix = -1; ix < static_cast<GS::Int32>(hSect.GetSize ()); ++ix) {
			CutParam		t1, t2;
			if (IsValidPiece (polyline, cutBoundaries, doDifference, hSect, ix, t1, t2)) {
				GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>> tmp;
				typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult res = polyline->CutPiece (t1, t2, tmp);
				if (res == CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::EmptyPolyline)
					continue;
				else if (res == CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ResultSameAsThis)
					tmp = polyline;
				if (tmp.Get () != nullptr && !tmp->IsEmpty ())
					polylineResult.Push (tmp);
			}
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElemBorderOnlyInternal (const Sector& sector,
																											   GS::Array<Sector>& results,
																											   LineCutMode cutMode) const
{
	results.Clear ();

	GS::Array<Sector> remainders = { sector };
	GS::Array<Sector> overlaps;

	for (UIndex iContour = 1; iContour <= (GS::Int32) nContours; iContour++) {
		for (UIndex iVertex = contourEnds[iContour - 1] + 1; iVertex < (GS::Int32) contourEnds[iContour]; iVertex++) {
			Sector		edgeSec;
			edgeSec.c1 = vertices[iVertex];
			edgeSec.c2 = vertices[iVertex + 1];

			UIndex edgeArcInd = GetInternalArcIdx (iVertex);
			double	edgeArcAng = arcs[edgeArcInd].arcAngle;

			if (edgeArcInd == 0 || fabs (edgeArcAng) < RadEps) { //if the edge really is a sector
				GS::Array<Sector> newRemainders;
				for (Sector secToCut : remainders) {
					Sector overlapWithOneEdge;
					GS::Array<Sector> remainsFromOneEdge;
					Geometry::CutSectorWithOtherSector (secToCut, edgeSec, overlapWithOneEdge, remainsFromOneEdge);

					if (fabs (overlapWithOneEdge.GetLength ()) > Eps)
						overlaps.Push (overlapWithOneEdge);

					newRemainders.Append (remainsFromOneEdge);
				}
				remainders = newRemainders;
			}
		}
	}

	switch (cutMode)
	{
		case CorePolygon2D::LineCutMode::Difference:
			results.Append (remainders);
			break;
		case CorePolygon2D::LineCutMode::Overlap:
			results.Append (overlaps);
			break;
		default:
			DBBREAK_STR ("Is there a new cutMode?");
			break;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElemBorderOnlyInternal (const GenArc& arc,
																											   GS::Array<GenArc>& results,
																											   LineCutMode cutMode) const
{
	results.Clear ();

	GS::Array<GenArc> remainders = { arc };
	GS::Array<GenArc> overlaps;

	for (UIndex iContour = 1; iContour <= (GS::Int32) nContours; iContour++) {
		for (UIndex iVertex = contourEnds[iContour - 1] + 1; iVertex < (GS::Int32) contourEnds[iContour]; iVertex++) {
			Sector		edgeSec;
			edgeSec.c1 = vertices[iVertex];
			edgeSec.c2 = vertices[iVertex + 1];

			UIndex edgeArcInd = GetInternalArcIdx (iVertex);
			double	edgeArcAng = arcs[edgeArcInd].arcAngle;
			GenArc	edgeArc;
			if (edgeArcInd > 0 && fabs (edgeArcAng) > RadEps) {
				edgeArc = SetGenArc (edgeSec.c1, edgeSec.c2, edgeArcAng);

				GS::Array<GenArc> newRemainders;
				for (GenArc arcToCut : remainders) {
					GenArc overlapWithOneEdge;
					GS::Array<GenArc> remainsFromOneEdge;
					Geometry::CutArcWithOtherArc (arcToCut, edgeArc, overlapWithOneEdge, remainsFromOneEdge);

					if (fabs (overlapWithOneEdge.GetArcAngle ()) > RadEps)
						overlaps.Push (overlapWithOneEdge);

					newRemainders.Append (remainsFromOneEdge);
				}
				remainders = newRemainders;
			}
		}
	}

	switch (cutMode)
	{
		case CorePolygon2D::LineCutMode::Difference:
			results.Append (remainders);
			break;
		case CorePolygon2D::LineCutMode::Overlap:
			results.Append (overlaps);
			break;
		default:
			DBBREAK_STR ("Is there a new cutMode?");
			break;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsValidPiece (const GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& polyline, Boundary cutBoundaries, bool doDifference, const GS::Array<CutParam>& hSect, Int32 actIndex, CutParam& t1, CutParam& t2) const
{
	const bool closed = IsEqualCoord (polyline->vertices[1], polyline->vertices[polyline->nVertices], Eps);
	const UIndex edgeNum = polyline->nVertices - 1;

	if (closed && actIndex == -1)
		return false;

	if (actIndex >= 0) {
		t1 = hSect[actIndex];
	} else {
		t1.edgeIndex = 1;
		t1.param = 0.0;
	}

	if (actIndex + 1 < static_cast<Int32> (hSect.GetSize ()))
		t2 = hSect[actIndex + 1];
	else if (closed) {
		t2 = hSect[0];
		t2.edgeIndex += edgeNum;		// !!! ez direkt van
	} else {
		t2.edgeIndex = edgeNum;
		t2.param = 1.0;
	}

	if (fabs (t1.ToOldStyleCutParam () - t2.ToOldStyleCutParam ()) < Eps)
		return false;

	CutParam		 tMid;
	if (t1.edgeIndex == t2.edgeIndex) {
		tMid.edgeIndex	= t1.edgeIndex;
		tMid.param		= (t1.param + t2.param) / 2.0;
	} else {
		tMid.ConvertFromOldStyleParam ((t1.ToOldStyleCutParam () + t2.ToOldStyleCutParam ()) / 2.0);
		if (!closed) {
			if (DBERROR (tMid.edgeIndex > edgeNum)) {
				tMid.edgeIndex = edgeNum;
				tMid.param = 1.0;
			}
		}
	}

	if (tMid.edgeIndex > edgeNum && closed)		// ha nem closed, akkor vmi hiba miatt lehetne
		tMid.edgeIndex -= edgeNum;

	Point2D cMid = polyline->CutParamToCutPoint (tMid);
	RelativePosition relPos = GetPosition (cMid, cutBoundaries);

	if (!doDifference) {
		// point inside -> element inside
		return IsOverlap (relPos);
	} else {
		// point disjuct -> element disjunct
		return IsDisjunct (relPos);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElemInternal (	Boundary				cutBoundaries,	// means that a linepiece overlapping cutpoly Boundary is accepted or not (opened/closed)
	const GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >&	polyline,
										PieceFunc*				StorePiece,		// call back for storing pieces
										const void*				userData,		// user data for call back func.
										bool					doDifference) const	// compute difference or section
{
	GS::Int32					nCoords = polyline->nVertices;
	GS::Int32					arcsNum = polyline->nArcs;
	const PolyArcRec*			pArcs = polyline->nArcs == 0 ? nullptr : polyline->arcs.GetContent () + 1;

	if (nCoords == 0)
		return;

	//closed = false;		/* sm401 #33370 ugy kezeljuk, mintha nyilt lenne, mert zartkent kulon meg kellene irni */
	//closed = (pCoords[0].x == 0.0);
	const bool closed = IsEqualCoord (polyline->vertices[1], polyline->vertices[nCoords], Eps);
	const UIndex edgeNum = nCoords - 1;

	GS::ArrayFB<CutParam, 6> hSect;

	GSErrCode  err = CalcSectionsForCutElem (cutBoundaries, polyline, hSect);

	if (doDifference) {
		if (!closed) {
			CutParam cutParam;
			cutParam.edgeIndex = 1;
			cutParam.param = 0.0;
			hSect.Push (cutParam);
			cutParam.edgeIndex = edgeNum;
			cutParam.param = 1.0;
			hSect.Push (cutParam);
		}
	}

	/* -------------------------- sort sect.params */
	if (err == NoError)
		GS::Sort (hSect.Begin (), hSect.End (), [] (const CutParam& p1, const CutParam& p2) -> bool {
				if (p1.edgeIndex != p2.edgeIndex)
					return p1.edgeIndex < p2.edgeIndex;
				return p1.param < p2.param;
			});

	/* -------------------------- store pieces */
	RelativePosition	relPos;
	Point2D				cMid;
	GS::Int32			ix;
	if (hSect.GetSize () == 0 && err == NoError) {
		CutParam middle;
		middle.edgeIndex = (UIndex)(edgeNum / 2.0 + 1);
		middle.param = ((edgeNum % 2) == 1) ? 0.5 : 0.0;

		GetElemCoord (middle, CURVE2D_PolyLine, nullptr, nullptr, nCoords, polyline->vertices.GetContent (), nullptr, arcsNum, pArcs, &cMid);
		relPos = GetPosition (cMid, cutBoundaries);

		bool isValid = false;
		if (!doDifference) {
			// point inside -> element inside
			isValid = IsOverlap (relPos);
		} else {
			// point disjuct -> element disjunct
			isValid = IsDisjunct (relPos);
		}

		if (isValid) {
			CutParam dummy (-2.0);
			MakePiece (CURVE2D_PolyLine, nullptr, nullptr, nCoords, polyline->vertices.GetContent (), nullptr, nullptr, arcsNum, pArcs, dummy, dummy, StorePiece, userData);
		}

	} else {
		for (ix = -1; ix < (GS::Int32)hSect.GetSize () && err == NoError; ix++) {
			CutParam		t1, t2, tMid;
			if (closed && ix == -1)
				continue;

			if (ix >= 0) {
				t1 = hSect[ix];
			} else {
				t1.edgeIndex = 1;
				t1.param = 0.0;
			}

			if (ix + 1 < (GS::Int32)hSect.GetSize ())
				t2 = hSect[ix + 1];
			else if (closed) {
				t2 = hSect[0];
				t2.edgeIndex += edgeNum;		// !!! ez direkt van
			} else {
				t2.edgeIndex = edgeNum;
				t2.param = 1.0;
			}

			if (fabs (t1.ToOldStyleCutParam () - t2.ToOldStyleCutParam ()) < Eps)
				continue;

			if (t1.edgeIndex == t2.edgeIndex) {
				tMid.edgeIndex	= t1.edgeIndex;
				tMid.param		= (t1.param + t2.param) / 2.0;
			} else  {
				if ((t2.edgeIndex > edgeNum) || (polyline->GetEdgeLength (t2.edgeIndex) * t2.param) > Eps) {
					tMid.edgeIndex	= t2.edgeIndex;
					tMid.param		= 0.0;
				} else {
					if (t2.edgeIndex == t1.edgeIndex + 1) {
						tMid.edgeIndex	= t1.edgeIndex;
						tMid.param		= (t1.param + 1.0) / 2.0;
					} else {
						tMid.edgeIndex	= t2.edgeIndex - 1;
						tMid.param		= 0.5;
					}
				}
			}

			if (tMid.edgeIndex > edgeNum && closed)		// ha nem closed, akkor vmi hiba miatt lehetne
				tMid.edgeIndex -= edgeNum;

			GetElemCoord (tMid, CURVE2D_PolyLine, nullptr, nullptr, nCoords, polyline->vertices.GetContent (), nullptr, arcsNum, pArcs, &cMid);

			relPos = GetPosition (cMid, cutBoundaries);

			bool isValid = false;
			if (!doDifference) {
				// point inside -> element inside
				isValid = IsOverlap (relPos);
			} else {
				// point disjuct -> element disjunct
				isValid = IsDisjunct (relPos);
			}

			if (isValid)
				MakePiece (CURVE2D_PolyLine, nullptr, nullptr, nCoords, polyline->vertices.GetContent (), nullptr, nullptr, arcsNum, pArcs, t1, t2, StorePiece, userData);
		}
	}

	return;
}


////Csak belso hasznalatra. Szukseg lehet utana egy Regularizalasra
//template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
//CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (Flags actFlags, const Polygon2DData& polygon)
//{
//	//DBCHECKCOREPOLY2DDATA (polygon);
//
//	InitInternalData ();
//	flags = actFlags;
//	status.isRegularized = true;
//	CopyPolygonLevelDataFrom (polygon);
//
//	if (polygon.nVertices == 0 || polygon.nContours == 0) {
//		return;
//	}
//
//	SetInternalData (polygon);
//}


////////////////////////////////// PG ////////////////////////////////////////
/* Common funcions */
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MakePolyExt (Geometry::PGPOLYEXT	&polyExt) const
{
	BNZeroMemory (&polyExt, sizeof (polyExt));
	polyExt.status = NormalPolyStatus;
	polyExt.status.isSameDirEdgeLegal = flags.isSameDirEdgeLegal;
	polyExt.status.force64BitPrecision = flags.force64BitPrecision;
	polyExt.boundBox	= boundBox;
	polyExt.nContours	= nContours;
	polyExt.nEdges		= nVertices - nContours;
	polyExt.nArcs		= nArcs;
	polyExt.sizeOfData	= 0;
	polyExt.data		= const_cast<GSPtr> (reinterpret_cast<const char*> (this));
	polyExt.getEdge		= &GetPolyEdge;
	polyExt.newEdge		= nullptr;
	polyExt.epsilon		= Eps;
	polyExt.minVertexDist	= 3 * Eps;
	polyExt.angleEpsilon   = 0.0;
	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData)
		polyExt.defaultVertexData   = (GS::GSPtr)(&defaultVertexData);
	else
		polyExt.defaultVertexData   = nullptr;
	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData)
		polyExt.defaultInhEdgeData  = (GS::GSPtr)(&defaultEdgeData);
	else
		polyExt.defaultInhEdgeData  = nullptr;
// 	if (defaultUserData != nullptr)
// 		polyExt.defaultUniqEdgeData = defaultUserData;
// 	else
		polyExt.defaultUniqEdgeData = nullptr;
	if (inhPolygonInfo.GetSize () != 0 && flags.isPolygonUserData)
		polyExt.inhPolygonData   = (GS::GSPtr)(&inhPolygonInfo[0]);
	else
		polyExt.inhPolygonData   = nullptr;
	if (contourInfos.GetSize() != 0 && flags.isContourUserData)
		polyExt.defaultContourData   = (GS::GSPtr)(&defaultContourData);
	else
		polyExt.defaultContourData   = nullptr;
	polyExt.unid           = 0;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MakePolyExtArr (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& poly2DArray, Geometry::PGPOLYEXT	&polyExt)
{
	BNZeroMemory (&polyExt, sizeof (polyExt));
	if (poly2DArray.GetSize () == 0) {
		return;
	}

	polyExt.status = NormalPolyStatus;
	polyExt.status.isSameDirEdgeLegal = poly2DArray[0]->flags.isSameDirEdgeLegal;
	polyExt.status.force64BitPrecision = poly2DArray[0]->flags.force64BitPrecision;
	polyExt.sizeOfData	= 0;
	polyExt.data		= const_cast<GSPtr> (reinterpret_cast<const char*> (&poly2DArray));
	polyExt.getEdge		= &GetPolyEdgeArr;
	polyExt.newEdge		= nullptr;
	polyExt.epsilon		= Eps;
	polyExt.minVertexDist	= 3 * Eps;
	polyExt.angleEpsilon   = 0.0;

	Box2DData	tmpBoundBox;
	ULong verticesNum = 0;
	ULong contoursNum = 0;

	polyExt.defaultVertexData   = nullptr;
	polyExt.defaultInhEdgeData  = nullptr;
	polyExt.defaultUniqEdgeData = nullptr;
	polyExt.inhPolygonData   = nullptr;
	polyExt.defaultContourData   = nullptr;
	polyExt.unid           = 0;

	for (ULong i = 0; i < poly2DArray.GetSize (); i++) {
		GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > poly2D = poly2DArray[i];

		verticesNum += poly2D->nVertices;
		contoursNum += poly2D->nContours;

		UnionBox (&poly2D->boundBox, &tmpBoundBox);

		if (i == 0) {
			if (poly2D->vertexInfos.GetSize () != 0 && poly2D->flags.isVertexUserData)
				polyExt.defaultVertexData   = (GS::GSPtr)(&poly2D->defaultVertexData);
			else
				polyExt.defaultVertexData   = nullptr;
			if (poly2D->inhEdgeInfos.GetSize () != 0 && poly2D->flags.isEdgeUserData)
				polyExt.defaultInhEdgeData  = (GS::GSPtr)(&poly2D->defaultEdgeData);
			else
				polyExt.defaultInhEdgeData  = nullptr;
			// 	if (poly2D->defaultUserData != nullptr)
			// 		polyExt.defaultUniqEdgeData = poly2D->defaultUserData;
			// 	else
			polyExt.defaultUniqEdgeData = nullptr;
			if (poly2D->inhPolygonInfo.GetSize () != 0 && poly2D->flags.isPolygonUserData)
				polyExt.inhPolygonData   = (GS::GSPtr)(&poly2D->inhPolygonInfo[0]);
			else
				polyExt.inhPolygonData   = nullptr;
			if (poly2D->contourInfos.GetSize() != 0 && poly2D->flags.isContourUserData)
				polyExt.defaultContourData   = (GS::GSPtr)(&poly2D->defaultContourData);
			else
				polyExt.defaultContourData   = nullptr;

		} else {
			;
		}
	}

	polyExt.boundBox	= tmpBoundBox;
	polyExt.nEdges		= verticesNum - contoursNum;

}

/* Callback functions */
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PGEDGEEXT CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPolyEdge (const PGPOLYEXT* polygon, GS::Int32 ind)
{
	PGEDGEEXT result;
	const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>* poly2D = reinterpret_cast<const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>*> (polygon->data);

	BNZeroMemory (&result, sizeof (result));
	result.status = NormalEdgeStatus;
	result.status.isArc = false;
	GS::Int32 inNHoles = 0;
	for (USize i = 1; i <= poly2D->nContours; i++) {
		GS::Int32 endEdgeIdx = poly2D->contourEnds[i] - i;
		if (ind == endEdgeIdx + 1)
			result.status.isBegHole = true;
		if (ind == endEdgeIdx) {
			result.status.isEndContour = true;
			//				if (i == poly2D->nContours)
			//					result.status.isEndPolygon = true;
		}
		if (ind > endEdgeIdx)
			inNHoles++;
	}
	ind += inNHoles;
	result.begPt = poly2D->vertices[ind];
	const double edgeLen = Geometry::Dist (poly2D->vertices[ind], poly2D->vertices[ind + 1]);
	result.invlen = (edgeLen > polygon->minVertexDist) ? 1.0 / edgeLen : Geometry::InvLen_ZeroEdge;
	result.fi1    =	0.0;
	result.fi2    = 0.0;
	UIndex arcIndex = poly2D->GetInternalArcIdx (ind);
	if (arcIndex > 0) {
		if (Geometry::ArcGetOrigo (&poly2D->vertices[ind], &poly2D->vertices[ind + 1], poly2D->arcs[arcIndex].arcAngle, &result.center)) {
			result.status.isArc = true;
			result.status.isArcRevoriented = poly2D->arcs[arcIndex].arcAngle < 0.0 ? true : false;
			result.radius = Geometry::Dist (result.center, poly2D->vertices[ind]);
			result.fi1    =	Geometry::ComputeFi (result.center, poly2D->vertices[ind]);
			result.fi2    = Geometry::ComputeFi (result.center, poly2D->vertices[ind + 1]);
		}
	}
	if (poly2D->vertexInfos.GetSize() != 0 && poly2D->flags.isVertexUserData)
		result.vertexData        = (GS::GSPtr) (&((poly2D->vertexInfos) [ind]));
	else
		result.vertexData        = nullptr;

	if (poly2D->inhEdgeInfos.GetSize() != 0 && poly2D->flags.isEdgeUserData)
		result.inhEdgeData        = (GS::GSPtr) (&((poly2D->inhEdgeInfos) [ind]));
	else
		result.inhEdgeData        = nullptr;

	result.uniqEdgeData        = nullptr;

	if (poly2D->contourInfos.GetSize() != 0 && poly2D->flags.isContourUserData)
		result.contourData        = (GS::GSPtr) (&((poly2D->contourInfos) [(inNHoles + 1)]));
	else
		result.contourData        = nullptr;
	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PGEDGEEXT CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPolyEdgeArr (const PGPOLYEXT* polygon, GS::Int32 ind)
{
	PGEDGEEXT result;
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >* poly2DArray = reinterpret_cast<GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >*> (polygon->data);
	ULong actPolyInd = 0;
	for (ULong i = 0; i < poly2DArray->GetSize (); i++) {
		GS::Int32 verticesNum = static_cast<GS::Int32>((*poly2DArray)[i]->nVertices);
		GS::Int32 contoursNum = static_cast<GS::Int32>((*poly2DArray)[i]->nContours);
		if (ind <= verticesNum - contoursNum) {
			actPolyInd = i;
			break;
		}
		ind -= (verticesNum - contoursNum);
	}

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > poly2D = (*poly2DArray)[actPolyInd];

	BNZeroMemory (&result, sizeof (result));
	result.status.isArc = false;
	GS::Int32 inNHoles = 0;
	for (USize i = 1; i <= poly2D->nContours; i++) {
		GS::Int32 endEdgeIdx = poly2D->contourEnds[i] - i;
		if (ind == endEdgeIdx + 1)
			result.status.isBegHole = true;
		if (ind == endEdgeIdx) {
			result.status.isEndContour = true;
			if (i == poly2D->nContours)
				result.status.isEndPolygon = true;
		}
		if (ind > endEdgeIdx)
			inNHoles++;
	}
	ind += inNHoles;
	result.begPt = poly2D->vertices[ind];
	const double edgeLen = Geometry::Dist (poly2D->vertices[ind], poly2D->vertices[ind + 1]);
	result.invlen = (edgeLen > polygon->minVertexDist) ? 1.0 / edgeLen : Geometry::InvLen_ZeroEdge;
	result.fi1    =	0.0;
	result.fi2    = 0.0;
	UIndex arcIndex = poly2D->GetInternalArcIdx (ind);
	if (arcIndex > 0) {
		if (Geometry::ArcGetOrigo (&poly2D->vertices[ind], &poly2D->vertices[ind + 1], poly2D->arcs[arcIndex].arcAngle, &result.center)) {
			result.status.isArc = true;
			result.status.isArcRevoriented = poly2D->arcs[arcIndex].arcAngle < 0.0 ? true : false;
			result.radius = Geometry::Dist (result.center, poly2D->vertices[ind]);
			result.fi1    =	Geometry::ComputeFi (result.center, poly2D->vertices[ind]);
			result.fi2    = Geometry::ComputeFi (result.center, poly2D->vertices[ind + 1]);
		}
	}
	if (poly2D->vertexInfos.GetSize() != 0 && poly2D->flags.isVertexUserData)
		result.vertexData        = (GS::GSPtr) (&((poly2D->vertexInfos) [ind]));
	else
		result.vertexData        = nullptr;

	if (poly2D->inhEdgeInfos.GetSize() != 0 && poly2D->flags.isEdgeUserData)
		result.inhEdgeData        = (GS::GSPtr) (&((poly2D->inhEdgeInfos) [ind]));
	else
		result.inhEdgeData        = nullptr;

	result.uniqEdgeData        = nullptr;

	if (poly2D->contourInfos.GetSize() != 0 && poly2D->flags.isContourUserData)
		result.contourData        = (GS::GSPtr) (&((poly2D->contourInfos) [(inNHoles + 1)]));
	else
		result.contourData        = nullptr;

	return result;
}

#ifdef DEBUVERS_RJ
extern GEOMETRY_DLL_EXPORT GS::ThreadSpecificStorage<USize> dbgContoursNum, dbgVerticesNum, dbgArcsNum;
#endif

#ifdef CHECKED_VERSION
// The variable is ThreadLocal to help debugging. The values can be acquired from the GS::Threads.
extern GEOMETRY_DLL_EXPORT GS::ThreadLocal<bool> contours_OK;
#endif

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErr CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolyEdge	(PGPOLYEXT* polygon, const PGEDGEEXT* pgedge)
{
	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>* poly2D = reinterpret_cast<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>*> (polygon->data);

	if (!pgedge->status.isEndPolygon) {
		if (pgedge->status.isBegHole)
			poly2D->AddOneContour (reinterpret_cast<const ContourUserData*> (pgedge->contourData));
		PolyArcRec arcRec;
		PolyArcRec* arcRecPtr = nullptr;
		if (pgedge->status.isArc) {
			arcRecPtr = &arcRec;
			arcRec.arcAngle = pgedge->fi2 - pgedge->fi1;
			arcRec.arcAngle = Geometry::NormFi02Pi(arcRec.arcAngle);
			if (pgedge->status.isArcRevoriented)
				arcRec.arcAngle -= 2.0 * PI;
		}
		poly2D->AddOneVertex (pgedge->begPt, reinterpret_cast<const VertexUserData*> (pgedge->vertexData), reinterpret_cast<const EdgeUserData*> (pgedge->inhEdgeData), arcRecPtr);
		/* status:invisible kezeles */
		if (pgedge->status.isEndContour) {
#ifdef CHECKED_VERSION
			contours_OK.Set (false);
#endif
			GS::Int32 firstInd = poly2D->contourEnds[poly2D->nContours - 1] + 1;
			VertexUserData vertexInfo;
			EdgeUserData edgeInfo;
			if (poly2D->vertexInfos.GetSize() != 0 && poly2D->flags.isVertexUserData)
				vertexInfo = (poly2D->vertexInfos) [firstInd];
			if (poly2D->inhEdgeInfos.GetSize() != 0 && poly2D->flags.isEdgeUserData)
				edgeInfo = (poly2D->inhEdgeInfos) [firstInd];
			poly2D->AddOneVertex (poly2D->vertices[firstInd], reinterpret_cast<const VertexUserData*> (&vertexInfo), reinterpret_cast<const EdgeUserData*> (&edgeInfo));
			if (poly2D->contourInfos.GetSize() != 0 && poly2D->flags.isContourUserData) {
				if (pgedge->contourData != nullptr)
					poly2D->contourInfos [poly2D->nContours] = *(reinterpret_cast<ContourUserData*> (pgedge->contourData));
				else
					poly2D->contourInfos[poly2D->nContours] = poly2D->defaultContourData;
			}
#ifdef CHECKED_VERSION
			if (polygon->nContours == (GS::Int32) poly2D->nContours)
				contours_OK.Set (true);
#endif
		}
	} else {
#ifdef DEBUVERS_RJ
		DBASSERT (dbgContoursNum.Get () == poly2D->nContours);
		DBASSERT (dbgArcsNum.Get () == poly2D->nArcs);
		DBASSERT (dbgVerticesNum.Get () == poly2D->nVertices);
#endif
#ifdef CHECKED_VERSION
		DBASSERT (contours_OK.Get ());
		contours_OK.Clear ();
#endif
	}
	DBCHECKCOREPOLY_MEMORY;
	return NoError;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErr CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolygon	(PGRESPOLYEXT* polygons, const PGPOLYEXT* newPoly, PGPOLYEXT** storedPoly)
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >	*resultPolys  = (GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > *)polygons->polygonsData;

#ifdef DEBUVERS_RJ
	dbgContoursNum.Set (newPoly->nContours);
	dbgArcsNum.Set (newPoly->nArcs);
	dbgVerticesNum.Set (newPoly->nEdges + newPoly->nContours);
#endif

	const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>* poly2D = reinterpret_cast<const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>*> (newPoly->data);
	DBASSERT (poly2D != nullptr);

	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>* newPoly2DPtr = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*poly2D, true);
	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPoly2D (newPoly2DPtr);
	newPoly2DPtr->CopyPolygonLevelDataFrom (*poly2D);
	newPoly2D->AllocateInternalData (0, 0, 1, newPoly->nEdges + newPoly->nContours, newPoly->nArcs, newPoly->nContours);

	newPoly2D->defaultVertexData	= poly2D->defaultVertexData;
	newPoly2D->defaultEdgeData		= poly2D->defaultEdgeData;
	newPoly2D->defaultContourData	= poly2D->defaultContourData;

	if (newPoly2D->inhPolygonInfo.GetSize() != 0 && newPoly2D->flags.isPolygonUserData && newPoly->inhPolygonData != nullptr)
		newPoly2D->inhPolygonInfo[0] = *(reinterpret_cast<const PolygonUserData*> (newPoly->inhPolygonData));

	newPoly2D->boundBox = newPoly->boundBox;

	resultPolys->Push (newPoly2D);
	*storedPoly = const_cast<PGPOLYEXT*> (newPoly);

	(*storedPoly)->newEdge = NewPolyEdge;
	(*storedPoly)->getEdge = nullptr;
	(*storedPoly)->sizeOfData = 0;
	(*storedPoly)->data = (GSPtr) newPoly2DPtr;
	return NoError;
}

#ifdef CHECKED_VERSION
// The variable is ThreadLocal to help debugging. The values can be acquired from the GS::Threads.
extern GEOMETRY_DLL_EXPORT GS::ThreadLocal<bool> contourlast_OK;
#endif

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErr CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolyEdgeArr	(PGPOLYEXT* polygon, const PGEDGEEXT* pgedge)
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >* poly2DArray = reinterpret_cast<GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >*> (polygon->data);
	if (poly2DArray == nullptr || poly2DArray->GetSize () == 0) {
		DBBREAK ();
		return Error;
	}

	if (!pgedge->status.isEndPolygon) {
		if (pgedge->status.isBegHole)
			poly2DArray->GetLast ()->AddOneContour (reinterpret_cast<const ContourUserData*> (pgedge->contourData));
		PolyArcRec arcRec;
		PolyArcRec* arcRecPtr = nullptr;
		if (pgedge->status.isArc) {
			arcRecPtr = &arcRec;
			arcRec.arcAngle = pgedge->fi2 - pgedge->fi1;
			arcRec.arcAngle = Geometry::NormFi02Pi(arcRec.arcAngle);
			if (pgedge->status.isArcRevoriented)
				arcRec.arcAngle -= 2.0 * PI;
		}
		poly2DArray->GetLast ()->AddOneVertex (pgedge->begPt, reinterpret_cast<const VertexUserData*> (pgedge->vertexData), reinterpret_cast<const EdgeUserData*> (pgedge->inhEdgeData), arcRecPtr);
		/* status:invisible kezeles */
		if (pgedge->status.isEndContour) {
#ifdef CHECKED_VERSION
			contourlast_OK.Set (false);
#endif
			GS::Int32 firstInd = poly2DArray->GetLast ()->contourEnds[poly2DArray->GetLast ()->nContours - 1] + 1;
			VertexUserData vertexInfo;
			EdgeUserData edgeInfo;
			if (poly2DArray->GetLast ()->vertexInfos.GetSize() != 0 && poly2DArray->GetLast ()->flags.isVertexUserData)
				vertexInfo = (poly2DArray->GetLast ()->vertexInfos) [firstInd];
			if (poly2DArray->GetLast ()->inhEdgeInfos.GetSize() != 0 && poly2DArray->GetLast ()->flags.isEdgeUserData)
				edgeInfo = (poly2DArray->GetLast ()->inhEdgeInfos) [firstInd];
			poly2DArray->GetLast ()->AddOneVertex (poly2DArray->GetLast ()->vertices[firstInd], reinterpret_cast<const VertexUserData*> (&vertexInfo), reinterpret_cast<const EdgeUserData*> (&edgeInfo));
			if (poly2DArray->GetLast ()->contourInfos.GetSize() != 0 && pgedge->contourData != nullptr) {
				if (pgedge->contourData != nullptr)
					(poly2DArray->GetLast ()->contourInfos) [poly2DArray->GetLast ()->nContours] = *(reinterpret_cast<ContourUserData*> (pgedge->contourData));
				else
					(poly2DArray->GetLast ()->contourInfos) [poly2DArray->GetLast ()->nContours] = poly2DArray->GetLast ()->defaultContourData;
			}
#ifdef CHECKED_VERSION
			if (polygon->nContours == (GS::Int32) poly2DArray->GetLast ()->nContours)
				contourlast_OK.Set (true);
#endif
		}
	} else {
#ifdef DEBUVERS_RJ
		DBASSERT (dbgContoursNum.Get () == poly2DArray->GetLast ()->nContours);
		DBASSERT (dbgArcsNum.Get () == poly2DArray->GetLast ()->nArcs);
		DBASSERT (dbgVerticesNum.Get () == poly2DArray->GetLast ()->nVertices);
#endif
#ifdef CHECKED_VERSION
		DBASSERT (contourlast_OK.Get ());
		contourlast_OK.Clear ();
#endif
	}
	DBCHECKCOREPOLY_MEMORY;
	return NoError;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErr CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolygonArr	(PGRESPOLYEXT* polygons, const PGPOLYEXT* newPoly, PGPOLYEXT** storedPoly)
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >* resultPolys  = (GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > *) polygons->polygonsData;

#ifdef DEBUVERS_RJ
	dbgContoursNum.Set (newPoly->nContours);
	dbgArcsNum.Set (newPoly->nArcs);
	dbgVerticesNum.Set (newPoly->nEdges + newPoly->nContours);
#endif

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >* poly2DArray = reinterpret_cast<GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >*> (newPoly->data);
	DBASSERT (poly2DArray != nullptr);
	if (poly2DArray == nullptr || poly2DArray->GetSize () == 0)
		ThrowGeometryExceptionAtError (ErrParam, "CorePolygon2D::NewPolygonArr", __FILE__, __LINE__);

	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>* newPoly2DPtr = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*poly2DArray, true);
	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPoly2D (newPoly2DPtr);
	newPoly2D->AllocateInternalData (0, 0, 1, newPoly->nEdges + newPoly->nContours, newPoly->nArcs, newPoly->nContours);

	if (newPoly2D->inhPolygonInfo.GetSize() != 0 && newPoly2D->flags.isPolygonUserData && newPoly->inhPolygonData != nullptr)
		newPoly2D->inhPolygonInfo[0] = *(reinterpret_cast<PolygonUserData*> (newPoly->inhPolygonData));

	newPoly2D->boundBox = newPoly->boundBox;

	resultPolys->Push (newPoly2D);
	*storedPoly = const_cast<PGPOLYEXT*> (newPoly);

 	(*storedPoly)->newEdge = NewPolyEdgeArr;
 	(*storedPoly)->getEdge = nullptr;
 	(*storedPoly)->sizeOfData = 0;
 	(*storedPoly)->data = (GSPtr) resultPolys;

	return NoError;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErr CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewSector (PGRESSECTOREXT* sectors, const Sector& newSector)
{
	GS::Array<Sector>* resSectors = reinterpret_cast<GS::Array<Sector>*> (sectors->sectorsData);
	resSectors->Push (newSector);
	return NoError;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::~CorePolygon2D ()
{
	FreeInternalData ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source)
{
	InitInternalData ();

	CopyInternalDataFrom (source, 0, 0, 0);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, USize verticesCapacity, USize arcsCapacity, USize contoursCapacity)
{
	InitInternalData ();

	CopyInternalDataFrom (source, verticesCapacity, arcsCapacity, contoursCapacity);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (Flags actFlags)
{
	InitInternalData ();
	flags = actFlags;
	if (inhPolygonInfo.GetSize() == 0 && flags.isPolygonUserData) {
		inhPolygonInfo.SetSize (1);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, bool copyPolygonLevelDataOnly)
{
	InitInternalData ();
	if (copyPolygonLevelDataOnly)
		CopyPolygonLevelDataFrom (source);
	else
		CopyInternalDataFrom (source, 0 /*verticesCapacity*/, 0 /*arcsCapacity*/, 0 /*contoursCapacity*/);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& source)
{
	if (source.GetSize () == 0)
		ThrowGeometryExceptionAtError (ErrParam, "CorePolygon2D::SetUserData", __FILE__, __LINE__);

	InitInternalData ();
	CopyPolygonLevelDataFrom (source);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (Flags actFlags, const Box2DData& box)
{
	InitInternalData ();
	flags = actFlags;

	if (box.IsEmpty ())
		return;

	AllocateInternalData (5 /*nVertices*/, 0 /*nArcs*/, 1 /*nContour*/);
	Box2DData tmpBox;
	tmpBox.xMin = GS::Min (box.xMin, box.xMax);
	tmpBox.xMax = GS::Max (box.xMin, box.xMax);
	tmpBox.yMin = GS::Min (box.yMin, box.yMax);
	tmpBox.yMax = GS::Max (box.yMin, box.yMax);
	Point2D coords[4];
	coords[0].x = tmpBox.xMin;
	coords[0].y = tmpBox.yMin;

	coords[1].x = tmpBox.xMax;
	coords[1].y = tmpBox.yMin;

	coords[2].x = tmpBox.xMax;
	coords[2].y = tmpBox.yMax;

	coords[3].x = tmpBox.xMin;
	coords[3].y = tmpBox.yMax;
	SetInternalData (coords, 4, nullptr /*arcs*/, 0 /*nArcs*/, nullptr /*contourEnds*/, 1 /*nContours*/, 0 /*PolyCreateFlags*/);
	status.isRegularized = (tmpBox.xMax - tmpBox.xMin > EPS && tmpBox.yMax - tmpBox.yMin > EPS);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (Flags actFlags, const Circle2D& circ)
{
	InitInternalData ();
	flags = actFlags;

	AllocateInternalData (5 /*nVertices*/, 4 /*nArcs*/, 1 /*nContour*/);

	const Point2D origo = circ.Origo ();
	const double radius = circ.Radius ();

	Point2D coords[4];
	coords[0].x = origo.x;
	coords[0].y = origo.y - radius;

	coords[1].x = origo.x + radius;
	coords[1].y = origo.y;

	coords[2].x = origo.x;
	coords[2].y = origo.y + radius;

	coords[3].x = origo.x - radius;
	coords[3].y = origo.y;

	PolyArcRec arcs[4] =  { PolyArcRec (1, 2, PI / 2), PolyArcRec (2, 3, PI / 2), PolyArcRec (3, 4, PI / 2), PolyArcRec (4, 5, PI / 2) };

	SetInternalData (coords, 4, arcs, 4 /*nArcs*/, nullptr /*contourEnds*/, 1 /*nContours*/, 0 /*PolyCreateFlags*/);
	status.isRegularized = (radius > EPS);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (Flags actFlags, const Ellipse& ell, ArcDivParams arcDivParams)
{
	InitInternalData ();
	flags = actFlags;

	GS::ArrayFB<GenArc, 4> quadrants;
	const Point2D rightPoint  = ell.GetOrigo() + Vector2D (ell.GetMainAxisLength(), 0);
	const Point2D leftPoint   = ell.GetOrigo() + Vector2D (-ell.GetMainAxisLength(), 0);
	const Point2D topPoint    = ell.GetOrigo() + Vector2D (0, ell.GetOtherAxisLength());
	const Point2D bottomPoint = ell.GetOrigo() + Vector2D (0, -ell.GetOtherAxisLength());
	quadrants.Push (GenArc::CreateEllipseArc (ell.GetOrigo(), rightPoint, topPoint, 0.0, ell.GetAxisLengthRatio()));
	quadrants.Push (GenArc::CreateEllipseArc (ell.GetOrigo(), topPoint, leftPoint, 0.0, ell.GetAxisLengthRatio()));
	quadrants.Push (GenArc::CreateEllipseArc (ell.GetOrigo(), leftPoint, bottomPoint, 0.0, ell.GetAxisLengthRatio()));
	quadrants.Push (GenArc::CreateEllipseArc (ell.GetOrigo(), bottomPoint, rightPoint, 0.0, ell.GetAxisLengthRatio()));
	GS::Array<GenArc> result;
	for (const GenArc& quandrant : quadrants) {
		GS::Array<Point2D> arcSegmentCorners;
		GS::Array<Point2D> arcSegmentCenters;
		Geometry::DivideEllArcToArcs (quandrant, arcDivParams, arcSegmentCorners, arcSegmentCenters);
		for (UIndex i = 0; i < arcSegmentCenters.GetSize (); ++i) {
			result.Push (GenArc::CreateCircleArc (arcSegmentCenters[i], arcSegmentCorners[i], arcSegmentCorners[i + 1]));
		}
	}
	const UInt32 arcNum = result.GetSize ();
	GS::Array<Point2D> coordList (arcNum);
	GS::Array<PolyArcRec> arcList (arcNum);
	GS::Array<UIndex> contourEndList ({ arcNum - 1 });
	for (UIndex i = 0; i < result.GetSize (); ++i) {
		const GenArc& arc = result[i];
		coordList.Push (arc.GetBegC ());
		arcList.Push (PolyArcRec (i, i + 1, arc.GetArcAngle ()));
	}
	UInt32 createFlags = Geometry::PolyCreateFlags_IdxRefInArcFromZero | Geometry::PolyCreateFlags_IdxRefInContourEndFromZero;

	AllocateInternalData (coordList.GetSize () + 1, arcList.GetSize (), 1);

	SetInternalData (coordList, arcList, contourEndList, createFlags);

	GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > regularizedPolygons;
	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult res;
	status.isRegularized = false;
	res = Regularize (regularizedPolygons);
	DBASSERT (res == ResultSameAsThis);
	if (res != ResultSameAsThis) {
		operator= (*(regularizedPolygons[0]));
		DBASSERT (regularizedPolygons.GetSize () == 1);
	}
	status.isRegularized = true;

}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, UIndex contourIdx, bool keepRegularized)
{
	DBCHECKINDEX_COREPOLY(contourIdx, 1, source.GetContourNum ());
	InitInternalData ();
	CopyPolygonLevelDataFrom (source);

	CopyInternalDataFrom (source, contourIdx);
	if (keepRegularized) {
		DBASSERT (source.status.isRegularized);
		if (source.status.isRegularized) {
			UpdateOrientation ();
			status.isRegularized = true;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (Flags actFlags, const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags)
{
	InitInternalData ();

	DBASSERT (arcList.IsEmpty () || contourEndList.IsEmpty () || ((PolyCreateFlags_IdxRefInArcFromZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) ||
		(!(PolyCreateFlags_IdxRefInArcFromZero & createFlags) && !(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (arcList.IsEmpty () || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));
	DBASSERT (contourEndList.IsEmpty () || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (contourEndList.IsEmpty () || (!contourEndList.IsEmpty () && contourEndList[0] == 0 && (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)) || (!contourEndList.IsEmpty () && !(PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)));

	flags = actFlags;
	status.isRegularized = false;

	UIndex coordOffset = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 0 : 1;

#ifdef CHECKED_VERSION
	UIndex coordIdxOffset = (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags) ? 0 : 1;
	UIndex contourIdxOffset = (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags) ? 0 : 1;
	UIndex firstContourEndIdx = (contourEndList.IsEmpty ()) ? coordList.GetSize ()-1 : contourEndList[1-contourIdxOffset]-coordIdxOffset;
	DBASSERT ((PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) && IsEqualCoord (coordList[1-coordOffset], coordList[firstContourEndIdx], EPS) ||
			  !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags));
#endif
	USize contourNum = 1;
	if (!contourEndList.IsEmpty ()) {
		if (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)
			contourNum = contourEndList.GetSize () - 1;
		else
			contourNum = contourEndList.GetSize ();
	}

	if (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) { //duplicated
		DBASSERT (contourEndList.IsEmpty () || coordList.GetSize ()-1 == contourEndList[contourEndList.GetSize ()-1]-coordIdxOffset);
		AllocateInternalData (coordList.GetSize () - 1 + coordOffset,
			(!arcList.IsEmpty () && PolyCreateFlags_DummyArcAtIdxZero & createFlags) ? arcList.GetSize () - 1 : arcList.GetSize (), contourNum);
	} else { //first coords not duplicated at contour ends in input list
		AllocateInternalData (coordList.GetSize () - 1 + coordOffset + contourNum,
			(!arcList.IsEmpty () && PolyCreateFlags_DummyArcAtIdxZero & createFlags) ? arcList.GetSize () - 1 : arcList.GetSize (), contourNum);
	}

	SetInternalData (coordList, arcList, contourEndList, createFlags);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (Flags actFlags, const Point2D* pCoords, USize coordNum, const PolyArcRec* pArcs, USize arcNum, const UIndex* pContourEnds, USize contourNum, GS::UInt32 createFlags)
{
	InitInternalData ();

	DBASSERT (pArcs == nullptr || pContourEnds == nullptr || ((PolyCreateFlags_IdxRefInArcFromZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) ||
		(!(PolyCreateFlags_IdxRefInArcFromZero & createFlags) && !(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (pArcs == nullptr || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));
	DBASSERT (pContourEnds == nullptr || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (contourNum == 1 || (contourNum > 1 && pContourEnds != nullptr));

	flags = actFlags;
	status.isRegularized = false;

#ifdef CHECKED_VERSION
	UIndex coordOffset = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 0 : 1;
	UIndex coordIdxOffset = (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags) ? 0 : 1;
	UIndex contourIdxOffset = (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags) ? 0 : 1;
	UIndex firstContourEndIdx = (pContourEnds == nullptr) ? coordNum-coordOffset : pContourEnds[1-contourIdxOffset]-coordIdxOffset;
	DBASSERT ((PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) && IsEqualCoord (pCoords[1-coordOffset], pCoords[firstContourEndIdx], EPS) ||
			  !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags));
#endif
	if (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) { //duplicated
		DBASSERT (pContourEnds == nullptr || coordNum-coordOffset == pContourEnds[contourNum-contourIdxOffset]-coordIdxOffset);
		AllocateInternalData (coordNum, arcNum, contourNum);
	} else { //first coords not duplicated at contour ends in input list
		AllocateInternalData (coordNum + contourNum, arcNum, contourNum);
	}

	SetInternalData (pCoords, coordNum, arcNum == 0 ? nullptr : pArcs, arcNum, pContourEnds, contourNum, createFlags);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FillCorePolygon2DFromContourDesc (const GS::Array<CustomPolyContourDescription<VertexUserData, EdgeUserData, ContourUserData> >& contourDesc)
{
	UIndex contourIdx = 0;
	UIndex vertexIdx = 0;
	UIndex vertIdx = 0;
	UIndex arcIdx = 1;
	for (contourIdx = 0; contourIdx < contourDesc.GetSize(); contourIdx++) {
		if (contourDesc[contourIdx].GetSegmentList().GetSize() <= 1) {
			//A 2 mar lehet ervenyes (pl. ket koriv) A Polygon2DData regularizalasa ugyis eldobja az ervenytelen lyukakat
			DBBREAK ();
			continue;
		}
		for (vertexIdx = 0; vertexIdx < contourDesc[contourIdx].GetSegmentList().GetSize() - 1; vertexIdx++) {
			vertIdx++;
			vertices[vertIdx] = contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetVertex().GetCoord();
			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
				((vertexInfos))[vertIdx] = contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetVertex().GetPolyVertexUserData();
			if (!contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().IsStraight()) {
				arcs[arcIdx].arcAngle = contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().GetArcAngle();
				arcs[arcIdx].begIndex = vertIdx;
				arcs[arcIdx].endIndex = arcs[arcIdx].begIndex + 1;
				arcIdx++;
			}
			if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
				((inhEdgeInfos))[vertIdx] = contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().GetPolyEdgeUserData();
		}

		// Contour descriptions created from (Irregular)Polygon2Ds or Polyline2Ds usually don't have duplicated vertices at the contour end
		// ASSERT if the first and last coordinates are equal (may come from polyline) but the last edge has a valid angle other than zero
		DBASSERT (!(!contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().HasInvalidAngle() && !contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().IsStraight() &&
			IsEqualCoord (contourDesc[contourIdx].GetSegmentList()[0].GetVertex().GetCoord(), contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetVertex().GetCoord(), EPS)));
		// ASSERT if the first and last coordinates are not equal but the last edge has an invalid angle (contour description originally converted from a fully open polyline)
		DBASSERT (!(contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().HasInvalidAngle() &&
			!IsEqualCoord (contourDesc[contourIdx].GetSegmentList()[0].GetVertex().GetCoord(), contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetVertex().GetCoord(), EPS)));

		vertIdx++;
		vertices[vertIdx] = contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetVertex().GetCoord();
		if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
			((vertexInfos))[vertIdx] = contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetVertex().GetPolyVertexUserData();
		if (!contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().HasInvalidAngle() && !contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().IsStraight()) {
			arcs[arcIdx].arcAngle = contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().GetArcAngle();
			arcs[arcIdx].begIndex = vertIdx;
			arcs[arcIdx].endIndex = arcs[arcIdx].begIndex + 1;
			arcIdx++;
		}
		if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
			((inhEdgeInfos))[vertIdx] = contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().GetPolyEdgeUserData();

		vertIdx++;
		vertices[vertIdx] = contourDesc[contourIdx].GetSegmentList()[0].GetVertex().GetCoord();
		if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
			((vertexInfos))[vertIdx] = contourDesc[contourIdx].GetSegmentList()[0].GetVertex().GetPolyVertexUserData();
		if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
			((inhEdgeInfos))[vertIdx] = contourDesc[contourIdx].GetSegmentList()[0].GetEdge().GetPolyEdgeUserData();

		contourEnds[contourIdx + 1] = vertIdx;
		if (contourInfos.GetSize() != 0 && flags.isContourUserData)
			((contourInfos))[contourIdx + 1] = contourDesc[contourIdx].GetPolyContourUserData();
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (Flags actFlags, const GS::Array<CustomPolyContourDescription<VertexUserData, EdgeUserData, ContourUserData> >& contourDesc)
{
	InitInternalData ();

	UIndex contourIdx = 0;
	UIndex vertexIdx = 0;
	UIndex verticesNum = 0;
	UIndex arcsNum = 0;
	UIndex contoursNum = 0;

	for (contourIdx = 0; contourIdx < contourDesc.GetSize(); contourIdx++) {
		if (contourDesc[contourIdx].GetSegmentList().GetSize() <= 1) {
			//A 2 mar lehet ervenyes (pl. ket koriv) A Polygon2DData regularizalasa ugyis eldobja az ervenytelen lyukakat
			continue;
		}
		contoursNum++;
		verticesNum += contourDesc[contourIdx].GetSegmentList().GetSize() + 1;
		for (vertexIdx = 0; vertexIdx < contourDesc[contourIdx].GetSegmentList().GetSize() - 1; vertexIdx++) {
			if (!contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().IsStraight()) {
				arcsNum++;
			}
		}
		if (!contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().HasInvalidAngle() &&
			!contourDesc[contourIdx].GetSegmentList()[vertexIdx].GetEdge().IsStraight()) {
			arcsNum++;
		}
	}

	flags = actFlags;

	if (contoursNum == 0 || verticesNum <= 1) {
		status.isRegularized = true;
		if (inhPolygonInfo.GetSize() == 0 && flags.isPolygonUserData) {
			inhPolygonInfo.SetSize (1);
		}
		return;
	}
	status.isRegularized = false;

	AllocateInternalData (verticesNum, arcsNum, contoursNum);

	FillCorePolygon2DFromContourDesc (contourDesc);

	RemoveSmallArcs ();

	UpdateBoundingBox ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CorePolygon2D (const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline)
{
	InitInternalData ();

	flags.isSameDirEdgeLegal = polyline.flags.isSameDirEdgeLegal;
	flags.isVertexUserData = polyline.flags.isVertexUserData;
	flags.isEdgeUserData = polyline.flags.isEdgeUserData;
	flags.isPolygonUserData = polyline.flags.isPolygonUserData;

	flags.isContourUserData = polyline.flags.isPolygonUserData;

	if (!polyline.IsEmpty ()) {
		status.isRegularized = false;

		AllocateInternalData ((polyline.flags.isClosed || polyline.IsFirstLastCoordEqual ()) ? polyline.vertices.GetSize () - 1 : polyline.vertices.GetSize (), polyline.arcs.GetSize () - 1, 1);
		GS::UInt32 createFlags = PolyCreateFlags_Polygon2DDataRepresentation;
		if (!polyline.flags.isClosed && !polyline.IsFirstLastCoordEqual ())
			createFlags &= ~PolyCreateFlags_1stCoordDuplAtContourEnd;
		GS::ArrayFB<UIndex,6> coEnds;
		SetInternalData (polyline.vertices, polyline.arcs, coEnds, createFlags);
		vertices [nVertices] = vertices [1];

		if (flags.isVertexUserData && polyline.flags.isVertexUserData) {
			CopyInfo_Data <VertexUserData> (vertexInfos, 1, polyline.vertexInfos, 1, GS::Min (GetVertexNum (), polyline.GetVertexNum ()));
			vertexInfos [nVertices] = vertexInfos [1];
		}
		if (flags.isEdgeUserData && polyline.flags.isEdgeUserData) {
			CopyInfo_Data <EdgeUserData> (inhEdgeInfos, 1, polyline.inhEdgeInfos, 1, GS::Min (GetEdgeNum (), polyline.GetEdgeNum ()));
			inhEdgeInfos [nVertices] = inhEdgeInfos [1];
		}
		if (flags.isContourUserData)
			contourInfos[1] = defaultContourData;
	}
	if (flags.isPolygonUserData && polyline.flags.isPolygonUserData)
		inhPolygonInfo [0] = (polyline.inhPolygonInfo) [0];
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (Flags actFlags, const Point2D* pCoords, USize coordNum, const PolyArcRec* pArcs, USize arcNum, const UIndex* pContourEnds, USize contourNum, GS::UInt32 createFlags, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result)
{
	DBASSERT (pArcs == nullptr || pContourEnds == nullptr || ((PolyCreateFlags_IdxRefInArcFromZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) ||
		(!(PolyCreateFlags_IdxRefInArcFromZero & createFlags) && !(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (pArcs == nullptr || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));
	DBASSERT (pContourEnds == nullptr || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (contourNum == 1 || (contourNum > 1 && pContourEnds != nullptr));

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (actFlags);

#ifdef CHECKED_VERSION
	UIndex coordOffset = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 0 : 1;
	UIndex coordIdxOffset = (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags) ? 0 : 1;
	UIndex contourIdxOffset = (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags) ? 0 : 1;
	UIndex firstContourEndIdx = (pContourEnds == nullptr) ? coordNum-coordOffset : pContourEnds[1-contourIdxOffset]-coordIdxOffset;
	DBASSERT ((PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) && IsEqualCoord (pCoords[1-coordOffset], pCoords[firstContourEndIdx], EPS) ||
			  !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags));
#endif
	if (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) { //duplicated
		DBASSERT (pContourEnds == nullptr || coordNum-coordOffset == pContourEnds[contourNum-contourIdxOffset]-coordIdxOffset);
		tmpPoly->AllocateInternalData (coordNum, arcNum, contourNum);
	} else //first coords not duplicated at contour ends in input list
		tmpPoly->AllocateInternalData (coordNum + contourNum, arcNum, contourNum);

	tmpPoly->SetInternalData (pCoords, coordNum, arcNum == 0 ? nullptr : pArcs, arcNum, pContourEnds, contourNum, createFlags);

	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
		DBASSERT (result.GetSize () == 0);
		result.Push (tmpPoly);
	}
}

//template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
//void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create(Flags actFlags, const Polygon2DData& polygon, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result)
//
//{
//	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (actFlags, polygon);
//
//	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
//		DBASSERT (result.GetSize () == 0);
//		result.Push (tmpPoly);
//	}
//}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (Flags actFlags, const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result)
{
	DBASSERT (arcList.IsEmpty () || contourEndList.IsEmpty () || ((PolyCreateFlags_IdxRefInArcFromZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) ||
		(!(PolyCreateFlags_IdxRefInArcFromZero & createFlags) && !(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (arcList.IsEmpty () || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));
	DBASSERT (contourEndList.IsEmpty () || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (contourEndList.IsEmpty () || (!contourEndList.IsEmpty () && contourEndList[0] == 0 && (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)) || (!contourEndList.IsEmpty () && !(PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)));

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (actFlags, coordList, arcList, contourEndList, createFlags);

	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
		DBASSERT (result.GetSize () == 0);
		result.Push (tmpPoly);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (Flags actFlags, const GS::Array<CustomPolyContourDescription<VertexUserData, EdgeUserData, ContourUserData> >& contourDesc, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result)
{
	UIndex contourIdx = 0;
	UIndex verticesNum = 0;
	UIndex contoursNum = 0;

	for (contourIdx = 0; contourIdx < contourDesc.GetSize(); contourIdx++) {
		contoursNum++;
		verticesNum += contourDesc[contourIdx].GetSegmentList().GetSize() + 1;
	}

	if (contoursNum == 0 || verticesNum <= 1) {
		result.Push (new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (actFlags));
		return;
	}

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (actFlags, contourDesc);

	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
		DBASSERT (result.GetSize () == 0);
		result.Push (tmpPoly);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result)
{
	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (polyline);

	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
		DBASSERT (result.GetSize () == 0);
		result.Push (tmpPoly);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonDataVertices (Point2D* destCoords, USize& coordNum,  const GS::Array<UIndex>& reversedContourIndices, GS::UInt32 createFlags) const
{
	bool errorOccured = false;
	//vertices
	USize numOfCoords = nVertices;
	if (!(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) //do not duplicate first coords at contour ends
		numOfCoords -= nContours;

	if (destCoords != nullptr) {
		if (numOfCoords <= coordNum) {
			const Point2D* sourceCoords = vertices.GetContent ();
			if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags)) //do not start with blank coord
				sourceCoords++;
			if ((PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) && reversedContourIndices.IsEmpty ()) //duplicate first coords at contour ends
				BNCopyMemory (destCoords, sourceCoords, ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? nVertices + 1 : nVertices) * sizeof (Point2D));
			else {
				Point2D* tmpCoords = destCoords;
				if (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) { //start with blank coord
					*tmpCoords = *sourceCoords;
					sourceCoords++;
					tmpCoords++;
				}
				USize contourLength;
				if (reversedContourIndices.IsEmpty ()) {
					for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
						contourLength = contourEnds [contourIdx] - contourEnds [contourIdx - 1] - 1;
						BNCopyMemory (tmpCoords, sourceCoords, contourLength * sizeof (Point2D));
						tmpCoords += contourLength;
						sourceCoords += contourLength + 1;
					}
				} else {
					for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
						contourLength = contourEnds [contourIdx] - contourEnds [contourIdx - 1] - 1;
						if (reversedContourIndices.Contains (contourIdx)) {
							for (GSIndex vertOffset = contourLength; vertOffset > 0; vertOffset--, tmpCoords++)
								*tmpCoords = *(sourceCoords + vertOffset);
							if (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) {
								*tmpCoords = *(sourceCoords + contourLength);
								tmpCoords++;
							}
						} else {
							UIndex duplOffset = (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) ? 1 : 0;
							BNCopyMemory (tmpCoords, sourceCoords, (contourLength+duplOffset) * sizeof (Point2D));
							tmpCoords += contourLength + duplOffset;
						}
						sourceCoords += contourLength + 1;
					}
				}
			}
		} else
			errorOccured = true;
	}
	coordNum = numOfCoords;
	return !errorOccured;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonDataVertices (GS::Array<Point2D>& destCoordList,  const GS::Array<UIndex>& reversedContourIndices, GS::UInt32 createFlags) const
{
	destCoordList.Clear (true);
	//vertices
	if (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags && reversedContourIndices.IsEmpty ()) { //duplicate first coords at contour ends
		for (UIndex vertIdx = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 0 : 1; vertIdx <= nVertices; vertIdx++)
			destCoordList.Push (vertices[vertIdx]);
	} else {
		if (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) //start with blank coord
			destCoordList.Push (vertices[0]);
		if (reversedContourIndices.IsEmpty ()) {
			for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++)
				for (UIndex vertIdx = contourEnds[contourIdx - 1] + 1; vertIdx < contourEnds[contourIdx]; vertIdx++)
					destCoordList.Push (vertices[vertIdx]);
		} else {
			for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
				if (reversedContourIndices.Contains (contourIdx)) {
					for (UIndex vertIdx = contourEnds[contourIdx]; vertIdx > contourEnds [contourIdx - 1] + 1; vertIdx--)
						destCoordList.Push (vertices[vertIdx]);
					if (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)
						destCoordList.Push (vertices[contourEnds[contourIdx]]);
				} else {
					UIndex duplOffset = (PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) ? 1 : 0;
					for (UIndex vertIdx = contourEnds[contourIdx - 1] + 1; vertIdx < contourEnds[contourIdx] + duplOffset; vertIdx++)
						destCoordList.Push (vertices[vertIdx]);
				}
			}
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonDataArcs (PolyArcRec* destArcs, USize& arcNum, const GS::Array<UIndex>& reversedContourIndices, GS::UInt32 createFlags) const
{
	bool errorOccured = false;
	//arcs
	if (destArcs != nullptr) {
		if (nArcs <= arcNum) {
			const PolyArcRec* sourcePolyArcs = arcs.GetContent ();
			UIndex arcOffset = 0;
			if (PolyCreateFlags_DummyArcAtIdxZero & createFlags) //start with blank PolyArc
				arcOffset++;
			else
				sourcePolyArcs++;
			BNCopyMemory (destArcs, sourcePolyArcs, (nArcs + arcOffset) * sizeof (PolyArcRec));

			if ((!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)) ||
				!(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) || !reversedContourIndices.IsEmpty ()) {
					UIndex begVertexIdx = 0;
					UIndex endVertexIdx = 0;
					//first meaningful coord should be at index 0 or indexing should not follow duplicated first coord at contour end
					for (UIndex arcIdx = arcOffset; arcIdx < nArcs + arcOffset; arcIdx++) {
						for (UIndex idx = 0; idx < reversedContourIndices.GetSize (); idx++) {
							DBCHECKINDEX_COREPOLY (reversedContourIndices[idx], 1, GetContourNum ());
							begVertexIdx = contourEnds[reversedContourIndices[idx]-1]+1;
							endVertexIdx = contourEnds[reversedContourIndices[idx]];
							if (destArcs[arcIdx].begIndex >= begVertexIdx && destArcs[arcIdx].begIndex < endVertexIdx) {
								destArcs[arcIdx].begIndex = (endVertexIdx + begVertexIdx - destArcs[arcIdx].begIndex) - 1; //previous begIndex will become new endIndex (this is why we need the -1)
								destArcs[arcIdx].arcAngle *= -1;
							}
						}
						if (!(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) //indexing does not follow duplicated first coord at contour end
							destArcs[arcIdx].begIndex = InternalVertexIdx2VertexIdx (destArcs[arcIdx].begIndex);
						if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) &&
							(PolyCreateFlags_IdxRefInArcFromZero & createFlags)) //first meaningful coord at index 0
							destArcs[arcIdx].begIndex--;
						destArcs[arcIdx].endIndex = destArcs[arcIdx].begIndex + 1;
					}
			}
		} else
			errorOccured = true;
	}
	arcNum = nArcs;
	return !errorOccured;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonDataArcs (GS::Array<PolyArcRec>& destArcList, const GS::Array<UIndex>& reversedContourIndices, GS::UInt32 createFlags) const
{
	destArcList.Clear (true);
	//arcs
	for (UIndex arcIdx = (PolyCreateFlags_DummyArcAtIdxZero & createFlags) ? 0 : 1; arcIdx <= nArcs; arcIdx++)
		destArcList.Push (arcs[arcIdx]);

	if ((!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)) ||
		!(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) || !reversedContourIndices.IsEmpty ()) {
			UIndex begVertexIdx = 0;
			UIndex endVertexIdx = 0;
			//first meaningful coord should be at index 0 or indexing should not follow duplicated first coord at contour end
			UIndex arcOffset = 0;
			if (PolyCreateFlags_DummyArcAtIdxZero & createFlags) //start with blank PolyArc
				arcOffset++;

			for (UIndex arcIdx = arcOffset; arcIdx < nArcs + arcOffset; arcIdx++) {
				for (UIndex idx = 0; idx < reversedContourIndices.GetSize (); idx++) {
					DBCHECKINDEX_COREPOLY (reversedContourIndices[idx], 1, GetContourNum ());
					begVertexIdx = contourEnds[reversedContourIndices[idx]-1]+1;
					endVertexIdx = contourEnds[reversedContourIndices[idx]];
					if (destArcList[arcIdx].begIndex >= begVertexIdx && destArcList[arcIdx].begIndex < endVertexIdx) {
						destArcList[arcIdx].begIndex = (endVertexIdx + begVertexIdx - destArcList[arcIdx].begIndex) - 1; //previous begIndex will become new endIndex (this is why we need the -1)
						destArcList[arcIdx].arcAngle *= -1;
					}
				}
				if (!(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) //indexing does not follow duplicated first coord at contour end
					destArcList[arcIdx].begIndex = InternalVertexIdx2VertexIdx (destArcList[arcIdx].begIndex);
				if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) &&
					(PolyCreateFlags_IdxRefInArcFromZero & createFlags)) //first meaningful coord at index 0
					destArcList[arcIdx].begIndex--;
				destArcList[arcIdx].endIndex = destArcList[arcIdx].begIndex + 1;
			}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonDataContours (UIndex* destContourEnds, USize& contourNum, GS::UInt32 createFlags) const
{
	bool errorOccured = false;
	//contour ends
	if (destContourEnds != nullptr) {
		if (nContours <= contourNum) {
			const UIndex* sourceContourEnds = contourEnds.GetContent ();
			UIndex contourOffset = 0;
			if (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags) //start with blank contour end
				contourOffset++;
			else
				sourceContourEnds++;
			BNCopyMemory (destContourEnds, sourceContourEnds, (nContours + contourOffset) * sizeof (UIndex));

			if ((!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) ||
				!(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) {
					//first meaningful coord at index 0 or indexing does not follow duplicated first coords at contour ends
					for (UIndex contourIdx = contourOffset; contourIdx < nContours + contourOffset; contourIdx++) {
						if (!(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) //indexing does not follow duplicated first coords at contour ends
							destContourEnds[contourIdx] = InternalVertexIdx2VertexIdx (destContourEnds[contourIdx] - 1);
						if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) &&
							(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) //first meaningful coord at index 0
							destContourEnds[contourIdx]--;
					}
			}
		} else
			errorOccured = true;
	}
	contourNum = nContours;
	return !errorOccured;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonDataContours (GS::Array<UIndex>& destContourEndList, GS::UInt32 createFlags) const
{
	destContourEndList.Clear (true);
	//contour ends
	for (UIndex contourIdx = (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags) ? 0 : 1; contourIdx <= nContours; contourIdx++)
		destContourEndList.Push (contourEnds[contourIdx]);

	if ((!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) ||
		!(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) {
			//first meaningful coord at index 0 or indexing does not follow duplicated first coords at contour ends
			UIndex contourOffset = 0;
			if (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags) //start with blank contour end
				contourOffset++;

			for (UIndex contourIdx = contourOffset; contourIdx < nContours + contourOffset; contourIdx++) {
				if (!(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) //indexing does not follow duplicated first coords at contour ends
					destContourEndList[contourIdx] = InternalVertexIdx2VertexIdx (destContourEndList[contourIdx] - 1);
				if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) &&
					(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) //first meaningful coord at index 0
					destContourEndList[contourIdx]--;
			}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcContourPerimeter (UIndex contourIdx) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 0, GetContourNum ());
	double perimeter = 0.0;

	ULong contoursNum = (contourIdx != 0 ? contourIdx : nContours);
	for (ULong j = (contourIdx != 0 ? contourIdx : 1); j <= contoursNum; j++) {
		ULong iBegContour = contourEnds[j - 1] + 1;
		ULong iEndContour = contourEnds[j];

		for (ULong iVertex = iBegContour + 1; iVertex <= iEndContour; iVertex++) {
			Point2D begEdge = vertices [iVertex - 1];
			Point2D endEdge = vertices [iVertex];
			UIndex arcIndex;

			arcIndex = GetInternalArcIdx (iVertex - 1);
			if (arcIndex == 0)
				perimeter += Geometry::Dist (begEdge, endEdge);
			else {
				Point2D origC;
				Geometry::ArcGetOrigo (&begEdge, &endEdge, arcs[arcIndex].arcAngle, &origC);
				perimeter += (Geometry::Dist (origC, begEdge) * fabs (arcs[arcIndex].arcAngle));
			}
		}
	}

	return perimeter;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>&	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator= (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source)
{
	if (this == &source)
		return *this;

	DBCHECKCOREPOLY_ONEREFTOTHIS;

	FreeInternalData ();
	InitInternalData ();

	CopyInternalDataFrom (source, 0, 0, 0);

	return *this;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CompareGeometry (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source) const
{
	GS::Int32 differences = 0;
	// 	if (polyChanges != nullptr)
	// 		polyChanges->Clear ();

	for (UIndex pContour = 1; pContour <= source.nContours; pContour++) {
		UIndex pFirstContourVertex = pContour == 1 ? 1 : (source.contourEnds)[pContour - 1] + 1;
		UIndex pLastContourVertex = (source.contourEnds)[pContour];
		for (UIndex vp = pFirstContourVertex; vp < pLastContourVertex; ++vp) {
			const Sector *pEdge = reinterpret_cast<const Sector*> (&source.vertices[vp]);
			UIndex ap = source.GetInternalArcIdx (vp);
			bool found = false;
			for (UIndex rContour = 1; rContour <= nContours; rContour++) {
				UIndex rFirstContourVertex = rContour == 1 ? 1 : (contourEnds)[rContour - 1] + 1;
				UIndex rLastContourVertex = (contourEnds)[rContour];
				for (UIndex vr = rFirstContourVertex; vr < rLastContourVertex; ++vr) {
					const Sector *rEdge = reinterpret_cast<const Sector*> (&vertices[vr]);
					UIndex ar = GetInternalArcIdx (vr);
					if (
						(fabs (pEdge->c1.x - rEdge->c1.x) < EPS) && (fabs (pEdge->c1.y - rEdge->c1.y) < EPS) &&
						(fabs (pEdge->c2.x - rEdge->c2.x) < EPS) && (fabs (pEdge->c2.y - rEdge->c2.y) < EPS) &&
						((ap > 0 && ar > 0 && fabs (source.arcs[ap].arcAngle - arcs[ar].arcAngle) < EPS) || (ap <= 0 && ar <= 0))
						) {
							found = true;
							break;
					}
				}
			}
			if (!found) {
				++differences;
				// 			if (polyChanges != nullptr)
				// 				polyChanges->Add (vp);
				//			else
				return false;

			}
		}
	}

	return (differences == 0);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Compare (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source) const
{
	if (inhPolygonInfo.GetSize() != (source.inhPolygonInfo).GetSize() || vertexInfos.GetSize() != (source.vertexInfos).GetSize() ||
		inhEdgeInfos.GetSize() != (source.inhEdgeInfos).GetSize() || contourInfos.GetSize() != (source.contourInfos).GetSize())
		return false;
	if (flags.isSameDirEdgeLegal != source.flags.isSameDirEdgeLegal)
		return false;
	if (flags.force64BitPrecision != source.flags.force64BitPrecision)
		return false;
	if (flags.isContourUserData != source.flags.isContourUserData)
		return false;
	if (flags.isEdgeUserData != source.flags.isEdgeUserData)
		return false;
	if (flags.isVertexUserData != source.flags.isVertexUserData)
		return false;
	if (flags.isPolygonUserData != source.flags.isPolygonUserData)
		return false;

	if ((inhPolygonInfo.GetSize() == 0) != ((source.inhPolygonInfo).GetSize() == 0))
		return false;
	if (flags.isPolygonUserData)
		if (inhPolygonInfo[0] != (source.inhPolygonInfo)[0])
			return false;

	if (nContours != source.nContours)
		return false;

	if (nVertices != source.nVertices)
		return false;

	if (nArcs != source.nArcs)
		return false;

	return CompareGeometry (source);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
template <class VertexUserDataTarget, class EdgeUserDataTarget, class ContourUserDataTarget, class PolygonUserDataTarget>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConvertFromCorePolygon2D (
	CorePolygon2D<VertexUserDataTarget, EdgeUserDataTarget, ContourUserDataTarget, PolygonUserDataTarget> & polygon,
	const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & source,
	Poly2DUserDataConverter<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData,
	VertexUserDataTarget, EdgeUserDataTarget, ContourUserDataTarget, PolygonUserDataTarget>* userDataConverter)
{
	polygon.Clear ();
	polygon.CopyInternalDataFromWithUserData (source, 0, 0, 0, userDataConverter);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Convert (GS::Array<CustomPolyContourDescription<VertexUserData, EdgeUserData, ContourUserData> >& contourDescArray) const
{
	contourDescArray.Clear (true);

	UIndex vertexIdx;
	UIndex contourIdx;
	for (contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		CustomPolyContourDescription<VertexUserData, EdgeUserData, ContourUserData> contourDesc;
		if (contourInfos.GetSize() != 0 && flags.isContourUserData)
			contourDesc.SetPolyContourUserData ((contourInfos)[contourIdx]);

		UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);
		for(vertexIdx = begVertexIdx; vertexIdx < endVertexIdx; vertexIdx++)
		{
			CustomPolySegment<VertexUserData, EdgeUserData> segment;

			segment.GetVertexRef ().SetCoord (vertices[vertexIdx]);
			if (nArcs != 0 && arcs.GetSize () > 1) {
				for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
					if (arcs[arcIdx].begIndex == vertexIdx)
						segment.GetEdgeRef ().SetArcAngle (arcs[arcIdx].arcAngle);
				}
			}
			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
				segment.GetVertexRef ().SetPolyVertexUserData ((vertexInfos)[vertexIdx]);
			if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
				segment.GetEdgeRef ().SetPolyEdgeUserData ((inhEdgeInfos)[vertexIdx]);
			contourDesc.GetSegmentListRef ().Push(segment);
		}
		contourDescArray.Push(contourDesc);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonData (Point2D* destCoords, USize& coordNum, PolyArcRec* destArcs, USize& arcNum, UIndex* destContourEnds, USize& contourNum, const GS::Array<UIndex>& reversedContourIndices, GS::UInt32 createFlags) const
{
	DBASSERT (((PolyCreateFlags_IdxRefInArcFromZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) ||
		(!(PolyCreateFlags_IdxRefInArcFromZero & createFlags) && !(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));
	DBASSERT (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));

	if (IsEmpty ()) {
		coordNum = 0;
		arcNum = 0;
		contourNum = 0;
		return;
	}
	bool errorOccured = false;

	if (CopyPolygonDataVertices (destCoords, coordNum, reversedContourIndices, createFlags) != true)
		errorOccured = true;
	if (CopyPolygonDataArcs (destArcs, arcNum, reversedContourIndices, createFlags) != true)
		errorOccured = true;
	if (CopyPolygonDataContours (destContourEnds, contourNum, createFlags) != true)
		errorOccured = true;

	if (errorOccured)
		throw GS::OutOfMemoryException ("Error in CorePolygon2D::CopyPolygonData!!!", __FILE__, __LINE__);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonData (GS::Array<Point2D>& destCoordList, GS::Array<PolyArcRec>& destArcList, GS::Array<UIndex>& destContourEndList, const GS::Array<UIndex>& reversedContourIndices, GS::UInt32 createFlags) const
{
	DBASSERT (((PolyCreateFlags_IdxRefInArcFromZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) ||
		(!(PolyCreateFlags_IdxRefInArcFromZero & createFlags) && !(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));
	DBASSERT (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));

	if (IsEmpty ())
		return;

	CopyPolygonDataVertices (destCoordList, reversedContourIndices, createFlags);
	CopyPolygonDataArcs (destArcList, reversedContourIndices, createFlags);
	CopyPolygonDataContours (destContourEndList, createFlags);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetUserData (const PolygonUserData* userData)
{
	if (inhPolygonInfo.GetSize() == 0 || !flags.isPolygonUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolygon2D::SetUserData", __FILE__, __LINE__);
	}
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	inhPolygonInfo[0] = *userData;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const PolygonUserData* CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetUserData (void) const
{
	if (inhPolygonInfo.GetSize() == 0 || !flags.isPolygonUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolygon2D::SetUserData", __FILE__, __LINE__);
	}
	return (&(inhPolygonInfo[0]));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetSameDirEdgeLegalAndRegularize (bool isSameDirEdgeLegal, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result)
{
	if (flags.isSameDirEdgeLegal != isSameDirEdgeLegal && !isSameDirEdgeLegal) {
		flags.isSameDirEdgeLegal = isSameDirEdgeLegal;
		status.isRegularized = false;
		RemoveSameDirEdge ();
		CorePolygon2D::PolygonResult polygonResult = Regularize (result);

		return polygonResult;
	}

	flags.isSameDirEdgeLegal = isSameDirEdgeLegal;
	return ResultSameAsThis;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetForce64BitPrecision (bool force64BitPrecision, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result)
{
	if (flags.force64BitPrecision != force64BitPrecision && force64BitPrecision) {
		flags.force64BitPrecision = force64BitPrecision;
		status.isRegularized = false;
		return Regularize (result);
	}

	flags.force64BitPrecision = force64BitPrecision;
	return ResultSameAsThis;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetIsVertexUserData	(bool actIsUserData)
{
	if (flags.isVertexUserData == actIsUserData)
		return;
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	flags.isVertexUserData = actIsUserData;
	if (flags.isVertexUserData) {
		if (vertexInfos.GetSize() == 0) {
			vertexInfos.SetSize (vertices.GetSize ());
		} else {
			DBBREAK_STR ("Ennek uresnek kell lenni");
			vertexInfos.SetSize (vertices.GetSize ());
		}
//		BNZeroMemory (vertexInfos, BMGetPtrSize (vertexInfos));
	} else {
		vertexInfos.Clear (true);
	}
}

//bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetIsVertexUserData	() const { return flags.isVertexUserData; }

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetIsEdgeUserData		(bool actIsUserData)
{
	if (flags.isEdgeUserData == actIsUserData)
		return;
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	flags.isEdgeUserData = actIsUserData;
	if (flags.isEdgeUserData) {
		if (inhEdgeInfos.GetSize() == 0) {
			inhEdgeInfos.SetSize (vertices.GetSize ());
		} else {
			DBBREAK_STR ("Ennek uresnek kell lenni");
			inhEdgeInfos.SetSize (vertices.GetSize ());
		}
//		BNZeroMemory (inhEdgeInfos, BMGetPtrSize (inhEdgeInfos));
	} else {
		inhEdgeInfos.Clear (true);
	}
}

//bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetIsEdgeUserData		() const { return flags.isEdgeUserData; }

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetIsContourUserData	(bool actIsUserData)
{
	if (flags.isContourUserData == actIsUserData)
		return;
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	flags.isContourUserData = actIsUserData;
	if (flags.isContourUserData) {
		if (contourInfos.GetSize() == 0) {
			contourInfos.SetSize (contourEnds.GetSize ());
		} else {
			DBBREAK_STR ("Ennek uresnek kell lenni");
			contourInfos.SetSize (contourEnds.GetSize ());
		}
//		BNZeroMemory (contourInfos, BMGetPtrSize (contourInfos));
	} else {
		contourInfos.Clear (true);
	}
}

//bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetIsContourUserData	() const { return flags.isContourUserData; }

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetIsPolygonUserData	(bool actIsUserData)
{
	if (flags.isPolygonUserData == actIsUserData)
		return;
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	flags.isPolygonUserData = actIsUserData;
	if (flags.isPolygonUserData) {
		if (inhPolygonInfo.GetSize() == 0) {
			inhPolygonInfo.SetSize (1);
		}
		inhPolygonInfo [0] = PolygonUserData ();
	} else {
		inhPolygonInfo.Clear (true);
	}
}

//bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetIsPolygonUserData	() const { return flags.isPolygonUserData; }

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetVertexDefaultUserData (const VertexUserData& userData)
{
	defaultVertexData = userData;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResetUserData (void)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	if (GetIsVertexUserData ()) {
		defaultVertexData = VertexUserData ();
		vertexInfos.Fill (defaultVertexData, 0, vertexInfos.GetSize ());
	}
	if (GetIsEdgeUserData ()) {
		defaultEdgeData = EdgeUserData ();
		inhEdgeInfos.Fill (defaultEdgeData, 0, inhEdgeInfos.GetSize ());
	}
	if (GetIsContourUserData ()) {
		defaultContourData = ContourUserData ();
		contourInfos.Fill (defaultContourData, 0, contourInfos.GetSize ());
	}
	if (GetIsPolygonUserData ()) {
		const PolygonUserData data;
		SetUserData (&data);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const VertexUserData& CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexDefaultUserData (void) const
{
	return (defaultVertexData);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexNum (void) const
{
	DBASSERT (nVertices >= 0);
	if (nVertices <= 0)
		return 0;
	return nVertices - nContours;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexIdx (const Point2D& coord) const
{
	UIndex vertexIdx = 0;
	for (vertexIdx = 1; vertexIdx <= nVertices; vertexIdx++) {
		if (Geometry::IsEqualCoord (coord, vertices[vertexIdx], EPS)) {
			return InternalVertexIdx2VertexIdx (vertexIdx);
		}
	}
	return GetVertexNum () + 1;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const Point2D& CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetCoord (UIndex vertexIdx) const
{
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	vertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);
	return vertices[vertexIdx];
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetCoord (UIndex vertexIdx, const Point2D& newCoord)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	status.isRegularized = false;
	flags.isSameDirEdgeLegal = true;

	vertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);
	vertices[vertexIdx] = newCoord;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const VertexUserData* CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexUserData (UIndex vertexIdx) const
{
	if (vertexInfos.GetSize() == 0 || !flags.isVertexUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolygon2D::GetVertexUserData", __FILE__, __LINE__);
	}
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	vertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);
	return &(vertexInfos [vertexIdx]);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetVertexUserData (UIndex vertexIdx, const VertexUserData* userData)
{
	if (vertexInfos.GetSize() == 0 || !flags.isVertexUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolygon2D::SetVertexUserData", __FILE__, __LINE__);
	}
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	vertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);
	vertexInfos [vertexIdx] = *userData;

	UIndex contourIdx = GetContourIdxFromInternalVertexIdx (vertexIdx);
	UIndex beginVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
	if (vertexIdx == beginVertexIdx) {
		vertexInfos [GetInternalVertexEndIdxInContour (contourIdx)] = *userData;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeDefaultUserData (const EdgeUserData& userData)
{
	defaultEdgeData = userData;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const EdgeUserData& CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeDefaultUserData (void) const
{
	return (defaultEdgeData);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetArcAngle (UIndex edgeIdx) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	if (nArcs == 0)
		return 0.0;
	for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
		if (arcs[arcIdx].begIndex == edgeIdx)
			return arcs[arcIdx].arcAngle;
	}
	return 0.0;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeLength (UIndex edgeIdx) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	UIndex arcInd = GetInternalArcIdx (edgeIdx);
	if (arcInd > 0) {
		Point2D origo;
		if (ArcGetOrigo (&vertices[edgeIdx], &vertices[edgeIdx + 1], arcs[arcInd].arcAngle, &origo))
			return fabs (arcs[arcInd].arcAngle * Dist (origo, vertices[edgeIdx]));
	}

	return Dist (vertices[edgeIdx], vertices[edgeIdx + 1]);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSector (UIndex edgeIdx, Sector& sect, GenArc& genArc) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);

	sect.c1 = vertices[edgeIdx];
	UIndex vertexIdx = 0;
	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);
		if (endVertexIdx - 1 == edgeIdx)
			vertexIdx = (begVertexIdx);
		if (edgeIdx < endVertexIdx)
			vertexIdx = (edgeIdx + 1);
	}
	sect.c2 = vertices[vertexIdx];

	double angle = 0.0;
	if (nArcs != 0) {
		for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
			if (arcs[arcIdx].begIndex == edgeIdx)
				angle = arcs[arcIdx].arcAngle;
		}
	} else {
		genArc = GenArc ();	// safety	// TODO genArc.Clear () vagy genArc.SetToDefault () ???
		return false;
	}

	if (fabs (angle) <= RadEps) {
		genArc = GenArc ();	// safety
		return false;
	} else {
		Geometry::SetGenArcPtr (&genArc, sect.c1, sect.c2, angle);
		return true;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSector (UIndex edgeIdx, Point2D& begC, Point2D& endC, double& angle) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);

	begC = vertices[edgeIdx];
	UIndex vertexIdx = 0;
	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);
		if (endVertexIdx - 1 == edgeIdx)
			vertexIdx = (begVertexIdx);
		if (edgeIdx < endVertexIdx)
			vertexIdx = (edgeIdx + 1);
	}
	endC = vertices[vertexIdx];

	angle = 0.0;

	if (nArcs == 0) {
		angle = 0;		// safety
		return false;
	} else {
		for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
			if (arcs[arcIdx].begIndex == edgeIdx)
				angle = arcs[arcIdx].arcAngle;
		}
	}

	if (fabs (angle) <= RadEps) {
		return false;
	} else {
		return true;
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Optional<Sector>	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSector (UIndex edgeIdx) const
{
	Sector sector;
	GenArc arc;
	if (GetSector (edgeIdx, sector, arc))
		return GS::NoValue;

	return sector;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Optional<GenArc>	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetArc (UIndex edgeIdx) const
{
	Sector sector;
	GenArc arc;
	if (!GetSector (edgeIdx, sector, arc))
		return GS::NoValue;

	return arc;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const EdgeUserData* CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeUserData (UIndex edgeIdx) const
{
	if (inhEdgeInfos.GetSize() == 0 || !flags.isEdgeUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolygon2D::GetEdgeUserData", __FILE__, __LINE__);
	}
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	return &(inhEdgeInfos [edgeIdx]);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetContourDefaultUserData (const ContourUserData& userData)
{
	defaultContourData = userData;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const ContourUserData& CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourDefaultUserData (void) const
{
	return (defaultContourData);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeUserData (UIndex edgeIdx, const EdgeUserData* userData)
{
	if (inhEdgeInfos.GetSize() == 0 || !flags.isEdgeUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolygon2D::SetEdgeUserData", __FILE__, __LINE__);
	}
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	inhEdgeInfos [edgeIdx] = *userData;

	UIndex contourIdx = GetContourIdxFromInternalVertexIdx (edgeIdx);
	UIndex beginVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
	if (edgeIdx == beginVertexIdx) {
		inhEdgeInfos [GetInternalVertexEndIdxInContour (contourIdx)] = *userData;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexBeginIdxInContour (UIndex contourIdx) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	return InternalVertexIdx2VertexIdx (GetInternalVertexBeginIdxInContour (contourIdx));
}

//A contour-hoz mar nem tartozo vertex indexet adja vissza
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexEndIdxInContour (UIndex contourIdx) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	return InternalVertexIdx2VertexIdx (GetInternalVertexEndIdxInContour (contourIdx) - 1) + 1;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeBeginIdxInContour (UIndex contourIdx) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	return InternalVertexIdx2VertexIdx (GetInternalVertexBeginIdxInContour (contourIdx));
}

//A contour-hoz mar nem tartozo edge indexet adja vissza
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeEndIdxInContour (UIndex contourIdx) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	return InternalVertexIdx2VertexIdx (GetInternalVertexEndIdxInContour (contourIdx) - 1) + 1;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const ContourUserData* CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourUserData (UIndex contourIdx) const
{
	if (contourInfos.GetSize() == 0 || !flags.isContourUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolygon2D::GetContourUserData", __FILE__, __LINE__);
	}
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	return &(contourInfos [contourIdx]);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetContourUserData (UIndex contourIdx, const ContourUserData* userData)
{
	if (contourInfos.GetSize() == 0 || !flags.isContourUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolygon2D::SetContourUserData", __FILE__, __LINE__);
	}
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	contourInfos [contourIdx] = *userData;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetNextVertexIndex (UIndex vertexIdx, const VertexUserData* ud) const
{
	//Itt vegig external vertex idx-et hasznalunk
	DBCHECKINDEX_COREPOLY(vertexIdx, 0, GetVertexNum ());
	vertexIdx++;
	while (vertexIdx <= GetVertexNum()) {
		if (*(GetVertexUserData (vertexIdx)) == *ud)
			return vertexIdx;
		vertexIdx++;
	}
	return vertexIdx;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPrevVertexIndex (UIndex vertexIdx, const VertexUserData* ud) const
{
	//Itt vegig external vertex idx-et hasznalunk
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum () + 1);
	vertexIdx--;
	while (vertexIdx > 0) {
		if (*(GetVertexUserData (vertexIdx)) == *ud)
			return vertexIdx;
		vertexIdx--;
	}
	return vertexIdx;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetNextEdgeIndex (UIndex edgeIdx, const EdgeUserData* ud) const
{
	//Itt vegig external vertex idx-et hasznalunk
	DBCHECKINDEX_COREPOLY(edgeIdx, 0, GetEdgeNum ());
	edgeIdx++;
	while (edgeIdx <= GetEdgeNum()) {
		if (*(GetEdgeUserData (edgeIdx)) == *ud)
			return edgeIdx;
		edgeIdx++;
	}
	return edgeIdx;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPrevEdgeIndex (UIndex edgeIdx, const EdgeUserData* ud) const
{
	//Itt vegig external vertex idx-et hasznalunk
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum () + 1);
	edgeIdx--;
	while (edgeIdx > 0) {
		if (*(GetEdgeUserData (edgeIdx)) == *ud)
			return edgeIdx;
		edgeIdx--;
	}
	return edgeIdx;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetNextContourIndex (UIndex contourIdx, const ContourUserData* ud) const
{
	//Itt vegig external vertex idx-et hasznalunk
	DBCHECKINDEX_COREPOLY(contourIdx, 0, GetContourNum ());
	contourIdx++;
	while (contourIdx <= GetContourNum()) {
		if (*(GetContourUserData (contourIdx)) == *ud)
			return contourIdx;
		contourIdx++;
	}
	return contourIdx;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPrevContourIndex (UIndex contourIdx, const ContourUserData* ud) const
{
	//Itt vegig external vertex idx-et hasznalunk
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum () + 1);
	contourIdx--;
	while (contourIdx > 0) {
		if (*(GetContourUserData (contourIdx)) == *ud)
			return contourIdx;
		contourIdx--;
	}
	return contourIdx;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetBeginVertexIdxOfEdge (UIndex edgeIdx) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
#ifdef CHECKED_VERSION
	UIndex internalEdgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	DBASSERT (InternalVertexIdx2VertexIdx (internalEdgeIdx) == edgeIdx);
#endif
	return edgeIdx;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEndVertexIdxOfEdge (UIndex edgeIdx) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);
		if (endVertexIdx - 1 == edgeIdx)
			return InternalVertexIdx2VertexIdx (begVertexIdx);
		if (edgeIdx < endVertexIdx)
			return InternalVertexIdx2VertexIdx (edgeIdx + 1);
		if (edgeIdx == endVertexIdx) {
			DBBREAK ();
			return InternalVertexIdx2VertexIdx (endVertexIdx);
		}
	}
	DBBREAK ();
	return InternalVertexIdx2VertexIdx (nVertices);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPrevEdgeIdxOfVertex (UIndex vertexIdx) const
{
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	vertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);
	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);
		if (begVertexIdx == vertexIdx)
			return InternalVertexIdx2VertexIdx (endVertexIdx - 1);
		DBASSERT (vertexIdx != endVertexIdx);
		if (vertexIdx <= endVertexIdx)
			return InternalVertexIdx2VertexIdx (vertexIdx - 1);
	}
	DBBREAK ();
	return InternalVertexIdx2VertexIdx (nVertices);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
UIndex CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetNextEdgeIdxOfVertex (UIndex vertexIdx) const
{
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
#ifdef CHECKED_VERSION
	UIndex internalVertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);
	DBASSERT (InternalVertexIdx2VertexIdx (internalVertexIdx) == vertexIdx);
#endif
	return vertexIdx;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Clear (void)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	FreeInternalData ();
	InitInternalData ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsABox (void) const
{
	if (nContours != 1 || nArcs > 0 || nVertices != 5)
		return false;

	if (fabs (vertices[1].x - vertices[2].x) > EPS) {		// different in x
		if (fabs (vertices[1].y - vertices[2].y) > EPS || fabs (vertices[3].y - vertices[4].y) > EPS) {
			return false;
		} else if (fabs (vertices[1].x - vertices[4].x) > EPS || fabs (vertices[2].x - vertices[3].x) > EPS) {
			return false;
		} else {
			return true;
		}
	} else {		// not different in x
		if (fabs (vertices[3].x - vertices[4].x) > EPS) {
			return false;
		} else if (fabs (vertices[1].y - vertices[4].y) > EPS || fabs (vertices[2].y - vertices[3].y) > EPS) {
			return false;
		} else {
			return true;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsACircle (Circle2D& circ) const
{
	if (nContours != 1)
		return false;
	if (GetInternalArcIdx (1) != 0) {
		const double arcAngle = arcs[GetInternalArcIdx (1)].arcAngle;
		const Point2D& c    = vertices[1];
		const Point2D& next = vertices[2];
		Point2D origo;
		ArcGetOrigo (&c, &next, arcAngle, &origo);
		circ.SetOrigo (origo);
		circ.SetRadius (Dist (c, origo));
	} else
		return false;

	for (GS::UInt32 i = 2; i < contourEnds[1]; i++) {
		if (GetInternalArcIdx (i) != 0) {
			const double arcAngle = arcs[GetInternalArcIdx (i)].arcAngle;
			const Point2D& c    = vertices[i];
			const Point2D& next = vertices[i + 1];
			Point2D actArcOrigo;
			ArcGetOrigo (&c, &next, arcAngle, &actArcOrigo);
			if (Dist (actArcOrigo, circ.Origo ()) > Eps)
				return false;
		} else
			return false;
	}
	return true;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveSmallArcs (void)
{
	for (Int32 arcIdx = nArcs; arcIdx > 0; --arcIdx) {
		if (fabs (arcs[arcIdx].arcAngle) < RadEps || !CanCalculateArcOrigo (arcIdx)) {
			arcs.Delete (arcIdx);
			--nArcs;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Read (GS::IChannel& ic)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, CorePolygon2DPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	GSErrCode err = NoError;
	switch (frame.GetMainVersion ()) {
		case 1:			err = ReadVersion1Full (ic, frame); break;
		case 2:			err = ReadVersion2Full (ic, frame); break;
		default:
			DBPRINTF ("Unsupported CorePolygon2D class version.");
			err = Error;
			break;
	}

	RemoveSmallArcs ();

	DBASSERT_GUID (Check (PolyCheckFlags_All_Polygon, nullptr, MaxCoordValue ()), "{6A2BCE65-324D-41F3-AB1C-48ACC52EA612}");

	return err;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadVersion1 (GS::IChannel& ic)
{
	GSErrCode errorCode = NoError;

	USize			verticesNum = 0;
	USize			arcsNum = 0;
	USize			contoursNum = 0;
	USize			newUserDataSize = 0;
	if (errorCode == NoError)
		errorCode = ic.Read (newUserDataSize);

	if (DBERROR (newUserDataSize != 0 && newUserDataSize != sizeof (PolyId)))
		throw GeometryException ();
	if (errorCode == NoError)
		errorCode = ic.ReadBin (reinterpret_cast<char*> (&status), sizeof (status));
	if (errorCode == NoError)
		errorCode = ic.ReadBin (reinterpret_cast<char*> (&flags), sizeof (flags));
	if (errorCode == NoError)
		errorCode = ic.Read (boundBox);
	if (errorCode == NoError)
		errorCode = ic.Read (verticesNum);
	if (errorCode == NoError)
		errorCode = ic.Read (arcsNum);
	if (errorCode == NoError)
		errorCode = ic.Read (contoursNum);

	if (verticesNum != 0 || arcsNum != 0 || contoursNum != 0) {
		AllocateInternalData (verticesNum, arcsNum, contoursNum);

		if (nVertices != 0 && errorCode == NoError) {
			errorCode = ic.ReadBin (reinterpret_cast<char*> (vertices.GetContent ()), (nVertices + 1) * sizeof (Point2D));
		}

		if (nArcs != 0 && errorCode == NoError) {
			errorCode = ic.ReadBin (reinterpret_cast<char*> (arcs.GetContent ()), (nArcs + 1) * sizeof (PolyArcRec));
		}

		if (nContours != 0 && errorCode == NoError) {
			errorCode = ic.ReadBin (reinterpret_cast<char*> (contourEnds.GetContent ()), (nContours + 1) * sizeof (UIndex));
		}

		if (newUserDataSize != 0) {
			if (errorCode == NoError)
				errorCode = ReadVersion1UserData (ic);
		}
	} else {
		Clear ();
	}

	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadVersion1UserData (GS::IChannel& ic)
{
	GSErrCode errorCode = NoError;
	if (nVertices != 0 && flags.isVertexUserData && errorCode == NoError) {
		errorCode = ic.ReadBin (reinterpret_cast<char*> (vertexInfos.GetContent ()), (nVertices + 1) * sizeof (PolyId));
	}
	if (nVertices != 0 && flags.isEdgeUserData && errorCode == NoError) {
		errorCode = ic.ReadBin (reinterpret_cast<char*> (inhEdgeInfos.GetContent ()), (nVertices + 1) * sizeof (PolyId));
	}
	if (nContours != 0 && flags.isContourUserData && errorCode == NoError) {
		errorCode = ic.ReadBin (reinterpret_cast<char*> (contourInfos.GetContent ()), (nContours + 1) * sizeof (PolyId));
	}
	if (flags.isPolygonUserData && errorCode == NoError) {
		errorCode = ic.ReadBin (reinterpret_cast<char*> (inhPolygonInfo.GetContent ()), 1 * sizeof (PolyId));
	}
	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadVersion1Full (GS::IChannel& ic, const GS::InputFrame& /*frame*/)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	NULL_REF_CHECK (ic);

	Clear ();

#pragma warning (disable : 4127)		// conditional expression is constant
	//	do not change to static_assert or CTASSERT, SymbBinCache won't compile
	if (DBERROR (sizeof (VertexUserData)	!= sizeof (PolyId) ||
				 sizeof (EdgeUserData)		!= sizeof (PolyId) ||
				 sizeof (ContourUserData)	!= sizeof (PolyId) ||
				 sizeof (PolygonUserData)	!= sizeof (PolyId)
				 )) {
		return Error;
	}
#pragma warning (default : 4127)


	GSErrCode errorCode = NoError;
	try {
	    errorCode = ReadVersion1 (ic);
	} catch (const GS::GSException& e) {
		FreeInternalData ();
		return e.GetErrCode ();
	}

	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame)
{
	GSErrCode errorCode = NoError;

	USize			verticesNum = 0;
	USize			arcsNum = 0;
	USize			contoursNum = 0;
	if (errorCode == NoError)
		errorCode = ic.ReadBin (reinterpret_cast<char*> (&status), sizeof (status));
	if (errorCode == NoError)
		errorCode = ic.ReadBin (reinterpret_cast<char*> (&flags), sizeof (flags));
	if (errorCode == NoError)
		errorCode = ic.Read (boundBox);
	if (errorCode == NoError)
		errorCode = ic.Read (verticesNum);
	if (errorCode == NoError)
		errorCode = ic.Read (arcsNum);
	if (errorCode == NoError)
		errorCode = ic.Read (contoursNum);

	if (verticesNum != 0 || arcsNum != 0 || contoursNum != 0) {
		AllocateInternalData (verticesNum, arcsNum, contoursNum);

		if (nVertices != 0 && errorCode == NoError) {
			errorCode = ic.ReadBin (reinterpret_cast<char*> (vertices.GetContent ()), (nVertices + 1) * sizeof (Point2D));
		}

		if (nArcs != 0 && errorCode == NoError) {
			errorCode = ic.ReadBin (reinterpret_cast<char*> (arcs.GetContent ()), (nArcs + 1) * sizeof (PolyArcRec));
		}

		if (nContours != 0 && errorCode == NoError) {
			errorCode = ic.ReadBin (reinterpret_cast<char*> (contourEnds.GetContent ()), (nContours + 1) * sizeof (UIndex));
		}

		if (errorCode == NoError)
			errorCode = ReadVersion2UserData (ic);
	} else {
		Clear ();
	}

	if (frame.GetSubVersion () > 0) {
		if (errorCode == NoError)
			errorCode = defaultVertexData.Read (ic);
		if (errorCode == NoError)
			errorCode = defaultEdgeData.Read (ic);
		if (errorCode == NoError)
			errorCode = defaultContourData.Read (ic);
	}

	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadVersion2UserData (GS::IChannel& ic)
{
	GSErrCode errorCode = NoError;
	if (nVertices != 0 && flags.isVertexUserData && errorCode == NoError) {
		errorCode = vertexInfos.Read (ic);
	}
	if (nVertices != 0 && flags.isEdgeUserData && errorCode == NoError) {
		errorCode = inhEdgeInfos.Read (ic);
	}
	if (nVertices != 0 && flags.isContourUserData && errorCode == NoError) {
		errorCode = contourInfos.Read (ic);
	}
	if (nVertices != 0 && flags.isPolygonUserData && errorCode == NoError) {
		errorCode = inhPolygonInfo.Read (ic);
	}
	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadVersion2Full (GS::IChannel& ic, const GS::InputFrame& frame)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;
	NULL_REF_CHECK (ic);

	GSErrCode errorCode = NoError;
	try {
		errorCode = ReadVersion2 (ic, frame);
	} catch (const GS::GSException& e) {
		FreeInternalData ();
		return e.GetErrCode ();
	}

	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Write (GS::OChannel& oc) const
{
	DBCHECKCOREPOLY_CHECK;
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, CorePolygon2DPrivate::classInfo);

	GSErrCode err = NoError;
	switch (frame.GetMainVersion ()) {
		case 1:			err = WriteVersion1Full (oc, frame); break;
		case 2:			err = WriteVersion2Full (oc, frame); break;
		default:
			DBPRINTF ("Unsupported CorePolygon2D class version.");
			err = Error;
			break;
	}

	return err;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteVersion1 (GS::OChannel& oc) const
{
	GSErrCode errorCode = NoError;
	USize userDataSize = sizeof (PolyId);
	if (errorCode == NoError)
		errorCode = oc.Write (userDataSize);
	if (errorCode == NoError)
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (&status), sizeof (status));
	if (errorCode == NoError)
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (&flags), sizeof (flags));
	if (errorCode == NoError)
		errorCode = oc.Write (boundBox);
	if (errorCode == NoError)
		errorCode = oc.Write (nVertices);
	if (errorCode == NoError)
		errorCode = oc.Write (nArcs);
	if (errorCode == NoError)
		errorCode = oc.Write (nContours);

	if (nVertices != 0 || nArcs != 0 || nContours != 0) {
		if (nVertices != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (vertices.GetContent ()), (nVertices + 1) * sizeof (Point2D));
		}

		if (nArcs != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (arcs.GetContent ()), (nArcs + 1) * sizeof (PolyArcRec));
		}

		if (nContours != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (contourEnds.GetContent ()), (nContours + 1) * sizeof (UIndex));
		}

		if (errorCode == NoError)
			errorCode = WriteVersion1UserData (oc);
	}

	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteVersion1UserData (GS::OChannel& oc) const
{
	GSErrCode errorCode = NoError;
	if (vertexInfos.GetSize() != 0 && flags.isVertexUserData && nVertices != 0 && errorCode == NoError) {
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (vertexInfos.GetContent ()), (nVertices + 1) * sizeof (PolyId));
	}

	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData && nVertices != 0 && errorCode == NoError) {
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (inhEdgeInfos.GetContent ()), (nVertices + 1) * sizeof (PolyId));
	}

	if (contourInfos.GetSize() != 0 && flags.isContourUserData && nVertices != 0 && errorCode == NoError) {
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (contourInfos.GetContent ()), (nContours + 1) * sizeof (PolyId));
	}

	if (inhPolygonInfo.GetSize() != 0 && flags.isPolygonUserData && errorCode == NoError) {
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (inhPolygonInfo.GetContent ()), 1 * sizeof (PolyId));
	}
	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteVersion1Full (GS::OChannel& oc, const GS::OutputFrame& /*frame*/) const
{
	NULL_REF_CHECK (oc);
	DBCHECKCOREPOLY_CHECK;

#pragma warning (disable : 4127)		// conditional expression is constant
	//	do not change to static_assert or CTASSERT, SymbBinCache won't compile
	if (DBERROR (sizeof (VertexUserData)	!= sizeof (PolyId) ||
				 sizeof (EdgeUserData)		!= sizeof (PolyId) ||
				 sizeof (ContourUserData)	!= sizeof (PolyId) ||
				 sizeof (PolygonUserData)	!= sizeof (PolyId)
				 )) {
		return Error;
	}
#pragma warning (default : 4127)

	return WriteVersion1 (oc);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const
{
	GSErrCode errorCode = NoError;
	if (errorCode == NoError)
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (&status), sizeof (status));
	if (errorCode == NoError)
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (&flags), sizeof (flags));
	if (errorCode == NoError)
		errorCode = oc.Write (boundBox);
	if (errorCode == NoError)
		errorCode = oc.Write (nVertices);
	if (errorCode == NoError)
		errorCode = oc.Write (nArcs);
	if (errorCode == NoError)
		errorCode = oc.Write (nContours);

	if (nVertices != 0 || nArcs != 0 || nContours != 0) {
		if (nVertices != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (vertices.GetContent ()), (nVertices + 1) * sizeof (Point2D));
		}

		if (nArcs != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (arcs.GetContent ()), (nArcs + 1) * sizeof (PolyArcRec));
		}

		if (nContours != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (contourEnds.GetContent ()), (nContours + 1) * sizeof (UIndex));
		}

		if (errorCode == NoError)
			errorCode = WriteVersion2UserData (oc);
	}

	if (frame.GetSubVersion () > 0) {
		if (errorCode == NoError)
			errorCode = defaultVertexData.Write (oc);
		if (errorCode == NoError)
			errorCode = defaultEdgeData.Write (oc);
		if (errorCode == NoError)
			errorCode = defaultContourData.Write (oc);
	}

	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteVersion2UserData (GS::OChannel& oc) const
{
	GSErrCode errorCode = NoError;
	if (vertexInfos.GetSize() != 0 && flags.isVertexUserData && nVertices != 0 && errorCode == NoError) {
		errorCode = vertexInfos.Write (oc);
	}

	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData && nVertices != 0 && errorCode == NoError) {
		errorCode = inhEdgeInfos.Write (oc);
	}

	if (contourInfos.GetSize() != 0 && flags.isContourUserData && nContours != 0 && errorCode == NoError) {
		errorCode = contourInfos.Write (oc);
	}

	if (inhPolygonInfo.GetSize() != 0 && flags.isPolygonUserData && nVertices != 0 && errorCode == NoError) {
		errorCode = inhPolygonInfo.Write (oc);
	}
	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteVersion2Full (GS::OChannel& oc, const GS::OutputFrame& frame) const
{
	NULL_REF_CHECK (oc);
	DBCHECKCOREPOLY_CHECK;

	return WriteVersion2 (oc, frame);
}


extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_CorePolygon2D;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_IsSameDirEdgeLegal;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_Force64BitPrecision;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_IsVertexUserData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_IsEdgeUserData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_IsContourUserData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_IsPolygonUserData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_DefaultData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Attr_xMin;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Attr_yMin;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Attr_xMax;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Attr_yMax;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_Contours;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Attr_ContoursNum;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_Contour;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_Segments;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Attr_SegmentsNum;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_Segment;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_Vertex;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_CoordX;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_CoordY;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_Edge;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_ArcAngle;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_PolyId;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_DefaultVertexData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_DefaultEdgeData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Tag_DefaultContourData;

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadXMLCreateContourDesc	(GS::XMLIChannel& ic, GS::XMLITag& tagCorePolygon2D, Flags actFlags, USize GS_DEBUG_ONLY (contoursNum), GS::Array<CustomPolyContourDescription<VertexUserData, EdgeUserData, ContourUserData> >& polyContourDescArray)
{
	GSErrCode errCode = NoError;
	Point2D coord (0.0, 0.0);
	double arcAngle = 0.0;
	CustomPolySegment<VertexUserData, EdgeUserData> polySegment;

	GS::UniString tokenName;
	while (tagCorePolygon2D.IsNextChildStartTag (tokenName) && (errCode == NoError)) {
#ifdef CHECKED_VERSION
		contoursNum--;
#endif
		//Begin Contour
		CustomPolyContourDescription<VertexUserData, EdgeUserData, ContourUserData> polyContourDesc;

		GS::XMLITag tagContour (ic, XMLCore_Tag_Contour);
		if (actFlags.isContourUserData) {
			if (errCode == NoError) {
				ContourUserData tmpPolyid;
				errCode = GS::ReadXML (ic, XMLCore_Tag_PolyId ,tmpPolyid);
				polyContourDesc.SetPolyContourUserData (tmpPolyid);
			}
		}

		{ // Begin Segments
			GS::XMLITag tagSegments (ic, XMLCore_Tag_Segments);

			while (tagSegments.IsNextChildStartTag (tokenName) && (errCode == NoError)) {

				//Begin Segment
				GS::XMLITag tagSegment (ic, XMLCore_Tag_Segment);
				{ //Begin Vertex
					GS::XMLITag tagVertex (ic, XMLCore_Tag_Vertex);
					if (errCode == NoError)
						errCode = ic.ReadXML (XMLCore_Tag_CoordX, coord.x);
					if (errCode == NoError)
						errCode = ic.ReadXML (XMLCore_Tag_CoordY, coord.y);
					if (actFlags.isVertexUserData) {
						if (errCode == NoError) {
							VertexUserData tmpPolyid;
							errCode = GS::ReadXML (ic, XMLCore_Tag_PolyId ,tmpPolyid);
							polySegment.GetVertexRef ().SetPolyVertexUserData (tmpPolyid);
						}
					}
				} //End Vertex
				{ //Begin Edge
					GS::XMLITag tagEdge (ic, XMLCore_Tag_Edge);
					if (errCode == NoError)
						errCode = ic.ReadXML (XMLCore_Tag_ArcAngle, arcAngle);

					if (actFlags.isEdgeUserData) {
						if (errCode == NoError) {
							EdgeUserData tmpPolyid;
							errCode = GS::ReadXML (ic, XMLCore_Tag_PolyId ,tmpPolyid);
							polySegment.GetEdgeRef ().SetPolyEdgeUserData (tmpPolyid);
						}
					}
				} //End Edge
				if (errCode == NoError) {
					polySegment.GetVertexRef ().SetCoord (coord);
					polySegment.GetEdgeRef ().SetArcAngle (arcAngle);

					polyContourDesc.GetSegmentListRef ().Push (polySegment);
				}
				//EndSegment
			}
			GS::UniString name;
			ic.GetNextTokenTypeName(name);
			DBASSERT_STR (name != XMLCore_Tag_Segment, "Segment not read");
		} //End Segments
		polyContourDescArray.Push (polyContourDesc);
		//End Contour
	}
	DBASSERT (contoursNum == 0);
	return errCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadXMLAndCreate	(GS::XMLIChannel& ic)
{
	GSErrCode errCode = NoError;
	GS::XMLITag tagCorePolygon2D (ic, XMLCore_Tag_CorePolygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		GS::ClassVersion currentClassVersion;
		ic.ReadXMLVersionAttr (currentClassVersion);
		//currentClassVersion.ReadXML (ic);
		DBASSERT (currentClassVersion == CorePolygon2DPrivate::classInfo.GetVersion ());
	}

	double	xMin = 0.0;
	double	yMin = 0.0;
	double	xMax = 0.0;
	double	yMax = 0.0;
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLCore_Attr_xMin, xMin);
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLCore_Attr_yMin, yMin);
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLCore_Attr_xMax, xMax);
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLCore_Attr_yMax, yMax);

	GS::ArrayFB<CustomPolyContourDescription<VertexUserData, EdgeUserData, ContourUserData>, 6 > polyContourDescArray;

	Flags	actFlags;
	bool tmpFlag	= true;
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Tag_IsSameDirEdgeLegal, tmpFlag);
		actFlags.isSameDirEdgeLegal = tmpFlag;
	}
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Tag_Force64BitPrecision, tmpFlag);
		actFlags.force64BitPrecision = tmpFlag;
	}
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Tag_IsVertexUserData, tmpFlag);
		actFlags.isVertexUserData = tmpFlag;
	}
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Tag_IsEdgeUserData, tmpFlag);
		actFlags.isEdgeUserData = tmpFlag;
	}
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Tag_IsContourUserData, tmpFlag);
		actFlags.isContourUserData = tmpFlag;
	}
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Tag_IsPolygonUserData, tmpFlag);
		actFlags.isPolygonUserData = tmpFlag;
	}

	VertexUserData	inputDefaultVertexData;
	EdgeUserData	inputDefaultEdgeData;
	ContourUserData	inputDefaultContourData;
	bool			hasDefaultData = false;

	if (errCode == NoError)
		errCode = GS::ReadXML (ic, XMLCore_Tag_DefaultVertexData, inputDefaultVertexData);
	if (errCode == NoError)
		errCode = GS::ReadXML (ic, XMLCore_Tag_DefaultEdgeData, inputDefaultEdgeData);
	if (errCode == NoError)
		errCode = GS::ReadXML (ic, XMLCore_Tag_DefaultContourData, inputDefaultContourData);
	hasDefaultData = errCode == NoError;

	PolygonUserData polyId;
	if (actFlags.isPolygonUserData) {
		if (errCode == NoError) {
			errCode = GS::ReadXML (ic, XMLCore_Tag_PolyId ,polyId);
		}
	}

	if (errCode == NoError) { //Begin Contours
		GS::XMLITag tagContours (ic, XMLCore_Tag_Contours);
		USize			contoursNum = 0;
		if (errCode == NoError)
			errCode = ic.ReadXMLAttr (XMLCore_Attr_ContoursNum, contoursNum);

		if (contoursNum == 0) { //valid ures polygon
			GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > emptyResult = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (actFlags);
			if (emptyResult->flags.isPolygonUserData && errCode == NoError) {
				emptyResult->SetUserData (&polyId);
			}

			if (hasDefaultData) {
				emptyResult->defaultVertexData	= inputDefaultVertexData;
				emptyResult->defaultEdgeData	= inputDefaultEdgeData;
				emptyResult->defaultContourData = inputDefaultContourData;
			}

			return emptyResult;
		}

		if (errCode == NoError)
			errCode = ReadXMLCreateContourDesc (ic, tagCorePolygon2D, actFlags, contoursNum, polyContourDescArray);
	} //End Contours

	if (errCode != NoError || ic.GetErrorStatus () != GS::XMLIChannel::Ok)
		return nullptr;

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > result = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (actFlags, polyContourDescArray);

	if (hasDefaultData) {
		result->defaultVertexData	= inputDefaultVertexData;
		result->defaultEdgeData		= inputDefaultEdgeData;
		result->defaultContourData	= inputDefaultContourData;
	}

	if (result->flags.isPolygonUserData && errCode == NoError) {
		result->SetUserData (&polyId);
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteXMLContours (GS::XMLOChannel& oc) const
{
	GSErrCode errCode = NoError;
	GS::XMLTag tagContours (oc, XMLCore_Tag_Contours);
	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLCore_Attr_ContoursNum, GetContourNum());
	UIndex vertexIdx;
	UIndex contourIdx;
	for (contourIdx = 1; contourIdx <= GetContourNum() && errCode == NoError; contourIdx++) {
		//Begin Contour
		UIndex begVertexIdx = GetVertexBeginIdxInContour (contourIdx);
		UIndex endVertexIdx = GetVertexEndIdxInContour (contourIdx);

		GS::XMLTag tagContour (oc, XMLCore_Tag_Contour);

		if (flags.isContourUserData) {
			if (errCode == NoError) {
				const ContourUserData* id = GetContourUserData (contourIdx);
				if (id != nullptr)
					errCode = GS::WriteXML (oc, XMLCore_Tag_PolyId, *id);
			}
		}

		{ //Begin Segments
			GS::XMLTag tagSegments (oc, XMLCore_Tag_Segments);

			for(vertexIdx = begVertexIdx; vertexIdx < endVertexIdx && errCode == NoError; vertexIdx++)
			{
				//Begin Segment
				GS::XMLTag tagSegment (oc, XMLCore_Tag_Segment);
				{ //Begin Vertex
					GS::XMLTag tagVertex (oc, XMLCore_Tag_Vertex);
					if (errCode == NoError)
						errCode = oc.WriteXML (XMLCore_Tag_CoordX, GetCoord(vertexIdx).x);
					if (errCode == NoError)
						errCode = oc.WriteXML (XMLCore_Tag_CoordY, GetCoord(vertexIdx).y);
					if (flags.isVertexUserData) {
						if (errCode == NoError) {
							const VertexUserData* id = GetVertexUserData (vertexIdx);
							if (id != nullptr)
								errCode = GS::WriteXML (oc, XMLCore_Tag_PolyId, *id);
						}
					}
				} //End Vertex
				{ //Begin Edge
					GS::XMLTag tagEdge (oc, XMLCore_Tag_Edge);
					if (errCode == NoError)
						errCode = oc.WriteXML (XMLCore_Tag_ArcAngle, GetArcAngle (vertexIdx));

					if (flags.isEdgeUserData) {
						if (errCode == NoError) {
							const EdgeUserData* id = GetEdgeUserData (vertexIdx);
							if (id != nullptr)
								errCode = GS::WriteXML (oc, XMLCore_Tag_PolyId, *id);
						}
					}
				} //End Edge
				//End Segment
			}
		} //End Segments
	} //End Contour
	return errCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteXML (GS::XMLOChannel& oc) const
{
	GSErrCode errCode = NoError;
	GS::XMLTag tagCorePolygon2D (oc, XMLCore_Tag_CorePolygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		oc.WriteXMLVersionAttr (CorePolygon2DPrivate::classInfo.GetVersion ());
		//GetClassVersion ().WriteXML (oc);
	}
	Box2DData box = GetBoundBox ();
	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLCore_Attr_xMin, box.xMin);
	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLCore_Attr_yMin, box.yMin);
	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLCore_Attr_xMax, box.xMax);
	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLCore_Attr_yMax, box.yMax);

	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Tag_IsSameDirEdgeLegal, GetSameDirEdgeLegal ());
	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Tag_Force64BitPrecision, GetForce64BitPrecision ());
	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Tag_IsVertexUserData, GetIsVertexUserData ());
	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Tag_IsEdgeUserData, GetIsEdgeUserData ());
	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Tag_IsContourUserData, GetIsContourUserData ());
	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Tag_IsPolygonUserData, GetIsPolygonUserData ());

	if (errCode == NoError)
		errCode = GS::WriteXML (oc, XMLCore_Tag_DefaultVertexData, defaultVertexData);
	if (errCode == NoError)
		errCode = GS::WriteXML (oc, XMLCore_Tag_DefaultEdgeData, defaultEdgeData);
	if (errCode == NoError)
		errCode = GS::WriteXML (oc, XMLCore_Tag_DefaultContourData, defaultContourData);

	if (flags.isPolygonUserData) {
		if (errCode == NoError) {
			const PolygonUserData* id = GetUserData ();
			if (id != nullptr)
				errCode = GS::WriteXML (oc, XMLCore_Tag_PolyId, *id);
		}
	}

	if (errCode == NoError)
		errCode = WriteXMLContours (oc);

	if (errCode != NoError)
		return errCode;
	return oc.GetErrorStatus () == GS::XMLOChannel::Ok ? NoError : Error;
}

//Calculate
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const Box2DData& CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetBoundBox (void) const
{
	return boundBox;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcArea (void) const
{
	double	area = 0.0;
	UIndex	i;

	for (i = 1 ; i <= nContours; i++)
		area += CalcContourArea (i);

	return area;
}

//regularizalt polygon lyukakra negativ eredmenyt ad
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcContourArea (UIndex contourIdx) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	double		area = 0.0;
	UIndex		arcInd;
	GS::Int32	iVertex;
	Point2D		centre;
	Point2D		begEdge, endEdge;
	GS::Int32	iBegContour;
	GS::Int32	iEndContour;

	if (DBERROR_STR (contourIdx < 1 || contourIdx > nContours, "Error in CorePolygon2D::CalcContourArea parameters ")) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolygon2D::CalcContourArea", __FILE__, __LINE__);
	}

	iBegContour = (contourIdx > 1) ? (contourEnds[contourIdx - 1] + 1) : 1;
	iEndContour = contourEnds[contourIdx];
	area = 0.0;

	for (iVertex = iBegContour + 1; iVertex <= iEndContour; iVertex++) {
		begEdge = vertices [iVertex - 1];
		endEdge = vertices [iVertex];
		area += (endEdge.x + begEdge.x) * (endEdge.y - begEdge.y) * 0.5;

		arcInd = GetInternalArcIdx (iVertex - 1);
		if (arcInd > 0) {
			double	radius, angle;

			angle = arcs [arcInd].arcAngle;
			Geometry::ArcGetOrigo (&begEdge, &endEdge, angle, &centre);
			radius = Geometry::Dist (centre, endEdge);
			area += radius * radius * (angle - sin (angle)) * 0.5;
		}
	}

	begEdge = vertices [iEndContour];
	endEdge = vertices [iBegContour];
	if (!IsEqualCoord (begEdge, endEdge, Eps)) {
		area += (endEdge.x + begEdge.x) * (endEdge.y - begEdge.y) * 0.5;
		area = fabs (area);
		DBBREAK ();
	}

	return area;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::HasPositiveOrientation (UIndex contourIdx) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	if (status.isRegularized)
		return (contourIdx < 2);
	//Onatmetszo esetben (ahol nincs is ertelme koruljarasi iranyrol beszelni) 0 lesz a szamolt terulet, tehat mindenkepp pozitivnak mondja a koruljarast
	return (CalcContourArea (contourIdx) >= 0.0);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcPerimeter (void) const
{
	return CalcContourPerimeter (0);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcPerimeter (UIndex contourIdx) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	return CalcContourPerimeter (contourIdx);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcConvexHull (const ArcDivParams& arcDivParams, GS::Array<Point2D>& convexHull) const
{
	const bool needSegment = nArcs > 0 && arcs.GetSize () > 1;
	ConvexHull2DCreator	convexHullCreator;

	if (needSegment) {
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpPolygon (*this);
		tmpPolygon.SegmentUp (arcDivParams);
		for (UIndex vertexIdx = 1; vertexIdx <= tmpPolygon.nVertices; ++vertexIdx) {
			convexHullCreator.AddPoint (tmpPolygon.vertices[vertexIdx]);
		}
	} else {
		for (UIndex vertexIdx = 1; vertexIdx <= nVertices; ++vertexIdx) {
			convexHullCreator.AddPoint (vertices[vertexIdx]);
		}
	}

	GS::PagedArray<Point3D> convexHull3D = convexHullCreator.CalcConvexHull ();
	convexHull.Clear (true);
	for (UIndex i = 0; i < convexHull3D.GetSize (); ++i) {
		convexHull.Push (Point2D (convexHull3D[i].x, convexHull3D[i].y));
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcMaxVertexFillet (UIndex vertexIdx) const
{
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	vertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);
	double maxFilletRadius;
	GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	UIndex contourIdx = GetContourIdxFromInternalVertexIdx (vertexIdx);
	bool reveresedContour = (contourIdx == 1 && !HasPositiveOrientation (contourIdx)) || (contourIdx > 1 && HasPositiveOrientation (contourIdx));
	if (reveresedContour)
		vertexIdx = contourEnds[contourIdx] + contourEnds[contourIdx - 1] + 1 - vertexIdx;

	errorCode = Geometry::PGPolyGetMaxVertexFilletExt (&polyExt1, vertexIdx, &maxFilletRadius);

	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::CalcMaxVertexFillet", __FILE__, __LINE__);
	return maxFilletRadius;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsCoordOnEdge (const Point2D& c, UIndex& edgeIndex) const
{
	edgeIndex = 0;
	for (UIndex iEdge = 1; iEdge <= GetEdgeNum (); ++iEdge) {
		Sector s;
		GenArc a;
		if (GetSector (iEdge, s, a)) {		// arc
			if (ValidGenArcPointEps (&a, &c, Eps))  {
				edgeIndex = iEdge;
				return true;
			}
		} else {
			if (IsSectorPointIntersect (s, c, Boundary_Closed, Boundary_Closed, Eps)) {
				edgeIndex = iEdge;
				return true;
			}
		}
	}
	return false;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DistanceFromPoint (const Point2D& co) const
{
	if (DBERROR (IsEmpty ()))
		throw GeometryException ("DistanceFromPoint empty polygon", __FILE__, __LINE__);

	double	minDist = 1e9;
	for (UIndex i = 1; i <= GetEdgeNum (); ++i) {
		Sector	s;
		GenArc arc;
		double	d;
		if (!GetSector (i, s, arc)) {
			d = SpecDistPointToSector (co, s);
		} else {
			d = SpecDistPointToArc (co, arc);
		}
		if (d < minDist - Eps) {
			minDist = d;
		}
	}

	return minDist;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Point2D& point, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	RelativePosition position = RelativePosition_Unknown;
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;

	if (IsEmpty ())
		return RelativePosition_Disjunct;

	if (!IsBoxPointIntersect (boundBox, point, boundaries, Eps))
		return RelativePosition_Disjunct;

	GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	PGPositionExt polyPointPos = PGPoint2DPosition (&polyExt1, &point, false);
	switch (polyPointPos) {
		case PGInsidePoly:
			position = RelativePosition_Overlap;
			if (detailed != nullptr)
				*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
			break;
		case PGOutsidePoly: position = RelativePosition_Disjunct;		break;
		case PGOnPolyEdge:
			if (boundaries == Boundary_Closed) {
				position = RelativePosition_Overlap;
				if (detailed != nullptr)
					*detailed = DetailedRelativePosition_Overlap_OnBoundary;
			} else {
				position = RelativePosition_Disjunct;
			}
			break;
	}
	errorCode = NoError;

	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::GetPosition", __FILE__, __LINE__);
	return position;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Box2DData& box, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;

	if (IsEmpty ())
		return RelativePosition_Disjunct;

	if (boundBox.xMin > box.xMax + Eps ||
		boundBox.xMax < box.xMin - Eps ||
		boundBox.yMin > box.yMax + Eps ||
		boundBox.yMax < box.yMin - Eps)
			return RelativePosition_Disjunct;
	if (boundBox.xMin > box.xMin + Eps &&
		boundBox.xMax < box.xMax - Eps &&
		boundBox.yMin > box.yMin + Eps &&
		boundBox.yMax < box.yMax - Eps) {
			if (detailed != nullptr)
				*detailed = DetailedRelativePosition_Overlap_SecondCoversFirst;
			return RelativePosition_Overlap;
	}
	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>				boxPolygon2D (flags, box);
	return GetPosition (boxPolygon2D, boundaries, detailed);

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPositionSmallArea (const Sector& sect, Boundary boundaries) const
{
	if (boundaries != Boundary_Closed)
		return RelativePosition_Disjunct;

	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> polyline (*this, 1);

	bool intersect = false;
	Sector s;
	GenArc arc;
	Point2D tmp;
	Sector tmpSector;
	for (UIndex edgeIdx = 1; edgeIdx <= polyline.GetEdgeNum () && !intersect; ++edgeIdx) {
		if (!polyline.GetSector (edgeIdx, s, arc)) {	// two line segments
			intersect = XSectors (s, sect, boundaries, &tmp);
		} else {
			intersect = XGenArcSectorEps (&arc, &sect, &tmpSector, SmallEps) != 0;
		}
	}
	return (intersect) ? RelativePosition_Overlap : RelativePosition_Disjunct;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPositionNormal (const Sector& sect, Boundary boundaries, DetailedRelativePosition* detailed) const
{
	GS::ArrayFB<Sector, 6> sectInside;
	CutElem (sect, boundaries, sectInside);

	if (boundaries == Boundary_Opened) {
		if (sectInside.GetSize () == 0)
			return RelativePosition_Disjunct;

		if (detailed != nullptr && sectInside.GetSize () == 1) {
			const bool sectorsEqual = ((IsNear (sect.c1.x, sectInside[0].c1.x, EPS) && IsNear (sect.c1.y, sectInside[0].c1.y, EPS) && IsNear (sect.c2.x, sectInside[0].c2.x, EPS) && IsNear (sect.c2.y, sectInside[0].c2.y, EPS)) ||
				(IsNear (sect.c1.x, sectInside[0].c2.x, EPS) && IsNear (sect.c1.y, sectInside[0].c2.y, EPS) && IsNear (sect.c2.x, sectInside[0].c1.x, EPS) && IsNear (sect.c2.y, sectInside[0].c1.y, EPS)));
			if (sectorsEqual)
				*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
		}

		return RelativePosition_Overlap;
	} else {
		if (sectInside.GetSize () == 0) {			// sector still could touch a vertex or an arcular edge
			bool intersect = false;
			Sector s;
			GenArc arc;
			Point2D tmp;
			Sector tmpSector;
			for (UIndex edgeIdx = 1; edgeIdx <= GetEdgeNum () && !intersect; ++edgeIdx) {
				if (!GetSector (edgeIdx, s, arc)) {	// two line segments
					intersect = XSectors (s, sect, boundaries, &tmp);
				} else {
					intersect = XGenArcSectorEps (&arc, &sect, &tmpSector, SmallEps) != 0;
				}
			}

			if (intersect && detailed != nullptr)
				*detailed = DetailedRelativePosition_Overlap_OnBoundary;

			return (intersect) ? RelativePosition_Overlap : RelativePosition_Disjunct;
		}

		if (detailed != nullptr) {
			if (sectInside.GetSize () == 1) {
				const bool sectorsEqual = ((IsNear (sect.c1.x, sectInside[0].c1.x, EPS) && IsNear (sect.c1.y, sectInside[0].c1.y, EPS) && IsNear (sect.c2.x, sectInside[0].c2.x, EPS) && IsNear (sect.c2.y, sectInside[0].c2.y, EPS)) ||
					(IsNear (sect.c1.x, sectInside[0].c2.x, EPS) && IsNear (sect.c1.y, sectInside[0].c2.y, EPS) && IsNear (sect.c2.x, sectInside[0].c1.x, EPS) && IsNear (sect.c2.y, sectInside[0].c1.y, EPS)));
				if (sectorsEqual) {
					*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;

					DetailedRelativePosition begRelDetailedPos;
					RelativePosition begRelPos = GetPosition (sect.c1, boundaries, &begRelDetailedPos);
					DetailedRelativePosition endRelDetailedPos;
					RelativePosition endRelPos = GetPosition (sect.c2, boundaries, &endRelDetailedPos);
					if (IsOverlap (begRelPos) && begRelDetailedPos == DetailedRelativePosition_Overlap_OnBoundary &&
						IsOverlap (endRelPos) && endRelDetailedPos == DetailedRelativePosition_Overlap_OnBoundary)
					{
						Point2D mid = MidPoint (sect.c1, sect.c2);
						DetailedRelativePosition midRelDetailedPos;
						GetPosition (mid, boundaries, &midRelDetailedPos);
						if (midRelDetailedPos == DetailedRelativePosition_Overlap_OnBoundary)
							*detailed = DetailedRelativePosition_Overlap_OnBoundary;
					}
					return RelativePosition_Overlap;
				}
			}

			bool onBoundary = true;
			Sector edge;
			GenArc arc;
			Point2D tmp[2];
			for (UIndex sectorIndex = 0; sectorIndex < sectInside.GetSize () && onBoundary; ++sectorIndex) {
				const Sector& actSect = sectInside[sectorIndex];
				bool found = false;
				for (UIndex edgeIdx = 1; edgeIdx <= GetEdgeNum () && !found; ++edgeIdx) {
					if (!GetSector (edgeIdx, edge, arc))
						found = XSectorsOverLap (&actSect, &edge, tmp) == 2;
				}
				onBoundary = found;
			}

			if (onBoundary)
				*detailed = DetailedRelativePosition_Overlap_OnBoundary;

		}
		return RelativePosition_Overlap;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Sector& sect, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;

	if (IsEmpty ())
		return RelativePosition_Disjunct;

	Box2DData sectBounds = Geometry::SectorBox (&sect);
	const Box2DData& tmpBoundBox = GetBoundBox ();

	if (sectBounds.xMax < tmpBoundBox.xMin - EPS ||
		sectBounds.xMin > tmpBoundBox.xMax + EPS ||
		sectBounds.yMax < tmpBoundBox.yMin - EPS ||
		sectBounds.yMin > tmpBoundBox.yMax + EPS) {
			return RelativePosition_Disjunct;
	}

	if (fabs (CalcArea ()) < Eps) {
		return GetPositionSmallArea (sect, boundaries);
	} else {
		return GetPositionNormal (sect, boundaries, detailed);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPositionSmallArea (const GenArc& arc, Boundary boundaries) const
{
	if (boundaries != Boundary_Closed)
		return RelativePosition_Disjunct;

	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> polyline (*this, 1);

	bool intersect = false;
	Sector s;
	GenArc arcOfPolyline;
	Point2D tmp;
	Sector tmpSector;
	for (UIndex edgeIdx = 1; edgeIdx <= polyline.GetEdgeNum () && !intersect; ++edgeIdx) {
		if (polyline.GetSector (edgeIdx, s, arcOfPolyline)) {	// two arcs
			Point2D c[4];
			intersect = (XGenArcs (&arc, &arcOfPolyline, c) > 0);
		} else {
			intersect = XGenArcSectorEps (&arc, &s, &tmpSector, SmallEps) != 0;
		}
	}
	return (intersect) ? RelativePosition_Overlap : RelativePosition_Disjunct;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPositionNormal (const GenArc& arc, Boundary boundaries, DetailedRelativePosition* detailed) const
{
	DetailedRelativePosition begRelDetailedPos;
	RelativePosition begRelPos = GetPosition (arc.GetBegC (), boundaries, &begRelDetailedPos);
	DetailedRelativePosition endRelDetailedPos;
	RelativePosition endRelPos = GetPosition (arc.GetEndC (), boundaries, &endRelDetailedPos);

	GS::ArrayFB<GenArc, 6> arcInside;
	CutElem (arc, boundaries, arcInside);
	if (IsOverlap (begRelPos) && begRelDetailedPos == DetailedRelativePosition_Overlap_OnBoundary &&
		IsOverlap (endRelPos) && endRelDetailedPos == DetailedRelativePosition_Overlap_OnBoundary &&
		arcInside.GetSize () == 1) {

			if ((IsNear (arc.GetBegC ().x, arcInside[0].GetBegC ().x, EPS) && IsNear (arc.GetBegC ().y, arcInside[0].GetBegC ().y, EPS) && IsNear (arc.GetEndC ().x, arcInside[0].GetEndC ().x, EPS) && IsNear (arc.GetEndC ().y, arcInside[0].GetEndC ().y, EPS)) ||
				(IsNear (arc.GetBegC ().x, arcInside[0].GetEndC ().x, EPS) && IsNear (arc.GetBegC ().y, arcInside[0].GetEndC ().y, EPS) && IsNear (arc.GetEndC ().x, arcInside[0].GetBegC ().x, EPS) && IsNear (arc.GetEndC ().y, arcInside[0].GetBegC ().y, EPS))) {
					Point2D mid;
					Geometry::ComputeEllipseCoord (&arc, arc.GetBegAng () + arc.GetArcAngle () / 2, &mid);
					DetailedRelativePosition relDetailedPos;
					RelativePosition relPos = GetPosition (mid, boundaries, &relDetailedPos);
					DBASSERT (!IsDisjunct (relPos));
					if (IsOverlap (relPos)) {
						if (detailed != nullptr)
							*detailed = relDetailedPos;
						return RelativePosition_Overlap;
					} else if (IsOverlap (relPos) && relDetailedPos == DetailedRelativePosition_Overlap_OnBoundary) {
						if (detailed != nullptr)
							*detailed = relDetailedPos;
						return RelativePosition_Overlap;
					}
			}
	}

	if (arcInside.GetSize () == 1 && IsOverlap (begRelPos) && IsOverlap (endRelPos)) {
		if (detailed != nullptr)
			*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
		return RelativePosition_Overlap;
	} else if (arcInside.GetSize () > 0) {
		for (UIndex idx = 0; idx < arcInside.GetSize (); idx++) {
			Point2D mid;
			Geometry::ComputeEllipseCoord (&arc, (arcInside[idx].GetBegAng () + arcInside[idx].GetEndAng ()) / 2, &mid);
			RelativePosition relPos = GetPosition (mid, boundaries);
			if (IsOverlap (relPos)) {
				return RelativePosition_Overlap;
			}
		}
	}
	return RelativePosition_Disjunct;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GenArc& arc, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;

	if (IsEmpty ())
		return RelativePosition_Disjunct;

	Box2DData arcBounds = Geometry::GetGenArcBoundBox (arc);
	const Box2DData& tmpBoundBox = GetBoundBox ();

	if (arcBounds.xMax < tmpBoundBox.xMin - EPS ||
		arcBounds.xMin > tmpBoundBox.xMax + EPS ||
		arcBounds.yMax < tmpBoundBox.yMin - EPS ||
		arcBounds.yMin > tmpBoundBox.yMax + EPS) {
			return RelativePosition_Disjunct;
	}

	if (fabs (CalcArea ()) < Eps) {
		return GetPositionSmallArea (arc, boundaries);
	} else {
		return GetPositionNormal (arc, boundaries, detailed);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPositionZeroArea (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	RelativePosition position = RelativePosition_Unknown;
	if (boundaries == Boundary_Closed) {
		CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> polyline (*this, 1);

		if (fabs (poly.CalcArea ()) > Eps) {
			position = poly.GetPosition (polyline, boundaries, detailed);
			if (detailed != nullptr) {
				if (*detailed == DetailedRelativePosition_Overlap_SecondCoversFirst)
					*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
				else if (*detailed == DetailedRelativePosition_Overlap_FirstCoversSecond)
					*detailed = DetailedRelativePosition_Overlap_SecondCoversFirst;
			}
		} else {
			// ez az a minositett eset, amikor mindket polygon vonalla fajult
			CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> polyline2 (poly, 1);

			Sector s1, s2;
			GenArc arc1, arc2;
			bool isArc1, isArc2;
			bool intersect = false;
			for (UIndex edgeIdx = 1; edgeIdx <= polyline.GetEdgeNum () && !intersect; ++edgeIdx) {
				isArc1 = polyline.GetSector (edgeIdx, s1, arc1);
				for (UIndex edgeIdx2 = 1; edgeIdx2 <= polyline2.GetEdgeNum () && !intersect; ++edgeIdx2) {
					isArc2 = polyline2.GetSector (edgeIdx2, s2, arc2);
					if (isArc1 && isArc2) {			// two arcs
						Point2D c[4];
						intersect = (XGenArcs (&arc1, &arc2, c) > 0);
					} else if (!isArc1 && !isArc2) {	// two line segments
						Point2D tmp;
						intersect = XSectors (s1, s2, boundaries, &tmp);
					} else {
						GenArc *arc;
						Sector *s, res;

						if (isArc1) {				// first is arc, second is line segment
							arc = &arc1;
							s = &s2;
						} else {					// second is arc, first is line segment
							arc = &arc2;
							s = &s1;
						}

						intersect = XGenArcSectorEps (arc, s, &res, SmallEps) != 0;
					}
				}
			}
			position = (intersect) ? RelativePosition_Overlap : RelativePosition_Disjunct;
		}
	} else {
		position = RelativePosition_Disjunct;
	}
	return position;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;

	if (IsEmpty () || poly.IsEmpty ())
		return RelativePosition_Disjunct;

	const Box2DData& polyBounds = poly.GetBoundBox ();
	const Box2DData& tmpBoundBox = GetBoundBox ();

	if (polyBounds.xMax < tmpBoundBox.xMin - EPS ||
		polyBounds.xMin > tmpBoundBox.xMax + EPS ||
		polyBounds.yMax < tmpBoundBox.yMin - EPS ||
		polyBounds.yMin > tmpBoundBox.yMax + EPS) {
			return RelativePosition_Disjunct;
	}

	RelativePosition position = RelativePosition_Unknown;
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;
	GSErr errorCode;

	PGRelPolyPosExt				pgposition;
	Geometry::PGPOLYEXT			polyExt1;
	Geometry::PGPOLYEXT			polyExt2;
	MakePolyExt (polyExt1);
	poly.MakePolyExt (polyExt2);
	errorCode = Geometry::PGPolyPositionExt (&polyExt1, &polyExt2, &pgposition);
	if (errorCode == NoError) {
		switch (pgposition) {
			case UnknownStatus:		position = RelativePosition_Unknown;			break;
			case PolysOverlap:		position = RelativePosition_Overlap;			break;
			case Poly1CoversPoly2:
				position = RelativePosition_Overlap;
				if (detailed != nullptr)
					*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
				break;
			case Poly2CoversPoly1:
				position = RelativePosition_Overlap;
				if (detailed != nullptr)
					*detailed = DetailedRelativePosition_Overlap_SecondCoversFirst;
				break;
			case PolysEqual:
				position = RelativePosition_Overlap;
				if (detailed != nullptr)
					*detailed = DetailedRelativePosition_Overlap_Equal;
				break;
			case PolysDisjunct:		position = RelativePosition_Disjunct;			break;
			case PolysDisjunct_Node:
				if (boundaries == Boundary_Closed) {
					position = RelativePosition_Overlap;
					if (detailed != nullptr)
						*detailed = DetailedRelativePosition_Overlap_OnBoundary;
				} else {
					position = RelativePosition_Disjunct;
				}
				break;
			case PolysDisjunct_Edge:
				if (boundaries == Boundary_Closed) {
					position = RelativePosition_Overlap;
					if (detailed != nullptr)
						*detailed = DetailedRelativePosition_Overlap_OnBoundary;
				} else {
					position = RelativePosition_Disjunct;
				}
				break;
			case Poly1HasZeroArea:
				{
					position = GetPositionZeroArea (poly, boundaries, detailed);
				}
				break;
			case Poly2HasZeroArea:
				{
					if (poly.IsEmpty () || boundaries != Boundary_Closed) {
						position = RelativePosition_Disjunct;
					} else {
						CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> polyline (poly, 1);

						position = GetPosition (polyline, boundaries, detailed);
					}
				}
				break;
		}
	}

	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::GetPosition", __FILE__, __LINE__);
	return position;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
{
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;

	if (IsEmpty () || poly.IsEmpty ())
		return RelativePosition_Disjunct;

	const Box2DData& polyBounds = poly.GetBoundBox ();
	const Box2DData& tmpBoundBox = GetBoundBox ();

	if (polyBounds.xMax < tmpBoundBox.xMin - EPS ||
		polyBounds.xMin > tmpBoundBox.xMax + EPS ||
		polyBounds.yMax < tmpBoundBox.yMin - EPS ||
		polyBounds.yMin > tmpBoundBox.yMax + EPS) {
			return RelativePosition_Disjunct;
	}

	RelativePosition result = RelativePosition_Unknown;

	DetailedRelativePosition	detailedRelPos = DetailedRelativePosition_Unknown;
	RelativePosition			relPos = RelativePosition_Unknown;

	GenArc arc;
	Sector sect;
	UIndex edgeIdx;
	for (edgeIdx = 1; edgeIdx <= poly.GetEdgeNum (); edgeIdx++) {
		if (poly.GetSector (edgeIdx, sect, arc)) {
			relPos = GetPosition (arc, boundaries, &detailedRelPos);
		} else {
			relPos = GetPosition (sect, boundaries, &detailedRelPos);
		}
		if (result == RelativePosition_Unknown) {
			result = relPos;
			if (detailed != nullptr) {
				*detailed = detailedRelPos;
			}
		} else if (IsDisjunct (result)) {
			if (IsOverlap (relPos)) {
				result = RelativePosition_Overlap;
				if (detailed != nullptr) {
					if (detailedRelPos == DetailedRelativePosition_Overlap_OnBoundary) {
						*detailed = detailedRelPos;
					}
				}
			}
		} else if (IsOverlap (result)) {
			if (detailed != nullptr) {
				if (IsOverlap (relPos)) {
					if (detailedRelPos != DetailedRelativePosition_Unknown) {
						if (*detailed != detailedRelPos) {
							*detailed = DetailedRelativePosition_Unknown;
						}
					}
				} else {
					if (detailedRelPos != DetailedRelativePosition_Overlap_OnBoundary) {
						*detailed = DetailedRelativePosition_Unknown;
					}
				}
			}
		} else {
			DBBREAK ();
			result = RelativePosition_Unknown;
		}
		if (detailed == nullptr && result == RelativePosition_Overlap)
			return result;
	}
	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray, const Point2D& point, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/)
{
	RelativePosition result = RelativePosition_Disjunct;
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;
	USize overlapNum = 0;
	USize overlapFirstCoversSecondNum = 0;
	USize overlapSecondCoversFirstNum = 0;
	USize overlapEqualNum = 0;
	USize overlapOnBoundaryNum = 0;

	for(UIndex idx = 0; idx < polygonArray.GetSize(); idx++) {
		RelativePosition relPos;
		DetailedRelativePosition detailedRelPos;
		relPos = polygonArray [idx]->GetPosition (point, boundaries, &detailedRelPos);
		//Az overlap a legerosebb
		if (IsOverlap (relPos)) {
			result = RelativePosition_Overlap;
			switch (detailedRelPos) {
			case DetailedRelativePosition_Unknown:
				overlapNum++;
				break;
			case DetailedRelativePosition_Overlap_FirstCoversSecond:
				overlapFirstCoversSecondNum++;
				break;
			case DetailedRelativePosition_Overlap_SecondCoversFirst:
				overlapSecondCoversFirstNum++;
				break;
			case DetailedRelativePosition_Overlap_Equal:
				overlapEqualNum++;
				break;
			case DetailedRelativePosition_Overlap_OnBoundary:
				overlapOnBoundaryNum++;
				break;
			default:
				overlapNum++;
				DBBREAK ();
				break;
			}
		}
	}
	if (detailed != nullptr) {
		if (overlapFirstCoversSecondNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
		} else if (overlapSecondCoversFirstNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_SecondCoversFirst;
		} else if (overlapEqualNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_Equal;
		} else if (overlapOnBoundaryNum > 0 &&  overlapNum + overlapOnBoundaryNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_OnBoundary;
		} else {
			*detailed = DetailedRelativePosition_Unknown;
		}
	}
	return result;
}
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GS::Array<GS::SharedPtr<CorePolygon2D <VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray, const Sector& sect, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/)
{
	RelativePosition result = RelativePosition_Disjunct;
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;
	USize overlapNum = 0;
	USize overlapFirstCoversSecondNum = 0;
	USize overlapSecondCoversFirstNum = 0;
	USize overlapEqualNum = 0;
	USize overlapOnBoundaryNum = 0;

	for(UIndex idx = 0; idx < polygonArray.GetSize(); idx++) {
		RelativePosition relPos;
		DetailedRelativePosition detailedRelPos;
		relPos = polygonArray [idx]->GetPosition (sect, boundaries, &detailedRelPos);
		//Az overlap a legerosebb
		if (IsOverlap (relPos)) {
			result = RelativePosition_Overlap;
			switch (detailedRelPos) {
			case DetailedRelativePosition_Unknown:
				overlapNum++;
				break;
			case DetailedRelativePosition_Overlap_FirstCoversSecond:
				overlapFirstCoversSecondNum++;
				break;
			case DetailedRelativePosition_Overlap_SecondCoversFirst:
				overlapSecondCoversFirstNum++;
				break;
			case DetailedRelativePosition_Overlap_Equal:
				overlapEqualNum++;
				break;
			case DetailedRelativePosition_Overlap_OnBoundary:
				overlapOnBoundaryNum++;
				break;
			default:
				overlapNum++;
				DBBREAK ();
				break;
			}
		}
	}
	if (detailed != nullptr) {
		if (overlapFirstCoversSecondNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
		} else if (overlapSecondCoversFirstNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_SecondCoversFirst;
		} else if (overlapEqualNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_Equal;
		} else if (overlapOnBoundaryNum > 0 &&  overlapNum + overlapOnBoundaryNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_OnBoundary;
		} else {
			*detailed = DetailedRelativePosition_Unknown;
		}
	}
	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray, const GenArc& arc, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/)
{
	RelativePosition result = RelativePosition_Disjunct;
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;
	USize overlapNum = 0;
	USize overlapFirstCoversSecondNum = 0;
	USize overlapSecondCoversFirstNum = 0;
	USize overlapEqualNum = 0;
	USize overlapOnBoundaryNum = 0;

	for(UIndex idx = 0; idx < polygonArray.GetSize(); idx++) {
		RelativePosition relPos;
		DetailedRelativePosition detailedRelPos;
		relPos = polygonArray [idx]->GetPosition (arc, boundaries, &detailedRelPos);
		//Az overlap a legerosebb
		if (IsOverlap (relPos)) {
			result = RelativePosition_Overlap;
			switch (detailedRelPos) {
			case DetailedRelativePosition_Unknown:
				overlapNum++;
				break;
			case DetailedRelativePosition_Overlap_FirstCoversSecond:
				overlapFirstCoversSecondNum++;
				break;
			case DetailedRelativePosition_Overlap_SecondCoversFirst:
				overlapSecondCoversFirstNum++;
				break;
			case DetailedRelativePosition_Overlap_Equal:
				overlapEqualNum++;
				break;
			case DetailedRelativePosition_Overlap_OnBoundary:
				overlapOnBoundaryNum++;
				break;
			default:
				overlapNum++;
				DBBREAK ();
				break;
			}
		}
	}
	if (detailed != nullptr) {
		if (overlapFirstCoversSecondNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
		} else if (overlapSecondCoversFirstNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_SecondCoversFirst;
		} else if (overlapEqualNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_Equal;
		} else if (overlapOnBoundaryNum > 0 &&  overlapNum + overlapOnBoundaryNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_OnBoundary;
		} else {
			*detailed = DetailedRelativePosition_Unknown;
		}
	}
	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray, const Box2DData& box, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/)
{
	RelativePosition result = RelativePosition_Disjunct;
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;
	USize overlapNum = 0;
	USize overlapFirstCoversSecondNum = 0;
	USize overlapSecondCoversFirstNum = 0;
	USize overlapEqualNum = 0;
	USize overlapOnBoundaryNum = 0;

	for(UIndex idx = 0; idx < polygonArray.GetSize(); idx++) {
		RelativePosition relPos;
		DetailedRelativePosition detailedRelPos;
		relPos = polygonArray [idx]->GetPosition (box, boundaries, &detailedRelPos);
		//Az overlap a legerosebb
		if (IsOverlap (relPos)) {
			result = RelativePosition_Overlap;
			switch (detailedRelPos) {
			case DetailedRelativePosition_Unknown:
				overlapNum++;
				break;
			case DetailedRelativePosition_Overlap_FirstCoversSecond:
				overlapFirstCoversSecondNum++;
				break;
			case DetailedRelativePosition_Overlap_SecondCoversFirst:
				overlapSecondCoversFirstNum++;
				break;
			case DetailedRelativePosition_Overlap_Equal:
				overlapEqualNum++;
				break;
			case DetailedRelativePosition_Overlap_OnBoundary:
				overlapOnBoundaryNum++;
				break;
			default:
				overlapNum++;
				DBBREAK ();
				break;
			}
		}
	}
	if (detailed != nullptr) {
		if (overlapFirstCoversSecondNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
		} else if (overlapSecondCoversFirstNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_SecondCoversFirst;
		} else if (overlapEqualNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_Equal;
		} else if (overlapOnBoundaryNum > 0 &&  overlapNum + overlapOnBoundaryNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_OnBoundary;
		} else {
			*detailed = DetailedRelativePosition_Unknown;
		}
	}
	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray, const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/)
{
	RelativePosition result = RelativePosition_Disjunct;
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;
	USize overlapNum = 0;
	USize overlapFirstCoversSecondNum = 0;
	USize overlapSecondCoversFirstNum = 0;
	USize overlapEqualNum = 0;
	USize overlapOnBoundaryNum = 0;

	for(UIndex idx = 0; idx < polygonArray.GetSize(); idx++) {
		RelativePosition relPos;
		DetailedRelativePosition detailedRelPos;
		relPos = polygonArray [idx]->GetPosition (poly, boundaries, &detailedRelPos);
		//Az overlap a legerosebb
		if (IsOverlap (relPos)) {
			result = RelativePosition_Overlap;
			switch (detailedRelPos) {
			case DetailedRelativePosition_Unknown:
				overlapNum++;
				break;
			case DetailedRelativePosition_Overlap_FirstCoversSecond:
				overlapFirstCoversSecondNum++;
				break;
			case DetailedRelativePosition_Overlap_SecondCoversFirst:
				overlapSecondCoversFirstNum++;
				break;
			case DetailedRelativePosition_Overlap_Equal:
				overlapEqualNum++;
				break;
			case DetailedRelativePosition_Overlap_OnBoundary:
				overlapOnBoundaryNum++;
				break;
			default:
				overlapNum++;
				DBBREAK ();
				break;
			}
		}
	}
	if (detailed != nullptr) {
		if (overlapFirstCoversSecondNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
		} else if (overlapSecondCoversFirstNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_SecondCoversFirst;
		} else if (overlapEqualNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_Equal;
		} else if (overlapOnBoundaryNum > 0 &&  overlapNum + overlapOnBoundaryNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_OnBoundary;
		} else {
			*detailed = DetailedRelativePosition_Unknown;
		}
	}
	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GS::Array<GS::SharedPtr<CorePolygon2D > >& polygonArray, const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/)
{
	RelativePosition result = RelativePosition_Disjunct;
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;
	USize overlapNum = 0;
	USize overlapFirstCoversSecondNum = 0;
	USize overlapSecondCoversFirstNum = 0;
	USize overlapEqualNum = 0;
	USize overlapOnBoundaryNum = 0;

	for(UIndex idx = 0; idx < polygonArray.GetSize(); idx++) {
		RelativePosition relPos;
		DetailedRelativePosition detailedRelPos;
		relPos = polygonArray [idx]->GetPosition (poly, boundaries, &detailedRelPos);
		//Az overlap a legerosebb
		if (IsOverlap (relPos)) {
			result = RelativePosition_Overlap;
			switch (detailedRelPos) {
			case DetailedRelativePosition_Unknown:
				overlapNum++;
				break;
			case DetailedRelativePosition_Overlap_FirstCoversSecond:
				overlapFirstCoversSecondNum++;
				break;
			case DetailedRelativePosition_Overlap_SecondCoversFirst:
				overlapSecondCoversFirstNum++;
				break;
			case DetailedRelativePosition_Overlap_Equal:
				overlapEqualNum++;
				break;
			case DetailedRelativePosition_Overlap_OnBoundary:
				overlapOnBoundaryNum++;
				break;
			default:
				overlapNum++;
				DBBREAK ();
				break;
			}
		}
	}
	if (detailed != nullptr) {
		if (overlapFirstCoversSecondNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
		} else if (overlapSecondCoversFirstNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_SecondCoversFirst;
		} else if (overlapEqualNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_Equal;
		} else if (overlapOnBoundaryNum > 0 &&  overlapNum + overlapOnBoundaryNum == polygonArray.GetSize()) {
			*detailed = DetailedRelativePosition_Overlap_OnBoundary;
		} else {
			*detailed = DetailedRelativePosition_Unknown;
		}
	}
	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PGPositionExt CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentIn (Sector sector, GS::Array<Sector>* resSectors /*= nullptr*/) const
{
	PGPositionExt result;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	PGRESSECTOREXT	newSectors;
	newSectors.sectorsData = reinterpret_cast<GSPtr> (resSectors);
	newSectors.newSector = &NewSector;

	result = PGSegmentInPolyExt (&polyExt1, &sector.c1, &sector.c2, false, resSectors ? &newSectors : nullptr);

	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PGPositionExt CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentOut (Sector sector, GS::Array<Sector>* resSectors /*= nullptr*/) const
{
	PGPositionExt result;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	PGRESSECTOREXT	newSectors;
	newSectors.sectorsData = reinterpret_cast<GSPtr> (resSectors);
	newSectors.newSector = &NewSector;

	result = PGSegmentInPolyExt (&polyExt1, &sector.c1, &sector.c2, true, resSectors ? &newSectors : nullptr);

	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Intersect (const Point2D& c, const Vector2D& dir, GS::Array<Sector>* result) const
{

	Sector s;
	if (fabs (dir.x) > fabs (dir.y)) {
		double x = boundBox.xMin - 1.0;
		double k = (x - c.x) / dir.x;
		s.c1 = c + MulVector (dir, k);

		x = boundBox.xMax + 1.0;
		k = (x - c.x) / dir.x;
		s.c2 = c + MulVector (dir, k);
	} else {
		double y = boundBox.yMin - 1.0;
		double k = (y - c.y) / dir.y;
		s.c1 = c + MulVector (dir, k);

		y = boundBox.yMax + 1.0;
		k = (y - c.y) / dir.y;
		s.c2 = c + MulVector (dir, k);
	}
	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	PGRESSECTOREXT	newSectors;
	newSectors.sectorsData = reinterpret_cast<GSPtr> (result);
	newSectors.newSector = &NewSector;

	return PGSegmentInPolyExt (&polyExt1, &s.c1, &s.c2, false, result ? &newSectors : nullptr) != PGOutsidePoly;

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::FixArray<Point2D, 4>	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetTransformedBoundBox (const TRANMAT& tr, const TRANMAT& invTr /*= Geometry::IdentityTranMat*/) const
{
	GS::FixArray<Point2D, 4> box;

	ArcDivParams arcDivParams;
	GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > result;
	PolygonResult polyResult = Transform (arcDivParams, tr, result);
	if (polyResult != ResultSameAsThis && (result.GetSize () == 0 || polyResult == EmptyPolygon)) {
		BNZeroMemory (box.GetContent (), 4 * sizeof (Point2D));
		return box;
	}
	Box2DData tmpBoundBox;
	if (polyResult == ResultSameAsThis) {
		tmpBoundBox = GetBoundBox ();
	} else {
		tmpBoundBox = result[0]->GetBoundBox ();
		for (UIndex polyIdx = 1; polyIdx < result.GetSize (); polyIdx++) {
			UnionBox(result[polyIdx]->GetBoundBox (), &tmpBoundBox);
		}
	}

	box[0]	= Point2D (tmpBoundBox.xMin, tmpBoundBox.yMin);
	box[1]	= Point2D (tmpBoundBox.xMax, tmpBoundBox.yMin);
	box[2]	= Point2D (tmpBoundBox.xMax, tmpBoundBox.yMax);
	box[3]	= Point2D (tmpBoundBox.xMin, tmpBoundBox.yMax);

	if (!invTr.IsIdentity ()) {
		for (GS::Int32 i = 0; i < 4; i++)
			box[i] = SetCoord2D (TransformPoint (invTr, SetCoord3D (box[i])));
	}

	return box;
}

//Modify polygon
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveHoles (GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& newPoly) const
{
	GSErr errorCode;

	if (nContours <= 1) {
		return ResultSameAsThis;
	}

	GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 >  result;
	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyRemoveHolesExt (&polyExt1, &resPolyExt);
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::RemoveHoles", __FILE__, __LINE__);

	DBCHECKCOREPOLY_CHECK;

	DBASSERT (result.GetSize () == 1);
	if (result.GetSize () != 1) {
		return EmptyPolygon;
	}
	newPoly = result[0];
	newPoly->status.isRegularized = true;

	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteHoleUpdateUserData (GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result, UIndex begVertexIdx, UIndex endVertexIdx, UIndex contourIdx) const
{
	//VertexId
	DBASSERT ((!flags.isVertexUserData && vertexInfos.GetSize() == 0 ) || (flags.isVertexUserData && vertexInfos.GetSize()));
	if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
		CopyInfo_Data <VertexUserData> (result->vertexInfos, 0, vertexInfos, 0, begVertexIdx);
		CopyInfo_Data <VertexUserData> (result->vertexInfos, begVertexIdx, vertexInfos, (endVertexIdx + 1), (nVertices - endVertexIdx));
	}

	//EdgeId
	DBASSERT ((!flags.isEdgeUserData && inhEdgeInfos.GetSize() == 0) || (flags.isEdgeUserData && inhEdgeInfos.GetSize() != 0));
	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
		CopyInfo_Data <EdgeUserData> (result->inhEdgeInfos, 0, inhEdgeInfos, 0, begVertexIdx);
		CopyInfo_Data <EdgeUserData> (result->inhEdgeInfos, begVertexIdx, inhEdgeInfos, (endVertexIdx + 1), (nVertices - endVertexIdx));
	}

	//ContourId
	DBASSERT ((!flags.isContourUserData && contourInfos.GetSize() == 0) || (flags.isContourUserData && contourInfos.GetSize() != 0));
	if (contourInfos.GetSize() != 0 && flags.isContourUserData) {
		CopyInfo_Data <ContourUserData> (result->contourInfos, 0, contourInfos, 0, contourIdx);
		CopyInfo_Data <ContourUserData> (result->contourInfos, contourIdx, contourInfos, (contourIdx + 1), (nContours - contourIdx));
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteHole (UIndex contourIdx) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 2, GetContourNum ());

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > result = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this, true);

	UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
	UIndex endVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);
	USize nDelVertex = endVertexIdx - begVertexIdx + 1;

	USize nDelArcs = 0;
	if (nArcs != 0 && arcs.GetSize () > 1) {
		for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
			if (arcs[arcIdx].begIndex >= begVertexIdx && arcs[arcIdx].begIndex < endVertexIdx)
				nDelArcs++;
		}
	}

	result->CopyPolygonLevelDataFrom (*this);
	result->AllocateInternalData (nVertices - nDelVertex, nArcs - nDelArcs, nContours - 1);

	result->status.isRegularized = status.isRegularized; //A lyuk torles nem szunteti meg a regularizalt allapotot

	for (UIndex vertexIdx = 1; vertexIdx < begVertexIdx; vertexIdx++) {
		result->vertices[vertexIdx] = vertices[vertexIdx];
	}
	for (UIndex vertexIdx = begVertexIdx, sourceVertexIdx = endVertexIdx + 1; vertexIdx <= result->nVertices && sourceVertexIdx <= nVertices; vertexIdx++, sourceVertexIdx++) {
		result->vertices[vertexIdx] = vertices[sourceVertexIdx];
	}
	if (arcs.GetSize () > 1 && nArcs != 0) {
		UIndex actArcIdx = 1;
		for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
			if (actArcIdx > result->nArcs) {
				break;
			}
			if (arcs[arcIdx].begIndex < begVertexIdx) {
				result->arcs[actArcIdx].arcAngle = arcs[arcIdx].arcAngle;
				result->arcs[actArcIdx].begIndex = arcs[arcIdx].begIndex;
				result->arcs[actArcIdx].endIndex = arcs[arcIdx].endIndex;
				actArcIdx++;
			} else if (arcs[arcIdx].begIndex > endVertexIdx) {
				result->arcs[actArcIdx].arcAngle = arcs[arcIdx].arcAngle;
				result->arcs[actArcIdx].begIndex = arcs[arcIdx].begIndex - nDelVertex;
				result->arcs[actArcIdx].endIndex = result->arcs[actArcIdx].begIndex + 1;
				actArcIdx++;
			}
		}
		DBASSERT (actArcIdx - 1 == result->nArcs);
	}
	UIndex actContourIdx = 1;
	for (UIndex tmpContourIdx = 1; tmpContourIdx <= nContours; tmpContourIdx++) {
		if (contourEnds[tmpContourIdx] < begVertexIdx) {
			result->contourEnds[actContourIdx] = contourEnds[tmpContourIdx];
			actContourIdx++;
		} else if (contourEnds[tmpContourIdx] > endVertexIdx) {
			result->contourEnds[actContourIdx] = contourEnds[tmpContourIdx] - nDelVertex;
			actContourIdx++;
		}
	}
	DBASSERT (actContourIdx - 1 == result->nContours);

	DeleteHoleUpdateUserData (result, begVertexIdx, endVertexIdx, contourIdx);

	result->UpdateBoundingBox ();

	DBASSERT (result->Check (PolyCheckFlags_All_Polygon, nullptr, MaxCoordValue ()));
	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Move (Vector2D offset)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	for (UIndex vertexIdx = 1; vertexIdx <= nVertices; vertexIdx++) {
		vertices[vertexIdx] = vertices[vertexIdx] + offset;
	}
	OffsetBox (&boundBox, offset.x, offset.y);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearVertexUserDatas (void)
{
	if (vertexInfos.GetSize() != 0) {
		ZeroInfo_Data <VertexUserData> (vertexInfos, 0, (nVertices + 1), defaultVertexData);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearEdgeUserDatas (void)
{
	if (inhEdgeInfos.GetSize() != 0) {
		ZeroInfo_Data <EdgeUserData> (inhEdgeInfos, 0, (nVertices + 1), defaultEdgeData);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearContourUserDatas (void)
{
	if (contourInfos.GetSize() != 0) {
		ZeroInfo_Data <ContourUserData> (contourInfos, 0, (nContours + 1), defaultContourData);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Stretch (const Point2D& fixPoint,
	const Point2D& draggedPoint,
	const Vector2D& offsetAxisX,
	const Vector2D& offsetAxisY /*= Vector2D (0.0, 0.0)*/,
	const ArcDivParams& arcDivParams /*= ArcDivParams (0.0)*/)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	if (offsetAxisX.GetLengthSqr () < (EPS * EPS) && offsetAxisY.GetLengthSqr () < (EPS * EPS))
		return;

	const Vector2D fixToDraggedVector = draggedPoint - fixPoint;

	if (fixToDraggedVector.GetLengthSqr () < (EPS * EPS)) {
		ThrowGeometryExceptionAtError (Error, "CorePolygon2D::Stretch: Dragged point = Fix point", __FILE__, __LINE__);
		return;
	}

	const bool needSegment = nArcs > 0 && arcs.GetSize () > 1;
	if ( (arcDivParams.maxDifference != 0.0 || arcDivParams.boxToKeepMaxDifferenceIn != nullptr) && needSegment) {
		SegmentUp (arcDivParams); //A visszateresi erteket nem kell vizsgalni, mert nArcs > 0
	}

	if (offsetAxisX.GetLengthSqr () >= (EPS * EPS)) {
		const Vector2D offsetAxisXUnit = offsetAxisX.GetUnitVector ();

		for (UIndex i = 1; i <= nVertices; ++i) {
			Point2D& coord = vertices[i];

			const double projLengthOfFixToDraggedVector = fixToDraggedVector * offsetAxisXUnit;
			const double projLengthOfFixToCoordVector = (coord - fixPoint) * offsetAxisXUnit;
			const double scale = projLengthOfFixToCoordVector / projLengthOfFixToDraggedVector;

			const Vector2D move = offsetAxisX * scale;

			coord += move;
		}
	}

	if (offsetAxisY.GetLengthSqr () >= (EPS * EPS)) {
		const Vector2D offsetAxisYUnit = offsetAxisY.GetUnitVector ();

		for (UIndex i = 1; i <= nVertices; ++i) {
			Point2D& coord = vertices[i];

			const double projLengthOfFixToDraggedVector = fixToDraggedVector * offsetAxisYUnit;
			const double projLengthOfFixToCoordVector = (coord - fixPoint) * offsetAxisYUnit;
			const double scale = projLengthOfFixToCoordVector / projLengthOfFixToDraggedVector;

			const Vector2D move = offsetAxisY * scale;

			coord += move;
		}
	}

	UpdateBoundingBox ();
	status.isRegularized = false;

	DBCHECKCOREPOLY_CHECK;
}

//Ha az iveket torzitani kellene, akkor assertal
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::TransformPreserveArcs (const TRANMAT& tran)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	if (tran.IsIdentity ()) {
		return;
	}
	if (IsEmpty ()) {
		return;
	}

	DBASSERT (nArcs == 0 || Geometry::TMIsPreserveArc (tran));

	if (tran.HasMirror () || (nArcs > 0 && !Geometry::TMIsPreserveArc (tran)))
		status.isRegularized = false;

	for (UIndex vertexIdx = 1; vertexIdx <= nVertices; vertexIdx++) {
		vertices[vertexIdx] = Geometry::Transform2dPoint (tran, vertices[vertexIdx]);
	}

	if (arcs.GetSize () > 1 && tran.HasMirror ()) {
		for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++)
			arcs[arcIdx].arcAngle *= -1;
	}
	RemoveSmallArcs ();

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::TransformPreserveArcs (	const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& filterWithPolygon,
											const TRANMAT& tran,
											bool& isTransformedAll)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	if (tran.IsIdentity ()) {
		return;
	}
	if (IsEmpty ()) {
		return;
	}

	DBASSERT (nArcs == 0 || Geometry::TMIsPreserveArc (tran));

	isTransformedAll = true;

	for (UIndex vertexIdx = 1; vertexIdx <= nVertices; vertexIdx++) {
		RelativePosition relpos = filterWithPolygon.GetPosition (vertices[vertexIdx], Boundary_Closed);
		if (IsOverlap (relpos))
			vertices[vertexIdx] = Geometry::Transform2dPoint (tran, vertices[vertexIdx]);
		else
			isTransformedAll = false;
	}

	if (arcs.GetSize () > 1 && tran.HasMirror ()) {
		for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
			RelativePosition relpos1 = filterWithPolygon.GetPosition (vertices[arcs[arcIdx].begIndex], Boundary_Closed);
			RelativePosition relpos2 = filterWithPolygon.GetPosition (vertices[arcs[arcIdx].endIndex], Boundary_Closed);
			if (IsOverlap (relpos1) && IsOverlap (relpos2))
				arcs[arcIdx].arcAngle *= -1.0;
		}
	}
	UpdateBoundingBox ();

	if (!isTransformedAll || tran.HasMirror () || (nArcs > 0 && !Geometry::TMIsPreserveArc (tran)))
		status.isRegularized = false;
	if (!isTransformedAll)
		flags.isSameDirEdgeLegal = true;

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::TransformPreserveArcs (	const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& filterPolygonArray,
											const TRANMAT& tran,
											bool& isTransformedAll)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	if (tran.IsIdentity ()) {
		return;
	}
	if (IsEmpty ()) {
		return;
	}

	DBASSERT (nArcs == 0 || Geometry::TMIsPreserveArc (tran));

	isTransformedAll = true;

	for (UIndex vertexIdx = 1; vertexIdx <= nVertices; vertexIdx++) {
		RelativePosition relpos = CorePolygon2D::GetPosition (filterPolygonArray, vertices[vertexIdx], Boundary_Closed);
		if (IsOverlap (relpos))
			vertices[vertexIdx] = Geometry::Transform2dPoint (tran, vertices[vertexIdx]);
		else
			isTransformedAll = false;
	}

	if (arcs.GetSize () > 1 && tran.HasMirror ()) {
		for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
			RelativePosition relpos1 = CorePolygon2D::GetPosition (filterPolygonArray, vertices[arcs[arcIdx].begIndex], Boundary_Closed);
			RelativePosition relpos2 = CorePolygon2D::GetPosition (filterPolygonArray, vertices[arcs[arcIdx].endIndex], Boundary_Closed);
			if (IsOverlap (relpos1) && IsOverlap (relpos2))
				arcs[arcIdx].arcAngle *= -1.0;
		}
	}
	UpdateBoundingBox ();

	if (!isTransformedAll || tran.HasMirror () || (nArcs > 0 && !Geometry::TMIsPreserveArc (tran)))
		status.isRegularized = false;
	if (!isTransformedAll)
		flags.isSameDirEdgeLegal = true;

	DBCHECKCOREPOLY_CHECK;
}

//Megtartjuk az iveket. Ha szukseges, akkor elotte transzformalni kell. Az automatikus szegmentalas gazos, mert ha eloszor szegmentalunk, akkor megvaltozhat a lyukak szama, ezert az indexek rosszak lehetnek. Ha utana szegmentalunk akkor csak az eredmeny rossz
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::TransformHolePreserveArcs (	const GS::Array<UIndex>& contourIdxs,
												const GS::Array<TRANMAT>& trans,
												bool keepOriginals)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	DBASSERT (contourIdxs.GetSize () > 0);
	DBASSERT (trans.GetSize () > 0);
#ifdef CHECKED_VERSION
	for (GS::Array <UIndex>::ConstIterator contourIdxIter = contourIdxs.Enumerate (); contourIdxIter != nullptr; ++contourIdxIter) {
		DBASSERT (*contourIdxIter > 1 && *contourIdxIter <= nContours);
	}
	for (GS::Array<TRANMAT>::ConstIterator tranIter = trans.Enumerate (); tranIter != nullptr; ++tranIter) {
		DBASSERT (nArcs == 0 || Geometry::TMIsPreserveArc (*tranIter));
	}
#endif

	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpPoly (*this, true);

	USize transNum = trans.GetSize ();
	USize selectedContourNum = 0;
	USize selectedContourVertexNum = 0;
	USize selectedContourArcNum = 0;
	for (GS::Array <UIndex>::ConstIterator contourIdxIter = contourIdxs.Enumerate (); contourIdxIter != nullptr; ++contourIdxIter) {
		UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (*contourIdxIter);
		UIndex endVertexIdx = GetInternalVertexEndIdxInContour (*contourIdxIter);
		++selectedContourNum;
		selectedContourVertexNum += (endVertexIdx - begVertexIdx + 1);
		for (UIndex vertexIdx = begVertexIdx; vertexIdx < endVertexIdx; vertexIdx++) {
			if (GetInternalArcIdx (vertexIdx) > 0)
				++selectedContourArcNum;
		}
	}

	USize verticesNum	= nVertices + transNum * selectedContourVertexNum;
	USize arcsNum		= nArcs		+ transNum * selectedContourArcNum;
	USize contoursNum	= nContours	+ transNum * selectedContourNum;
	if (!keepOriginals) {
		verticesNum	-= selectedContourVertexNum;
		arcsNum		-= selectedContourArcNum;
		contoursNum	-= selectedContourNum;
	}
	tmpPoly.CopyPolygonLevelDataFrom (*this);
	tmpPoly.AllocateInternalData (verticesNum, arcsNum, contoursNum);
	tmpPoly.status.isRegularized = false;

	tmpPoly.nVertices = 0;
	tmpPoly.nArcs = 0;
	tmpPoly.nContours = 0;

	for (UIndex contourIdx = 1; contourIdx <= nContours; contourIdx++) {
		if (contourIdxs.Contains (contourIdx)) {
			if (keepOriginals)
				tmpPoly.CopyInternalContourFrom (*this, contourIdx);
			for (GS::Array<TRANMAT>::ConstIterator tranIt = trans.Enumerate (); tranIt != nullptr; ++tranIt) {
				tmpPoly.CopyInternalContourFrom (*this, contourIdx);

				UIndex begVertexIdx = tmpPoly.GetInternalVertexBeginIdxInContour (tmpPoly.nContours);
				UIndex endVertexIdx = tmpPoly.GetInternalVertexEndIdxInContour (tmpPoly.nContours);
				for(UIndex vertexIdx = begVertexIdx; vertexIdx <= endVertexIdx; vertexIdx++)
					tmpPoly.vertices[vertexIdx] = Geometry::Transform2dPoint ((*tranIt), tmpPoly.vertices[vertexIdx]);

				if (tmpPoly.arcs.GetSize () > 1 && ((*tranIt).HasMirror ())) {
					for (UIndex arcIdx = 1; arcIdx <= tmpPoly.nArcs; arcIdx++) {
						if (tmpPoly.arcs[arcIdx].begIndex >= begVertexIdx && tmpPoly.arcs[arcIdx].begIndex < endVertexIdx) {
							tmpPoly.arcs[arcIdx].arcAngle *= -1.0;
						}
					}
				}
			}
		} else {
			tmpPoly.CopyInternalContourFrom (*this, contourIdx);
		}
	}

	tmpPoly.UpdateBoundingBox ();

	// ezen lehetne picit gyorsitani
	operator= (tmpPoly);

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentUp (const ArcDivParams& arcDivParams)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	if (nArcs <= 0 || arcs.GetSize () <= 1) {
		return;
	}

	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpPoly (*this, true);

	try {
		GS::ArrayFB< GS::Array<Point2D> , 6> segmentedArcs;
		USize numOfSegmentedVertex = 0;
		FillSegmentedArc (arcDivParams, segmentedArcs, numOfSegmentedVertex);
		tmpPoly.CopyPolygonLevelDataFrom (*this);
		tmpPoly.AllocateInternalData (0, 0, 0, nVertices + numOfSegmentedVertex  /*nVertices*/, 0 /*nArcs*/, nContours /*nContours*/); //Egyesevel adjuk hozza a vertexeket es contourokat
		SetSegmentUp (tmpPoly, segmentedArcs);
	} catch (const std::exception&) {
		ThrowGeometryExceptionAtError (Error, "CorePolygon2D::SegmentUp", __FILE__, __LINE__);
	} catch (const GS::Exception& e) {
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolygon2D::SegmentUp", __FILE__, __LINE__);
	}

	tmpPoly.UpdateBoundingBox ();
	tmpPoly.status.isRegularized = false;

	// ezen lehetne picit gyorsitani
	operator= (tmpPoly);

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EliminateArcs (void)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	if (nArcs <= 0 || arcs.GetSize () <= 1) {
		return;
	}

	status.isRegularized = false;
	flags.isSameDirEdgeLegal = true;


	arcs.Clear (true);
	PolyArcRec dummyArc;
	dummyArc.arcAngle = 0.0;
	dummyArc.begIndex = 0;
	dummyArc.endIndex = 0;
	arcs.Push (dummyArc);
	nArcs = 0;

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MoveVertex (UIndex vertexIdx, const Point2D& newPosition)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	vertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);

	status.isRegularized = false;
	flags.isSameDirEdgeLegal = true;

	UIndex contourIdx = GetContourIdxFromInternalVertexIdx (vertexIdx);
	vertices [vertexIdx] = newPosition;

	UIndex duplicatedVertexIdx = vertexIdx;

	if (vertexIdx == GetInternalVertexBeginIdxInContour (contourIdx)) {
		duplicatedVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);
		vertices [duplicatedVertexIdx] = newPosition;
	}

	RemoveSmallArcs ();

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertVertex (UIndex edgeIdx, const Point2D& newPosition)
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetVertexNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	InsertVertexInternal (edgeIdx, newPosition);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertEdge (const UIndex vertexIndex)
{
	DBCHECKINDEX_COREPOLY (vertexIndex, 1, GetVertexNum ());
	UIndex vertexInternalIndex = VertexIdx2InternalVertexIdx (vertexIndex);
	InsertEdgeInternal (vertexInternalIndex);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertVertexOnPolygon (const Point2D& newPosition, UIndex edgeIndex, GS::SharedPtr<CorePolygon2D>& result, UIndex& vertexIdx) const
{
	if (DBERROR (IsEmpty ()))
		ThrowGeometryExceptionAtError (Error, "CorePolygon2D::InsertVertexOnPolygon empty polygon", __FILE__, __LINE__);

	if (DBERROR (!IsCoordOnEdge (newPosition, edgeIndex)))
		ThrowGeometryExceptionAtError (Error, "CorePolygon2D::InsertVertexOnPolygon vertex not on polygon", __FILE__, __LINE__);

	result = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);

	const UIndex internalEdgeIndex = VertexIdx2InternalVertexIdx (edgeIndex);
	result->InsertVertexInternal (internalEdgeIndex, newPosition, true, true);

	UIndex arcIndex = GetInternalArcIdx (internalEdgeIndex);

	if (arcIndex > 0) {
		Point2D origC;
		const double& origArcAngle = arcs[arcIndex].arcAngle;
		if (ArcGetOrigo (&vertices[internalEdgeIndex], &vertices[internalEdgeIndex + 1], origArcAngle, &origC)) {
			const double newAngle = ComputeRotFi (origC, vertices[internalEdgeIndex], newPosition, origArcAngle < 0.0);
			PolyArcRec newArc;
			newArc.begIndex = internalEdgeIndex;
			newArc.endIndex = internalEdgeIndex + 1;
			newArc.arcAngle = newAngle;
			++result->nArcs;
			result->arcs.Insert (arcIndex, newArc);
			result->arcs[arcIndex + 1].arcAngle = origArcAngle - newAngle;
		}
	}

	result->UpdateBoundingBox ();

	if (IsEqualCoord (result->vertices[edgeIndex], newPosition, Eps))
		vertexIdx = edgeIndex;
	else
		vertexIdx = edgeIndex + 1;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteVertex (UIndex vertexIdx)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	vertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);

	status.isRegularized = false;
	flags.isSameDirEdgeLegal = true;

	DeleteVertexFromInternalData (vertexIdx);
	FixingContours ();

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeAngle (UIndex edgeIdx, double edgeAngle)
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	SetEdgeAngleInternal (edgeIdx, edgeAngle);

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MoveVertices (const GS::HashTable<UIndex, Point2D>& newValues)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	for (UIndex vertexIdx : newValues.Keys ()) {
		DBCHECKINDEX_COREPOLY (vertexIdx, 1, GetVertexNum ());
		UIndex internalVertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);
		UIndex contourIdx = GetContourIdxFromInternalVertexIdx (internalVertexIdx);
		vertices[internalVertexIdx] = newValues[vertexIdx];
		if (internalVertexIdx == GetInternalVertexBeginIdxInContour (contourIdx)) {
			vertices[GetInternalVertexEndIdxInContour (contourIdx)] = newValues[vertexIdx];
		}
	}

	RemoveSmallArcs ();

	status.isRegularized = false;
	flags.isSameDirEdgeLegal = true;

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdge (UIndex edgeIdx, const GS::Array<GenArc>& arcs, const ArcDivParams& arcDivParams)
{
	for (UIndex i = 0; i < arcs.GetSize (); ++i) {
		if (DBERROR (arcs[i].IsWhole ()))
			ThrowGeometryExceptionAtError (Error, "CorePolygon2D::RepleceEdge full arc", __FILE__, __LINE__);
	}

	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	ReplaceEdgeInternal (edgeIdx, arcs, arcDivParams);

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdge (UIndex edgeIdx, const GS::Array<double>& angles, const GS::Array<Point2D>& internalVerts)
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	ReplaceEdgeInternal (edgeIdx, angles, internalVerts);

	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AddHole (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, UIndex contourIdx)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	UIndex begVertexIdx = source.GetInternalVertexBeginIdxInContour (contourIdx);
	UIndex endVertexIdx = source.GetInternalVertexEndIdxInContour (contourIdx);

	USize newVerticesNum = endVertexIdx - begVertexIdx + 1;
	USize newArcsNum = 0;

	if (source.arcs.GetSize () > 1 && source.nArcs != 0) {
		for (UIndex arcIdx = 1; arcIdx <= source.nArcs; arcIdx++) {
			if (source.arcs[arcIdx].begIndex >= begVertexIdx && source.arcs[arcIdx].begIndex < endVertexIdx) {
				newArcsNum++;
			}
		}
	}

	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpPoly (*this, nVertices + newVerticesNum, nArcs + newArcsNum, nContours + 1);
	tmpPoly.CopyInternalContourFrom (source, contourIdx);

	tmpPoly.UpdateBoundingBox ();

	// ezen lehetne picit gyorsitani
	operator= (tmpPoly);

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Visit (CorePolygon2DVertexVisitor &visitor)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	for (UIndex contourIdx = 1; contourIdx <= nContours; ++contourIdx) {
		UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);

		for (UIndex vIdx = begVertexIdx; vIdx < endVertexIdx; ++vIdx) {
			visitor (vertices[vIdx]);	// Coord may be modified!
		}
		vertices[endVertexIdx] = vertices[begVertexIdx];
	}

	status.isRegularized = false;
	UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Visit (CorePolygon2DConstVertexVisitor &visitor) const
{
	for (UIndex contourIdx = 1; contourIdx <= nContours; ++contourIdx) {
		UIndex begVertexIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endVertexIdx = GetInternalVertexEndIdxInContour (contourIdx);

		for (UIndex vIdx = begVertexIdx; vIdx < endVertexIdx; ++vIdx) {
			visitor (vertices[vIdx]);
		}
	}
}

#pragma warning(push)
#pragma warning(disable:4127) //conditional expression is constant - Because of template argument
#pragma warning(disable:4100) //'comparator': unreferenced formal parameter - It is unreferenced when "checkUserData" is false

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
template <class EdgeUserDataComparator, bool checkUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveSameDirEdge (const EdgeUserDataComparator& comparator)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	status.isRegularized = false; //Extrem esetekben elkepzelheto, hogy egy vertex megszunesevel egy el annyit valtozik, hogy egy masik vertex mar a kuszobon belulre kerul

	USize origNVertices = nVertices;

	GS::UInt32		i;
	double	dx12, dy12, dx23, dy23, a12, a23;

	for (UIndex iContour = 1; iContour <= nContours; iContour++) {
		UIndex iFirstContourVertex = iContour == 1 ? 1 : contourEnds[iContour - 1] + 1;
		if (contourEnds[iContour] <= iFirstContourVertex) {
			DBBREAK ();
			continue;
		}

		for (i = iFirstContourVertex + 1; i < contourEnds[iContour]; i++) {
			if (!checkUserData || comparator (inhEdgeInfos[i - 1], inhEdgeInfos[i])) {
				if (GetInternalArcIdx (i) == 0 && GetInternalArcIdx (i - 1) == 0) {

					const Point2D& prev	= vertices[i - 1];
					const Point2D& c		= vertices[i];
					const Point2D& next	= vertices[i + 1];

					dx12 = c.x - prev.x;
					dy12 = c.y - prev.y;
					dx23 = next.x - c.x;
					dy23 = next.y - c.y;

					a12 = Geometry::ArcTan (dy12, dx12);
					a23 = Geometry::ArcTan (dy23, dx23);
					if (IsNearZero (a12 - a23, Eps)) {
						DeleteVertexFromInternalData (i);
						i--;
					}
				}
				if (GetInternalArcIdx (i) != 0 && GetInternalArcIdx (i - 1) != 0) {
					const UIndex prevEdgeArcInd = GetInternalArcIdx (i - 1);
					const double prevEdgeArcAngle = arcs[prevEdgeArcInd].arcAngle;
					const UIndex nextEdgeArcInd = GetInternalArcIdx (i);
					const double nextEdgeArcAngle = arcs[nextEdgeArcInd].arcAngle;
					if (prevEdgeArcAngle * nextEdgeArcAngle > 0.0) {		/* Same arc direction*/
						if (fabs (prevEdgeArcAngle + nextEdgeArcAngle) < 2 * PI - RadEps) {
							const Point2D& prev = vertices[i - 1];
							const Point2D& c = vertices[i];
							const Point2D& next = vertices[i + 1];
							Point2D prevArcOrigo;
							ArcGetOrigo (&prev, &c, prevEdgeArcAngle, &prevArcOrigo);
							Point2D nextArcOrigo;
							ArcGetOrigo (&c, &next, nextEdgeArcAngle, &nextArcOrigo);
							if (Dist (prevArcOrigo, nextArcOrigo) < Eps) {
								arcs[prevEdgeArcInd].arcAngle = prevEdgeArcAngle + nextEdgeArcAngle;
								DeleteVertexFromInternalData (i);
								i--;
							}
						}
					}
				}
			}
		}
		if (!checkUserData || comparator (inhEdgeInfos[contourEnds[iContour] - 1], inhEdgeInfos[iFirstContourVertex])) {
			if (GetInternalArcIdx (contourEnds[iContour] - 1) == 0 && GetInternalArcIdx (iFirstContourVertex) == 0) {
				const Point2D& prev	= vertices[contourEnds[iContour] - 1];
				const Point2D& c	= vertices[iFirstContourVertex];
				const Point2D& next	= vertices[iFirstContourVertex + 1];

				dx12 = c.x - prev.x;
				dy12 = c.y - prev.y;
				dx23 = next.x - c.x;
				dy23 = next.y - c.y;

				a12 = Geometry::ArcTan (dy12, dx12);
				a23 = Geometry::ArcTan (dy23, dx23);
				if (IsNearZero (a12 - a23, Eps))
					DeleteVertexFromInternalData (iFirstContourVertex);
			}
			if (GetInternalArcIdx (contourEnds[iContour] - 1) != 0 && GetInternalArcIdx (iFirstContourVertex) != 0) {
				const UIndex prevEdgeArcInd = GetInternalArcIdx (contourEnds[iContour] - 1);
				const double prevEdgeArcAngle = arcs[prevEdgeArcInd].arcAngle;
				const UIndex nextEdgeArcInd = GetInternalArcIdx (iFirstContourVertex);
				const double nextEdgeArcAngle = arcs[nextEdgeArcInd].arcAngle;
				if (prevEdgeArcAngle * nextEdgeArcAngle > 0.0) {		/* Same arc direction*/
					if (fabs (prevEdgeArcAngle + nextEdgeArcAngle) < 2 * PI - RadEps) {
						const Point2D& prev = vertices[contourEnds[iContour] - 1];
						const Point2D& c = vertices[iFirstContourVertex];
						const Point2D& next = vertices[iFirstContourVertex + 1];
						Point2D prevArcOrigo;
						ArcGetOrigo (&prev, &c, prevEdgeArcAngle, &prevArcOrigo);
						Point2D nextArcOrigo;
						ArcGetOrigo (&c, &next, nextEdgeArcAngle, &nextArcOrigo);
						if (Dist (prevArcOrigo, nextArcOrigo) < Eps) {
							arcs[prevEdgeArcInd].arcAngle = prevEdgeArcAngle + nextEdgeArcAngle;
							DeleteVertexFromInternalData (iFirstContourVertex);
						}
					}
				}
			}
		}
	}

	FixingContours ();

	if (origNVertices != nVertices) {
		UpdateBoundingBox ();
	}
	DBCHECKCOREPOLY_CHECK;
}

#pragma warning(pop)

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveSameDirEdge ()
{
	RemoveSameDirEdge<std::equal_to<EdgeUserData>, false> (std::equal_to<EdgeUserData> ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
template <class EdgeUserDataComparator>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveSameDirEdgesOnlyWithSameUserData (const EdgeUserDataComparator& comparator)
{
	RemoveSameDirEdge<EdgeUserDataComparator, true> (comparator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveSameDirEdgesOnlyWithSameUserData ()
{
	RemoveSameDirEdge<std::equal_to<EdgeUserData>, true> (std::equal_to<EdgeUserData> ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveZeroEdgesAndArcs (double minEdgeLength, double minArcAngle)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	status.isRegularized = false; //Extrem esetekben elkepzelheto, hogy egy vertex megszunesevel egy el annyit valtozik, hogy egy masik vertex mar a kuszobon belulre kerul

	USize origNVertices = nVertices;

	for (UIndex iContour = 1; iContour <= nContours; ++iContour) {
		UIndex iFirstContourVertex = iContour == 1 ? 1 : contourEnds[iContour - 1] + 1;
		if (contourEnds[iContour] <= iFirstContourVertex) {
			DBBREAK ();
			continue;
		}

		for (UIndex iVertex = contourEnds[iContour] - 1; iVertex >= iFirstContourVertex; --iVertex) {
			if (IsEqualCoord (vertices[iVertex], vertices [iVertex + 1], minEdgeLength)) {
				DeleteVertexFromInternalData (iVertex);
			}
		}
	}

	for (UIndex iArc = 1; iArc <= nArcs; ++iArc) {
		double	angle	= Angle(arcs[iArc].arcAngle).GetValue ();
		Point2D	begC	= vertices[arcs[iArc].begIndex];
		Point2D	endC	= vertices[arcs[iArc].endIndex];

		if (IsNear (angle, 0.0, minArcAngle) ||
			IsNear (angle, 2.0 * PI, minArcAngle) ||
			IsNear (angle, -2.0 * PI, minArcAngle) ||
			IsEqualCoord (begC, endC, 2.0 * Eps))
		{
			arcs.Delete (iArc);
			--nArcs;
			--iArc;
#ifdef CHECKED_VERSION
		} else {
			Point2D origo;
			DBASSERT (ArcGetOrigo (&begC, &endC, angle, &origo));
#endif // DEBUVERS
		}
	}

	FixingContours ();

	if (origNVertices != nVertices) {
		UpdateBoundingBox ();
	}
	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>	//	ez duplikalva van a CorePolyline2D-ben
class CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ArrayRangeRotator {
public:
	template<class Array>
	static void Rotate (Array& array, UIndex iStart, UIndex iNewStart, UIndex iEnd)
	{
		Array tmp;
		tmp.SetCapacity (iNewStart - iStart);
		for (UIndex iSrc = iStart; iSrc < iNewStart; ++iSrc)
			tmp.Push (array[iSrc]);
		UIndex iDst = iStart;
		for (UIndex iSrc = iNewStart; iSrc < iEnd; ++iSrc, ++iDst)
			array[iDst] = array[iSrc];
		for (UIndex iSrc = 0; iSrc < tmp.GetSize (); ++iSrc, ++iDst)
			array[iDst] = tmp[iSrc];
	}
};

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RotateVerticeIndicesInContour (UIndex iContourToRotate, UIndex iVertexToFirst)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	iVertexToFirst = VertexIdx2InternalVertexIdx (iVertexToFirst);

	const UIndex iFirstVertex	= contourEnds[iContourToRotate - 1] + 1;
	const UIndex iLastVertex	= contourEnds[iContourToRotate];

	if (iFirstVertex == iVertexToFirst || iVertexToFirst == iLastVertex)
		return;

	if (DBERROR (!(iFirstVertex < iVertexToFirst && iVertexToFirst < iLastVertex)))
		throw GeometryIllegalArgumentException();

	ArrayRangeRotator::Rotate (vertices, iFirstVertex, iVertexToFirst, iLastVertex);
	vertices[iLastVertex] = vertices[iFirstVertex];
	for (UIndex i = 1; i < arcs.GetSize (); ++i) {
		if (iFirstVertex <= arcs[i].begIndex && arcs[i].begIndex < iVertexToFirst) {
			arcs[i].begIndex += iLastVertex - iVertexToFirst;
			arcs[i].endIndex += iLastVertex - iVertexToFirst;
		} else if (iVertexToFirst <= arcs[i].begIndex && arcs[i].begIndex < iLastVertex) {
			arcs[i].begIndex -= iVertexToFirst - iFirstVertex;
			arcs[i].endIndex -= iVertexToFirst - iFirstVertex;
		}
	}
	if (flags.isVertexUserData) {
		ArrayRangeRotator::Rotate (vertexInfos, iFirstVertex, iVertexToFirst, iLastVertex);
		vertexInfos[iLastVertex] = vertexInfos[iFirstVertex];
	}
	if (flags.isEdgeUserData) {
		ArrayRangeRotator::Rotate (inhEdgeInfos, iFirstVertex, iVertexToFirst, iLastVertex);
		inhEdgeInfos[iLastVertex] = inhEdgeInfos[iFirstVertex];
	}

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SwapContourOrder (const GS::Array<UIndex>& newContourOrder)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	//	Parameter check
	if (DBERROR (newContourOrder.GetSize () != nContours))
		throw GeometryIllegalArgumentException();

	if (DBERROR (newContourOrder[0] != 1))
		throw GeometryIllegalArgumentException();

	for (UIndex i = 0; i < nContours; ++i)
	{
		if (DBERROR (!(0 < newContourOrder[i] && newContourOrder[i] <= nContours)))
			throw GeometryIllegalArgumentException();

		for (UIndex ii = i + 1; ii < nContours; ++ii)
			if (DBERROR (newContourOrder[ii] == newContourOrder[i]))
				throw GeometryIllegalArgumentException();
	}

	//	Store contours
	GS::ArrayFB<ContourForSwap<VertexUserData, EdgeUserData, ContourUserData>, 6> tmpContours;
	tmpContours.SetSize (nContours + 1);
	for (UIndex iContour = 1; iContour <= nContours; ++iContour) {
		ContourForSwap<VertexUserData, EdgeUserData, ContourUserData>& contour = tmpContours[iContour];

		const UIndex iFirstVertex	= contourEnds[iContour - 1] + 1;
		const UIndex iLastVertex	= contourEnds[iContour];

		contour.nVertices = iLastVertex - iFirstVertex + 1;

		contour.vertices.SetSize (contour.nVertices);
		for (UIndex i = 0; i < contour.nVertices; ++i)
			contour.vertices[i] = vertices[iFirstVertex + i];

		if (flags.isVertexUserData) {
			contour.vertexInfos.SetSize (contour.nVertices);
			for (UIndex i = 0; i < contour.nVertices; ++i)
				contour.vertexInfos[i] = vertexInfos[iFirstVertex + i];
		}

		for (UIndex i = 1; i < nArcs; ++i) {
			if (iFirstVertex <= arcs[i].begIndex && arcs[i].begIndex < iLastVertex) {
				++contour.nArcs;
				PolyArcRec tmpArc;
				tmpArc.begIndex = arcs[i].begIndex - iFirstVertex;
				tmpArc.endIndex = arcs[i].endIndex - iFirstVertex;
				tmpArc.arcAngle = arcs[i].arcAngle;
				contour.arcs.Push (tmpArc);
			}
		}

		if (flags.isEdgeUserData) {
			contour.inhEdgeInfos.SetSize (contour.nVertices);
			for (UIndex i = 0; i < contour.nVertices; ++i)
				contour.inhEdgeInfos[i] = inhEdgeInfos[iFirstVertex + i];
		}

		if (flags.isContourUserData) {
			contour.contourInfo = contourInfos[iContour];
		}
	}

	//	Write contours
	USize tmpNArcs = 0;
	for (UIndex iContour = 1; iContour <= nContours; ++iContour) {
		const ContourForSwap<VertexUserData, EdgeUserData, ContourUserData>& contour = tmpContours[newContourOrder[iContour - 1]];

		contourEnds[iContour] = contourEnds[iContour - 1] + contour.nVertices;

		const UIndex iFirstVertex = contourEnds[iContour - 1] + 1;

		for (UIndex i = 0; i < contour.nVertices; ++i)
			vertices[iFirstVertex + i] = contour.vertices[i];

		if (flags.isVertexUserData) {
			for (UIndex i = 0; i < contour.nVertices; ++i)
				vertexInfos[iFirstVertex + i] = contour.vertexInfos[i];
		}

		for (UIndex i = 0; i < contour.nArcs; ++i) {
			PolyArcRec tmpArc;
			tmpArc.begIndex = contour.arcs[i].begIndex + iFirstVertex;
			tmpArc.endIndex = contour.arcs[i].endIndex + iFirstVertex;
			tmpArc.arcAngle = contour.arcs[i].arcAngle;
			arcs[++tmpNArcs] = tmpArc;
		}

		if (flags.isEdgeUserData) {
			for (UIndex i = 0; i < contour.nVertices; ++i)
				inhEdgeInfos[iFirstVertex + i] = contour.inhEdgeInfos[i];
		}

		if (flags.isContourUserData) {
			contourInfos[iContour] = contour.contourInfo;
		}
	}

	DBCHECKCOREPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SortArcsByIndices (void)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	class ArcSorter {
	public:
		static CmpResult Cmp (const PolyArcRec& op1, const PolyArcRec& op2)
		{
			return (op1.begIndex < op2.begIndex);
		}
	};
	GS::Sort (arcs.Begin (), arcs.End (), ArcSorter::Cmp);

	DBCHECKCOREPOLY_CHECK;
}


//Create new polygons

//Ha az iveket torzitani kellene, akkor felszegmentalja oket
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	if (tran.IsIdentity ()) {
		return ResultSameAsThis;
	}
	if (IsEmpty ()) {
		return ResultSameAsThis;
	}

	bool needSegment = nArcs > 0 && arcs.GetSize () > 1 && !Geometry::TMIsPreserveArc (tran);
	 //Akkor kell regularizalni, ha eredetileg is regularis volt
	bool needRegularize = status.isRegularized && needSegment;
	if ( (arcDivParams.maxDifference != 0.0 || arcDivParams.boxToKeepMaxDifferenceIn != nullptr) && needSegment) {
		if (status.isRegularized) {
			//Ilyenkor a SegmentUp regularizal, nem kell ujbol regularizalni
			SegmentUp (arcDivParams, result); //A visszateresi erteket nem kell vizsgalni, mert nArcs > 0
			needRegularize = false;
		} else {
			GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
			tmpPoly->SegmentUp (arcDivParams);
			result.Push (tmpPoly);
		}
	} else {
		result.Push (new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this));
	}

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		for (UIndex vertexIdx = 1; vertexIdx <= result[idx]->nVertices; vertexIdx++) {
			result[idx]->vertices[vertexIdx] = Geometry::Transform2dPoint (tran, result[idx]->vertices[vertexIdx]);
		}

		if (result[idx]->arcs.GetSize () > 1 && (tran.HasMirror ())) {
			for (UIndex arcIdx = 1; arcIdx <= result[idx]->nArcs; arcIdx++)
				result[idx]->arcs[arcIdx].arcAngle *= -1;
		}
		if (result[idx]->status.isRegularized) {
			//Csak akkor kell rendbetenni a koruljarasi iranyt, ha eredetileg regularizalt volt
			if (tran.HasMirror ()) {
				if (!needRegularize) {
					result[idx]->status.isRegularized = false;
					result[idx]->UpdateOrientation ();
					result[idx]->status.isRegularized = true;
				}
			}
		}
		result[idx]->UpdateBoundingBox ();
	}
	if (needRegularize) {
		//Erre csak akkor van szukseg, ha eredetileg regularis volt es nem lett segmentalva
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > irregularPolygons = result;
		result.Clear (true);
		for (UIndex idx = 0; idx < irregularPolygons.GetSize (); idx++) {
			irregularPolygons[idx]->status.isRegularized = false;
			GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > regularizedPolygons;
			if (irregularPolygons[idx]->Regularize (regularizedPolygons) == ResultSameAsThis) {
				DBASSERT (regularizedPolygons.GetSize () == 0);
				result.Push (irregularPolygons[idx]);
			} else {
				for (UIndex regIdx = 0; regIdx < regularizedPolygons.GetSize (); regIdx++) {
					result.Push (regularizedPolygons [regIdx]);
				}
			}
		}
	}
	DBCHECKCOREPOLY_CHECKRESULT;

	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& filterWithPolygon,
													   const ArcDivParams& arcDivParams,
													   const TRANMAT& tran,
													   GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result,
													   bool& isTransformedAll) const
{
	if (tran.IsIdentity ()) {
		return ResultSameAsThis;
	}
	if (IsEmpty ()) {
		return ResultSameAsThis;
	}

	isTransformedAll = true;
	bool needSegment = nArcs > 0 && arcs.GetSize () > 1 && !Geometry::TMIsPreserveArc (tran);
	GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > segmentedPolygons;
	if ( (arcDivParams.maxDifference != 0.0 || arcDivParams.boxToKeepMaxDifferenceIn != nullptr) && needSegment) {
		SegmentUp (arcDivParams, segmentedPolygons); //A visszateresi erteket nem kell vizsgalni, mert nArcs > 0
		needSegment = false;
	} else {
		segmentedPolygons.Push (new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this));
	}

	bool currentIsTransformedall = true;
	for (UIndex idx = 0; idx < segmentedPolygons.GetSize (); idx++) {
		currentIsTransformedall = true;
		for (UIndex vertexIdx = 1; vertexIdx <= segmentedPolygons[idx]->nVertices; vertexIdx++) {
			RelativePosition relpos = filterWithPolygon.GetPosition (segmentedPolygons[idx]->vertices[vertexIdx], Boundary_Closed);
			if (IsOverlap (relpos))
				segmentedPolygons[idx]->vertices[vertexIdx] = Geometry::Transform2dPoint (tran, segmentedPolygons[idx]->vertices[vertexIdx]);
			else
				currentIsTransformedall = false;
		}

		if (segmentedPolygons[idx]->arcs.GetSize () > 1 && tran.HasMirror ()) {
			for (UIndex arcIdx = 1; arcIdx <= segmentedPolygons[idx]->nArcs; arcIdx++) {
				RelativePosition relpos1 = filterWithPolygon.GetPosition (segmentedPolygons[idx]->vertices[segmentedPolygons[idx]->arcs[arcIdx].begIndex], Boundary_Closed);
				RelativePosition relpos2 = filterWithPolygon.GetPosition (segmentedPolygons[idx]->vertices[segmentedPolygons[idx]->arcs[arcIdx].endIndex], Boundary_Closed);
				if (IsOverlap (relpos1) && IsOverlap (relpos2))
					segmentedPolygons[idx]->arcs[arcIdx].arcAngle *= -1.0;
			}
		}

		if (tran.HasMirror ())
			segmentedPolygons[idx]->UpdateOrientation ();
		segmentedPolygons[idx]->UpdateBoundingBox ();

		if (!currentIsTransformedall || needSegment) {
			segmentedPolygons[idx]->status.isRegularized = false;
			GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > regularizedResult;
			if (segmentedPolygons[idx]->Regularize (regularizedResult) == ResultSameAsThis) {
				DBASSERT (regularizedResult.GetSize () == 0);
				result.Push (segmentedPolygons[idx]);
			} else {
				for (UIndex polyIdx = 0; polyIdx < regularizedResult.GetSize (); polyIdx++) {
					result.Push (regularizedResult[polyIdx]);
				}
			}
		} else {
			segmentedPolygons[idx]->status.isRegularized = true;
			result.Push (segmentedPolygons[idx]);
		}
		if (!currentIsTransformedall)
			isTransformedAll = false;
	}
	DBCHECKCOREPOLY_CHECKRESULT;

	//Ezutan mar nincs szukseg regularizalasra. A SegmentUp regularizal ha kell a koordinata transzformalas utan pedig nincs szukseg regularizalasra
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& filterPolygonArray,
													   const ArcDivParams& arcDivParams,
													   const TRANMAT& tran,
													   GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result,
													   bool& isTransformedAll) const
{
	if (tran.IsIdentity ()) {
		return ResultSameAsThis;
	}
	if (IsEmpty ()) {
		return ResultSameAsThis;
	}

	isTransformedAll = true;
	bool needSegment = nArcs > 0 && arcs.GetSize () > 1 && !Geometry::TMIsPreserveArc (tran);
	GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > segmentedPolygons;
	if ( (arcDivParams.maxDifference != 0.0 || arcDivParams.boxToKeepMaxDifferenceIn != nullptr) && needSegment) {
		SegmentUp (arcDivParams, segmentedPolygons); //A visszateresi erteket nem kell vizsgalni, mert nArcs > 0
	} else {
		segmentedPolygons.Push (new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this));
	}

	bool currentIsTransformedall = true;
	for (UIndex idx = 0; idx < segmentedPolygons.GetSize (); idx++) {
		currentIsTransformedall = true;
		for (UIndex vertexIdx = 1; vertexIdx <= segmentedPolygons[idx]->nVertices; vertexIdx++) {
			RelativePosition relpos = CorePolygon2D::GetPosition (filterPolygonArray, segmentedPolygons[idx]->vertices[vertexIdx], Boundary_Closed);
			if (IsOverlap (relpos))
				segmentedPolygons[idx]->vertices[vertexIdx] = Geometry::Transform2dPoint (tran, segmentedPolygons[idx]->vertices[vertexIdx]);
			else
				currentIsTransformedall = false;
		}

		if (segmentedPolygons[idx]->arcs.GetSize () > 1 && tran.HasMirror ()) {
			for (UIndex arcIdx = 1; arcIdx <= segmentedPolygons[idx]->nArcs; arcIdx++) {
				RelativePosition relpos1 = CorePolygon2D::GetPosition (filterPolygonArray, segmentedPolygons[idx]->vertices[segmentedPolygons[idx]->arcs[arcIdx].begIndex], Boundary_Closed);
				RelativePosition relpos2 = CorePolygon2D::GetPosition (filterPolygonArray, segmentedPolygons[idx]->vertices[segmentedPolygons[idx]->arcs[arcIdx].endIndex], Boundary_Closed);
				if (IsOverlap (relpos1) && IsOverlap (relpos2))
					segmentedPolygons[idx]->arcs[arcIdx].arcAngle *= -1.0;
			}
		}
		if (tran.HasMirror ())
			segmentedPolygons[idx]->UpdateOrientation ();
		segmentedPolygons[idx]->UpdateBoundingBox ();

		if (!currentIsTransformedall || needSegment) {
			segmentedPolygons[idx]->status.isRegularized = false;
			GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > regularizedResult;
			if (segmentedPolygons[idx]->Regularize (regularizedResult) == ResultSameAsThis) {
				DBASSERT (regularizedResult.GetSize () == 0);
				result.Push (segmentedPolygons[idx]);
			} else {
				for (UIndex polyIdx = 0; polyIdx < regularizedResult.GetSize (); polyIdx++) {
					result.Push (regularizedResult[polyIdx]);
				}
			}
		} else {
			segmentedPolygons[idx]->status.isRegularized = true;
			result.Push (segmentedPolygons[idx]);
		}
		if (!currentIsTransformedall)
			isTransformedAll = false;
	}
	DBCHECKCOREPOLY_CHECKRESULT;

	//Ezutan mar nincs szukseg regularizalasra. A SegmentUp regularizal ha kell a koordinata transzformalas utan pedig nincs szukseg regularizalasra
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentUp (const ArcDivParams& arcDivParams, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{

	if (nArcs <= 0 || arcs.GetSize () <= 1) {
		return ResultSameAsThis;
	}

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this, true);

	try {
		GS::ArrayFB< GS::Array<Point2D>, 6> segmentedArcs;
		USize numOfSegmentedVertex = 0;
		FillSegmentedArc (arcDivParams, segmentedArcs, numOfSegmentedVertex);
		tmpPoly->CopyPolygonLevelDataFrom (*this);
		tmpPoly->AllocateInternalData (0, 0, 0, nVertices + numOfSegmentedVertex  /*nVertices*/, 0 /*nArcs*/, nContours /*nContours*/); //Egyesevel adjuk hozza a vertexeket es contourokat
		SetSegmentUp (tmpPoly, segmentedArcs);
	} catch (const std::exception&) {
		ThrowGeometryExceptionAtError (Error, "CorePolygon2D::SegmentUp", __FILE__, __LINE__);
	} catch (const GS::Exception& e) {
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolygon2D::SegmentUp", __FILE__, __LINE__);
	}

	tmpPoly->UpdateBoundingBox ();

	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
		DBASSERT (result.GetSize () == 0);
		result.Push (tmpPoly);
	}

	return NewPolygons;
}
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EliminateArcs (GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	if (nArcs <= 0 || arcs.GetSize () <= 1) {
		return ResultSameAsThis;
	}
	if (nVertices <= 3) {
		return EmptyPolygon;
	}

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);

	tmpPoly->EliminateArcs ();

	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
		DBASSERT (result.GetSize () == 0);
		result.Push (tmpPoly);
	}
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetContour (UIndex contourIdx, double offset, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBASSERT (status.isRegularized);
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyResizeContourExt (&polyExt1, contourIdx, offset, &resPolyExt);
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz

	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::OffsetContour", __FILE__, __LINE__);


	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetEdge (UIndex edgeIdx, double offset, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBASSERT (status.isRegularized);
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyOffsetEdgeExt (&polyExt1, edgeIdx, offset, &resPolyExt);
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::OffsetEdge", __FILE__, __LINE__);


	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetEdgeFixArea (UIndex edgeIdx, UIndex vertexIndex, double offset, double area, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBASSERT (status.isRegularized);
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	DBCHECKINDEX_COREPOLY(vertexIndex, 1, GetVertexNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	vertexIndex = VertexIdx2InternalVertexIdx (vertexIndex);

	GSErr errorCode = NoError;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyOffsetEdgeFixAreaExt (&polyExt1, edgeIdx, vertexIndex, offset, area, &resPolyExt);
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::OffsetEdgeFixArea", __FILE__, __LINE__);

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MoveVertex (UIndex vertexIdx, const Point2D& newPosition, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	vertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);
	GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyMoveVertexExt (&polyExt1, vertexIdx, newPosition, &resPolyExt);
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::MoveVertex", __FILE__, __LINE__);

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletAllVertex (const double filletRadius, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBASSERT (status.isRegularized);
	GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyFilletContourExt (&polyExt1, 0, filletRadius, &resPolyExt);
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::FilletAllVertex", __FILE__, __LINE__);

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletVertex (UIndex vertexIdx, const double filletRadius, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBASSERT (status.isRegularized);
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	vertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);
	GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyFilletVertexExt (&polyExt1, vertexIdx, filletRadius, &resPolyExt);
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::FilletVertex", __FILE__, __LINE__);

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletVertexInContour (UIndex contourIdx, const double filletRadius, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBASSERT (status.isRegularized);
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyFilletContourExt (&polyExt1, contourIdx, filletRadius, &resPolyExt);
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::FilletVertexInContour", __FILE__, __LINE__);

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferAllVertex (const double chamferRadius, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBASSERT (status.isRegularized);

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	Geometry::PGPolyChamferContourExt (&polyExt1, 0, chamferRadius, &resPolyExt);

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferVertex (UIndex vertexIdx, const double chamferRadius, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBASSERT (status.isRegularized);
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	vertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);
	GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyChamferVertexExt (&polyExt1, vertexIdx, chamferRadius, &resPolyExt);
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::ChamferVertex", __FILE__, __LINE__);

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferVertexInContour (UIndex contourIdx, const double chamferRadius, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBASSERT (status.isRegularized);
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	[[maybe_unused]] GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyChamferContourExt (&polyExt1, contourIdx, chamferRadius, &resPolyExt);
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::ChamferVertexInContour", __FILE__, __LINE__);

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetEdgesInContour (const UIndex contourIdx, const GS::HashTable<UIndex, double>& offsets, const bool multiEdgeOffset, GS::SharedPtr<CorePolygon2D>& result) const
{
	try {
		result = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
		result->status.isRegularized = false;

		const UIndex begContourIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endContourIdx = GetInternalVertexEndIdxInContour (contourIdx) - 1;
		GS::Array<Point2D>	movedPts (endContourIdx - begContourIdx + 1);

		GS::HashTable<UIndex, double> offsetsCopy (offsets);

		// for all vertices in the contour
		for (UIndex iVertex = begContourIdx; iVertex <= endContourIdx; iVertex++) {
			const UIndex prevEdge = (iVertex == begContourIdx) ? endContourIdx : iVertex - 1;
			Curve2DData	prevCurve, offsetedPrevCurve;
			Curve2DData nextCurve, offsetedNextCurve;

			result->GetEdgeAsCurve2DData (prevEdge, prevCurve);
			if (IsCurve2DDataStraight (prevCurve)) {
				prevCurve.type = CURVE2D_Line;
			} else {
				prevCurve.type = CURVE2D_Circle;	// even it is a circle, but the isRevoriented flag is important!!!
			}

			result->GetEdgeAsCurve2DData (iVertex, nextCurve);
			if (IsCurve2DDataStraight (nextCurve)) {
				nextCurve.type = CURVE2D_Line;
			} else {
				nextCurve.type = CURVE2D_Circle;	// even it is a circle, but the isRevoriented flag is important!!!
			}

			const double prevEdgeOffset = offsetsCopy.ContainsKey (prevEdge) ? offsetsCopy.Get (prevEdge) :  0.0;
			const double nextEdgeOffset = offsetsCopy.ContainsKey (iVertex) ? offsetsCopy.Get (iVertex) :  0.0;

			Point2D newVertexPosition;
			GetGivenDistantPointResult getGivenDistantPointResult = GetGivenDistantPoint   (prevCurve,
																							prevEdgeOffset,
																							nextCurve,
																							nextEdgeOffset,
																							result->vertices[iVertex],
																							&newVertexPosition,
																							&offsetedPrevCurve,
																							&offsetedNextCurve);

			if (getGivenDistantPointResult == DistantPointSuccess) {
				movedPts.Push (newVertexPosition);
			} else if (multiEdgeOffset && getGivenDistantPointResult == DistantPointNoIntersection) {
				// create a nu edge if possibru

				if (nextCurve.type == CURVE2D_Circle)
					nextCurve.type = CURVE2D_GenArc;
				if (prevCurve.type == CURVE2D_Circle)
					prevCurve.type = CURVE2D_GenArc;
				if (offsetedPrevCurve.type == CURVE2D_Circle)
					offsetedPrevCurve.type = CURVE2D_GenArc;
				if (offsetedNextCurve.type == CURVE2D_Circle)
					offsetedNextCurve.type = CURVE2D_GenArc;

				result->InsertVertexInternal (iVertex, GetCurve2DDataBegPosition (nextCurve), true, true);
				if (result->inhEdgeInfos.GetSize () != 0 && result->flags.isEdgeUserData) {
					result->inhEdgeInfos[iVertex] = result->defaultEdgeData;
				}

				movedPts.Push (GetCurve2DDataEndPosition (offsetedPrevCurve));
				movedPts.Push (GetCurve2DDataBegPosition (offsetedNextCurve));
				GS::HashTable<UIndex, double> tmp;
				for (auto it : offsetsCopy) {
					if (it.key < iVertex)
						tmp.Add (it.key, it.value);
					else
						tmp.Add (it.key + 1, it.value);
				}
				offsetsCopy.Swap (tmp);
				++endContourIdx;
				++iVertex;
				getGivenDistantPointResult = DistantPointSuccess;
			}

			if (getGivenDistantPointResult != DistantPointSuccess) {
				if (contourIdx == 1) {
					return EmptyPolygon;
				}
				result->DeleteHole (contourIdx);
				DBCHECKCOREPOLY_CHECKRESULT_SINGLE;
				return NewPolygons;
			}
		}

		// *** check for reversed edges ***
		// it is an interesting thing: if the poly is "turnes out"
		// while resizing, its orientation will remain right
		// but the direction of the individual edges will swap

		// We will investigate all the edges for robustness
		ULong rightCount = 0;
		ULong wrongCount = 0;
		for (UIndex iVertex = begContourIdx; iVertex <= endContourIdx; iVertex++) {

			UIndex iNextVertex = (iVertex + 1 <= endContourIdx) ? iVertex + 1 : begContourIdx;
			const Point2D& newBegVertexPos = movedPts [iVertex - begContourIdx];
			const Point2D& newEndVertexPos = movedPts [iNextVertex - begContourIdx];
			Vector2D newDir = UnitVector (newEndVertexPos - newBegVertexPos);

			const Point2D& oldBegVertexPos = result->vertices[iVertex];
			const Point2D& oldEndVertexPos = result->vertices[iNextVertex];
			Vector2D oldDir = UnitVector (oldEndVertexPos - oldBegVertexPos);

			//fgy 2003.12.01 ERR#25254
			Vector2D sum = newDir + oldDir;
			double sumLen = sum.GetLength ();
			if (IsGreater (sumLen, 1.0)) {
				rightCount++;
			} else {
				wrongCount++;
			}
		}

		// if it is turned out, then del
		if (wrongCount >= rightCount) {
			if (contourIdx == 1) {
				return EmptyPolygon;
			}
			result->DeleteHole (contourIdx);
			DBCHECKCOREPOLY_CHECKRESULT_SINGLE;
			return NewPolygons;
		}

		// make the move
		Sector tmpSector;
		GenArc tmpGenArc;
		for (UIndex iVertex = begContourIdx; iVertex <= endContourIdx; iVertex++) {
			const Point2D& newVertexPosition = movedPts [iVertex - begContourIdx];
			UIndex nextVertIdx = (iVertex == endContourIdx) ? begContourIdx : iVertex + 1;
			if (result->GetSector (result->InternalVertexIdx2VertexIdx (iVertex), tmpSector, tmpGenArc)) {
				const Point2D& nextNewVertexPosition = movedPts [nextVertIdx - begContourIdx];
				double begAng = ComputeFi (tmpGenArc.GetOrigo (), newVertexPosition);
				double endAng = ComputeFi (tmpGenArc.GetOrigo (), nextNewVertexPosition);
				double fi = 0.0;
				if (!tmpGenArc.IsReflected ())
					fi = SubAngle (endAng, begAng);
				else
					fi = -SubAngle (begAng, endAng);
				result->SetEdgeAngleInternal (iVertex, fi);
			}
			result->vertices[iVertex] = newVertexPosition;		// mi a PG-s hez kepest elobb frissitjuk az edge angle-t,
																// mert kulonben rossz lesz az origC
		}

		result->vertices[endContourIdx + 1] = result->vertices[begContourIdx];

		if (result->flags.isVertexUserData)
			result->vertexInfos [endContourIdx + 1] = result->vertexInfos[begContourIdx];

		if (result->flags.isEdgeUserData)
			result->inhEdgeInfos [endContourIdx + 1] = result->inhEdgeInfos[begContourIdx];

		result->UpdateBoundingBox ();
	} catch (const GS::GSException& e) {
		e.Print (dbChannel);
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolygon2D::OffsetEdgesInContour", __FILE__, __LINE__);
	}

	if (result->nVertices <= 1) {
		DBBREAK (); //elofordulhat ilyen?
		//ilyenkor egy ures polygon-t adunk vissza
		result = nullptr;
		return EmptyPolygon;
	}

	DBCHECKCOREPOLY_CHECKRESULT_SINGLE;
	return NewPolygons;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetContour (UIndex contourIdx, double offset, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	if (IsNearZero (offset, Eps))
		return ResultSameAsThis;

	try {
		// ezt az ivek miatt ugy kellene csinalni, hogy megnezzuk,
		// mennyi az az offset, amit minden csucs enged, es megjegyezzuk
		// a szuk keresztmetszeteket - amik miatt nem lehet tobb az offset -
		// ket egyenes elnel a max. mindig a vegtelen.
		//
		// ha ez Eps, akkor kiiktatjuk a gatlo eleket, es ujraszamoljuk a maxot.
		//
		// egyebkent elvegezzuk az offset-et a min (offset, possibleOffset) offset-tel
		// ha meg nem eleg, akkor most is kidobjuk a gatlo eleket, es mehet elolrol az
		// egesz

		const UIndex begContourIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		const UIndex endContourIdx = GetInternalVertexEndIdxInContour (contourIdx) - 1;

		// strange thing because of the opposite direction of main contour and the holes
		if (HasPositiveOrientation (contourIdx))
			offset *= -1.0;

		for (UIndex iVertex = begContourIdx; iVertex <= endContourIdx; ++iVertex) {
			double vertMaxOffset = 0.0;
			UIndex prevEdge = (iVertex == begContourIdx) ? endContourIdx : iVertex - 1;
			Curve2DData	prevCurve;
			Curve2DData nextCurve;

			GetEdgeAsCurve2DData (prevEdge, prevCurve);
			if (IsCurve2DDataStraight (prevCurve)) {
				prevCurve.type = CURVE2D_Line;
			} else {
				prevCurve.type = CURVE2D_Circle;	// even it is a circle, but the isRevoriented flag is important!!!
			}

			GetEdgeAsCurve2DData (iVertex, nextCurve);
			if (IsCurve2DDataStraight (nextCurve)) {
				nextCurve.type = CURVE2D_Line;
			} else {
				nextCurve.type = CURVE2D_Circle;	// even it is a circle, but the isRevoriented flag is important!!!
			}

			GetMaxOffsetValue (prevCurve, nextCurve, offset, &vertMaxOffset);

			if (offset < 0.0) {
				offset = MAX (offset, vertMaxOffset);
			} else {
				offset = MIN (offset, vertMaxOffset);
			}
		}

		GS::HashTable<UIndex, double> edgesToOffset;
		for (UIndex i = begContourIdx; i <= endContourIdx; ++i)
			edgesToOffset.Add (i, offset);

		return OffsetEdgesInContour (contourIdx, edgesToOffset, false /*multiEdgeOffset*/, result);
	} catch (const GS::GSException& e) {
		e.Print (dbChannel);
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolygon2D::OffsetContour", __FILE__, __LINE__);
	}

	DBBREAK ();
	return EmptyPolygon;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetEdge (UIndex edgeIdx, double offset, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());

	if (IsNearZero (offset, Eps))
		return ResultSameAsThis;

	try {
		result = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
		result->status.isRegularized = false;

		edgeIdx = result->VertexIdx2InternalVertexIdx (edgeIdx);

		Sector tmpSector;
		GenArc tmpGenArc;

		/* initializing the variables */
		UIndex contourIdx = result->GetContourIdxFromInternalVertexIdx (edgeIdx);
		UIndex begContourIdx = result->GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endContourIdx = result->GetInternalVertexEndIdxInContour (contourIdx) - 1;

		if (result->HasPositiveOrientation (contourIdx))
			offset *= -1.0;

		// The meaning of the offset sign is always the following:
		// "+" means direction into INSIDE of the polygon
		// "-" means direction into OUTSIDE of the poligon
		// It means that this data itself is not enough to decide
		// whether an arc shrinks or grows.
		// If the arc is NORMAL (not reflected) then we should DECREASE it with the offset
		// If the arc is REFLECTED then we should INCREASE it with the offset

		UIndex prevEdgeIdx = (edgeIdx == begContourIdx) ? endContourIdx : edgeIdx - 1;
		UIndex nextEdgeIdx = (edgeIdx == endContourIdx) ? begContourIdx : edgeIdx + 1;

		// Set up auxiliary curves for the offseted edge form neighbouring edges
		Curve2DData	begXEdgeCurve;
		result->GetEdgeAsCurve2DData (prevEdgeIdx, begXEdgeCurve);
		UnitVector_2D begCurveEndDir = GetCurve2DDataEndDirection (begXEdgeCurve);
		if (IsCurve2DDataStraight (begXEdgeCurve)) {
			begXEdgeCurve.type = CURVE2D_Line;
		} else {
			begXEdgeCurve.type = CURVE2D_Circle;	// even it is a circle, but the isRevoriented flag is important!!!
		}

		Curve2DData	endXEdgeCurve;
		result->GetEdgeAsCurve2DData (nextEdgeIdx, endXEdgeCurve);
		UnitVector_2D endCurveBegDir = GetCurve2DDataBegDirection (endXEdgeCurve);
		if (IsCurve2DDataStraight (endXEdgeCurve)) {
			endXEdgeCurve.type = CURVE2D_Line;
		} else {
			endXEdgeCurve.type = CURVE2D_Circle;	// even it is a circle, but the isRevoriented flag is important!!!
		}

		Curve2DData	offsetEdgeCurve;
		result->GetEdgeAsCurve2DData (edgeIdx, offsetEdgeCurve);

		UnitVector_2D offsetCurveBegDir = GetCurve2DDataBegDirection (offsetEdgeCurve);
		UnitVector_2D offsetCurveEndDir = GetCurve2DDataEndDirection (offsetEdgeCurve);
		bool isBegParallel = fabs (GetDeflectionFromTo (begCurveEndDir, offsetCurveBegDir).GetValue (Degree)) < 10.0;
		bool isEndParallel = fabs (GetDeflectionFromTo (endCurveBegDir, offsetCurveEndDir).GetValue (Degree)) < 10.0;

		if (!isBegParallel && !isEndParallel) {
			offset = LimitOffsetToXNeigEdges (begXEdgeCurve, endXEdgeCurve, offsetEdgeCurve, offset);

			double maxBegOffset = offset;
			double maxEndOffset = offset;
			LimitOffsetForArc (begXEdgeCurve, endXEdgeCurve, offsetEdgeCurve, offset, &maxBegOffset, &maxEndOffset);
			if (offset < 0.0) {
				offset = MAX (offset, maxBegOffset);
				offset = MAX (offset, maxEndOffset);
			} else {
				offset = MIN (offset, maxBegOffset);
				offset = MIN (offset, maxEndOffset);
			}
		}
		// First, we will give the simple not adjusted offseted edge points
		// which can give an acceptable result
		// if all else fails (eg. poligons turning out)
		Curve2DData offsetEdgeCurveNewPos;
		OffsetCurve2DData (offsetEdgeCurve, offset, &offsetEdgeCurveNewPos, nullptr);
		Point2D	begNewPt = GetCurve2DDataBegPosition (offsetEdgeCurveNewPos);
		Point2D	endNewPt = GetCurve2DDataEndPosition (offsetEdgeCurveNewPos);

		if (IsCurve2DDataStraight (offsetEdgeCurve)) {
			offsetEdgeCurve.type = CURVE2D_Line;
		} else {
			offsetEdgeCurve.type = CURVE2D_Circle;	// even it is a circle, but the isRevoriented flag is important!!!
		}
		const Point2D	vert1Pt (result->vertices[edgeIdx]);
		const Point2D	vert2Pt (result->vertices[nextEdgeIdx]);

		// special case for the parallel edges
		if (isBegParallel) {
			result->InsertVertexSplitArc (prevEdgeIdx, vert1Pt);
			result->SetEdgeAngleInternal (prevEdgeIdx + 1, 0.0);

			// update indices
			++endContourIdx;
			if (prevEdgeIdx < edgeIdx) {
				edgeIdx++;	// edgeIdx cannot wrap in such case
			}
			if (prevEdgeIdx < nextEdgeIdx) {
				nextEdgeIdx++;	// edgeIdx cannot wrap in such case
			}
		} else {
			Point2D	begIntersectionPt (0.0, 0.0);
			if (GetGivenDistantPoint (begXEdgeCurve, 0.0, offsetEdgeCurve, offset, vert1Pt, &begIntersectionPt) == DistantPointSuccess) {
				begNewPt = begIntersectionPt;
			}
		}

		// special case for the parallel edges
		if (isEndParallel) {
			result->InsertVertexSplitArc (nextEdgeIdx, vert2Pt);
			result->SetEdgeAngleInternal (nextEdgeIdx, 0.0);

			// update indices
			++endContourIdx;
			if (nextEdgeIdx < edgeIdx) {
				edgeIdx++;	// edgeIdx cannot wrap in such case
			}
		} else {
			Point2D	endIntersectionPt (0.0, 0.0);
			if (GetGivenDistantPoint (endXEdgeCurve, 0.0, offsetEdgeCurve, offset, vert2Pt, &endIntersectionPt) == DistantPointSuccess) {
				endNewPt = endIntersectionPt;
			}
		}
		//
		// Itt jon maga a muvelet
		// moving the offseted edge to the desired position
		//
		UIndex begMovedEdgeIdx = edgeIdx;
		UIndex endMovedEdgeIdx = (edgeIdx == endContourIdx) ? begContourIdx : edgeIdx + 1;

		result->vertices[begMovedEdgeIdx] = begNewPt;
		result->vertices[endMovedEdgeIdx] = endNewPt;
		result->vertices[endContourIdx + 1] = result->vertices[begContourIdx];

		// calculate angle of previous edge
		UIndex beforeMovedEdgeIdx = (begMovedEdgeIdx == begContourIdx) ? endContourIdx : begMovedEdgeIdx - 1;
		if (result->GetSector (result->InternalVertexIdx2VertexIdx (beforeMovedEdgeIdx), tmpSector, tmpGenArc)) {
			double begAng = ComputeFi (begXEdgeCurve.genArc.GetOrigo (), result->vertices[beforeMovedEdgeIdx]);
			double endAng = ComputeFi (begXEdgeCurve.genArc.GetOrigo (), begNewPt);
			double fi = 0.0;
			if (!begXEdgeCurve.genArc.IsReflected ())
				fi = SubAngle (endAng, begAng);
			else
				fi = -SubAngle (begAng, endAng);
			result->SetEdgeAngleInternal (beforeMovedEdgeIdx, fi);
		}

		// calculate angle of offseted edge
		if (result->GetSector (result->InternalVertexIdx2VertexIdx (edgeIdx), tmpSector, tmpGenArc)) {
			double begAng = ComputeFi (offsetEdgeCurve.genArc.GetOrigo (), begNewPt);
			double endAng = ComputeFi (offsetEdgeCurve.genArc.GetOrigo (), endNewPt);
			double fi = 0.0;
			if (!offsetEdgeCurve.genArc.IsReflected ())
				fi = SubAngle (endAng, begAng);
			else
				fi = -SubAngle (begAng, endAng);
			result->SetEdgeAngleInternal (edgeIdx, fi);
		}

		// calculate angle of next edge
		UIndex afterMovedEdgeIdx = (endMovedEdgeIdx == endContourIdx) ? begContourIdx : endMovedEdgeIdx + 1;
		if (result->GetSector (result->InternalVertexIdx2VertexIdx (endMovedEdgeIdx), tmpSector, tmpGenArc)) {
			double begAng = ComputeFi (endXEdgeCurve.genArc.GetOrigo (), endNewPt);
			double endAng = ComputeFi (endXEdgeCurve.genArc.GetOrigo (), result->vertices[afterMovedEdgeIdx]);
			double fi = 0.0;
			if (!endXEdgeCurve.genArc.IsReflected ())
				fi = SubAngle (endAng, begAng);
			else
				fi = -SubAngle (begAng, endAng);
			result->SetEdgeAngleInternal (endMovedEdgeIdx, fi);
		}
		result->UpdateBoundingBox ();
	} catch (const GS::GSException& e) {
		e.Print (dbChannel);
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolygon2D::OffsetEdge", __FILE__, __LINE__);
	}

	if (result->nVertices <= 1) {
		DBBREAK (); //elofordulhat ilyen?
		//ilyenkor egy ures polygon-t adunk vissza
		result = nullptr;
		return EmptyPolygon;
	}

	DBCHECKCOREPOLY_CHECKRESULT_SINGLE;
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetMultipleEdges (const GS::Array<GS::Pair<UIndex, double> >& offsets, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	if (offsets.GetSize () == 0 || IsEmpty ())
		return ResultSameAsThis;

	bool	offsetsAreZero		= true;
	UIndex	contourIdx			= 0;
	GS::HashTable<UIndex, double> offsetsCopy;
	bool	hasPositiveOrientation = true;

	for (UIndex i = 0; i < offsets.GetSize (); ++i) {
		DBCHECKINDEX_COREPOLY(offsets[i].first, 1, GetEdgeNum ());

		const UIndex edgeIndex = VertexIdx2InternalVertexIdx (offsets[i].first);

		if (contourIdx == 0) {
			contourIdx = GetContourIdxFromInternalVertexIdx (edgeIndex);
			hasPositiveOrientation = HasPositiveOrientation (contourIdx);
		} else if (contourIdx != GetContourIdxFromInternalVertexIdx (edgeIndex)) {
			throw GeometryException ("OffsetMultipleEdges not all edge on same contour!", __FILE__, __LINE__);
		}

		if (offsetsAreZero && !IsNearZero (offsets[i].second, Eps))
			offsetsAreZero = false;

		if (hasPositiveOrientation)
			offsetsCopy.Add (edgeIndex, -offsets[i].second);
		else
			offsetsCopy.Add (edgeIndex, offsets[i].second);
	}

	if (offsetsAreZero)
		return ResultSameAsThis;

	return OffsetEdgesInContour (contourIdx, offsetsCopy, true /*multiEdgeOffset*/, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetEdgeFixArea (UIndex edgeIdx, UIndex vertexIndex, double offset, double area, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	DBCHECKINDEX_COREPOLY(vertexIndex, 1, GetVertexNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	vertexIndex = VertexIdx2InternalVertexIdx (vertexIndex);

	// if area is zero, we are done, return
	if (area < Eps)
		return ResultSameAsThis;

	// if polygon is not a rectangle, return
	if (GetEdgeNum () != 4)
		return ResultSameAsThis;

	if (nArcs != 0)
		return ResultSameAsThis;

	Vector2D v1 = vertices[2] - vertices[1];
	Vector2D v2 = vertices[3] - vertices[2];
	Vector2D v3 = vertices[4] - vertices[3];
	Vector2D v4 = vertices[1] - vertices[4];
	if (MulsVectors (v1, v2) > Eps)
		return ResultSameAsThis;
	if (MulsVectors (v2, v3) > Eps)
		return ResultSameAsThis;
	if (MulsVectors (v3, v4) > Eps)
		return ResultSameAsThis;
	if (MulsVectors (v4, v1) > Eps)
		return ResultSameAsThis;

	// offseting with fix area

	double rectA = Dist (vertices[1], vertices[2]);
	double rectB = Dist (vertices[2], vertices[3]);

	if (IsNearZero (rectA, Eps) || IsNearZero (rectB, Eps))
		return ResultSameAsThis;

	if (edgeIdx % 2 == 0)
		GS::Swap (rectA, rectB);

	double actArea = rectA * rectB;

	// if area is equal and offset is zero return
	if (IsNear (actArea, area, Eps) && IsNearZero (offset, Eps))
		return ResultSameAsThis;

	if (!IsNear (actArea, area, Eps))
		actArea = area;

	double newRectB = fabs (rectB + offset);
	if (IsNearZero (newRectB, Eps))
		return ResultSameAsThis;

	double newRectA = actArea / newRectB;
	if (IsNearZero (newRectA, Eps))
		return ResultSameAsThis;

	try {
		GS::ArrayFB<GS::Pair<UIndex, Point2D>, 4> newCoords;
		for (UIndex i = 0; i < 4; ++i) {
			UIndex index = (edgeIdx + i);
			if (index > 4)
				index -= 4;
			newCoords.Push (GS::Pair<UIndex, Point2D> (index, vertices[index]));
		}

		double offsetA = newRectA - rectA;
		double offsetB = -offset;

		Vector2D offsetVectorA = offsetA * UnitVector (newCoords[1].second - newCoords[0].second);
		Vector2D offsetVectorB = offsetB * UnitVector (newCoords[2].second - newCoords[1].second);

		if (vertexIndex == newCoords[3].first) {
			newCoords[0].second.x += offsetVectorB.x;	newCoords[0].second.y += offsetVectorB.y;
			newCoords[1].second.x += offsetVectorA.x;	newCoords[1].second.y += offsetVectorA.y;
			newCoords[1].second.x += offsetVectorB.x;	newCoords[1].second.y += offsetVectorB.y;
			newCoords[2].second.x += offsetVectorA.x;	newCoords[2].second.y += offsetVectorA.y;
		} else if (vertexIndex == newCoords[2].first) {
			newCoords[0].second.x -= offsetVectorA.x;	newCoords[0].second.y -= offsetVectorA.y;
			newCoords[0].second.x += offsetVectorB.x;	newCoords[0].second.y += offsetVectorB.y;
			newCoords[1].second.x += offsetVectorB.x;	newCoords[1].second.y += offsetVectorB.y;
			newCoords[3].second.x -= offsetVectorA.x;	newCoords[3].second.y -= offsetVectorA.y;
		}

		result = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
		result->status.isRegularized = false;

		for (UIndex i = 0; i < 4; ++i)
			result->vertices[newCoords[i].first] = newCoords[i].second;

		result->vertices[5] = result->vertices[1];

		result->UpdateBoundingBox ();
	} catch (const GS::GSException& e) {
		e.Print (dbChannel);
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolygon2D::OffsetEdgeFixArea", __FILE__, __LINE__);
	}

	DBCHECKCOREPOLY_CHECKRESULT_SINGLE;
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletAllVertex (const double filletRadius, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	return FilletChamferContour (0, filletRadius, true /*doFillet*/, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletVertex (UIndex vertexIdx, const double filletRadius, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	return FilletChamferVertex (vertexIdx, filletRadius, true /*doFillet*/, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletVertexInContour (UIndex contourIdx, const double filletRadius, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	return FilletChamferContour (contourIdx, filletRadius, true /*doFillet*/, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferAllVertex (const double chamferRadius, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	return FilletChamferContour (0, chamferRadius, false /*doFillet*/, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferVertex (UIndex vertexIdx, const double chamferRadius, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	return FilletChamferVertex (vertexIdx, chamferRadius, false /*doFillet*/, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferVertexInContour (UIndex contourIdx, const double chamferRadius, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 1, GetContourNum ());
	return FilletChamferContour (contourIdx, chamferRadius, false /*doFillet*/, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertNewVerticesAndDeleteOld  (UIndex filletChamferVertexIdx, const Point2D& begFilletChamferPosition, const Point2D& endFilletChamferPosition, UIndex begContourIdx,  UIndex endContourIdx, UIndex& prevVertIdx, bool isNextEdgeArc, const GenArc& nextEdgeArc, bool united1, bool united2, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	/* insert new vertices and delete old vertex */
	if (!united2) {
		result->InsertVertexSplitArc (filletChamferVertexIdx, endFilletChamferPosition);
		if (isNextEdgeArc) {
			double begAng = ComputeFi (nextEdgeArc.GetOrigo (), endFilletChamferPosition);
			double endAng = ComputeFi (nextEdgeArc.GetOrigo (), result->vertices[result->GetNextVertexIndex (result->GetNextVertexIndex (filletChamferVertexIdx))]);
			double fi = 0.0;
			if (!nextEdgeArc.IsReflected ())
				fi = SubAngle (endAng, begAng);
			else
				fi = -SubAngle (begAng, endAng);

			result->SetEdgeAngleInternal (result->GetNextVertexIndex (filletChamferVertexIdx), fi);
		}
	} else {
		if (prevVertIdx == endContourIdx)
			prevVertIdx = (prevVertIdx - 1 < begContourIdx) ? endContourIdx : prevVertIdx - 1;
	}

	result->DeleteVertex (result->InternalVertexIdx2VertexIdx (filletChamferVertexIdx));

	if (!united1) {
		result->InsertVertexSplitArc (prevVertIdx, begFilletChamferPosition);
	} else {
		prevVertIdx = result->GetPrevVertexIndex (prevVertIdx); // TT#19420
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletChamferVertex  (UIndex vertexIdx, const double filletChamferRadius, const bool doFillet, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());
	if (IsNearZero (filletChamferRadius, Eps))
		return ResultSameAsThis;

	try {
		result = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
		result->status.isRegularized = false;

		UIndex filletChamferVertexIdx = VertexIdx2InternalVertexIdx (vertexIdx);

		UIndex contourIdx = GetContourIdxFromInternalVertexIdx (filletChamferVertexIdx);
		UIndex begContourIdx = GetInternalVertexBeginIdxInContour (contourIdx);
		UIndex endContourIdx = GetInternalVertexEndIdxInContour (contourIdx) - 1;


		/* determining the three acting vertices */
		UIndex	prevVertIdx;
		UIndex	nextVertIdx;
		Point2D	actVertPt;
		Point2D	prevVertPt;
		Point2D	nextVertPt;

		prevVertIdx = (filletChamferVertexIdx - 1 < begContourIdx) ? endContourIdx : filletChamferVertexIdx - 1;
		nextVertIdx = (filletChamferVertexIdx + 1 > endContourIdx) ? begContourIdx : filletChamferVertexIdx + 1;

		prevVertPt = vertices[prevVertIdx];
		actVertPt  = vertices[filletChamferVertexIdx];
		nextVertPt = vertices[nextVertIdx];

		Point2D	filletChamferCircleCentrePt;
		Point2D	begFilletChamferPosition;
		Point2D	endFilletChamferPosition;

		/* collecting the needed data for the next function */
		Sector	prevEdgeSector;
		GenArc	prevEdgeArc;
		bool	isPrevEdgeArc        = GetSector (InternalVertexIdx2VertexIdx (prevVertIdx), prevEdgeSector, prevEdgeArc);
		Point2D	prevEdgeArcCentre    = prevEdgeArc.GetOrigo ();
		double	prevEdgeArcViewAngle = CalcRotFi (prevEdgeArc.GetBegAng (), prevEdgeArc.GetEndAng (), prevEdgeArc.IsReflected ());

		Sector	nextEdgeSector;
		GenArc	nextEdgeArc;
		bool	isNextEdgeArc        = GetSector (InternalVertexIdx2VertexIdx (filletChamferVertexIdx), nextEdgeSector, nextEdgeArc);
		Point2D	nextEdgeArcCentre    = nextEdgeArc.GetOrigo ();
		double	nextEdgeArcViewAngle = CalcRotFi (nextEdgeArc.GetBegAng (), nextEdgeArc.GetEndAng (), nextEdgeArc.IsReflected ());

		/* filtering out the wrong cases */
		if (IsEqualCoord (prevVertPt, actVertPt, Eps) ||
			(IsEqualCoord (prevVertPt, nextVertPt, Eps) && !isPrevEdgeArc && !isNextEdgeArc) ||
			IsEqualCoord (nextVertPt, actVertPt, Eps) ||
			filletChamferRadius <= Eps)
		{
			throw GS::LogicErrorException (doFillet ? "Filleting not possible!" : "Chamfering not possible!", __FILE__, __LINE__);
		}
		/* if the calculation of the centre of the arc of the new arced edge succeeded */
		double	newPrevEdgeArcViewAngle = 0.0;
		double	newNextEdgeArcViewAngle = 0.0;
		bool	united1 = false;
		bool	united2 = false;

		bool degen = false;
		if (GetCornerFilletCentre (
					&prevVertPt,				/* -> the three points      */
					&actVertPt,					/* -> 				      	*/
					&nextVertPt,				/* ->       				*/
					isPrevEdgeArc ? 1 : -1,		/* -> first circle index    */
					&prevEdgeArcCentre,			/* -> first centre, if any  */
					prevEdgeArcViewAngle,		/* -> first angle, if any   */
					isNextEdgeArc ? 1 : -1,		/* -> second circle index   */
					&nextEdgeArcCentre,			/* -> second centre, if any */
					nextEdgeArcViewAngle,		/* -> second angle, if any  */
					true,						/* -> first offset flag     */
					true,						/* -> second offset flag    */
					filletChamferRadius,		/* -> displacement          */
					true,						/* -> displ. dir. flag		*/
					&filletChamferCircleCentrePt,/* <- the new point		*/
					&degen) && !degen) {

			/* determine the beg and end point of the new edge */
			Sector s1 = Sector (prevVertPt, actVertPt);
			Sector s2 = Sector (actVertPt, nextVertPt);
			if (!isPrevEdgeArc)
				begFilletChamferPosition = CoordProjSector (filletChamferCircleCentrePt, s1);
			else
				begFilletChamferPosition = prevEdgeArcCentre +
										MulVector (
											UnitVector (filletChamferCircleCentrePt - prevEdgeArcCentre),
											Dist (actVertPt, prevEdgeArcCentre));
			if (!isNextEdgeArc)
				endFilletChamferPosition = CoordProjSector (filletChamferCircleCentrePt, s2);
			else
				endFilletChamferPosition = nextEdgeArcCentre +
										MulVector (
											UnitVector (filletChamferCircleCentrePt - nextEdgeArcCentre),
											Dist (actVertPt, nextEdgeArcCentre));

			/* determine the new viewangle of the two original edge */
			if (isPrevEdgeArc) {
				GetViewAngle (
					&prevEdgeArcCentre,
					&prevVertPt,
					&begFilletChamferPosition,
					prevEdgeArcViewAngle,
					isPrevEdgeArc ? 1 : -1,
					&newPrevEdgeArcViewAngle);
				GenArc newArc = Geometry::SetGenArc (prevVertPt, begFilletChamferPosition, newPrevEdgeArcViewAngle);
				double fi;
				if (!newArc.IsReflected ())
					fi = SubAngle (newArc.GetEndAng (), newArc.GetBegAng ());
				else
					fi = -SubAngle (newArc.GetBegAng (), newArc.GetEndAng ());

				result->SetEdgeAngleInternal (prevVertIdx, fi);
			}
			if (isNextEdgeArc) {
				GetViewAngle (
					&nextEdgeArcCentre,
					&endFilletChamferPosition,
					&nextVertPt,
					nextEdgeArcViewAngle,
					isNextEdgeArc ? 1 : -1,
					&newNextEdgeArcViewAngle);
			}
			/* coincidence tests */
			united1 = (Dist (prevVertPt, begFilletChamferPosition) <  Eps);
			united2 = (Dist (nextVertPt, endFilletChamferPosition) <  Eps);

			if (!isPrevEdgeArc) {
				if ((Dist (prevVertPt, actVertPt) < Dist (begFilletChamferPosition, actVertPt) -  Eps)) {
					throw GS::LogicErrorException (doFillet ? "Filleting not possible!" : "Chamfering not possible!", __FILE__, __LINE__);
				}
			} else {
				if (!united1) {
					if (((prevEdgeArcViewAngle > 0) && (newPrevEdgeArcViewAngle > prevEdgeArcViewAngle)) || ((prevEdgeArcViewAngle < 0) && (newPrevEdgeArcViewAngle < prevEdgeArcViewAngle))) {
						throw GS::LogicErrorException (doFillet ? "Filleting not possible!" : "Chamfering not possible!", __FILE__, __LINE__);
					}
				}
			}
			if (!isNextEdgeArc) {
				if ((Dist (nextVertPt, actVertPt) < Dist (endFilletChamferPosition, actVertPt) -  Eps)) {
					throw GS::LogicErrorException (doFillet ? "Filleting not possible!" : "Chamfering not possible!", __FILE__, __LINE__);
				}
			} else {
	//				if (united2 == false)
	//					if (((nextEdgeArcViewAngle > 0) && (newPrevEdgeArcViewAngle > nextEdgeArcViewAngle) || (nextEdgeArcViewAngle < 0) && (newNextEdgeArcViewAngle < nextEdgeArcViewAngle))) {
	//						throw GS::LogicErrorException (doFillet ? "Filleting not possible!" : "Chamfering not possible!", __FILE__, __LINE__);
	//					}
			}

			/* RJ008 -] */
		} else {
			throw GS::LogicErrorException (doFillet ? "Filleting not possible!" : "Chamfering not possible!", __FILE__, __LINE__);
		}

		InsertNewVerticesAndDeleteOld (filletChamferVertexIdx, begFilletChamferPosition, endFilletChamferPosition, begContourIdx, endContourIdx, prevVertIdx, isNextEdgeArc, nextEdgeArc, united1, united2, result);

		if (doFillet) {
			/* calculating the viewangle for the filleted new edge */
			double	begAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, begFilletChamferPosition);
			double	endAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, endFilletChamferPosition);
			double	actAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, actVertPt);
			bool	isReverted = !Geometry::IsInsideAngle (begAngle, endAngle, actAngle);
			double	viewAngle;
			viewAngle = Geometry::ComputeRotFi (filletChamferCircleCentrePt, begFilletChamferPosition, endFilletChamferPosition, isReverted);

			/* make curved the new begFilletPosition -> endFilletPosition edge */
			GenArc newArc = Geometry::SetGenArc (begFilletChamferPosition, endFilletChamferPosition, viewAngle);
			UIndex curvedEdgeIdx = result->GetNextVertexIndex (prevVertIdx);
			double fi;
			if (!newArc.IsReflected ())
				fi = SubAngle (newArc.GetEndAng (), newArc.GetBegAng ());
			else
				fi = -SubAngle (newArc.GetBegAng (), newArc.GetEndAng ());

			result->SetEdgeAngleInternal (curvedEdgeIdx, fi);
		} else {
			UIndex curvedEdgeIdx = result->GetNextVertexIndex (prevVertIdx);
			result->SetEdgeAngleInternal (curvedEdgeIdx, 0.0);
		}
		result->RemoveSmallArcs ();


		result->UpdateBoundingBox ();
	} catch (const GS::GSException& e) {
		e.Print (dbChannel);
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolygon2D::FilletChamferVertex", __FILE__, __LINE__);
	}

	if (result->nVertices <= 1) {
		DBBREAK (); //elofordulhat ilyen?
		//ilyenkor egy ures polygon-t adunk vissza
		result = nullptr;
		return EmptyPolygon;
	}

	DBCHECKCOREPOLY_CHECKRESULT_SINGLE;
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletChamferContour (UIndex contour, const double filletChamferRadius, const bool doFillet, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	if (IsNearZero (filletChamferRadius, Eps))
		return ResultSameAsThis;

	if (IsEmpty ())
		return EmptyPolygon;

	try {
		result = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
		result->status.isRegularized = false;

		UIndex prevVertIdx;
		UIndex nextVertIdx;
		Point2D prevVertPt;
		Point2D actVertPt;
		Point2D nextVertPt;

		Point2D	filletChamferCircleCentrePt;
		Point2D	begFilletChamferPosition;
		Point2D	endFilletChamferPosition;

		/* collecting the needed data for the next function */
		bool	isPrevEdgeArc;
		GenArc	prevEdgeArc;
		Point2D	prevEdgeArcCentre;
		double	prevEdgeArcViewAngle;
		Sector	prevEdgeSector;

		bool	isNextEdgeArc;
		GenArc	nextEdgeArc;
		Point2D	nextEdgeArcCentre;
		double	nextEdgeArcViewAngle;
		Sector	nextEdgeSector;

		double	maxFilletChamferRadius;

		UIndex	loopBeg = (contour == 0) ? 1 : contour;
		UIndex	loopEnd = (contour == 0) ? nContours : contour;
		for (UIndex contourIdx = loopBeg; contourIdx <= loopEnd; contourIdx++) {
			UIndex begContourIdx = result->GetInternalVertexBeginIdxInContour (contourIdx);
			UIndex endContourIdx = result->GetInternalVertexEndIdxInContour (contourIdx) - 1;

			UIndex filletChamferVertexIdx = begContourIdx;
			UIndex countourVertexCount = endContourIdx - begContourIdx + 1;
			for (UIndex i = countourVertexCount; i >= 1; i--) {

				try {
					maxFilletChamferRadius = result->CalcMaxVertexFillet (result->InternalVertexIdx2VertexIdx (filletChamferVertexIdx));
					if (filletChamferRadius > maxFilletChamferRadius + SmallEps) {
						filletChamferVertexIdx = result->GetNextVertexIndex (filletChamferVertexIdx);
						continue;
					}
				} catch (...) {
					filletChamferVertexIdx = result->GetNextVertexIndex (filletChamferVertexIdx);
					continue;
				}

				prevVertIdx = result->GetPrevVertexIndex (filletChamferVertexIdx);
				nextVertIdx = result->GetNextVertexIndex (filletChamferVertexIdx);
				/* determining the three acting vertices */
				prevVertPt = result->vertices[prevVertIdx];
				actVertPt  = result->vertices[filletChamferVertexIdx];
				nextVertPt = result->vertices[nextVertIdx];

				/* collecting the needed data for the next function */
				isPrevEdgeArc        = result->GetSector (result->InternalVertexIdx2VertexIdx (prevVertIdx), prevEdgeSector, prevEdgeArc);
				prevEdgeArcCentre    = prevEdgeArc.GetOrigo ();
				prevEdgeArcViewAngle = CalcRotFi (prevEdgeArc.GetBegAng (), prevEdgeArc.GetEndAng (), prevEdgeArc.IsReflected ());

				isNextEdgeArc        = result->GetSector (result->InternalVertexIdx2VertexIdx (filletChamferVertexIdx), nextEdgeSector, nextEdgeArc);
				nextEdgeArcCentre    = nextEdgeArc.GetOrigo ();
				nextEdgeArcViewAngle = CalcRotFi (nextEdgeArc.GetBegAng (), nextEdgeArc.GetEndAng (), nextEdgeArc.IsReflected ());

				/* filtering out the wrong cases */
				if (IsEqualCoord (prevVertPt, actVertPt, Eps) ||
					(IsEqualCoord (prevVertPt, nextVertPt, Eps) && !isPrevEdgeArc && !isNextEdgeArc) ||
					IsEqualCoord (nextVertPt, actVertPt, Eps) ||
					filletChamferRadius <= Eps)
				{
					filletChamferVertexIdx = result->GetNextVertexIndex (filletChamferVertexIdx);
					continue;	//Filleting not possible!
				}
				/* if the calculation of the centre of the arc of the new arced edge succeeded */
				double	newPrevEdgeArcViewAngle = 0.0;
				double	newNextEdgeArcViewAngle = 0.0;
				bool	united1 = false;
				bool	united2 = false;

				bool degen = false;
				if (GetCornerFilletCentre (
							&prevVertPt,				/* -> the three points      */
							&actVertPt,					/* -> 				      	*/
							&nextVertPt,				/* ->       				*/
							isPrevEdgeArc ? 1 : -1,		/* -> first circle index    */
							&prevEdgeArcCentre,			/* -> first centre, if any  */
							prevEdgeArcViewAngle,		/* -> first angle, if any   */
							isNextEdgeArc ? 1 : -1,		/* -> second circle index   */
							&nextEdgeArcCentre,			/* -> second centre, if any */
							nextEdgeArcViewAngle,		/* -> second angle, if any  */
							true,						/* -> first offset flag     */
							true,						/* -> second offset flag    */
							filletChamferRadius,		/* -> displacement          */
							true,						/* -> displ. dir. flag		*/
							&filletChamferCircleCentrePt,/* <- the new point		*/
							&degen) && !degen) {

					/* determine the beg and end point of the new edge */
					Sector s1 = Sector (prevVertPt, actVertPt);
					Sector s2 = Sector (actVertPt, nextVertPt);
					if (!isPrevEdgeArc)
						begFilletChamferPosition = CoordProjSector (filletChamferCircleCentrePt, s1);
					else
						begFilletChamferPosition = prevEdgeArcCentre +
												MulVector (
													UnitVector (filletChamferCircleCentrePt - prevEdgeArcCentre),
													Dist (actVertPt, prevEdgeArcCentre));
					if (!isNextEdgeArc)
						endFilletChamferPosition = CoordProjSector (filletChamferCircleCentrePt, s2);
					else
						endFilletChamferPosition = nextEdgeArcCentre +
												MulVector (
													UnitVector (filletChamferCircleCentrePt - nextEdgeArcCentre),
													Dist (actVertPt, nextEdgeArcCentre));

					/* determine the new viewangle of the two original edge */
					if (isPrevEdgeArc) {
						GetViewAngle (
							&prevEdgeArcCentre,
							&prevVertPt,
							&begFilletChamferPosition,
							prevEdgeArcViewAngle,
							isPrevEdgeArc ? 1 : -1,
							&newPrevEdgeArcViewAngle);
						GenArc newArc = Geometry::SetGenArc (prevVertPt, begFilletChamferPosition, newPrevEdgeArcViewAngle);
						double fi;
						if (!newArc.IsReflected ())
							fi = SubAngle (newArc.GetEndAng (), newArc.GetBegAng ());
						else
							fi = -SubAngle (newArc.GetBegAng (), newArc.GetEndAng ());

						result->SetEdgeAngleInternal (prevVertIdx, fi);
					}
					if (isNextEdgeArc) {
						GetViewAngle (
							&nextEdgeArcCentre,
							&endFilletChamferPosition,
							&nextVertPt,
							nextEdgeArcViewAngle,
							isNextEdgeArc ? 1 : -1,
							&newNextEdgeArcViewAngle);
					}
					/* coincidence tests */
					united1 = (Dist (prevVertPt, begFilletChamferPosition) <  Eps);
					united2 = (Dist (nextVertPt, endFilletChamferPosition) <  Eps);

					if (!isPrevEdgeArc) {
						if ((Dist (prevVertPt, actVertPt) < Dist (begFilletChamferPosition, actVertPt) -  Eps)) {
							filletChamferVertexIdx = result->GetNextVertexIndex (filletChamferVertexIdx);
							continue; //Filleting not possible!
						}
					} else {
						if (!united1) {
							if (((prevEdgeArcViewAngle > 0) && (newPrevEdgeArcViewAngle > prevEdgeArcViewAngle)) || ((prevEdgeArcViewAngle < 0) && (newPrevEdgeArcViewAngle < prevEdgeArcViewAngle))) {
								filletChamferVertexIdx = result->GetNextVertexIndex (filletChamferVertexIdx);
								continue; //Filleting not possible!
							}
						}
					}
					if (!isNextEdgeArc) {
						if ((Dist (nextVertPt, actVertPt) < Dist (endFilletChamferPosition, actVertPt) -  Eps)) {
							filletChamferVertexIdx = result->GetNextVertexIndex (filletChamferVertexIdx);
							continue; //Filleting not possible!
						}
					} else {
			//				if (united2 == false)
			//					if (((nextEdgeArcViewAngle > 0) && (newPrevEdgeArcViewAngle > nextEdgeArcViewAngle) || (nextEdgeArcViewAngle < 0) && (newNextEdgeArcViewAngle < nextEdgeArcViewAngle))) {
			//						throw GS::LogicErrorException ("Filleting not possible!", __FILE__, __LINE__);
			//					}
					}

					/* RJ008 -] */
				} else {
					filletChamferVertexIdx = result->GetNextVertexIndex (filletChamferVertexIdx);
					continue; //Filleting not possible!
				}

				InsertNewVerticesAndDeleteOld (filletChamferVertexIdx, begFilletChamferPosition, endFilletChamferPosition, begContourIdx, endContourIdx, prevVertIdx, isNextEdgeArc, nextEdgeArc, united1, united2, result);

				if (doFillet) {
					/* calculating the viewangle for the filleted new edge */
					double	begAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, begFilletChamferPosition);
					double	endAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, endFilletChamferPosition);
					double	actAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, actVertPt);
					bool	isReverted	= !Geometry::IsInsideAngle (begAngle, endAngle, actAngle);
					double	viewAngle	= Geometry::ComputeRotFi (filletChamferCircleCentrePt, begFilletChamferPosition, endFilletChamferPosition, isReverted);

					/* make curved the new begFilletPosition -> endFilletPosition edge */
					GenArc newArc = Geometry::SetGenArc (begFilletChamferPosition, endFilletChamferPosition, viewAngle);
					UIndex curvedEdgeIdx = result->GetNextVertexIndex (prevVertIdx);
					double fi;
					if (!newArc.IsReflected ())
						fi = SubAngle (newArc.GetEndAng (), newArc.GetBegAng ());
					else
						fi = -SubAngle (newArc.GetBegAng (), newArc.GetEndAng ());

					result->SetEdgeAngleInternal (curvedEdgeIdx, fi);
				} else {
					UIndex curvedEdgeIdx = result->GetNextVertexIndex (prevVertIdx);
					result->SetEdgeAngleInternal (curvedEdgeIdx, 0.0);
				}

				if (!united1) {
					if (!united2) {
						if (filletChamferVertexIdx == begContourIdx)
							filletChamferVertexIdx = result->GetNextVertexIndex (filletChamferVertexIdx);
						else
							filletChamferVertexIdx = result->GetNextVertexIndex (result->GetNextVertexIndex (filletChamferVertexIdx));
					} else {
						if (filletChamferVertexIdx != begContourIdx)
							filletChamferVertexIdx = result->GetNextVertexIndex (filletChamferVertexIdx);
					}
				} else {
					if (!united2) {
						filletChamferVertexIdx = result->GetNextVertexIndex (filletChamferVertexIdx);
					} else {
						//nothing to do
					}
				}
				// begContourIdx = polyOp->contours[contourIdx].fhedg; ez valtozhat?
				endContourIdx = result->contourEnds[contourIdx] - 1;
			}
			result->vertices[endContourIdx + 1] = result->vertices[begContourIdx];
		}
		result->UpdateBoundingBox ();
	} catch (const GS::GSException& e) {
		e.Print (dbChannel);
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolygon2D::FilletChamferContour", __FILE__, __LINE__);
	}

	if (result->nVertices <= 1) {
		DBBREAK (); //elofordulhat ilyen?
		//ilyenkor egy ures polygon-t adunk vissza
		result = nullptr;
		return EmptyPolygon;
	}

	DBCHECKCOREPOLY_CHECKRESULT_SINGLE;
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConvPgstatusToReletivePos (Geometry::PGRelPolyPosExt pgstatus, Boundary boundaries, RelativePosition* relativePosition, DetailedRelativePosition* detailed)
{
	if (relativePosition != nullptr) {
		switch (pgstatus) {
			case UnknownStatus:		*relativePosition = RelativePosition_Unknown;			break;
			case PolysOverlap:		*relativePosition = RelativePosition_Overlap;			break;
			case Poly1CoversPoly2:
				*relativePosition = RelativePosition_Overlap;
				if (detailed != nullptr)
					*detailed = DetailedRelativePosition_Overlap_FirstCoversSecond;
				break;
			case Poly2CoversPoly1:
				*relativePosition = RelativePosition_Overlap;
				if (detailed != nullptr)
					*detailed = DetailedRelativePosition_Overlap_SecondCoversFirst;
				break;
			case PolysEqual:
				*relativePosition = RelativePosition_Overlap;
				if (detailed != nullptr)
					*detailed = DetailedRelativePosition_Overlap_Equal;
				break;
			case PolysDisjunct:		*relativePosition = RelativePosition_Disjunct;			break;
			case PolysDisjunct_Node:
				if (boundaries == Boundary_Closed) {
					*relativePosition = RelativePosition_Overlap;
					if (detailed != nullptr)
						*detailed = DetailedRelativePosition_Overlap_OnBoundary;
				} else {
					*relativePosition = RelativePosition_Disjunct;
				}
				break;
			case PolysDisjunct_Edge:
				if (boundaries == Boundary_Closed) {
					*relativePosition = RelativePosition_Overlap;
					if (detailed != nullptr)
						*detailed = DetailedRelativePosition_Overlap_OnBoundary;
				} else {
					*relativePosition = RelativePosition_Disjunct;
				}
				break;
			case Poly1HasZeroArea:  *relativePosition = RelativePosition_Disjunct;			break;
			case Poly2HasZeroArea:  *relativePosition = RelativePosition_Disjunct;			break;
		}
	}

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertVertex (UIndex edgeIdx, const Point2D& newPosition, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyInsertVertexExt (&polyExt1, edgeIdx, newPosition, &resPolyExt);
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::InsertVertex", __FILE__, __LINE__);

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteVertex (UIndex vertexIdx, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBCHECKINDEX_COREPOLY(vertexIdx, 1, GetVertexNum ());



	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
	tmpPoly->DeleteVertex (vertexIdx);

	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
		DBASSERT (result.GetSize () == 0);
		result.Push (tmpPoly);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeAngle (UIndex edgeIdx, double edgeAngle, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	GSErr errorCode;

	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolySetEdgeAngleExt (&polyExt1, edgeIdx, edgeAngle, &resPolyExt);
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz

	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::SetEdgeAngle", __FILE__, __LINE__);

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}
	DBCHECKCOREPOLY_CHECKRESULT;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MoveVertices (const GS::HashTable<UIndex, Point2D>& newValues, GS::Array<GS::SharedPtr<CorePolygon2D> >& result) const
{
	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
	tmpPoly->MoveVertices (newValues);

	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
		DBASSERT (result.GetSize () == 0);
		result.Push (tmpPoly);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdge (UIndex edgeIdx, const GS::Array<GenArc>& arcs, const ArcDivParams& arcDivParams, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
	tmpPoly->ReplaceEdgeInternal (edgeIdx, arcs, arcDivParams);

	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
		DBASSERT (result.GetSize () == 0);
		result.Push (tmpPoly);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdge (UIndex edgeIdx, const GS::Array<double>& angles, const GS::Array<Point2D>& internalVerts, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
	tmpPoly->ReplaceEdgeInternal (edgeIdx, angles, internalVerts);

	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
		DBASSERT (result.GetSize () == 0);
		result.Push (tmpPoly);
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteEdge (UIndex edgeIdx, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBASSERT (status.isRegularized);
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());
	bool success = true;
	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);
	GSErr errorCode = NoError;

	USize origNVertices = nVertices;
	Geometry::PGPOLYEXT			polyExt1;
	MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyDeleteEdgeExt (&polyExt1, edgeIdx, nullptr, &resPolyExt);

	//A deleteAble es a resultPolys kozul valamelyik mindenkepp nullptr (a masikat szamoljuk)
	//Regularizalt polygonokat ad vissza, de az orientacioja lehet rossz
	if (errorCode != AlgorithmError) {
		ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::DeleteEdge", __FILE__, __LINE__);
	} else {
		//Ha AlgorithmError, akkor nem lehet torolni az elet, mert a mellete levo elek nem osszetartoak
		//Ilyenkor visszaadjuk az eredeti polygont es jelezzuk, hogy nem sikerult a muvelet
		result.Clear (true);
		GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPolygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
		result.Push(tmpPolygon);
		success = false;
	}

	if (result.GetSize () == 1 && origNVertices == result [0]->nVertices)
		success = false;

	for (UIndex idx = 0; idx < result.GetSize (); idx++) {
		result[idx]->UpdateOrientation ();
		result[idx]->status.isRegularized = true;
	}

	DBCHECKCOREPOLY_CHECKRESULT;
	return success;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteEdge (UIndex edgeIdx, GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& result) const
{
	DBCHECKINDEX_COREPOLY(edgeIdx, 1, GetEdgeNum ());

	edgeIdx = VertexIdx2InternalVertexIdx (edgeIdx);

	result = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this);
	result->status.isRegularized = false;

	bool success = result->PolygonDeleteEdge (edgeIdx);

	result->UpdateBoundingBox ();

	DBCHECKCOREPOLY_CHECKRESULT_SINGLE;
	return success;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FillSegmentedArc (const ArcDivParams& arcDivParams, GS::Array< GS::Array<Point2D> >& segmentedArcs, USize& numOfSegmentedVertex) const
{
	for (UIndex actSubPoly = 1; actSubPoly <= nContours; actSubPoly++) {
		GS::Int32 firstnode = contourEnds[actSubPoly - 1] + 1;
		GS::Int32 lastnode  = contourEnds[actSubPoly];
		for (GS::Int32 node = firstnode; node < lastnode; node++) {
			Point2D begC = vertices[node];
			Point2D endC = vertices[node + 1];
			UIndex arcInd = GetInternalArcIdx (node);
			if (arcInd > 0) {
				Point2D origC;
				double angle = arcs[arcInd].arcAngle;
				Geometry::ArcGetOrigo (&begC, &endC, angle, &origC);
				GS::ArrayFB<Point2D, 6> resultPolyVertices;
				segmentedArcs.Push (resultPolyVertices);
				Geometry::DivideArcToCo (&origC, &begC, angle, arcDivParams, segmentedArcs.GetLast ());
				numOfSegmentedVertex += (segmentedArcs.GetLast ().GetSize () - 2);
			}
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetSegmentUp (CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& tmpPoly, GS::Array< GS::Array<Point2D> >& segmentedArcs) const
{
	UIndex segmentedArcIdx = 0;
	for (UIndex actSubPoly = 1; actSubPoly <= nContours; actSubPoly++) {
		GS::Int32 firstnode = contourEnds[actSubPoly - 1] + 1;
		GS::Int32 lastnode  = contourEnds[actSubPoly];
		ContourUserData contourInfo;
		if (contourInfos.GetSize() != 0 && flags.isContourUserData)
			contourInfo = contourInfos [actSubPoly];
		tmpPoly.AddOneContour (&contourInfo);
		VertexUserData vertexInfo;
		EdgeUserData   edgeInfo;
		if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
			vertexInfo = vertexInfos [firstnode];
		if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
			edgeInfo = inhEdgeInfos [firstnode];
		tmpPoly.AddOneVertex (vertices[firstnode], &vertexInfo, &edgeInfo);

		for (GS::Int32 node = firstnode; node < lastnode; node++) {
			UIndex arcInd = GetInternalArcIdx (node);

			if (arcInd != 0 && segmentedArcIdx < segmentedArcs.GetSize ()) {
				for (UIndex idx = 1; idx < segmentedArcs[segmentedArcIdx].GetSize () - 1; ++idx) {
					if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
						vertexInfo = defaultVertexData;
					if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
						edgeInfo = inhEdgeInfos [node];
					tmpPoly.AddOneVertex (segmentedArcs[segmentedArcIdx][idx], &vertexInfo, &edgeInfo);
				}
				segmentedArcIdx++;
			}

			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
				vertexInfo = vertexInfos [(node + 1)];
			if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
				edgeInfo = inhEdgeInfos [(node + 1)];
			tmpPoly.AddOneVertex (vertices[node + 1], &vertexInfo, &edgeInfo);
		}

		DBASSERT (Geometry::IsEqualCoord (tmpPoly.vertices[tmpPoly.contourEnds[actSubPoly]], tmpPoly.vertices[tmpPoly.contourEnds[actSubPoly - 1] + 1], EPS)); //Ez nem biztos, hogy hiba
		//tmpPoly.vertices[tmpPoly.contourEnds[actSubPoly]] = tmpPoly.vertices[tmpPoly.contourEnds[actSubPoly - 1] + 1];
	}
	DBASSERT (segmentedArcIdx == segmentedArcs.GetSize ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetSegmentUp (GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& tmpPoly, GS::Array< GS::Array<Point2D> >& segmentedArcs) const
{
	UIndex segmentedArcIdx = 0;
	for (UIndex actSubPoly = 1; actSubPoly <= nContours; actSubPoly++) {
		GS::Int32 firstnode = contourEnds[actSubPoly - 1] + 1;
		GS::Int32 lastnode  = contourEnds[actSubPoly];
		ContourUserData contourInfo;
		if (contourInfos.GetSize() != 0 && flags.isContourUserData)
			contourInfo = contourInfos [actSubPoly];
		tmpPoly->AddOneContour (&contourInfo);
		VertexUserData vertexInfo;
		EdgeUserData   edgeInfo;
		if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
			vertexInfo = vertexInfos [firstnode];
		if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
			edgeInfo = inhEdgeInfos [firstnode];
		tmpPoly->AddOneVertex (vertices[firstnode], &vertexInfo, &edgeInfo);

		for (GS::Int32 node = firstnode; node < lastnode; node++) {
			UIndex arcInd = GetInternalArcIdx (node);

			if (arcInd != 0 && segmentedArcIdx < segmentedArcs.GetSize ()) {
				for (UIndex idx = 1; idx < segmentedArcs[segmentedArcIdx].GetSize () - 1; ++idx) {
					if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
						vertexInfo = defaultVertexData;
					if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
						edgeInfo = inhEdgeInfos [node];
					tmpPoly->AddOneVertex (segmentedArcs[segmentedArcIdx][idx], &vertexInfo, &edgeInfo);
				}
				segmentedArcIdx++;
			}

			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
				vertexInfo = vertexInfos [(node + 1)];
			if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
				edgeInfo = inhEdgeInfos [(node + 1)];
			tmpPoly->AddOneVertex (vertices[node + 1], &vertexInfo, &edgeInfo);
		}

		DBASSERT (Geometry::IsEqualCoord (tmpPoly->vertices[tmpPoly->contourEnds[actSubPoly]], tmpPoly->vertices[tmpPoly->contourEnds[actSubPoly - 1] + 1], EPS)); //Ez nem biztos, hogy hiba
		//tmpPoly->vertices[tmpPoly->contourEnds[actSubPoly]] = tmpPoly->vertices[tmpPoly->contourEnds[actSubPoly - 1] + 1];
	}
	DBASSERT (segmentedArcIdx == segmentedArcs.GetSize ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AddHoleUpdateUserData (GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& tmpPoly, const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& poly, UIndex contourIdx, USize oldNVertices, USize numNewVertices, USize oldNContours, USize numNewContours) const
{
	if (tmpPoly->vertexInfos.GetSize() != 0 && tmpPoly->flags.isVertexUserData) {
		if (poly.vertexInfos.GetSize() != 0 && poly.flags.isVertexUserData) {
			CopyInfo_Data <VertexUserData> (tmpPoly->vertexInfos, (oldNVertices + 1),
				poly.vertexInfos, (poly.contourEnds[contourIdx - 1] + 1),
				numNewVertices);
		} else {
			for (UIndex i = oldNVertices + 1; i <= tmpPoly->nVertices; ++i) {
				tmpPoly->vertexInfos[i] = tmpPoly->defaultVertexData;
			}
		}
	}
	if (tmpPoly->inhEdgeInfos.GetSize() != 0 && tmpPoly->flags.isEdgeUserData) {
		if (poly.inhEdgeInfos.GetSize() != 0 && poly.flags.isEdgeUserData) {
			CopyInfo_Data <EdgeUserData> (tmpPoly->inhEdgeInfos, (oldNVertices + 1),
				poly.inhEdgeInfos,(poly.contourEnds[contourIdx - 1] + 1),
				numNewVertices);
		} else {
			for (UIndex i = oldNVertices + 1; i <= tmpPoly->nVertices; ++i) {
				tmpPoly->inhEdgeInfos [i] =  tmpPoly->defaultEdgeData;
			}
		}
	}
	if (tmpPoly->contourInfos.GetSize() != 0 && tmpPoly->flags.isContourUserData) {
		if (poly.contourInfos.GetSize() != 0 && poly.flags.isContourUserData) {
			CopyInfo_Data <ContourUserData> (tmpPoly->contourInfos, (oldNContours + 1),
				poly.contourInfos, contourIdx,
				numNewContours);
		} else {
			for (UIndex i = oldNContours + 1; i <= tmpPoly->nContours; ++i) {
				tmpPoly->contourInfos[i] = tmpPoly->defaultContourData;
			}
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AddHole (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& poly, UIndex contourIdx, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	DBCHECKINDEX_COREPOLY(contourIdx, 2, poly.GetContourNum ());

	if (contourIdx <= 1 || poly.nContours < static_cast<USize> (contourIdx) || poly.nContours <= 0) {
		ThrowGeometryExceptionAtError (Error, "CorePolygon2D::AddHole", __FILE__, __LINE__);
	}

	USize numNewVertices		= poly.contourEnds[contourIdx] - poly.contourEnds[contourIdx - 1];
	USize numNewContours		= 1;
	USize numNewArcs			= 0;

	for (UIndex a = 1; a <= poly.nArcs; ++a) {
		if (poly.arcs[a].begIndex > poly.contourEnds[contourIdx - 1]
			&& poly.arcs[a].begIndex <= poly.contourEnds[contourIdx]
			&& poly.arcs[a].endIndex > poly.contourEnds[contourIdx - 1]
			&& poly.arcs[a].endIndex <= poly.contourEnds[contourIdx]
			) {
				numNewArcs++;
		}
	}

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*this, nVertices + numNewVertices, nArcs + numNewArcs, nContours + numNewContours);

	USize oldNVertices	= tmpPoly->nVertices;
	USize oldNContours	= tmpPoly->nContours;
	USize oldNArcs		= tmpPoly->nArcs;

	tmpPoly->nVertices	+= numNewVertices;
	tmpPoly->nContours	+= numNewContours;
	tmpPoly->nArcs		+= numNewArcs;

	tmpPoly->status.isRegularized = false;

	for (UIndex vertexIdx = oldNVertices + 1, sourceVertexIdx = poly.contourEnds[contourIdx - 1] + 1; vertexIdx <= tmpPoly->nVertices && sourceVertexIdx <= poly.contourEnds[contourIdx]; vertexIdx++, sourceVertexIdx++) {
		tmpPoly->vertices[vertexIdx] = poly.vertices[sourceVertexIdx];
	}
	tmpPoly->contourEnds[tmpPoly->nContours] = tmpPoly->nVertices;
	if (numNewArcs > 0) {
		UIndex da = oldNArcs + 1;
		GS::Int32 offset = static_cast<GS::Int32> ((oldNVertices + 1) - (poly.contourEnds[contourIdx - 1] + 1));
		for (UIndex a = 1; a <= poly.nArcs; ++a) {
			if (poly.arcs[a].begIndex > poly.contourEnds[contourIdx - 1]
				&& poly.arcs[a].begIndex <= poly.contourEnds[contourIdx]
				&& poly.arcs[a].endIndex > poly.contourEnds[contourIdx - 1]
				&& poly.arcs[a].endIndex <= poly.contourEnds[contourIdx]
				) {
					tmpPoly->arcs[da] = poly.arcs[a];
					tmpPoly->arcs[da].begIndex += offset;
					tmpPoly->arcs[da].endIndex += offset;
					da++;
				}
		}
	}
	AddHoleUpdateUserData (tmpPoly, poly, contourIdx, oldNVertices, numNewVertices, oldNContours, numNewContours);

	tmpPoly->UpdateBoundingBox ();

	if (tmpPoly->Regularize (result) == ResultSameAsThis) {
		DBASSERT (result.GetSize () == 0);
		result.Push (tmpPoly);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Unify (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& poly, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result) const
{
	if (IsEmpty () || poly.IsEmpty ()) {
		DBASSERT (result.GetSize () == 0);
		return ResultThisAndParameter;
	}

	const Box2DData& polyBoundingBox = poly.GetBoundBox ();

	if (polyBoundingBox.xMax < boundBox.xMin - EPS ||
		polyBoundingBox.xMin > boundBox.xMax + EPS ||
		polyBoundingBox.yMax < boundBox.yMin - EPS ||
		polyBoundingBox.yMin > boundBox.yMax + EPS)
	{
		DBASSERT (result.GetSize () == 0);
		return ResultThisAndParameter;
	}

	GSErr errorCode;

	Geometry::PGRelPolyPosExt	pgstatus = UnknownStatus;
	Geometry::PGPOLYEXT			polyExt1;
	Geometry::PGPOLYEXT			polyExt2;
	MakePolyExt (polyExt1);
	poly.MakePolyExt (polyExt2);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyUnionExt (&polyExt1, &polyExt2, &resPolyExt, &pgstatus);
	//Regularizalt polygonokat ad vissza
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::Unify", __FILE__, __LINE__);

	switch (pgstatus) {
		case PolysOverlap:
		case PolysDisjunct_Edge:			// cases already handled by PGPolyUnionExt
			break;

		case Poly2HasZeroArea:
		case Poly1CoversPoly2:
		case PolysEqual:				// the solution is the 1st input poly
			DBASSERT (result.GetSize () == 0);
			return ResultSameAsThis;
			break;

		case Poly1HasZeroArea:
		case Poly2CoversPoly1:			// the solution is the 2nd input poly
			DBASSERT (result.GetSize () == 0);
			return ResultSameAsFirstParameter;

		case PolysDisjunct:
		case PolysDisjunct_Node:		// the solution is both input polys
			DBASSERT (result.GetSize () == 0);
			return ResultThisAndParameter;

		case UnknownStatus:
		default:
			ThrowGeometryExceptionAtError (Error, "CorePolygon2D::Unify", __FILE__, __LINE__);
	}

	for (typename GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >::Iterator it = result.Enumerate (); it != nullptr; ++it) {
		(*it)->RemoveSmallArcs ();
		(*it)->status.isRegularized = true;
	}

	DBCHECKCOREPOLY_CHECKRESULT;
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Intersect (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& poly, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result, Boundary boundaries, RelativePosition* relativePosition, DetailedRelativePosition* detailed) const
{
	if (relativePosition != nullptr)
		*relativePosition = RelativePosition_Disjunct;
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;

	if (IsEmpty () || poly.IsEmpty ()) {
		DBASSERT (result.GetSize () == 0);
		return EmptyPolygon;
	}

	const Box2DData& polyBoundingBox = poly.GetBoundBox ();

	if (polyBoundingBox.xMax < boundBox.xMin - EPS ||
		polyBoundingBox.xMin > boundBox.xMax + EPS ||
		polyBoundingBox.yMax < boundBox.yMin - EPS ||
		polyBoundingBox.yMin > boundBox.yMax + EPS)
	{
		DBASSERT (result.GetSize () == 0);
		return EmptyPolygon;
	}

	GSErr errorCode;

	Geometry::PGRelPolyPosExt	pgstatus = UnknownStatus;
	Geometry::PGPOLYEXT			polyExt1;
	Geometry::PGPOLYEXT			polyExt2;
	MakePolyExt (polyExt1);
	poly.MakePolyExt (polyExt2);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyIntersectionExt (&polyExt1, &polyExt2, &resPolyExt, &pgstatus);
	//Regularizalt polygonokat ad vissza
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::Intersect", __FILE__, __LINE__);

	ConvPgstatusToReletivePos (pgstatus, boundaries, relativePosition, detailed);

	switch (pgstatus) {
		case PolysEqual:
		case Poly2CoversPoly1:
			DBASSERT (result.GetSize () == 0);
			return ResultSameAsThis;
		case Poly1CoversPoly2:
			DBASSERT (result.GetSize () == 0);
			return ResultSameAsFirstParameter;
			break;
		case PolysDisjunct:
		case PolysDisjunct_Node:
		case PolysDisjunct_Edge:
			DBASSERT (result.GetSize () == 0);
			return EmptyPolygon;
		case UnknownStatus:
		case PolysOverlap:
		case Poly1HasZeroArea:
		case Poly2HasZeroArea:
		default:
			// do nothing
			break;
	}

	for (typename GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >::Iterator it = result.Enumerate (); it != nullptr; ++it) {
		(*it)->RemoveSmallArcs ();
		(*it)->UpdateBoundingBox ();
		(*it)->status.isRegularized = true;
	}

	DBCHECKCOREPOLY_CHECKRESULT;
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Substract (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& poly, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result, Boundary boundaries, RelativePosition* relativePosition, DetailedRelativePosition* detailed) const
{
	if (relativePosition != nullptr)
		*relativePosition = RelativePosition_Disjunct;
	if (detailed != nullptr)
		*detailed = DetailedRelativePosition_Unknown;

	if (IsEmpty () || poly.IsEmpty ()) {
		DBASSERT (result.GetSize () == 0);
		return ResultSameAsThis;
	}

	const Box2DData& polyBoundingBox = poly.GetBoundBox ();

	if (polyBoundingBox.xMax < boundBox.xMin - EPS ||
		polyBoundingBox.xMin > boundBox.xMax + EPS ||
		polyBoundingBox.yMax < boundBox.yMin - EPS ||
		polyBoundingBox.yMin > boundBox.yMax + EPS)
	{
		DBASSERT (result.GetSize () == 0);
		return ResultSameAsThis;
	}

	GSErr errorCode;

	Geometry::PGRelPolyPosExt	pgstatus = UnknownStatus;
	Geometry::PGPOLYEXT			polyExt1;
	Geometry::PGPOLYEXT			polyExt2;
	MakePolyExt (polyExt1);
	poly.MakePolyExt (polyExt2);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyDifferenceExt (&polyExt1, &polyExt2, &resPolyExt, &pgstatus);
	//Regularizalt polygonokat ad vissza
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::Substract", __FILE__, __LINE__);

	ConvPgstatusToReletivePos (pgstatus, boundaries, relativePosition, detailed);

	switch (pgstatus) {
		case PolysDisjunct:
		case PolysDisjunct_Node:
		case PolysDisjunct_Edge:
		case Poly2HasZeroArea:
			DBASSERT (result.GetSize () == 0);
			return ResultSameAsThis;
		case Poly2CoversPoly1:
		case PolysEqual:
		case Poly1HasZeroArea:
			DBASSERT (result.GetSize () == 0);
			return EmptyPolygon;
		case PolysOverlap:
		case Poly1CoversPoly2:
		case UnknownStatus:
		default:
			// do nothing
			break;
	}

	for (typename GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >::Iterator it = result.Enumerate (); it != nullptr; ++it) {
		(*it)->RemoveSmallArcs ();
		(*it)->status.isRegularized = true;
	}

	DBCHECKCOREPOLY_CHECKRESULT;
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Cut (const HalfPlane2DData& cutline, bool regularizeResults, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result, bool* fullin /*= nullptr*/, GS::Int32* wrcode /*= nullptr*/, bool* degen /*= nullptr*/) const
{

	try {
		GS::ArrayFB<HalfPlane2DData, 6>	cutlines;
		cutlines.Push (cutline);

		return CutWithHalfPlanes (cutlines, regularizeResults, result, fullin, wrcode, degen);

		//Ha az eredmeny elfajult (egy szakasz) lenne akkor nem jon letre polygon de beallitja a degen-t
	} catch (GS::GSException& e) {
		e.Print (dbChannel);
	}
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Cut (const GS::Array<HalfPlane2DData>& cutlines, bool regularizeResults, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result, bool* fullin /*= nullptr*/, GS::Int32* wrcode /*= nullptr*/, bool* degen /*= nullptr*/) const
{
	try {
		return CutWithHalfPlanes (cutlines, regularizeResults, result, fullin, wrcode, degen);

		//Ha az eredmeny elfajult (egy szakasz) lenne akkor nem jon letre polygon de beallitja a degen-t
	} catch (GS::GSException& e) {
		e.Print (dbChannel);
	}
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Strip (const HalfPlane2DData& cutline1, const HalfPlane2DData& cutline2, bool regularizeResults, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result, GS::Int32* wrcode /*= nullptr*/) const
{
	try {
		bool				fullin;

		GS::ArrayFB<HalfPlane2DData, 6>	cutlines;
		cutlines.Push (cutline1);
		cutlines.Push (cutline2);

		return CutWithHalfPlanes (cutlines, regularizeResults, result, &fullin, wrcode, nullptr);
		//Ha az eredmeny elfajult (egy szakasz) lenne akkor nem jon letre polygon de beallitja a degen-t
	} catch (GS::GSException& e) {
		e.Print (dbChannel);
	}
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Clip (const Box2DData& box, bool regularizeResults, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& result, GS::Int32* wrcode /*= nullptr*/) const
{
	try {
		bool				fullin;

		GS::ArrayFB<HalfPlane2DData, 6>	cutlines;

		cutlines.Push (HalfPlane2DData (-1.0, 0.0, -box.xMin));
		cutlines.Push (HalfPlane2DData (1.0, 0.0, box.xMax));
		cutlines.Push (HalfPlane2DData (0.0, -1.0, -box.yMin));
		cutlines.Push (HalfPlane2DData (0.0, 1.0, box.yMax));

		return CutWithHalfPlanes (cutlines, regularizeResults, result, &fullin, wrcode, nullptr);
		//Ha az eredmeny elfajult (egy szakasz) lenne akkor nem jon letre polygon de beallitja a degen-t
	} catch (GS::GSException& e) {
		if (wrcode != nullptr)
			*wrcode = 1;
		e.Print (dbChannel);
	}
	return NewPolygons;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::StoreElem (
				short			typ,
				Sector*			pSector,
				GenArc*			pGenArc,
				GS::Int32			nCoords,		// spline/polyLine/polygon
				Point2D*			pCoords,		// spline/polyLine/polygon
				DirType*		pDirs,			// spline
				GS::UInt32*			/*pVertInds*/,	// polyLine/polygon
				GS::Int32			/*nEnds*/,		// polygon
				GS::Int32*			/*pEnds*/,		// polygon
				GS::Int32			/*arcsNum*/,		// polyLine/polygon
				PolyArcRec*		/*pArcs*/,			// polyLine/polygon
				//Polygon2DData*	/*pPoly*/,			// polygon (alternative form)		// TODO
				const void*		userData)
{
	switch (typ) {
		case CURVE2D_Sector:
			{
				SectorCreator* creator = const_cast<SectorCreator*> (reinterpret_cast<const SectorCreator*> (userData));
				DBASSERT (creator != nullptr);
				DBASSERT (pSector != nullptr);
				if (creator != nullptr && pSector != nullptr)
					creator->CreateSector (*pSector);
				break;
			}
		case CURVE2D_GenArc:
			{
				GenArcCreator* creator = const_cast<GenArcCreator*> (reinterpret_cast<const GenArcCreator*> (userData));
				DBASSERT (creator != nullptr);
				DBASSERT (pGenArc != nullptr);
				if (creator != nullptr && pGenArc != nullptr)
					creator->CreateGenArc (*pGenArc);
				break;
			}
		case CURVE2D_Point:
			{
				PointCreator* creator = const_cast<PointCreator*> (reinterpret_cast<const PointCreator*> (userData));
				DBASSERT (creator != nullptr);
				if (creator != nullptr) {
					if (pCoords != nullptr) {
						creator->CreatePoint (*pCoords);
					} else {
						DBBREAK ();
						creator->CreatePoint (Point2D (0, 0));
					}
				}
				break;
			}
		case CURVE2D_Spline:
			{
				SplineCreator* creator = const_cast<SplineCreator*> (reinterpret_cast<const SplineCreator*> (userData));
				DBASSERT (creator != nullptr);
				DBASSERT (pCoords != nullptr);
				if (creator != nullptr && pCoords != nullptr) {
					BezierDetails bezier;
					Int32	nCo = GS::Abs (nCoords);
					bezier.SetData (nCo, pCoords, pDirs);
					bezier.SetClosed (nCoords < 0);
					creator->CreateSpline (bezier);
				}
				break;
			}
		default:
			DBBREAK ();
	}

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IntersectionDetector (
											short			typ,
											Sector*			pSector,
											GenArc*			pGenArc,
											GS::Int32			nCoords,		// spline/polyLine/polygon
											Point2D*			pCoords,		// spline/polyLine/polygon
											DirType*		pDirs,			// spline
											GS::UInt32*			pVertInds,		// polyLine/polygon
											GS::Int32			nEnds,			// polygon
											GS::Int32*			pEnds,			// polygon
											GS::Int32			arcsNum,			// polyLine/polygon
											PolyArcRec*		pArcs,			// polyLine/polygon
											//Polygon2DData*	pPoly,			// polygon (alternative form)
											const void*		userData)
{
	UNUSED_PARAMETER (typ);
	UNUSED_PARAMETER (pSector);
	UNUSED_PARAMETER (pGenArc);
	UNUSED_PARAMETER (nCoords);
	UNUSED_PARAMETER (pCoords);
	UNUSED_PARAMETER (pDirs);
	UNUSED_PARAMETER (pVertInds);
	UNUSED_PARAMETER (nEnds);
	UNUSED_PARAMETER (pEnds);
	UNUSED_PARAMETER (arcsNum);
	UNUSED_PARAMETER (pArcs);
//	UNUSED_PARAMETER (pPoly);

	DBASSERT (userData != nullptr);
	if (userData != nullptr) {
		bool* intersect = const_cast<bool*> (static_cast<const bool*> (userData));
		*intersect = true;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Sector& sector, Boundary cutBoundaries, SectorCreator& creator) const
{
	CutElemInternal ( cutBoundaries, sector, StoreElem, &creator, false);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const GenArc& genArc, Boundary cutBoundaries, GenArcCreator& creator) const
{
	CutElemInternal (cutBoundaries, genArc, StoreElem, &creator, false);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Point2D& coord, Boundary cutBoundaries, PointCreator& creator) const
{
	CutElemInternal (cutBoundaries, coord, StoreElem, &creator, false);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const BezierDetails& bezier, Boundary cutBoundaries, SplineCreator& creator) const
{
	CutElemInternal (cutBoundaries, bezier, StoreElem, &creator, false);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Sector& sector, Boundary cutBoundaries, GS::Array<Sector>& results) const
{
	class StorePieces : public Geometry::SectorCreator
	{
	private:
		GS::Array<Sector>& pieces;

		virtual void CreateSector (const Sector& sector) override
		{
			pieces.Push (sector);
		}
		StorePieces& operator= (const StorePieces& source)
		{
			pieces = source.pieces;
			return *this;
		}

	public:
		StorePieces (GS::Array<Sector>& results) : pieces (results) {}
	};
	StorePieces creator (results);
	CutElem (sector, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const GenArc& genArc, Boundary cutBoundaries, GS::Array<GenArc>& results) const
{
	class StorePieces : public Geometry::GenArcCreator
	{
	private:
		GS::Array<GenArc>& pieces;

		virtual void CreateGenArc (const GenArc& genArc) override
		{
			pieces.Push (genArc);
		}
		StorePieces& operator= (const StorePieces& source)
		{
			pieces = source.pieces;
			return *this;
		}

	public:
		StorePieces (GS::Array<GenArc>& results) : pieces (results) {}
	};
	StorePieces creator (results);
	CutElem (genArc, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Point2D& coord, Boundary cutBoundaries, GS::Array<Point2D>& results) const
{
	class StorePieces : public Geometry::PointCreator
	{
	private:
		GS::Array<Point2D>& pieces;

		virtual void CreatePoint (const Point2D& coord) override
		{
			pieces.Push (coord);
		}
		StorePieces& operator= (const StorePieces& source)
		{
			pieces = source.pieces;
			return *this;
		}

	public:
		StorePieces (GS::Array<Point2D>& results) : pieces (results) {}
	};
	StorePieces creator (results);
	CutElem (coord, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const BezierDetails& bezier, Boundary cutBoundaries, GS::Array<BezierDetails>& results) const
{
	class StorePieces : public Geometry::SplineCreator
	{
	private:
		GS::Array<BezierDetails>& pieces;

		virtual void CreateSpline (const BezierDetails& bezier) override
		{
			pieces.Push (bezier);
		}
		StorePieces& operator= (const StorePieces& source)
		{
			pieces = source.pieces;
			return *this;
		}

	public:
		StorePieces (GS::Array<BezierDetails>& results) : pieces (results) {}
	};
	StorePieces creator (results);
	CutElem (bezier, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& polygon, Boundary cutBoundaries, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& results) const
{
	bool touching;
	CutElemInternal ( cutBoundaries, polygon, results, touching, false);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& polyline, Boundary cutBoundaries, GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >& results) const
{
	//	bool touching;
	CutElemInternal ( cutBoundaries, polyline, results, false);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Sector& sector, Boundary cutBoundaries, SectorCreator& creator) const
{
	CutElemInternal (cutBoundaries, sector, StoreElem, &creator, true);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const GenArc& genArc, Boundary cutBoundaries, GenArcCreator& creator) const
{
	CutElemInternal (cutBoundaries, genArc, StoreElem, &creator, true);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Point2D& coord, Boundary cutBoundaries, PointCreator& creator) const
{
	CutElemInternal (cutBoundaries, coord, StoreElem, &creator, true);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const BezierDetails& bezier, Boundary cutBoundaries, SplineCreator& creator) const
{
	CutElemInternal (cutBoundaries, bezier, StoreElem, &creator, true);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Sector& sector, Boundary cutBoundaries, GS::Array<Sector>& results) const
{
	class StorePieces : public Geometry::SectorCreator
	{
	private:
		GS::Array<Sector>& pieces;

		virtual void CreateSector (const Sector& sector) override
		{
			pieces.Push (sector);
		}
		StorePieces& operator= (const StorePieces& source)
		{
			pieces = source.pieces;
			return *this;
		}

	public:
		StorePieces (GS::Array<Sector>& results) : pieces (results) {}
	};
	StorePieces creator (results);
	ElemPolyDifference (sector, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const GenArc& genArc, Boundary cutBoundaries, GS::Array<GenArc>& results) const
{
	class StorePieces : public Geometry::GenArcCreator
	{
	private:
		GS::Array<GenArc>& pieces;

		virtual void CreateGenArc (const GenArc& genArc) override
		{
			pieces.Push (genArc);
		}
		StorePieces& operator= (const StorePieces& source)
		{
			pieces = source.pieces;
			return *this;
		}

	public:
		StorePieces (GS::Array<GenArc>& results) : pieces (results) {}
	};
	StorePieces creator (results);
	ElemPolyDifference (genArc, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Point2D& coord, Boundary cutBoundaries, GS::Array<Point2D>& results) const
{
	class StorePieces : public Geometry::PointCreator
	{
	private:
		GS::Array<Point2D>& pieces;

		virtual void CreatePoint (const Point2D& coord) override
		{
			pieces.Push (coord);
		}
		StorePieces& operator= (const StorePieces& source)
		{
			pieces = source.pieces;
			return *this;
		}

	public:
		StorePieces (GS::Array<Point2D>& results) : pieces (results) {}
	};
	StorePieces creator (results);
	ElemPolyDifference (coord, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const BezierDetails& bezier, Boundary cutBoundaries, GS::Array<BezierDetails>& results) const
{
	class StorePieces : public Geometry::SplineCreator
	{
	private:
		GS::Array<BezierDetails>& pieces;

		virtual void CreateSpline (const BezierDetails& bezier) override
		{
			pieces.Push (bezier);
		}
		StorePieces& operator= (const StorePieces& source)
		{
			pieces = source.pieces;
			return *this;
		}

	public:
		StorePieces (GS::Array<BezierDetails>& results) : pieces (results) {}
	};
	StorePieces creator (results);
	ElemPolyDifference (bezier, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& polygon, Boundary cutBoundaries, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& results) const
{
	bool touching;
	CutElemInternal (cutBoundaries, polygon, results, touching,  true);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>& polyline, Boundary cutBoundaries, GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >& results) const
{
	CutElemInternal (cutBoundaries, polyline, results/*, touching*/,  true);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const Sector& sector, Boundary cutBoundaries) const
{
	bool intersect = false;
	CutElemInternal (cutBoundaries, sector, IntersectionDetector, &intersect, false);
	return intersect;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const GenArc& genArc, Boundary cutBoundaries) const
{
	bool intersect = false;
	CutElemInternal (cutBoundaries, genArc, IntersectionDetector, &intersect, false);
	return intersect;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const Point2D& coord, Boundary cutBoundaries) const
{
	bool intersect = false;
	CutElemInternal (cutBoundaries, coord, IntersectionDetector, &intersect, false);
	return intersect;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const BezierDetails& bezier, Boundary cutBoundaries) const
{
	bool intersect = false;
	CutElemInternal (cutBoundaries, bezier, IntersectionDetector, &intersect, false);
	return intersect;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& polygon, Boundary cutBoundaries, bool& touching) const
{
	GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > poly2DResult;
	CutElemInternal (cutBoundaries, polygon, poly2DResult, touching, false);
	return (poly2DResult.GetSize () != 0);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& polyline, Boundary cutBoundaries) const
{
	bool intersect = false;
	CutElemInternal (cutBoundaries, polyline, IntersectionDetector, &intersect, false);
	return intersect;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDiffBorderOnly (const Sector& sector, GS::Array<Sector>& results) const
{
	CutElemBorderOnlyInternal (sector, results, LineCutMode::Difference);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDiffBorderOnly (const GenArc& arc, GS::Array<GenArc>& results) const
{
	CutElemBorderOnlyInternal (arc, results, LineCutMode::Difference);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IntersectElemBorderOnly (const Sector& sector, GS::Array<Sector>& results) const
{
	CutElemBorderOnlyInternal (sector, results, LineCutMode::Overlap);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IntersectElemBorderOnly (const GenArc& arc, GS::Array<GenArc>& results) const
{
	CutElemBorderOnlyInternal (arc, results, LineCutMode::Overlap);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CreateCommonEdgeSections (CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& poly1, CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& poly2, bool toRegular, GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>>>& result)
{
	bool changed = false;
	GSErr errorCode;
	Geometry::PGPOLYEXT			polyExt1;
	Geometry::PGPOLYEXT			polyExt2;
	poly1.MakePolyExt (polyExt1);
	poly2.MakePolyExt (polyExt2);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	errorCode = Geometry::PGPolyCreateCommonEdgeSectionsExt (&polyExt1, &polyExt2, &resPolyExt);
	ThrowGeometryExceptionAtError (errorCode, "CorePolygon2D::CreateCommonEdgeSections", __FILE__, __LINE__);

	if (result.GetSize () == 0) {
		changed = false;
	} else if (result.GetSize () == 2) {
		if (toRegular) {
			result[1]->UpdateOrientation ();
			result[1]->status.isRegularized = true;
			result[0]->status.isRegularized = true;
		}
		changed = true;
		if (result[1]->nArcs + 1 < (result[1]->arcs).GetSize ())
			(result[1]->arcs).SetSize (result[1]->nArcs + 1);
		if (result[1]->nVertices + 1 < (result[1]->vertices).GetSize ()) {
			(result[1]->vertices).SetSize (result[1]->nVertices + 1);
			result[1]->UpdateBoundingBox ();
			if (result[1]->flags.isVertexUserData)
				(result[1]->vertexInfos).SetSize (result[1]->nVertices + 1);
			if (result[1]->flags.isEdgeUserData)
				(result[1]->inhEdgeInfos).SetSize (result[1]->nVertices + 1);

		}
		if (result[0]->nArcs + 1 < (result[0]->arcs).GetSize ())
			(result[0]->arcs).SetSize (result[0]->nArcs + 1);
		if (result[0]->nVertices + 1 < (result[0]->vertices).GetSize ()) {
			(result[0]->vertices).SetSize (result[0]->nVertices + 1);
			result[0]->UpdateBoundingBox ();
			if (result[0]->flags.isVertexUserData)
				(result[0]->vertexInfos).SetSize (result[0]->nVertices + 1);
			if (result[0]->flags.isEdgeUserData)
				(result[0]->inhEdgeInfos).SetSize (result[0]->nVertices + 1);
		}
	} else {
		ThrowGeometryExceptionAtError (Error, "CorePolygon2D::CreateCommonEdgeSections", __FILE__, __LINE__);
	}

	for (UIndex polyIdx = 0; polyIdx < result.GetSize (); polyIdx++)
		result[polyIdx]->RemoveSmallArcs ();

	DBCHECKCOREPOLY_CHECKRESULT;
	return changed;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertCommonXLineOnPolygon (double x, bool& changed, const EdgeSplitControl& cntrl)
{
	changed = false;
	for (UIndex iEdge = 1; iEdge <= GetEdgeNum (); ++iEdge) {
		Sector s;
		GenArc a;
		Point2D newArcP[2];
		double newAngleP[2];
		Point2D newP;
		if (GetSector (iEdge, s, a)) {		// arc
			UIndex arcIndex = GetInternalArcIdx (iEdge);
			double origArcAngle = arcs[arcIndex].arcAngle;
			Box2DData sBox = GetGenArcBoundBox (a);
			if (sBox.xMin < x && sBox.xMax > x) {
				bool firstOK, secondOK;
				newArcP[0].x = x;
				newArcP[1].x = x;
				Point2D origo = a.GetOrigo ();
				double dist = sqrt ((a.GetMainAxisLength () * a.GetMainAxisLength ()) - ((x - origo.x) * (x - origo.x)));
				newArcP[0].y = origo.y + dist;
				newArcP[1].y = origo.y - dist;
				firstOK = ValidGenArcPointEps (&a, &newArcP[0], Eps);
				secondOK = ValidGenArcPointEps (&a, &newArcP[1], Eps);
				if (!firstOK && !secondOK)
					continue;
				if (firstOK)
					newAngleP[0] = ComputeRotFi (origo, a.GetBegC(), newArcP[0], origArcAngle < 0.0);
				if (secondOK)
					newAngleP[1] = ComputeRotFi (origo, a.GetBegC(), newArcP[1], origArcAngle < 0.0);
				if (firstOK ^ secondOK) {
					if ((DistSqr (newArcP[firstOK ? 0 : 1], a.GetBegC()) > 4.0 * Eps * Eps) && (DistSqr (newArcP[firstOK ? 0 : 1], a.GetEndC()) > 4.0 * Eps * Eps) &&
						cntrl.AllowSplit (a, newArcP[firstOK ? 0 : 1])) {
						InsertVertexInternal (iEdge, newArcP[firstOK ? 0 : 1], true, true);
						changed = true;
						PolyArcRec newArc;
						newArc.begIndex = iEdge;
						newArc.endIndex = iEdge + 1;
						newArc.arcAngle = newAngleP[firstOK ? 0 : 1];
						++nArcs;
						arcs.Insert (arcIndex, newArc);
						arcs[arcIndex + 1].arcAngle = origArcAngle - newAngleP[firstOK ? 0 : 1];
						iEdge++;
					}
				} else {
					if ((origArcAngle > 0.0 && newAngleP[0] > newAngleP[1]) || (origArcAngle < 0.0 && newAngleP[0] < newAngleP[1])) {
						Point2D tmp;
						double angTmp;
						angTmp = newAngleP[0];
						newAngleP[0] = newAngleP[1];
						newAngleP[1] = angTmp;
						tmp = newArcP[0];
						newArcP[0] = newArcP[1];
						newArcP[1] = tmp;
					}
					if ((DistSqr (newArcP[0], a.GetBegC()) > 4.0 * Eps * Eps) && (DistSqr (newArcP[0], a.GetEndC()) > 4.0 * Eps * Eps) &&
						cntrl.AllowSplit (a, newArcP[0])) {
						InsertVertexInternal (iEdge, newArcP[0], true, true);
						changed = true;
						PolyArcRec newArc;
						newArc.begIndex = iEdge;
						newArc.endIndex = iEdge + 1;
						newArc.arcAngle = newAngleP[0];
						++nArcs;
						arcs.Insert (arcIndex, newArc);
						arcs[arcIndex + 1].arcAngle = origArcAngle - newAngleP[0];
						origArcAngle = origArcAngle - newAngleP[0];
						arcIndex++;
						iEdge++;
					}
					if ((DistSqr (newArcP[1], newArcP[0]) > 4.0 * Eps * Eps) && (DistSqr (newArcP[1], a.GetEndC()) > 4.0 * Eps * Eps) &&
						cntrl.AllowSplit (a, newArcP[1])) {
						InsertVertexInternal (iEdge, newArcP[1], true, true);
						changed = true;
						PolyArcRec newArc;
						newArc.begIndex = iEdge;
						newArc.endIndex = iEdge + 1;
						newArc.arcAngle = newAngleP[1] - newAngleP[0];
						++nArcs;
						arcs.Insert (arcIndex, newArc);
						arcs[arcIndex + 1].arcAngle = origArcAngle - (newAngleP[1] - newAngleP[0]);
						iEdge++;
					}
				}
			}
		} else {
			Box2DData sBox = SectorBox (&s);
			if (sBox.xMin < x && sBox.xMax > x) {
				newP.x = x;
				newP.y = s.c1.y + (s.c2.y - s.c1.y) * (x - s.c1.x) / (s.c2.x - s.c1.x);
				if ((DistSqr (newP, s.c1) > Eps * Eps) && (DistSqr (newP, s.c2) > Eps * Eps) && cntrl.AllowSplit (s, newP) ) {
					InsertVertexInternal (iEdge, newP, false, false);
					changed = true;
					iEdge++;
				}
			}
		}
	}
	if (changed == true)
		UpdateBoundingBox ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertCommonYLineOnPolygon (double y, bool& changed, const EdgeSplitControl& cntrl)
{
	changed = false;
	for (UIndex iEdge = 1; iEdge <= GetEdgeNum (); ++iEdge) {
		Sector s;
		GenArc a;
		Point2D newArcP[2];
		double newAngleP[2];
		Point2D newP;
		if (GetSector (iEdge, s, a)) {		// arc
			UIndex arcIndex = GetInternalArcIdx (iEdge);
			double origArcAngle = arcs[arcIndex].arcAngle;
			Box2DData sBox = GetGenArcBoundBox (a);
			if (sBox.yMin < y && sBox.yMax > y) {
				bool firstOK, secondOK;
				newArcP[0].y = y;
				newArcP[1].y = y;
				Point2D origo = a.GetOrigo ();
				double dist = sqrt ((a.GetMainAxisLength () * a.GetMainAxisLength ()) - ((y - origo.y) * (y - origo.y)));
				newArcP[0].x = origo.x + dist;
				newArcP[1].x = origo.x - dist;
				firstOK = ValidGenArcPointEps (&a, &newArcP[0], Eps);
				secondOK = ValidGenArcPointEps (&a, &newArcP[1], Eps);
				if (!firstOK && !secondOK)
					continue;
				if (firstOK)
					newAngleP[0] = ComputeRotFi (origo, a.GetBegC(), newArcP[0], origArcAngle < 0.0);
				if (secondOK)
					newAngleP[1] = ComputeRotFi (origo, a.GetBegC(), newArcP[1], origArcAngle < 0.0);
				if (firstOK ^ secondOK) {
					if ((DistSqr (newArcP[firstOK ? 0 : 1], a.GetBegC()) > 4.0 * Eps * Eps) && (DistSqr (newArcP[firstOK ? 0 : 1], a.GetEndC()) > 4.0 * Eps * Eps) &&
						cntrl.AllowSplit (a, newArcP[firstOK ? 0 : 1])) {
						InsertVertexInternal (iEdge, newArcP[firstOK ? 0 : 1], true, true);
						changed = true;
						PolyArcRec newArc;
						newArc.begIndex = iEdge;
						newArc.endIndex = iEdge + 1;
						newArc.arcAngle = newAngleP[firstOK ? 0 : 1];
						++nArcs;
						arcs.Insert (arcIndex, newArc);
						arcs[arcIndex + 1].arcAngle = origArcAngle - newAngleP[firstOK ? 0 : 1];
						iEdge++;
					}
				} else {
					if ((origArcAngle > 0.0 && newAngleP[0] > newAngleP[1]) || (origArcAngle < 0.0 && newAngleP[0] < newAngleP[1])) {
						Point2D tmp;
						double angTmp;
						angTmp = newAngleP[0];
						newAngleP[0] = newAngleP[1];
						newAngleP[1] = angTmp;
						tmp = newArcP[0];
						newArcP[0] = newArcP[1];
						newArcP[1] = tmp;
					}
					if ((DistSqr (newArcP[0], a.GetBegC()) > 4.0 * Eps * Eps) && (DistSqr (newArcP[0], a.GetEndC()) > 4.0 * Eps * Eps) &&
						cntrl.AllowSplit (a, newArcP[0])) {
						InsertVertexInternal (iEdge, newArcP[0], true, true);
						changed = true;
						PolyArcRec newArc;
						newArc.begIndex = iEdge;
						newArc.endIndex = iEdge + 1;
						newArc.arcAngle = newAngleP[0];
						++nArcs;
						arcs.Insert (arcIndex, newArc);
						arcs[arcIndex + 1].arcAngle = origArcAngle - newAngleP[0];
						origArcAngle = origArcAngle - newAngleP[0];
						arcIndex++;
						iEdge++;
					}
					if ((DistSqr (newArcP[1], newArcP[0]) > 4.0 * Eps * Eps) && (DistSqr (newArcP[1], a.GetEndC()) > 4.0 * Eps * Eps) &&
						cntrl.AllowSplit (a, newArcP[1])) {
						InsertVertexInternal (iEdge, newArcP[1], true, true);
						changed = true;
						PolyArcRec newArc;
						newArc.begIndex = iEdge;
						newArc.endIndex = iEdge + 1;
						newArc.arcAngle = newAngleP[1] - newAngleP[0];
						++nArcs;
						arcs.Insert (arcIndex, newArc);
						arcs[arcIndex + 1].arcAngle = origArcAngle - (newAngleP[1] - newAngleP[0]);
						iEdge++;
					}
				}
			}
		} else {
			Box2DData sBox = SectorBox (&s);
			if (sBox.yMin < y && sBox.yMax > y) {
				newP.y = y;
				newP.x = s.c1.x + (s.c2.x - s.c1.x) * (y - s.c1.y) / (s.c2.y - s.c1.y);
				if ((DistSqr (newP, s.c1) > Eps * Eps) && (DistSqr (newP, s.c2) > Eps * Eps) && cntrl.AllowSplit (s, newP)) {
					InsertVertexInternal (iEdge, newP, false, false);
					changed = true;
					iEdge++;
				}
			}
		}
	}
	if (changed == true)
		UpdateBoundingBox ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::UnifyWithOnePoly (GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& poly2DArray, PolyHoleHandling holeHandling /*= ReturnHoles*/)
{
	if (poly2DArray.GetSize () != 1)
		ThrowGeometryExceptionAtError (Error, "CorePolygon2D::Unify", __FILE__, __LINE__);

	Geometry::PGPOLYEXT			polyExt1;
	GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > result;
	(poly2DArray)[0]->MakePolyExt (polyExt1);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	PGBooleanOperations pgBool (nullptr /*breaker*/);
	PGRelPolyPosExt status = pgBool.DoBoolean (&polyExt1, nullptr, WindingRulePos, WindingRulePos, AUnionB, nullptr, holeHandling);

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly;
	switch (status) {
	case PolysOverlap:
	case PolysDisjunct_Edge:
		pgBool.GetResultPolygons (&resPolyExt);
		for (UIndex polyIdx = 0; polyIdx < result.GetSize (); polyIdx++)
			result[polyIdx]->status.isRegularized = true;
		DBCHECKCOREPOLY_CHECKRESULT;

		poly2DArray.Clear (true);
		poly2DArray = result;
		break;
	case PolysDisjunct:
	case PolysDisjunct_Node:
	case Poly2HasZeroArea:
	case Poly1CoversPoly2:
	case PolysEqual:				// the solution is the 1st input poly
		DBASSERT (result.GetSize () == 0);
		if (holeHandling != ReturnHoles && poly2DArray[0]->GetContourNum () > 1) { //Tolrolni kell a lyukakat
			pgBool.GetResultPolygons (&resPolyExt);
			for (UIndex polyIdx = 0; polyIdx < result.GetSize (); polyIdx++)
				result[polyIdx]->status.isRegularized = true;
			DBCHECKCOREPOLY_CHECKRESULT;

			poly2DArray.Clear (true);
			poly2DArray = result;
		} else {
			tmpPoly = poly2DArray[0];
			poly2DArray.Clear (true);
			poly2DArray.Push (tmpPoly);
		}
		break;
	case Poly1HasZeroArea:
	case Poly2CoversPoly1:			// the solution is the 2nd input poly
		DBBREAK ();
		break;
	case UnknownStatus:
	default:
		ThrowGeometryExceptionAtError (Error, "CorePolygon2D::Unify", __FILE__, __LINE__);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::UnifyWithTwoPoly (GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& poly2DArray, PolyHoleHandling holeHandling /*= ReturnHoles*/)
{
	if (poly2DArray.GetSize () != 2)
		ThrowGeometryExceptionAtError (Error, "CorePolygon2D::Unify", __FILE__, __LINE__);

	Geometry::PGPOLYEXT			polyExt1;
	Geometry::PGPOLYEXT			polyExt2;
	GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > result;
	(poly2DArray)[0]->MakePolyExt (polyExt1);
	(poly2DArray)[1]->MakePolyExt (polyExt2);

	Geometry::PGRESPOLYEXT	resPolyExt;
	BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
	resPolyExt.polygonsData		= (GSPtr) &result;
	resPolyExt.newPolygon		= &NewPolygon;

	PGBooleanOperations pgBool (nullptr /*breaker*/);
	PGRelPolyPosExt status = pgBool.DoBoolean (&polyExt1, &polyExt2, WindingRulePos, WindingRulePos, AUnionB, nullptr, holeHandling);

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > tmpPoly;
	switch (status) {
	case PolysOverlap:
	case PolysDisjunct_Edge:
		pgBool.GetResultPolygons (&resPolyExt);
		for (UIndex polyIdx = 0; polyIdx < result.GetSize (); polyIdx++) {
			result[polyIdx]->RemoveSmallArcs ();
			result[polyIdx]->status.isRegularized = true;
		}
		DBCHECKCOREPOLY_CHECKRESULT;

		poly2DArray.Clear (true);
		poly2DArray = result;
		break;
	case Poly2HasZeroArea:
	case Poly1CoversPoly2:
	case PolysEqual:				// the solution is the 1st input poly
		if (holeHandling != ReturnHoles && poly2DArray[0]->GetContourNum () > 1) { //Tolrolni kell a lyukakat
			pgBool.GetResultPolygons (&resPolyExt);
			for (UIndex polyIdx = 0; polyIdx < result.GetSize (); polyIdx++)
				result[polyIdx]->status.isRegularized = true;
			DBCHECKCOREPOLY_CHECKRESULT;

			poly2DArray.Clear (true);
			poly2DArray = result;
		} else {
			DBASSERT (result.GetSize () == 0);
			tmpPoly = poly2DArray[0];
			poly2DArray.Clear (true);
			poly2DArray.Push (tmpPoly);
		}
		break;
	case Poly1HasZeroArea:
	case Poly2CoversPoly1:			// the solution is the 2nd input poly
		DBASSERT (result.GetSize () == 0);
		if (holeHandling != ReturnHoles && poly2DArray[1]->GetContourNum () > 1) { //Tolrolni kell a lyukakat
			pgBool.GetResultPolygons (&resPolyExt);
			for (UIndex polyIdx = 0; polyIdx < result.GetSize (); polyIdx++)
				result[polyIdx]->status.isRegularized = true;
			DBCHECKCOREPOLY_CHECKRESULT;

			poly2DArray.Clear (true);
			poly2DArray = result;
		} else {
			tmpPoly = poly2DArray[1];
			poly2DArray.Clear (true);
			poly2DArray.Push (tmpPoly);
		}
		break;
	case PolysDisjunct:
	case PolysDisjunct_Node:		// the solution is both input polys
		DBASSERT (result.GetSize () == 0);
		if (holeHandling != ReturnHoles && (poly2DArray[0]->GetContourNum () > 1 || poly2DArray[1]->GetContourNum () > 1)) { //Tolrolni kell a lyukakat
			pgBool.GetResultPolygons (&resPolyExt);
			for (UIndex polyIdx = 0; polyIdx < result.GetSize (); polyIdx++)
				result[polyIdx]->status.isRegularized = true;
			DBCHECKCOREPOLY_CHECKRESULT;

			poly2DArray.Clear (true);
			poly2DArray = result;
		}
		break;
	case UnknownStatus:
	default:
		ThrowGeometryExceptionAtError (Error, "CorePolygon2D::Unify", __FILE__, __LINE__);
	}
}

//TODO !!!! nem talalja a DoBoolean-t mag mast is (edddig megtalalta, miota a polygon2D es IrregularPolygon2D templates azota nem talalja !!! ???
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Unify (GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& poly2DArray, PolyHoleHandling holeHandling /*= ReturnHoles*/)
{
	if (poly2DArray.GetSize () == 0)
		return;

	if (poly2DArray.GetSize () == 1 && holeHandling == ReturnHoles)
		return;

	if (poly2DArray.GetSize () == 1) {
		UnifyWithOnePoly (poly2DArray, holeHandling);
	} else if (poly2DArray.GetSize () == 2) {
		UnifyWithTwoPoly (poly2DArray, holeHandling);
	} else {
		DBASSERT (poly2DArray.GetSize () != 0);
		if (poly2DArray.GetSize () == 0) {
			ThrowGeometryExceptionAtError (Error, "CorePolygon2D::Unify", __FILE__, __LINE__);
		}

		Geometry::PGPOLYEXT			polyExt1;
		MakePolyExtArr (poly2DArray, polyExt1);
		GS::ArrayFB<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >, 6 > result;

		Geometry::PGRESPOLYEXT	resPolyExt;
		BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
		resPolyExt.polygonsData		= (GSPtr) &result;
		resPolyExt.newPolygon		= &NewPolygonArr;

		PGBooleanOperations pgBool (nullptr /*breaker*/);
		/* PGRelPolyPosExt status =*/ pgBool.DoBoolean (&polyExt1, nullptr, WindingRulePos, WindingRulePos, AUnionB, nullptr, holeHandling);
		pgBool.GetResultPolygons (&resPolyExt);
		for (UIndex polyIdx = 0; polyIdx < result.GetSize (); polyIdx++) {
			result[polyIdx]->RemoveSmallArcs ();
			result[polyIdx]->status.isRegularized = true;
		}
		DBCHECKCOREPOLY_CHECKRESULT;

		poly2DArray.Clear (true);
		poly2DArray = result;
	}
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>>>
CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Substract (
	const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>>>&	minuendPolygons,
	const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>>>&	subtrahendPolygons,
	bool*																											changed)
{
	if (changed != nullptr) {
		*changed = false;
	}

	if (subtrahendPolygons.IsEmpty ()) {
		return minuendPolygons;
	}

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>>> resultPolygons;
	for (const GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>>& minuendPolygon : minuendPolygons) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>>> actualMinuendPolygons;
		actualMinuendPolygons.Push (minuendPolygon);
		Geometry::PGPOLYEXT polyExt1;
		MakePolyExtArr (actualMinuendPolygons, polyExt1);

		Geometry::PGPOLYEXT polyExt2;
		MakePolyExtArr (subtrahendPolygons, polyExt2);

		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>>> result;
		Geometry::PGRESPOLYEXT resPolyExt;
		BNZeroMemory (&resPolyExt, sizeof (resPolyExt));
		resPolyExt.polygonsData = (GSPtr)&result;
		resPolyExt.newPolygon = &NewPolygonArr;

		PGBooleanOperations pgBool (nullptr);
		PGRelPolyPosExt pgStatus = pgBool.DoBoolean (&polyExt1, &polyExt2, WindingRulePos, WindingRulePos, AMinusB);
		pgBool.GetResultPolygons (&resPolyExt);
		if (changed != nullptr) {
			RelativePosition relativePosition;
			ConvPgstatusToReletivePos (pgStatus, Boundary_Closed, &relativePosition, nullptr);
			*changed |= (relativePosition != RelativePosition_Disjunct);
		}

		for (typename GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >::Iterator it = result.Enumerate (); it != nullptr; ++it) {
			(*it)->RemoveSmallArcs ();
			(*it)->status.isRegularized = true;
		}

		DBCHECKCOREPOLY_CHECKRESULT;

		resultPolygons.Append (result);
	}
	return resultPolygons;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AUnionB (bool a, bool b)
{
	return a || b;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AMinusB (bool a, bool b)
{
	return a && !b;
}

// Debug
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Dump3DGDL (Geometry::Plane * thePlane, GS::OChannel& oc) const
{
	Geometry::Plane plane;
	if (thePlane != nullptr )
		plane = *thePlane;

	if (GetVertexNum () == 0)
		return;
	if (GetEdgeNum () == 0)
		return;
	if (nContours == 0)
		return;

	oc << "!polygon\n";
	USize vertCntr = 0;
	std::map <UIndex, USize> vertexRenumber;
	UIndex	iContour;
	for (iContour = 1; iContour <= nContours; iContour++) {
		UIndex iFirstVertex = iContour == 1 ? 1 : contourEnds[iContour - 1] + 1;
		UIndex iVertex;
		for (iVertex = iFirstVertex; iVertex < contourEnds[iContour]; iVertex++) {
			vertexRenumber[iVertex] = ++vertCntr;
			const Point2D & c2D = vertices[iVertex];
			const Geometry::Point3D	c3D = plane.PlaneToWorld (c2D.x, c2D.y, 0.0);

			oc << "vert " << c3D.x << ", " << c3D.y << ", " << c3D.z << "\t! V" << vertCntr << "\n";
		}
	}

	USize edgeCntr = 0;
	for (iContour = 1; iContour <= nContours; iContour++) {
		UIndex iFirstVertex = iContour == 1 ? 1 : contourEnds[iContour - 1] + 1;
		UIndex iVertex;
		for (iVertex = iFirstVertex; iVertex + 1 < contourEnds[iContour]; iVertex++) {
			++edgeCntr;
			oc << "edge " << vertexRenumber[iVertex] << ", " << vertexRenumber[iVertex+1] << ", " << -1 << ", " << -1 << ", " << 0 << "\t! E" << edgeCntr << "\n";
		}

		++edgeCntr;
		oc << "edge " << vertexRenumber[iVertex] << ", " << vertexRenumber[iFirstVertex] << ", " << -1 << ", " << -1 << ", " << 0 << "\t! E" << edgeCntr << "\n";
	}

	oc << "pgon	" << (edgeCntr +  nContours - 1) << ", 0, 0,\n\t";

	edgeCntr = 0;
	for (iContour = 1; iContour <= nContours; iContour++) {
		if (iContour > 1) {
			oc << ",\n\t 0, !Hole starts here\n\t";	//signal of hole
		}

		UIndex iFirstVertex = iContour == 1 ? 1 : contourEnds[iContour - 1] + 1;
		UIndex iVertex;
		USize edgeInContourCntr = 0;
		for (iVertex = iFirstVertex; iVertex < contourEnds[iContour]; iVertex++, ++edgeInContourCntr) {
			if (iVertex > iFirstVertex) {
				oc << ", ";
				if ((edgeInContourCntr % 6) == 0) {
					oc << "\n\t";
				}
			}

			++edgeCntr;
			oc << edgeCntr;
		}
	}

	oc << "\nbody -1\n";
	oc << "!End polygon\n\n";
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
template <class Output>
void CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Print (Output& oc) const
{
	/*if (PGGetDebugFlagsExt () == 0) {
		return;
	}*/

	oc << "\n!***-----------------***\n\n";
	oc << "!CorePolygon2D at " << this << "\n";

	oc << "!\tBounding Box: [ ";
	oc << " xMin: " << boundBox.xMin;
	oc << " yMin: " << boundBox.yMin;
	oc << " xMax: " << boundBox.xMax;
	oc << " yMax: " << boundBox.yMax;
	oc << "]\n";

	oc << "!\t Contours: " << nContours << "\t";
	oc << "\t Vertices: " << nVertices << "\t";
	oc << "\t Arcs:	" << nArcs << "\n";


	oc << "POLY2_ " << nVertices + 2 * nArcs << " , 7";

	UIndex	iContour;
	for (iContour = 1; iContour <= nContours; iContour++) {
		UIndex iFirstVertex = iContour == 1 ? 1 : contourEnds[iContour - 1] + 1;
		UIndex iVertex;
		oc << ",\n";
		for (iVertex = iFirstVertex; iVertex < contourEnds[iContour]; iVertex++) {
			bool isArc = false;
			UIndex iArc;
			for (iArc = 1; iArc <= nArcs; iArc++) {
				if (arcs[iArc].begIndex == iVertex) {
					isArc = true;
					break;
				}
			}
			oc << vertices[iVertex].x << ",  " << vertices[iVertex].y << ",  1,\n";
			if (isArc) {
				Point2D	begC, endC, origo;
				begC.x = vertices[arcs[iArc].begIndex].x;
				begC.y = vertices[arcs[iArc].begIndex].y;
				endC.x = vertices[arcs[iArc].endIndex].x;
				endC.y = vertices[arcs[iArc].endIndex].y;
				double angle = arcs[iArc].arcAngle;
				if (ArcGetOrigo (&begC, &endC, angle, &origo)) {
					oc << origo.x << ",  " << origo.y << ",  900,\n";
					oc << 0 << ",  " << angle * 180 / PI << ",  4001,\n";
				}
			}
		}
		oc << vertices[iVertex].x << ",  " << vertices[iVertex].y << ",  -1";
	}
	oc << "\n";

	oc << "\n! UserData \tp: ";
	if (inhPolygonInfo.GetSize() != 0 && flags.isPolygonUserData) {
		const PolygonUserData* polyId = GetUserData ();
		if (polyId != nullptr) {
//			oc << polyId->Get () << "\n!\t\t v\te\tc\n";
			polyId->Print (oc);
			oc << "\n!\t\t v\te\tc\n";
		} else
			oc << "-\n!\t\t v\te\tc\n";
	} else
		oc << "-\n!\t\t v\te\tc\n";
	for (iContour = 1; iContour <= nContours; iContour++) {
		UIndex iFirstVertex = iContour == 1 ? 1 : contourEnds[iContour - 1] + 1;
		const ContourUserData* contId = nullptr;
		if (contourInfos.GetSize() != 0 && flags.isContourUserData)
			contId = GetContourUserData (iContour);
		UIndex iVertex;
		for (iVertex = iFirstVertex; iVertex < contourEnds[iContour]; iVertex++) {
			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
				const VertexUserData* id = GetVertexUserData (InternalVertexIdx2VertexIdx(iVertex));
				if (id != nullptr)
//					oc << "![" << iVertex <<"]\t" << id->Get ();
					id->Print (oc);
				else
					oc << "![" << iVertex <<"]\t-";
			} else
				oc << "![" << iVertex <<"]\t-";
			if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
				const EdgeUserData* id = GetEdgeUserData (InternalVertexIdx2VertexIdx(iVertex));
				if (id != nullptr)
//					oc << "\t" << id->Get ();
					id->Print (oc);
				else
					oc << "\t-";
			} else
				oc << "\t-";
			if (contId != nullptr) {
//				oc << "\t" << contId->Get () << "\n";
				contId->Print (oc);
				oc << "\n";
			} else
				oc << "\t-\n";
		}
		if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
			const VertexUserData* id = GetVertexUserData (InternalVertexIdx2VertexIdx(iFirstVertex));
			if (id != nullptr)
//				oc << "![" << iVertex <<"]\t" << id->Get ();
				id->Print (oc);
			else
				oc << "![" << iVertex <<"]\t-";
		} else
			oc << "![" << iVertex <<"]\t-";
		if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
			const EdgeUserData* id = GetEdgeUserData (InternalVertexIdx2VertexIdx(iFirstVertex));
			if (id != nullptr)
//				oc << "\t" << id->Get ();
				id->Print (oc);
			else
				oc << "\t-";
		} else
			oc << "\t-";
		if (contId != nullptr) {
//			oc << "\t" << contId->Get () << "\n";
			contId->Print (oc);
			oc << "\n";
		} else
			oc << "\t-\n";
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CheckSizes (void) const
{
	/* check for geometric data */
	if (nContours < 1 || nContours > nVertices / 2) {
		DBPRINTF ("CorePolygon2D::Check: polygon has wrong contour number!\n");
		return false;
	}
	if (contourEnds.GetSize () != (nContours + 1)) {
		DBPRINTF ("CorePolygon2D::Check: polygon has wrong contour!\n");
		return false;
	}
	if (nVertices < 2) {
		DBPRINTF ("CorePolygon2D::Check: polygon has wrong vertices number!\n");
		return false;
	}
	if (vertices.GetSize () != (nVertices + 1)) {
		DBPRINTF ("CorePolygon2D::Check: polygon has wrong vertices!\n");
		return false;
	}
	if (nArcs >= nVertices) {
		DBPRINTF ("CorePolygon2D::Check: polygon has wrong arcs number!\n");
		return false;
	}
	if (nArcs != 0 && arcs.GetSize () != nArcs + 1) {
		DBPRINTF ("CorePolygon2D::Check: polygon has wrong arcs!\n");
		return false;
	}
	if (nArcs == 0 && arcs.GetSize () != 1) {
		DBPRINTF ("CorePolygon2D::Check: polygon has wrong arcs!\n");
		return false;
	}

	if (flags.isContourUserData) {
		if (contourInfos.GetSize() == 0) {
			DBPRINTF ("CorePolygon2D::Check: polygon has wrong contourInfos!\n");
			return false;
		}
		if (contourInfos.GetSize() < (nContours + 1)) {
			DBPRINTF ("CorePolygon2D::Check: polygon has wrong contourInfos handle!\n");
			return false;
		}
	} else {
		if (contourInfos.GetSize() != 0) {
			DBPRINTF ("CorePolygon2D::Check: polygon has wrong contourInfos!\n");
			return false;
		}
	}
	if (flags.isVertexUserData) {
		if (vertexInfos.GetSize() == 0) {
			DBPRINTF ("CorePolygon2D::Check: polygon has wrong vertexInfos!\n");
			return false;
		}
		if (vertexInfos.GetSize() < (nVertices + 1)) {
			DBPRINTF ("CorePolygon2D::Check: polygon has wrong vertexInfos handle!\n");
			return false;
		}
	} else {
		if (vertexInfos.GetSize() != 0) {
			DBPRINTF ("CorePolygon2D::Check: polygon has wrong vertexInfos!");
			return false;
		}
	}
	if (flags.isEdgeUserData) {
		if (inhEdgeInfos.GetSize() == 0) {
			DBPRINTF ("CorePolygon2D::Check: polygon has wrong inhEdgeInfos!");
			return false;
		}
		if (inhEdgeInfos.GetSize() < (nVertices + 1)) {
			DBPRINTF ("CorePolygon2D::Check: polygon has wrong inhEdgeInfos handle!\n");
			return false;
		}
	} else {
		if (inhEdgeInfos.GetSize() != 0 /*inhEdgeInfos != nullptr*/) {
			DBPRINTF ("CorePolygon2D::Check: polygon has wrong inhEdgeInfos!\n");
			return false;
		}
	}
	if (flags.isPolygonUserData) {
		if (inhPolygonInfo.GetSize() != 1) {
			DBPRINTF ("CorePolygon2D::Check: polygon has wrong inhPolygonInfo!\n");
			return false;
		}
	} else {
		if (inhPolygonInfo.GetSize() != 0) {
			DBPRINTF ("CorePolygon2D::Check: polygon has wrong inhPolygonInfo!\n");
			return false;
		}
	}
	return true;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CheckVertices	(PolyCheckFlags checkFlags, PolyCheckFlags* errorType, double coordUpperRange) const
{
	//check the contents of vertices
	if ((checkFlags & PolyCheckFlags_Zero0thElements) != 0) {
		if (vertices[0].x != 0.0 ||
			vertices[0].y != 0.0)
		{
			DBPRINTF ("CorePolygon2D::Check: 0. vertex!\n");
			if (errorType != nullptr)
				*errorType = PolyCheckFlags_Zero0thElements;
			return false;
		}
	}
	if ((checkFlags & PolyCheckFlags_InvalidDoubles) != 0) {
		for (UIndex vertexIdx = 1; vertexIdx <= nVertices; ++vertexIdx) {
			if (GS::ClassifyDouble (vertices[vertexIdx].x) <= GS::DoubleClass::Infinite ||
				GS::ClassifyDouble (vertices[vertexIdx].y) <= GS::DoubleClass::Infinite)
			{
				DBPRINTF ("CorePolygon2D::Check: invalid coord value!\n");
				if (errorType != nullptr)
					*errorType = PolyCheckFlags_InvalidDoubles;
				return false;
			}
		}
	}
	if ((checkFlags & PolyCheckFlags_DenormalDoubles) != 0) {
		for (UIndex vertexIdx = 1; vertexIdx <= nVertices; ++vertexIdx) {
			if (GS::ClassifyDouble (vertices[vertexIdx].x) == GS::DoubleClass::Denormal ||
				GS::ClassifyDouble (vertices[vertexIdx].y) == GS::DoubleClass::Denormal)
			{
				DBPRINTF ("CorePolygon2D::Check: invalid coord value!\n");
				if (errorType != nullptr)
					*errorType = PolyCheckFlags_DenormalDoubles;
				return false;
			}
		}
	}
	if ((checkFlags & PolyCheckFlags_CoordRange) != 0) {
		for (UIndex vertexIdx = 1; vertexIdx <= nVertices; ++vertexIdx) {
			if (!CheckCoord (vertices[vertexIdx], coordUpperRange)) {
				DBPRINTF ("CorePolygon2D::Check: coord value out of range!\n");
				if (errorType != nullptr)
					*errorType = PolyCheckFlags_CoordRange;
				return false;
			}
		}
	}
	return true;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CheckContourEnds	(PolyCheckFlags checkFlags, PolyCheckFlags* errorType) const
{
	/* check the contents of contourEnds */
	if ((checkFlags & PolyCheckFlags_Zero0thElements) != 0) {
		if (contourEnds[0] != 0) {
			DBPRINTF ("CorePolygon2D::Check: 0. contour End!\n");
			if (errorType != nullptr)
				*errorType = PolyCheckFlags_Zero0thElements;
			return false;
		}
	}

	if (contourEnds[nContours] != nVertices) {
		DBPRINTF ("CorePolygon2D::Check: last contour End!\n");
		return false;
	}
	for (UIndex iContour = 1; iContour <= nContours; iContour++) {
		UIndex iFirstContourVertex = (iContour == 1) ? 1 : contourEnds[iContour - 1] + 1;
		UIndex iLastContourVertex = contourEnds[iContour];

		if (iFirstContourVertex < 1 || iLastContourVertex > nVertices || iLastContourVertex < iFirstContourVertex) {
			DBPRINTF ("CorePolygon2D::Check: contourEnds have false indices!\n");
			return false;
		}
		if (!Geometry::IsEqualCoord (vertices[iFirstContourVertex], vertices[iLastContourVertex], Eps)) {
			DBPRINTF ("CorePolygon2D::Check: not closed contour!\n");
			return false;
		}

		if (flags.isVertexUserData) {
			if (vertexInfos [iFirstContourVertex] != vertexInfos [iLastContourVertex]) {
				DBPRINTF ("CorePolygon2D::Check: not closed contour! (vertexData)\n");
				return false;
			}
		}
		if (flags.isEdgeUserData) {
			if (inhEdgeInfos [iFirstContourVertex] != inhEdgeInfos [iLastContourVertex]) {
				DBPRINTF ("CorePolygon2D::Check: not closed contour! (edgeData)\n");
				return false;
			}
		}
	}
	if ((checkFlags & PolyCheckFlags_ContourHasFewVertices) !=0) {
		for (UIndex iContour = 1; iContour <= nContours; iContour++) {
			UIndex iFirstContourVertex = (iContour == 1) ? 1 : contourEnds[iContour - 1] + 1;
			UIndex iLastContourVertex = contourEnds[iContour];
			if (iLastContourVertex - iFirstContourVertex < 2) {
				DBPRINTF ("CorePolygon2D::Check: few vertex in contour!\n");
				if (errorType != nullptr)
					*errorType = PolyCheckFlags_ContourHasFewVertices;
				return false;
			}
		}
	}
	return true;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CheckArcs	(PolyCheckFlags checkFlags, PolyCheckFlags* errorType) const
{
	/* check the contents of arcs */
	if ((checkFlags & PolyCheckFlags_Zero0thElements) != 0) {
		if (arcs[0].begIndex != 0 ||
			arcs[0].endIndex != 0 ||
			arcs[0].arcAngle != 0.0)
		{
			DBPRINTF ("CorePolyline2D::Check: 0. arc!\n");
			if (errorType != nullptr)
				*errorType = PolyCheckFlags_Zero0thElements;
			return false;
		}
	}
	Point2D dummyOrigin;
	for (UIndex iArc = 1; iArc <= nArcs; ++iArc) {
		UIndex begIndex = arcs[iArc].begIndex;
		UIndex endIndex = arcs[iArc].endIndex;
		// Because of bug #122629, we do not want to be too strict in this
		// check. Once the reason for that bug is found and fixed, strictness
		// can be restored here.
		if (begIndex < 1 || begIndex > nVertices - 1) {
			DBPRINTF ("CorePolygon2D::Check: arcs have false begIndex indices\n");
			return false;
		}
		if (endIndex < 2 || endIndex > nVertices) {
			DBPRINTF ("CorePolygon2D::Check: arcs have false endIndex indices\n");
			return false;
		}
		if (endIndex != begIndex + 1) {
			DBPRINTF ("CorePolygon2D::Check: Invalid arc\n");
			return false;
		}
		if ((checkFlags & PolyCheckFlags_TooSmallArcs) != 0) {
			if (fabs (arcs[iArc].arcAngle) < RadEps) {
				DBPRINTF ("Invalid arcAngle\n");
				if (errorType != nullptr)
					*errorType = PolyCheckFlags_TooSmallArcs;
				return false;
			}
			if (!CanCalculateArcOrigo (iArc)) {
				DBPRINTF ("Failed to calculate arc origin\n");
				if (errorType != nullptr)
					*errorType = PolyCheckFlags_TooSmallArcs;
				return false;
			}
		}
	}
	return true;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CanCalculateArcOrigo (UIndex internalArcIdx) const
{
	if (DBERROR (internalArcIdx < 1 || internalArcIdx > nArcs)) {
		return false;
	}
	UIndex begIndex = arcs[internalArcIdx].begIndex;
	UIndex endIndex = arcs[internalArcIdx].endIndex;

	Point2D dummyOrigin;
	return ArcGetOrigo (&vertices[begIndex], &vertices[endIndex], arcs[internalArcIdx].arcAngle, &dummyOrigin);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Check (PolyCheckFlags checkFlags, PolyCheckFlags* errorType, double coordUpperRange) const
{
	DBASSERT ((checkFlags & PolyCheckFlags_CoordRange) == 0 || (IsPositive(coordUpperRange) && (checkFlags & PolyCheckFlags_InvalidDoubles) != 0));

	if (errorType != nullptr)
		*errorType = static_cast<PolyCheckFlags>(0);

	DBCHECKCOREPOLY_MEMORY;

	if (nContours				== 0 &&
		nVertices				== 0 &&
		nArcs					== 0 &&
		vertices.GetSize ()		== 0 &&
		contourEnds.GetSize ()	== 0 &&
		arcs.GetSize ()			== 0) {
			return true;
	}

	DBASSERT (nVertices < 100000); //Ez nem hiba de azert gyanus

	if (!CheckSizes ())
		return false;

	if (!CheckVertices (checkFlags, errorType, coordUpperRange))
		return false;

	if (!CheckContourEnds (checkFlags, errorType))
		return false;

	if (!CheckArcs (checkFlags, errorType))
		return false;

#ifdef CHECKED_VERSION
	Box2DData calcedBox;
	calcedBox = CalcBoundBox ();
	if (!IsEqualBox (calcedBox, boundBox, Eps)) {
		DBPRINTF ("CorePolygon2D::Check: Invalid bounding box\n");
		return false;
	}
	if (status.isRegularized) {
		if (!CheckOrientInternalData ()) {
			DBPRINTF ("CorePolygon2D::Check: Invalid orientation\n");
			return false;
		}
	}
#endif
	return true;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PolyRepairResult CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Repair (PolyCheckFlags repairType)
{
	DBCHECKCOREPOLY_ONEREFTOTHIS;

	DBASSERT ((repairType & (repairType - 1)) == 0);	// Csak egy bit! http://en.wikipedia.org/wiki/Power_of_two#Fast_algorithm_to_check_if_a_positive_number_is_a_power_of_two

	PolyRepairResult result;
	result.succeeded = result.modified = false;

	switch (repairType) {
		case PolyCheckFlags_Zero0thElements:
			vertices[0].Set(0.0, 0.0);
			arcs[0].begIndex = 0;
			arcs[0].endIndex = 0;
			arcs[0].arcAngle = 0.0;
			contourEnds[0] = 0;
			result.succeeded = result.modified = true;
			return result;
		case PolyCheckFlags_InvalidDoubles:
			return result;
		case PolyCheckFlags_DenormalDoubles:
			for (UIndex i = 1; i < vertices.GetSize (); ++i) {
				if (GS::ClassifyDouble (vertices[i].x) == GS::DoubleClass::Denormal) {
					vertices[i].x = 0.0;
					result.modified = true;
				}
				if (GS::ClassifyDouble (vertices[i].y) == GS::DoubleClass::Denormal) {
					vertices[i].y = 0.0;
					result.modified = true;
				}
			}
			if (result.modified)
				UpdateBoundingBox ();
			result.succeeded = true;
			return result;
		case PolyCheckFlags_CoordRange:
			return result;
		case PolyCheckFlags_ContourHasFewVertices:
			if (contourEnds[1] < 3)
				return result;
			FixingContours ();
			UpdateBoundingBox ();
			result.succeeded = result.modified = true;
			return result;
		case PolyCheckFlags_TooSmallArcs:
		case PolyCheckFlags_All_Polygon:
		case PolyCheckFlags_All_Polyline:
		default:
			DBBREAK ();
			return result;
	}
}

}	// namespace Geometry

#endif //GEOMETRY_COREPOLYGON2D_HPP
