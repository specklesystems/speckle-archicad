// MeshBrep calculation templates
#ifndef MESHBREPCALCULATIONS_HPP
#define MESHBREPCALCULATIONS_HPP
#pragma once

#include "MeshBrepAccessors.hpp"

namespace Brep {

template<typename MeshBrepT>
Box3D MeshCalculateTransformedTightBounds (const MeshBrepT& meshBrep, const TRANMAT& trafo, const GS::Array<UIndex>& omittedVertices = GS::Array<UIndex> ())
{
	Box3D bounds;

	bounds.xMin = bounds.yMin = bounds.zMin = 1;
	bounds.xMax = bounds.yMax = bounds.zMax = -1;

	bool first = true;
	for (ULong i = 0; i < meshBrep.GetVertexCount (); i++) {
		if (omittedVertices.Contains (i)) {
			continue;
		}

		const Coord3D vertPos = GetMeshTransformedVertex (meshBrep, i, trafo);

		if (first) {
			first = false;
			bounds.xMin = bounds.xMax = vertPos.x;
			bounds.yMin = bounds.yMax = vertPos.y;
			bounds.zMin = bounds.zMax = vertPos.z;
		} else {
			bounds.xMin = GS::Min (bounds.xMin, vertPos.x);
			bounds.xMax = GS::Max (bounds.xMax, vertPos.x);
			bounds.yMin = GS::Min (bounds.yMin, vertPos.y);
			bounds.yMax = GS::Max (bounds.yMax, vertPos.y);
			bounds.zMin = GS::Min (bounds.zMin, vertPos.z);
			bounds.zMax = GS::Max (bounds.zMax, vertPos.z);
		}
	}

	return bounds;
}


template<typename MeshBrepT>
F_Box3D MeshCalculateTransformedBounds (const MeshBrepT& meshBrep, const TRANMAT& trafo, const GS::Array<UIndex>& omittedVertices = GS::Array<UIndex> ())
{
	return Geometry::ToF_Box3D (MeshCalculateTransformedTightBounds (meshBrep, trafo, omittedVertices));
}


template<typename MeshBrepT>
void MeshGetAllPolygonBounds (GS::Array<Box3D>& allPolygonBounds, const MeshBrepT& meshBrep, const TRANMAT& trafo)
{
	const USize PolygonCount = meshBrep.GetPolygonCount ();
	allPolygonBounds.Clear ();
	if (PolygonCount < 1) {
		return;
	}
	allPolygonBounds.SetCapacity (PolygonCount);

	const USize VertexCount = meshBrep.GetVertexCount ();
	GS::Array<MeshBrep::Vertex> transformedBodyVertices (VertexCount);
	for (UIndex vertexIndex = 0; vertexIndex < VertexCount; ++vertexIndex) {
		transformedBodyVertices.Push (Brep::GetMeshTransformedVertex (meshBrep, vertexIndex, trafo));
	}

	const auto GetOnePolygonBounds = [&] (Box3D& box, UIndex polygonIndex) {
		Geometry::InitBox3D (&box);

		const MeshBrep::Polygon& polygon = meshBrep.GetConstPolygon (polygonIndex);
		const USize edgeCnt = polygon.GetEdgeCount ();
		DBASSERT (edgeCnt > 0);
		for (UIndex i = 0; i < edgeCnt; ++i) {
			const Int32 vertexIndex = Brep::GetMeshVertexIndexFromPolyEdgeIndex (meshBrep, polygon.fpedg + i);
			if (vertexIndex < 0) {	// hole marker
				continue; // Continue processing the holes. Degenerate holes might be outside the main contour.
			}

			Geometry::Box3DBound (&box, &transformedBodyVertices[vertexIndex]);
		}

		return box;
	};

	for (UIndex polygonIndex = 0; polygonIndex < PolygonCount; ++polygonIndex) {
		allPolygonBounds.PushNew ();
		GetOnePolygonBounds (allPolygonBounds.GetLast (), polygonIndex);
	}
}


} // namespace Brep

#endif // MESHBREPCALCULATIONS_HPP