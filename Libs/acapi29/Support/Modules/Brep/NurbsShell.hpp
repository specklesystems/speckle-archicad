// *********************************************************************************************************************
// Data structure that represents a closed set of NURBS faces in a NurbsBRep object.
// The set may not be 2-manifold.
// 
// Note. All indices refer to containing NurbsBRep, starting from 0.
// *********************************************************************************************************************

#if !defined(NURBSSHELL_HPP)
#define NURBSSHELL_HPP

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


struct DirectedFaceIndex {
	UInt32	face;
	bool	reversed;
	DirectedFaceIndex () : face (MaxUInt32), reversed (false) { }
	DirectedFaceIndex (UInt32 f, bool r) : face (f), reversed (r) { }
	bool operator== (const DirectedFaceIndex& other) const { return (face == other.face && reversed == other.reversed); }
	bool operator!= (const DirectedFaceIndex& other) const { return !(*this == other); }
};


class BREP_DLL_EXPORT NurbsShell {
	// A shell is a closed set of faces connected at edges.
	// Closed means that all face in the shell has a neighbour face along all of its edges.
	// Front side of the reversed faces is on the back side of the shell.

	static	GS::ClassInfo	classInfo;
	GS::Array<DirectedFaceIndex>	faceIndices;			// not empty
	Int32							lumpIndex;				// may be negative temporarily
	
public:
	NurbsShell ();
	NurbsShell (const GS::Array<DirectedFaceIndex>& faces);
	NurbsShell (GS::XMLIChannel& inXML, const char* tagName) { ReadXML (inXML, tagName); }
	bool				Equals			(const NurbsShell& other) const;
	void				AttachNurbsLump			(UInt32 lump);
	void				Reorient				();
	UInt32				GetFaceCount			()				const	{ return faceIndices.GetSize ();		}
	DirectedFaceIndex	GetDirectedFaceIndex	(UInt32 index)	const	{ return faceIndices[index];			}
	UInt32				GetFaceIndex			(UInt32 index)	const	{ return faceIndices[index].face;		}
	bool				IsFaceReversed			(UInt32 index)	const	{ return faceIndices[index].reversed;	}
	Int32				GetLumpIndex			()				const	{ return lumpIndex;						}

	ULong				GetUsedBytes			() const;
	ULong				GetHeapUsedBytes		() const;

	void				Read					(GS::IChannel& ic);
	void				Write					(GS::OChannel& oc) const;
	void				WriteXML				(GS::XMLOChannel& outXML, const char* tagName) const;
	void				ReadXML					(GS::XMLIChannel& inXML, const char* tagName);

private:
	void	DetachNurbsLump ();

	void	ReadVersion1 (GS::IChannel &ic);
	void	WriteVersion1 (GS::OChannel &oc) const;
};

}		// namespace Brep

#endif	// NURBSSHELL_HPP
