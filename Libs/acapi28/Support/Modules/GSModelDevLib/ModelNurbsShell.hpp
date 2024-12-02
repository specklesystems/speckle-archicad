#ifndef ModelNurbsShell_h__
#define ModelNurbsShell_h__

#pragma once

#include "NurbsAttributes.hpp"

namespace ModelerAPI
{

class NurbsShell {
	// A shell is a closed set of faces connected at edges.
	// Closed means that all face in the shell has a neighbor face along all of its edges.
	// Front side of the reversed faces is on the back side of the shell.
private:
	GS::Array<ModelerAPI::DirectedFaceIndex>	faceIndices;			// not empty
	UInt32										lumpIndex;
public:
	NurbsShell(GS::Array<ModelerAPI::DirectedFaceIndex> faceIndices,
		UInt32 lumpIndex) : faceIndices(faceIndices), lumpIndex(lumpIndex)
	{}

	UInt32										GetFaceIndexCount	()				const { return faceIndices.GetSize (); }
	ModelerAPI::DirectedFaceIndex				GetFaceIndex		(UInt32 index)	const { return faceIndices[index-1]; }
	UInt32										GetLumpIndex		()				const { return lumpIndex; }
};

} // namespace ModelerAPI
#endif // ModelNurbsShell_h__
