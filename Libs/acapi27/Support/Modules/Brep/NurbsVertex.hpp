// *********************************************************************************************************************
// Data structure that represents a vertex of a NurbsBRep object.
// 
// Note. All indices refer to containing NurbsBRep, starting from 0.
// *********************************************************************************************************************

#if !defined(NURBSVERTEX_HPP)
#define NURBSVERTEX_HPP

#pragma once

#include "BrepExport.hpp"

// from Geometry
#include "Vector3D.hpp"

// from Brep
#include "NurbsElementWithTolerance.hpp"

//from GSRoot
#include "ClassInfo.hpp"

namespace GS {
	class XMLIChannel;
	class XMLOChannel;
}

struct TRANMAT;

namespace Brep {


class BREP_DLL_EXPORT NurbsVertex : public NurbsElementWithToleranceTransform {
	// A node of a nurbs body, has no dimension but a position
private:
	static	GS::ClassInfo	classInfo;
	Coord3D position;

	void ReadVersion1 (GS::IChannel &ic);
	void WriteVersion1 (GS::OChannel &oc) const;
public:
	NurbsVertex ();
	NurbsVertex (const Coord3D& pos, double tol);
	NurbsVertex (GS::XMLIChannel& inXML, const char* tagName) { ReadXML (inXML, tagName); }

	bool				Equals			(const NurbsVertex& other, double eps = SmallEps) const;
	void				Transform		(const TRANMAT& tran);
	Coord3D				GetPosition		(const TRANMAT& tran) const;
	const Coord3D&		GetPosition		() const { return position; }

	void				Read	(GS::IChannel& ic);
	void				Write	(GS::OChannel& oc) const;
	void				WriteXML (GS::XMLOChannel& outXML, const char* tagName)	const;
	void				ReadXML (GS::XMLIChannel& inXML, const char* tagName);
};

}		// namespace Brep

#endif	// NURBSVERTEX_HPP
