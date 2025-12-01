
// *****************************************************************************
//
//	                           Interface RollingVFS
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ROLLINGVFS_HPP
#define ROLLINGVFS_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "VirtualFileSystem.hpp"



// =========================== Interface RollingVFS ============================

namespace IO {

class IO_DLL_EXPORT RollingVFS: public VirtualFileSystem {
public:
		// Destructor

   ~RollingVFS ();

		// Interface

	virtual bool	Manages (const Location& loc) const = 0;
};

}	// namespace IO
// ___________________________ Interface RollingVFS ____________________________


#endif
