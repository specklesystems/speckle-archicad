// *********************************************************************************************************************
// Data structure that represents a closed, finite part of 3D space bounded by NURBS shells.
// 
// Note. All indices refer to containing NurbsBRep, starting from 0.
// *********************************************************************************************************************

#if !defined(NURBSLUMP_HPP)
#define NURBSLUMP_HPP

#pragma once

#include "BrepExport.hpp"

// from GSRoot
#include "Array.hpp"
#include "ClassInfo.hpp"


namespace GS {
	class XMLIChannel;
	class XMLOChannel;
}


namespace Brep {


class BREP_DLL_EXPORT NurbsLump {
	// A lump is a connected, finite part of 3d space bounded by
	// * one outer shell (separating the lump from the infinite void) and
	// * zero or more inner shells (separating the lump from inner voids, cavities).
	// A lump is always a solid lump, surface shells does not belong to any lump.
	// The lump is towards the back sides of its shells.

	static	GS::ClassInfo	classInfo;
	GS::Array<UInt32>	shellIndices;	// not empty, first is the outer shell

	void ReadVersion1 (GS::IChannel &ic);
	void WriteVersion1 (GS::OChannel &oc) const;
public:
	NurbsLump ();
	NurbsLump (const GS::Array<UInt32>& shells);
	NurbsLump (GS::XMLIChannel& inXML, const char* tagName) { ReadXML (inXML, tagName); }
	bool				Equals	(const NurbsLump& other) const;
	UInt32				GetShellCount	()				const	{ return shellIndices.GetSize ();	}
	UInt32				GetShellIndex	(UInt32 index)	const	{ return shellIndices[index];		}

	ULong				GetUsedBytes			() const;
	ULong				GetHeapUsedBytes		() const;

	void				Read			(GS::IChannel& ic);
	void				Write			(GS::OChannel& oc) const;
	void				WriteXML		(GS::XMLOChannel& outXML, const char* tagName) const;
	void				ReadXML			(GS::XMLIChannel& inXML, const char* tagName);
};

}		// namespace Brep

#endif	// NURBSLUMP_HPP
