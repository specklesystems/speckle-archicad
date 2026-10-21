
// *****************************************************************************
//
//	                       Interface ReadOnlyFolderEntry
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined READONLYFOLDERENTRY_HPP
#define READONLYFOLDERENTRY_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "FolderEntry.hpp"



// ======================= Interface ReadOnlyFolderEntry =======================

namespace IO {

class IO_DLL_EXPORT ReadOnlyFolderEntry: public FolderEntry {
public:
		// Destructor

   ~ReadOnlyFolderEntry () {}

		// Interface

	virtual TimeStatus		SetCreationTime		(const GSTime& newTime) override;
	virtual TimeStatus		SetModificationTime (const GSTime& newTime) override;

	virtual CreateStatus	CreateFile   (const Name& name) override;
	virtual CreateStatus	CreateFolder (const Name& name) override;
	virtual CreateStatus	CreateLink   (const Name& name, const Location& target) override;

	virtual MoveStatus		Move   (const Name& from, FolderEntry& parent, const Name& to, bool ignoreWriteProtection) override;
	virtual DeleteStatus	Delete (const Name& name, bool ignoreWriteProtection) override;

	virtual AttributeStatus	GetFreeSpace (UInt64* resultHigh) const override;

	virtual bool			IsWriteable (void) const override;
};

}	// namespace IO
// _______________________ Interface ReadOnlyFolderEntry _______________________


#endif
