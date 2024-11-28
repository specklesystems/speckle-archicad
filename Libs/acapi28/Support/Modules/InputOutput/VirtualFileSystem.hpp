
// *****************************************************************************
//
//	                       Interface VirtualFileSystem
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined VIRTUALFILESYSTEM_HPP
#define VIRTUALFILESYSTEM_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "BaseFileSystem.hpp"

namespace IO { class RelativeLocation; }



// ======================== Interface VirtualFileSystem ========================

namespace IO {

class IO_DLL_EXPORT VirtualFileSystem: public BaseFileSystem {
public:
	~VirtualFileSystem ();

	virtual bool	IsLegal (const RelativeLocation& relLoc) const;

	virtual bool	IsSubmountingEnabled (void) const;
};

}	// namespace IO
// ________________________ Interface VirtualFileSystem ________________________


#endif
