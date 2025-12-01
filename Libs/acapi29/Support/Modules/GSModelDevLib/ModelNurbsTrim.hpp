#ifndef NurbsTrim_h__
#define NurbsTrim_h__

#pragma once

#include "ModelNurbsElementWithTolerance.hpp"

namespace ModelerAPI
{

class NurbsTrim : public NurbsElementWithTolerance
{
	// A trim is a bounding edge of a face
	// * connects face to edge (or to vertex in singular case)
	// * defines a boundary in the parameter space of the surface of the face.
	// Trim is singular if surface is one point along the whole trim
private:
	Int32		edgeIndex;			// negative for singular trim, nonnegative for nonsingular trim
	Int32		vertexIndex;		// nonnegative for singular trim, negative for nonsingular trim (neither vertex of its edge in this case!)
	UInt32		loopIndex;
	Int32		trimCurve2DIndex;	// 2d curve which defines the boundary of the face in the domain of the face
	Interval	curveSubDomain;		// 2d geometry of trim is part of the curve determined by this subdomain in the domain of 2d curve
	
public:
	NurbsTrim(Int32 edgeIndex,
		Int32 vertexIndex,
		UInt32 loopIndex,
		Int32 trimCurve2DIndex,
		Interval curveSubDomain,
		double tolerance) : edgeIndex (edgeIndex), vertexIndex (vertexIndex), loopIndex (loopIndex), trimCurve2DIndex (trimCurve2DIndex), curveSubDomain (curveSubDomain), NurbsElementWithTolerance (tolerance)
	{}

	Int32		GetEdgeIndex () const { return edgeIndex; }
	Int32		GetVertexIndex () const { return vertexIndex; }
	UInt32		GetLoopIndex () const { return loopIndex; }
	Int32		GetTrimcurve2DIndex () const { return trimCurve2DIndex; }
	Interval	GetCurveSubdomain () const { return curveSubDomain; }
	bool		IsSingular () const { return (edgeIndex < 0); }
};

} // namespace ModelerAPI

#endif // NurbsTrim_h__
