// MeshBrep data accessors
#ifndef MESHBREPACCESSORS_HPP
#define MESHBREPACCESSORS_HPP
#pragma once

#include "MeshBrep.hpp"

//from Geometry
#include "TM.h"
#include "Plane3DData.h"

namespace Brep {

template <typename MeshBrepT>
Int32					GetMeshVertexIndexFromPolyEdgeIndex (const MeshBrepT& meshBrep, Int32 pedgIdx);

template <typename MeshBrepT>
MeshBrep::Vertex		GetMeshTransformedVertex (const MeshBrepT& meshBrep, UIndex vertexIndex);

template<typename MeshBrepT>
MeshBrep::PolyNormal	GetMeshPolygonNormalFromSignedIndex (const MeshBrepT& meshBrep, Int32 ivect, const TRANMAT& trafo);

template<typename MeshBrepT>
MeshBrep::PolyNormal	GetMeshPolygonNormalVector (const MeshBrepT& meshBrep, UIndex polygonIndex, const TRANMAT& trafo = Geometry::IdentityTranMat);

template<typename MeshBrepT>
MeshBrep::PolyEdge 		GetMeshPolygonPolyEdge (const MeshBrepT& meshBrep, UIndex polygonIndex, UInt32 edgeIdx);

template<typename MeshBrepT>
MeshBrep::Edge			GetMeshPolygonOrientedEdge (const MeshBrepT& meshBrep, UIndex polygonIndex, UInt32 edgeIdx);

template<typename MeshBrepT>
MeshBrep::Vertex		GetMeshPolygonVertex (const MeshBrepT& meshBrep, UIndex polygonIndex, UInt32 vertexIdx, bool* holeMarker, const TRANMAT& trafo = Geometry::IdentityTranMat);

template<typename MeshBrepT>
UInt32					GetMeshPolygonHoleCount (const MeshBrepT& meshBrep, UIndex polygonIndex);

template<typename MeshBrepT>
Int32					GetMeshPolygonContourNextIPedg (const MeshBrepT& meshBrep, UIndex polygonIndex, Int32 ipedg);

template<typename MeshBrepT>
Int32					GetMeshPolygonContourPrevIPedg (const MeshBrepT& meshBrep, UIndex polygonIndex, Int32 ipedg);

template<typename MeshBrepT>
Box3D					GetMeshPolygonBounds (const MeshBrepT& meshBrep, UIndex polygonIndex, const TRANMAT& trafo = Geometry::IdentityTranMat);

template<typename MeshBrepT>
PlaneEq					GetMeshPolygonPlane (const MeshBrepT& meshBrep, UIndex polygonIndex, const TRANMAT& trafo);


template <typename MeshBrepT>
Int32	GetMeshVertexIndexFromPolyEdgeIndex (const MeshBrepT& meshBrep, Int32 pedgIdx)
{
	MeshBrep::PolyEdge apedg = meshBrep.GetConstPolyEdge (pedgIdx);

	if (apedg == 0) {
		return -1;
	}

	const UIndex iedge = GS::Abs (apedg) - 1;
	const MeshBrep::Edge& aedge = meshBrep.GetConstEdge (iedge);
	Int32 ivert = -1;

	if (apedg > 0) {
		ivert = aedge.vert1;
	} else {
		DBASSERT (apedg < 0);
		ivert = aedge.vert2;
	}
	DBASSERT (ivert >= 0 && ivert < static_cast<Int32> (meshBrep.GetVertexCount ()));

	return ivert;
}


template <typename MeshBrepT>
MeshBrep::Vertex GetMeshTransformedVertex (const MeshBrepT& meshBrep, UIndex vertexIndex, const TRANMAT& trafo)
{
	MeshBrep::Vertex vertex = meshBrep.GetConstVertex (vertexIndex);
	return Geometry::TransformPoint (trafo, vertex);
}


template<typename MeshBrepT>
MeshBrep::PolyNormal	GetMeshPolygonNormalFromSignedIndex (const MeshBrepT& meshBrep, Int32 ivect, const TRANMAT& trafo)
{
	UInt32 normalIndex = GS::Abs (ivect) - 1;
	if (normalIndex >= meshBrep.GetPolyNormalCount ()) {
		throw GS::IllegalArgumentException ();
	}	
	MeshBrep::PolyNormal normal = meshBrep.GetConstPolyNormal (normalIndex);
	if (ivect < 0) {
		normal = -normal;
	}
	return Geometry::TransformUnitNormalVector (trafo, normal);
}


template<typename MeshBrepT>
MeshBrep::PolyNormal GetMeshPolygonNormalVector (const MeshBrepT& meshBrep, UIndex polygonIndex, const TRANMAT& trafo)
{
	const Int32 ivect = meshBrep.GetConstPolygon (polygonIndex).ivect;
	return GetMeshPolygonNormalFromSignedIndex (meshBrep, ivect, trafo);
}


template<typename MeshBrepT>
MeshBrep::PolyEdge 	GetMeshPolygonPolyEdge (const MeshBrepT& meshBrep, UIndex polygonIndex, UInt32 edgeIdx)
{
	return meshBrep.GetConstPolyEdge (meshBrep.GetConstPolygon (polygonIndex).fpedg + edgeIdx);
}


template<typename MeshBrepT>
MeshBrep::Edge	GetMeshPolygonOrientedEdge (const MeshBrepT& meshBrep, UIndex polygonIndex, UInt32 edgeIdx)
{
	Int32 pedg = GetMeshPolygonPolyEdge (meshBrep, polygonIndex, edgeIdx);
	bool foreDir = (pedg > 0);
	UInt32 edgeIdxInBody = GS::Abs (pedg) - 1;

	MeshBrep::Edge edge = meshBrep.GetConstEdge (edgeIdxInBody);

	if (!foreDir) {
		GS::Swap (edge.vert1, edge.vert2);
	}
	return edge;
}


template<typename MeshBrepT>
MeshBrep::Vertex GetMeshPolygonVertex (const MeshBrepT& meshBrep, UIndex polygonIndex, UInt32 vertexIdx, bool* holeMarker, const TRANMAT& trafo /*= Geometry::IdentityTranMat*/)
{	
	const Int32 bodyVertexIdx = GetMeshVertexIndexFromPolyEdgeIndex (meshBrep, meshBrep.GetConstPolygon (polygonIndex).fpedg + vertexIdx);
	if (bodyVertexIdx < 0) {
		*holeMarker = true;
		return MeshBrep::Vertex ();
	} else {
		*holeMarker = false;
		return GetMeshTransformedVertex (meshBrep, bodyVertexIdx, trafo);
	}
}


template<typename MeshBrepT>
UInt32 GetMeshPolygonHoleCount (const MeshBrepT& meshBrep, UIndex polygonIndex)
{
	const MeshBrep::Polygon& polygon = meshBrep.GetConstPolygon (polygonIndex);
	UInt32 nHoles = 0;
	for (Int32 ipedg = polygon.fpedg; ipedg <= polygon.lpedg; ++ipedg) {
		const MeshBrep::PolyEdge pedg = meshBrep.GetConstPolyEdge (ipedg);
		if (pedg == 0) {
			++nHoles;
		}
	}
	return nHoles;
}


template<typename MeshBrepT>
Int32	GetMeshPolygonContourNextIPedg (const MeshBrepT& meshBrep, UIndex polygonIndex, Int32 ipedg)
{
	const MeshBrep::Polygon& polygon = meshBrep.GetConstPolygon (polygonIndex);
	DBASSERT (polygon.fpedg <= ipedg && polygon.lpedg >= ipedg);
	if (ipedg == polygon.lpedg || meshBrep.GetConstPolyEdge (ipedg + 1) == 0) {
		while (ipedg > polygon.fpedg && meshBrep.GetConstPolyEdge (ipedg - 1) != 0) {
			--ipedg;
		}
		return ipedg;
	} else {
		return ipedg + 1;
	}
}


template<typename MeshBrepT>
Int32	GetMeshPolygonContourPrevIPedg (const MeshBrepT& meshBrep, UIndex polygonIndex, Int32 ipedg)
{
	const MeshBrep::Polygon& polygon = meshBrep.GetConstPolygon (polygonIndex);
	DBASSERT (polygon.fpedg <= ipedg && polygon.lpedg >= ipedg);
	if (ipedg == polygon.fpedg || meshBrep.GetConstPolyEdge (ipedg - 1) == 0) {
		while (ipedg < polygon.lpedg && meshBrep.GetConstPolyEdge (ipedg + 1) != 0) {
			++ipedg;
		}
		return ipedg;
	} else {
		return ipedg - 1;
	}
}

template<typename MeshBrepT>
Box3D	GetMeshPolygonBounds (const MeshBrepT& meshBrep, UIndex polygonIndex, const TRANMAT& trafo /*= Geometry::IdentityTranMat*/)
{
	bool holeMarker;
	Coord3D c = Brep::GetMeshPolygonVertex (meshBrep, polygonIndex, 0, &holeMarker, trafo);	
	Box3D box;
	Geometry::SetBox3D (&box, c.x, c.y, c.z, c.x, c.y, c.z);

	ULong edgeCnt = meshBrep.GetConstPolygon (polygonIndex).GetEdgeCount ();
	for (ULong i = 1; i < edgeCnt; ++i) {
		c = Brep::GetMeshPolygonVertex (meshBrep, polygonIndex, i, &holeMarker, trafo);
		if (holeMarker) {
			continue; // Continue processing the holes. Degenerate holes might be outside the main contour.
		}
		Geometry::Box3DBound (&box, &c);			
	}

	return box;
}


template<typename MeshBrepT>
PlaneEq	GetMeshPolygonPlane (const MeshBrepT& meshBrep, UIndex polygonIndex, const TRANMAT& trafo)
{
	bool holeMarker = true;
	const MeshBrep::Vertex vertPos = GetMeshPolygonVertex (meshBrep, polygonIndex, 0, &holeMarker, trafo);
	DBASSERT (!holeMarker);

	const MeshBrep::PolyNormal polyNormal = GetMeshPolygonNormalVector (meshBrep, polygonIndex, trafo);
	return PlaneEq (polyNormal, vertPos);
}


} // namespace Brep

#endif // MESHBREPACCESSORS_HPP