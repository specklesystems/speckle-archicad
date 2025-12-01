
// *****************************************************************************
//
//                             Class TreeEnumerator
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined TREEENUMERATOR_HPP
#define TREEENUMERATOR_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "Name.hpp"
#include "Folder.hpp"



// =========================== Class TreeEnumerator ============================

namespace IO {

class IO_DLL_EXPORT TreeEnumerator {
private:
	const Folder*	parent;		// points to the folder under enumeration
	bool			stop;		// user break (stop the enumeration if it is true)
	GSErrCode		status;		// status of the enumeration (stores first error code encountered)

	static bool		CCALL EnumCallback (const Folder& parent, const Name& entryName, bool isFolder, void* userData);

	bool	ProcessEntryFound  (const Name& entryName, bool isComposite);

	void	ProcessFolderEntered (const Name& folderName, const Folder& current);
	void	ProcessFolderExited  (const Name& folderName, const Folder& current);

	inline bool		IsStopped (void) const;
	inline void		SetStatus (GSErrCode ec);

protected:
		// Overridables for recursive enumeration

	virtual bool	EntryFound	  (const Name& entryName, bool isComposite);
	virtual bool	FileFound	  (const Name& fileName);
	virtual bool	FolderFound	  (const Name& folderName);
	virtual bool	LinkFound	  (const Name& linkName);

	virtual void	FolderEntered (const Name& folderName, const Folder& current);
	virtual void	FolderExited  (const Name& folderName, const Folder& current);

		// Additional methods for derived classes

	const Folder&	GetParent (void) const;

	void	Stop (void);

	void	ProcessFileFound   (const Name& fileName);
	void	ProcessFolderFound (const Name& folderName);
	void	ProcessLinkFound   (const Name& linkName);

	GSErrCode	GetStatus (void) const;

public:
		// Error codes

	enum {
		AccessDenied = TreeEnumeratorErrors + 0		// access to entry is denied
	};

		// User interface

	explicit TreeEnumerator (const Folder& root);

	virtual	GSErrCode	Do (void);
};

}	// namespace IO
// ___________________________ Class TreeEnumerator ___________________________


#endif
