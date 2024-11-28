// *****************************************************************************
//
// Declaration of CorePolygline2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA, RJ
//
// *****************************************************************************

#ifndef GEOMETRY_COREPOLYLINE2D_HPP
#define GEOMETRY_COREPOLYLINE2D_HPP

#pragma once

// --- Includes ----------------------------------------------------------------
#include "CorePolyline2DClassDefinition.hpp"
#include "CorePolygon2DClassDefinition.hpp"
#include "NurbsCurve2D.hpp"

#include <float.h>


namespace Geometry {

#if defined (DEBUVERS)
#define DEBUVERS_POLY2D
#endif

#if defined(DEBUVERS_POLY2D)
#define DBCHECKINDEX(idx, minIdx, maxIdx) DBASSERT ((idx) >= (minIdx) && (idx) <= (maxIdx))

#define DBCHECKPOLY_CHECK DBASSERT (Check (PolyCheckFlags_All_Polyline, nullptr, MaxCoordValue ()))
#define DBCHECKPOLY_CHECKRESULT DBASSERT (result->Check (PolyCheckFlags_All_Polyline, nullptr, MaxCoordValue ()))
#define DBCHECKPOLY_MEMORY
#define DBCHECKPOLY_ONEREFTOTHIS DBASSERT (GetRefCount () <= 1)
#else
#define DBCHECKINDEX(idx, minIdx, maxIdx)

#define DBCHECKPOLY_CHECK
#define DBCHECKPOLY_MEMORY
#define DBCHECKPOLY_CHECKRESULT
#define DBCHECKPOLY_ONEREFTOTHIS
#endif

#define DBCHECKPOLY_NONURBS const_cast<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> *> (this)->DropNurbs ()


// Geometry::CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::NurbsRec

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::NurbsRec::Store (GS::ObjectState& os) const
{
	os.Add ("begIndex", begIndex);
	os.Add ("nurbs", nurbs);
	return NoError;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::NurbsRec::Restore (const GS::ObjectState& os)
{
	os.Get ("begIndex", begIndex);
	os.Get ("nurbs", nurbs);
	return NoError;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::NurbsRec::Read (GS::IChannel& ic)
{
	GSErrCode err = ic.Read (begIndex);
	if (err == NoError)
		err = ic.Read (nurbs);
	return err;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::NurbsRec::Write (GS::OChannel& oc) const
{
	GSErrCode err = oc.Write (begIndex);
	if (err == NoError)
		err = oc.Write (nurbs);
	return err;
}


// Geometry::CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Flags

template<class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Flags::Store (GS::ObjectState& os) const
{
	bool tmpIsSameDirEdgeLegal = isSameDirEdgeLegal;
	bool tmpIsVertexUserData = isVertexUserData;
	bool tmpIsEdgeUserData = isEdgeUserData;
	bool tmpIsPolygonUserData = isPolygonUserData;

	os.Add ("isSameDirEdgeLegal", tmpIsSameDirEdgeLegal);
	os.Add ("isVertexUserData", tmpIsVertexUserData);
	os.Add ("isEdgeUserData", tmpIsEdgeUserData);
	os.Add ("isPolygonUserData", tmpIsPolygonUserData);
	return NoError;
}


template<class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Flags::Restore (const GS::ObjectState& os)
{
	bool tmpIsSameDirEdgeLegal;
	bool tmpIsVertexUserData;
	bool tmpIsEdgeUserData;
	bool tmpIsPolygonUserData;

	os.Get ("isSameDirEdgeLegal", tmpIsSameDirEdgeLegal);
	os.Get ("isVertexUserData", tmpIsVertexUserData);
	os.Get ("isEdgeUserData", tmpIsEdgeUserData);
	os.Get ("isPolygonUserData", tmpIsPolygonUserData);


	isSameDirEdgeLegal = tmpIsSameDirEdgeLegal;
	isVertexUserData = tmpIsVertexUserData;
	isEdgeUserData = tmpIsEdgeUserData;
	isPolygonUserData = tmpIsPolygonUserData;
	return NoError;
}


// Geometry::CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::InitInternalData (void)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	boundBox = Box2DData ();
	flags.Clear ();

	defaultVertexData = VertexUserData ();
	defaultEdgeData = EdgeUserData ();

	inhPolygonInfo.Clear ();

	nVertices = 0;
	vertices.Clear ();
	vertexInfos.Clear ();

	nArcs = 0;
	arcs.Clear ();
	inhEdgeInfos.Clear ();

	nNurbs = 0;
	nurbs.Clear ();

	if (inhPolygonInfo.GetSize() == 0 && flags.isPolygonUserData) {
		inhPolygonInfo.SetSize (1);
	}

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::FreeInternalData (void)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	DBASSERT_GUID (Check (PolyCheckFlags_All_Polyline, nullptr, MaxCoordValue ()), "{6C2D555F-62E3-4966-BF80-F31E33778113}");
	try {
#ifdef DEBUVERS
		nVertices = 0xcdcdcdcd;
		nArcs = 0xcdcdcdcd;
		nNurbs = 0xcdcdcdcd;
#else
		nVertices = 0;
		nArcs = 0;
		nNurbs = 0;
#endif
		vertices.Clear ();
		arcs.Clear ();
		nurbs.Clear ();

		vertexInfos.Clear ();
		inhEdgeInfos.Clear ();
		inhPolygonInfo.Clear();
	} catch (GS::GSException& e) {
		e.Print (dbChannel);
		throw;
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::AllocateInternalData (USize verticesNum, USize arcsNum, USize nurbsNum, USize verticesCapacity /*= 0*/, USize arcsCapacity /*= 0*/, USize nurbsCapacity /*= 0*/)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	try {
		ReallocateInternalData (verticesNum, arcsNum, nurbsNum, verticesCapacity, arcsCapacity, nurbsCapacity);

	} catch (GS::GSException& e) {
		e.Print (dbChannel);
		throw GS::OutOfMemoryException ("Error in CorePolyline2D::AllocateInternalData!!!", __FILE__, __LINE__);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReallocateInternalDataSizes (USize verticesNum, USize arcsNum, USize nurbsNum, USize verticesCapacity, USize arcsCapacity, USize nurbsCapacity)
{
#ifdef DEBUVERS
	DBASSERT (verticesCapacity >= 1);
	//Vagy csak memoriat allokalunk vagy legalabb egy vertex-nek kell lenni
	DBASSERT ((verticesNum == 0 && arcsNum == 0 && nurbsNum == 0) || verticesNum >=0);
#else
UNUSED_PARAMETER (verticesNum);
UNUSED_PARAMETER (arcsNum);
UNUSED_PARAMETER (nurbsNum);
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

	//PolyId
	if (flags.isPolygonUserData) {
		if (inhPolygonInfo.GetSize () == 0) {
			inhPolygonInfo.SetSize (1);
		}
	}

	//NURBS
	if (nurbs.GetSize () != nurbsCapacity) {
		nurbs.SetSize (nurbsCapacity);
	}

	if (!flags.isEdgeUserData)
		inhEdgeInfos.Clear();
	if (!flags.isVertexUserData)
		vertexInfos.Clear ();
	if (!flags.isPolygonUserData)
		inhPolygonInfo.Clear ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReallocateInternalData (USize verticesNum, USize arcsNum, USize nurbsNum, USize verticesCapacity /*= 0*/, USize arcsCapacity /*= 0*/, USize nurbsCapacity /*= 0*/)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	try {
		DBASSERT (((vertices.GetSize () == 0 || !flags.isVertexUserData) && vertexInfos.GetSize () == 0) || (flags.isVertexUserData && vertices.GetSize () == vertexInfos.GetSize ()));
		DBASSERT (((vertices.GetSize () == 0 || !flags.isEdgeUserData) && inhEdgeInfos.GetSize () == 0) || (flags.isEdgeUserData && vertices.GetSize () == inhEdgeInfos.GetSize ()));
		DBASSERT (nVertices == 0 || vertices.GetSize () > nVertices);
		DBASSERT (nArcs == 0 || arcs.GetSize () > nArcs);
		DBASSERT (nNurbs == 0 || nurbs.GetSize () > nNurbs);

		verticesCapacity = GS::Max(verticesCapacity, verticesNum);
		arcsCapacity = GS::Max(arcsCapacity, arcsNum);
		nurbsCapacity = GS::Max(nurbsCapacity, nurbsNum);

		if (verticesCapacity == 0 && arcsCapacity == 0 && nurbsCapacity == 0) {
			//Felszabaditjuk a memoriat.
			FreeInternalData ();
			InitInternalData ();

			return;
		}

		ReallocateInternalDataSizes (verticesNum, arcsNum, nurbsNum, verticesCapacity, arcsCapacity, nurbsCapacity);

		nVertices = verticesNum;
		nArcs = arcsNum;
		nNurbs = nurbsNum;
	} catch (GS::GSException& e) {
		e.Print (dbChannel);
		throw GS::OutOfMemoryException ("Error in CorePolyline2D::ReallocateInternalData!!!", __FILE__, __LINE__);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetInternalDataVertices (const Point2D* pCoords, USize coordNum, GS::UInt32 createFlags)
{
	//coords
	if (PolyCreateFlags_DummyCoordAtIdxZero & createFlags)
		pCoords++;
	for (UIndex vertexIdx = 1; vertexIdx <= coordNum; vertexIdx++, pCoords++) {
		vertices[vertexIdx] = *pCoords;
	}
	if (GetClosed () && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags))
		vertices[nVertices] = vertices[1];
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetInternalDataVertices (const GS::Array<Point2D>& coordList, USize coordNum, GS::UInt32 createFlags)
{
	//coords
	UIndex coordIdx = 0;
	if (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) //input starts with blank coord
		coordIdx++;

	for (UIndex vertexIdx = 1; vertexIdx <= coordNum; vertexIdx++, coordIdx++) {
		vertices[vertexIdx] = coordList[coordIdx];
	}
	if (GetClosed () && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags))
		vertices[nVertices] = vertices[1];
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetInternalDataArcs (const PolyArcRec* pArcs, USize arcNum, GS::UInt32 createFlags)
{
	//arcs
	if (pArcs != nullptr && arcNum != 0 && PolyCreateFlags_DummyArcAtIdxZero & createFlags)
		pArcs++;
	for (UIndex arcIdx = 1; arcIdx <= arcNum; arcIdx++, pArcs++) {
		arcs[arcIdx] = *pArcs;
		if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) &&
			(PolyCreateFlags_IdxRefInArcFromZero & createFlags)) { //first meaningful coord at index 0
				arcs[arcIdx].begIndex++;
				arcs[arcIdx].endIndex = arcs[arcIdx].begIndex + 1;
		}
		DBASSERT (arcs[arcIdx].begIndex < nVertices); //assert indicates wrong input => overindexing will happen when calculating bounding box
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetInternalDataArcs (const GS::Array<PolyArcRec>& arcList, USize arcNum, GS::UInt32 createFlags)
{
	//arcs
	UIndex srcArcIdx = 0;
	if (PolyCreateFlags_DummyArcAtIdxZero & createFlags)
		srcArcIdx++;
	for (UIndex arcIdx = 1; arcIdx <= arcNum; arcIdx++, srcArcIdx++) {
		arcs[arcIdx] = arcList[srcArcIdx];
		if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) &&
			(PolyCreateFlags_IdxRefInArcFromZero & createFlags)) { //first meaningful coord at index 0
				arcs[arcIdx].begIndex++;
				arcs[arcIdx].endIndex = arcs[arcIdx].begIndex + 1;
		}
		DBASSERT (arcs[arcIdx].begIndex < nVertices); //assert indicates wrong input => overindexing will happen when calculating bounding box
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetInternalDataNurbs (const NurbsRec* pNurbs, USize nurbsNum)
{
	//nurbs
	if (nurbsNum == 0 || DBERROR (pNurbs == nullptr))
		return;

	for (UIndex nurbsIdx = 0; nurbsIdx < nurbsNum; nurbsIdx++) {
		nurbs[nurbsIdx] = *pNurbs;
		DBASSERT (nurbs[nurbsIdx].begIndex < nVertices); //assert indicates wrong input => overindexing will happen when calculating bounding box
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetInternalDataNurbs (const GS::Array<NurbsRec>& inNurbs, USize nurbsNum)
{
	//nurbs
	if (nurbsNum == 0)
		return;
	
	for (UIndex nurbsIdx = 0; nurbsIdx < nurbsNum; nurbsIdx++) {
		nurbs[nurbsIdx] = inNurbs[nurbsIdx];
		DBASSERT (nurbs[nurbsIdx].begIndex < nVertices); //assert indicates wrong input => overindexing will happen when calculating bounding box
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetInternalData (const Point2D* pCoords, USize coordNum, const PolyArcRec* pArcs, USize arcNum, const NurbsRec* pNurbs, USize nurbsNum, GS::UInt32 createFlags)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	DBASSERT (coordNum > 0 && pCoords != nullptr);
	DBASSERT ((arcNum == 0 && pArcs == nullptr) || (arcNum != 0 && pArcs != nullptr));
	DBASSERT ((nurbsNum == 0 && pNurbs == nullptr) || (nurbsNum != 0 && pNurbs != nullptr));
	DBASSERT ((GetClosed () && coordNum == nVertices - 1 && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) || coordNum == nVertices);
	DBASSERT (arcNum == nArcs);
	DBASSERT (nurbsNum == nNurbs);
	if ((coordNum != nVertices && coordNum != nVertices - 1) || arcNum != nArcs || nurbsNum != nNurbs)
		throw GeometryIllegalArgumentException ("Invalid number of Vertices or Arcs in CorePolyline2D::SetInternalData!", __FILE__, __LINE__);

	SetInternalDataVertices (pCoords, coordNum, createFlags);

	SetInternalDataArcs (pArcs, arcNum, createFlags);

	SetInternalDataNurbs (pNurbs, nurbsNum);

	RemoveSmallArcs ();

	UpdateBoundingBox ();

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetInternalData (const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<NurbsRec>& inNurbs, GS::UInt32 createFlags)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	USize coordNum = coordList.GetSize ();
	if (PolyCreateFlags_DummyCoordAtIdxZero & createFlags)
		coordNum--;

	USize arcNum = arcList.GetSize ();
	if (arcNum > 0 && PolyCreateFlags_DummyArcAtIdxZero & createFlags)
		arcNum--;

	USize nurbsNum = inNurbs.GetSize ();

	DBASSERT (coordNum == nVertices || (coordNum == nVertices - 1 && GetClosed () && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)));
	DBASSERT (arcNum == nArcs);
	DBASSERT (nurbsNum == nNurbs);

	if ((coordNum != nVertices && coordNum != nVertices - 1) || arcNum != nArcs || nurbsNum != nNurbs)
		throw GeometryIllegalArgumentException ("Invalid number of Vertices or Arcs in CorePolyline2D::SetInternalData!", __FILE__, __LINE__); //ha az allocate jol ment, ide nem lenne szabad jonni

	SetInternalDataVertices (coordList, coordNum, createFlags);

	SetInternalDataArcs (arcList, arcNum, createFlags);
	
	SetInternalDataNurbs (inNurbs, nurbsNum);

	RemoveSmallArcs ();

	UpdateBoundingBox ();

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyInternalDataFrom( const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& source )
{
	DBCHECKPOLY_ONEREFTOTHIS;

	if (source.IsEmpty ()) {
		Clear ();

		CopyPolygonLevelDataFrom (source);

		return;
	}

	CopyPolygonLevelDataFrom (source);
	AllocateInternalData (source.nVertices, source.nArcs, source.nNurbs);

	DBASSERT (source.nVertices == nVertices);
	for (UIndex vertexIdx = 1; vertexIdx <= nVertices && vertexIdx <= source.nVertices; vertexIdx++) {
		vertices[vertexIdx] = source.vertices[vertexIdx];
	}
	DBASSERT (source.nArcs == nArcs);
	for (UIndex arcIdx = 1; arcIdx <= nArcs && arcIdx <= source.nArcs; arcIdx++) {
		arcs[arcIdx] = source.arcs[arcIdx];
	}
	DBASSERT (source.nNurbs == nNurbs);
	for (UIndex nurbsIdx = 0; nurbsIdx < nNurbs && nurbsIdx <= source.nNurbs; nurbsIdx++) {
		nurbs[nurbsIdx] = source.nurbs[nurbsIdx];
	}
	
	//VertexId
	DBASSERT ((!flags.isVertexUserData && vertexInfos.GetSize () == 0) || (flags.isVertexUserData && vertexInfos.GetSize () != 0));
	if (flags.isVertexUserData && vertexInfos.GetSize () != 0) {
		if (source.flags.isVertexUserData && source.vertexInfos.GetSize () != 0)
			CopyInfo_Data <VertexUserData> (vertexInfos, 0, source.vertexInfos, 0, (nVertices + 1) );
		else
			ZeroInfo_Data <VertexUserData> (vertexInfos, 0, (nVertices + 1), defaultVertexData);
	}

	//EdgeId
	DBASSERT ((!flags.isEdgeUserData && inhEdgeInfos.GetSize () == 0) || (flags.isEdgeUserData && inhEdgeInfos.GetSize () != 0));
	if (flags.isEdgeUserData && inhEdgeInfos.GetSize () != 0) {
		if (source.flags.isEdgeUserData && source.inhEdgeInfos.GetSize () != 0)
			CopyInfo_Data <EdgeUserData> (inhEdgeInfos, 0, source.inhEdgeInfos, 0, (nVertices + 1));
		else
			ZeroInfo_Data <EdgeUserData> (inhEdgeInfos, 0, (nVertices + 1), defaultEdgeData);
	}

	boundBox = source.boundBox;

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyInternalDataFromWithoutUserData (const CorePolyline2D<VertexUserData1, EdgeUserData1, PolygonUserData1>& source, USize verticesCapacity, USize arcsCapacity, USize nurbsCapacity)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	if (source.IsEmpty ()) {
		Clear ();
		flags.isSameDirEdgeLegal	= source.flags.isSameDirEdgeLegal;
		flags.isClosed				= source.flags.isClosed;
		flags.isSameCoord			= source.flags.isSameCoord;
		flags.isVertexUserData		= source.flags.isVertexUserData;
		flags.isEdgeUserData		= source.flags.isEdgeUserData;
		flags.isPolygonUserData		= source.flags.isPolygonUserData;

		return;
	}

	flags.isSameDirEdgeLegal	= source.flags.isSameDirEdgeLegal;
	flags.isClosed				= source.flags.isClosed;
	flags.isSameCoord			= source.flags.isSameCoord;
	flags.isVertexUserData		= source.flags.isVertexUserData;
	flags.isEdgeUserData		= source.flags.isEdgeUserData;
	flags.isPolygonUserData		= source.flags.isPolygonUserData;

	USize nVertices = source.vertices.GetSize() - 1;
	USize arcNum    = source.arcs.GetSize() - 1;
	USize nurbsNum  = source.nurbs.GetSize();
	AllocateInternalData (nVertices, arcNum, nurbsNum, verticesCapacity, arcsCapacity, nurbsCapacity);

	for (UIndex vertexIdx = 1; vertexIdx <= nVertices; vertexIdx++) {
		vertices[vertexIdx] = source.vertices[vertexIdx];
	}
	for (UIndex arcIdx = 0; arcIdx <= arcNum; arcIdx++) {
		arcs[arcIdx] = source.arcs[arcIdx];
	}
	for (UIndex nurbsIdx = 0; nurbsIdx < nurbsNum; nurbsIdx++) {
		nurbs[nurbsIdx].nurbs = source.nurbs[nurbsIdx].nurbs;
		nurbs[nurbsIdx].begIndex = source.nurbs[nurbsIdx].begIndex;
	}

	CopyInternalDataFromClearUserData ();

	//ContourId -> polyId
	DBASSERT ((!flags.isPolygonUserData && inhPolygonInfo.GetSize () == 0) || (flags.isPolygonUserData && inhPolygonInfo.GetSize () != 0));
	if (flags.isPolygonUserData && inhPolygonInfo.GetSize () != 0) {
		inhPolygonInfo [0] = PolygonUserData ();
	}

	UpdateBoundingBox ();

	DBCHECKPOLY_CHECK;

}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyInternalDataFromClearUserData (void)
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
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyInternalDataFromUserData (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, UIndex fromVertex, UIndex begVertexIdx, USize newVerticesNum)
{
	//VertexId
	DBASSERT ((!flags.isVertexUserData && vertexInfos.GetSize () == 0) || (flags.isVertexUserData && vertexInfos.GetSize () != 0));
	if (flags.isVertexUserData && vertexInfos.GetSize () != 0) {
		if (source.flags.isVertexUserData && source.vertexInfos.GetSize() != 0)
			CopyInfo_Data <VertexUserData> (vertexInfos, fromVertex, source.vertexInfos, begVertexIdx, newVerticesNum );
		else
			ZeroInfo_Data <VertexUserData> (vertexInfos, fromVertex, newVerticesNum, defaultVertexData);
	}

	//EdgeId
	DBASSERT ((!flags.isEdgeUserData && inhEdgeInfos.GetSize () == 0) || (flags.isEdgeUserData && inhEdgeInfos.GetSize () != 0));
	if (flags.isEdgeUserData && inhEdgeInfos.GetSize () != 0) {
		if (source.flags.isEdgeUserData && source.inhEdgeInfos.GetSize() != 0 )
			CopyInfo_Data <EdgeUserData> (inhEdgeInfos, fromVertex, source.inhEdgeInfos, begVertexIdx, newVerticesNum);
		else
			ZeroInfo_Data <EdgeUserData> (inhEdgeInfos, fromVertex, newVerticesNum, defaultEdgeData);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyInternalDataFrom (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, UIndex contourIdx)
{
	DBCHECKPOLY_ONEREFTOTHIS;
	UIndex begVertexIdx = source.GetInternalVertexBeginIdxInContour (contourIdx);
	UIndex endVertexIdx = source.GetInternalVertexEndIdxInContour (contourIdx);

	USize arcsNum = 0;
	if (source.nArcs != 0 && source.arcs.GetSize () > 1) {
		for (UIndex arcIdx = 1; arcIdx <= source.nArcs; arcIdx++) {
			if (source.arcs[arcIdx].begIndex >= begVertexIdx && source.arcs[arcIdx].begIndex < endVertexIdx)
				arcsNum++;
		}
	}

	flags.isSameDirEdgeLegal = source.flags.isSameDirEdgeLegal;
	flags.isClosed = true;
	flags.isSameCoord = !source.status.isRegularized;
	flags.isVertexUserData = source.flags.isVertexUserData;
	flags.isEdgeUserData = source.flags.isEdgeUserData;
	flags.isPolygonUserData = source.flags.isPolygonUserData || source.flags.isContourUserData;

	AllocateInternalData (0, 0, 0, endVertexIdx - begVertexIdx + 1, arcsNum, 0);

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

	CopyInternalDataFromUserData (source, nVertices + 1, begVertexIdx, newVerticesNum);

	//ContourId -> polyId
	DBASSERT (((!flags.isPolygonUserData) && inhPolygonInfo.GetSize () == 0) || (flags.isPolygonUserData && inhPolygonInfo.GetSize () != 0));
	USize sourcePolygonDataSize = sizeof (PolyId);
	if (flags.isPolygonUserData && inhPolygonInfo.GetSize () != 0) {
		if (sizeof (inhPolygonInfo [0]) == sourcePolygonDataSize && source.flags.isPolygonUserData && source.inhPolygonInfo.GetSize() != 0)
			inhPolygonInfo [0] = source.inhPolygonInfo [0];
		else
			inhPolygonInfo [0] = PolygonUserData ();
	}

	nVertices += newVerticesNum;
	nArcs += newArcsNum;

	UpdateBoundingBox ();

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyPolygonLevelDataFrom (const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& source)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	flags = source.flags;

	defaultVertexData = source.defaultVertexData;
	defaultEdgeData = source.defaultEdgeData;

	//PolyId
	if (flags.isPolygonUserData) {
		if (inhPolygonInfo.GetSize () == 0)
			inhPolygonInfo.SetSize (1);
		if (source.inhPolygonInfo.GetSize () != 0 && source.flags.isPolygonUserData)
			inhPolygonInfo [0] = source.inhPolygonInfo [0];
		else
			inhPolygonInfo [0] = PolygonUserData ();
	} else {
		inhPolygonInfo.Clear ();
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::AddOneVertex (const Point2D& coord, const VertexUserData* vertexInfo, const EdgeUserData* edgeInfo, const PolyArcRec* arc /*= nullptr*/, const NurbsRec* inNurbs /*= nullptr */)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	DBASSERT (arc == nullptr || (arc->arcAngle != 0.0));
	DBASSERT (vertices.GetSize () >= nVertices + 1);
	DBASSERT (arc == nullptr || (arcs.GetSize () > nArcs + 1));
	DBASSERT (inNurbs == nullptr || (nurbs.GetSize () > nNurbs + 1));
	DBASSERT (inNurbs == nullptr || inNurbs->nurbs.Check ());

	if (nVertices + 1 >= vertices.GetSize ())
		ReallocateInternalData (nVertices, nArcs, nNurbs, GS::Max (nVertices + 1, vertices.GetSize () - 1), GS::Max (arc == nullptr ? nArcs : nArcs + 1, arcs.GetSize () - 1), GS::Max (inNurbs == nullptr ? nNurbs : nNurbs + 1, nurbs.GetSize () - 1));

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

	if (arc != nullptr) {
		nArcs++;
		arcs[nArcs].arcAngle = arc->arcAngle;
		arcs[nArcs].begIndex = vertexIdx;
		arcs[nArcs].endIndex = arcs[nArcs].begIndex + 1;
	}

	if (inNurbs != nullptr) {	// TODO ellenorzes 
		nNurbs++;
		nurbs[nNurbs].begIndex = vertexIdx;
		nurbs[nNurbs].nurbs = inNurbs->nurbs;
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetInternalArcIdx (UIndex edgeIdx) const
{
	UIndex arcIdx = 0;
	if (nArcs > 0 && arcs.GetSize () > 1 && edgeIdx <= nVertices) {
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

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetInternalSector (UIndex edgeIdx, Point2D& begC, Point2D& endC, Point2D& origo, double& angle) const
{
	UIndex arcIdx = GetInternalArcIdx (edgeIdx);
	begC = vertices[edgeIdx];
	endC = vertices[edgeIdx + 1];
	if (arcIdx > 0) {
		angle = arcs [arcIdx].arcAngle;
		Geometry::ArcGetOrigo(&begC, &endC, angle, &origo);
	} else {
		angle = 0.0;
	}
	return arcIdx;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetInternalNurbsIdx (UIndex edgeIdx) const
{
	UIndex nurbsIdx = MaxUInt32;
	if (nNurbs > 0 && nurbs.GetSize () > 0 && edgeIdx <= nVertices) {
		for (UIndex i = 0; i < nNurbs; ++i) {
			if (nurbs[i].begIndex == edgeIdx) {
				nurbsIdx = i;
				break;
			}
		}
		if (nurbsIdx == MaxUInt32 && edgeIdx == nVertices) {
			DBBREAK (); //Erre nem lenne szabad, hogy fusson
			nurbsIdx = GetInternalNurbsIdx (0);
		}
	}
	return nurbsIdx;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetCoord (const CutParam& cutParam, Point2D *c) const
{
	DBCHECKPOLY_NONURBS;

	DBASSERT (c != nullptr);
	DBASSERT ((cutParam.edgeIndex > 1) || (cutParam.edgeIndex == 1 && cutParam.param > -Eps));
	if (c == nullptr)
		return;
	if (cutParam.edgeIndex == 1 && cutParam.param < Eps) {
		*c = vertices[1];
		return;
	}
	GS::Int32 inIndex = cutParam.edgeIndex;
	double param = cutParam.param;
	if (param < Eps) {			// #53172 sector elott, mert itt tulcimzes lehetne
		*c = vertices[inIndex];
		return;
	}
	Sector	sector;
	sector.c1 = vertices[inIndex];
	sector.c2 = vertices[inIndex + 1];
	UIndex arcInd = GetInternalArcIdx (inIndex);
	if (arcInd > 0) {
		double	angle = arcs[arcInd].arcAngle;
		GenArc	arc;
		Point2D	origo;
		ArcGetOrigo (&sector.c1, &sector.c2, angle, &origo);
		SetGenArcPtr (&arc, sector.c1, sector.c2, angle);
		param *= fabs (angle);
		double	t0 = arc.IsWhole () ? 0.0 : arc.GetBegAng ();
		double	fi = !arc.IsReflected () ? t0 + param : t0 - param;
		ComputeEllipseCoord (&arc, fi, c);
	} else {
		param *= sector.GetLength ();
		Vector2D v = UnitVector (sector.c2 - sector.c1);
		*c = sector.c1 + v * param;
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DeleteVertexFromInternalData (UIndex remIndex)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	UIndex	i, remIndexForArc, remIndexForNURBS;
	GS::Int32	remArcInd, remNurbsInd;
	bool	lastPNotClosed = false;

	lastPNotClosed = false;
	remArcInd = -1;
	if (nVertices == remIndex)
		lastPNotClosed = !GetClosed ();
	remIndexForArc = lastPNotClosed ? remIndex - 1 : remIndex;
	for (i = 1; i <= nArcs; i++) {
		if (arcs[i].begIndex == remIndexForArc)
			remArcInd = i;
		if (arcs[i].begIndex > remIndexForArc) {
			arcs[i].begIndex -= 1;
			arcs[i].endIndex -= 1;
		}
	}
	if (remArcInd >= 0) {
		/* arcs handle remArcInd elemenek torlese */
		arcs.Delete (remArcInd);
		nArcs -= 1;
	}

	remNurbsInd = -1;
	remIndexForNURBS = lastPNotClosed ? remIndex - 1 : remIndex;
	for (i = 0; i < nNurbs; i++) {
		if (nurbs[i].begIndex == remIndexForNURBS) {
			remNurbsInd = i;
		}
		if (nurbs[i].begIndex > remIndexForNURBS) {
			nurbs[i].begIndex -= 1;
		}
	}
	if (remNurbsInd >= 0) {
		nurbs.Delete (remNurbsInd);
		nNurbs -= 1;
	}

	/* vertices handle remIndex elemenek torlese */
	vertices.Delete (remIndex);

	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
		vertexInfos.Delete (remIndex);
	}
	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
		inhEdgeInfos.Delete (remIndex);
	}
	nVertices -= 1;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReplaceEdgeFromInternalData (UIndex internalEdgeIdx, const GenArc& genArc, const ArcDivParams& arcDivParams)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	// ?? DropNurbs ();
	vertices[internalEdgeIdx]     = genArc.GetBegC ();
	vertices[internalEdgeIdx + 1] = genArc.GetEndC ();
	if (GetClosed () && (internalEdgeIdx == 1))
		vertices[nVertices] = genArc.GetBegC ();
	if (GetClosed () && (internalEdgeIdx + 1 == nVertices))
		vertices[1] = genArc.GetEndC ();

	UIndex arcInd = GetInternalArcIdx (internalEdgeIdx);
	double edgeAngle = genArc.GetArcAngle ();

	if (!genArc.IsElliptic ()) {
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

		GS::Array<Point2D> newPositions;
		Geometry::DivideEllArcToCo (genArc, arcDivParams.maxDifference, newPositions);
		Int32 insNum = newPositions.GetSize () - 2;		/* First and last no nedded */
		for (Int32 i = insNum; i > 0; --i)
			vertices.Insert (internalEdgeIdx + 1, newPositions[i]);

		for (UIndex arcIdx = 1; arcIdx <= nArcs; ++arcIdx) {
			PolyArcRec& arc = arcs[arcIdx];
			if (arc.begIndex > internalEdgeIdx || ((arc.begIndex == internalEdgeIdx))) {
				arc.begIndex += insNum;
				arc.endIndex += insNum;
			}
		}

		if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
			vertexInfos.SetSize (nVertices + 1 + insNum);
			CopyInfo_Data <VertexUserData> (vertexInfos, (internalEdgeIdx + insNum), vertexInfos, internalEdgeIdx, (nVertices - internalEdgeIdx + 1));
			for (Int32 i = 0; i < insNum; ++i)
				vertexInfos[internalEdgeIdx + 1 + i] = defaultVertexData;
		}
		if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
			inhEdgeInfos.SetSize (nVertices + 1 + insNum);
			CopyInfo_Data <EdgeUserData> (inhEdgeInfos, (internalEdgeIdx + insNum), inhEdgeInfos, internalEdgeIdx, (nVertices - internalEdgeIdx + 1));
			for (Int32 i = 0; i < insNum; ++i)
				inhEdgeInfos[internalEdgeIdx + 1 + i] = inhEdgeInfos[internalEdgeIdx];
		}
		nVertices += insNum;

		GS::Int32	insNurbsInd = -1;
		for (UIndex i = 0; i < nNurbs; i++) {
			if ((nurbs[i].begIndex == internalEdgeIdx))
				insNurbsInd = i;
			if (nurbs[i].begIndex > internalEdgeIdx || (nurbs[i].begIndex == internalEdgeIdx)) {
				nurbs[i].begIndex += insNum;
			}
		}

		if (insNurbsInd >= 0) {
			nurbs.Delete (insNurbsInd);
			nNurbs -= 1;
		}


	}

	UpdateBoundingBox ();

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::InsertVertexFromInternalData (UIndex insIndex, const Point2D& newPosition, bool keepArc /*= false*/, bool insArc /*= false*/)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	GS::Int32	insArcInd = -1;

	for (UIndex i = 1; i <= nArcs; i++) {
		if ((arcs[i].begIndex == insIndex) && !keepArc)
			insArcInd = i;
		if (arcs[i].begIndex > insIndex || ((arcs[i].begIndex == insIndex) && keepArc && insArc)) {
			arcs[i].begIndex += 1;
			arcs[i].endIndex += 1;
		}
	}

	if (insArcInd >= 0) {
		/* arcs handle insArcInd elemenek torlese */
		arcs.Delete (insArcInd);
		nArcs -= 1;
	}

	GS::Int32	insNurbsInd = -1;
	for (UIndex i = 0; i < nNurbs; i++) {
		if ((nurbs[i].begIndex == insIndex) && !keepArc)
			insNurbsInd = i;
		if (nurbs[i].begIndex > insIndex || ((nurbs[i].begIndex == insIndex) && keepArc && insArc)) {
			nurbs[i].begIndex += 1;
		}
	}

	if (insNurbsInd >= 0) {
		nurbs.Delete (insNurbsInd);
		nNurbs -= 1;
	}

	/* vertices handle insIndex elemenek insertalasa */
	vertices.Insert (insIndex + 1, newPosition);

	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
		vertexInfos.SetSize (nVertices + 1 + 1);
		CopyInfo_Data <VertexUserData> (vertexInfos, (insIndex + 1), vertexInfos, insIndex, (nVertices - insIndex + 1));
		vertexInfos [insIndex + 1] = defaultVertexData;
	}
	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
		inhEdgeInfos.SetSize (nVertices + 1 + 1);
		CopyInfo_Data <EdgeUserData> (inhEdgeInfos, (insIndex + 1), inhEdgeInfos, insIndex, (nVertices - insIndex + 1));
	}
	nVertices += 1;

}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::Int32 CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::LineLineToDeleteEdge (const Sector &prevEdgeLine, const Sector &nextEdgeLine, Point2D *result)
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

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetEdgeArcToDeleteEdge (GS::Int32& arcInd, bool& isEdgeArc, GenArc& edgeArc, Point2D& edgeArcCentre, double& edgeArcViewAngle, UIndex edgeIdx, const Point2D& vertFromPt, const Point2D& vertFromTo) const
{
	arcInd = GetInternalArcIdx (edgeIdx);
	isEdgeArc        = (arcInd > 0);
	edgeArc          = (arcInd > 0) ? GenArc::CreateCircleArc (vertFromPt, vertFromTo, arcs[arcInd].arcAngle) : GenArc ();
	edgeArcCentre    = edgeArc.GetOrigo ();
	edgeArcViewAngle = CalcRotFi (edgeArc.GetBegAng (), edgeArc.GetEndAng (), edgeArc.IsReflected ());
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineDeleteEdge (UIndex edgeIdx)
{
	DBCHECKPOLY_NONURBS;
	DBCHECKPOLY_ONEREFTOTHIS;

	/* initializing the variables */
	UIndex	begContourIdx;
	UIndex	endContourIdx;

	begContourIdx = 0;
	endContourIdx = 0;
	if (edgeIdx <= nVertices) {
		begContourIdx = 1;
		endContourIdx = nVertices;
	}

	if (GetClosed ())
		endContourIdx--;

	if (endContourIdx - begContourIdx < 2) {
		return false;
	}

	if (!GetClosed () && (edgeIdx == begContourIdx || edgeIdx == endContourIdx - 1)) {
		if (endContourIdx - begContourIdx > 2)	{
			if (edgeIdx == endContourIdx - 1)
				edgeIdx = endContourIdx;
			DeleteVertexFromInternalData (edgeIdx);
		} else {
			throw GeometryAlgorithmErrorException ("Can not delete the edge!", __FILE__, __LINE__);
		}
		return true;
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

	GS::Int32		arcIndBeg, arcIndEnd;
	bool			isPrevEdgeArc, isNextEdgeArc; 
	GenArc			prevEdgeArc, nextEdgeArc;
	Point2D			prevEdgeArcCentre, nextEdgeArcCentre;
	double			prevEdgeArcViewAngle, nextEdgeArcViewAngle;
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

	if (GetClosed ()) {
		vertices[nVertices] = vertices[1];
		if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
			vertexInfos [nVertices] = vertexInfos [1];
		}
		if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
			inhEdgeInfos [nVertices] = inhEdgeInfos [1];
		}
	}
	return true;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineFilletChamferContour (double filletChamferRadius, bool doFillet)
{
	DBCHECKPOLY_NONURBS;
	DBCHECKPOLY_ONEREFTOTHIS;

	UIndex	begContourIdx;
	UIndex	endContourIdx;

	UIndex	prevVertIdx;
	UIndex	filletChamferVertexIdx;
	UIndex	nextVertIdx;
	Point2D	actVertPt;
	Point2D	prevVertPt;
	Point2D	nextVertPt;

	Point2D	filletChamferCircleCentrePt;
	Point2D	begFilletChamferPosition;
	Point2D	endFilletChamferPosition;

	/* collecting the needed data for the next function */
	bool	isPrevEdgeArc;
	GenArc	prevEdgeArc;
	Point2D	prevEdgeArcCentre;
	double	prevEdgeArcViewAngle;

	bool	isNextEdgeArc;
	GenArc	nextEdgeArc;
	Point2D	nextEdgeArcCentre;
	double	nextEdgeArcViewAngle;
	double	maxFilletChamferRadius;

	begContourIdx = 1;
	endContourIdx = nVertices;
	if (GetClosed ())
		endContourIdx--;

	filletChamferVertexIdx = begContourIdx;
	UIndex countourVertexCount = endContourIdx - begContourIdx + 1;

	for (UIndex i = countourVertexCount; i >= 1; i--) {
		if (!GetClosed () && ((UIndex) filletChamferVertexIdx == begContourIdx || (UIndex) filletChamferVertexIdx == endContourIdx)) {	//opened polylines
			filletChamferVertexIdx = (filletChamferVertexIdx + 1 > endContourIdx) ? begContourIdx : filletChamferVertexIdx + 1;
			continue;
		}
		GetMaxVertexFillet (filletChamferVertexIdx, &maxFilletChamferRadius);
		if (filletChamferRadius > maxFilletChamferRadius + SmallEps) {
			filletChamferVertexIdx = (filletChamferVertexIdx + 1 > endContourIdx) ? begContourIdx : filletChamferVertexIdx + 1;
			continue;
		}

		/* determining the three acting vertices */

		prevVertIdx = (filletChamferVertexIdx - 1 < begContourIdx) ? endContourIdx : filletChamferVertexIdx - 1;
		nextVertIdx = (filletChamferVertexIdx + 1 > endContourIdx) ? begContourIdx : filletChamferVertexIdx + 1;

		prevVertPt = vertices[prevVertIdx];
		actVertPt  = vertices[filletChamferVertexIdx];
		nextVertPt = vertices[nextVertIdx];

		/* collecting the needed data for the next function */
		GS::Int32					arcIndBeg, arcIndEnd;

		arcIndBeg = GetInternalArcIdx (prevVertIdx);
		isPrevEdgeArc        = (arcIndBeg > 0);
		prevEdgeArc          = (arcIndBeg > 0) ? GenArc::CreateCircleArc (prevVertPt, actVertPt, arcs[arcIndBeg].arcAngle) : GenArc ();
		prevEdgeArcCentre    = prevEdgeArc.GetOrigo ();
		prevEdgeArcViewAngle = CalcRotFi (prevEdgeArc.GetBegAng (), prevEdgeArc.GetEndAng (), prevEdgeArc.IsReflected ());

		arcIndEnd = GetInternalArcIdx (filletChamferVertexIdx);
		isNextEdgeArc        = (arcIndEnd > 0);
		nextEdgeArc          = (arcIndEnd > 0) ? GenArc::CreateCircleArc (actVertPt, nextVertPt, arcs[arcIndEnd].arcAngle) : GenArc ();
		nextEdgeArcCentre    = nextEdgeArc.GetOrigo ();
		nextEdgeArcViewAngle = CalcRotFi (nextEdgeArc.GetBegAng (), nextEdgeArc.GetEndAng (), nextEdgeArc.IsReflected ());

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
					UnitVector (filletChamferCircleCentrePt - prevEdgeArcCentre) * Dist (actVertPt, prevEdgeArcCentre);
				if (!isNextEdgeArc)
					endFilletChamferPosition = CoordProjSector (filletChamferCircleCentrePt, s2);
				else
					endFilletChamferPosition = nextEdgeArcCentre +
					UnitVector (filletChamferCircleCentrePt - nextEdgeArcCentre) * Dist (actVertPt, nextEdgeArcCentre);

				/* determine the new viewangle of the two original edge */
				if (isPrevEdgeArc)
					GetViewAngle (
					&prevEdgeArcCentre,
					&prevVertPt,
					&begFilletChamferPosition,
					prevEdgeArcViewAngle,
					isPrevEdgeArc ? 1 : -1,
					&newPrevEdgeArcViewAngle);

				if (isNextEdgeArc)
					GetViewAngle (
					&nextEdgeArcCentre,
					&endFilletChamferPosition,
					&nextVertPt,
					nextEdgeArcViewAngle,
					isNextEdgeArc ? 1 : -1,
					&newNextEdgeArcViewAngle);

				/* coincidence tests */
				united1 = (Dist (prevVertPt, begFilletChamferPosition) <  Eps);
				united2 = (Dist (nextVertPt, endFilletChamferPosition) <  Eps);

				if (!isPrevEdgeArc) {
					if ((Dist (prevVertPt, actVertPt) < Dist (begFilletChamferPosition, actVertPt) -  Eps)) {
						filletChamferVertexIdx = (filletChamferVertexIdx + 1 > endContourIdx) ? begContourIdx : filletChamferVertexIdx + 1;
						continue; //Filleting not possible!
					}
				} else {
					if (!united1) {
						if ((((prevEdgeArcViewAngle > 0) && (newPrevEdgeArcViewAngle > prevEdgeArcViewAngle)) || ((prevEdgeArcViewAngle < 0) && (newPrevEdgeArcViewAngle < prevEdgeArcViewAngle)))) {
							filletChamferVertexIdx = (filletChamferVertexIdx + 1 > endContourIdx) ? begContourIdx : filletChamferVertexIdx + 1;
							continue; //Filleting not possible!
						}
					}
				}
				if (!isNextEdgeArc) {
					if ((Dist (nextVertPt, actVertPt) < Dist (endFilletChamferPosition, actVertPt) -  Eps)) {
						filletChamferVertexIdx = (filletChamferVertexIdx + 1 > endContourIdx) ? begContourIdx : filletChamferVertexIdx + 1;
						continue; //Filleting not possible!
					}
				} else {
					//					if (united2 == false)
					//						if (((nextEdgeArcViewAngle > 0) && (newPrevEdgeArcViewAngle > nextEdgeArcViewAngle) || (nextEdgeArcViewAngle < 0) && (newNextEdgeArcViewAngle < nextEdgeArcViewAngle))) {
					//							filletChamferVertexIdx = (filletChamferVertexIdx + 1 > endContourIdx) ? begContourIdx : filletChamferVertexIdx + 1;
					//							continue; //Filleting not possible!
					//						}
				}

				/* RJ008 -] */
		} else {
			filletChamferVertexIdx = (filletChamferVertexIdx + 1 > endContourIdx) ? begContourIdx : filletChamferVertexIdx + 1;
			continue; //Filleting not possible!
		}

		/* insert new vertices and delete old vertex */
		if (!united2) {
			if (isNextEdgeArc)
				arcs[arcIndEnd].arcAngle = newNextEdgeArcViewAngle;
			InsertVertexFromInternalData (filletChamferVertexIdx, endFilletChamferPosition, true, true);
		} else {
			if (prevVertIdx == endContourIdx)
				prevVertIdx = (prevVertIdx - 1 < begContourIdx) ? endContourIdx : prevVertIdx - 1;
		}

		DeleteVertexFromInternalData (filletChamferVertexIdx);

		if (!united1) {
			if (isPrevEdgeArc)
				arcs[arcIndBeg].arcAngle = newPrevEdgeArcViewAngle;
			InsertVertexFromInternalData (prevVertIdx, begFilletChamferPosition, true, false);	/* Ha ives elotte akkor mi van ???? */
		} else {
			filletChamferVertexIdx = prevVertIdx;
		}
		if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
			UIndex insertedEdgeIndex = prevVertIdx;
			if (!united1) {
				insertedEdgeIndex++;
			}
			inhEdgeInfos [insertedEdgeIndex] = defaultEdgeData;
		}

		if (doFillet) {
			/* calculating the viewangle for the filleted new edge */
			double	begAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, begFilletChamferPosition);
			double	endAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, endFilletChamferPosition);
			double	actAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, actVertPt);
			bool	isReverted = !Geometry::IsInsideAngle (begAngle, endAngle, actAngle);
			double	viewAngle;
			viewAngle = Geometry::ComputeRotFi (filletChamferCircleCentrePt, begFilletChamferPosition, endFilletChamferPosition, isReverted);

			PolyArcRec arcRec;
			arcRec.begIndex = united1 ? prevVertIdx : prevVertIdx + 1;
			arcRec.endIndex = united1 ? prevVertIdx + 1 : prevVertIdx + 2;
			arcRec.arcAngle = viewAngle;
			/* felvenni a arcos bejegyzest */
			nArcs += 1;
			if (nArcs == 1) {
				arcs.SetSize (2);

				arcs[0].begIndex = 0;
				arcs[0].endIndex = 0;
				arcs[0].arcAngle = 0.0;
			} else {
				arcs.SetSize (nArcs + 1);
			}
			arcs[nArcs] = arcRec;
		}

		if (GetClosed ())
			vertices[nVertices] = vertices[1];

		if (!united1) {
			if (filletChamferVertexIdx != begContourIdx)
				filletChamferVertexIdx = (filletChamferVertexIdx + 1 > endContourIdx) ? begContourIdx : filletChamferVertexIdx + 1;
		}
		if (!united2) {
			filletChamferVertexIdx = (filletChamferVertexIdx + 1 > endContourIdx) ? begContourIdx : filletChamferVertexIdx + 1;
		}
		begContourIdx = 1;
		endContourIdx = nVertices;
		if (GetClosed ())
			endContourIdx--;

	}

	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
		vertexInfos [nVertices] = vertexInfos [1];
	}
	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
		inhEdgeInfos [nVertices] = inhEdgeInfos [1];
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetMaxMid (									/* RJ012 */
				 bool			twocirc,			/* -> two circles ? 	*/
				 const Circle2D*	ci1,				/* -> first circle		*/
				 const GenArc*	arc1,				/* -> first arc			*/
				 const Circle2D*	ci2,				/* -> second circle		*/
				 const GenArc*	arc2,				/* -> second arc		*/
				 const Sector*	ls)					/* -> line sector		*/
{
	Sector		s, s1;
	Point2D		c1, c2;

	if (twocirc) {
		c1 = Geometry::CoordProjSector (ci2->Origo (), *ls);
		if (!Geometry::InternalCoord (*ls, c1, Geometry::Boundary_Closed))
			return 0.0;
		s1 = Sector (c1, ci2->Origo ());
	} else {
		s1 = Sector (ci1->Origo (), ci2->Origo ());
		Geometry::XCircleLine (ci1, &s1, &s);
		if (Geometry::ValidGenArcPoint (arc1, &(s.c1)))
			c1 = s.c1;
		else
			if (Geometry::ValidGenArcPoint (arc1, &(s.c2)))
				c1 = s.c2;
			else
				return 0.0;
	}
	Geometry::XCircleLine (ci2, &s1, &s);
	if (Geometry::ValidGenArcPoint (arc2, &(s.c1)))
		c2 = s.c1;
	else
		if (Geometry::ValidGenArcPoint (arc2, &(s.c2)))
			c2 = s.c2;
		else
			return 0.0;
	return (Sector (c2, c1).GetLength ()/2 - Eps);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetMaxVertexFillet (UIndex filletedVertexIdx, double* maxFilletRadius) const
{
	DBCHECKPOLY_NONURBS;
	const double TopFill = 1000.0;
	/* 2 fok sinusa: az erintesi hatareset */
	const double MinSin = 0.05;

	UIndex	begContourIdx;
	UIndex	endContourIdx;

	begContourIdx = 0;
	endContourIdx = 0;
	if (filletedVertexIdx <= nVertices) {
		begContourIdx = 1;
		endContourIdx = nVertices;
	}

	if (GetClosed ())
		endContourIdx--;

	/* determining the three acting vertices */
	GS::Int32	prevVertIdx;
	GS::Int32	nextVertIdx;
	Point2D	actVertPt;
	Point2D	prevVertPt;
	Point2D	nextVertPt;

	prevVertIdx = (filletedVertexIdx - 1 < begContourIdx) ? endContourIdx : filletedVertexIdx - 1;
	nextVertIdx = (filletedVertexIdx + 1 > endContourIdx) ? begContourIdx : filletedVertexIdx + 1;

	prevVertPt = vertices[prevVertIdx];
	actVertPt  = vertices[filletedVertexIdx];
	nextVertPt = vertices[nextVertIdx];

	/* collecting the needed data for the next function */
	GS::Int32					arcIndBeg, arcIndEnd;

	arcIndBeg = GetInternalArcIdx (prevVertIdx);
	bool	isPrevEdgeArc        = (arcIndBeg > 0);
	GenArc	prevEdgeArc          = (arcIndBeg > 0) ? GenArc::CreateCircleArc (prevVertPt, actVertPt, arcs[arcIndBeg].arcAngle) : GenArc ();
	Point2D	prevEdgeArcCentre    = prevEdgeArc.GetOrigo ();
	double	prevEdgeArcViewAngle = CalcRotFi (prevEdgeArc.GetBegAng (), prevEdgeArc.GetEndAng (), prevEdgeArc.IsReflected ());

	arcIndEnd = GetInternalArcIdx (filletedVertexIdx);
	bool	isNextEdgeArc        = (arcIndEnd > 0);
	GenArc	nextEdgeArc          = (arcIndEnd > 0) ? GenArc::CreateCircleArc (actVertPt, nextVertPt, arcs[arcIndEnd].arcAngle) : GenArc ();
	Point2D	nextEdgeArcCentre    = nextEdgeArc.GetOrigo ();
	double	nextEdgeArcViewAngle = CalcRotFi (nextEdgeArc.GetBegAng (), nextEdgeArc.GetEndAng (), nextEdgeArc.IsReflected ());

	Point2D		c, c1, c2, c3;
	Vector2D	c4, c5;
	Sector		s, s1, s2, s3, s4, s5, s6;
	double		r1, r2;
	Circle2D	ci1 (Point2D (), 0), ci2 (Point2D (), 0);
	double		max1, max2, max3;

	if (isPrevEdgeArc) {
		ci1.SetRadius (prevEdgeArc.GetMainAxisLength ());
		ci1.SetOrigo (prevEdgeArcCentre);
		r1 = prevEdgeArc.GetMainAxisLength ();
	} else {
		r1 = 0.0;
		BNZeroMemory (&ci1, sizeof (ci1));
	}

	if (isNextEdgeArc) {
		ci2.SetRadius (nextEdgeArc.GetMainAxisLength ());
		ci2.SetOrigo (nextEdgeArcCentre);
		r2 = nextEdgeArc.GetMainAxisLength ();
	} else {
		r2 = 0.0;
		BNZeroMemory (&ci2, sizeof (ci2));
	}

	*maxFilletRadius = TopFill;
	max1 = 0.0;
	max2 = 0.0;
	if (!isPrevEdgeArc) {
		if (!isNextEdgeArc) {	/* Ket egyenes */
			Vector2D vv = Geometry::UnitVector (nextVertPt - actVertPt) + Geometry::UnitVector (prevVertPt - actVertPt);
			s = Sector (actVertPt, actVertPt + vv);
			s1 = Sector (prevVertPt, prevVertPt + (actVertPt - prevVertPt).GetNormalVector ());
			s2 = Sector (nextVertPt + (nextVertPt - actVertPt).GetNormalVector (), nextVertPt);
			if (Geometry::XLines (s1, s, &c)) {
				max1 = Geometry::Dist (prevVertPt, c);
				if (Geometry::XLines (s2, s, &c)) {
					max2 = Geometry::Dist (nextVertPt, c);
					*maxFilletRadius = MIN (max1, max2);
				}
			}
		} else {				/* Egy egyenes es egy kor */
			s1 = Sector (prevVertPt, prevVertPt + (actVertPt - prevVertPt).GetNormalVector ());
			s3 = Sector (prevVertPt, actVertPt);
			if (nextEdgeArcViewAngle < 0.0) {
				s2 = Sector (nextVertPt, nextEdgeArcCentre);
				s5 = Sector (nextEdgeArcCentre, prevVertPt + Geometry::UnitVector (Geometry::SectorVector (s1)) * -r2);
			} else {
				s2 = Sector (nextEdgeArcCentre, nextVertPt);
				s5 = Sector (nextEdgeArcCentre, prevVertPt + Geometry::UnitVector (Geometry::SectorVector (s1)) * r2);
			}
			s6 = Sector (nextEdgeArcCentre, actVertPt);
			c4 = Geometry::UnitVector (Geometry::SectorVector (s3));
			c5 = Geometry::UnitVector (Geometry::SectorVector (s6)).GetNormalVector ();
			if (fabs (c4 ^ c5) < MinSin && (Geometry::MulsVectors (c4, c5) * nextEdgeArcViewAngle) > 0.0)
				*maxFilletRadius = Eps;
			else {
				s4 = Sector (nextVertPt, nextVertPt + Geometry::UnitVector (Geometry::SectorVector (s1)) + Geometry::UnitVector (Geometry::SectorVector (s2)));
				c1 = Geometry::MidPoint (nextEdgeArcCentre, s5.c2);
				s6 = Sector (c1, c1 + Geometry::SectorVector (s5).GetNormalVector ());
				if (Geometry::XLines (s1, s6, &c)) {
					max1 = Geometry::Dist (prevVertPt, c);		/* A kor sugara ami atmegy prevVertPt-en es erinti az egyenest es a kort */
					c3 = nextEdgeArcCentre + Geometry::MulVector (Geometry::UnitVector (Geometry::SectorVector (Sector (nextEdgeArcCentre, c))), r2);
					if (Geometry::XLines (s3, s4, &c2)) {
						s5 = Sector (c2, c2 + Geometry::SectorVector (s1));
						if (Geometry::XLines (s5, s2, &c))	/* A kor sugara ami atmegy nextVertPt-en es erinti az egyenest es a kort */
							max2 = Geometry::Dist (nextVertPt, c);
						else
							max2 = Geometry::Dist (nextVertPt, c2) / 2.0;
						if (max2 > r2)
							max2 = r2;
						max3 = GetMaxMid (false, &ci2, &nextEdgeArc, &ci2, &nextEdgeArc, &s3);	/* RJ012 */
						if (!InternalCoord (s3, c2, Geometry::Boundary_Closed))
							max2 = 0.0;
					} else {
						max2 = 0.0;
						max3 = 0.0;
					}
					if (!Geometry::ValidGenArcPoint (&nextEdgeArc, &c3))
						max1 = 0.0;

					*maxFilletRadius = MAX (max1, max2);
					if (max3 > *maxFilletRadius)
						*maxFilletRadius = max3;
				}
			}
		}
	} else {
		if (!isNextEdgeArc) {	/* Egy kor es egy egyenes */
			s2 = Sector (nextVertPt, nextVertPt + (nextVertPt - actVertPt).GetNormalVector ());
			s4 = Sector (nextVertPt, actVertPt);
			if (prevEdgeArcViewAngle < 0.0) {
				s1 = Sector (prevVertPt, prevEdgeArcCentre);
				s5 = Sector (prevEdgeArcCentre, nextVertPt + Geometry::MulVector (Geometry::UnitVector (Geometry::SectorVector (s2)), -r1));
			} else {
				s1 = Sector (prevEdgeArcCentre, prevVertPt);
				s5 = Sector (prevEdgeArcCentre, nextVertPt + Geometry::MulVector (Geometry::UnitVector (Geometry::SectorVector (s2)), r1));
			}
			s6 = Sector (prevEdgeArcCentre, actVertPt);
			c4 = Geometry::UnitVector (Geometry::SectorVector (s4));
			c5 = Geometry::UnitVector (Geometry::SectorVector (s6)).GetNormalVector ();
			if (fabs(c4 ^ c5) < MinSin && (Geometry::MulsVectors (c4, c5) * prevEdgeArcViewAngle) < 0.0)
				*maxFilletRadius = Eps;
			else {
				s3 = Sector (prevVertPt, prevVertPt + Geometry::UnitVector (Geometry::SectorVector (s1)) + Geometry::UnitVector (Geometry::SectorVector (s2)));
				c1 = Geometry::MidPoint (prevEdgeArcCentre, s5.c2);
				s6 = Sector (c1, c1 + Geometry::SectorVector (s5).GetNormalVector ());
				if (Geometry::XLines (s2, s6, &c)) {
					max2 = Geometry::Dist (nextVertPt, c);		/* A kor sugara ami atmegy next-en es erinti a kort es az egyenest */
					c3 = prevEdgeArcCentre + Geometry::MulVector (Geometry::UnitVector (Geometry::SectorVector (Sector (prevEdgeArcCentre, c))), r1);
					if (Geometry::XLines (s3, s4, &c2)) {
						s5 = Sector (c2, c2 + Geometry::SectorVector (s2));
						if (Geometry::XLines (s5, s1, &c))	/* A kor sugara ami atmegy prevVertPt-en es erinti a kort es az egyenest */
							max1 = Geometry::Dist (prevVertPt, c);
						else
							max1 = Geometry::Dist (prevVertPt, c2) / 2.0;
						if (max1 > r1)
							max1 = r1;
						max3 = GetMaxMid (false, &ci1, &prevEdgeArc, &ci1, &prevEdgeArc, &s4);	/* RJ012 */
						if (!InternalCoord (s4, c2, Geometry::Boundary_Closed))
							max1 = 0.0;
					} else {
						max1 = 0.0;
						max3 = 0.0;
					}
					if (!Geometry::ValidGenArcPoint (&prevEdgeArc, &c3))
						max2 = 0.0;

					*maxFilletRadius = MAX (max1, max2);
					if (max3 > *maxFilletRadius)
						*maxFilletRadius = max3;
				}
			}
		} else {				/* Ket kor */
			s1 = Sector (prevVertPt, prevEdgeArcCentre);
			s2 = Sector (nextVertPt, nextEdgeArcCentre);
			s5 = Sector (prevEdgeArcCentre, actVertPt);
			s6 = Sector (nextEdgeArcCentre, actVertPt);
			c4 = Geometry::UnitVector (Geometry::SectorVector (s5));
			c5 = Geometry::UnitVector (Geometry::SectorVector (s6));
			if (fabs(c4 ^ c5) < MinSin)
				*maxFilletRadius = Eps;
			else {
				s3 = Sector (prevVertPt, prevVertPt + Geometry::SectorVector (s1).GetNormalVector ());
				s4 = Sector (nextVertPt, nextVertPt + Geometry::SectorVector (s2).GetNormalVector ());
				if (Geometry::XCircleLine (&ci2, &s3, &s) || Geometry::XCircleLine (&ci1, &s4, &s) || prevEdgeArcViewAngle * nextEdgeArcViewAngle < 0.0) {
					if (Geometry::XLines (s1, s2, &c)) {
						if (prevEdgeArcViewAngle * nextEdgeArcViewAngle < 0.0)
							s3 = Sector (nextEdgeArcCentre, prevVertPt + Geometry::MulVector (Geometry::UnitVector (Geometry::SectorVector (s1)), -r2));
						else
							s3 = Sector (nextEdgeArcCentre, prevVertPt + Geometry::MulVector (Geometry::UnitVector (Geometry::SectorVector (s1)), r2));
						c1 = Geometry::MidPoint (s3.c1, s3.c2);
						s4 = Sector (c1, c1 +Geometry::SectorVector (s3).GetNormalVector ());
						if (Geometry::XLines (s4, s1, &c))
							max1 = Geometry::Dist (prevVertPt, c);	/* A kor sugara ami atmegy prev-en es erinti a ket kort */
						c2 = nextEdgeArcCentre + Geometry::MulVector (Geometry::UnitVector (Geometry::SectorVector (Sector (nextEdgeArcCentre, c))), r2);
						if (!Geometry::ValidGenArcPoint (&nextEdgeArc, &c2))
							max1 = 0.0;

						if (prevEdgeArcViewAngle * nextEdgeArcViewAngle < 0.0)
							s3 = Sector (prevEdgeArcCentre, nextVertPt + Geometry::MulVector (Geometry::UnitVector (Geometry::SectorVector (s2)), -r1));
						else
							s3 = Sector (prevEdgeArcCentre, nextVertPt + Geometry::MulVector (Geometry::UnitVector (Geometry::SectorVector (s2)), r1));
						c1 = Geometry::MidPoint (s3.c1, s3.c2);
						s4 = Sector (c1, c1 + Geometry::SectorVector (s3).GetNormalVector ());
						if (Geometry::XLines (s4, s2, &c))
							max2 = Geometry::Dist (nextVertPt, c);	/* A kor sugara ami atmegy next-en es erinti a ket kort */
						c2 = prevEdgeArcCentre + Geometry::MulVector (Geometry::UnitVector (Geometry::SectorVector (Sector (prevEdgeArcCentre, c))), r1);
						if (!Geometry::ValidGenArcPoint (&prevEdgeArc, &c2))
							max2 = 0.0;

						max3 = GetMaxMid (true, &ci1, &prevEdgeArc, &ci2, &nextEdgeArc, &s4);		/* RJ012 */

						*maxFilletRadius = MAX (max1, max2);
						if (max3 > *maxFilletRadius)
							*maxFilletRadius = max3;
					}
				} else {
					*maxFilletRadius = TopFill/2;
				}
			}
		}
	}
	if (*maxFilletRadius < Eps)				/* RJ012 */
		*maxFilletRadius = Eps;
	//	if (*maxFilletRadius > TopFill)			/* RJ213 */	//csp040512 - #31865
	//		*maxFilletRadius = TopFill;

}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineFilletChamferVertex (UIndex filletChamferVertexIdx, double filletChamferRadius, bool doFillet)
{
	DBCHECKPOLY_NONURBS;
	DBCHECKPOLY_ONEREFTOTHIS;

	UIndex	begContourIdx;
	UIndex	endContourIdx;

	begContourIdx = 0;
	endContourIdx = 0;
	if (filletChamferVertexIdx <= nVertices) {
		begContourIdx = 1;
		endContourIdx = nVertices;
	}

	if (GetClosed ())
		endContourIdx--;


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
	GS::Int32				arcIndBeg, arcIndEnd;
	PolyArcRec				emptyPolyArc;
	emptyPolyArc.begIndex = 0;
	emptyPolyArc.endIndex = 0;
	emptyPolyArc.arcAngle = 0.0;


	arcIndBeg = GetInternalArcIdx (prevVertIdx);
	bool	isPrevEdgeArc        = (arcIndBeg > 0);
	GenArc	prevEdgeArc          = (arcIndBeg > 0) ? GenArc::CreateCircleArc (prevVertPt, actVertPt, arcs[arcIndBeg].arcAngle) : GenArc ();
	Point2D	prevEdgeArcCentre    = prevEdgeArc.GetOrigo ();
	double	prevEdgeArcViewAngle = CalcRotFi (prevEdgeArc.GetBegAng (), prevEdgeArc.GetEndAng (), prevEdgeArc.IsReflected ());

	arcIndEnd = GetInternalArcIdx (filletChamferVertexIdx);
	bool	isNextEdgeArc        = (arcIndEnd > 0);
	GenArc	nextEdgeArc          = (arcIndEnd > 0) ? GenArc::CreateCircleArc (actVertPt, nextVertPt, arcs[arcIndEnd].arcAngle) : GenArc ();
	Point2D	nextEdgeArcCentre    = nextEdgeArc.GetOrigo ();
	double	nextEdgeArcViewAngle = CalcRotFi (nextEdgeArc.GetBegAng (), nextEdgeArc.GetEndAng (), nextEdgeArc.IsReflected ());

	try {
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
			&filletChamferCircleCentrePt,/* <- the new point			*/
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
				if (isPrevEdgeArc)
					GetViewAngle (
					&prevEdgeArcCentre,
					&prevVertPt,
					&begFilletChamferPosition,
					prevEdgeArcViewAngle,
					isPrevEdgeArc ? 1 : -1,
					&newPrevEdgeArcViewAngle);

				if (isNextEdgeArc)
					GetViewAngle (
					&nextEdgeArcCentre,
					&endFilletChamferPosition,
					&nextVertPt,
					nextEdgeArcViewAngle,
					isNextEdgeArc ? 1 : -1,
					&newNextEdgeArcViewAngle);

				/* coincidence tests */
				united1 = (Dist (prevVertPt, begFilletChamferPosition) <  Eps);
				united2 = (Dist (nextVertPt, endFilletChamferPosition) <  Eps);

				if (!isPrevEdgeArc) {
					if ((Dist (prevVertPt, actVertPt) < Dist (begFilletChamferPosition, actVertPt) -  Eps)) {
						throw GS::LogicErrorException (doFillet ? "Filleting not possible!" : "Chamfering not possible!", __FILE__, __LINE__);
					}
				} else {
					if (!united1) {
						if ((((prevEdgeArcViewAngle > 0) && (newPrevEdgeArcViewAngle > prevEdgeArcViewAngle)) || ((prevEdgeArcViewAngle < 0) && (newPrevEdgeArcViewAngle < prevEdgeArcViewAngle)))) {
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

		InsertNewVerticesAndDeleteOld (filletChamferVertexIdx, begFilletChamferPosition, endFilletChamferPosition, begContourIdx, endContourIdx, prevVertIdx, isPrevEdgeArc, arcIndBeg, newPrevEdgeArcViewAngle, isNextEdgeArc, arcIndEnd, newNextEdgeArcViewAngle, united1, united2);

		if (doFillet) {
			/* calculating the viewangle for the filleted new edge */
			double	begAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, begFilletChamferPosition);
			double	endAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, endFilletChamferPosition);
			double	actAngle	= Geometry::ComputeFi (filletChamferCircleCentrePt, actVertPt);
			bool	isReverted = !Geometry::IsInsideAngle (begAngle, endAngle, actAngle);
			double	viewAngle;
			viewAngle = Geometry::ComputeRotFi (filletChamferCircleCentrePt, begFilletChamferPosition, endFilletChamferPosition, isReverted);

			PolyArcRec arcRec;
			arcRec.begIndex = united1 ? prevVertIdx : prevVertIdx + 1;
			arcRec.endIndex = united1 ? prevVertIdx + 1 : prevVertIdx + 2;
			arcRec.arcAngle = viewAngle;
			/* felvenni a arcos bejegyzest */
			nArcs += 1;
			if (nArcs == 1) {
				arcs.SetSize (2);
				arcs[0] = emptyPolyArc;
			} else {
				arcs.SetSize (nArcs + 1);
			}
			arcs[nArcs] = arcRec;
		}

		if (GetClosed ()) {
			vertices[nVertices] = vertices[1];
			if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
				vertexInfos [nVertices] = vertexInfos [1];
			}
			if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
				inhEdgeInfos [nVertices] = inhEdgeInfos [1];
			}
		}
		RemoveSmallArcs ();

	} catch (const GS::GSException& e) {
		e.Print (dbChannel);
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolyline2D::PolylineFilletChamferVertex", __FILE__, __LINE__);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetOffsetLimit (double *offset) const
{
	DBCHECKPOLY_NONURBS;
	UIndex					iVertex, begI;
	GS::Int32				arcIndp, arcIndn;
	Curve2DData	prevCurve;
	Curve2DData	nextCurve;

	begI = GetClosed () ? 1 : 2;
	prevCurve.epsilon = prevCurve.angleEpsilon = Eps;
	nextCurve.epsilon = nextCurve.angleEpsilon = Eps;
	for (iVertex = begI; iVertex <= nVertices - 1; iVertex++) {
		double maxOffset = 0.0;
		arcIndp = GetInternalArcIdx ((iVertex == 1) ?  nVertices - 1 : iVertex - 1);
		if (arcIndp > 0) {
			prevCurve.type = CURVE2D_GenArc;
			prevCurve.genArc = SetGenArc (vertices[(iVertex == 1) ?  nVertices - 1 : iVertex - 1], vertices[iVertex], arcs[arcIndp].arcAngle);
		} else {
			prevCurve.type = CURVE2D_Line;
			prevCurve.sector.c1 = vertices[(iVertex == 1) ?  nVertices - 1 : iVertex - 1];
			prevCurve.sector.c2 = vertices[iVertex];
		}
		arcIndn = GetInternalArcIdx (iVertex);
		if (arcIndn > 0) {
			nextCurve.type = CURVE2D_GenArc;
			nextCurve.genArc = SetGenArc (vertices[iVertex], vertices[iVertex + 1], arcs[arcIndn].arcAngle);
		} else {
			nextCurve.type = CURVE2D_Line;
			nextCurve.sector.c1 = vertices[iVertex];
			nextCurve.sector.c2 = vertices[iVertex + 1];
		}
		GetMaxOffsetValue (prevCurve, nextCurve, *offset, &maxOffset);
		if (fabs (maxOffset) > SmallEps9) {		/* #30733 RJ  ( a GetCornerFilletCentre SmallEps-et hasznal !) */
			maxOffset = (*offset < 0.0) ? maxOffset + SmallEps9 : maxOffset - SmallEps9;
		}
		*offset = (*offset < 0.0) ? (MAX (*offset, maxOffset)) : (MIN (*offset, maxOffset));
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::OffsetAllEdge (double offset)
{
	DBCHECKPOLY_NONURBS;

	UIndex i;
	UIndex arcInd1, arcInd2;
	Vector2D	v;
	Point2D	cprev, c0, cnext, ori1, ori2, cnew1, cnew2;
	double	fi1, fi2;

	if (GetClosed ()) {
		arcInd1 = GetInternalSector (nVertices - 1, cprev, c0, ori1, fi1);
		i = 1;
	} else {
		arcInd1 = GetInternalSector (1, cprev, c0, ori1, fi1);
		if (arcInd1 > 0) {
			v = UnitVector (cprev - ori1);
			cnew2 = cprev + MulVector (v, fi1 > 0 ? -offset : offset);
			vertices [1] = cnew2;
		} else {
			v = MulVector (UnitVector (c0 - cprev), offset);
			vertices [1].x -= v.y;
			vertices [1].y += v.x;
		}
		i = 2;
	}
	for (; i < nVertices; i++) {
		arcInd2 = GetInternalSector (i, c0, cnext, ori2, fi2);
		GetCornerFilletCentre (&cprev, &c0, &cnext, arcInd1 > 0 ? arcInd1 : -1, &ori1, fi1, arcInd2 > 0 ? arcInd2 : -1, &ori2, fi2, true, true, offset, false, &cnew1 );
		if (i != 1 && arcInd1 > 0)	/* fgy021 */
			arcs [arcInd1].arcAngle = ComputeRotFi (ori1, cnew2, cnew1, fi1 < 0.0);
		vertices [i] = cnew1;
		arcInd1 = arcInd2;
		ori1 	= ori2;
		fi1  	= fi2;
		cnew2 	= cnew1;
		cprev 	= c0;
		c0		= cnext;
	}
	if (GetClosed ()) {
		vertices [nVertices] = vertices [1];
	} else {
		Point2D	invalidModifiedBegC;
		Point2D	invalidModifiedOrigo;
		double	invalidModifiedFi;
		arcInd1 = GetInternalSector (nVertices - 1, invalidModifiedBegC, c0, invalidModifiedOrigo, invalidModifiedFi);
		if (arcInd1 > 0) {
			v = UnitVector (c0 - ori1);
			cnew1 = vertices [nVertices] + MulVector (v, fi1 > 0 ? -offset : offset);
			vertices [nVertices] = cnew1;
		} else {
			v = MulVector (UnitVector (c0 - cprev), offset);
			vertices [nVertices].x -= v.y;
			vertices [nVertices].y += v.x;
		}
	}
	if (arcInd1 > 0)	/* fgy021 */
		arcs [arcInd1].arcAngle = ComputeRotFi (ori1, vertices [nVertices-1], vertices [nVertices], fi1 < 0.0);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetOffsetLimitEdge (double *offset, UIndex edgeId) const
{
	DBCHECKPOLY_NONURBS;
	GS::Int32				arcIndp, arcIndn, arcIndo;
	Curve2DData	begXEdgeCurve;
	Curve2DData	endXEdgeCurve;
	Curve2DData	offsetEdgeCurve;
	double maxOffset = *offset;
	UIndex					prevind, nextind, lastind;

	if (edgeId == 1 && !GetClosed ())
		return; //prevind = edgeId;
	else
		prevind = (edgeId == 1) ? nVertices - 1 : edgeId - 1;
	if (edgeId == nVertices - 1 && !GetClosed ())
		return; //nextind = edgeId;
	else
		nextind = (edgeId == nVertices - 1)? 1 : edgeId + 1;
	if (!GetClosed ())
		lastind = nextind + 1;
	else
		lastind = (nextind == nVertices - 1)? 1 : nextind + 1;

	begXEdgeCurve.epsilon = begXEdgeCurve.angleEpsilon = Eps;
	endXEdgeCurve.epsilon = endXEdgeCurve.angleEpsilon = Eps;
	offsetEdgeCurve.epsilon = offsetEdgeCurve.angleEpsilon = Eps;
	arcIndp = GetInternalArcIdx (prevind);
	if (arcIndp > 0) {
		begXEdgeCurve.type = CURVE2D_GenArc;
		begXEdgeCurve.genArc = SetGenArc (vertices[prevind], vertices[edgeId], arcs[arcIndp].arcAngle);
	} else {
		begXEdgeCurve.type = CURVE2D_Line;
		begXEdgeCurve.sector.c1 = vertices[prevind];
		begXEdgeCurve.sector.c2 = vertices[edgeId];
	}
	arcIndo = GetInternalArcIdx (edgeId);
	if (arcIndo > 0) {
		offsetEdgeCurve.type = CURVE2D_GenArc;
		offsetEdgeCurve.genArc = SetGenArc (vertices[edgeId], vertices[nextind], arcs[arcIndo].arcAngle);
	} else {
		offsetEdgeCurve.type = CURVE2D_Line;
		offsetEdgeCurve.sector.c1 = vertices[edgeId];
		offsetEdgeCurve.sector.c2 = vertices[nextind];
	}
	arcIndn = GetInternalArcIdx (nextind);
	if (arcIndn > 0) {
		endXEdgeCurve.type = CURVE2D_GenArc;
		endXEdgeCurve.genArc = SetGenArc (vertices[nextind], vertices[lastind], arcs[arcIndn].arcAngle);
	} else {
		endXEdgeCurve.type = CURVE2D_Line;
		endXEdgeCurve.sector.c1 = vertices[nextind];
		endXEdgeCurve.sector.c2 = vertices[lastind];
	}

	UnitVector_2D begCurveEndDir = GetCurve2DDataEndDirection (begXEdgeCurve);
	UnitVector_2D endCurveBegDir = GetCurve2DDataBegDirection (endXEdgeCurve);
	UnitVector_2D offsetCurveBegDir = GetCurve2DDataBegDirection (offsetEdgeCurve);
	UnitVector_2D offsetCurveEndDir = GetCurve2DDataEndDirection (offsetEdgeCurve);
	bool isBegParallel = fabs (GetDeflectionFromTo (begCurveEndDir, offsetCurveBegDir).GetValue (Degree)) < 10.0;
	bool isEndParallel = fabs (GetDeflectionFromTo (endCurveBegDir, offsetCurveEndDir).GetValue (Degree)) < 10.0;

	if (!isBegParallel && !isEndParallel) {
		maxOffset = LimitOffsetToXNeigEdges (begXEdgeCurve, endXEdgeCurve, offsetEdgeCurve, maxOffset);

		double maxBegOffset = maxOffset;
		double maxEndOffset = maxOffset;
		LimitOffsetForArc (begXEdgeCurve, endXEdgeCurve, offsetEdgeCurve, maxOffset, &maxBegOffset, &maxEndOffset);
		if (maxOffset < 0.0) {
			maxOffset = MAX (maxOffset, maxBegOffset);
			maxOffset = MAX (maxOffset, maxEndOffset);
		} else {
			maxOffset = MIN (maxOffset, maxBegOffset);
			maxOffset = MIN (maxOffset, maxEndOffset);
		}
		*offset = maxOffset;
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::OffsetOneEdge (double offset, UIndex edgeId, bool *degen1, Point2D *degenC1, bool *degen2, Point2D *degenC2)
{
	DBCHECKPOLY_NONURBS;
	CorePolyline2D origPolyline (*this);
	bool goodOffset;
	GS::Int32	prevind;
	UIndex	arcInd1, arcInd2;
	Vector2D	v;
	Point2D	cprev, c0, cnext, ori1, ori2, cnew1, cnew2;
	double	fi1, fi2;

	goodOffset = true;
	if (degen1 != nullptr)
		*degen1 = false;
	if (degen2 != nullptr)
		*degen2 = false;

	if ((edgeId == 1) && !GetClosed ()) {
		arcInd1 = GetInternalSector (1, cprev, c0, ori1, fi1);
		if (arcInd1 > 0) {
			v = UnitVector (cprev - ori1);
			cnew2 = cprev + MulVector (v, fi1 > 0 ? -offset : offset);
			vertices [1] = cnew2;
		} else {
			v = MulVector (UnitVector (c0 - cprev), offset);
			vertices [1].x -= v.y;
			vertices [1].y += v.x;
		}
	} else {
		prevind = (edgeId == 1) ? nVertices - 1 : edgeId - 1;
		arcInd1 = GetInternalSector (prevind, cprev, c0, ori1, fi1);
		cnew2 = cprev;
		arcInd2 = GetInternalSector (edgeId, c0, cnext, ori2, fi2);
		if (!GetCornerFilletCentre (&cprev, &c0, &cnext, arcInd1 > 0 ? arcInd1 : -1, &ori1, fi1, arcInd2 > 0 ? arcInd2 : -1, &ori2, fi2, false, true, offset, false, &cnew1, degen1))
			goodOffset = false;
		if (degen1 != nullptr && degenC1 != nullptr && *degen1)
			*degenC1 = vertices [edgeId];
		vertices [edgeId] = cnew1;
		if (arcInd1 > 0 && degen1 != nullptr && !*degen1)
			arcs [arcInd1].arcAngle = ComputeRotFi (ori1, cnew2, cnew1, fi1 < 0.0);
		if (degen1 != nullptr && *degen1 && !goodOffset) {
			goodOffset = true;
			*degen1    = false;
		}
		arcInd1 = arcInd2;
		ori1 	= ori2;
		fi1  	= fi2;
		cnew2 	= cnew1;
		cprev 	= c0;
		c0		= cnext;
	}

	if ((edgeId == nVertices - 1) && !GetClosed ()) {
		arcInd1 = origPolyline.GetInternalSector (nVertices - 1, cprev, c0, ori1, fi1);
		if (arcInd1 > 0) {
			v = UnitVector (c0 - ori1);
			cnew1 = origPolyline.vertices [nVertices] + v * (fi1 > 0 ? -offset : offset);
			vertices [nVertices] = cnew1;
		} else {
			v = UnitVector (c0 - cprev) * offset;
			vertices [nVertices].x -= v.y;
			vertices [nVertices].y += v.x;
		}
	} else {
		arcInd2 = GetInternalSector ((edgeId == nVertices - 1) ? 1 : edgeId + 1, c0, cnext, ori2, fi2);
		if (!GetCornerFilletCentre (&cprev, &c0, &cnext, arcInd1 > 0 ? arcInd1 : -1, &ori1, fi1, arcInd2 ? arcInd2 : -1, &ori2, fi2, true, false, offset, false, &cnew1, degen2))
			goodOffset = false;
		if (degen2 != nullptr && degenC2 != nullptr && *degen2)
			*degenC2 = vertices [(edgeId == nVertices - 1) ? 1 : edgeId + 1];
		vertices [(edgeId == nVertices - 1) ? 1 : edgeId + 1] = cnew1;
		if (arcInd1 > 0)
			arcs [arcInd1].arcAngle = ComputeRotFi (ori1, cnew2, cnew1, fi1 < 0.0);
		if (arcInd2 > 0 && degen2 != nullptr && !*degen2)
			arcs [arcInd2].arcAngle = ComputeRotFi (ori2, cnew1, cnext, fi2 < 0.0);
		if (degen2 != nullptr && *degen2 && !goodOffset) {
			*degen2    = false;
		}
	}
	if (GetClosed ())
		vertices [nVertices] = vertices [1];
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DropNurbs (void) {
	if (nNurbs == 0)
		return;

	DBBREAK_STR ("Polyline's NURBSes will be dropped");
	nNurbs = 0;
	nurbs.Clear ();
	UpdateBoundingBox ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetInternalData (	const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>&	origPoly,
																						const USize																verticesNum,
																						const double*															coords,
																						const USize																arcsNum,
																						const PolyArcRec*														pArcs,
																						const USize																nurbsNum,
																						const NurbsRec*															inNurbs,
																						const GS::Array <const EdgeUserData*>&									customInhEdgeInfo,
																						const GS::Int32*														inds,
																						const GS::Int32*														indc)
{
	UIndex	i;
	for (i = 1; i <= verticesNum; i++) {
		vertices[i].x = coords[2*i];		// first coords index is 1
		vertices[i].y = coords[2*i + 1];
	}
	for (UIndex arcIdx = 1; arcIdx <= arcsNum; arcIdx++) {
		arcs[arcIdx] = pArcs[arcIdx - 1];	// first pArcs index is 0
	}
	for (i = 0; i < nurbsNum; i++) {
		nurbs[i] = inNurbs[i];
	}

	GS::Int32 nOriVert = origPoly.nVertices;
	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
		inhEdgeInfos [0] = defaultEdgeData;
		for (i = 1; i <= verticesNum; i++) {
			if (inds == nullptr || inds[i] == 0 || inds[i] >= nOriVert) {
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
	if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
		vertexInfos [0] = defaultVertexData;
		for (i = 1; i <= verticesNum; i++) {
			if (indc == nullptr || indc[i] == 0 || indc[i] > nOriVert)
				vertexInfos [i] = defaultVertexData;
			else
				vertexInfos [i] = origPoly.vertexInfos [indc[i]];
		}
	}
	
	flags.isClosed = false;

	RemoveSmallArcs ();

	UpdateBoundingBox ();

	if (origPoly.flags.isClosed)
		DetectAndSetClosed ();

	DBCHECKPOLY_CHECK;
}		/* SetInternalData */

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CutWithHalfPlanes (	const GS::Array<HalfPlane2DData>&			cutlines,	/* -> line params. 			*/
																	GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >&	result, 	/* <- result polylines		*/
																	bool										*fullin,	/* <- full inside 			*/
																	GS::Int32 									*wrcode) const	/* <- warning error code   	*/
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

	DBCHECKPOLY_NONURBS;
	PolylineResult polyResult = NewPolylines;

	GS::Int32	i;
	GS::Int32	ipa, ipb, ipc, ipr;
	GS::Int32	*parts;
	GS::UInt32	*pends;
	double		*pcoos;
	PolyArcRec	*parcs;
	GS::Int32	*pcind, *ppind;
	GS::Int32	jpa, jpb, jpc, jpr;
	GS::Int32	*cparts;
	GS::UInt32	*cpends;
	double		*cpcoos;
	PolyArcRec	*cparcs;
	GS::Int32	*cpcind, *cppind;
	GS::Int32	iipa, iipb, ipbb, ipcc;
	UIndex		iprr;
	GS::Int32	ipa1, ipa2, oends;
	UIndex		ocoos;
	UIndex		oarcs;

	*wrcode = 0;
	*fullin = false;

	ipa = 1;
	ipb = 1;
	ipc = nVertices;
	ipr = nArcs;

	if (ipc < 1)
		return EmptyPolyline;

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
		BMpFree ((GSPtr) parts); BMpFree ((GSPtr) pends); BMpFree ((GSPtr) pcoos); BMpFree ((GSPtr) parcs); BMpFree ((GSPtr) pcind); BMpFree ((GSPtr) ppind);
		return EmptyPolyline;
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
	pends[1] = nVertices;
	if (GetClosed ()) {
		pcind[pends[1]] = pcind[pends[0] + 1];		/* RJ007 */
		ppind[pends[1]] = ppind[pends[0] + 1];		/* RJ019 */
	}

	for (i = 0; i < ipr; i++)								/* sm200 */
		parcs[i] = arcs[i+1];

	ipa1 = cparts [0] + 1;
	ipa2 = cparts [1];
	cpends [0] = 0;

	CutPolyRes ret = CUCutNumPoly ((short)cutlines.GetSize (), const_cast<HalfPlane2DData*> (cutlines.GetContent ()), ipa, parts, ipb, pends, ipc, pcoos, ipr, parcs, true, !GetClosed (), true, &(boundBox), true, pcind, ppind,
		&jpa, &cparts, &jpb, &cpends, &jpc, &cpcoos, &jpr, &cparcs, &cpcind, &cppind, fullin, wrcode, nullptr);

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
					GS::Array <const EdgeUserData*>	customInhEdgeInfo;
					//TODO inhEdgeInfos.GetSize() helyett sizeof (EdgeUserData)  ??  CorePolygon2D-ben is !!!!!
					if ((GS::UInt32)cutlines[0].sizeOfInhEdgeInfo == inhEdgeInfos.GetSize() && flags.isEdgeUserData) {
						for (UIndex cutIdx = 0; cutIdx < cutlines.GetSize (); cutIdx++) {
							if ((GS::UInt32)cutlines [cutIdx].sizeOfInhEdgeInfo != inhEdgeInfos.GetSize()) {
								customInhEdgeInfo.Clear ();
								break;
							}
							customInhEdgeInfo.Push (reinterpret_cast<const EdgeUserData*> (cutlines [cutIdx].inhEdgeInfo));
						}
					}

					GS::SharedPtr<CorePolyline2D> newPoly = new CorePolyline2D (*this, true);
					newPoly->CopyPolygonLevelDataFrom (*this);
					newPoly->AllocateInternalData (ipcc /*verticesNum*/, iprr /*arcsNum*/, 0/*nurbsNum*/);

					newPoly->SetInternalData (	*this,
												ipcc, cpcoos + 2*ocoos,
												iprr, cparcs + oarcs,
												0, nullptr,
												customInhEdgeInfo,
												cpcind + ocoos,
												cppind + ocoos);
					result.Push (newPoly);
				}

				/* for the next ipcc calculation */
				cpends [oends + ipbb] += ocoos;
				oends += ipbb;	/* oends == cparts [iipa] */
				ocoos += ipcc;
				oarcs += iprr;
			}
		}
	}

	BMpFree ((GSPtr) cparts); BMpFree ((GSPtr) cpends); BMpFree ((GSPtr) cpcoos); BMpFree ((GSPtr) cparcs); BMpFree ((GSPtr) cpcind); BMpFree ((GSPtr) cppind);

	return ret == Failed ? EmptyPolyline : polyResult;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
Box2DData CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CalcBoundBox (void) const
{
	Box2DData tmpBoundBox;

	// go through on the main contour vertices
	for (UIndex iVertex = 1; iVertex <= nVertices; iVertex++) {
		tmpBoundBox.xMin = MIN (tmpBoundBox.xMin, vertices[iVertex].x);
		tmpBoundBox.yMin = MIN (tmpBoundBox.yMin, vertices[iVertex].y);
		tmpBoundBox.xMax = MAX (tmpBoundBox.xMax, vertices[iVertex].x);
		tmpBoundBox.yMax = MAX (tmpBoundBox.yMax, vertices[iVertex].y);
	}

	// go through on the main contour arcs
	for (UIndex iArc = 1; iArc <= nArcs; iArc++) {
		if (arcs[iArc].begIndex <= nVertices) {
			GS::Int32	iBegPt = arcs[iArc].begIndex;
			GS::Int32	iEndPt = arcs[iArc].endIndex;
			double	angView = arcs[iArc].arcAngle;
			Point2D	ptBeg = vertices[iBegPt];
			Point2D	ptEnd = vertices[iEndPt];
			Point2D	ptCenter;
			Geometry::ArcGetOrigo (&ptBeg, &ptEnd, angView, &ptCenter);
			double	angBeg = Geometry::ComputeFi (ptCenter, ptBeg);
			double	angEnd = Geometry::ComputeFi (ptCenter, ptEnd);
			double	radius = (ptCenter - ptBeg).GetLength ();
			/* if back-oriented */
			if (angView < 0.0) {
				double	angSwap;
				angSwap = angBeg;
				angBeg = angEnd;
				angEnd = angSwap;
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

	// go through on the main contour nurbs
	for (UIndex iNurbs = 0; iNurbs < nNurbs; iNurbs++) {
		Box2DData nurbsBox = nurbs[iNurbs].nurbs.CalculateTightBoundingBox ();	// TODO : ha a CPBB benne van a tmpBB-ben, felesleges szuk BB-t szamolni

		tmpBoundBox.xMax = MAX (tmpBoundBox.xMax, nurbsBox.xMax);
		tmpBoundBox.yMax = MAX (tmpBoundBox.yMax, nurbsBox.yMax);
		tmpBoundBox.xMin = MIN (tmpBoundBox.xMin, nurbsBox.xMin);
		tmpBoundBox.yMin = MIN (tmpBoundBox.yMin, nurbsBox.yMin);
	}

	return tmpBoundBox;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::UpdateBoundingBox (void)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	boundBox = CalcBoundBox ();
}

#pragma warning(push)
#pragma warning(disable:4127) //conditional expression is constant - Because of template argument
#pragma warning(disable:4100) //'comparator': unreferenced formal parameter - It is unreferenced when "checkUserData" is false

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class EdgeUserDataComparator, bool checkUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::RemoveSameDirEdge (const EdgeUserDataComparator& comparator)
{
	double	dx12, dy12, dx23, dy23, a12, a23;
	for (GS::UInt32 i = 2; i < nVertices; ++i) {
		if (!checkUserData || comparator (inhEdgeInfos[i - 1], inhEdgeInfos[i])) {
			if (GetInternalArcIdx (i) == 0 && GetInternalArcIdx (i - 1) == 0 &&
				GetInternalNurbsIdx (i) == MaxUInt32 && GetInternalNurbsIdx (i - 1) == MaxUInt32) {
				const Point2D& prev = vertices[i - 1];
				const Point2D& c = vertices[i];
				const Point2D& next = vertices[i + 1];

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
	if (nVertices > 2 && GetClosed ()) {
		if (!checkUserData || comparator (inhEdgeInfos[nVertices - 1], inhEdgeInfos[nVertices])) {
			if (GetInternalArcIdx (nVertices - 1) == 0 && GetInternalArcIdx (1) == 0 &&
				GetInternalNurbsIdx (nVertices - 1) == MaxUInt32 && GetInternalNurbsIdx (1) == MaxUInt32) {
				const Point2D& prev = vertices[nVertices - 1];
				const Point2D& c = vertices[nVertices];
				const Point2D& next = vertices[2];

				dx12 = c.x - prev.x;
				dy12 = c.y - prev.y;
				dx23 = next.x - c.x;
				dy23 = next.y - c.y;

				a12 = Geometry::ArcTan (dy12, dx12);
				a23 = Geometry::ArcTan (dy23, dx23);
				if (IsNearZero (a12 - a23, Eps))
					DeleteVertexFromInternalData (nVertices);
			}
		}
		if (GetInternalArcIdx (nVertices - 1) != 0 && GetInternalArcIdx (1) != 0) {
			const UIndex prevEdgeArcInd = GetInternalArcIdx (nVertices - 1);
			const double prevEdgeArcAngle = arcs[prevEdgeArcInd].arcAngle;
			const UIndex nextEdgeArcInd = GetInternalArcIdx (1);
			const double nextEdgeArcAngle = arcs[nextEdgeArcInd].arcAngle;
			if (prevEdgeArcAngle * nextEdgeArcAngle > 0.0) {		/* Same arc direction*/
				if (fabs (prevEdgeArcAngle + nextEdgeArcAngle) < 2 * PI - RadEps) {
					const Point2D& prev = vertices[nVertices - 1];
					const Point2D& c = vertices[nVertices];
					const Point2D& next = vertices[2];
					Point2D prevArcOrigo;
					ArcGetOrigo (&prev, &c, prevEdgeArcAngle, &prevArcOrigo);
					Point2D nextArcOrigo;
					ArcGetOrigo (&c, &next, nextEdgeArcAngle, &nextArcOrigo);
					if (Dist (prevArcOrigo, nextArcOrigo) < Eps) {
						arcs[prevEdgeArcInd].arcAngle = prevEdgeArcAngle + nextEdgeArcAngle;
						DeleteVertexFromInternalData (nVertices);
					}
				}
			}
		}
	}
}

#pragma warning(pop)

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::RemoveSameDirEdge ()
{
	RemoveSameDirEdge<std::equal_to<EdgeUserData>, false> (std::equal_to<EdgeUserData> ());
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Regularize (void)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	USize origNVertices = nVertices;

	if (!flags.isSameCoord && nVertices > 0) {
		DeleteNearPoints ();
	}

	if (!flags.isSameDirEdgeLegal) {
		RemoveSameDirEdge ();
	}

	if (nVertices == 1) {
		nVertices = 0;
		vertices.Clear ();
		vertexInfos.Clear();

		nArcs = 0;
		arcs.Clear ();
		nNurbs = 0;
		nurbs.Clear ();
		inhEdgeInfos.Clear();
	} else if (nVertices > 1 && GetClosed ()) {
		if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
			vertexInfos [1] = vertexInfos [nVertices];
		}
		if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
			inhEdgeInfos [nVertices] = inhEdgeInfos [1];
		}

		vertices[1] = vertices[nVertices];
	}

	RemoveSmallArcs ();
	if (origNVertices != nVertices) {
		UpdateBoundingBox ();
	}
	DBCHECKPOLY_CHECK;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DeleteNearPoints (void)
{
	GS::UInt32 pointNrToBeDeleted = 0;

	GS::UInt32 arcNrToBeDeleted = 0;
	GS::UInt32 arcIndex = 1;

	GS::UInt32 nurbsNrToBeDeleted = 0;
	GS::UInt32 nurbsIndex = 0;

	GS::UInt32 firstPointToBeDeleted = 2;

	for (; firstPointToBeDeleted <= nVertices; ++firstPointToBeDeleted) {
		if (IsEqualCoord (vertices[firstPointToBeDeleted], vertices[firstPointToBeDeleted - 1], Eps)) {
			break;
		}
	}

	if (arcs.GetSize () > 2)
		GS::Sort (++arcs.Begin (), arcs.End (), [](const PolyArcRec& arc1, const PolyArcRec& arc2) -> bool { return arc1.begIndex < arc2.begIndex; });

	for (; arcIndex <= nArcs && arcs[arcIndex].endIndex < firstPointToBeDeleted; ++arcIndex);
	for (; nurbsIndex < nNurbs && nurbs[nurbsIndex].begIndex + 1 < firstPointToBeDeleted; ++nurbsIndex);

	if (firstPointToBeDeleted <= nVertices) {
		// base of the algorithm
		for (GS::UInt32 i = firstPointToBeDeleted; i <= nVertices; ++i) {
			if (IsEqualCoord (vertices[i], vertices[i - 1 - pointNrToBeDeleted], Eps)) {
				++pointNrToBeDeleted;

				if (nArcs >= arcIndex && arcs[arcIndex].endIndex == i) {
					++arcNrToBeDeleted;
					++arcIndex;
				}

				if (nNurbs > nurbsIndex && nurbs[nurbsIndex].begIndex + 1 == i) {
					++nurbsNrToBeDeleted;
					++nurbsIndex;
				}
			} else {
				vertices[i - pointNrToBeDeleted] = vertices[i];
				if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
					vertexInfos[i - pointNrToBeDeleted] = vertexInfos[i];
				}
				if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
					inhEdgeInfos[i - pointNrToBeDeleted - 1] = inhEdgeInfos[i - 1];
				}

				if (nArcs >= arcIndex && arcs[arcIndex].endIndex == i) {
					arcs[arcIndex - arcNrToBeDeleted] = arcs[arcIndex];
					arcs[arcIndex - arcNrToBeDeleted].begIndex -= pointNrToBeDeleted;
					arcs[arcIndex - arcNrToBeDeleted].endIndex -= pointNrToBeDeleted;
					++arcIndex;
				}

				if (nNurbs > nurbsIndex && nurbs[nurbsIndex].begIndex + 1 == i) {
					nurbs[nurbsIndex - nurbsNrToBeDeleted] = nurbs[nurbsIndex];
					nurbs[nurbsIndex - nurbsNrToBeDeleted].begIndex -= pointNrToBeDeleted;
				}
			}
		}
		DBASSERT (arcIndex == nArcs + 1);
		DBASSERT (nurbsIndex == nNurbs);

		nVertices -= pointNrToBeDeleted;
		
		vertices.SetSize (nVertices + 1);
		if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
			vertexInfos.SetSize (nVertices + 1);
		}
		if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
			inhEdgeInfos.SetSize (nVertices + 1);
		}

		nArcs -= arcNrToBeDeleted;
		arcs.SetSize (nArcs + 1);

		nNurbs -= nurbsNrToBeDeleted;
		nurbs.SetSize (nNurbs);
	}
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CorePolyline2D ( const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& source )
{
	InitInternalData ();

	CopyInternalDataFrom (source);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CorePolyline2D ( const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, UIndex contourIdx )
{
	InitInternalData ();

	if (source.IsEmpty ())
		return;

	CopyInternalDataFrom (source, contourIdx);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CorePolyline2D (Flags actFlags )
{
	InitInternalData ();
	flags = actFlags;
	if (inhPolygonInfo.GetSize () != 0 && flags.isPolygonUserData) {
		inhPolygonInfo.SetSize (1);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CorePolyline2D (const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& source, bool copyPolygonLevelDataOnly)
{
	InitInternalData ();
	if (copyPolygonLevelDataOnly)
		CopyPolygonLevelDataFrom (source);
	else
		CopyInternalDataFrom (source);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CorePolyline2D (Flags actFlags, const Box2DData& box)
{
	InitInternalData ();
	flags = actFlags;

	if (box.IsEmpty ())
		return;

	SetClosed (true);

	AllocateInternalData (5 /*nVertices*/, 0 /*nArcs*/, 0 /*nNurbs*/);
	Point2D coords[4];
	coords[0].x = box.xMin;
	coords[0].y = box.yMin;

	coords[1].x = box.xMax;
	coords[1].y = box.yMin;

	coords[2].x = box.xMax;
	coords[2].y = box.yMax;

	coords[3].x = box.xMin;
	coords[3].y = box.yMax;
	SetInternalData (coords, 4, nullptr, 0, nullptr, 0, 0 /*PolyCreateFlags*/);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CorePolyline2D (Flags actFlags, const Point2D* pCoords, USize coordNum, const PolyArcRec* pArcs, USize arcNum, GS::UInt32 createFlags)
{
	DBASSERT (pArcs == nullptr || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));

	InitInternalData ();
	flags = actFlags;

#ifdef DEBUVERS
	UIndex coordOffset = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 0 : 1;
	DBASSERT (!actFlags.isClosed ||
			  ((PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) && IsEqualCoord (pCoords[1-coordOffset], pCoords[coordNum-coordOffset], EPS)) ||
			  !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags));
#endif

	if (actFlags.isClosed && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags))
		AllocateInternalData (coordNum + 1, arcNum, 0);
	else
		AllocateInternalData (coordNum, arcNum, 0);
	SetInternalData (pCoords, coordNum, arcNum == 0 ? nullptr : pArcs, arcNum, nullptr, 0, createFlags);

	Regularize ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CorePolyline2D (Flags actFlags, const Point2D* pCoords, USize coordNum, const PolyArcRec* pArcs, USize arcNum, UIndex begCoordIdx, UIndex endCoordIdx, GS::UInt32 createFlags)
{
#ifndef DEBUVERS
	UNUSED_PARAMETER (coordNum);
#endif

	DBASSERT (coordNum > 0 && pCoords != nullptr);
	DBASSERT ((arcNum == 0 && pArcs == nullptr) || (arcNum != 0 && pArcs != nullptr));
	DBASSERT (endCoordIdx > begCoordIdx);

	UIndex coordIdxOffset = (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags) ? 0 : 1;
#ifdef DEBUVERS
	UIndex coordOffset = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 0 : 1;

	DBASSERT (endCoordIdx-coordIdxOffset <= coordNum-coordOffset);
#endif

	InitInternalData ();
	flags = actFlags;

	if (pArcs != nullptr && arcNum != 0 && PolyCreateFlags_DummyArcAtIdxZero & createFlags)
		pArcs++;

	USize nCoords = endCoordIdx - begCoordIdx + 1;

	//count arcs
	USize nRelevantArcs = 0;
#ifdef DEBUVERS
	USize nLostArcs = 0;
#endif
	const PolyArcRec* pArcsCount = pArcs;
	for (UIndex srcArcIdx = 1; srcArcIdx <= arcNum; srcArcIdx++, pArcsCount++) {
		if (pArcsCount->begIndex >= begCoordIdx && pArcsCount->begIndex < endCoordIdx)
			nRelevantArcs++;
#ifdef DEBUVERS
		if (pArcsCount->begIndex == endCoordIdx ||
			(endCoordIdx-coordIdxOffset == coordNum-coordOffset && pArcsCount->begIndex > endCoordIdx))
			nLostArcs++;
#endif
	}

#ifdef DEBUVERS
	DBASSERT (nLostArcs == 0); //probably unintended data loss
#endif

	if (actFlags.isClosed && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags))
		AllocateInternalData (nCoords + 1, nRelevantArcs, 0);
	else
		AllocateInternalData (nCoords, nRelevantArcs, 0);

	//coords
	pCoords += begCoordIdx - coordIdxOffset;
	for (UIndex vertexIdx = 1; vertexIdx <= nCoords; vertexIdx++, pCoords++)
		vertices[vertexIdx] = *pCoords;
	if (actFlags.isClosed && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags))
		vertices[nVertices] = vertices[1];

	//arcs
	for (UIndex arcIdx = 1, srcArcIdx = 1; srcArcIdx <= arcNum && arcIdx <= nRelevantArcs; srcArcIdx++, pArcs++) {
		if (pArcs->begIndex >= begCoordIdx && pArcs->begIndex < endCoordIdx) {
			arcs[arcIdx] = *pArcs;
			arcs[arcIdx].begIndex -= begCoordIdx - 1;
			arcs[arcIdx].endIndex = arcs[arcIdx].begIndex + 1;
			arcIdx++;
		}
	}

	UpdateBoundingBox ();

	Regularize ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CorePolyline2D (Flags actFlags, const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags)
{
	DBASSERT (arcList.IsEmpty() || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));

	InitInternalData ();
	flags = actFlags;

	UIndex coordOffset = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 0 : 1;

	DBASSERT (!actFlags.isClosed ||
			  ((PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) && IsEqualCoord (coordList[1-coordOffset], coordList[coordList.GetSize ()-1], EPS)) ||
			  !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags));

	if (actFlags.isClosed && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags))
		AllocateInternalData (coordList.GetSize () + coordOffset,
			(!arcList.IsEmpty () && PolyCreateFlags_DummyArcAtIdxZero & createFlags) ? arcList.GetSize () - 1 : arcList.GetSize (), 0);
	else
		AllocateInternalData (coordList.GetSize () - 1 + coordOffset,
			(!arcList.IsEmpty () && PolyCreateFlags_DummyArcAtIdxZero & createFlags) ? arcList.GetSize () - 1 : arcList.GetSize (), 0);
		
	GS::Array<NurbsRec> nurbs;
	SetInternalData (coordList, arcList, /*TODO*/ nurbs, createFlags);

	Regularize ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CorePolyline2D (Flags actFlags, const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, UIndex begCoordIdx, UIndex endCoordIdx, GS::UInt32 createFlags)
{
	DBASSERT (endCoordIdx > begCoordIdx);

	UIndex coordIdxOffset = (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags) ? 0 : 1;

	DBASSERT (endCoordIdx-coordIdxOffset < coordList.GetSize ());

	InitInternalData ();
	flags = actFlags;

	USize nCoords = endCoordIdx - begCoordIdx + 1;

	//count arcs
	USize nRelevantArcs = 0;
#ifdef DEBUVERS
	USize nLostArcs = 0;
#endif
	UIndex srcArcIdx = 0;
	if (PolyCreateFlags_DummyArcAtIdxZero & createFlags)
		srcArcIdx++;
	for (; srcArcIdx < arcList.GetSize (); srcArcIdx++) {
		if (arcList[srcArcIdx].begIndex >= begCoordIdx && arcList[srcArcIdx].begIndex < endCoordIdx)
			nRelevantArcs++;
#ifdef DEBUVERS
		if (arcList[srcArcIdx].begIndex == endCoordIdx ||
			(endCoordIdx-coordIdxOffset == coordList.GetSize ()-1 && arcList[srcArcIdx].begIndex > endCoordIdx))
			nLostArcs++;
#endif
	}

#ifdef DEBUVERS
	DBASSERT (nLostArcs == 0); //probably unintended data loss
#endif

	if (actFlags.isClosed && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags))
		AllocateInternalData (nCoords + 1, nRelevantArcs, 0);
	else
		AllocateInternalData (nCoords, nRelevantArcs, 0);

	//coords
	UIndex coordIdx = begCoordIdx - coordIdxOffset;
	for (UIndex vertexIdx = 1; vertexIdx <= nCoords; vertexIdx++, coordIdx++)
		vertices[vertexIdx] = coordList[coordIdx];
	if (actFlags.isClosed && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags))
		vertices[nVertices] = vertices[1];

	//arcs
	srcArcIdx = 0;
	if (PolyCreateFlags_DummyArcAtIdxZero & createFlags)
		srcArcIdx++;
	for (UIndex arcIdx = 1; srcArcIdx < arcList.GetSize () && arcIdx <= nRelevantArcs; srcArcIdx++) {
		if (arcList[srcArcIdx].begIndex >= begCoordIdx && arcList[srcArcIdx].begIndex < endCoordIdx) {
			arcs[arcIdx] = arcList[srcArcIdx];
			arcs[arcIdx].begIndex -= begCoordIdx - 1;
			arcs[arcIdx].endIndex = arcs[arcIdx].begIndex + 1;
			arcIdx++;
		}
	}

	UpdateBoundingBox ();

	Regularize ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CorePolyline2D (Flags actFlags, const GenArc genArc, const ArcDivParams& arcDivParams)
{
	InitInternalData ();
	flags = actFlags;

	if (arcDivParams.maxDifference != 0.0 || arcDivParams.boxToKeepMaxDifferenceIn != nullptr) {
		GS::Array<Point2D>		coords;
		GS::Array<PolyArcRec>	arcs;
		GS::Array<NurbsRec>		nurbs;
		if (genArc.IsElliptic ()) {
			Geometry::DivideEllArcToCo (genArc, arcDivParams.maxDifference, coords);
		} else {
			Geometry::DivideArcToCo (genArc, arcDivParams, coords);
		}

		AllocateInternalData (coords.GetSize (), 0, 0);
		SetInternalData (coords, arcs, nurbs, 0 /*PolyCreateFlags*/);
	} else {
		AllocateInternalData (2, 1, 0);
		Point2D coords[2];
		coords[0] = genArc.GetBegC ();
		coords[1] = genArc.GetEndC ();
		PolyArcRec pArcs;
		pArcs.begIndex = 1;
		pArcs.endIndex = 2;
		pArcs.arcAngle = genArc.GetArcAngle ();

		SetInternalData (coords, 2, &pArcs, 1, nullptr, 0, 0 /*PolyCreateFlags*/);
	}
	Regularize ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::FillCorePolyline2DFromContourDesc (const CustomPolyContourDescription<VertexUserData, EdgeUserData, PolygonUserData>& contourDesc)
{
	UIndex vertexIdx = 0;
	UIndex vertIdx = 0;
	UIndex arcIdx = 1;
	UIndex nurbsIdx = 0;
	{
		for (vertexIdx = 0; vertexIdx < contourDesc.GetSegmentList().GetSize() - 1; vertexIdx++) {
			vertIdx++;
			vertices[vertIdx] = contourDesc.GetSegmentList()[vertexIdx].GetVertex().GetCoord();
			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
				(vertexInfos)[vertIdx] = contourDesc.GetSegmentList()[vertexIdx].GetVertex().GetPolyVertexUserData();
			if (!contourDesc.GetSegmentList()[vertexIdx].GetEdge().IsStraight()) {
				arcs[arcIdx].arcAngle = contourDesc.GetSegmentList()[vertexIdx].GetEdge().GetArcAngle();
				arcs[arcIdx].begIndex = vertIdx;
				arcs[arcIdx].endIndex = arcs[arcIdx].begIndex + 1;
				arcIdx++;
			}
			if (!contourDesc.GetSegmentList()[vertexIdx].GetNurbs().IsEmpty()) {
				nurbs[nurbsIdx].nurbs		= contourDesc.GetSegmentList()[vertexIdx].GetNurbs();
				nurbs[nurbsIdx].begIndex	= vertIdx;
				nurbsIdx++;
			}
			if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
				(inhEdgeInfos)[vertIdx] = contourDesc.GetSegmentList()[vertexIdx].GetEdge().GetPolyEdgeUserData();
		}

		// Contour descriptions created from (Irregular)Polygon2Ds or Polyline2Ds usually don't have duplicated vertices at the contour end
		// ASSERT if the first and last coordinates are equal but the last edge has a valid angle other than zero
		DBASSERT (!(!contourDesc.GetSegmentList()[vertexIdx].GetEdge().HasInvalidAngle() && !contourDesc.GetSegmentList()[vertexIdx].GetEdge().IsStraight() &&
			IsEqualCoord (contourDesc.GetSegmentList()[0].GetVertex().GetCoord(), contourDesc.GetSegmentList()[vertexIdx].GetVertex().GetCoord(), EPS)));
		// 1. we are creating a closed polyline from a contour description originally converted from a fully open polyline (first coords != last coords) =>
		// ASSERT if the first and last coordinates are not equal but the last edge has an invalid angle
		DBASSERT (!(GetClosed () && contourDesc.GetSegmentList()[vertexIdx].GetEdge().HasInvalidAngle() &&
			!IsEqualCoord (contourDesc.GetSegmentList()[0].GetVertex().GetCoord(), contourDesc.GetSegmentList()[vertexIdx].GetVertex().GetCoord(), EPS)));
		// 2. we are trying to create an open polyline from a contour description originally converted from a closed polyline =>
		// ASSERT if the last edge has a valid angle and the first and last coordinates are not equal
		DBASSERT (!(!GetClosed () && !contourDesc.GetSegmentList()[vertexIdx].GetEdge().HasInvalidAngle() &&
			!IsEqualCoord (contourDesc.GetSegmentList()[0].GetVertex().GetCoord(), contourDesc.GetSegmentList()[vertexIdx].GetVertex().GetCoord(), EPS)));

		vertIdx++;
		vertices[vertIdx] = contourDesc.GetSegmentList()[vertexIdx].GetVertex().GetCoord();
		if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
			(vertexInfos)[vertIdx] = contourDesc.GetSegmentList()[vertexIdx].GetVertex().GetPolyVertexUserData();
		if (!contourDesc.GetSegmentList()[vertexIdx].GetEdge().HasInvalidAngle() && !contourDesc.GetSegmentList()[vertexIdx].GetEdge().IsStraight()) {
			arcs[arcIdx].arcAngle = contourDesc.GetSegmentList()[vertexIdx].GetEdge().GetArcAngle();
			arcs[arcIdx].begIndex = vertIdx;
			arcs[arcIdx].endIndex = arcs[arcIdx].begIndex + 1;
			arcIdx++;
		}
		if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
			(inhEdgeInfos)[vertIdx] = contourDesc.GetSegmentList()[vertexIdx].GetEdge().GetPolyEdgeUserData();

		if (GetClosed ()) {
			vertIdx++;
			vertices[vertIdx] = contourDesc.GetSegmentList()[0].GetVertex().GetCoord();
			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
				(vertexInfos)[vertIdx] = contourDesc.GetSegmentList()[0].GetVertex().GetPolyVertexUserData();
			if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
				(inhEdgeInfos)[vertIdx] = contourDesc.GetSegmentList()[0].GetEdge().GetPolyEdgeUserData();
		}
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CorePolyline2D (Flags actFlags, const CustomPolyContourDescription<VertexUserData, EdgeUserData, PolygonUserData>& contourDesc)
{
	InitInternalData ();
	flags = actFlags;

	UIndex vertexIdx = 0;
	UIndex verticesNum = 0;
	UIndex arcsNum = 0;
	UIndex nurbsNum = 0;

	if (GetClosed ())
		verticesNum += contourDesc.GetSegmentList().GetSize() + 1;
	else
		verticesNum += contourDesc.GetSegmentList().GetSize();
	for (vertexIdx = 0; vertexIdx < contourDesc.GetSegmentList().GetSize() - 1; vertexIdx++) {
		if (!contourDesc.GetSegmentList()[vertexIdx].GetEdge().IsStraight()) {
			arcsNum++;
		}
		if (!contourDesc.GetSegmentList()[vertexIdx].GetNurbs().IsEmpty()) {
			nurbsNum++;
		}
	}
	if (!contourDesc.GetSegmentList()[vertexIdx].GetEdge().HasInvalidAngle() && !contourDesc.GetSegmentList()[vertexIdx].GetEdge().IsStraight()) {
		arcsNum++;
	}

	if (verticesNum <= 1) {
		if (inhPolygonInfo.GetSize() == 0 && flags.isPolygonUserData) {
			inhPolygonInfo.SetSize (1);
		}
		return;
	}

	AllocateInternalData (verticesNum, arcsNum, nurbsNum);
	if (inhPolygonInfo.GetSize() != 0 && flags.isPolygonUserData) {
		inhPolygonInfo [0] = contourDesc.GetPolyContourUserData ();
	}

	FillCorePolyline2DFromContourDesc (contourDesc);
	UpdateBoundingBox ();
	Regularize ();

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::~CorePolyline2D ()
{
	FreeInternalData ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (Flags actFlags, const Point2D* pCoords, USize coordNum, const PolyArcRec* pArcs, USize arcNum, const UIndex* pContourEnds, USize contourNum, GS::UInt32 createFlags, GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >& result)
{
	DBASSERT (pArcs == nullptr || ((PolyCreateFlags_IdxRefInArcFromZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) ||
		(!(PolyCreateFlags_IdxRefInArcFromZero & createFlags) && !(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (pArcs == nullptr || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));
	DBASSERT (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (contourNum >= 1 && pContourEnds != nullptr);

	UIndex coordOffset = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 0 : 1;
	UIndex coordIdxOffset = ((PolyCreateFlags_IdxRefInArcFromZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) ? 0 : 1;

	if (pContourEnds != nullptr && PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)
		pContourEnds++;

	UIndex begCoordIdx = 1 - coordOffset + coordIdxOffset;
	UIndex endCoordIdx = begCoordIdx;

	for (UIndex contourIdx = 1; contourIdx <= contourNum && endCoordIdx <= coordNum; contourIdx++, pContourEnds++) {
		endCoordIdx = *pContourEnds;

		DBASSERT (!actFlags.isClosed ||
				  ((PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) && IsEqualCoord (pCoords[begCoordIdx], pCoords[endCoordIdx], EPS)) ||
				  !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags));

		result.Push (new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (actFlags, pCoords, coordNum, pArcs, arcNum, begCoordIdx, endCoordIdx, createFlags));
		begCoordIdx = endCoordIdx + 1;
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (Flags actFlags, const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex> contourEndList, GS::UInt32 createFlags, GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >& result)
{
	DBASSERT (arcList.IsEmpty () || ((PolyCreateFlags_IdxRefInArcFromZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)) ||
		(!(PolyCreateFlags_IdxRefInArcFromZero & createFlags) && !(PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (arcList.IsEmpty () || !(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));
	DBASSERT (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags)));
	DBASSERT (!contourEndList.IsEmpty ());

	UIndex coordOffset = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 0 : 1;
	UIndex coordIdxOffset = (PolyCreateFlags_IdxRefInContourEndFromZero & createFlags) ? 0 : 1;

	UIndex begCoordIdx = 1 - coordOffset + coordIdxOffset;
	UIndex endCoordIdx = begCoordIdx;

	UIndex srcContourIdx = 0;
	if (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags)
		srcContourIdx++;
	for (; srcContourIdx < contourEndList.GetSize () && endCoordIdx < coordList.GetSize (); srcContourIdx++) {
		endCoordIdx = contourEndList[srcContourIdx];

		DBASSERT (!actFlags.isClosed ||
				  ((PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags) && IsEqualCoord (coordList[begCoordIdx], coordList[endCoordIdx], EPS)) ||
				  !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags));

		result.Push (new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (actFlags, coordList, arcList, begCoordIdx, endCoordIdx, createFlags));
		begCoordIdx = endCoordIdx + 1;
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::IsFirstLastCoordEqual (void) const
{
	if (nVertices < 1) {
		DBBREAK ();
		return true;
	}
	return IsEqualCoord (vertices[1], vertices[nVertices], EPS);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyPolylineDataVertices (Point2D* destCoords, USize& coordNum, GS::UInt32 createFlags) const
{
	bool errorOccured = false;

	//vertices
	USize numOfCoords = nVertices;
	if (GetClosed () && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) //do not duplicate first coord at contour end
		numOfCoords--;

	if (destCoords != nullptr) {
		if (numOfCoords <= coordNum) {
			const Point2D* sourceCoords = vertices.GetContent ();
			if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags)) //do not start with blank coord
				sourceCoords++;
			BNCopyMemory (destCoords, sourceCoords, ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? numOfCoords + 1 : numOfCoords) * sizeof (Point2D));
		} else
			errorOccured = true;
	}
	coordNum = numOfCoords;
	return !errorOccured;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyPolylineDataArcs (PolyArcRec* destArcs, USize& arcNum, GS::UInt32 createFlags) const
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

			if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) &&
				(PolyCreateFlags_IdxRefInArcFromZero & createFlags)) { //first meaningful coord at index 0
					for (UIndex arcIdx = arcOffset; arcIdx < nArcs + arcOffset; arcIdx++) {
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

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyPolylineDataNurbs (GS::Array<NurbsCurve2D>& destNurbs) const
{
	destNurbs.SetSize (nNurbs);
	for (UIndex iNurbs = 0; iNurbs < nNurbs; iNurbs++) {
		destNurbs[iNurbs] = nurbs[iNurbs].nurbs;
	}

	return true;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::operator=( const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& source )
{
	if (this == &source)
		return *this;

	DBCHECKPOLY_ONEREFTOTHIS;

	FreeInternalData ();
	InitInternalData ();

	CopyInternalDataFrom (source);

	return *this;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CompareGeometry( const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& source ) const
{
	GS::Int32 differences = 0;
	// 	if (polyChanges != nullptr)
	// 		polyChanges->Clear ();

	for (GS::Int32 vp = 1; static_cast<UIndex> (vp) < source.nVertices; ++vp) {
		const Sector *pEdge = reinterpret_cast<const Sector*> (&source.vertices[vp]);
		UIndex ap = source.GetInternalArcIdx (vp);
		UIndex np = source.GetInternalNurbsIdx (vp);
		bool found = false;
		for (GS::Int32 vr = 1; static_cast<UIndex> (vr) < nVertices; ++vr) {
			const Sector *rEdge = reinterpret_cast<const Sector*> (&vertices[vr]);
			UIndex ar = GetInternalArcIdx (vr);
			UIndex nr = source.GetInternalNurbsIdx (vr);
			if (
				fabs (pEdge->c1.x - rEdge->c1.x) < EPS && fabs (pEdge->c1.y - rEdge->c1.y) < EPS &&
				fabs (pEdge->c2.x - rEdge->c2.x) < EPS && fabs (pEdge->c2.y - rEdge->c2.y) < EPS &&
				((ap > 0 && ar > 0 && fabs (source.arcs[ap].arcAngle - arcs[ar].arcAngle) < EPS) || (ap <= 0 && ar <= 0)) &&
				((np != MaxUInt32 && nr != MaxUInt32 && np == nr) || (np == MaxUInt32 && nr == MaxUInt32))
				) {
					found = true;
					break;
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

	return (differences == 0);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Compare( const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& source ) const
{
	if (nVertices != source.nVertices)
		return false;
	if (nArcs != source.nArcs)
		return false;
	if (inhPolygonInfo.GetSize() != (source.inhPolygonInfo).GetSize() || vertexInfos.GetSize() != (source.vertexInfos).GetSize() ||
		inhEdgeInfos.GetSize() != (source.inhEdgeInfos).GetSize())
		return false;
	if (flags.isSameDirEdgeLegal != source.flags.isSameDirEdgeLegal)
		return false;
	if (flags.isClosed != source.flags.isClosed)
		return false;
	if (flags.isSameCoord != source.flags.isSameCoord)
		return false;
	if (flags.isVertexUserData != source.flags.isVertexUserData)
		return false;
	if (flags.isEdgeUserData != source.flags.isEdgeUserData)
		return false;
	if (flags.isPolygonUserData != source.flags.isPolygonUserData)
		return false;

	if ((inhPolygonInfo.GetSize() == 0) != ((source.inhPolygonInfo).GetSize() == 0))
		return false;
	if (flags.isPolygonUserData)
		if (inhPolygonInfo[0] != (source.inhPolygonInfo)[0])
			return false;

	return CompareGeometry (source);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ConvertFromCorePolyline2D (CorePolyline2D<VertexUserData1, EdgeUserData1, PolygonUserData1> & polyline, const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> & source)
{
	polyline.Clear ();
	polyline.CopyInternalDataFromWithoutUserData (source, 0, 0, 0);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Convert( CustomPolyContourDescription<VertexUserData, EdgeUserData, PolygonUserData>& contourDesc ) const
{
	contourDesc.Clear ();

	UIndex vertexIdx;
	if (inhPolygonInfo.GetSize() != 0 && flags.isPolygonUserData)
		contourDesc.SetPolyContourUserData (inhPolygonInfo[0]);

	for(vertexIdx = 1; vertexIdx <= GetVertexNum (); vertexIdx++)
	{
		CustomPolySegment<VertexUserData, EdgeUserData> segment;

		segment.GetVertexRef ().SetCoord (vertices[vertexIdx]);
		if (nArcs != 0 && arcs.GetSize () > 1) {
			for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
				if (arcs[arcIdx].begIndex == vertexIdx)
					segment.GetEdgeRef ().SetArcAngle (arcs[arcIdx].arcAngle);
			}
		}
		if (nNurbs != 0 && nurbs.GetSize () > 1) {
			for (UIndex nurbsIdx = 0; nurbsIdx < nNurbs; nurbsIdx++) {
				if (nurbs[nurbsIdx].begIndex == vertexIdx)
					segment.GetNurbsRef () = nurbs[nurbsIdx].nurbs;
			}
		}
		if (vertexIdx == GetVertexNum () && !GetClosed ())
			segment.GetEdgeRef ().SetArcAngle (PolyEdge::GetInvalidAngle());
		if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
			segment.GetVertexRef ().SetPolyVertexUserData ((vertexInfos)[vertexIdx]);
		if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
			segment.GetEdgeRef ().SetPolyEdgeUserData ((inhEdgeInfos)[vertexIdx]);
		contourDesc.GetSegmentListRef ().Push(segment);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyPolylineData (Point2D* destCoords, USize& coordNum, PolyArcRec* destArcs, USize& arcNum, GS::Array<NurbsCurve2D>& destNurbs, GS::UInt32 createFlags) const
{
	DBASSERT (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));

	if (IsEmpty ()) {
		coordNum = 0;
		arcNum = 0;
		return;
	}
	bool errorOccured = false;

	if (CopyPolylineDataVertices (destCoords, coordNum, createFlags) != true)
		errorOccured = true;
	if (CopyPolylineDataArcs (destArcs, arcNum, createFlags) != true)
		errorOccured = true;
	if (CopyPolylineDataNurbs (destNurbs) != true)
		errorOccured = true;

	if (errorOccured)
		throw GS::OutOfMemoryException ("Error in CorePolyline2D::CopyPolylineData!!!", __FILE__, __LINE__);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CopyPolylineData (GS::Array<Point2D>& destCoordList, GS::Array<PolyArcRec>& destArcList, GS::Array<NurbsCurve2D>& destNurbsList, GS::UInt32 createFlags) const
{
	DBASSERT (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) || ((PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)));

	if (IsEmpty ())
		return;

	destCoordList.Clear ();
	destArcList.Clear ();
	destNurbsList.Clear ();
	//vertices
	USize numOfCoords = nVertices;
	if (GetClosed () && !(PolyCreateFlags_1stCoordDuplAtContourEnd & createFlags)) //do not duplicate first coord at contour end
		numOfCoords--;
	for (UIndex vertIdx = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 0 : 1; vertIdx <= numOfCoords; vertIdx++)
		destCoordList.Push (vertices[vertIdx]);

	//arcs
	for (UIndex arcIdx = (PolyCreateFlags_DummyArcAtIdxZero & createFlags) ? 0 : 1; arcIdx <= nArcs; arcIdx++)
		destArcList.Push (arcs[arcIdx]);
		
	//nurbs
	for (UIndex iNurbs = 0; iNurbs < nNurbs; iNurbs++) 
		destNurbsList.Push (nurbs[iNurbs].nurbs);

	if (!(PolyCreateFlags_DummyCoordAtIdxZero & createFlags) && (PolyCreateFlags_IdxRefInArcFromZero & createFlags)) {
		//first meaningful coord should be at index 0
		UIndex arcOffset = 0;
		if (PolyCreateFlags_DummyArcAtIdxZero & createFlags) //start with blank PolyArc
			arcOffset++;

		for (UIndex arcIdx = arcOffset; arcIdx < nArcs + arcOffset; arcIdx++) {
			destArcList[arcIdx].begIndex--;
			destArcList[arcIdx].endIndex = destArcList[arcIdx].begIndex + 1;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ResetUserData (void)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	if (flags.isPolygonUserData) {
		inhPolygonInfo.Fill (PolygonUserData (), 0, inhPolygonInfo.GetSize ());
	}
	if (flags.isEdgeUserData) {
		defaultEdgeData = EdgeUserData ();
		inhEdgeInfos.Fill (defaultEdgeData, 0, inhEdgeInfos.GetSize ());
	}
	if (flags.isVertexUserData) {
		defaultVertexData = VertexUserData ();
		vertexInfos.Fill (defaultVertexData, 0, vertexInfos.GetSize ());
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetUserData(const PolygonUserData* userData)
{
	if (inhPolygonInfo.GetSize() == 0 || !flags.isPolygonUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolyline2D::SetUserData", __FILE__, __LINE__);
	}
	DBCHECKPOLY_ONEREFTOTHIS;

	inhPolygonInfo[0] = *userData;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const PolygonUserData* CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetUserData (void) const
{
	if (inhPolygonInfo.GetSize() == 0 || !flags.isPolygonUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolyline2D::GetUserData", __FILE__, __LINE__);
	}
	return (&(inhPolygonInfo[0]));
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetSameDirEdgeLegal (bool isSameDirEdgeLegal)
{
	if (flags.isSameDirEdgeLegal != isSameDirEdgeLegal && !isSameDirEdgeLegal) {
		DBCHECKPOLY_ONEREFTOTHIS;
		flags.isSameDirEdgeLegal = isSameDirEdgeLegal;
		Regularize ();
		return;
	}

	flags.isSameDirEdgeLegal = isSameDirEdgeLegal;
}

//bool GetSameDirEdgeLegal (void) const { return flags.isSameDirEdgeLegal; }

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetIsVertexUserData	(bool actIsUserData)
{
	if (flags.isVertexUserData == actIsUserData)
		return;
	DBCHECKPOLY_ONEREFTOTHIS;
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
		vertexInfos.Clear ();
	}
}

//bool CorePolyline2D::GetIsVertexUserData	() const { return flags.isVertexUserData; }

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetIsEdgeUserData		(bool actIsUserData)
{
	if (flags.isEdgeUserData == actIsUserData)
		return;
	DBCHECKPOLY_ONEREFTOTHIS;
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
		inhEdgeInfos.Clear ();
	}
}

//bool CorePolyline2D::GetIsEdgeUserData		() const { return flags.isEdgeUserData; }

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetIsPolygonUserData	(bool actIsUserData)
{
	if (flags.isPolygonUserData == actIsUserData)
		return;
	DBCHECKPOLY_ONEREFTOTHIS;
	flags.isPolygonUserData = actIsUserData;
	if (flags.isPolygonUserData) {
		if (inhPolygonInfo.GetSize() == 0) {
			inhPolygonInfo.SetSize (1);
		}
		inhPolygonInfo [0] = PolygonUserData ();
	} else {
		inhPolygonInfo.Clear ();
	}
}

//bool CorePolyline2D::GetIsPolygonUserData	() const { return flags.isPolygonUserData; }


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetClosed( bool closed )
{
	DBCHECKPOLY_ONEREFTOTHIS;

	if (closed == GetClosed ())
		return;
	if (nVertices == 0){
		if (closed) {
			flags.isClosed = true;
		} else {
			flags.isClosed = false;
		}
		return;
	}
	if (closed) {
		flags.isClosed = true;
		if (IsFirstLastCoordEqual ()) {
			vertices[nVertices] = vertices[1];
			if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
				vertexInfos [nVertices] = vertexInfos [1];
			}
			if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
				inhEdgeInfos [nVertices] = inhEdgeInfos [1];
			}
		} else {
			if (nVertices > 1) {
				vertices.Push (vertices[1]);
				if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
					vertexInfos.SetSize (nVertices + 2);
					vertexInfos [nVertices + 1] = vertexInfos [1];
				}

				if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
					inhEdgeInfos.SetSize (nVertices + 2);
					inhEdgeInfos [nVertices] = defaultEdgeData;
					inhEdgeInfos [nVertices + 1] = inhEdgeInfos [1];
				}
				nVertices += 1;
			}
		}
		Regularize ();
	} else {
		flags.isClosed = false;
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DetectAndSetClosed (void)
{
	if (GetClosed ())
		return;

	DBCHECKPOLY_ONEREFTOTHIS;

	if (nVertices < 1)
		return;
	if (IsFirstLastCoordEqual ()) {
		vertices[nVertices] = vertices[1];
		if (vertexInfos.GetSize () != 0 && flags.isVertexUserData)
			vertexInfos [nVertices] = vertexInfos [1];
		if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData)
			inhEdgeInfos [nVertices] = inhEdgeInfos [1];
		flags.isClosed = true;
		Regularize ();
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetIsSameCoord		(bool isSameCoord)
{
	if (flags.isSameCoord == isSameCoord)
		return;

	DBCHECKPOLY_ONEREFTOTHIS;

	flags.isSameCoord = isSameCoord;
	if (!flags.isSameCoord)
		Regularize ();
}

//bool CorePolyline2D::GetIsSameCoord		() const { return flags.isSameCoord; }

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetVertexDefaultUserData (const VertexUserData& userData)
{
	defaultVertexData = userData;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const VertexUserData& CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetVertexDefaultUserData (void) const
{
	return (defaultVertexData);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
USize CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetVertexNum( void ) const
{
	if (nVertices <= 0)
		return 0;
	if (GetClosed ())
		return nVertices - 1;
	else
		return nVertices;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetVertexIdx (const Point2D& coord) const
{
	UIndex vertexIdx = 0;
	for (vertexIdx = 1; vertexIdx <= nVertices; vertexIdx++) {
		if (Geometry::IsEqualCoord (coord, vertices[vertexIdx], EPS)) {
			return vertexIdx;
		}
	}
	return GetVertexNum () + 1;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const Point2D& CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetCoord( UIndex vertexIdx ) const
{
	DBCHECKINDEX(vertexIdx, 1, GetVertexNum ());
	return vertices[vertexIdx];
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetCoord( UIndex vertexIdx, const Point2D& newCoord )
{
	DBCHECKPOLY_ONEREFTOTHIS;


	DBCHECKINDEX(vertexIdx, 1, GetVertexNum ());
	vertices[vertexIdx] = newCoord;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const VertexUserData* CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetVertexUserData( UIndex vertexIdx ) const
{
	if (vertexInfos.GetSize() == 0 || !flags.isVertexUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolyline2D::GetVertexUserData", __FILE__, __LINE__);
	}
	DBCHECKINDEX(vertexIdx, 1, GetVertexNum ());
	return &(vertexInfos [vertexIdx]);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetVertexUserData( UIndex vertexIdx, const VertexUserData* userData )
{
	if (vertexInfos.GetSize() == 0 || !flags.isVertexUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolyline2D::GetVertexUserData", __FILE__, __LINE__);
	}
	DBCHECKPOLY_ONEREFTOTHIS;
	DBCHECKINDEX(vertexIdx, 1, GetVertexNum ());
	vertexInfos [vertexIdx] = *userData;
	if (GetClosed () && vertexIdx == 1) {
		vertexInfos [nVertices] = *userData;
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetEdgeDefaultUserData (const EdgeUserData& userData)
{
	defaultEdgeData = userData;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const EdgeUserData& CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetEdgeDefaultUserData (void) const
{
	return (defaultEdgeData);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetArcAngle( UIndex edgeIdx ) const
{
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());
	if (nArcs == 0)
		return 0.0;
	for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
		if (arcs[arcIdx].begIndex == edgeIdx)
			return arcs[arcIdx].arcAngle;
	}
	return 0.0;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetEdgeLength( UIndex edgeIdx ) const
{
	DBCHECKPOLY_NONURBS;
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());
	UIndex arcInd = GetInternalArcIdx (edgeIdx);
	if (arcInd > 0) {
		Point2D origo;
		if (ArcGetOrigo (&vertices[edgeIdx], &vertices[edgeIdx + 1], arcs[arcInd].arcAngle, &origo))
			return fabs (arcs[arcInd].arcAngle * Dist (origo, vertices[edgeIdx]));
	}

	return Dist (vertices[edgeIdx], vertices[edgeIdx + 1]);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
NurbsCurve2D CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetNurbs( UIndex edgeIdx ) const
{
	DBCHECKINDEX(edgeIdx, 0, GetEdgeNum ());
	
	UIndex index = GetInternalNurbsIdx (edgeIdx);

	if (index == MaxUInt32)
		return NurbsCurve2D ();

	return nurbs[index].nurbs;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetSector (UIndex edgeIdx, Sector& sect, GenArc& genArc) const
{
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());

	sect.c1 = vertices[GetBeginVertexIdxOfEdge (edgeIdx)];
	sect.c2 = vertices[GetEndVertexIdxOfEdge (edgeIdx)];

	if (nArcs == 0) {
		genArc = GenArc ();	// safety
		return false;
	}

	DBASSERT_STR (GetInternalNurbsIdx (edgeIdx) == MaxUInt32, "Sector wanted, NURBS found");
	double angle = GetArcAngle (edgeIdx);

	if (fabs (angle) <= RadEps) {
		genArc = GenArc ();	// safety
		return false;
	} else {
		Geometry::SetGenArcPtr (&genArc, sect.c1, sect.c2, angle);
		return true;
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetSector (UIndex edgeIdx, Point2D& begC, Point2D& endC, double& angle) const
{
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());

	begC = vertices[GetBeginVertexIdxOfEdge (edgeIdx)];
	endC = vertices[GetEndVertexIdxOfEdge (edgeIdx)];

	if (nArcs == 0) {
		angle = 0;		// safety
		return false;
	}

	DBASSERT_STR (GetInternalNurbsIdx (edgeIdx) == MaxUInt32, "Sector wanted, NURBS found");
	angle = GetArcAngle (edgeIdx);

	if (fabs (angle) <= RadEps) {
		return false;
	} else {
		return true;
	}
}



template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::Optional<Sector>	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetSector (UIndex edgeIdx) const
{
	Sector sector;
	GenArc arc;
	if (GetSector (edgeIdx, sector, arc))
		return GS::NoValue;

	return sector;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::Optional<GenArc>	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetArc (UIndex edgeIdx) const
{
	Sector sector;
	GenArc arc;
	if (!GetSector (edgeIdx, sector, arc))
		return GS::NoValue;

	return arc;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const EdgeUserData* CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetEdgeUserData( UIndex edgeIdx ) const
{
	if (inhEdgeInfos.GetSize() == 0 || !flags.isEdgeUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolyline2D::GetEdgeUserData", __FILE__, __LINE__);
	}
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());
	return &(inhEdgeInfos [edgeIdx]);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetEdgeUserData( UIndex edgeIdx, const EdgeUserData* userData )
{
	if (inhEdgeInfos.GetSize() == 0 || !flags.isEdgeUserData) {
		ThrowGeometryExceptionAtError (ErrParam, "CorePolyline2D::SetEdgeUserData", __FILE__, __LINE__);
	}
	DBCHECKPOLY_ONEREFTOTHIS;
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());
	inhEdgeInfos [edgeIdx] = *userData;

	if (GetClosed () && edgeIdx == 1) {
		inhEdgeInfos [nVertices] = *userData;
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetNextVertexIndex( UIndex vertexIdx, const VertexUserData* ud ) const
{
	DBCHECKINDEX(vertexIdx, 0, GetVertexNum ());
	vertexIdx++;
	while (vertexIdx <= GetVertexNum()) {
		if (*(GetVertexUserData (vertexIdx)) == *ud)
			return vertexIdx;
		vertexIdx++;
	}
	return vertexIdx;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetPrevVertexIndex (UIndex vertexIdx, const VertexUserData* ud) const
{
	//Itt vegig external vertex idx-et hasznalunk
	DBCHECKINDEX(vertexIdx, 1, GetVertexNum () + 1);
	vertexIdx--;
	while (vertexIdx > 0) {
		if (*(GetVertexUserData (vertexIdx)) == *ud)
			return vertexIdx;
		vertexIdx--;
	}
	return vertexIdx;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetNextEdgeIndex( UIndex edgeIdx, const EdgeUserData* ud ) const
{
	DBCHECKINDEX(edgeIdx, 0, GetEdgeNum ());
	edgeIdx++;
	while (edgeIdx <= GetEdgeNum()) {
		if (*(GetEdgeUserData (edgeIdx)) == *ud)
			return edgeIdx;
		edgeIdx++;
	}
	return edgeIdx;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetPrevEdgeIndex (UIndex edgeIdx, const EdgeUserData* ud) const
{
	//Itt vegig external vertex idx-et hasznalunk
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum () + 1);
	edgeIdx--;
	while (edgeIdx > 0) {
		if (*(GetEdgeUserData (edgeIdx)) == *ud)
			return edgeIdx;
		edgeIdx--;
	}
	return edgeIdx;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetBeginVertexIdxOfEdge( UIndex edgeIdx ) const
{
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());
	return edgeIdx;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetEndVertexIdxOfEdge( UIndex edgeIdx ) const
{
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());
	if (GetClosed () && GetEdgeNum () == edgeIdx)
		return 1;
	return edgeIdx + 1;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetPrevEdgeIdxOfVertex( UIndex vertexIdx ) const
{
	DBCHECKINDEX(vertexIdx, 1, GetVertexNum ());
	if (vertexIdx > 1)
		return vertexIdx - 1;
	if (GetClosed ())
		return nVertices - 1;
	else
		return GetEdgeNum () + 1;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
UIndex CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetNextEdgeIdxOfVertex( UIndex vertexIdx ) const
{
	DBCHECKINDEX(vertexIdx, 1, GetVertexNum ());
	return vertexIdx;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Clear (void)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	FreeInternalData ();
	InitInternalData ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::IsABox (void) const
{
	if (nArcs > 0 || nNurbs > 0 ||  nVertices != 5 || !(GetClosed () || IsEqualCoord (vertices[1], vertices[5], EPS)))
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

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::RemoveSmallArcs(void)
{
	Point2D dummyOrigin;
	for (Int32 arcIdx = nArcs; arcIdx > 0; --arcIdx) {
		if (fabs (arcs[arcIdx].arcAngle) < RadEps || !ArcGetOrigo (&vertices[arcs[arcIdx].begIndex], &vertices[arcs[arcIdx].endIndex], arcs[arcIdx].arcAngle, &dummyOrigin)) {
			arcs.Delete (arcIdx);
			--nArcs;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Read( GS::IChannel& ic )
{
	DBCHECKPOLY_ONEREFTOTHIS;

	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, CorePolyline2DPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	GSErrCode err = NoError;
	switch (frame.GetMainVersion ()) {
	case 1:			err = ReadVersion1 (ic, frame); break;
	case 2:			err = ReadVersion2 (ic, frame); break;
	case 3:			err = ReadVersion3 (ic, frame); break;
	default:
		DBPRINTF ("Unsupported CorePolyline2D class version.");
		err = Error;
		break;
	}

	RemoveSmallArcs ();

	DBASSERT_GUID (Check (PolyCheckFlags_All_Polyline, nullptr, MaxCoordValue ()), "{363201BE-0BD4-4B34-AD83-80475E482142}");

	return err;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReadVersion1( GS::IChannel& ic, const GS::InputFrame& /*frame*/ )
{
	DBCHECKPOLY_ONEREFTOTHIS;

	NULL_REF_CHECK (ic);

	Clear ();

	GSErrCode errorCode = NoError;
	try {
		USize			verticesNum = 0;
		USize			arcsNum = 0;
		USize			newUserDataSize = 0;
		if (errorCode == NoError)
			errorCode = ic.Read (newUserDataSize);

		if (DBERROR (newUserDataSize != 0 && newUserDataSize != sizeof (PolyId)))
			throw GeometryException ();
		if (errorCode == NoError)
			errorCode = ic.ReadBin (reinterpret_cast<char*> (&flags), sizeof (flags));
		if (errorCode == NoError)
			errorCode = ic.Read (boundBox);
		if (errorCode == NoError)
			errorCode = ic.Read (verticesNum);
		if (errorCode == NoError)
			errorCode = ic.Read (arcsNum);

		if (verticesNum != 0 || arcsNum != 0) {
			AllocateInternalData (verticesNum, arcsNum, 0);

			if (nVertices != 0 && errorCode == NoError) {
				errorCode = ic.ReadBin (reinterpret_cast<char*> (vertices.GetContent ()), (nVertices + 1) * sizeof (Point2D));
			}

			if (nArcs != 0 && errorCode == NoError) {
				errorCode = ic.ReadBin (reinterpret_cast<char*> (arcs.GetContent ()), (nArcs + 1) * sizeof (PolyArcRec));
			}

			if (newUserDataSize != 0) {
				if (errorCode == NoError)
					errorCode = ReadVersion1UserData (ic);
			}
		} else {
			Clear ();
		}

	} catch (const GS::GSException& e) {
		FreeInternalData ();
		return e.GetErrCode ();
	}

	return ic.GetInputStatus ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReadVersion1UserData (GS::IChannel& ic)
{
	GSErrCode errorCode = NoError;
	if (nVertices != 0 && flags.isVertexUserData && errorCode == NoError) {
		errorCode = ic.ReadBin (reinterpret_cast<char*> (vertexInfos.GetContent ()), (nVertices + 1) * sizeof (PolyId));
	}
	if (nVertices != 0 && flags.isEdgeUserData && errorCode == NoError) {
		errorCode = ic.ReadBin (reinterpret_cast<char*> (inhEdgeInfos.GetContent ()), (nVertices + 1) * sizeof (PolyId));
	}
	if (flags.isPolygonUserData && errorCode == NoError) {
		errorCode = ic.ReadBin (reinterpret_cast<char*> (inhPolygonInfo.GetContent ()), 1 * sizeof (PolyId));
	}
	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReadVersion2( GS::IChannel& ic, const GS::InputFrame& frame )
{
	DBCHECKPOLY_ONEREFTOTHIS;

	NULL_REF_CHECK (ic);

	GSErrCode errorCode = NoError;
	try {
		USize			verticesNum = 0;
		USize			arcsNum = 0;

		if (errorCode == NoError)
			errorCode = ic.ReadBin (reinterpret_cast<char*> (&flags), sizeof (flags));
		if (errorCode == NoError)
			errorCode = ic.Read (boundBox);
		if (errorCode == NoError)
			errorCode = ic.Read (verticesNum);
		if (errorCode == NoError)
			errorCode = ic.Read (arcsNum);

		if (verticesNum != 0 || arcsNum != 0) {
			AllocateInternalData (verticesNum, arcsNum, 0);

			if (nVertices != 0 && errorCode == NoError) {
				errorCode = ic.ReadBin (reinterpret_cast<char*> (vertices.GetContent ()), (nVertices + 1) * sizeof (Point2D));
			}

			if (nArcs != 0 && errorCode == NoError) {
				errorCode = ic.ReadBin (reinterpret_cast<char*> (arcs.GetContent ()), (nArcs + 1) * sizeof (PolyArcRec));
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
		}

	} catch (const GS::GSException& e) {
		FreeInternalData ();
		return e.GetErrCode ();
	}

	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReadVersion2UserData (GS::IChannel& ic)
{
	GSErrCode errorCode = NoError;
	if (nVertices != 0 && flags.isVertexUserData && errorCode == NoError) {
		errorCode = vertexInfos.Read (ic);
	}
	if (nVertices != 0 && flags.isEdgeUserData && errorCode == NoError) {
		errorCode = inhEdgeInfos.Read (ic);
	}
	if (nVertices != 0 && flags.isPolygonUserData && errorCode == NoError) {
		errorCode = inhPolygonInfo.Read (ic);
	}
	return errorCode;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReadVersion3( GS::IChannel& ic, const GS::InputFrame& /*frame*/ )
{
	DBCHECKPOLY_ONEREFTOTHIS;

	NULL_REF_CHECK (ic);

	GSErrCode errorCode = NoError;
	try {
		USize			verticesNum = 0;
		USize			arcsNum = 0;
		USize			nurbsNum = 0;

		if (errorCode == NoError)
			errorCode = ic.ReadBin (reinterpret_cast<char*> (&flags), sizeof (flags));
		if (errorCode == NoError)
			errorCode = ic.Read (boundBox);
		if (errorCode == NoError)
			errorCode = ic.Read (verticesNum);
		if (errorCode == NoError)
			errorCode = ic.Read (arcsNum);	
		if (errorCode == NoError)
			errorCode = ic.Read (nurbsNum);

		if (verticesNum != 0 || arcsNum != 0 || nurbsNum != 0) {
			AllocateInternalData (verticesNum, arcsNum, nurbsNum);

			if (nVertices != 0 && errorCode == NoError) {
				errorCode = ic.ReadBin (reinterpret_cast<char*> (vertices.GetContent ()), (nVertices + 1) * sizeof (Point2D));
			}

			if (nArcs != 0 && errorCode == NoError) {
				errorCode = ic.ReadBin (reinterpret_cast<char*> (arcs.GetContent ()), (nArcs + 1) * sizeof (PolyArcRec));
			}

			nurbs.SetSize (nurbsNum);
			for (UInt32 i = 0; i < nurbsNum; i++) {
				ic.Read (nurbs[i].begIndex);
				nurbs[i].nurbs.Read (ic);
			}

			if (errorCode == NoError)
				errorCode = ReadVersion2UserData (ic);
		} else {
			Clear ();
		}

		if (errorCode == NoError)
			errorCode = defaultVertexData.Read (ic);
		if (errorCode == NoError)
			errorCode = defaultEdgeData.Read (ic);

	} catch (const GS::GSException& e) {
		FreeInternalData ();
		return e.GetErrCode ();
	}

	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Write( GS::OChannel& oc ) const
{
	NULL_REF_CHECK (oc);
	DBCHECKPOLY_CHECK;

	GS::OutputFrame frame (oc, CorePolyline2DPrivate::classInfo);

	GSErrCode err = NoError;
	switch (frame.GetMainVersion ()) {
	case 1:			err = WriteVersion1 (oc, frame); break;
	case 2:			err = WriteVersion2 (oc, frame); break;
	case 3:			err = WriteVersion3 (oc, frame); break;
	default:
		DBPRINTF ("Unsupported CorePolyline2D class version.");
		err = Error;
		break;
	}

	return err;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::WriteVersion1( GS::OChannel& oc, const GS::OutputFrame& /*frame*/ ) const
{
	NULL_REF_CHECK (oc);
	DBCHECKPOLY_CHECK;

#pragma warning (disable : 4127)		// conditional expression is constant
	if (DBERROR (sizeof (VertexUserData) != sizeof (PolyId) || sizeof (EdgeUserData) != sizeof (PolyId) || sizeof (PolygonUserData) != sizeof (PolyId)))
		return Error;
#pragma warning (default : 4127)

	GSErrCode errorCode = NoError;
	USize userDataSize = sizeof (PolyId);
	if (errorCode == NoError)
		errorCode = oc.Write (userDataSize);
	if (errorCode == NoError)
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (&flags), sizeof (flags));
	if (errorCode == NoError)
		errorCode = oc.Write (boundBox);
	if (errorCode == NoError)
		errorCode = oc.Write (nVertices);
	if (errorCode == NoError)
		errorCode = oc.Write (nArcs);

	if (nVertices != 0 || nArcs != 0) {
		if (nVertices != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (vertices.GetContent ()), (nVertices + 1) * sizeof (Point2D));
		}

		if (nArcs != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (arcs.GetContent ()), (nArcs + 1) * sizeof (PolyArcRec));
		}

		if (errorCode == NoError)
			errorCode = WriteVersion1UserData (oc);
	}
	return oc.GetOutputStatus ();
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::WriteVersion1UserData (GS::OChannel& oc) const
{
	GSErrCode errorCode = NoError;
	if (vertexInfos.GetSize() != 0 && flags.isVertexUserData && nVertices != 0 && errorCode == NoError) {
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (vertexInfos.GetContent ()), (nVertices + 1) * sizeof (PolyId));
	}

	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData && nVertices != 0 && errorCode == NoError) {
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (inhEdgeInfos.GetContent ()), (nVertices + 1) * sizeof (PolyId));
	}
	if (inhPolygonInfo.GetSize() != 0 && flags.isPolygonUserData && errorCode == NoError) {
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (inhPolygonInfo.GetContent ()), 1 * sizeof (PolyId));
	}
	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::WriteVersion2( GS::OChannel& oc, const GS::OutputFrame& frame ) const
{
	NULL_REF_CHECK (oc);
	DBCHECKPOLY_CHECK;

	GSErrCode errorCode = NoError;
	if (errorCode == NoError)
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (&flags), sizeof (flags));
	if (errorCode == NoError)
		errorCode = oc.Write (boundBox);
	if (errorCode == NoError)
		errorCode = oc.Write (nVertices);
	if (errorCode == NoError)
		errorCode = oc.Write (nArcs);

	if (nVertices != 0 || nArcs != 0) {
		if (nVertices != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (vertices.GetContent ()), (nVertices + 1) * sizeof (Point2D));
		}

		if (nArcs != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (arcs.GetContent ()), (nArcs + 1) * sizeof (PolyArcRec));
		}

		if (errorCode == NoError)
			errorCode = WriteVersion2UserData (oc);
	}

	if (frame.GetSubVersion () > 0) {
		if (errorCode == NoError)
			errorCode = defaultVertexData.Write (oc);
		if (errorCode == NoError)
			errorCode = defaultEdgeData.Write (oc);
	}

	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::WriteVersion2UserData (GS::OChannel& oc) const
{
	GSErrCode errorCode = NoError;
	if (vertexInfos.GetSize() != 0 && flags.isVertexUserData && nVertices != 0 && errorCode == NoError) {
		errorCode = vertexInfos.Write (oc);
	}

	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData && nVertices != 0 && errorCode == NoError) {
		errorCode = inhEdgeInfos.Write (oc);
	}

	if (inhPolygonInfo.GetSize() != 0 && flags.isPolygonUserData && nVertices != 0 && errorCode == NoError) {
		errorCode = inhPolygonInfo.Write (oc);
	}
	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::WriteVersion3( GS::OChannel& oc, const GS::OutputFrame& /*frame*/ ) const
{
	NULL_REF_CHECK (oc);
	DBCHECKPOLY_CHECK;

	GSErrCode errorCode = NoError;
	if (errorCode == NoError)
		errorCode = oc.WriteBin (reinterpret_cast<const char*> (&flags), sizeof (flags));
	if (errorCode == NoError)
		errorCode = oc.Write (boundBox);
	if (errorCode == NoError)
		errorCode = oc.Write (nVertices);
	if (errorCode == NoError)
		errorCode = oc.Write (nArcs);	
	if (errorCode == NoError)
		errorCode = oc.Write (nNurbs);

	if (nVertices != 0 || nArcs != 0) {
		if (nVertices != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (vertices.GetContent ()), (nVertices + 1) * sizeof (Point2D));
		}

		if (nArcs != 0 && errorCode == NoError) {
			errorCode = oc.WriteBin (reinterpret_cast<const char*> (arcs.GetContent ()), (nArcs + 1) * sizeof (PolyArcRec));
		}

		for (UInt32 i = 0; i < nNurbs; i++) {
			oc.Write (nurbs[i].begIndex);
			nurbs[i].nurbs.Write (oc);
		}

		if (errorCode == NoError)
			errorCode = WriteVersion2UserData (oc);
	}

	if (errorCode == NoError)
		errorCode = defaultVertexData.Write (oc);
	if (errorCode == NoError)
		errorCode = defaultEdgeData.Write (oc);

	return errorCode;
}

extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_CorePolyline2D;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Attr_SegmentsNum;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_IsSameDirEdgeLegal;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_Closed;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_IsSameCoord;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_IsVertexUserData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_IsEdgeUserData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_IsPolygonUserData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_DefaultData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Attr_xMin;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Attr_yMin;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Attr_xMax;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Attr_yMax;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Attr_UserDataSize;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_Segments;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_Segment;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_Vertex;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_CoordX;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_CoordY;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_Edge;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_ArcAngle;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_PolyId;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_DefaultVertexData;
extern GEOMETRY_DLL_EXPORT const char*		XMLCore_Pl_Tag_DefaultEdgeData;

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReadXMLCreateContourDesc (GS::XMLIChannel& ic, GS::XMLITag& tagSegments, Flags actFlags, CustomPolyContourDescription<VertexUserData, EdgeUserData, PolygonUserData>& polyContourDesc, bool& isEdgeTag)
{
	GSErrCode errCode = NoError;
	Point2D coord (0.0, 0.0);
	double arcAngle = 0.0;
	CustomPolySegment<VertexUserData, EdgeUserData> polySegment;

	GS::UniString tokenName;
	while (tagSegments.IsNextChildStartTag (tokenName) && (errCode == NoError)) {
		NurbsCurve2D nurbs;

		//Begin Segment
		GS::XMLITag tagSegment (ic, XMLCore_Pl_Tag_Segment);
		{ //Begin Vertex
			GS::XMLITag tagVertex (ic, XMLCore_Pl_Tag_Vertex);
			if (errCode == NoError)
				errCode = ic.ReadXML (XMLCore_Pl_Tag_CoordX, coord.x);
			if (errCode == NoError)
				errCode = ic.ReadXML (XMLCore_Pl_Tag_CoordY, coord.y);
			if (actFlags.isVertexUserData) {
				if (errCode == NoError) {
					VertexUserData tmpPolyId;
					errCode = GS::ReadXML (ic, XMLCore_Pl_Tag_PolyId ,tmpPolyId);
					polySegment.GetVertexRef ().SetPolyVertexUserData (tmpPolyId);
				}
			}
		} //End Vertex
		{ //Begin Edge
			if (tagSegment.IsNextChildStartTag (tokenName) && (errCode == NoError)) {
				GS::XMLITag tagEdge (ic, XMLCore_Pl_Tag_Edge);
				if (errCode == NoError)
					errCode = ic.ReadXML (XMLCore_Pl_Tag_ArcAngle, arcAngle);

				if (actFlags.isEdgeUserData) {
					if (errCode == NoError) {
						EdgeUserData tmpPolyId;
						errCode = GS::ReadXML (ic, XMLCore_Pl_Tag_PolyId ,tmpPolyId);
						polySegment.GetEdgeRef ().SetPolyEdgeUserData (tmpPolyId);
					}
				}
				isEdgeTag = true;
			} else {
				isEdgeTag = false;
			}
		} //End Edge
		{ //Begin Nurbs
			if (tagSegment.IsNextChildStartTag (tokenName) && tokenName == "NurbsCurve2D" && (errCode == NoError)) {
				errCode = nurbs.ReadXML (ic);
			}
		} //End Nurbs
		if (errCode == NoError) {
			polySegment.GetVertexRef ().SetCoord (coord);
			polySegment.GetEdgeRef ().SetArcAngle (arcAngle);
			polySegment.GetNurbsRef () = nurbs;

			polyContourDesc.GetSegmentListRef ().Push (polySegment);
		}
		//End Segment
	}
	return errCode;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReadXMLAndCreate (GS::XMLIChannel& ic )
{
	GSErrCode errCode = NoError;
	GS::XMLITag tagCorePolyline2D (ic, XMLCore_Pl_Tag_CorePolyline2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		GS::ClassVersion currentClassVersion;
		ic.ReadXMLVersionAttr (currentClassVersion);
		//currentClassVersion.ReadXML (ic);
		DBASSERT (currentClassVersion == CorePolyline2DPrivate::classInfo.GetVersion ());
	}

	double	xMin = 0.0;
	double	yMin = 0.0;
	double	xMax = 0.0;
	double	yMax = 0.0;
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLCore_Pl_Attr_xMin, xMin);
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLCore_Pl_Attr_yMin, yMin);
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLCore_Pl_Attr_xMax, xMax);
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLCore_Pl_Attr_yMax, yMax);

	CustomPolyContourDescription<VertexUserData, EdgeUserData, PolygonUserData> polyContourDesc;

	Flags	actFlags;
	bool tmpFlag	= true;
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Pl_Tag_IsSameDirEdgeLegal, tmpFlag);
		actFlags.isSameDirEdgeLegal = tmpFlag;
	}
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Pl_Tag_Closed, tmpFlag);
		actFlags.isClosed = tmpFlag;
	}
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Pl_Tag_IsSameCoord, tmpFlag);
		actFlags.isSameCoord = tmpFlag;
	}
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Pl_Tag_IsVertexUserData, tmpFlag);
		actFlags.isVertexUserData = tmpFlag;
	}
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Pl_Tag_IsEdgeUserData, tmpFlag);
		actFlags.isEdgeUserData = tmpFlag;
	}
	if (errCode == NoError) {
		errCode = ic.ReadXML (XMLCore_Pl_Tag_IsPolygonUserData, tmpFlag);
		actFlags.isPolygonUserData = tmpFlag;
	}

	VertexUserData	inputDefaultVertexData;
	EdgeUserData	inputDefaultEdgeData;
	bool			hasDefaultData = false;

	if (errCode == NoError)
		errCode = GS::ReadXML (ic, XMLCore_Pl_Tag_DefaultVertexData, inputDefaultVertexData);
	if (errCode == NoError) 
		errCode = GS::ReadXML (ic, XMLCore_Pl_Tag_DefaultEdgeData, inputDefaultEdgeData);
	hasDefaultData = errCode == NoError;

	PolygonUserData polyId;
	if (actFlags.isPolygonUserData) {
		if (errCode == NoError) {
			errCode = GS::ReadXML (ic, XMLCore_Pl_Tag_PolyId, polyId);
			polyContourDesc.SetPolyContourUserData (polyId);
		}
	}

	bool isEdgeTag = false;
#if !defined (DEBUVERS)
	UNUSED_VARIABLE (isEdgeTag);
#endif
	if (errCode == NoError) { //Begin Segments
		GS::XMLITag tagSegments (ic, XMLCore_Pl_Tag_Segments);
		GS::UniString name = "";
		ic.GetNextTokenTypeName(name);
		if (name != XMLCore_Pl_Tag_Segment) { //valid ures polyline
			GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > emptyResult = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (actFlags);
			if (emptyResult->flags.isPolygonUserData && errCode == NoError) {
				emptyResult->SetUserData (&polyId);
			}

			if (hasDefaultData) {
				emptyResult->defaultVertexData	= inputDefaultVertexData;
				emptyResult->defaultEdgeData	= inputDefaultEdgeData;
			}

			return emptyResult;
		}

		if (errCode == NoError)
			errCode = ReadXMLCreateContourDesc (ic, tagSegments, actFlags, polyContourDesc, isEdgeTag);
	} //End Segments

	if (!actFlags.isClosed) {
		DBASSERT (!isEdgeTag);
		polyContourDesc.GetSegmentListRef ().GetLast ().GetEdgeRef ().SetArcAngle (PolyEdge::GetInvalidAngle ());
	}

	if (errCode != NoError || ic.GetErrorStatus () != GS::XMLIChannel::Ok)
		return nullptr;

	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>* result = nullptr;
	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (actFlags, polyContourDesc);

	if (hasDefaultData) {
		result->defaultVertexData	= inputDefaultVertexData;
		result->defaultEdgeData		= inputDefaultEdgeData;
	}

	return result;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::WriteXMLContour (GS::XMLOChannel& oc ) const
{
	GSErrCode errCode = NoError;
	//Begin Segments
	GS::XMLTag tag (oc, XMLCore_Pl_Tag_Segments);

	for (UIndex idx = 1; idx <= GetVertexNum (); idx++) {
		//Begin Segment
		GS::XMLTag tag (oc, XMLCore_Pl_Tag_Segment);
		{ //Begin Vertex
			GS::XMLTag tag (oc, XMLCore_Pl_Tag_Vertex);
			if (errCode == NoError)
				errCode = oc.WriteXML (XMLCore_Pl_Tag_CoordX, GetCoord (idx).x);
			if (errCode == NoError)
				errCode = oc.WriteXML (XMLCore_Pl_Tag_CoordY, GetCoord (idx).y);
			if (flags.isVertexUserData) {
				if (errCode == NoError) {
					const VertexUserData* id = GetVertexUserData (idx);
					if (id != nullptr)
						errCode = GS::WriteXML (oc, XMLCore_Pl_Tag_PolyId, *id);
				}
			}
		} //End Vertex
		{ //Begin Edge
			if (GetClosed () || idx != GetVertexNum ()) {
				GS::XMLTag tag (oc, XMLCore_Pl_Tag_Edge);
				if (errCode == NoError)
					errCode = oc.WriteXML (XMLCore_Pl_Tag_ArcAngle, GetArcAngle (idx));

				if (flags.isEdgeUserData) {
					if (errCode == NoError) {
						const EdgeUserData* id = GetEdgeUserData (idx);
						if (id != nullptr)
							errCode = GS::WriteXML (oc, XMLCore_Pl_Tag_PolyId, *id);
					}
				}
			}
		} //End Edge
		{ //Begin Nurbs
			if (GetClosed () || idx != GetVertexNum ()) {
				NurbsCurve2D nurbs = GetNurbs (idx);
				if (!nurbs.IsEmpty ())
					nurbs.WriteXML (oc);
			}
		} //End Nurbs
		//End Segment
	}
	//End Segments
	return errCode;

}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GSErrCode CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::WriteXML( GS::XMLOChannel& oc ) const
{
	GSErrCode errCode = NoError;
	GS::XMLTag tag (oc, XMLCore_Pl_Tag_CorePolyline2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		oc.WriteXMLVersionAttr (CorePolyline2DPrivate::classInfo.GetVersion ());
		//GetClassVersion ().WriteXML (oc);
	}
	Box2DData box = GetBoundBox ();
	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLCore_Pl_Attr_xMin, box.xMin);
	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLCore_Pl_Attr_yMin, box.yMin);
	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLCore_Pl_Attr_xMax, box.xMax);
	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLCore_Pl_Attr_yMax, box.yMax);

	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Pl_Tag_IsSameDirEdgeLegal, GetSameDirEdgeLegal ());
	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Pl_Tag_Closed, GetClosed ());
	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Pl_Tag_IsSameCoord, GetIsSameCoord ());
	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Pl_Tag_IsVertexUserData, GetIsVertexUserData ());
	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Pl_Tag_IsEdgeUserData, GetIsEdgeUserData ());
	if (errCode == NoError)
		errCode = oc.WriteXML (XMLCore_Pl_Tag_IsPolygonUserData, GetIsPolygonUserData ());
	
	if (errCode == NoError) 
		errCode = GS::WriteXML (oc, XMLCore_Pl_Tag_DefaultVertexData, defaultVertexData);
	if (errCode == NoError) 
		errCode = GS::WriteXML (oc, XMLCore_Pl_Tag_DefaultEdgeData, defaultEdgeData);

	if (flags.isPolygonUserData) {
		if (errCode == NoError) {
			const PolygonUserData* id = GetUserData ();
			if (id != nullptr)
				errCode = GS::WriteXML (oc, XMLCore_Pl_Tag_PolyId, *id);
		}
	}

	if (errCode == NoError)
		errCode = WriteXMLContour (oc);

	if (errCode != NoError)
		return errCode;
	return oc.GetErrorStatus () == GS::XMLOChannel::Ok ? NoError : Error;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
const Box2DData& CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetBoundBox(void) const
{
	return boundBox;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CalcArea (bool signedArea) const
{
	DBCHECKPOLY_NONURBS;
	double	area = 0.0;
	UIndex		arcInd;
	GS::Int32	iVertex;
	Point2D		centre;
	Point2D		begEdge, endEdge;
	GS::Int32	iBegContour;
	GS::Int32	iEndContour;

	iBegContour = 1;
	iEndContour = nVertices;
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

	area += (endEdge.x + begEdge.x) * (endEdge.y - begEdge.y) * 0.5;
	if (!signedArea)
		area = fabs (area);
	return area;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::IsClockwise (void) const
{
	return (CalcArea (true) < 0.0);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CalcLength (void) const
{
	DBCHECKPOLY_NONURBS;
	double perimeter = 0.0;

	ULong iBegContour = 1;
	ULong iEndContour = nVertices;

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

	return perimeter;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CalcMaxVertexFillet( UIndex vertexIdx ) const
{
#if defined(DEBUVERS_POLY2D)
	if (GetClosed ()) {
		DBCHECKINDEX(vertexIdx, 1, GetVertexNum ());
	} else {
		DBCHECKINDEX(vertexIdx, 2, GetVertexNum () - 1);
	}
#endif
	double maxFilletRadius;
	GetMaxVertexFillet (vertexIdx, &maxFilletRadius);
	return maxFilletRadius;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::IsCoordOnEdge (const Point2D& c, GS::Array<UIndex>& edgeIndex) const
{
	DBCHECKPOLY_NONURBS;
	edgeIndex.Clear ();
	if (DBERROR (IsEmpty ())) {
		return false;
	}
	for (UIndex iEdge = 1; iEdge <= GetEdgeNum (); ++iEdge) {
		Sector s;
		GenArc a;
		if (GetSector (iEdge, s, a)) {		// arc
			if (ValidGenArcPointEps (&a, &c, Eps))  {
				edgeIndex.Push (iEdge);
			}
		} else {
			if (IsSectorPointIntersect (s, c, Boundary_Closed, Boundary_Closed, Eps)) {
				edgeIndex.Push (iEdge);
			}
		}
	}
	return edgeIndex.GetSize () > 0;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::Array<GS::Pair<UIndex, Vector2D>> CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetTangentAtPoint (const Point2D& c) const
{
	DBCHECKPOLY_NONURBS;
	GS::Array<UIndex> edges;
	if (DBERROR (!IsCoordOnEdge (c, edges)))
		throw GeometryException ("GetTangentAtPoint coord not on polyline", __FILE__, __LINE__);

	GS::Array<GS::Pair<UIndex, Vector2D>> tangents (edges.GetSize ());
	for (auto it = edges.Enumerate (); it != nullptr; ++it) {
		UIndex edgeIndex = *it;

		Vector2D tangent;
		Sector s;
		GenArc arc;
		if (GetSector (edgeIndex, s, arc)) {		// arc
			tangent = UnitVector ((c - arc.GetOrigo ()).GetNormalVector ());
			if (arc.IsReflected ())
				tangent *= -1.0;
		} else {
			tangent = UnitVector (s.c2 - s.c1);
		}
		tangents.Push (GS::Pair<UIndex, Vector2D> (edgeIndex, tangent));
	}
	return tangents;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
Point2D CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetMiddlePoint (void) const
{
	DBCHECKPOLY_NONURBS;
	if (DBERROR (IsEmpty () || GetClosed ()))
		throw GeometryException ("GetMiddlePoint empty or closed polyline", __FILE__, __LINE__);

	double halfLength = CalcLength () / 2.0;
	double actLength = 0.0;
	UIndex halfPointEdge;
	for (halfPointEdge = 1; halfPointEdge < nVertices; ++halfPointEdge) {
		double edgeLength = GetEdgeLength (halfPointEdge);
		if (actLength + edgeLength > halfLength - Eps)
			break;
		else
			actLength += edgeLength;
	}
	double remainder = halfLength - actLength;
	if (fabs (remainder) < Eps)
		return vertices[halfPointEdge];

	Sector s;
	GenArc arc;
	if (GetSector (halfPointEdge, s, arc)) {		// arc
		double arcAngle = remainder / arc.GetMainAxisLength ();
		if (arc.IsReflected ())
			arcAngle *= -1.0;
		return RotCoord (arc.GetOrigo (), arc.GetBegC (), sin (arcAngle), cos (arcAngle));
	} else {
		return s.c1 + UnitVector (s.c2 - s.c1) * remainder;
	}
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::FixArray<Point2D, 4>	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetTransformedBoundBox (const TRANMAT& tr, const TRANMAT& invTr /*= Geometry::IdentitTranMat*/) const
{
	GS::FixArray<Point2D, 4> box;
	ArcDivParams arcDivParams;
	GS::SharedPtr<CorePolyline2D> result;
	PolylineResult polyResult = Transform (arcDivParams, tr, result);
	if (polyResult != ResultSameAsThis && (result->IsEmpty () || polyResult == EmptyPolyline)) {
		BNZeroMemory (box.GetContent (), 4 * sizeof (Point2D));
		return box;
	}
	Box2DData tmpBoundBox;
	if (polyResult == ResultSameAsThis) {
		tmpBoundBox = GetBoundBox ();
	} else {
		tmpBoundBox = result->GetBoundBox ();
	}

	box[0]	= Point2D (tmpBoundBox.xMin, tmpBoundBox.yMin);
	box[1]	= Point2D (tmpBoundBox.xMax, tmpBoundBox.yMin);
	box[2]	= Point2D (tmpBoundBox.xMax, tmpBoundBox.yMax);
	box[3]	= Point2D (tmpBoundBox.xMin, tmpBoundBox.yMax);

	if (!invTr.IsIdentity ()) {
		for (GS::Int32 i = 0; i < 4; i++)
			box[i] = SetCoord2D (TransformPoint (invTr, SetCoord3D(box[i])));
	}

	return box;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DistanceFromPoint (const Point2D& co, UIndex& edgeOfMin, GS::Array<bool>* filter) const
{
	DBCHECKPOLY_NONURBS;
	if (DBERROR (IsEmpty ()))
		throw GeometryException ("DistanceFromPoint empty polyline", __FILE__, __LINE__);

	double	minDist = 1e9, overHangMin = 0;
	UIndex	i = 1;
	UIndex	iMin = 0;
	for (UIndex edgeIndex = 1; edgeIndex < nVertices; ++edgeIndex, ++i) {
		if (filter != nullptr && !(*filter)[i - 1])
			continue;

		Sector	s;
		GenArc arc;
		double	d, overHang;
		bool	csere = false;
		if (!GetSector (edgeIndex, s, arc)) {
			d = SpecDistPointToSector (co, s, &overHang);
		} else {
			d = SpecDistPointToArc (co, arc, &overHang);
		}
		if (d < minDist - Eps) {
			csere = true;
		} else if (d < minDist + Eps) {		// kb. azonos
			csere = overHang < overHangMin;
		}
		if (csere) {
			minDist = d;
			overHangMin = overHang;
			iMin = i;
		}
	}
	
	edgeOfMin = iMin;
	return minDist;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Visit (CorePolyline2DConstVertexVisitor &visitor) const
{
	DBCHECKPOLY_NONURBS;
	UIndex endVertexIdx = nVertices;
	if (GetClosed ())
		endVertexIdx--;

	for (UIndex vIdx = 1; vIdx < endVertexIdx + 1; ++vIdx) {
		visitor (vertices[vIdx]);
	}
}

template<class VertexUserData, class EdgeUserData, class PolygonUserData>
double CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::GetTurningAngleAtVertex (UIndex vertexIdx) const
{
	Curve2DData	prevEdgeCurve;
	Curve2DData	nextEdgeCurve;
	UIndex prevVertexIdx, nextVertexIdx;
	UIndex prevEdgeIdx, nextEdgeIdx;

	if (vertexIdx == 1 && !GetClosed ()) {
		return 0.0;
	} else {
		prevVertexIdx = prevEdgeIdx = (vertexIdx == 1) ? nVertices - 1 : vertexIdx - 1;
	}

	if (vertexIdx == nVertices && !GetClosed ()) {
		return 0.0;
	} else {
		nextVertexIdx = (vertexIdx == nVertices) ? 2 : vertexIdx + 1;
		nextEdgeIdx = (vertexIdx == nVertices) ? 1 : vertexIdx ;
	}

	if (GetEdgeLength (prevEdgeIdx) < Eps || GetEdgeLength (nextEdgeIdx) < Eps) {
		return 0.0;
	}

	prevEdgeCurve.epsilon = prevEdgeCurve.angleEpsilon = Eps;
	GS::Int32 arcIndprev = GetInternalArcIdx (prevEdgeIdx);
	if (arcIndprev > 0) {
		prevEdgeCurve.type = CURVE2D_GenArc;
		prevEdgeCurve.genArc = SetGenArc (vertices[prevVertexIdx], vertices[vertexIdx], arcs[arcIndprev].arcAngle);
	} else {
		prevEdgeCurve.type = CURVE2D_Line;
		prevEdgeCurve.sector.c1 = vertices[prevVertexIdx];
		prevEdgeCurve.sector.c2 = vertices[vertexIdx];
	}

	nextEdgeCurve.epsilon = nextEdgeCurve.angleEpsilon = Eps;
	GS::Int32 arcIndnext = GetInternalArcIdx (nextEdgeIdx);
	if (arcIndnext > 0) {
		nextEdgeCurve.type = CURVE2D_GenArc;
		nextEdgeCurve.genArc = SetGenArc (vertices[vertexIdx], vertices[nextVertexIdx], arcs[arcIndnext].arcAngle);
	} else {
		nextEdgeCurve.type = CURVE2D_Line;
		nextEdgeCurve.sector.c1 = vertices[vertexIdx];
		nextEdgeCurve.sector.c2 = vertices[nextVertexIdx];
	}

	UnitVector_2D prevEdgeEndDir = GetCurve2DDataEndDirection (prevEdgeCurve);
	UnitVector_2D nextEdgeBegDir = GetCurve2DDataBegDirection (nextEdgeCurve);
	double cosin = MulsVectors (prevEdgeEndDir, nextEdgeBegDir);
	double turningAngle = ArcCos (cosin);

	if (IsNegative (prevEdgeEndDir ^ nextEdgeBegDir)) { //right turn
		turningAngle *= -1.0;
	}

	return turningAngle;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::FillSegmentedArc (const ArcDivParams& arcDivParams, GS::Array< GS::Array<Point2D> >& segmentedArcs, USize& numOfSegmentedVertex) const
{
	for (GS::UInt32 node = 1; node < nVertices; node++) {
		Point2D begC = vertices[node];
		Point2D endC = vertices[node + 1];
		UIndex arcInd = GetInternalArcIdx (node);
		if (arcInd > 0) {
			Point2D origC;
			double angle = arcs[arcInd].arcAngle;
			Geometry::ArcGetOrigo (&begC, &endC, angle, &origC);
			GS::Array<Point2D> resultPolyVertices;
			segmentedArcs.Push (resultPolyVertices);
			Geometry::DivideArcToCo (&origC, &begC, angle, arcDivParams, segmentedArcs.GetLast ());
			numOfSegmentedVertex += (segmentedArcs.GetLast ().GetSize () - 2);
		}
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::FillSegmentedNurbs (const ArcDivParams& /*arcDivParams*/, GS::Array< GS::Array<Point2D> >& segmentedNurbs, USize& numOfSegmentedVertex) const
{
	for (GS::UInt32 i = 0; i < nNurbs; i++) {
		UIndex nurbsInd = GetInternalNurbsIdx (i);
		if (nurbsInd != MaxUInt32) {
			GS::Array<Point2D> resultPolyVertices = nurbs[nurbsInd].nurbs.SegmentUp (0.1 /* TODO arcDivParams.maxDifference*/);
			numOfSegmentedVertex += (resultPolyVertices.GetSize ());
			segmentedNurbs.Push (resultPolyVertices);
		}
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetSegmentUp (GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& result, GS::Array< GS::Array<Point2D> >& segmentedArcs, GS::Array< GS::Array<Point2D> >& segmentedNurbs) const
{
	UIndex segmentedArcIdx = 0;
	UIndex segmentedNurbsIdx = 0;
	VertexUserData vertexInfo;
	EdgeUserData   edgeInfo;
	if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
		vertexInfo = vertexInfos [1];
	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
		edgeInfo = inhEdgeInfos [1];
	result->AddOneVertex (vertices[1], &vertexInfo, &edgeInfo);
	for (GS::UInt32 node = 1; node < nVertices; node++) {
		UIndex arcInd = GetInternalArcIdx (node);
		UIndex NurbsInd = GetInternalNurbsIdx (node);

		if (arcInd != 0 && segmentedArcIdx < segmentedArcs.GetSize ()) {
			for (UIndex idx = 1; idx < segmentedArcs[segmentedArcIdx].GetSize () - 1; ++idx) {
				if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
					vertexInfo = defaultVertexData;
				if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
					edgeInfo = inhEdgeInfos [node];
				result->AddOneVertex (segmentedArcs[segmentedArcIdx][idx], &vertexInfo, &edgeInfo);
			}
			segmentedArcIdx++;
		}

		if (NurbsInd != MaxUInt32 && segmentedNurbsIdx < segmentedNurbs.GetSize ()) {
			for (UIndex idx = 1; idx < segmentedNurbs[segmentedNurbsIdx].GetSize () - 1; ++idx) {
				if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
					vertexInfo = defaultVertexData;
				if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
					edgeInfo = inhEdgeInfos [node];
				result->AddOneVertex (segmentedNurbs[segmentedNurbsIdx][idx], &vertexInfo, &edgeInfo);
			}
			segmentedNurbsIdx++;
		}
		if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
			vertexInfo = vertexInfos [(node + 1)];
		if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
			edgeInfo = inhEdgeInfos [(node + 1)];
		result->AddOneVertex (vertices[node + 1], &vertexInfo, &edgeInfo);
	}
	DBASSERT (segmentedArcIdx == segmentedArcs.GetSize () || segmentedNurbsIdx == segmentedNurbs.GetSize ());
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Move( Vector2D offset )
{
	DBCHECKPOLY_ONEREFTOTHIS;

	for (UIndex vertexIdx = 1; vertexIdx <= nVertices; vertexIdx++) {
		vertices[vertexIdx] = vertices[vertexIdx] + offset;
	}

	for (UIndex i = 0; i < nNurbs; i++) {
		nurbs[i].nurbs.Move (offset);
	}
	
	OffsetBox (&boundBox, offset.x, offset.y);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::TransformPreserveArcs( const TRANMAT& tran )
{
	DBCHECKPOLY_ONEREFTOTHIS;

	if (tran.IsIdentity ()) {
		return;
	}
	if (IsEmpty ()) {
		return;
	}

	DBASSERT (nArcs == 0 || Geometry::TMIsPreserveArc (tran));

	for (UIndex vertexIdx = 1; vertexIdx <= nVertices; vertexIdx++) {
		vertices[vertexIdx] = Geometry::Transform2dPoint (tran, vertices[vertexIdx]);
	}

	if (arcs.GetSize () > 1 && (tran.HasMirror ())) {
		for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++)
			arcs[arcIdx].arcAngle *= -1;
	}
		
	for (UIndex i = 0; i < nNurbs; i++) {
		nurbs[nNurbs].nurbs.Transform (tran);
	}

	RemoveSmallArcs ();

	UpdateBoundingBox ();
	DBCHECKPOLY_CHECK;

	//Ezutan mar nincs szukseg regularizalasra, koordinata transzformalas utan nem kell
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ClearVertexUserDatas (void)
{
	if (vertexInfos.GetSize() != 0) {
		ZeroInfo_Data <VertexUserData> (vertexInfos, 0, (nVertices + 1), defaultVertexData);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ClearEdgeUserDatas (void)
{
	if (inhEdgeInfos.GetSize() != 0) {
		ZeroInfo_Data <EdgeUserData> (inhEdgeInfos, 0, (nVertices + 1), defaultEdgeData);
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Reverse (void)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	UIndex sourceIdx;
	UIndex edgeSourceIdx;

	for (UIndex coordIdx = 1; coordIdx <= nVertices; coordIdx++) {
		sourceIdx = nVertices - coordIdx + 1;
		edgeSourceIdx = sourceIdx - 1;
		if (coordIdx >= sourceIdx) {
			DBASSERT (coordIdx >= edgeSourceIdx);
			break;
		}
		DBASSERT (coordIdx <= edgeSourceIdx);

		GS::Swap (vertices[coordIdx], vertices[sourceIdx]);
		if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
			GS::Swap (vertexInfos[coordIdx], vertexInfos[sourceIdx]);
		}
		if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData && edgeSourceIdx >= 1) {
			GS::Swap (inhEdgeInfos[coordIdx], inhEdgeInfos[edgeSourceIdx]);
		}
	}

	if (GetClosed () && inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData)
		inhEdgeInfos [nVertices] = inhEdgeInfos [1];

	for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
		arcs[arcIdx].begIndex = nVertices - arcs[arcIdx].endIndex + 1;
		arcs[arcIdx].endIndex = arcs[arcIdx].begIndex + 1;
		arcs[arcIdx].arcAngle = -arcs[arcIdx].arcAngle;
	}

	for (UIndex nurbsIdx = 0; nurbsIdx < nNurbs; nurbsIdx++) {
		nurbs[nurbsIdx].begIndex = nVertices - nurbs[nurbsIdx].begIndex;
		nurbs[nurbsIdx].nurbs.SetReverseDirection ();
	}
	
	Regularize ();
	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Stretch (	const Point2D& fixPoint,
								const Point2D& draggedPoint,
								const Vector2D& offsetAxisX,
								const Vector2D& offsetAxisY /*= Vector (0.0, 0.0)*/,
								const ArcDivParams& arcDivParams /*= ArcDivParams (0.0)*/)
{
	DBCHECKPOLY_ONEREFTOTHIS;
	
	DBCHECKPOLY_NONURBS;
	if (offsetAxisX.GetLengthSqr () < EPS && offsetAxisY.GetLengthSqr () < EPS)
		return;

	const Vector2D fixToDraggedVector = draggedPoint - fixPoint;

	if (fixToDraggedVector.GetLengthSqr () < EPS) {
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::Stretch: Dragged point = Fix point", __FILE__, __LINE__);
		return;
	}

	const bool needSegment = nArcs > 0 && arcs.GetSize () > 1;
	if ( (arcDivParams.maxDifference != 0.0 || arcDivParams.boxToKeepMaxDifferenceIn != nullptr) && needSegment) {
		GS::SharedPtr<CorePolyline2D> polyline2DPtr;
		SegmentUp (arcDivParams, polyline2DPtr);
		CopyInternalDataFrom (*polyline2DPtr);
	}

	if (offsetAxisX.GetLengthSqr () >= EPS) {
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

	if (offsetAxisY.GetLengthSqr () >= EPS) {
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

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>	//	ez duplikalva van a CorePolygon2D-ben
class CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ArrayRangeRotator {
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

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::RotateVerticeIndices (UIndex iVertexToFirst)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	if (DBVERIFY (flags.isClosed)) {
		const UIndex iFirstVertex	= 1;
		const UIndex iLastVertex	= nVertices;

		if (iFirstVertex == iVertexToFirst || iVertexToFirst == iLastVertex)
			return;

		if (DBERROR (!(iFirstVertex < iVertexToFirst && iVertexToFirst < iLastVertex)))
			throw GeometryIllegalArgumentException();

		ArrayRangeRotator::Rotate (vertices, iFirstVertex, iVertexToFirst, iLastVertex);
		vertices[iLastVertex] = vertices[iFirstVertex];
		for (UIndex i = 1; i < arcs.GetSize (); ++i) {
			if (arcs[i].begIndex < iVertexToFirst) {
				DBASSERT (iFirstVertex <= arcs[i].begIndex);
				arcs[i].begIndex += iLastVertex - iVertexToFirst;
				arcs[i].endIndex += iLastVertex - iVertexToFirst;
			} else if (iVertexToFirst <= arcs[i].begIndex) {
				DBASSERT (arcs[i].begIndex < iLastVertex);
				arcs[i].begIndex -= iVertexToFirst - iFirstVertex;
				arcs[i].endIndex -= iVertexToFirst - iFirstVertex;
			}
		}
		for (UIndex i = 0; i < nurbs.GetSize (); ++i) {
			if (nurbs[i].begIndex < iVertexToFirst) {
				DBASSERT (iFirstVertex <= nurbs[i].begIndex);
				nurbs[i].begIndex += iLastVertex - iVertexToFirst;
			} else if (iVertexToFirst <= nurbs[i].begIndex) {
				DBASSERT (nurbs[i].begIndex < iLastVertex);
				nurbs[i].begIndex -= iVertexToFirst - iFirstVertex;
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
	}

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SortArcsByIndices (void)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	class ArcSorter {
	public:
		static CmpResult Cmp (const PolyArcRec& op1, const PolyArcRec& op2)
		{
			return (op1.begIndex < op2.begIndex);
		}
	};
	GS::Sort (arcs.Begin (), arcs.End (), ArcSorter::Cmp);

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Append (const Point2D& c, const bool atEnd)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	if (DBERROR_GUID (GetClosed () || IsEmpty (), "{62A50F4B-4156-4E95-B519-16CFF8221857}")) {
		throw GeometryException ();
	}

 	UIndex newVertexIndex = (atEnd) ? (nVertices + 1) : 1;
 
 	if (!atEnd) {
 		for (UIndex i = 1; i <= nArcs; i++) {
 			++arcs[i].begIndex;
 			arcs[i].endIndex = arcs[i].begIndex + 1;
 		}
		for (UIndex i = 0; i < nNurbs; i++) {
 			++nurbs[i].begIndex;
 		}
 	}
 
 	vertices.Insert (newVertexIndex, c);
 
	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
		vertexInfos.SetSize (nVertices + 1 + 1);
		if (!atEnd) {
			CopyInfo_Data <VertexUserData> (vertexInfos, 2, vertexInfos, 1, nVertices);
		}
		vertexInfos [newVertexIndex] = defaultVertexData;
	}
	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
		inhEdgeInfos.SetSize (nVertices + 1 + 1);
		if (atEnd) {
			inhEdgeInfos [newVertexIndex - 1] = defaultEdgeData;
		} else {
			CopyInfo_Data <EdgeUserData> (inhEdgeInfos, 2, inhEdgeInfos, 1, nVertices);
			inhEdgeInfos [1] = defaultEdgeData;
		}
	}

 	++nVertices;

	UpdateBoundingBox ();
	Regularize ();

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Append (const CorePolyline2D& polylineToAppend)
{
	DBCHECKPOLY_ONEREFTOTHIS;
	DBCHECKPOLY_NONURBS;

	if (DBERROR_GUID (GetClosed () || polylineToAppend.GetClosed (), "{D40B501E-E87B-4FF5-B5B7-658633999B74}"))
		throw GeometryIllegalArgumentException ("Can't merge closed polylines!!!", __FILE__, __LINE__);

	if (polylineToAppend.IsEmpty ())
		return;

	if (IsEmpty ()) {
		operator= (polylineToAppend);
		return;
	}

	VertexUserData auldLastVertexUserData;
	UIndex oldnVertices = nVertices;
	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData)
		auldLastVertexUserData = vertexInfos.GetLast ();

	if (!flags.isSameCoord && IsEqualCoord (polylineToAppend.vertices[1], vertices.GetLast (), Eps)) {
		vertices.Pop ();
		--nVertices;
		if (vertexInfos.GetSize () != 0 && flags.isVertexUserData)
			vertexInfos.Pop ();
		if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData)
			inhEdgeInfos.Pop ();
	}

	vertices.Insert (vertices.GetSize (), ++polylineToAppend.vertices.Enumerate ());
	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
		vertexInfos.Insert (vertexInfos.GetSize (), ++polylineToAppend.vertexInfos.Enumerate ());
		vertexInfos[oldnVertices] = auldLastVertexUserData;
	}
	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData) {
		inhEdgeInfos.Insert (inhEdgeInfos.GetSize (), ++polylineToAppend.inhEdgeInfos.Enumerate ());
	}
	if (polylineToAppend.nArcs > 0) {
		if (nArcs == 0) {
			arcs = polylineToAppend.arcs;
		} else {
			arcs.Insert (arcs.GetSize (), ++polylineToAppend.arcs.Enumerate ());
		}
		for (UIndex i = nArcs + 1; i < arcs.GetSize (); ++i) {
			arcs[i].begIndex += nVertices;
			arcs[i].endIndex = arcs[i].begIndex + 1;
		}
		nArcs += polylineToAppend.nArcs;
	}
	nVertices += polylineToAppend.nVertices;

	UpdateBoundingBox ();
	Regularize ();

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Visit (CorePolyline2DVertexVisitor &visitor)
{
	DBCHECKPOLY_ONEREFTOTHIS;
	DBCHECKPOLY_NONURBS;

	UIndex endVertexIdx = nVertices;
	if (GetClosed ())
		endVertexIdx--;

	for (UIndex vIdx = 1; vIdx < endVertexIdx + 1; ++vIdx) {
		visitor (vertices[vIdx]);	// Coord may be modified!
	}
	if (GetClosed ())
		vertices[nVertices] = vertices[1];

	UpdateBoundingBox ();
	Regularize ();
	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ArcToNurbs ()
{
	for (GS::UInt32 i = 1; i <= nArcs; i++) {
		NurbsRec nurbsRec;
		nurbsRec.begIndex = arcs[i].begIndex;
		nurbsRec.nurbs.CreateArc (vertices[arcs[i].begIndex], vertices[arcs[i].endIndex], arcs[i].arcAngle);
		nurbs.Push (nurbsRec);
		nNurbs++;
	}
	arcs.Clear ();
	arcs.Push (PolyArcRec (0, 0, 0.0));
	nArcs = 0;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Transform( const ArcDivParams& arcDivParams, const TRANMAT& tran, GS::SharedPtr<CorePolyline2D>& result ) const
{
	if (tran.IsIdentity ()) {
		return ResultSameAsThis;
	}
	if (IsEmpty ()) {
		return ResultSameAsThis;
	}

	if ( (arcDivParams.maxDifference != 0.0 || arcDivParams.boxToKeepMaxDifferenceIn != nullptr) && nArcs > 0 && arcs.GetSize () > 1 && !Geometry::TMIsPreserveArc (tran)) {
		SegmentUp (arcDivParams, result); //A visszateresi erteket nem kell vizsgalni, mert nArcs > 0
	} else {
		result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);
	}

	for (UIndex vertexIdx = 1; vertexIdx <= result->nVertices; vertexIdx++) {
		result->vertices[vertexIdx] = Geometry::Transform2dPoint (tran, result->vertices[vertexIdx]);
	}
	for (UIndex nurbsIdx = 0; nurbsIdx < nNurbs; nurbsIdx++) {
		result->nurbs[nurbsIdx].nurbs.Transform (tran);
	}

	if (result->arcs.GetSize () > 1 && (tran.HasMirror ())) {
		for (UIndex arcIdx = 1; arcIdx <= result->nArcs; arcIdx++)
			result->arcs[arcIdx].arcAngle *= -1;
	}
	result->UpdateBoundingBox ();
	result->Regularize ();

	DBCHECKPOLY_CHECKRESULT;
	//Ezutan mar nincs szukseg regularizalasra. A SegmentUp regularizal ha kell a koordinata transzformalas utan pedig nincs szukseg regularizalasra
	return NewPolylines;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Transform (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& filterWithPolygon, const ArcDivParams& arcDivParams, const TRANMAT& tran, GS::SharedPtr<CorePolyline2D>& result, bool& isTransformedAll) const
{
	if (tran.IsIdentity ()) {
		return ResultSameAsThis;
	}
	if (IsEmpty ()) {
		return ResultSameAsThis;
	}

	isTransformedAll = true;
	if ((arcDivParams.maxDifference != 0.0 || arcDivParams.boxToKeepMaxDifferenceIn != nullptr) && nArcs > 0 && arcs.GetSize () > 1 && !Geometry::TMIsPreserveArc (tran)) {
		SegmentUp (arcDivParams, result); //A visszateresi erteket nem kell vizsgalni, mert nArcs > 0
	} else {
		result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);
	}

	for (UIndex vertexIdx = 1; vertexIdx <= result->nVertices; vertexIdx++) {
		RelativePosition relpos = filterWithPolygon.GetPosition (result->vertices[vertexIdx], Boundary_Closed);
		if (IsOverlap (relpos))
			result->vertices[vertexIdx] = Geometry::Transform2dPoint (tran, result->vertices[vertexIdx]);
		else
			isTransformedAll = false;
	}

	if (result->arcs.GetSize () > 1 && (tran.HasMirror ())) {
		for (UIndex arcIdx = 1; arcIdx <= result->nArcs; arcIdx++) {
			RelativePosition relpos1 = filterWithPolygon.GetPosition (result->vertices[result->arcs[arcIdx].begIndex], Boundary_Closed);
			RelativePosition relpos2 = filterWithPolygon.GetPosition (result->vertices[result->arcs[arcIdx].endIndex], Boundary_Closed);
			if (IsOverlap (relpos1) && IsOverlap (relpos2))
				result->arcs[arcIdx].arcAngle *= -1.0;
		}
	}

	for (GS::UInt32 i = 0; i < result->nNurbs; i++)
		result->nurbs[i].nurbs.Transform (tran);

	result->UpdateBoundingBox ();
	result->Regularize ();

	DBCHECKPOLY_CHECKRESULT;
	//Ezutan mar nincs szukseg regularizalasra. A SegmentUp regularizal ha kell a koordinata transzformalas utan pedig nincs szukseg regularizalasra
	return NewPolylines;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class ContourUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Transform (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& filterPolygonArray, const ArcDivParams& arcDivParams, const TRANMAT& tran, GS::SharedPtr<CorePolyline2D>& result, bool& isTransformedAll) const
{
	if (tran.IsIdentity ()) {
		return ResultSameAsThis;
	}
	if (IsEmpty ()) {
		return ResultSameAsThis;
	}

	isTransformedAll = true;
	if ((arcDivParams.maxDifference != 0.0 || arcDivParams.boxToKeepMaxDifferenceIn != nullptr) && nArcs > 0 && arcs.GetSize () > 1 && !Geometry::TMIsPreserveArc (tran)) {
		SegmentUp (arcDivParams, result); //A visszateresi erteket nem kell vizsgalni, mert nArcs > 0
	} else {
		result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);
	}
	
		for (UIndex vertexIdx = 1; vertexIdx <= result->nVertices; vertexIdx++) {
		RelativePosition relpos = CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (filterPolygonArray, result->vertices[vertexIdx], Boundary_Closed);
		if (IsOverlap (relpos))
			result->vertices[vertexIdx] = Geometry::Transform2dPoint (tran, result->vertices[vertexIdx]);
		else
			isTransformedAll = false;
	}

	if (result->arcs.GetSize () > 1 && (tran.HasMirror ())) {
		for (UIndex arcIdx = 1; arcIdx <= result->nArcs; arcIdx++) {
			RelativePosition relpos1 = CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (filterPolygonArray, result->vertices[result->arcs[arcIdx].begIndex], Boundary_Closed);
			RelativePosition relpos2 = CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (filterPolygonArray, result->vertices[result->arcs[arcIdx].endIndex], Boundary_Closed);
			if (IsOverlap (relpos1) && IsOverlap (relpos2))
				result->arcs[arcIdx].arcAngle *= -1.0;
		}
	}

	for (GS::UInt32 i = 0; i < result->nNurbs; i++)
		result->nurbs[i].nurbs.Transform (tran);

	result->UpdateBoundingBox ();
	result->Regularize ();

	DBCHECKPOLY_CHECKRESULT;
	//Ezutan mar nincs szukseg regularizalasra. A SegmentUp regularizal ha kell a koordinata transzformalas utan pedig nincs szukseg regularizalasra
	return NewPolylines;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SegmentUp( const ArcDivParams& arcDivParams, GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& result ) const
{
	if ((nArcs <= 0 || arcs.GetSize () == 0) && (nNurbs <= 0 || nurbs.GetSize () == 0)) {
		return ResultSameAsThis;
	}

	try {
		GS::Array< GS::Array<Point2D> > segmentedArcs;
		GS::Array< GS::Array<Point2D> > segmentedNurbs;
		USize numOfSegmentedVertex = 0;
		FillSegmentedArc (arcDivParams, segmentedArcs, numOfSegmentedVertex);
		FillSegmentedNurbs (arcDivParams, segmentedNurbs, numOfSegmentedVertex);
		result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this, true);
		result->CopyPolygonLevelDataFrom (*this);
		result->AllocateInternalData (0 /*nVertices*/, 0 /*nArcs*/, 0 /*nNurbs*/, nVertices + numOfSegmentedVertex /*verticesCapacity*/, 0 /*arcsCapacity*/, 0 /*nurbsCapacity*/);
		SetSegmentUp (result, segmentedArcs, segmentedNurbs);
	} catch (const std::exception&) {
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::SegmentUp", __FILE__, __LINE__);
	} catch (const GS::Exception& e) {
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolyline2D::SegmentUp", __FILE__, __LINE__);
	}

	DBASSERT (!GetClosed () || Geometry::IsEqualCoord (result->vertices[result->nVertices], result->vertices[1], EPS)); //Ez nem biztos, hogy hiba
	/*if (GetClosed ()) {
		result->vertices[result->nVertices] = result->vertices[1];
	}*/

	result->UpdateBoundingBox ();
	result->Regularize ();
	DBCHECKPOLY_CHECKRESULT;
	return NewPolylines;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::EliminateArcs ( GS::SharedPtr<CorePolyline2D>& result ) const
{
	if (nArcs <= 0 || arcs.GetSize () <= 1) {
		return ResultSameAsThis;
	}

	try {
		result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);
		result->arcs.Clear ();
		PolyArcRec dummyArc;
		dummyArc.arcAngle = 0.0;
		dummyArc.begIndex = 0;
		dummyArc.endIndex = 0;
		result->arcs.Push (dummyArc);
		result->nArcs = 0;
		result->nurbs.Clear ();
		result->nNurbs = 0;
	} catch (const std::exception&) {
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::EliminateArcs", __FILE__, __LINE__);
	} catch (const GS::Exception& e) {
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolyline2D::SegmentUp", __FILE__, __LINE__);
	}

	result->UpdateBoundingBox ();
	result->Regularize ();

	DBCHECKPOLY_CHECKRESULT;
	return NewPolylines;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Reverse ( GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& result ) const
{
	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this, true);
	result->CopyPolygonLevelDataFrom (*this);
	result->AllocateInternalData (nVertices, nArcs, nNurbs);

	UIndex sourceIdx;
	UIndex edgeSourceIdx;

	for (UIndex coordIdx = 1; coordIdx <= nVertices; coordIdx++) {
		sourceIdx = nVertices - coordIdx + 1;
		edgeSourceIdx = sourceIdx - 1;
		result->vertices[coordIdx] = vertices[sourceIdx];
		if (result->vertexInfos.GetSize() != 0 && result->flags.isVertexUserData && vertexInfos.GetSize() != 0 && flags.isVertexUserData)
			result->vertexInfos[coordIdx] = vertexInfos[sourceIdx];
		if (result->inhEdgeInfos.GetSize() != 0 && result->flags.isEdgeUserData && inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
			if (edgeSourceIdx >= 1)
				result->inhEdgeInfos[coordIdx] = inhEdgeInfos[edgeSourceIdx];
			else if (GetClosed ())
				result->inhEdgeInfos[coordIdx] = inhEdgeInfos[1];
		}
	}

	for (UIndex arcIdx = 1; arcIdx <= nArcs; arcIdx++) {
		sourceIdx = nArcs - arcIdx + 1;
		result->arcs[arcIdx].begIndex = nVertices - arcs[sourceIdx].endIndex + 1;
		result->arcs[arcIdx].endIndex = nVertices - arcs[sourceIdx].begIndex + 1;
		result->arcs[arcIdx].arcAngle = -arcs[sourceIdx].arcAngle;
	}

	for (UIndex nurbsIdx = 1; nurbsIdx <= nNurbs; nurbsIdx++) {
		sourceIdx = nNurbs - nurbsIdx + 1;
		result->nurbs[nurbsIdx].begIndex = nVertices - nurbs[sourceIdx].begIndex;
		result->nurbs[nurbsIdx].nurbs.SetReverseDirection ();
	}

	result->UpdateBoundingBox ();

	result->Regularize ();
	DBCHECKPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::OffsetAllEdge ( double offset, GS::SharedPtr<CorePolyline2D>& result, double* newOffset ) const
{
	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);
	result->DropNurbs ();

	if (IsEmpty () || fabs (offset) < Eps) {
		if (newOffset != nullptr)
			*newOffset = (-1.0 * offset);
		return;
	}

	try {
		/* Az arcokat meg at kell konvertalni !!!! 0-tol ill. 1-tol, eldobni a felesleges handlekat, egyforma pontok kiszurese */
		offset *= -1.0;

		result->GetOffsetLimit (&offset);
		result->OffsetAllEdge (offset);

		if (newOffset != nullptr)
			*newOffset = offset;
	} catch (const GS::GSException& e) {
		e.Print (dbChannel);
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolyline2D::OffsetAllEdge", __FILE__, __LINE__);
	}
	result->RemoveSmallArcs ();

	result->UpdateBoundingBox ();

	result->Regularize ();
	DBCHECKPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::OffsetEdge( UIndex edgeIdx, double offset, GS::SharedPtr<CorePolyline2D>& result ) const
{
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());
	if (DBERROR (edgeIdx <= 0 || ULong (edgeIdx) > nVertices)) {
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::OffsetEdge", __FILE__, __LINE__);
	}

	try {
		result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);
		result->DropNurbs ();

		UIndex						begContourIdx;
		UIndex						endContourIdx;
		bool						degen1, degen2;
		Point2D						degenC1, degenC2;

		offset *= -1;
		begContourIdx = 1;
		endContourIdx = result->nVertices;
		if (result->GetClosed ())
			endContourIdx--;
		result->GetOffsetLimitEdge (&offset, edgeIdx);
		result->OffsetOneEdge (offset, edgeIdx, &degen1, &degenC1, &degen2, &degenC2);
		if (degen2) {
			UIndex  nextEdgeIdx = (edgeIdx + 1 > endContourIdx) ? begContourIdx : edgeIdx + 1;
			result->InsertVertexFromInternalData(nextEdgeIdx, degenC2, true, true);
			if (result->inhEdgeInfos.GetSize () != 0 && result->flags.isEdgeUserData) {
				result->inhEdgeInfos [nextEdgeIdx] = result->defaultEdgeData;
			}
			endContourIdx++;
		}
		if (degen1) {
			UIndex	prevEdgeIdx = (edgeIdx - 1 < begContourIdx) ? endContourIdx : edgeIdx - 1;
			result->InsertVertexFromInternalData(prevEdgeIdx, degenC1, true, false);
			if (result->inhEdgeInfos.GetSize () != 0 && result->flags.isEdgeUserData) {
				result->inhEdgeInfos [prevEdgeIdx + 1] = result->defaultEdgeData;
			}
		}
	} catch (const GS::GSException& e) {
		e.Print (dbChannel);
		ThrowGeometryExceptionAtError (e.GetErrCode (), "CorePolyline2D::OffsetEdge", __FILE__, __LINE__);
	}

	result->UpdateBoundingBox ();

	result->Regularize ();

	if (result->nVertices <= 1) {
		DBBREAK (); //elofordulhat ilyen?
		//ilyenkor egy ures polygon-t adunk vissza
		result = nullptr;
		return EmptyPolyline;
	}

	DBCHECKPOLY_CHECKRESULT;
	return NewPolylines;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::MoveVertex( UIndex vertexIdx, const Point2D& newPosition, GS::SharedPtr<CorePolyline2D>& result ) const
{
	DBCHECKINDEX(vertexIdx, 1, GetVertexNum ());
	if (DBERROR (vertexIdx <= 0 || ULong (vertexIdx) > nVertices))
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::MoveVertex", __FILE__, __LINE__);

	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);
	result->DropNurbs ();

	if (GetClosed () && (vertexIdx == 1 || vertexIdx == nVertices)) {
		result->vertices[1] = newPosition;
		result->vertices[nVertices] = newPosition;
	} else {
		result->vertices[vertexIdx] = newPosition;
	}

	result->UpdateBoundingBox ();

	result->Regularize ();
	DBCHECKPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::FilletAllVertex( const double filletRadius, GS::SharedPtr<CorePolyline2D>& result ) const
{
	if (IsEmpty ())
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::FilletAllVertex on empty polyline", __FILE__, __LINE__);

	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);
	result->DropNurbs ();

	result->PolylineFilletChamferContour (filletRadius, true);

	result->UpdateBoundingBox ();

	result->Regularize ();
	DBCHECKPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::FilletVertex( UIndex vertexIdx, const double filletRadius, GS::SharedPtr<CorePolyline2D>& result ) const
{
	if (IsEmpty ())
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::FilletVertex on empty polyline", __FILE__, __LINE__);

#if defined(DEBUVERS_POLY2D)
	if (GetClosed ()) {
		DBCHECKINDEX(vertexIdx, 1, GetVertexNum ());
	} else {
		DBCHECKINDEX(vertexIdx, 2, GetVertexNum () - 1);
	}
#endif
	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);
	result->DropNurbs ();

	result->PolylineFilletChamferVertex (vertexIdx, filletRadius, true);

	result->UpdateBoundingBox ();

	result->Regularize ();

	DBCHECKPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ChamferAllVertex( const double chamferRadius, GS::SharedPtr<CorePolyline2D>& result ) const
{
	if (IsEmpty ())
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::ChamferAllVertex on empty polyline", __FILE__, __LINE__);

	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);
	result->DropNurbs ();

	result->PolylineFilletChamferContour (chamferRadius, false);

	result->UpdateBoundingBox ();

	result->Regularize ();

	DBCHECKPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ChamferVertex( UIndex vertexIdx, const double chamferRadius, GS::SharedPtr<CorePolyline2D>& result ) const
{
	if (IsEmpty ())
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::ChamferVertex on empty polyline", __FILE__, __LINE__);

#if defined(DEBUVERS_POLY2D)
	if (GetClosed ()) {
		DBCHECKINDEX(vertexIdx, 1, GetVertexNum ());
	} else {
		DBCHECKINDEX(vertexIdx, 2, GetVertexNum () - 1);
	}
#endif
	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);
	result->DropNurbs ();

	result->PolylineFilletChamferVertex (vertexIdx, chamferRadius, false);

	result->UpdateBoundingBox ();

	result->Regularize ();

	DBCHECKPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::InsertNewVerticesAndDeleteOld (UIndex filletChamferVertexIdx, const Point2D& begFilletChamferPosition, const Point2D& endFilletChamferPosition, UIndex begContourIdx, UIndex endContourIdx, UIndex& prevVertIdx, bool isPrevEdgeArc, GS::Int32 arcIndBeg, double newPrevEdgeArcViewAngle, bool isNextEdgeArc, GS::Int32 arcIndEnd, double newNextEdgeArcViewAngle, bool united1, bool united2)
{
	/* insert new vertices and delete old vertex */
	if (!united2) {
		if (isNextEdgeArc)
			arcs[arcIndEnd].arcAngle = newNextEdgeArcViewAngle;
		InsertVertexFromInternalData (filletChamferVertexIdx, endFilletChamferPosition, true, true);
	} else {
		if (prevVertIdx == endContourIdx)
			prevVertIdx = (prevVertIdx - 1 < begContourIdx) ? endContourIdx : prevVertIdx - 1;
	}

	DeleteVertexFromInternalData (filletChamferVertexIdx);

	if (!united1) {
		if (isPrevEdgeArc)
			arcs[arcIndBeg].arcAngle = newPrevEdgeArcViewAngle;
		InsertVertexFromInternalData (prevVertIdx, begFilletChamferPosition, true, false);	/* Ha ives elotte akkor mi van ???? */
	}
	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
		UIndex insertedEdgeIndex = prevVertIdx;
		if (!united1) {
			insertedEdgeIndex++;
		}
		inhEdgeInfos [insertedEdgeIndex] = defaultEdgeData;
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::InsertVertex( UIndex edgeIdx, const Point2D& newPosition, GS::SharedPtr<CorePolyline2D>& result ) const
{
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());

	if (DBERROR (edgeIdx <= 0 || ULong (edgeIdx) > nVertices))
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::InsertVertex", __FILE__, __LINE__);

	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);

	result->InsertVertexFromInternalData (edgeIdx, newPosition);

	result->UpdateBoundingBox ();

	result->Regularize ();

	DBCHECKPOLY_CHECKRESULT;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::InsertVertexOnPolyline (const Point2D& newPosition, UIndex edgeIndex, GS::SharedPtr<CorePolyline2D>& result, UIndex& vertexIdx) const
{
	DBCHECKPOLY_NONURBS;

	if (DBERROR (IsEmpty ()))
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::InsertVertexOnPolyline empty polyline", __FILE__, __LINE__);

	GS::Array<UIndex> edges;
	if (DBERROR (!IsCoordOnEdge (newPosition, edges) || !edges.Contains (edgeIndex)))
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::InsertVertexOnPolyline vertex not on polyline", __FILE__, __LINE__);

	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);

	result->InsertVertexFromInternalData (edgeIndex, newPosition, true, true);

	UIndex arcIndex = GetInternalArcIdx (edgeIndex);

	if (arcIndex > 0) {
		Point2D origC;
		const double& origArcAngle = arcs[arcIndex].arcAngle;
		if (ArcGetOrigo (&vertices[edgeIndex], &vertices[edgeIndex + 1], origArcAngle, &origC)) {
			const double newAngle = ComputeRotFi (origC, vertices[edgeIndex], newPosition, origArcAngle < 0.0);
			PolyArcRec newArc;
			newArc.begIndex = edgeIndex;
			newArc.endIndex = edgeIndex + 1;
			newArc.arcAngle = newAngle;
			++result->nArcs;
			result->arcs.Insert (arcIndex, newArc);
			result->arcs[arcIndex + 1].arcAngle = origArcAngle - newAngle;
		}
	}

	result->UpdateBoundingBox ();

	result->Regularize ();

	if (IsEqualCoord (result->vertices[edgeIndex], newPosition, Eps))
		vertexIdx = edgeIndex;
	else
		vertexIdx = edgeIndex + 1;

	DBCHECKPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DeleteVertex( UIndex vertexIdx, GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& result ) const
{
	DBCHECKINDEX(vertexIdx, 1, GetVertexNum ());

	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);

	result->DeleteVertexFromInternalData (vertexIdx);

	// utolsok visszalinkelese
	if (GetClosed ()) {
		GS::UInt32	firstVert = 1;
		GS::UInt32	lastVert = result->nVertices;

		result->vertices[lastVert] = result->vertices[firstVert];
		if (result->vertexInfos.GetSize() != 0 && result->flags.isVertexUserData)
			result->vertexInfos[lastVert] = result->vertexInfos[firstVert];
		if (result->inhEdgeInfos.GetSize() != 0 && result->flags.isEdgeUserData)
			result->inhEdgeInfos[lastVert] = result->inhEdgeInfos[firstVert];
	}

	result->UpdateBoundingBox ();

	result->Regularize ();

	DBCHECKPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::SetEdgeAngle( UIndex edgeIdx, double edgeAngle, GS::SharedPtr<CorePolyline2D>& result ) const
{
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());

	if (DBERROR (edgeIdx <= 0 || ULong (edgeIdx) > nVertices))
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::SetEdgeAngle", __FILE__, __LINE__);

	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);

	GS::Int32	chArcInd = -1;
	for (UIndex i = 1; i <= result->nArcs; i++) {
		if (result->arcs[i].begIndex == (UIndex) edgeIdx) {
			chArcInd = i;
			break;
		}
	}

	if (edgeAngle != 0.0) { // exact match!!!
		if (chArcInd >= 0) {
			result->arcs[chArcInd].arcAngle = edgeAngle;
		} else {
			PolyArcRec arcRec;
			arcRec.begIndex = edgeIdx;
			arcRec.endIndex = edgeIdx + 1;
			arcRec.arcAngle = edgeAngle;
			/* felvenni a arcos bejegyzest */
			result->nArcs += 1;
			if (result->nArcs == 1) {
				result->arcs.SetSize (2);
				result->arcs[0].begIndex = 0;
				result->arcs[0].endIndex = 0;
				result->arcs[0].arcAngle = 0.0;
			} else {
				result->arcs.SetSize (result->nArcs + 1);
			}
			result->arcs[result->nArcs] = arcRec;
		}
	} else {
		if (chArcInd >= 0) {
			/* torolni a arcos bejegyzest */
			result->arcs.Delete (chArcInd);
			result->nArcs -= 1;
		}
	}

	result->UpdateBoundingBox ();

	result->Regularize ();
	DBCHECKPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ReplaceEdge (UIndex edgeIdx, const GenArc& genArc, const ArcDivParams& arcDivParams, GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& result) const
{
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());

	if (DBERROR (edgeIdx <= 0 || ULong (edgeIdx) > nVertices || genArc.IsWhole ()))
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::ReplaceEdge", __FILE__, __LINE__);

	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);

	result->ReplaceEdgeFromInternalData (edgeIdx, genArc, arcDivParams);

	result->UpdateBoundingBox ();

	result->Regularize ();

	DBCHECKPOLY_CHECK;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DeleteEdge( UIndex edgeIdx, GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& result ) const
{
	DBCHECKINDEX(edgeIdx, 1, GetEdgeNum ());
	bool success = true;

	if (DBERROR (edgeIdx <= 0 || ULong (edgeIdx) > nVertices))
		ThrowGeometryExceptionAtError (Error, "CorePolyline2D::DeleteEdge", __FILE__, __LINE__);

	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this);

	success = result->PolylineDeleteEdge (edgeIdx);

	result->UpdateBoundingBox ();

	result->Regularize ();

	DBCHECKPOLY_CHECKRESULT;
	return success;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::ShiftPolyline (double length, bool firstEdge, GS::SharedPtr<CorePolyline2D>& result) const
{
	DBCHECKPOLY_NONURBS;

	if (DBERROR (IsEmpty () || GetClosed ()))
		throw GeometryException ("ShiftPolyline empty or closed polyline", __FILE__, __LINE__);

	if (length < 0.0) {
		length *= -1.0;
		firstEdge = !firstEdge;
	}
	const double origPolylineLength = CalcLength ();

	CutParam t1, t2;
	bool removeFakeEdge = false;
	if (firstEdge) {
		t1.edgeIndex = 1;
		t1.param = 0.0;

		double act = 0.0;
		UIndex edge = nVertices - 1;
		do {
			act += GetEdgeLength (edge);
			if (act > length + Eps)
				break;
			--edge;
		} while (edge > 0);

		if (edge != 0) {
			t2.edgeIndex = edge;
			t2.param = (act - length) / GetEdgeLength (edge);
		} else {
			removeFakeEdge = true;
			t2.edgeIndex = 1;
			t2.param = 1.0;
		}
	} else {
		t2.edgeIndex = nVertices - 1;
		t2.param = 1.0;

		double act = 0.0;
		UIndex edge = 1;
		do {
			act += GetEdgeLength (edge);
			if (act > length + Eps)
				break;
			++edge;
		} while (edge < nVertices);

		if (edge < nVertices) {
			t1.edgeIndex = edge;
			t1.param = 1.0 - (act - length) / GetEdgeLength (edge);
		} else {
			removeFakeEdge = true;
			t1.edgeIndex = nVertices - 1;
			t1.param = 0.0;
		}
	}

	if (CutPiece (t1, t2, result) != NewPolylines)
		throw GeometryException ("ShiftPolyline something went wrong!", __FILE__, __LINE__);

	const UIndex edgeIndex			= (firstEdge) ? 1 : result->nVertices - 1;
	const UIndex vertexIndex		= (firstEdge) ? 1 : result->nVertices;
	const UIndex otherVertexIndex	= (firstEdge) ? 2 : result->nVertices - 1;

	const double origEdgeAngle		= result->GetArcAngle (edgeIndex);

	Sector s;
	GenArc genArc;
	if (result->GetSector (edgeIndex, s, genArc)) {
		UIndex arcIndex = result->GetInternalArcIdx (edgeIndex);
		double angle = length / genArc.GetMainAxisLength ();
		if (origEdgeAngle < 0.0)
			angle *= -1.0;
		const double vertexRotAngle = (firstEdge) ? - angle : angle;
		const Point2D& coordToRotate = (firstEdge) ? genArc.GetBegC () : genArc.GetEndC ();
		Point2D endC = RotCoord (genArc.GetOrigo (), coordToRotate, sin (vertexRotAngle), cos (vertexRotAngle));
		result->vertices[vertexIndex] = endC;
		result->arcs[arcIndex].arcAngle = origEdgeAngle + angle;
		if (removeFakeEdge) {
			DBASSERT (length > origPolylineLength - Eps);
			double angle = origPolylineLength / genArc.GetMainAxisLength ();
			if (origEdgeAngle < 0.0)
				angle *= -1.0;
			const double vertexRotAngle = (firstEdge) ? angle : -angle;
			endC = RotCoord (genArc.GetOrigo (), endC, sin (vertexRotAngle), cos (vertexRotAngle));
			result->vertices[otherVertexIndex] = endC;
			result->arcs[arcIndex].arcAngle = angle;
		}
	} else {
		Vector2D v = UnitVector (s.c2 - s.c1) * length;
		if (firstEdge)
			v *= -1.0;
		result->vertices[vertexIndex] = result->vertices[vertexIndex] + v;
		if (removeFakeEdge) {
			DBASSERT (length > origPolylineLength - Eps);
			Vector2D v = UnitVector (s.c1 - s.c2) * origPolylineLength;
			if (firstEdge)
				v *= -1.0;
			result->vertices[otherVertexIndex] = result->vertices[vertexIndex] + v;
		}
	}

	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData) {
		result->vertexInfos[1] = vertexInfos[1];
		result->vertexInfos[result->nVertices] = vertexInfos[nVertices];
	}

	DBASSERT (fabs (origPolylineLength - result->CalcLength ()) < Eps);

	result->UpdateBoundingBox ();
	result->Regularize ();

	DBCHECKPOLY_CHECKRESULT;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CutAtVertices (GS::Array<UIndex>& vertexIdxArray, GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >& result) const 
{
	if (vertexIdxArray.GetSize () == 0)
		return ResultSameAsThis;

	for (UIndex i = 0; i < vertexIdxArray.GetSize (); i++) {
		DBCHECKINDEX(vertexIdxArray[i], 1, nVertices);
	}

	bool needToCloseBegAndEndParts = flags.isClosed && !vertexIdxArray.Contains (1) && !vertexIdxArray.Contains (nVertices);

	Point2D*			pVerticesNew = (Point2D*) BMpAll (sizeof (Point2D) * (nVertices + 1));
	PolyArcRec*		pArcsNew = (PolyArcRec*) BMpAll (sizeof (PolyArcRec) * (nArcs + 1));
	NurbsRec*		pNurbsNew = (NurbsRec*) BMpAll (sizeof (NurbsRec) * (nNurbs)); // nurbs 0-tol indexelodik
	Int32*			pVertIndsNew = (vertexInfos.GetSize() != 0 && flags.isVertexUserData) ? (Int32*) BMpAll (sizeof (Int32) * (nVertices + 1)) : nullptr;
	Int32*			pEdgeIndsNew = (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) ? (Int32*) BMpAll (sizeof (Int32) * (nVertices + 1)) : nullptr;
	if (pVerticesNew == nullptr || pArcsNew == nullptr || 
		(vertexInfos.GetSize() != 0 && flags.isVertexUserData && pVertIndsNew == nullptr) || 
		(inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData && pEdgeIndsNew == nullptr)) {
		throw GS::OutOfMemoryException ("Error in CorePolyline2D::CutAtVertices!!!", __FILE__, __LINE__);
	}

	// 0. elemek
	pVerticesNew[0] = Point2D ();
	pArcsNew[0] = PolyArcRec ();
	pVertIndsNew[0] = 0;
	pEdgeIndsNew[0] = 0;

	GS::Sort (vertexIdxArray.Begin (), vertexIdxArray.End ());
	vertexIdxArray.Insert (0, 1);
	vertexIdxArray.Push (nVertices);
	for (UIndex i = 0; i < vertexIdxArray.GetSize () - 1; i++) {
		const UIndex firstVertexIdx = vertexIdxArray[i];
		const UIndex lastVertexIdx = vertexIdxArray[i+1];		
		if (firstVertexIdx == lastVertexIdx || lastVertexIdx == 1 || firstVertexIdx == nVertices)
			continue;

		USize nVerticesNew = lastVertexIdx - firstVertexIdx + 1; 
		USize nArcsNew = 0;
		USize nNurbsNew = 0;
		UIndex	idxOld, idxNew;
		for (idxOld = firstVertexIdx, idxNew = 1; idxOld <= lastVertexIdx; idxOld++, idxNew++) {
			pVerticesNew[idxNew].x = vertices[idxOld].x;
			pVerticesNew[idxNew].y = vertices[idxOld].y;
			if (idxOld != lastVertexIdx) {
				UIndex arcIdxOld = GetInternalArcIdx (idxOld);
				if (arcIdxOld != 0) {					
					pArcsNew[nArcsNew].begIndex = idxNew;
					pArcsNew[nArcsNew].endIndex = idxNew + 1;
					pArcsNew[nArcsNew].arcAngle = arcs[arcIdxOld].arcAngle;
					nArcsNew++;		// a kesobb hivando SetInternalData fuggveny a Vertex-eket 1-tol, az Arc-okat 0-tol kezdi indexelni
				}
				UIndex nurbsIdxOld = GetInternalNurbsIdx (idxOld);
				if (nurbsIdxOld != MaxUInt32) {
					pNurbsNew[nNurbsNew].begIndex = idxNew;
					pNurbsNew[nNurbsNew].nurbs = nurbs[nurbsIdxOld].nurbs;
					nNurbsNew++;	// a kesobb hivando SetInternalData fuggveny a Vertex-eket 1-tol, a Nurbs-okat 0-tol kezdi indexelni
				}
			}
			pVertIndsNew[idxNew] = idxOld;
			pEdgeIndsNew[idxNew] = idxOld;
		}

		GS::SharedPtr<CorePolyline2D> newPolyline = new CorePolyline2D (*this, true);
		newPolyline->CopyPolygonLevelDataFrom (*this);	// atmasolja PolygonUserData-t es a flag-eket
		newPolyline->AllocateInternalData (nVerticesNew, nArcsNew, nNurbs);
		GS::Array<const EdgeUserData*> customInhEdgeInfo;		
		newPolyline->SetInternalData (*this, 
									  nVerticesNew, 
									  (double*) pVerticesNew,
									  nArcsNew, 
									  pArcsNew, 
									  nNurbsNew,
									  pNurbsNew,
									  customInhEdgeInfo, 
									  pEdgeIndsNew, 
									  pVertIndsNew);	// kezeli a closed flag-et
		if (!newPolyline->IsEmpty ())
			result.Push (newPolyline);
	}

	const bool partsAreAppendable = result.GetSize () > 1 && !result.GetFirst ()->GetClosed () && !result.GetLast ()->GetClosed ();
	if (needToCloseBegAndEndParts && partsAreAppendable) {
		GS::SharedPtr<CorePolyline2D> begPart = result.GetFirst ();

		result.GetLast ()->Append (*begPart);
		result.Delete (0);
	}

	BMpKill ((GSPtr*) (&pVerticesNew));
	BMpKill ((GSPtr*) (&pArcsNew));
	BMpKill ((GSPtr*) (&pNurbsNew));
	BMpKill ((GSPtr*) (&pVertIndsNew));
	BMpKill ((GSPtr*) (&pEdgeIndsNew));

	return NewPolylines;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Cut( const HalfPlane2DData& cutline, GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >& result, bool* fullin /*= nullptr*/, GS::Int32* wrcode /*= nullptr*/) const
{
	try {
		GS::Array<HalfPlane2DData>	cutlines;
		cutlines.Push (cutline);

		return CutWithHalfPlanes (cutlines, result, fullin, wrcode);
		//Ha az eredmeny elfajult (egy szakasz) lenne akkor nem jon letre polygon de beallitja a degen-t
	} catch (GS::GSException& e) {
		e.Print (dbChannel);
	}
	return NewPolylines;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Strip( const HalfPlane2DData& cutline1, const HalfPlane2DData& cutline2, GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >& result, GS::Int32* wrcode /*= nullptr*/) const
{
	try {
		bool				fullin;

		GS::Array<HalfPlane2DData>	cutlines;
		cutlines.Push (cutline1);
		cutlines.Push (cutline2);

		return CutWithHalfPlanes (cutlines, result, &fullin, wrcode);
		//Ha az eredmeny elfajult (egy szakasz) lenne akkor nem jon letre polygon de beallitja a degen-t
	} catch (GS::GSException& e) {
		e.Print (dbChannel);
	}
	return NewPolylines;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Clip( const Box2DData& box, GS::Array<GS::SharedPtr<CorePolyline2D> >& result, GS::Int32* wrcode /*= nullptr*/) const
{
	try {
		bool				fullin;

		GS::Array<HalfPlane2DData>	cutlines;

		cutlines.Push (HalfPlane2DData (-1.0, 0.0, -box.xMin));
		cutlines.Push (HalfPlane2DData (1.0, 0.0, box.xMax));
		cutlines.Push (HalfPlane2DData (0.0, -1.0, -box.yMin));
		cutlines.Push (HalfPlane2DData (0.0, 1.0, box.yMax));

		return CutWithHalfPlanes (cutlines, result, &fullin, wrcode);
	} catch (GS::GSException& e) {
		e.Print (dbChannel);
	}
	return NewPolylines;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CutPiece (const CutParam& cutParam1, const CutParam& cutParam2, GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>& result) const
{
	if (cutParam1.param < -1.0)
		return ResultSameAsThis;

	if (IsEmpty ())
		return EmptyPolyline;

	if (cutParam1.edgeIndex == cutParam2.edgeIndex && fabs (cutParam1.param - cutParam2.param) < Eps)
		return EmptyPolyline;

	CutParam t1 = cutParam1;
	CutParam t2 = cutParam2;

	USize edgeNum = nVertices - 1;

	DBASSERT ( (1 <= t1.edgeIndex) &&
			  ((t2.edgeIndex > t1.edgeIndex) || (t2.edgeIndex == t1.edgeIndex && t2.param > t1.param)));

	if (t1.edgeIndex == 0.0) {
		t1.edgeIndex = 1;
		t1.param = 0.0;
	} else if (t1.edgeIndex == 1 && t1.param < 0.0) {
		t1.param = 0.0;
	}

	if (t2.edgeIndex < t1.edgeIndex || (t2.edgeIndex == t1.edgeIndex && t2.param < t1.param))
		return EmptyPolyline;

	if (GetClosed ()) {
		while (t1.edgeIndex > edgeNum) {
			t1.edgeIndex -= edgeNum;
			if (t2.edgeIndex > edgeNum)
				t2.edgeIndex -= edgeNum;
		}

		if (t1.edgeIndex > t2.edgeIndex) // ezen a ponton nVertices-1 (tLen) hozzaadasaval t2 mar biztosan nem lesz kisebb
			t2.edgeIndex += edgeNum;

		DBASSERT (t2.edgeIndex - t1.edgeIndex <= edgeNum); // ne menjen tovabb egy teljes kornel
		if (t2.edgeIndex - t1.edgeIndex > edgeNum)
			t2.edgeIndex = t1.edgeIndex + edgeNum;
	} else {
		if (t1.edgeIndex > edgeNum)
			return EmptyPolyline;
		if (t1.edgeIndex > t2.edgeIndex || (t1.edgeIndex == t2.edgeIndex && t1.param > t2.param))
			return EmptyPolyline;
		DBASSERT (t2.edgeIndex <= edgeNum); // a vegparameterrel ne menjen tul a polyline-on
		if (t2.edgeIndex > edgeNum) {
			t2.edgeIndex = edgeNum;
			t2.param = 1.0;
		}
	}

	// t goes 0..nVertices-1; indices go 1..nVertices !
	UIndex	i1, i2;		// az intervallumban levo min/max egesz ertekek
	UIndex	f1, f2;		// frame beg/end indexek, f1 <= t1; t2 <= f2
	f1 = i1 = t1.edgeIndex;
	if (t1.param > Eps)
		i1++;
	f2 = i2 = t2.edgeIndex;
	if (t2.param > Eps)
		f2++;

	if (i1 == 1 && i2 == nVertices && f2 == nVertices)
		return ResultSameAsThis;
	else if (f1 == f2)
		return EmptyPolyline;

	GS::Int32				nVerticesNew = f2 - f1 + 1;
	GS::Int32				nArcsNew = 0;
	GS::Array<Point2D>		pCoordsNew;
	pCoordsNew.SetSize (nVerticesNew + 1);

	// nArcs+1 is lehet, ha zart es egy elvagott iv egy resze az eredmeny elejere, masik resze a vegere kerul:
	GS::Array<PolyArcRec>	pArcsNew;
	pArcsNew.SetSize (nArcs + 1);

	GS::Array<Int32>		pVertIndsNew;
	if (vertexInfos.GetSize () != 0 && flags.isVertexUserData)
		pVertIndsNew.SetSize (nVerticesNew + 1);

	GS::Array<Int32>		pEdgeIndsNew;
	if (inhEdgeInfos.GetSize () != 0 && flags.isEdgeUserData)
		pEdgeIndsNew.SetSize (nVerticesNew + 1);

	pCoordsNew[0].x = 0;
	pCoordsNew[0].y = 0;
	if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
		pVertIndsNew[0] = 0;
	if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
		pEdgeIndsNew[0] = 0;
	UIndex	src = i1;
	for (UIndex f = f1; f <= f2; f++) {
		UIndex	dst = f - f1 + 1;
		if (f == f1 && f1 != i1) {
			GetCoord (t1, &pCoordsNew[dst]);
			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
				pVertIndsNew[dst] = 0;
			if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
				pEdgeIndsNew[dst] = src-1;
		} else if (f == f2 && f2 != i2) {
			CutParam	t = t2;
			if (t.edgeIndex > edgeNum) // csak zart esetben fordulhat elo
				t.edgeIndex -= edgeNum;
			GetCoord (t, &pCoordsNew[dst]);
			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
				if (IsEqualCoord (pCoordsNew[dst], vertices[src], Eps))
					pVertIndsNew[dst] = src;
				else
					pVertIndsNew[dst] = 0;
			}
			if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData)
				pEdgeIndsNew[dst] = src;
		} else {
			pCoordsNew[dst] = vertices[src];
			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData)
				pVertIndsNew[dst] = src;
			if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
				pEdgeIndsNew[dst] = (src != nVertices) ? src : 1; // src == nVertices csak zart esetben fordulhat elo
				if (dst == (UIndex) nVerticesNew && pEdgeIndsNew[dst] != pEdgeIndsNew[1])
					pEdgeIndsNew[dst] = 0; // nyilt eredmeny eseten "nincs" utolso el (nVerticesNew > 1 mindig)
			}
			src++;
			if (src > nVertices) // csak zart esetben fordulhat elo
				src = 2;
		}
	}

	bool	inverse = t2.edgeIndex > edgeNum; // csak zart esetben lehet true
	UIndex cutArcIdxOrig = 0;
	for (UIndex iArc = 1; iArc <= nArcs; iArc++) {
		PolyArcRec	arc = arcs[iArc];
		if (inverse) {
			if (arc.endIndex <= f1) {
				arc.begIndex += edgeNum;
				arc.endIndex += edgeNum;
			}
		}
		if (arc.endIndex <= f1 || arc.begIndex >= f2)
			continue;
		double	factor = 1.0;
		if (arc.begIndex == f1 && f1 != i1)
			factor -= t1.param;
		if (arc.endIndex == f2 && f2 != i2)
			factor -= (1.0 - t2.param);
		arc.arcAngle *= factor;
		arc.begIndex -= (f1 - 1);
		arc.endIndex -= (f1 - 1);
		pArcsNew[nArcsNew] = arc;
		nArcsNew++;
		if (arc.begIndex == 1)
			cutArcIdxOrig = iArc;
	}
	if (cutArcIdxOrig > 0 && f1 != i1 && f1 == i2 - edgeNum && i1 == f2 - edgeNum) {
		PolyArcRec	arc = arcs[cutArcIdxOrig];
		arc.begIndex = nVerticesNew-1;
		arc.endIndex = nVerticesNew;
		double	factor = t2.param;
		arc.arcAngle *= factor;
		pArcsNew[nArcsNew] = arc;
		nArcsNew++;
	}

	pArcsNew.SetSize (nArcsNew);

	result = new CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (*this, true);
	result->AllocateInternalData (nVerticesNew, nArcsNew, 0);
	GS::Array <const EdgeUserData*>	customInhEdgeInfo;
	result->SetInternalData (*this,
		nVerticesNew, reinterpret_cast<double*> (pCoordsNew.GetContent ()),
		nArcsNew, pArcsNew.GetContent (),
		0, nullptr,
		customInhEdgeInfo,
		pEdgeIndsNew.GetSize () > 0 ? pEdgeIndsNew.GetContent () : nullptr,
		pVertIndsNew.GetSize () > 0 ? pVertIndsNew.GetContent () : nullptr);

	result->Regularize ();

	if (result->IsEmpty ())
		return EmptyPolyline;

	return NewPolylines;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
GS::Array<CutParam> CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CutPointToCutParam (const Point2D& cutPoint) const
{
	DBCHECKPOLY_NONURBS;
	if (DBERROR (IsEmpty ()))
		throw GeometryException ("CutPointToCutParam empty polyline", __FILE__, __LINE__);

	GS::Array<UIndex> edgeIndex;
	if (DBERROR (!IsCoordOnEdge (cutPoint, edgeIndex)))
		throw GeometryException ("CutPointToCutParam not on polyline", __FILE__, __LINE__);

	GS::Array<CutParam> params (edgeIndex.GetSize ());
	for (auto it = edgeIndex.Enumerate (); it != nullptr; ++it)
		params.Push (CalcElemParam (CURVE2D_PolyLine, nullptr, nullptr, nVertices, vertices.GetContent (), nArcs, (nArcs > 0) ? (arcs.GetContent () + 1) : nullptr, &cutPoint, *it, true /*onlyOnCurve*/));
	return params;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
Point2D	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CutParamToCutPoint (const CutParam& cutParam) const	
{
	DBCHECKPOLY_NONURBS;
	if (DBERROR (IsEmpty ()))
		throw GeometryException ("CutParamToCutPoint empty polyline", __FILE__, __LINE__);

	if (DBERROR (cutParam.edgeIndex < 1 || cutParam.edgeIndex > GetEdgeNum ()))
		throw GeometryException ("CutParamToCutPoint invalid CutParam", __FILE__, __LINE__);

	Point2D c;
	GetElemCoord (cutParam, CURVE2D_PolyLine, nullptr, nullptr, nVertices, vertices.GetContent (), nullptr, nArcs, (nArcs > 0) ? (arcs.GetContent () + 1) : nullptr, &c);
	return c;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
double CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CutParamToDistance (const CutParam& cutParam) const
{
	DBCHECKPOLY_NONURBS;
	if (DBERROR (IsEmpty ()))
		throw GeometryException ("CutParamToDistance empty polyline", __FILE__, __LINE__);

	if (DBERROR (cutParam.edgeIndex < 1 || cutParam.edgeIndex > GetEdgeNum ()))
		throw GeometryException ("CutParamToDistance bad cutParam", __FILE__, __LINE__);

	double length = 0.0;
	for (UIndex i = 1; i < cutParam.edgeIndex; ++i)
		length += GetEdgeLength (i);

	length += GetEdgeLength (cutParam.edgeIndex) * cutParam.param;

	return length;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
CutParam	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::DistanceToCutParam (double distance) const
{
	DBCHECKPOLY_NONURBS;
	if (DBERROR (IsEmpty ()))
		throw GeometryException ("DistanceToCutParam empty polyline", __FILE__, __LINE__);

	if (DBERROR (distance < -Eps || distance > CalcLength () + Eps))
		throw GeometryException ("DistanceToCutParam invalid distance", __FILE__, __LINE__);

	Geometry::CutParam t;
	double length = 0.0;
	for (UIndex i = 1; i <= GetEdgeNum (); ++i) {
		const double edgeLength = GetEdgeLength (i);
		length += edgeLength;
		if (length > distance - Eps) {
			t.edgeIndex = i;
			t.param = (edgeLength - (length - distance)) / edgeLength;
			if (t.param < 0.0)
				t.param = 0.0;
			if  (t.param > 1.0)
				t.param = 1.0;
			break;
		}
	}

	return t;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
template <class EdgeUserDataComparator>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::RemoveSameDirEdgesOnlyWithSameUserData (const EdgeUserDataComparator& comparator)
{
	RemoveSameDirEdge<EdgeUserDataComparator, true> (comparator);
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::RemoveSameDirEdgesOnlyWithSameUserData ()
{
	RemoveSameDirEdge<std::equal_to<EdgeUserData>, true> (std::equal_to<EdgeUserData> ());
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylinePointPosition	CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PointPosition (const Point2D& sidePoint) const
{
	DBCHECKPOLY_NONURBS;
	double	minDistance = DBL_MAX;
	GS::UInt32	minDIndex = MaxUInt32;
	Vector2D	tangent, vec2;
	bool	vertexNeighbouring = false;
	for (GS::UInt32 i = 1; i < nVertices; i++) {
		UIndex arcIndex = GetInternalArcIdx (i);
		double	arcAngle = arcIndex == 0 ? 0.0 : arcs[arcIndex].arcAngle;

		const Point2D&	begC = vertices[i];
		const Point2D&	endC = vertices[i + 1];

		if (Geometry::IsEqualCoord (begC, endC, Eps))
			continue;

		double	begDist = Dist (sidePoint, begC);
		double	endDist = Dist (sidePoint, endC);
		if (begDist < minDistance) {
			minDistance = begDist;
			minDIndex = i;
			vertexNeighbouring = true;
		}
		if (endDist < minDistance) {
			minDistance = endDist;
			minDIndex = i + 1;
			vertexNeighbouring = true;
		}

		if (arcIndex == 0) {
			Sector s;
			s.c1 = begC;
			s.c2 = endC;
			double dist = DistCoordSector (sidePoint, s);
			if (dist < minDistance) {
				Point2D	projCoord = CoordProjSector (sidePoint, s);
				Vector2D	edgeVector = endC - begC;
				if (MulsVectors (projCoord - begC, edgeVector) > - EPS &&
					MulsVectors (endC - projCoord, edgeVector) > - EPS) {
					minDistance = dist;
					minDIndex = i;
					tangent = edgeVector;
					vec2 = sidePoint - projCoord;
					vertexNeighbouring = false;
				}
			}
		} else {
			Point2D origo;
			ArcGetOrigo (&begC, &endC, arcAngle, &origo);

			//get distance from clickCoord and the arc
			double radius = Dist (begC, origo);
			Circle2D c (origo, radius);
			Sector line, res;
			line.c1 = sidePoint;
			line.c2 = origo;
			XCircleLine (&c, &line, &res);

			double angleBeg = ComputeFi (origo, begC);
			double angleEnd = angleBeg + arcAngle;
			if (arcAngle < 0.0) {
				double	tmp = angleBeg;
				angleBeg = angleEnd;
				angleEnd = tmp;
			}

			double angleX1 = ComputeFi (origo, res.c1) - angleBeg;
			double angleX2 = ComputeFi (origo, res.c2) - angleBeg;
			while (angleX1 < 0.0)
				angleX1 += 2.0 * PI;
			while (angleX2 < 0.0)
				angleX2 += 2.0 * PI;
			while (angleX1 > 2.0 * PI)
				angleX1 -= 2.0 * PI;
			while (angleX2 > 2.0 * PI)
				angleX2 -= 2.0 * PI;
			angleEnd -= angleBeg;
			while (angleEnd < 0.0)
				angleEnd += 2.0 * PI;
			while (angleEnd > 2.0 * PI)
				angleEnd -= 2.0 * PI;

			if (angleX1 < angleEnd + RadEps) {
				double dist = Dist (sidePoint, res.c1);
				if (dist < minDistance) {
					minDistance = dist;
					minDIndex = i;
					Vector2D	radiusVector = res.c1 - origo;
					// rotate the radiusVector by +90 degree
					tangent.x = - radiusVector.y;
					tangent.y =   radiusVector.x;
					if (arcAngle < 0.0) {
						tangent.x = - tangent.x;
						tangent.y = - tangent.y;
					}
					vec2 = sidePoint - res.c1;
					vertexNeighbouring = false;
				}
			}
			if (angleX2 <= angleEnd + RadEps) {
				double dist = Dist (sidePoint, res.c2);
				if (dist < minDistance) {
					minDistance = dist;
					minDIndex = i;
					Vector2D	radiusVector = res.c2 - origo;
					// rotate the radiusVector by +90 degree
					tangent.x = - radiusVector.y;
					tangent.y =   radiusVector.x;
					if (arcAngle < 0.0) {
						tangent.x = - tangent.x;
						tangent.y = - tangent.y;
					}
					vec2 = sidePoint - res.c2;
					vertexNeighbouring = false;
				}
			}
		}
	}

	if (fabs (minDistance) < Eps)
		return PointOnPolyline;

	PolylinePointPosition	retVal = PointOnRightSide;
	if (vertexNeighbouring) {
		GS::UInt32	prevEdgeInd = (minDIndex == 1) ? 0 : minDIndex - 1;
		GS::UInt32	nextEdgeInd = (minDIndex == nVertices) ? 0 : minDIndex;
		UIndex	arcPrevIndex = nArcs > 0 && prevEdgeInd != 0 ? GetInternalArcIdx (prevEdgeInd) : 0;
		UIndex	arcNextIndex = nArcs > 0 && nextEdgeInd != 0 ? GetInternalArcIdx (nextEdgeInd) : 0;

		const Point2D& vertex = vertices[minDIndex];
		if (arcPrevIndex == 0 && arcNextIndex == 0) {
			Point2D	prevCoord	= (prevEdgeInd == 0) ? vertex + (vertex - vertices[nextEdgeInd + 1]) : vertices[prevEdgeInd];
			tangent = prevCoord - vertex;
		} else {
			UIndex	currArcIndex = (arcPrevIndex == 0) ? arcNextIndex : arcPrevIndex;
			double	arcAngle = arcs[currArcIndex].arcAngle;
			const Point2D& begC = vertices[arcs[currArcIndex].begIndex];
			const Point2D& endC = vertices[arcs[currArcIndex].endIndex];

			Point2D	origo;
			ArcGetOrigo (&begC, &endC, arcAngle, &origo);
			Vector2D	radiusVector = origo - begC;
			radiusVector = UnitVector (radiusVector);

			// rotate the radiusVector by +90 degree
			tangent.x = - radiusVector.y;
			tangent.y =   radiusVector.x;
			if (arcAngle < 0.0) {
				tangent.x = - tangent.x;
				tangent.y = - tangent.y;
			}
		}
		if (arcPrevIndex == 0 && arcNextIndex == 0) {
			Point2D	nextCoord		= (nextEdgeInd == 0) ? vertex + (vertex - vertices[prevEdgeInd]) : vertices[nextEdgeInd + 1];
			vec2	= nextCoord - vertex;
		} else {
			UIndex	currArcIndex = (arcNextIndex == 0) ? arcPrevIndex : arcNextIndex;
			double	arcAngle = arcs[currArcIndex].arcAngle;
			const Point2D& begC = vertices[arcs[currArcIndex].begIndex];
			const Point2D& endC = vertices[arcs[currArcIndex].endIndex];

			Point2D	origo;
			ArcGetOrigo (&begC, &endC, arcAngle, &origo);
			Vector2D	radiusVector = origo - endC;
			radiusVector = UnitVector (radiusVector);

			// rotate the radiusVector by -90 degree
			vec2.x =   radiusVector.y;
			vec2.y = - radiusVector.x;
			if (arcAngle < 0.0) {
				vec2.x = - vec2.x;
				vec2.y = - vec2.y;
			}
		}
		tangent = UnitVector (tangent);
		vec2 = UnitVector (vec2);
		Vector2D	clickVector = UnitVector (sidePoint - vertex);

		double	positionAngle = GetVectorsRelAngle (tangent, clickVector);
		double	edgeAngle = GetVectorsRelAngle (tangent, vec2);
		if (positionAngle < 0.0)
			positionAngle += 2.0 * PI;
		if (edgeAngle < 0.0)
			edgeAngle += 2.0 * PI;

		if (positionAngle < 0.0 || positionAngle > edgeAngle)
			retVal = PointOnLeftSide;
	} else {
		if ((tangent ^ vec2) > 0.0)
			retVal = PointOnLeftSide;
	}
	return retVal;
}


template <class VertexUserData, class EdgeUserData, class PolygonUserData>
void CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Print (GS::OChannel& oc) const
{
	/*if (PGGetDebugFlagsExt () == 0) {
		return;
	}*/

	oc << "\n!***-----------------***\n\n";
	oc << "!CorePolyline2D at " << this << "\n";

	oc << "!\tBounding Box: [ ";
	oc << " xMin: " << boundBox.xMin;
	oc << " yMin: " << boundBox.yMin;
	oc << " xMax: " << boundBox.xMax;
	oc << " yMax: " << boundBox.yMax;
	oc << "]\n";

	oc << "\t Vertices: " << nVertices << "\t";
	oc << "\t Arcs:	" << nArcs << "\n";


	oc << "POLY2_ " << nVertices + 2 * nArcs << " , 7";

	UIndex iFirstVertex = 1;
	UIndex iVertex;
	oc << ",\n";
	for (iVertex = iFirstVertex; iVertex < nVertices; iVertex++) {
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
		if (GetInternalNurbsIdx (iVertex) != MaxUInt32)
			oc << "! This edge is a NURBS\n";
	}
	if (!vertices.IsEmpty ()) // sima "if (!IsEmpty ())" is jo ha konzisztens a polyline
		oc << vertices[iVertex].x << ",  " << vertices[iVertex].y << ",  -1";

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
	} else {
		oc << "-\n!\t\t v\te\tc\n";
	}
	for (iVertex = iFirstVertex; iVertex < nVertices; iVertex++) {
		if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
			const VertexUserData* id = GetVertexUserData (iVertex);
			if (id != nullptr)
//				oc << "![" << iVertex <<"]\t" << id->Get ();
				id->Print (oc);
			else
				oc << "![" << iVertex <<"]\t-";
		} else
			oc << "![" << iVertex <<"]\t-";
		if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
			const EdgeUserData* id = GetEdgeUserData (iVertex);
			if (id != nullptr)
//				oc << "\t" << id->Get () << "\n";
				id->Print (oc);
			else
				oc << "\t-\n";
		} else
			oc << "\t-\n";
	}
	if (!vertices.IsEmpty ()) { // sima "if (!IsEmpty ())" is jo ha konzisztens a polyline
		if (GetClosed ()) {
			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
				const VertexUserData* id = GetVertexUserData (iFirstVertex);
				if (id != nullptr)
//					oc << "![" << iVertex <<"]\t" << id->Get ();
					id->Print (oc);
				else
					oc << "![" << iVertex <<"]\t-";
			} else
				oc << "![" << iVertex <<"]\t-";
			if (inhEdgeInfos.GetSize() != 0 && flags.isEdgeUserData) {
				const EdgeUserData* id = GetEdgeUserData (iFirstVertex);
				if (id != nullptr)
//					oc << "\t" << id->Get () << "\n";
					id->Print (oc);
				else
					oc << "\t-\n";
			} else
				oc << "\t-\n";
		} else {
			if (vertexInfos.GetSize() != 0 && flags.isVertexUserData) {
				const VertexUserData* id = reinterpret_cast<const VertexUserData*> (GetVertexUserData (iVertex));
				if (id != nullptr)
//					oc << "![" << iVertex <<"]\t" << id->Get ();
					id->Print (oc);
				else
					oc << "![" << iVertex <<"]\t-";
			} else
				oc << "![" << iVertex <<"]\t-";
			oc << "\t-\n";
		}
	}
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CheckSizes (void) const
{
	/* check for geometric data */
	if (nVertices < 2) {
		DBPRINTF ("CorePolyline2D::Check: polygon has wrong vertices number!\n");
		return false;
	}
	if (vertices.GetSize () != (nVertices + 1)) {
		DBPRINTF ("CorePolyline2D::Check: polygon has wrong vertices!\n");
		return false;
	}
	if (nArcs >= nVertices) {
		DBPRINTF ("CorePolyline2D::Check: polygon has wrong arcs number!\n");
		return false;
	}
	if (nArcs != 0 && arcs.GetSize () != nArcs + 1) {
		DBPRINTF ("CorePolyline2D::Check: polygon has wrong arcs!\n");
		return false;
	}
	if (nArcs == 0 && arcs.GetSize () != 1) {
		DBPRINTF ("CorePolyline2D::Check: polygon has wrong arcs!\n");
		return false;
	}

	if (nNurbs >= nVertices) {
		DBPRINTF ("CorePolyline2D::Check: polygon has wrong nurbs number!\n");
		return false;
	}
	if (nNurbs != 0 && nurbs.GetSize () != nNurbs) {
		DBPRINTF ("CorePolyline2D::Check: polygon has wrong nurbs!\n");
		return false;
	}
	if (nNurbs == 0 && nurbs.GetSize () != 0) {
		DBPRINTF ("CorePolyline2D::Check: polygon has wrong nurbs!\n");
		return false;
	}

	if (GetClosed () && !Geometry::IsEqualCoord (vertices[1], vertices[nVertices], Eps)) {
		DBPRINTF ("CorePolyline2D::Check: Internal data error at closed polyline !\n");
		return false;
	}

	if (flags.isVertexUserData) {
		if (vertexInfos.GetSize() == 0) {
			DBPRINTF ("CorePolyline2D::Check: polygon has wrong vertexInfos!\n");
			return false;
		}
		if (vertexInfos.GetSize() < (nVertices + 1)) {
			DBPRINTF ("CorePolyline2D::Check: polygon has wrong vertexInfos handle!\n");
			return false;
		}
	} else {
		if (vertexInfos.GetSize() != 0) {
			DBPRINTF ("CorePolyline2D::Check: polygon has wrong vertexInfos!");
			return false;
		}
	}
	if (flags.isEdgeUserData) {
		if (inhEdgeInfos.GetSize() == 0) {
			DBPRINTF ("CorePolyline2D::Check: polygon has wrong inhEdgeInfos!");
			return false;
		}
		if (inhEdgeInfos.GetSize() < (nVertices + 1)) {
			DBPRINTF ("CorePolyline2D::Check: polygon has wrong inhEdgeInfos handle!\n");
			return false;
		}
	} else {
		if (inhEdgeInfos.GetSize() != 0 /*inhEdgeInfos != nullptr*/) {
			DBPRINTF ("CorePolyline2D::Check: polygon has wrong inhEdgeInfos!\n");
			return false;
		}
	}
	if (flags.isPolygonUserData) {
		if (inhPolygonInfo.GetSize() != 1) {
			DBPRINTF ("CorePolyline2D::Check: polygon has wrong inhPolygonInfo!\n");
			return false;
		}
	} else {
		if (inhPolygonInfo.GetSize() != 0) {
			DBPRINTF ("CorePolyline2D::Check: polygon has wrong inhPolygonInfo!\n");
			return false;
		}
	}
	return true;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CheckVertices (PolyCheckFlags checkFlags, PolyCheckFlags* errorType, double coordUpperRange) const
{
	//check the contents of vertices
	if ((checkFlags & PolyCheckFlags_Zero0thElements) != 0) {
		if (vertices[0].x != 0.0 ||
			vertices[0].y != 0.0)
		{
			DBPRINTF ("CorePolyline2D::Check: 0. vertex!\n");
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
				DBPRINTF ("CorePolyline2D::Check: invalid coord value!\n");
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
				DBPRINTF ("CorePolyline2D::Check: invalid coord value!\n");
				if (errorType != nullptr)
					*errorType = PolyCheckFlags_DenormalDoubles;
				return false;
			}
		}
	}
	if ((checkFlags & PolyCheckFlags_CoordRange) != 0) {
		for (UIndex vertexIdx = 1; vertexIdx <= nVertices; ++vertexIdx) {
			if (!CheckCoord (vertices[vertexIdx], coordUpperRange)) {
				DBPRINTF ("CorePolyline2D::Check: coord value out of range!\n");
				if (errorType != nullptr)
					*errorType = PolyCheckFlags_CoordRange;
				return false;
			}
		}
	}
	return true;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CheckArcs (PolyCheckFlags checkFlags /*= PolyCheckFlags_All_Polyline*/, PolyCheckFlags* errorType /*= nullptr*/) const
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
			DBPRINTF ("CorePolyline2D::Check: arcs have false begIndex indices");
			return false;
		}
		if (endIndex < 2 || endIndex > nVertices) {
			DBPRINTF ("CorePolyline2D::Check: arcs have false endIndex indices");
			return false;
		}
		if (endIndex != begIndex + 1) {
			DBPRINTF ("CorePolyline2D::Check: Invalid arc");
			return false;
		}
		if ((checkFlags & PolyCheckFlags_TooSmallArcs) != 0) {
			if (fabs (arcs[iArc].arcAngle) < RadEps) {
				DBPRINTF ("Invalid arcAngle\n");
				if (errorType != nullptr)
					*errorType = PolyCheckFlags_TooSmallArcs;
				return false;
			}
			if (!ArcGetOrigo (&vertices[begIndex], &vertices[endIndex], arcs[iArc].arcAngle, &dummyOrigin)) {
				DBPRINTF ("Failed to calculate arc origin\n");
				if (errorType != nullptr)
					*errorType = PolyCheckFlags_TooSmallArcs;
				return false;
			}
		}
	}
	return true;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::CheckNurbs () const
{
	for (GS::UInt32 i = 0; i < nNurbs; i++) {
		UIndex begIndex = nurbs[i].begIndex;
		UIndex endIndex = begIndex + 1;

		if (begIndex < 1 || begIndex > nVertices - 1) {
			DBPRINTF ("CorePolyline2D::Check: nurbs have false begIndex indices");
			return false;
		}

		if (endIndex < 2 || endIndex > nVertices) {
			DBPRINTF ("CorePolyline2D::Check: nurbs have false endIndex indices");
			return false;
		}

		if (!IsNear (vertices[begIndex], nurbs[i].nurbs.GetControlPoint (0), Eps)) {
			DBPRINTF ("CorePolyline2D::Check: nurbs's first controlpoint is not the polyline's previous vertex");
			return false;
		}

		if (!IsNear (vertices[endIndex], nurbs[i].nurbs.GetControlPoint (nurbs[i].nurbs.GetControlPointCount () - 1), Eps)) {
			DBPRINTF ("CorePolyline2D::Check: nurbs's last controlpoint is not the polyline's next vertex");
			return false;
		}

		if (!nurbs[i].nurbs.Check ()) {
			DBPRINTF ("Nurbs is invalid");
			return false;
		}

		for (UIndex iArc = 1; iArc <= nArcs; ++iArc) {
			if (begIndex == arcs[iArc].begIndex) {
				DBPRINTF ("Nurbs and arc on same edge");
				return false;
			}
		}
	}
	
	return true;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
bool CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Check (PolyCheckFlags checkFlags, PolyCheckFlags* errorType, double coordUpperRange) const
{
	DBASSERT ((checkFlags & PolyCheckFlags_CoordRange) == 0 || (IsPositive(coordUpperRange) && (checkFlags & PolyCheckFlags_InvalidDoubles) != 0));
	DBASSERT ((checkFlags & PolyCheckFlags_ContourHasFewVertices) == 0);

	if (errorType != nullptr)
		*errorType = static_cast<PolyCheckFlags>(0);

	DBCHECKPOLY_MEMORY;

	if (nVertices			== 0 &&
		nArcs				== 0 &&
		vertices.GetSize ()	== 0 &&
		arcs.GetSize ()		== 0) {
			return true;
	}

	DBASSERT (nVertices < 100000); //Ez nem hiba de azert gyanus

	if (!CheckSizes ())
		return false;

	if (!CheckVertices (checkFlags, errorType, coordUpperRange))
		return false;

	if (!CheckArcs (checkFlags, errorType))
		return false;

	if (!CheckNurbs ())
		return false;

#ifdef DEBUVERS
	Box2DData calcedBox;
	calcedBox = CalcBoundBox ();
	if (!IsEqualBox (calcedBox, boundBox, Eps)) {
		DBPRINTF ("CorePolyline2D::Check: Invalid bounding box");
		return false;
	}
#endif
	return true;
}

template <class VertexUserData, class EdgeUserData, class PolygonUserData>
PolyRepairResult CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Repair (PolyCheckFlags repairType)
{
	DBCHECKPOLY_ONEREFTOTHIS;

	DBASSERT ((repairType & (repairType - 1)) == 0);	// Csak egy bit! http://en.wikipedia.org/wiki/Power_of_two#Fast_algorithm_to_check_if_a_positive_number_is_a_power_of_two

	PolyRepairResult result;
	result.succeeded = result.modified = false;

	switch (repairType) {
		case PolyCheckFlags_Zero0thElements:
			vertices[0].Set(0.0, 0.0);
			arcs[0].begIndex = 0;
			arcs[0].endIndex = 0;
			arcs[0].arcAngle = 0.0;
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
				boundBox = CalcBoundBox ();
			result.succeeded = true;
			return result;
		case PolyCheckFlags_CoordRange:
			return result;
		case PolyCheckFlags_ContourHasFewVertices:
		case PolyCheckFlags_TooSmallArcs:
		case PolyCheckFlags_All_Polyline:
		case PolyCheckFlags_All_Polygon:
		default:
			DBBREAK ();
			return result;
	}
}

}	// namespace Geometry

#endif //GEOMETRY_COREPOLYLINE2D_HPP
