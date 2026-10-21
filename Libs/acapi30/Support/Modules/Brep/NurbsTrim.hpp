// *********************************************************************************************************************
// Data structure that represents a face boundary element of a NurbsBRep object.
// Faces are connected to edges through loops which contain trims.
// 
// Note. All indices refer to containing NurbsBRep, starting from 0.
// *********************************************************************************************************************

#if !defined(NURBSTRIM_HPP)
#define NURBSTRIM_HPP

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


class BREP_DLL_EXPORT NurbsTrim : public NurbsElementWithTolerance {
	// A trim is a bounding edge of a face
	// * connects face to edge (or to vertex in singular case)
	// * defines a boundary in the parameter space of the surface of the face.
	// Trim is singular if surface is one point along the whole trim
	static	GS::ClassInfo	classInfo;
	Int32		edgeIndex;			// negative for singular trim, nonnegative for nonsingular trim
	Int32		vertexIndex;		// nonnegative for singular trim, negative for nonsingular trim (neither vertex of its edge in this case!)
	Int32		loopIndex;			// may be negative temporarily
	Int32		trimCurve2DIndex;	// 2d curve which defines the boundary of the face in the domain of the face
	Interval	curveSubDomain;		// 2d geometry of trim is part of the curve determined by this subdomain in the domain of 2d curve

	void ReadVersion1(GS::IChannel &ic);
	void WriteVersion1(GS::OChannel &oc) const;

public:
	NurbsTrim ();
	NurbsTrim (Int32 edgeIdx, Int32 vertexIdx, Int32 curve2DIdx, const Interval& curveSubDom, double tol);
	NurbsTrim (GS::XMLIChannel& inXML, const char* tagName) { ReadXML (inXML, tagName); }
	
	bool		Equals		(const NurbsTrim& other, double eps = SmallEps) const;
	void		AttachNurbsLoop		(UInt32 loopIdx);
	Int32		GetEdgeIndex		() const { return edgeIndex;				}
	Int32		GetVertexIndex		() const { return vertexIndex;				}
	Int32		GetLoopIndex		() const { return loopIndex;				}
	Int32		GetTrimCurve2DIndex () const { return trimCurve2DIndex;			}
	bool		HasTrimCurve2D		() const { return (trimCurve2DIndex >= 0);	}
	Interval	GetCurveSubDomain	() const { return curveSubDomain;			}
	bool		IsSingular			() const { return (edgeIndex < 0);			}

	void 		Read				(GS::IChannel& ic);
	void 		Write				(GS::OChannel& oc) const;
	void		WriteXML			(GS::XMLOChannel& outXML, const char* tagName)	const;
	void		ReadXML				(GS::XMLIChannel& inXML, const char* tagName);

};

}		// namespace Brep

#endif	// NURBSTRIM_HPP
