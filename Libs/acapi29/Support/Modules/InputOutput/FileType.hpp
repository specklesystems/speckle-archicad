// *****************************************************************************
//
//	                               Class FileType
//
// Module: Layer above IO
// Namespace: FTM
// Contact person: MD
//
// SG compatible
//
//------------------------------------------------------------------------
//
// The FileType class describes a file extension and/or MAC type
// group (i.e. *.htm;*.html). It provides sevices for identifing the
// type of a file.
//
// *****************************************************************************
#if !defined FILETYPE_HPP
#define FILETYPE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"
#include "File.hpp"


// ================================ Class FileType =================================

namespace FTM {

class FileTypeManager;

// Callback function that inspects a file and returns if it's a member of a
// given file type
typedef	bool (*FileTypeInspectorCallBack) (GS::IChannel& ic, void* retVal);

class IO_DLL_EXPORT FileType
{
friend class FileTypeManager;
private:
	UInt32					creator;			//MAC creator ID (i.e. "GSAC")
	int						iconID;				//Resource ID of icon
	IO::CString<32>			description;		//(name)

	char*					extList;			//null treminated list of extensions (no Unicode only MultiByte!!!)
	mutable char			extListBuffer[16];
	USize					extListSize;		//byte count of extList including last terminating null
	static const USize		defExtAllocSize;	//alloc step size for extList
	USize					extAllocSize;		//alloc size for extList


	UInt32*					macTypeList;
	mutable UInt32			macTypeListBuffer[4];
	USize					macTypeListSize;

	char*					mimeList;
	mutable char			mimeListBuffer[32];
	USize					mimeListSize;

	FileTypeInspectorCallBack pCallback;

	bool					hideMode;

	void					Copy (const FileType& source);
	void					Init (void);
	char*					GetExtList () const {return (extListSize <= sizeof (extListBuffer) ? extListBuffer : extList);}
	UInt32*					GetMacTypeList () const {return (macTypeListSize <= 4 ? macTypeListBuffer : macTypeList);}
	char*					GetMimeList () const {return (mimeListSize <= sizeof (mimeListBuffer) ? mimeListBuffer : mimeList);}

	GSErr					AddSingleExtension (const char* extension, bool toLower = true);
	GSErr					AddSingleMime (const char* mime);

	//fills an array with the ulong representation of the extension strings
	//it can be called with nullptr to get the size of the array
	int						GetExtensionIDs (UInt32* retArray, bool* truncatedArray = nullptr) const;
	Int32					ExtIndexCount (void) const;
	bool					GetMode (void) const;
	void					SetMode (bool mode);

public:
	//Default constructor
	FileType ();
	FileType (const FileType& source);
	FileType&				operator= (const FileType& source);

	//Simple constructor
	FileType(const char* description,
			 const char* fileExt,
			 UInt32 creator,
			 UInt32 macType,
			 int iconID,
			 FileTypeInspectorCallBack pCallbackIni = nullptr,
			 const char* mime = nullptr,
			 bool toLower = true);

	~FileType();

	void					Merge (const FileType& source);
	void					Subtract (const FileType& operand);

	bool					IsExtensionIncluded (const char* extension) const;
	bool                    IsExtensionIncluded (const GS::UniString& extension) const;
	const char*				GetExtension (UIndex index = 0) const;
	GSErr					AddExtension (const char* extListIni, bool toLower = true);
	int						FindExtension (const char* extension) const;
	bool					RemoveExtension (UIndex index);
	bool					RemoveExtension (const char* extension);
	int						CountExtensions (void) const;

	bool					IsMimeIncluded (const char* mime) const;
	const char*				GetMime (UIndex index = 0) const;
	GSErr					AddMime (const char* mimeListIni);
	int						FindMime (const char* mime) const;
	bool					RemoveMime (UIndex index);
	bool					RemoveMime (const char* mime);
	int						CountMimeTypes (void) const;

	bool					IsMacTypeIncluded (UInt32 macType) const;
	UInt32					GetMacType (UIndex index = 0) const;
	GSErr					AddMacType (UInt32 macType);
	int						FindMacType (UInt32 macType) const;
	bool					RemoveMacType (UIndex index);
	int						CountMacTypes (void) const;

	bool					CheckTypeCallback (GS::IChannel& ic, void* retVal=nullptr) const;
	inline UInt32			GetMacCreator (void) const { return creator; };
	inline int				GetIconID (void) const { return iconID; };
	inline const char*		GetDescription (void) const { return description; };
};

} //namespace FTM

#endif
