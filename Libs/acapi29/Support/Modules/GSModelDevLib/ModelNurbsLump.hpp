#ifndef ModelNurbsLump_h__
#define ModelNurbsLump_h__

#pragma once
namespace ModelerAPI
{

class NurbsLump {
	// A lump is a connected, finite part of 3d space bounded by
	// * one outer shell (separating the lump from the infinite void) and
	// * zero or more inner shells (separating the lump from inner voids, cavities).
	// A lump is always a solid lump, surface shells does not belong to any lump.
	// The lump is towards the back sides of its shells.

	GS::Array<UInt32>	shellIndices;	// not empty, first is the outer shell						lumpIndex;				// may be negative temporarily; or permanently for surface shells
public:
	NurbsLump(GS::Array<UInt32> shellIndices) : shellIndices(shellIndices)
	{}

	UInt32				GetShellIndexCount	()				const { return shellIndices.GetSize (); }
	UInt32				GetShellIndex		(UInt32 index)	const { return shellIndices[index-1]; }
};

} // namespace ModelerAPI
#endif // ModelNurbsLump_h__
