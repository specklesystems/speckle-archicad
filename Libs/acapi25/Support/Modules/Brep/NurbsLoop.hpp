// *********************************************************************************************************************
// Data structure that represents one closed contour of a face of a NurbsBRep object.
// 
// Note. All indices refer to containing NurbsBRep, starting from 0.
// *********************************************************************************************************************

#if !defined(NURBSLOOP_HPP)
#define NURBSLOOP_HPP

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


struct DirectedTrimIndex {
	UInt32	trim;
	bool	reversed;
	DirectedTrimIndex () : trim (MaxUInt32), reversed (false) { }
	DirectedTrimIndex (UInt32 t, bool r) : trim (t), reversed (r) { }
	bool operator== (const DirectedTrimIndex& other) const { return (trim == other.trim && reversed == other.reversed); }
	bool operator!= (const DirectedTrimIndex& other) const { return !(*this == other); }
};


class BREP_DLL_EXPORT NurbsLoop {
	// A loop is a circular sequence of trims, each trim is connected on its end to the begin of the next.
	// The Connections are at vertices of the edges of trims or vertices of singular trims.
	// A trim may appear only once in a loop.
	// A vertex may appear only once in a loop except vertex of a singular trim.
	
	static	GS::ClassInfo	classInfo;
	GS::Array<DirectedTrimIndex>	trimIndices;	// successive trims of the loops
													// not empty but can have only one element if it is a trim of a loop or ring edge
	Int32							faceIndex;		// may be negative temporarily

public:
	NurbsLoop ();
	NurbsLoop (const GS::Array<DirectedTrimIndex>& trims);
	NurbsLoop (GS::XMLIChannel& inXML, const char* tagName) { ReadXML (inXML, tagName); }
	bool				Equals			(const NurbsLoop& other) const;
	void				AttachNurbsFace			(UInt32 face);
	UInt32				GetTrimCount			()				const	{ return trimIndices.GetSize ();		}
	DirectedTrimIndex	GetDirectedTrimIndex	(UInt32 index)	const	{ return trimIndices[index];			}
	UInt32				GetTrimIndex			(UInt32 index)	const	{ return trimIndices[index].trim;		}
	bool				IsTrimReversed			(UInt32 index)	const	{ return trimIndices[index].reversed;	}
	Int32				GetFaceIndex			()				const	{ return faceIndex;						}

	ULong				GetUsedBytes			() const;
	ULong				GetHeapUsedBytes		() const;

	void				Read					(GS::IChannel& ic);
	void				Write					(GS::OChannel& oc) const;
	void				WriteXML				(GS::XMLOChannel& outXML, const char* tagName) const;
	void				ReadXML					(GS::XMLIChannel& inXML, const char* tagName);

private:
	void				DetachNurbsFace ();

	void WriteVersion1 (GS::OChannel &oc) const;
	void ReadVersion1 (GS::IChannel &ic);
};

}		// namespace Brep

#endif	// NURBSLOOP_HPP
