// *********************************************************************************************************************
// Data structure that represents an edge of a NurbsBRep object.
// 
// Note. All indices refer to containing NurbsBRep, starting from 0.
// *********************************************************************************************************************

#if !defined(NURBSEDGE_HPP)
#define NURBSEDGE_HPP

#pragma once

#include "BrepExport.hpp"

// from Brep
#include "NurbsElementWithTolerance.hpp"
#include "NurbsDomainInterval.hpp"

//from GSRoot
#include "ClassInfo.hpp"

namespace GS {
	class XMLIChannel;
	class XMLOChannel;
}


namespace Brep {

class BREP_DLL_EXPORT NurbsEdge : public NurbsElementWithToleranceTransform {
	// A part of boundary of one or two faces, or a wire edge
	// Its geometry is a connected part of a 3d nurbs curve
	// It is connected to a face by a trim

private:
	static	GS::ClassInfo	classInfo;
	Int32				beginVertexIndex;	// negative (invalid) for ring edge
	Int32				endVertexIndex;		// negative (invalid) for ring edge; or may equal to beginVertexIndex for loop edge
	GS::Array<UInt32>	trimIndices;		// any number of trims (and therefore face) is allowed, order is irrelevant
	UInt32				curve3DIndex;		// geometry of edge is part of this curve
	Interval			curveSubDomain;		// 3d geometry of edge is part of the curve determined by this subdomain in the domain of curve

	void		ReadVersion1	(GS::IChannel& ic);
	void		WriteVersion1	(GS::OChannel& oc) const;

public:
	NurbsEdge ();
	NurbsEdge (Int32 begVert, Int32 endVert, UInt32 curve, const Interval& curveSubDom, double tol);
	NurbsEdge (Int32 begVert, Int32 endVert, const GS::Array<UInt32>& trimInds, UInt32 curve, const Interval& curveSubDom, double tol);
	NurbsEdge (GS::XMLIChannel& inXML, const char* tagName) { ReadXML (inXML, tagName); }

	bool		Equals (const NurbsEdge& other, double eps = SmallEps) const;
	void		AttachNurbsTrim (UInt32 trimIndex);
	void		DetachAllNurbsTrims ();
	void		Transform (const TRANMAT& tran);

	Int32		GetBeginVertexIndex			() const				{ return beginVertexIndex;								}
	Int32		GetEndVertexIndex			() const				{ return endVertexIndex;								}
	Int32		GetDirectedBeginVertexIndex (bool reversed) const	{ return reversed ? endVertexIndex : beginVertexIndex;	}
	Int32		GetDirectedEndVertexIndex	(bool reversed) const	{ return reversed ? beginVertexIndex : endVertexIndex;	}
	UInt32		GetTrimCount				() const				{ return trimIndices.GetSize ();						}
	UInt32		GetTrimIndex				(UInt32 index) const	{ return trimIndices[index];							}
	const GS::Array<UInt32>&	GetTrimIndices () const				{ return trimIndices;									}
	UInt32		GetCurve3DIndex				() const				{ return curve3DIndex;									}
	Interval	GetCurveSubDomain			() const				{ return curveSubDomain;								}
	
	bool		IsLoopEdge			() const { return (beginVertexIndex == endVertexIndex) && (beginVertexIndex >= 0);	}
	bool		IsRingEdge			() const { return (beginVertexIndex < 0 && endVertexIndex < 0);						}
	bool		IsRegularEdge		() const { return !IsLoopEdge () && !IsRingEdge ();									}
	bool		IsWire				() const { return (trimIndices.GetSize () == 0);									}
	bool		IsSurfaceBoundary	() const { return (trimIndices.GetSize () == 1);									}
	bool		Is2Manifold			() const { return (trimIndices.GetSize () == 2);									}
	bool		IsNon2Manifold		() const { return (trimIndices.GetSize () >  2);									}
												// actually surface boundary and wire edges are also non-2-manifold ones.

	ULong		GetUsedBytes () const;
	ULong		GetHeapUsedBytes () const;

	void		Read	(GS::IChannel& ic);
	void		Write	(GS::OChannel& oc) const;

	void		WriteXML (GS::XMLOChannel& outXML, const char* tagName)	const;
	void		ReadXML (GS::XMLIChannel& inXML, const char* tagName);
};


}		// namespace Brep

#endif	// NURBSEDGE_HPP
