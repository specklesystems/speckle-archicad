
// *****************************************************************************
//
//	                         Interface BaseFileSystem
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined BASEFILESYSTEM_HPP
#define BASEFILESYSTEM_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

namespace IO { class Location; }
namespace IO { class FileEntry; }
namespace IO { class FolderEntry; }



// ========================= Interface BaseFileSystem ==========================

namespace IO {

class IO_DLL_EXPORT BaseFileSystem {
public:
		// Types

	enum ConnectStatus { CN_Ok, CN_NotAFile, CN_NotAFolder, CN_AccessDenied, CN_EntryNotFound, CN_Error };

		// Destructor

	virtual ~BaseFileSystem ();

		// Interface

	virtual ConnectStatus	Connect	   (Location* fileLoc, FileEntry** imp) = 0;
	virtual ConnectStatus	Connect	   (Location* folderLoc, FolderEntry** imp) = 0;
	virtual void			Disconnect (FileEntry* connection) = 0;
	virtual void			Disconnect (FolderEntry* connection) = 0;

	virtual bool			IsCompatibleWithFileSystem (BaseFileSystem* fileSystem) const;
};

}	// namespace IO
// _________________________ Interface BaseFileSystem __________________________


#endif
