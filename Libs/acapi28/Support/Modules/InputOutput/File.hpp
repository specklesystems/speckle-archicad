
// *****************************************************************************
//
//	                               Class File
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FILE_HPP
#define FILE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "Location.hpp"
#include "Name.hpp"
#include "InputBuffer.hpp"
#include "OutputBuffer.hpp"


namespace IO {
	class BaseFileSystem;
	class FileEntry;
	class Folder;
}
typedef	Int32 GSTime;	// definition from GSTime.h is repeated because GSTime is not of
						// class type and GSTime.h can not be included, but this is ugly


// ================================ Class File =================================

namespace IO {

class IO_DLL_EXPORT File: public GS::IChannel,
						  public GS::OChannel,
						  private GS::InputBuffer::BinInput,
						  private GS::OutputBuffer::BinOutput
{
public:
	enum OpenMode {		// possible modes in which file can be opened
		ReadMode,
		WriteMode,
		WriteEmptyMode,
		ReadWriteMode,
		AppendMode,
		ReadSharedRWMode,
		WriteSharedRMode,
		WriteEmptySharedRMode,
		ReadWriteSharedRMode
	};

private:
	enum FileStatus { Opened, Closed };

	Location	location;	// location of the file
	FileEntry*	imp;		// points to the object implementing the file on the current platform

	mutable GS::InputBuffer		inputBuffer;	// input buffer of the File
	mutable GS::OutputBuffer	outputBuffer;	// output buffer of the File

	OpenMode	openMode;			// stores mode in which the file was opened
	FileStatus	fileStatus;			// indicates whether is the file opened
	bool		isReadEnabled;		// read operations are enabled if it is true (redundant for efficiency)
	bool		isWriteEnabled;		// write operations are enabled if it is true (redundant for efficiency)
	bool		isRandomEnabled;	// random operations are enabled if it is true (redundant for efficiency)

	UInt64		filePosition;		// current position (in characters) in the file

	GSErrCode	status;				// object state (error code saved in constructor)

	static const USize	BufferCapacity;	// initial capacity of the internal buffers


	File (const File& source);				// disabled
	File&	operator= (const File& source);	// disabled

	void				Init (void);

	inline bool			CheckReadOperation	 (void) const;
	inline bool			CheckWriteOperation	 (void) const;
	inline bool			CheckRandomOperation (void) const;

	void				SetFileStatus (FileStatus fs);

	virtual GSErrCode	InternalRead  (char* destination, USize nOfCharToRead, USize* read) override;
	virtual GSErrCode	InternalWrite (const char* source, USize nOfCharToWrite, USize* written) override;

	static GSErrCode	Connect (Location* loc, FileEntry** imp);
	static void			LogConnection (GSErrCode status, const Location& fileLoc, bool ignoreFileNotFound);
	void				LogError (GS::ErrorLogLine& errorLog) const;

public:
		// Error codes

	enum {
		FileNotFound	= FileErrors + 0,	// file is not found, connection failed
		NotAFile		= FileErrors + 1,	// not a file was specified, connection failed
		AccessDenied	= FileErrors + 2,	// access to file or file data is denied
		CreationError	= FileErrors + 3,	// creation of the file is failed
		NoMoreOSFile	= FileErrors + 4,	// file can not be opened because there is no free OS handle
		IllegalPosition	= FileErrors + 5,	// illegal file position was specified
		InvalidTime		= FileErrors + 6	// invalid time is encountered
	};

		// Types

	enum OnNotFound { Fail, Create, Ignore };		// what to do if the file doesn't exist
	enum SeekOrigin { Start, Current, End };		// possible origins for the seek operation
	enum WriteAccessFailureReason { WriteProtection, Authorization, Exclusion, Unknown };	// possible reasons of a failed write access attempt

	class Mapping;

		// Constructors

	explicit File (const Location& loc, OnNotFound action = Fail);
	File (const Folder& parent, const Name& fileName);
	File (Folder& parent, const Name& fileName, OnNotFound action);
   ~File ();

	static GSErrCode	CCALL New (File** result, const Location& loc, OnNotFound action = Fail);
	static GSErrCode	CCALL New (File** result, const Folder& parent, const Name& fileName);
	static GSErrCode	CCALL New (File** result, Folder& parent, const Name& fileName, OnNotFound action);

		// State query

	inline GSErrCode	GetStatus (void) const;

		// File content (raw data) manipulation

	virtual GSErrCode	Open		(OpenMode om, AccessDeniedTreatment adTreatment = AccessDeniedIsErrorInPrivateLocations);
	virtual	bool		IsOpen		(void) const;
	virtual	bool		IsOpenable	(OpenMode om) const;
	virtual GSErrCode	Close		(void);

	using GS::IChannel::ReadBin;
	using GS::OChannel::WriteBin;

	virtual GSErrCode	ReadBin		(char* destination, USize nOfCharToRead, USize* read = nullptr) override;
	virtual GSErrCode	CopyBin		(char* destination, USize nOfCharToCopy, USize* copied = nullptr) override;
	virtual GSErrCode	Look		(UIndex idx, char* c) override;
	virtual	GSErrCode	PushBack	(const char* source, USize nOfChar) override;
	virtual	GSErrCode	PushBack	(char c) override;
	virtual	GSErrCode	Skip		(UInt64 nOfCharToSkip, UInt64* skipped = nullptr) override;
	virtual	GSErrCode	DirectInputAccess (USize nOfCharToAccess, char** source, USize* accessible = nullptr) override;
	virtual GSErrCode	GetInputPosition (UInt64* position) const override;
	virtual GSErrCode	GetAvailable     (UInt64* available) const override;

	virtual GSErrCode	WriteBin	(const char* source, USize nOfCharToWrite, USize* written = nullptr) override;
	virtual	GSErrCode	DirectOutputAccess (UIndex startPosition, char** output, USize* accessibleDataSize) override;
	virtual GSErrCode	Flush		(void) override;

	virtual GSErrCode	SetPosition (UInt64 newPos);
	virtual GSErrCode	GetPosition (UInt64 *result) const;
	inline UInt64		GetPosition (void) const;
	virtual GSErrCode	GetOutputPosition (UInt64 *result) const override;
	virtual GSErrCode	GetPosition (USize *result) const;
	virtual GSErrCode	Seek		(SeekOrigin so, Int64 offset);

		// Block support

	virtual GSErrCode	PushMark	(void) override;
	virtual GSErrCode	PopMark		(void) override;
	virtual USize		GetOffset	(void) const override;
	virtual void		ResetOffset	(void) override;

		// File attributes set / query

	virtual GSErrCode	SetDataLength		(UInt64 newLength);
	virtual GSErrCode	GetDataLength		(UInt64* result) const;
	virtual GSErrCode	GetDataLength		(USize* result) const;

	virtual GSErrCode	SetCreationTime		(const GSTime& newTime);
	virtual GSErrCode	GetCreationTime		(GSTime* result) const;
	virtual GSErrCode	SetModificationTime (const GSTime& newTime);
	virtual GSErrCode	GetModificationTime (GSTime* result) const;

	virtual GSErrCode	SetTypeInfo (UInt32 newType, UInt32 newCreator);
	virtual GSErrCode	GetTypeInfo (UInt32* type, UInt32* creator) const;

	virtual bool		IsReadable  (void) const;
	virtual bool		IsWriteable (void) const;
	virtual bool		IsWriteable (WriteAccessFailureReason* reason, GS::UniString* reasonParameters) const;

	virtual GSErrCode	IsWriteProtected	 (bool* result) const;
	virtual GSErrCode	SetWriteProtection   (void);
	virtual GSErrCode	ClearWriteProtection (void);

	virtual const BaseFileSystem*	GetOwnerFileSystem (void) const;

		// Default protocol restoring

	virtual void		SetDefaultInputProtocol  (void) override;
	virtual	void		SetDefaultOutputProtocol (void) override;

		// Channel status query and reset

	virtual GSErrCode	GetInputStatus	 (void) const override;
	virtual void		ResetInputStatus (void) override;

	virtual GSErrCode	GetOutputStatus	  (void) const override;
	virtual void		ResetOutputStatus (void) override;

		// Location query

	virtual void		GetLocation (Location* result) const;
	virtual Location	GetLocation (void) const;

		// File mapping

	virtual	Mapping		CreateMapping (UInt64 offset, USize size);
	virtual	void		CloseMapping (Mapping& mapping);

		// Types

	class IO_DLL_EXPORT Mapping {
	private:
		void*	address;
		USize	size;

	public:
		Mapping (void* address, USize size);

		void*	GetAddress () const;
		USize	GetSize () const;
	};
};

}	// namespace IO



inline GSErrCode	IO::File::GetStatus (void) const
{
	return status;
}


UInt64	IO::File::GetPosition (void) const
{
	return filePosition;
}
// ________________________________ Class File _________________________________


#endif
