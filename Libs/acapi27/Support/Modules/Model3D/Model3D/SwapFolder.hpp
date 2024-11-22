// *********************************************************************************************************************
// Guard-like type on a folder of the filesystem.
// 
// Creates and empties the folder on creation, removes it on destruction.
// Can be used with reference counting if multiple objects share the same
// swap folder (e.g. VMDESC members of Modeler::Sight).
// *********************************************************************************************************************

#if !defined MODEL3D_SWAPFOLDER_HPP
#define MODEL3D_SWAPFOLDER_HPP

#pragma once

// from GSRoot
#include "AtomicCounter.hpp"
#include "Ref.hpp"

// from Modeler
#include "Model3DPrivExp.h"

// from InputOutput
#include "Location.hpp"

namespace Modeler {

class SwapFolder;
typedef GS::Ref<SwapFolder, GS::AtomicCounter> SwapFolderRef;

class MODEL3D_PRIVATE_EXPORT SwapFolder {
public:
	SwapFolder (const IO::Location& swapFolderLocation);
	~SwapFolder ();

	const IO::Location& GetLocation () const { return location; }

private:
	IO::Location location;
};

}		// namespace Modeler

#endif	// MODEL3D_SWAPFOLDER_HPP