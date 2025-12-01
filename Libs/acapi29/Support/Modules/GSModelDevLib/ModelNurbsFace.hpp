#ifndef ModelNurbsFace_h__
#define ModelNurbsFace_h__

#pragma once

#include "ModelNurbsElementWithTolerance.hpp"

namespace ModelerAPI
{

class NurbsFace : public NurbsElementWithTolerance
{
	// A face is a connected, finite part of a surface bounded by
	// * one outer loop and
	// * zero or more inner loops (separating the face from holes).
	// A face has an orientation, the surface normals of its surface point to the front side of the face
	// Neighbouring faces may have inconsistent orientation, their loop may refer to the common edge in the same direction.
	//   In this case containing shell may refer these faces with different reversed flags.
	// Loop orientation is always determined on the face:
	//   looking in the direction of the loop with face front side upwards the face inside is on the left
private:
	GS::Array<UInt32>	loopIndices;		// not empty, first is the outer loop
	Int32				shellIndex;			// negative for lamina face
	UInt32				surfaceIndex;		// geometry of face is part of this surface
											// tolerance is not used in geometry checks
public:
	NurbsFace(GS::Array<UInt32> loopIndices,
		Int32 shellIndex,
		UInt32 surfaceIndex,
		double tolerance) : loopIndices (loopIndices), shellIndex (shellIndex), surfaceIndex (surfaceIndex), NurbsElementWithTolerance (tolerance)
	{}
	
	UInt32				GetLoopIndexCount	()				const { return loopIndices.GetSize (); }
	UInt32				GetLoopIndex		(UInt32 index)	const { return loopIndices[index-1]; }
	Int32				GetShellIndex		()				const { return shellIndex; }
	UInt32				GetSurfaceIndex		()				const { return surfaceIndex; }
};

} // namespace ModelerAPI
#endif // ModelNurbsFace_h__