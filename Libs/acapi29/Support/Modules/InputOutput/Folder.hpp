
// *****************************************************************************
//
//                                 Class Folder
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FOLDER_HPP
#define FOLDER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "Location.hpp"

#include "FastLogger.hpp"
#include "Tag.hpp"

#include <functional>

namespace IO {
	class BaseFileSystem;
	class File;
	class FileEntry;
	class FolderEntry;
}


// =============================== Class Folder ================================

namespace IO {

class IO_DLL_EXPORT Folder {
private:
	friend class File;	// to allow access to the location (only for efficiency) and imp members

	Location		 location;	// location of the folder
	IO::FolderEntry* imp;		// points to the object implementing the folder on the current platform

	GSErrCode	status;		// object state (error code saved in constructor)

	static const GS::UniString DefaultBase;

	Folder (const Folder& source);				// disabled
	Folder&	operator= (const Folder& source);	// disabled

	GSErrCode	PerformCopy (const Name& from, Folder& target, const Name& to);

	GSErrCode			CopyEntryWithReadWrite  (const Name& from, Folder& target, const Name& to) const;
	static GSErrCode	CopyEntryWithReadWrite	(const Folder& sourceParent, const Name& from, Folder& targetParent, const Name& to);
	static GSErrCode	CopyFileWithReadWrite	(const Folder& sourceParent, const Name& from, Folder& targetParent, const Name& to);
	static GSErrCode	CopyFolderWithReadWrite (const Folder& sourceParent, const Name& from, Folder& targetParent, const Name& to);
	struct CopyData {
		Folder*	  target;
		GSErrCode result;
	};
	static bool	  CCALL CopyEntryWithReadWriteCallback (const Folder& parent, const Name& entryName, bool isFolder, void* userData);

	GSErrCode  ExchangeDefault (const Name& from, const Name& to);

	enum CountMode { CM_File, CM_Folder, CM_Entry };
	struct CountData {
		CountMode countMode;
		USize	  counter;

		explicit CountData (CountMode cm): countMode (cm), counter (0) {}
	};
	static bool		CCALL EntryCounter (const Folder& parent, const Name& entryName, bool isFolder, void* userData);
	GSErrCode			  Count (CountMode cm, USize* result) const;

	static bool		CCALL EnumVMPCallback (const Location& mountPoint, void* userData);
	static bool		CCALL DeleteAllCallback (const Folder& parent, const Name& entryName, bool isFolder, void* userData);
	static bool		CCALL PrintContentCallback (const Folder& parent, const Name& entryName, bool isFolder, void* userData);

	void	Init (void);

	static GSErrCode	Connect (Location* loc, IO::FolderEntry** imp);
	static void			LogConnection (GSErrCode status, const Location& folderLoc, bool ignoreFolderNotFound);
	void				LogError (GS::ErrorLogLine& errorLog) const;

public:
		// Types

	typedef bool	(CCALL *EnumCallbackConst) (const Folder& parent, const Name& entryName, bool isFolder, void* userData);
	typedef bool	(CCALL *EnumCallback) (Folder& parent, const Name& entryName, bool isFolder, void* userData);

	enum OnNotFound { Fail, Create, Ignore };	// what to do if the folder doesn't exist

	enum EntryType { FileEntry, FolderEntry, LinkEntry };	// possible file system entry types in the folder

	enum DataSafety { Normal, IgnoreWriteProtection };	// data safety level for some operations

	enum LinkProcessing { ResolveLinks,	PreserveLinks };		// what to do with links: resolve or not

	enum Filters {		// which type of entries should be supplied during the enumeration
		FilterFiles		   = 1,	// supply files
		FilterFolders	   = 2,	// supply folders
		FilterLinks		   = 4,	// supply links
		FilterUnknownTypes = 8,	// supply dead links and inaccessible entries

		FilterFinalTypes   = FilterFiles | FilterFolders,
		FilterNormalTypes  = FilterFiles | FilterFolders | FilterLinks,
		FilterAllTypes	   = FilterFiles | FilterFolders | FilterLinks | FilterUnknownTypes
	};

		// Error codes

	enum {
		FolderNotFound = FolderErrors + 0,	// folder is not found, connection failed
		NotAFolder	   = FolderErrors + 1,	// not a folder was specified, connection failed
		AccessDenied   = FolderErrors + 2,	// access to folder, folder entry or folder data is denied
		CreationError  = FolderErrors + 3,	// folder creation failed
		SourceNotFound = FolderErrors + 4,	// source entry is not found
		TargetNotFound = FolderErrors + 5,	// target entry is not found
		TargetExists   = FolderErrors + 6,	// target entry already exists
		DeviceIsFull   = FolderErrors + 7,	// device is full
		InvalidTime	   = FolderErrors + 8	// invalid time is encountered
	};

		// Constructors

	explicit Folder (const Location& loc, OnNotFound action = Fail);
	Folder (const Folder& parent, const Name& folderName);
	Folder (Folder& parent, const Name& folderName, OnNotFound action);
	virtual ~Folder ();

	static GSErrCode	CCALL New (Folder** result, const Location& loc, OnNotFound action = Fail);
	static GSErrCode	CCALL New (Folder** result, const Folder& parent, const Name& folderName);
	static GSErrCode	CCALL New (Folder** result, Folder& parent, const Name& folderName, OnNotFound action);

		// State query

	inline GSErrCode	GetStatus	 (void) const;

		// Folder content manipulation

	virtual GSErrCode	CreateFile	 (const Name& fileName);
	virtual GSErrCode	CreateFolder (const Name& folderName, AccessDeniedTreatment adTreatment = AccessDeniedIsErrorInPrivateLocations);
	virtual GSErrCode	CreateLink	 (const Name& linkName, const Location& target);

	virtual GSErrCode	Rename		 (const Name& from, const Name& to, AccessDeniedTreatment adTreatment = AccessDeniedIsErrorInPrivateLocations);
	virtual GSErrCode	Move		 (const Name& from, Folder& target, const Name& to, DataSafety safety = Normal, AccessDeniedTreatment adTreatment = AccessDeniedIsErrorInPrivateLocations);
	virtual GSErrCode   Exchange     (const Name& from, const Name& to, AccessDeniedTreatment adTreatment = AccessDeniedIsErrorInPrivateLocations);
	virtual GSErrCode	Copy		 (const Name& from, const Name& to);
	virtual GSErrCode	Copy		 (const Name& from, Folder& target, const Name& to);
	virtual GSErrCode	Copy		 (const Name& from, Folder& target, const Name& to) const;
	virtual GSErrCode	Delete		 (const Name& name, DataSafety safety = Normal, AccessDeniedTreatment adTreatment = AccessDeniedIsErrorInPrivateLocations);
	virtual GSErrCode	DeleteAll	 (DataSafety safety = Normal, AccessDeniedTreatment adTreatment = AccessDeniedIsErrorInPrivateLocations);

		// Folder content query

	virtual GSErrCode	Contains		 (const Name& name, bool* result) const;
	virtual GSErrCode	GetType			 (const Name& name, EntryType* result) const;
	virtual GSErrCode	GetResolvedType  (const Name& name, EntryType* result) const;
	virtual GSErrCode	IsLink			 (const Name& name, bool* result) const;
	virtual GSErrCode	IsUsableAsFolder (const Name& name, bool* result) const;
	virtual GSErrCode	CountFiles		 (USize* result) const;
	virtual GSErrCode	CountFolders	 (USize* result) const;
	virtual GSErrCode	CountEntries	 (USize* result) const;
	virtual GSErrCode	IsEmpty			 (bool* result) const;

	GSErrCode			Enumerate	 (const std::function<void (const Name& name, bool isFolder)>& processor, GS::Tag<void>) const;
	GSErrCode			Enumerate	 (const std::function<bool (const Name& name, bool isFolder)>& processor, GS::Tag<bool>) const;

	template <class Callable>
	GSErrCode			Enumerate	 (const Callable& processor) const;

	virtual GSErrCode	Enumerate	 (EnumCallbackConst ec, void* userData = nullptr) const;
	virtual GSErrCode	Enumerate	 (EnumCallback ec, void* userData = nullptr);
	virtual GSErrCode	Enumerate	 (EnumCallbackConst ec, LinkProcessing lp, UInt32 typeFilter, void* userData = nullptr) const;
	virtual GSErrCode	Enumerate	 (EnumCallback ec, LinkProcessing lp, UInt32 typeFilter, void* userData = nullptr);
	virtual GSErrCode	PrintContent (GS::OChannel& oc) const;

	virtual	GSErrCode	GenerateUnusedName	(Name* result, const GS::UniString& prefix = DefaultBase, const GS::UniString& extension = "") const;
	
		// Folder attributes query / set

	virtual GSErrCode	SetCreationTime		(const GSTime& newTime);
	virtual GSErrCode	GetCreationTime		(GSTime* result) const;
	virtual GSErrCode	SetModificationTime (const GSTime& newTime);
	virtual GSErrCode	GetModificationTime (GSTime* result) const;

	virtual GSErrCode	GetFreeSpace (UInt64* result) const;

	virtual bool		IsReadable  (void) const;
	virtual bool		IsWriteable (void) const;

	virtual GSErrCode	IsOnLocalVolume	(bool* result) const;
	virtual GSErrCode	IsOnFixedVolume	(bool* result) const;

	virtual const BaseFileSystem*	GetOwnerFileSystem (void) const;

		// Location query

	virtual void		GetLocation (Location* result) const;
	virtual Location	GetLocation (void) const;
};


IO_DLL_EXPORT void	Append (GS::FastLogger::LogComposer& logComposer, const IO::Folder& folder);

}	// namespace IO



inline GSErrCode	IO::Folder::GetStatus (void) const
{
	return status;
}


template <class Callable>
GSErrCode	IO::Folder::Enumerate (const Callable& processor) const
{
	return Enumerate (processor, GS::Tag<GS::ResultType<Callable>> ());
}
// _______________________________ Class Folder ________________________________


#endif
