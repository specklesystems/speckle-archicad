// *****************************************************************************
//
//	                               Class FileTypeManager
//
// Module: Layer above IO
// Namespace: FTM
// Contact person: MD
//
// SG compatible
//
//------------------------------------------------------------------------
//
// FileTypeManager is used to manage file extensions and MAC types in a platform
// independent way.
//
// *****************************************************************************


#if !defined FILETYPEMANAGER_HPP
#define FILETYPEMANAGER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include <limits.h>
#include "IOBase.hpp"
#include "FileType.hpp"

typedef GS::IntPtr GSResModule;

namespace FTM {

class GroupID;
class TypeID;


// --------------------------------- Constants ----------------------------------

IO_DLL_EXPORT extern const GroupID	RootGroup;
IO_DLL_EXPORT extern const GroupID	UnknownGroup;
IO_DLL_EXPORT extern const TypeID	UnknownType;


// ================================ Class GeneralID =============================

class IO_DLL_EXPORT GeneralID
{
	friend class TypeID;
	friend class GroupID;
protected:
	GeneralID (Int32 init) {data = init;}

	Int32 data = 0;

	//operators for binary search
	bool	operator<= (const GeneralID& rightOp) const {return (data <= rightOp.data);}
	bool	operator< (const GeneralID& rightOp) const {return (data < rightOp.data);}
	bool	operator>= (const GeneralID& rightOp) const {return (data >= rightOp.data);}
	bool	operator> (const GeneralID& rightOp) const {return (data > rightOp.data);}

public:

	GeneralID () = default;

	bool	operator== (const GeneralID& rightOp) const {return (data == rightOp.data);}
	bool	operator!= (const GeneralID& rightOp) const {return (data != rightOp.data);}

	bool	IsGroup (void) const { return (data < 0); }

	void	Store (UInt32& extData) const {extData = (UInt32) data;}
	void	Load (UInt32 extData) {data = (Int32) extData;}

	ULong	GenerateHashValue (void) const		{	return GS::CalculateHashValue (data);	}
};


// ================================ Class TypeID ================================

class IO_DLL_EXPORT TypeID: public GeneralID
{
	friend class FileTypeManager;
private:
	static Int32 nextID;
	static TypeID NextID () { return (DBERROR (nextID == GS::MaxInt32) ? UnknownType : TypeID(nextID++)); }
public:
	TypeID () = default;

	TypeID (const GeneralID& initOp)
	{
		data = 0; //UnknownType
		if (!DBERROR (initOp.IsGroup ()))
			initOp.Store ((UInt32&) data);
	}
};


// ================================ Class GroupID ===============================

class IO_DLL_EXPORT GroupID: public GeneralID
{
	friend class FileTypeManager;
private:
	static Int32 nextID;
	static GroupID NextID () { return (DBERROR (nextID == -2) ? UnknownGroup : GroupID(nextID++)); }
public:
	GroupID () {data = -1;} //UnknownGroup
	GroupID (const char*) {data = INT_MIN;} //RootGroup
	GroupID (const GeneralID& initOp) {
		data = -1; //UnknownGroup
		if (!DBERROR (!initOp.IsGroup()))
			initOp.Store((UInt32&)data);
	}
};


// ================================ Class FileTypeManager =======================

class IO_DLL_EXPORT FileTypeManager
{

private:
	FileTypeManager();												// disabled
	FileTypeManager (const FileTypeManager& source);				// disabled
	FileTypeManager& operator= (const FileTypeManager& source);		// disabled

	IO::CString<64>		uniqueID;				//identifying different type managers

	//internal database structure
	struct ExtensionIndexRecord
	{
		Int32			typeIndex;				//record index of associated type data in hTypeDataArray
		UInt32			extension;				//first four bytes of extension
		bool			truncated;				//indicates if extension is larger than stored data
		UInt32			macType;				//MAC type ID used only at zero extension
	};
	static GSHandle		hExtensionIndexArray;	//extensions in handle sorted by extension than macType


	struct MimeIndexRecord
	{
		UIndex			index;					//record index of associated type or group data
		UInt32			mimeHash;				//hash digest of mime string
		bool			isType;					//type or group
	};
	static GSHandle		hMimeIndexArray;		//sorted by mime


	struct TypeDataRecord
	{
		FileTypeManager*	pManager;			//pointer of type manager which inserted the entry;
		TypeID				externalID;			//external ID of file type
		FileType			fileType;			//data storage of type info
		bool				tempCallbackResult;	//temp storage of callback result
	};
	static GSHandle			hTypeDataArray;		//type data sorted by externalID


	struct GroupDataRecord
	{
		Int32				parentIndex;		//index of parent group -1 if top
		IO::CString<16>		name;
		FileTypeManager*	pManager;			//pointer of type manager which inserted the entry;
		GroupID				externalID;			//external ID of group
		IO::CString<64>		mime;
	};
	static GSHandle			hGroupDataArray;	//group data sorted by external ID


	struct TypeGroupRecord
	{
		TypeID				typeID;				//external ID of file type
		GroupID				groupID;			//external ID of group
	};
	static GSHandle			hTypeGroupArray;	//type->group association data sorted by typeID, groupID


	Int32					InsertExtension (ExtensionIndexRecord extensionIndex);
	static UIndex			InsertMime (const MimeIndexRecord& mimeIndex);
	static void				RemoveMime (UIndex typeIndex, bool isType, bool reindex = true);
	bool					CheckMimeExists (const char* mime);

	static Int32			SearchForExtension (UInt32 extension, UInt32 macType=0);
	static Int32			SearchForTypeRec (TypeID externalID);
	static Int32			SearchForGroupRec (GroupID externalID);
	static Int32			SearchForTypeGroup (TypeID typeID, GroupID groupID);
	static UIndex			SearchForMimeIndex (UInt32 mimeHash);

	static void				RemoveDataRecord (Int32 recordIndex);

	static FileTypeManager* GetManager (GeneralID ftmID);
	static Int32			ConvertExtension (const char* chExtension, bool* truncated);
	static UInt32			HashKey (const char* key);

public:
	// Error codes
	enum {
		TypeNotFound	= IO::TypeErrors + 0,
		GroupNotFound	= IO::TypeErrors + 1,
		AccessDenied	= IO::TypeErrors + 2
	};

	FileTypeManager (const char* uniqueID);
	~FileTypeManager();


	//Identifies a location using data stored in database
	static GeneralID  CCALL	Identify (const IO::Location& loc, GroupID rootGroupID = RootGroup, void* retVal = nullptr);
	GeneralID				IdentifyOwn (const IO::Location& loc, GroupID rootGroupID = RootGroup, void* retVal = nullptr) const ;
	static USize	  CCALL	Identify (const IO::Location& loc, TypeID* retList, USize listSize, GroupID rootGroupID = RootGroup, void** retVal = nullptr);
	USize					IdentifyOwn (const IO::Location& loc, TypeID* retList, USize listSize, GroupID rootGroupID = RootGroup, void** retVal = nullptr) const ;
	static bool		  CCALL	Match (const IO::Location& loc, GeneralID referenceID, GroupID rootGroupID = RootGroup);
	bool					MatchOwn (const IO::Location& loc, GeneralID referenceID, GroupID rootGroupID = RootGroup) const;
	static bool		  CCALL	ExactMatch (const IO::Location& loc, GeneralID referenceID, GroupID rootGroupID = RootGroup);
	bool					ExactMatchOwn (const IO::Location& loc, GeneralID referenceID, GroupID rootGroupID = RootGroup) const;

	TypeID					AddType (const FileType& newType, GroupID ParentGroupID = RootGroup);
	GSErrCode				ReinsertType (TypeID typeID, const FileType& newType);
	GSErrCode				RemoveType (TypeID typeID);
	static GSErrCode  CCALL	GetType (TypeID typeID, FileType* retType);
	static bool		  CCALL	SetModeFileType (TypeID typeID, bool hide);
	static bool		  CCALL	IsHideFileType (TypeID typeID);
	static const char* CCALL GetManagerId (GeneralID id);

	GroupID					AddGroup (const char* name, GroupID parentGroupID = RootGroup, const char* mime = nullptr);
	GSErrCode				RemoveGroup (GroupID groupID);
	GSErrCode				AddTypeToGroup (TypeID typeID, GroupID parentGroupID);
	GSErrCode				RemoveTypeFromGroup (TypeID typeID, GroupID parentGroupID);
	GSErrCode				RenameGroup (GroupID groupID, const char* name);
	static USize	  CCALL GetGroupName (GroupID groupID, char* retName, USize length = 0);
	static USize	  CCALL	GetGroupExtensionList (GroupID parentGroupID, char* retList, USize length);
	static USize	  CCALL GetGroupMime (GroupID groupID, char* retMime, USize length = 0);

	static bool		  CCALL IsGroupInGroup (GroupID groupID, GroupID parentGroupID);
	static bool		  CCALL IsTypeInGroup (TypeID typeID, GroupID parentGroupID);
	static bool		  CCALL IsTypeOrGroupInTypeOrGroup (GeneralID id, GeneralID parentID);
	static bool		  CCALL IsExtensionInGroup (const GS::UniString& extension, const FTM::GroupID& groupId);

	static Int32	  CCALL CountAllChild (GroupID parentGroupID);
	static Int32	  CCALL CountGroupChild (GroupID parentGroupID);
	static Int32	  CCALL CountParent (TypeID childtypeID);
	static Int32	  CCALL CountTypeChild (GroupID parentGroupID);
	static Int32	  CCALL CountAllTypeChild (GroupID parentGroupID);
	static Int32	  CCALL GetAllTypeChildList (GroupID parentGroupID, TypeID* typeIDArray, Int32 arraySize);

	static GroupID	  CCALL GetFirstGroupChild (GroupID parentGroupID);
	static GroupID	  CCALL GetFirstParent (TypeID childtypeID);
	static TypeID	  CCALL GetFirstTypeChild (GroupID parentGroupID);
	static GroupID	  CCALL GetNextGroup (GroupID prevGroupID);
	static GroupID	  CCALL GetNextParent (TypeID childTypeID,GroupID prevGroupID);
	static TypeID	  CCALL GetNextType (GroupID parentGroupID,TypeID prevTypeID);
	static GroupID	  CCALL GetParent (GroupID childGroupID);

	static TypeID	  CCALL SearchForType (FileType refType, GroupID parentGroupID = RootGroup);
	static USize	  CCALL SearchForType (TypeID*		retList,
										   USize		listSize,
										   FileType		refType,
										   GroupID parentGroupID = RootGroup);

	static GroupID	  CCALL SearchForGroup (const char*	name, GroupID parentGroupID = RootGroup);
	static USize	  CCALL SearchForGroup (GroupID*	retList,
											USize		listSize,
											const char*	name,
											GroupID parentGroupID = RootGroup);
	GeneralID				SearchForMime (const char* mime) const;
	static GeneralID  CCALL SearchForMime (const char* mime, const char* managerID);
	static bool		  CCALL IsMimeRegistered (const char* mime, const char* managerID);

	//Input/Output
	static GeneralID  CCALL ReadID (GS::IChannel& ic, const char* managerId = nullptr);
	static GSErrCode  CCALL WriteID (GeneralID id, GS::OChannel& oc);

	static const char*  CCALL Dump (GroupID parentGroupID = RootGroup, int depth = 0);
#ifdef CHECKED_VERSION
	static IO::CString<1024>	strDump;
	const char*		dump;
#endif
};


// ======================= Return structures for file type callbacks ======================
struct IO_DLL_EXPORT ImageTypeCallbackInfo
{
	short pixelDepth;
	short hsize;
	short vsize;
};

IO_DLL_EXPORT void LoadFTMDefaults (FileTypeManager* pManager);

IO_DLL_EXPORT FTM::GroupID	FTMReadFTGPResource (FTM::FileTypeManager* pManager, FTM::GroupID parentGroup, GSResModule resModule, Int32 resID);


// =========================== Callbacks and type exports for common file types ============================

IO_DLL_EXPORT extern const GroupID&	ImageGroup;
IO_DLL_EXPORT extern const GroupID&	DocumentGroup;

IO_DLL_EXPORT extern const TypeID&	TextFileType;
IO_DLL_EXPORT bool					TextTypeCallback (GS::IChannel& ic, void* retVal);

IO_DLL_EXPORT extern const TypeID&	TIFFFileType;
IO_DLL_EXPORT bool					TIFFTypeCallback (GS::IChannel& ic, void* retVal);

IO_DLL_EXPORT extern const TypeID&	JPEGFileType;
IO_DLL_EXPORT bool					JPEGTypeCallback (GS::IChannel& ic, void* retVal);

IO_DLL_EXPORT extern const TypeID&	BMPFileType;
IO_DLL_EXPORT bool					BMPTypeCallback (GS::IChannel& ic, void* retVal);

IO_DLL_EXPORT extern const TypeID&	EMFFileType;
IO_DLL_EXPORT bool					EMFTypeCallback (GS::IChannel& ic, void* retVal);

IO_DLL_EXPORT extern const TypeID&	WMFFileType;
IO_DLL_EXPORT bool					WMFTypeCallback (GS::IChannel& ic, void* retVal);

IO_DLL_EXPORT extern const TypeID&	HTMFileType;
IO_DLL_EXPORT bool					HTMTypeCallback (GS::IChannel& ic, void* retVal);

IO_DLL_EXPORT extern const TypeID&	PDFFileType;
IO_DLL_EXPORT bool					PDFTypeCallback (GS::IChannel& ic, void* retVal);

IO_DLL_EXPORT extern const TypeID&	EXEFileType;
IO_DLL_EXPORT bool					EXETypeCallback (GS::IChannel& ic, void* retVal);

IO_DLL_EXPORT extern const TypeID&	GIFFileType;
IO_DLL_EXPORT bool					GIFTypeCallback (GS::IChannel& ic, void* retVal);

} //namespace FTM


#endif
