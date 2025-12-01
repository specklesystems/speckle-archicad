// *****************************************************************************
// File:			DGFileDialog.hpp
//
// Description:		Common File Open and File Save dialogs
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	MD
//
// SG compatible
// *****************************************************************************

#ifndef DGFILEDIALOG_HPP
#define DGFILEDIALOG_HPP

#pragma once


// --- C++ interface -----------------------------------------------------------

// --- Includes ----------------------------------------------------------------

#include "Event.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"

#include "DGUtility.hpp"

#include "FileTypeManager.hpp"
#include "DGDialog.hpp"			// DG::Panel
#include "DGItem.hpp"			// ItemUpdateEvent
#include "DGSystemDialog.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace IO {
	class Location;
}

namespace DG {
	class FileDialog;
	class FileDialogImpl;
}

class EmbeddedLibraryTreeDialog;

namespace DG {


// --- Class declarations ------------------------------------------------------

// --- FileDialogEvent ---------------------------------------------------------

class DG_DLL_EXPORT FileDialogEvent: public GS::Event
{
	friend class SystemDialog;					// To access protected constructor

protected:
	FileDialogEvent (FileDialog* source);

public:
	~FileDialogEvent ();

	FileDialog*		GetSource (void) const;
};


// --- FileDialogIncludeFileEvent ----------------------------------------------

class DG_DLL_EXPORT FileDialogIncludeFileEvent: public FileDialogEvent
{
	friend class FileDialog;					// To access protected constructor

private:
	IO::Location	location;
	FTM::GroupID	rootID;

protected:
	FileDialogIncludeFileEvent (FileDialog* source, IO::Location location, FTM::GroupID rootID);

public:
	~FileDialogIncludeFileEvent ();

	const IO::Location&		GetLocation (void) const;
	const FTM::GroupID&		GetRootID (void) const;
};


// --- FileDialogFolderChangeEvent ---------------------------------------------

class DG_DLL_EXPORT FileDialogFolderChangeEvent: public FileDialogEvent
{
	friend class FileDialog;					// To access protected constructor

private:
	IO::Location	newLocation;

protected:
	FileDialogFolderChangeEvent (FileDialog* source, IO::Location newLocationIni);

public:
	~FileDialogFolderChangeEvent ();

	IO::Location	GetLocation (void) const;
};


// --- FileDialogSelectionChangeEvent ------------------------------------------

class DG_DLL_EXPORT FileDialogSelectionChangeEvent: public FileDialogEvent
{
	friend class FileDialog;					// To access protected constructor

protected:
	FileDialogSelectionChangeEvent (FileDialog* source);

public:
	~FileDialogSelectionChangeEvent ();

//	Use the FileDialog selection methods for selection details
};


// --- FileDialogFolderSelectionChangeEvent ------------------------------------

class DG_DLL_EXPORT FileDialogFolderSelectionChangeEvent: public FileDialogEvent
{
	friend class FileDialog;					// To access protected constructor

protected:
	FileDialogFolderSelectionChangeEvent (FileDialog* source);

public:
	~FileDialogFolderSelectionChangeEvent ();

//	Use the FileDialog GetSelectedFolder method for selection details
};


// --- FileDialogFilterChangeEvent ---------------------------------------------

class DG_DLL_EXPORT FileDialogFilterChangeEvent: public FileDialogEvent
{
	friend class FileDialog;					// To access protected constructor

private:
	UIndex	index;

protected:
	FileDialogFilterChangeEvent (FileDialog* source, UIndex newIndex);

public:
	~FileDialogFilterChangeEvent ();

	UIndex	GetIndex (void) const { return index; };
};


// --- FileDialogPreviewUpdateEvent --------------------------------------------

class DG_DLL_EXPORT FileDialogPreviewUpdateEvent: public FileDialogEvent
{
	friend class FileDialog;				// To access protected constructor

private:
	DG::UserItemUpdateEventArg*	updateData;

protected:
	FileDialogPreviewUpdateEvent (FileDialog* source, DG::UserItemUpdateEventArg* updateData);

public:
	~FileDialogPreviewUpdateEvent ();

	void*	GetDrawContext (void) const;

	Rect	GetClientRect (void) const;
	short	GetClientWidth (void) const;
	short	GetClientHeight (void) const;
};


// --- FileDialogObserver ------------------------------------------------------

class DG_DLL_EXPORT FileDialogObserver: public SystemDialogObserver
{
	friend class FileDialog;					// To access protected observer methods

protected:
	virtual void	IncludeFile (const FileDialogIncludeFileEvent& ev, bool* enable);
	virtual void	FolderChanged (const FileDialogFolderChangeEvent& ev);
	virtual void	SelectionChanged (const FileDialogSelectionChangeEvent& ev);
	virtual void	FolderSelectionChanged (const FileDialogFolderSelectionChangeEvent& ev);
	virtual void	FilterChanged (const FileDialogFilterChangeEvent& ev);
	virtual void	PreviewUpdate (const FileDialogPreviewUpdateEvent& ev, bool* userDraw);
};


// --- FileDialog --------------------------------------------------------------

class DG_DLL_EXPORT FileDialog: public SystemDialog
{
	friend class FileDialogImpl;
	friend class EmbeddedLibraryTreeDialog;

public:
	enum ExtensionOptions {
		SystemDefault,
		DisplayExtensions,
		DontDisplayExtensions
	};

	enum Type {
		OpenFile,
		OpenMultiFile,
		OpenFolder,
		OpenMultiFolder,
		Save
	};

	struct PopupData
	{
		FTM::GeneralID		id;
		GS::UniString		text;			// should be GS::string
		void*				data;

		~PopupData () {}	// to avoid LINT e118
	};
	static GS::UniString	allFilesText;

private:
	PopupData*			popupData;
	USize				popupCount;
	static const USize	popupDataPageSize;
	UIndex				defaultPopup;

	IO::Location*		selectionData;
	USize				selectionCount;
	static const USize	selectionDataPageSize;

	IO::Location		selectedFolder;		// for OpenFolder dialog type

	bool                has31CharacterFileLimit;

	FileDialog (const FileDialog& source);				// disabled
	FileDialog& operator= (const FileDialog& source);	// disabled

	IO::Location		defLocation;
	bool				autoDefLocation;
	FTM::GroupID		filterRoot;
	Type				dialogType;

	FileDialogImpl*	GetImpl () const;

	virtual bool	ProcessIncludeFile (const IO::Location location);
	virtual void	ProcessFolderChange (const IO::Location newLocation);
	virtual void	ProcessSelectionChange (void);
	virtual void	ProcessFolderSelectionChange (const IO::Location selFolder);
	virtual void	ProcessFilterChange (UIndex newIndex);
	virtual bool	ProcessPreviewUpdate (DG::UserItemUpdateEventArg* updateData);

	bool			AddSelection (const IO::Location& loc);
	bool			RemoveSelection (const IO::Location& loc);
	Int32			SearchSelection (const IO::Location& loc) const;
	void			ClearSelection (void);

	bool            IsInvalidLocation (const IO::Location& loc) const;

public:
					FileDialog (Type type);
	virtual			~FileDialog ();

	// Filter methods
	void			SetFilterRoot (FTM::GroupID groupID);

	// Filter popup methods
	UIndex			AddFilter (FTM::GeneralID id, ExtensionOptions options = SystemDefault);
	UIndex			AddFilterTypeChildren (FTM::GroupID groupID, ExtensionOptions options = SystemDefault);
	UIndex			AddFilterGroupChildren (FTM::GroupID groupID, ExtensionOptions options = SystemDefault);
	bool			InsertFilter (UIndex index, FTM::GeneralID id);
	bool			ReplaceFilter (UIndex index, FTM::GeneralID id, ExtensionOptions options = SystemDefault);
	bool			RemoveFilter (UIndex index);
    Int32           RemoveFilterById (FTM::GeneralID id);
	void			SortFilters (void);

	FTM::GeneralID	GetFilterId (UIndex index) const;
	void*			GetFilterData (UIndex index) const;
	GS::UniString	GetFilterText (UIndex index) const;
	bool			SetFilterId (UIndex index, const FTM::GeneralID& ftmId);
	bool			SetFilterData (UIndex index, void* data);
	bool			SetFilterText (UIndex index, const GS::UniString& text);

	USize			GetFilterCount (void) const;
	UIndex			GetSelectedFilter (void) const;
	bool			SelectFilter (UIndex index);
	Int32			SearchFilter (const GS::UniString& extension) const;

	// Current folder methods
	bool			GetFolder (IO::Location* retLocation) const;
	bool			SetFolder (const IO::Location& location);

	// File-Folder selection methods for OpenFolder-type dialog
	const IO::Location&		GetSelectedFolder (void) const;
	const IO::Location&		GetSelectedLocation (void) const;

	// File selection methods
	USize					GetSelectionCount (void) const;
	const IO::Location&		GetSelectedFile (UIndex index = 0) const;

	bool			SelectFile (IO::Location location, bool needToDeleteExtension = true);
	bool			DeselectFile (IO::Location location);
	bool			IsFileSelected (IO::Location location) const;

	GS::UniString	GetEditTextValue (void) const;

	// Preview
	void			EnablePreview (void);
	void			DisablePreview (void);
	bool			IsPreviewEnabled (void) const;
	bool			IsPreviewVisible (void) const;

	// Other methods
	void			Refresh (void);
	void            ShowMacPackagesInDialog (void);

	void			Set31CharacterFileLimit (bool enable);
	bool			Has31CharacterFileLimit () const;

	// PopupData query methods
	const PopupData*	GetPopupData () const;
	USize				GetPopupCount () const;
};

class DG_DLL_EXPORT FileTypeGuard {
public:
	FileTypeGuard (const GS::Array<FTM::TypeID>& fileTypes);
	~FileTypeGuard ();
};

}	// namespace DG

#endif
