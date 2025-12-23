// *********************************************************************************************************************
// Description:		Extension Manager Types
//
// Module:			InputOutput
// Namespace:		FTM
// Contact person:	CsAd
//
// SG compatible
// *********************************************************************************************************************

#ifndef FILETYPELIST_HPP
#define FILETYPELIST_HPP

#pragma once

// from InputOutput
#include "IOBase.hpp"
#include "FileTypeManager.hpp"

// from GSRoot
#include "HashSet.hpp"
#include "HashTable.hpp"

namespace FTM {


class IO_DLL_EXPORT FileTypeList
{
public:
	class IO_DLL_EXPORT EntryProcessor
	{
	public:
		virtual ~EntryProcessor ();

		virtual void	ProcessFileType		(const GS::UniString& descriptionText, const GS::HashSet<GS::UniString>& extensions, const TypeID& fileTypeId) = 0;
		virtual void	ProcessGroupType	(const GS::UniString& descriptionText, const GS::HashSet<GS::UniString>& extensions, const GroupID& groupId) = 0;
	};

private:
	class IO_DLL_EXPORT EntryDescriptor
	{
	private:
		GS::UniString descriptionText;
		GS::HashSet<GS::UniString> extensions;
		GeneralID typeId;
		
	public:
		EntryDescriptor (const GS::UniString& descriptionText, const GS::UniString& extension, const TypeID& fileTypeId);
		EntryDescriptor (const GS::UniString& descriptionText, const GS::HashSet<GS::UniString>& extensions, const TypeID& fileTypeId);
		EntryDescriptor (const GS::UniString& descriptionText, const GS::HashSet<GS::UniString>& extensions, const GroupID& groupId);

		void	Process	(EntryProcessor& processor) const;
	};

	GS::HashTable<GeneralID, EntryDescriptor> list;
	GS::HashTable<GS::UniString, GeneralID> extensionToFileType;

public:
	FileTypeList ();
	~FileTypeList ();
	
	void	AddFileType			(const TypeID& fileTypeId);
	void	AddChildrenOfGroup	(const GroupID& groupId);

	void	RemoveFileType		(const TypeID& fileTypeId);

	void	AddFileType			(const FileType& fileType, const TypeID& fileTypeId);
	void	AddFileType			(const GS::UniString& descriptionText, const GS::HashSet<GS::UniString>& extensions, const TypeID& fileTypeId);
	void	AddGroupType		(const GS::UniString& descriptionText, const GS::HashSet<GS::UniString>& extensions, const GroupID& groupId);

	void	EnumerateEntries (EntryProcessor& processor) const;
	void	FindAndProcessEntry (const GeneralID& typeIdToFind, EntryProcessor& processor) const;

	GS::Optional<GS::UniString>		GetFirstExtension			(const GeneralID& typeId) const;
	GeneralID						GetMatchingTypeForFileName	(const GS::UniString& fileName) const;
	GeneralID						GetMatchingTypeByFTM		(const IO::Location& openableFileLocation) const;
	bool							ShouldFilterFile			(const GS::UniString& fileName) const;
};


}	// namespace FTM

#endif	// FILETYPELIST_HPP