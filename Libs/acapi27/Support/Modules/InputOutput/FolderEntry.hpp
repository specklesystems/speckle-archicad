
// *****************************************************************************
//
//	                           Interface FolderEntry
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FOLDERENTRY_HPP
#define FOLDERENTRY_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "FSEntry.hpp"

#include "UniString.hpp"

namespace IO { class Location; }
namespace IO { class Name; }
namespace IO { class EntryEnumerator; }
namespace IO { class FileEntry; }


// =========================== Interface FolderEntry ===========================

namespace IO {

class IO_DLL_EXPORT FolderEntry: public FSEntry {
private:
	GS::UniString CleanUpNameString (const GS::UniString& nameString) const;

public:
		// Types

	enum CreateStatus	 { CR_Ok, CR_EntryExists, CR_DeviceIsFull, CR_AccessDenied, CR_Error };
	enum GenUNStatus	 { GN_Ok, GN_AccessDenied, GN_Error, GN_AllUsed };
	enum MoveStatus		 { MV_Ok, MV_SourceNotFound, MV_TargetExists, MV_DeviceIsFull, MV_AccessDenied, MV_Error };
	enum ExchangeStatus	 { EX_Ok, EX_SourceNotFound, EX_DeviceIsFull, EX_AccessDenied, EX_NotImplemented, EX_Error };
	enum CopyStatus		 { CP_Ok, CP_SourceNotFound, CP_TargetExists, CP_DeviceIsFull, CP_AccessDenied, CP_Error };
	enum DeleteStatus	 { DL_Ok, DL_EntryNotFound, DL_AccessDenied, DL_Error };
	enum TypeStatus		 { TP_Ok, TP_AccessDenied, TP_EntryNotFound, TP_Error };
	enum EnumStatus		 { EN_Ok, EN_AccessDenied, EN_UserBreak, EN_Error };
	enum AttributeStatus { AT_Ok, AT_AccessDenied, AT_Error };

	enum EntryType { ET_File, ET_Folder, ET_Link };

		// Destructor

   ~FolderEntry () {}

		// Interface


	virtual CreateStatus	CreateFile   (const Name& name) = 0;
	virtual CreateStatus	CreateFolder (const Name& name) = 0;
	virtual CreateStatus	CreateLink   (const Name& name, const Location& target) = 0;

	virtual GenUNStatus     GenerateUnusedName	(Name* result, const GS::UniString& prefix, const GS::UniString& extension) const;

	virtual bool			ImplementsRename (void) const;
	virtual bool			ImplementsMove	 (void) const;
	virtual bool			ImplementsCopy	 (void) const;

	virtual ExchangeStatus  Exchange (const Name& from, const Name& to, bool ignoreWriteProtection, Name* fromNameAfterExchange, Name* toNameAfterExchange);
	virtual MoveStatus		Rename	 (const Name& from, const Name& to);
	virtual MoveStatus		Move	 (const Name& from, FolderEntry& parent, const Name& to, bool ignoreWriteProtection) = 0;
	virtual CopyStatus		Copy	 (const Name& from, FolderEntry& parent, const Name& to) = 0;
	virtual DeleteStatus	Delete	 (const Name& name, bool ignoreWriteProtection) = 0;
	virtual TypeStatus		GetType  (const Name& name, EntryType* result) const = 0;
	virtual TypeStatus		IsLink   (const Name& name, bool* result) const;

	virtual EnumStatus		Enumerate (EntryEnumerator& ee) const = 0;

	virtual AttributeStatus	GetFreeSpace (UInt64* result) const = 0;

	virtual bool			IsReadable  (void) const = 0;
	virtual bool			IsWriteable (void) const = 0;

	virtual AttributeStatus	IsOnLocalVolume	(bool* result) const = 0;
	virtual AttributeStatus	IsOnFixedVolume (bool* result) const = 0;
};

}	// namespace IO
// ___________________________ Interface FolderEntry ___________________________


#endif
