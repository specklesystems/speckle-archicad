#ifndef ModelNurbsEdge_h__
#define ModelNurbsEdge_h__

#pragma once

#include "ModelNurbsElementWithTolerance.hpp"

namespace ModelerAPI
{

class NurbsEdge : public NurbsElementWithTolerance
{
	// A part of boundary of one or two faces, or a wire edge
	// Its geometry is a connected part of a 3d nurbs curve
	// It is connected to a face by a trim
private:
	Int32				beginVertexIndex;	// negative (invalid) for ring edge
	Int32				endVertexIndex;		// negative (invalid) for ring edge; or may equal to beginVertexIndex for loop edge
	GS::Array<UInt32>	trimIndices;		// any number of trims (and therefore face) is allowed, order is irrelevant
	UInt32				curve3DIndex;		// geometry of edge is part of this curve
	Interval			curveSubDomain;		// 3d geometry of edge is part of the curve determined by this subdomain in the domain of curve

public:
	NurbsEdge(Int32 beginVertexIndex,
		Int32 endVertexIndex,
		GS::Array<UInt32> trimIndices,
		UInt32 curve3DIndex,
		Interval curveSubDomain,
		double tolerance) : beginVertexIndex(beginVertexIndex), endVertexIndex(endVertexIndex), trimIndices(trimIndices), curve3DIndex(curve3DIndex), curveSubDomain(curveSubDomain), NurbsElementWithTolerance (tolerance)
	{}


	bool				IsLoopEdge			()				const { return (beginVertexIndex == endVertexIndex) && (beginVertexIndex >= 0); }
	bool				IsRingEdge			()				const { return (beginVertexIndex < 0 && endVertexIndex < 0); }
	bool				IsRegularEdge		()				const { return !IsLoopEdge () && !IsRingEdge (); }
	bool				IsWire				()				const { return (trimIndices.GetSize () == 0); }
	bool				IsSurfaceBoundary	()				const { return (trimIndices.GetSize () == 1); }
	bool				Is2Manifold			()				const { return (trimIndices.GetSize () == 2); }
	bool				IsNon2Manifold		()				const { return (trimIndices.GetSize () > 2); }
	Int32				GetBeginVertexIndex ()				const { return beginVertexIndex; }
	Int32				GetEndVertexIndex	()				const { return endVertexIndex; }
	UInt32				GetTrimIndexCount	()				const { return trimIndices.GetSize (); }
	UInt32				GetTrimIndex		(UInt32 index)	const { return trimIndices[index-1]; }
	UInt32				GetCurve3DIndex		()				const { return curve3DIndex; }
	Interval			GetCurveSubdomain	()				const { return curveSubDomain; }
};

} // namespace ModelerAPI

#endif // ModelNurbsEdge_h__
