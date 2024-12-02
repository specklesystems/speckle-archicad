#ifndef ModelNurbsLoop_h__
#define ModelNurbsLoop_h__

#pragma once

#include "NurbsAttributes.hpp"

namespace ModelerAPI
{

class NurbsLoop {
	// A loop is a circular sequence of trims, each trim is connected on its end to the begin of the next.
	// The Connections are at vertices of the edges of trims or vertices of singular trims.
	// A trim may appear only once in a loop.
	// A vertex may appear only once in a loop except vertex of a singular trim.
private:
	GS::Array<DirectedTrimIndex>	trimIndices;	// successive trims of the loops
													// not empty but can have only one element if it is a trim of a loop or ring edge
	UInt32							faceIndex;

public:
	NurbsLoop(GS::Array<DirectedTrimIndex> trimIndices,
		UInt32 faceIndex) : trimIndices(trimIndices), faceIndex(faceIndex)
	{}

	bool							IsTrimReversed		(UInt32 index)	const { return trimIndices[index-1].reversed; }
	UInt32							GetTrimIndexCount	()				const { return trimIndices.GetSize (); }
	DirectedTrimIndex				GetTrimIndex		(UInt32 index)	const { return trimIndices[index-1]; }
	UInt32							GetFaceIndex		()				const { return faceIndex; }
};

} // namespace ModelerAPI
#endif // ModelNurbsLoop_h__