
// *****************************************************************************
//
//	                            Interface FixedVFS
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FIXEDVFS_HPP
#define FIXEDVFS_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "VirtualFileSystem.hpp"



// ============================ Interface FixedVFS =============================

namespace IO {

class IO_DLL_EXPORT FixedVFS: public VirtualFileSystem {
public:
		// Destructor

   ~FixedVFS ();

		// Interface

	virtual void	Mounted	  (const Location& to) = 0;
	virtual void	Unmounted (void) = 0;
};

}	// namespace IO
// ____________________________ Interface FixedVFS _____________________________


#endif
