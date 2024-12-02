
// *****************************************************************************
//
//	                            Class FileSystem
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FILESYSTEM_HPP
#define FILESYSTEM_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "Array.hpp"
#include "Location.hpp"

namespace IO { class VirtualFileSystem; }
namespace IO { class FixedVFS; }
namespace IO { class RollingVFS; }
namespace IO { class FileEntry; }
namespace IO { class FolderEntry; }


// ============================= Class FileSystem ==============================

namespace IO {

enum UserInteractionControl {
	EnableUserInteraction,
	DisableUserInteraction,
};

enum UserInteractionControlOverride {
	OverrideNestedScopes
};


class IO_DLL_EXPORT FileSystem {
private:
	struct VirtualMountPoint {	// describes virtual mount points
		FixedVFS*	fvfs;			// fixed virtual file system
		Location	mountPoint;		// mount point of the fixed virtual file system

		VirtualMountPoint (): fvfs (nullptr) {}
	};

	GS::Array<VirtualMountPoint>					vmpTable;					// stores virtual mount points
	GS::Array<RollingVFS*>							rvfsTable;					// stores rolling virtual file systems
	mutable UIndex									lastUsedFixedVFS;			// index of the last used fixed virtual file system
	GS::Array<Location>								privateLocations;			// stores locations that are treated private (application expects that nobody else can use files or folders under these locations)
	UInt32											accessDeniedRetryDuration;	// duration in milliseconds while an operation that has been failed due to access denied is retried
	static const UInt32								AccessDeniedWaitTime;		// wait time between two trials of an operation that has been failed due to access denied

	FileSystem ();										// disabled
	FileSystem (const FileSystem& source);				// disabled
	FileSystem&	operator= (const FileSystem& source);	// disabled

	enum VMPConstraint {
		CanBeMountPoint,
		MustBeUnderMountPoint
	};
	VirtualMountPoint	FindVMP			(const Location& loc, VMPConstraint constraint) const;
	VirtualFileSystem*	FindVFS			(const Location& loc, VMPConstraint constraint) const;

	static GSErrCode	MapErrorCode	(GSErrCode errorCode);

	friend class UserInteractionControlScope;

	void	ControlUserInteraction   (UserInteractionControl userInteractionControl);
	bool	IsUserInteractionEnabled (void) const;

	void	EnableUserInteractionControl  (void);
	void	DisableUserInteractionControl (void);

public:
	/*!!!*/	static FileSystem	singleton;	// don't use this instance directly!

		// Error codes

	enum {
		FileNotFound	 = FileSystemErrors + 0,	// file is not found
		FolderNotFound	 = FileSystemErrors + 1,	// folder is not found
		SourceNotFound	 = FileSystemErrors + 2,	// source entry is not found
		TargetNotFound	 = FileSystemErrors + 3,	// target entry is not found
		TargetExists	 = FileSystemErrors + 4,	// target entry already exists
		NotAFile		 = FileSystemErrors + 5,	// not a file was specified
		NotAFolder		 = FileSystemErrors + 6,	// not a folder was specified
		AccessDenied	 = FileSystemErrors + 7,	// access to entry (file or folder) is denied
		DeviceIsFull	 = FileSystemErrors + 8,	// device is full
		VFSMounted		 = FileSystemErrors + 9,	// virtual file system is already mounted
		VFSNotFound		 = FileSystemErrors + 10,	// virtual file system is not found
		MountPointExists = FileSystemErrors + 11	// mount point already exists
	};

		// Types

	typedef bool	(CCALL *EnumMPCallback) (const Location& mountPoint, void* userData);
	typedef bool	(CCALL *EnumVMPCallback) (const Location& mountPoint, void* userData);

	enum SpecLocId {	// common identifiers for special locations
		System,
		ApplicationFile,
		ApplicationFolder,
		InstallationFolder,
		CurrentFolder,
		UserLocalSettings,
		UserLocalData,
		UserLocalCache,
		UserLocalLog,
		UserRoamingSettings,
		CommonLocalSettings,
		Desktop,
		TemporaryFolder,
		UserDocuments,
		CommonDocuments,
		CommonLocalData,
		CommonLocalLogs,
		UserHome,
		SharedComponents,
		SystemMain
	};

	enum EntryType { File, Folder, Link, Network };	// file system entry types

	enum DataSafety { Normal, IgnoreWriteProtection };	// data safety level for some operation

		// File system navigation

	GSErrCode	GetSpecialLocation (SpecLocId locId, Location* result) const;

	GSErrCode	ResolveLocation (const Location& source, Location* target) const;
	GSErrCode	ResolveLocation (Location* loc) const;

	GSErrCode	EnumerateMountPoints (EnumMPCallback ec, void* userData = nullptr) const;

		// Legality

	bool		IsLegal (const Location& loc) const;

		// Respond-time management

	bool		IsOnLine (const Location& loc) const;

	GSErrCode	EstimateResolvedType (const Location& loc, EntryType* result) const;

		// Utility methods

	GSErrCode	CreateFile	 (const Location& loc);
	GSErrCode	CreateFolder (const Location& loc, AccessDeniedTreatment adTreatment = AccessDeniedIsErrorInPrivateLocations);

	GSErrCode	CreateFolderTree (const Location& tree);
	GSErrCode	CreateFolderTree (const Location& root, const RelativeLocation& tree);

	GSErrCode	Rename (const Location& loc, const Name& to, AccessDeniedTreatment adTreatment = AccessDeniedIsErrorInPrivateLocations);
	GSErrCode	Move   (const Location& from, const Location& to, DataSafety safety = Normal);
	GSErrCode	Copy   (const Location& from, const Location& to);
	GSErrCode	Delete (const Location& loc, DataSafety safety = Normal, AccessDeniedTreatment adTreatment = AccessDeniedIsErrorInPrivateLocations);

	GSErrCode	GetType			 (const Location& loc, EntryType* result) const;
	GSErrCode	GetResolvedType	 (const Location& loc, EntryType* result) const;

	GSErrCode	Contains (const Location& loc, bool* result) const;

	GSErrCode	CountFiles (const Location& root, USize* result) const;
	GSErrCode	CountSize (const Location& root, UInt64* result) const;

		// Virtual file system control

	GSErrCode	Mount   (FixedVFS& fvfs, const Location& mountPoint);
	GSErrCode	Mount   (RollingVFS& rvfs);

	GSErrCode	Unmount (FixedVFS& fvfs);
	GSErrCode	Unmount (RollingVFS& rvfs);

	bool		IsMountPoint (const Location& loc) const;
	bool		IsUnderMountPoint (const Location& loc) const;

	GSErrCode	EnumerateVirtualMountPoints (EnumVMPCallback ec, void* userData = nullptr) const;

		// File system entry connection

	GSErrCode	Connect	(Location* fileLoc, FileEntry** imp);
	GSErrCode	Connect	(Location* folderLoc, FolderEntry** imp);

	void		Disconnect (FileEntry* connection);
	void		Disconnect (FolderEntry* connection);

		// User interaction control

	class IO_DLL_EXPORT UserInteractionControlScope {
	private:
		UserInteractionControl oldUserInteractionControl;
		bool				   overrideNestedScopes;

	public:
		UserInteractionControlScope (UserInteractionControl userInteractionControl);
		UserInteractionControlScope (UserInteractionControl userInteractionControl, UserInteractionControlOverride);

	   ~UserInteractionControlScope ();
	};

		// Access denied management

	enum AccessDeniedAction { Stop, Retry };

	void		AddPrivateLocation	  (const Location& rootLoc);
	void		DeletePrivateLocation (const Location& rootLoc);
	bool		IsPrivateLocation	  (const Location& loc) const;

	void		SetAccessDeniedRetryDuration (UInt32 duration);
	UInt32		GetAccessDeniedRetryDuration (void) const;

	void		InitAccessDeniedCounter (UInt32* counter) const;
	AccessDeniedAction	ProcessAccessDenied (const Location& loc, AccessDeniedTreatment adTreatment, UInt32* counter) const;

		// Disk error management

	enum DiskError { DiskIOError, DiskFull };

	bool	GetLastDiskError   (DiskError* lastDiskError, Location* lastDiskErrorLocation) const;
	void	ClearLastDiskError (void);
};


IO_DLL_EXPORT extern FileSystem&	fileSystem;	// single global FileSystem instance

}	// namespace IO

// _____________________________ Class FileSystem ______________________________


#endif
