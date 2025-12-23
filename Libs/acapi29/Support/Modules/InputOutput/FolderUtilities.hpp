
// *****************************************************************************
//
//                                Folder Utilities
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FOLDERUTILITIES_HPP
#define FOLDERUTILITIES_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "IOBase.hpp"

namespace GS { class UniString; }
namespace IO { class Location; }


// -----------------------------------------------------------------------------

namespace IO {

IO_DLL_EXPORT void	EnsureMaxFolderSize (const Location& folderLoc, const GS::UniString& extension, UInt64 maxSizeInMBytes, UInt32 maxFileCount = MaxUInt32);

}	// namespace IO


#endif
