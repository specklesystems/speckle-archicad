// *********************************************************************************************************************
// Data structure that represents one face of a NurbsBRep object.
// 
// Note. All indices refer to containing NurbsBRep, starting from 0.
// *********************************************************************************************************************

#if !defined(NURBSFACE_HPP)
#define NURBSFACE_HPP

#pragma once

#include "BrepExport.hpp"

// from GSRoot
#include "Array.hpp"
#include "ClassInfo.hpp"

// from Brep
#include "NurbsElementWithTolerance.hpp"

namespace GS {
	class XMLIChannel;
	class XMLOChannel;
}


namespace Brep {

class BREP_DLL_EXPORT NurbsFace : public NurbsElementWithToleranceTransform {
	// A face is a connected, finite part of a surface bounded by
	// * one outer loop and
	// * zero or more inner loops (separating the face from holes).
	// A face has an orientation, the surface normals of its surface point to the front side of the face
	// Neighbouring faces may have inconsistent orientation, their loop may refer to the common edge in the same direction.
	//   In this case containing shell may refer these faces with different reversed flags.
	// Loop orientation is always determined on the face:
	//   looking in the direction of the loop with face front side upwards the face inside is on the left

private:
	static	GS::ClassInfo	classInfo;
	GS::Array<UInt32>	loopIndices;		// not empty, first is the outer loop
	Int32				shellIndex;			// may be negative temporarily (uninitialized) or permanently (for lamina face)
	UInt32				surfaceIndex;		// geometry of face is part of this surface
											// tolerance is not used in geometry checks
	void ReadVersion1 (GS::IChannel &ic);
	void WriteVersion1 (GS::OChannel &oc) const;

public:
	NurbsFace ();

	NurbsFace (const GS::Array<UInt32>& loops,
			   UInt32					surface,
			   double					tol);

	NurbsFace (const GS::Array<UInt32>& loops,
			   Int32					shellIndex,
			   UInt32					surface,
			   double					tol);

	NurbsFace (GS::XMLIChannel& inXML, const char* tagName) { ReadXML (inXML, tagName);  }

	bool				Equals (const NurbsFace& other) const;
	void				AttachNurbsShell (UInt32 shellIndex);
	void				DetachNurbsShell ();
	void				Transform (const TRANMAT& tran);

	UInt32				GetSurfaceIndex		()				const	{ return surfaceIndex;				}
	UInt32				GetLoopCount		()				const	{ return loopIndices.GetSize ();	}
	UInt32				GetLoopIndex		(UInt32 index)	const	{ return loopIndices[index];		}
	const GS::Array<UInt32>& GetLoopIndices ()				const	{ return loopIndices;				}
	Int32				GetShellIndex		()				const	{ return shellIndex;				}

	ULong				GetUsedBytes		() const;
	ULong				GetHeapUsedBytes	() const;

	void				Read				(GS::IChannel& ic);
	void				Write				(GS::OChannel& oc) const;
	void				WriteXML			(GS::XMLOChannel& outXML, const char* tagName)	const;
	void				ReadXML				(GS::XMLIChannel& inXML, const char* tagName);
};

}		// namespace Brep

#endif	// NURBSFACE_HPP
