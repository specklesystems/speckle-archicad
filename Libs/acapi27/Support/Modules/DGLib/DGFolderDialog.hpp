// *****************************************************************************
// File:			DGFolderDialog.hpp
//
// Description:		Folder Browser dialog
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	MD
//
// SG compatible
// *****************************************************************************

#ifndef DGFOLDERDIALOG_HPP
#define DGFOLDERDIALOG_HPP

#pragma once

// --- Predeclarations ---------------------------------------------------------

namespace IO {
	class Location;
}

// --- C++ interface -----------------------------------------------------------

// --- Includes ----------------------------------------------------------------

#include "Event.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"

#include "DGUtility.hpp"

#include "DGDialog.hpp"			//DG::Panel
#include "DGSystemDialog.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class FolderDialog;
	class FolderDialogImpl;
}


namespace DG {

// --- Class declarations ------------------------------------------------------

// --- FolderDialogEvent -------------------------------------------------------

class DG_DLL_EXPORT FolderDialogEvent: public GS::Event
{
	friend class SystemDialog;					// To access protected constructor

protected:
	FolderDialogEvent (FolderDialog* source);

public:
	~FolderDialogEvent ();

	FolderDialog*	GetSource (void) const;
};


// --- FolderDialogSelectionChangeEvent ----------------------------------------

class DG_DLL_EXPORT FolderDialogSelectionChangeEvent: public FolderDialogEvent
{
	friend class FolderDialog;					// To access protected constructor

private:
	IO::Location newLocation;

protected:
	FolderDialogSelectionChangeEvent (FolderDialog* source, IO::Location newLocationIni);

public:
	~FolderDialogSelectionChangeEvent ();

	IO::Location GetLocation (void) const;
};


// --- FolderDialogObserver ----------------------------------------------------

class DG_DLL_EXPORT FolderDialogObserver: public SystemDialogObserver
{
	friend class FolderDialog;					// To access protected observer methods

protected:
	virtual void	SelectionChanged (const FolderDialogSelectionChangeEvent& ev);
};


// --- FolderDialog ------------------------------------------------------------

class DG_DLL_EXPORT FolderDialog: public SystemDialog
{
	friend class FolderDialogImpl;
	friend class SystemDialogPanel; //SetCustomPanel

private:
	FolderDialog (const FolderDialog& source);				// disabled
	FolderDialog& operator= (const FolderDialog& source);	// disabled

	IO::Location					location;
	bool							autoDefLocation;

	virtual void	ProcessSelectionChange (const IO::Location newLocation);

public:
					FolderDialog ();
	virtual			~FolderDialog ();

	// Current folder methods
	IO::Location	GetFolder (void) const;
	bool			SetFolder (const IO::Location& location);
};


// --- FolderDialogImpl --------------------------------------------------------

class FolderDialogImpl: public virtual SystemDialogImpl
{
	friend class FolderDialog;

protected:
	virtual ~FolderDialogImpl ();

	static FolderDialogImpl*	CreateImpl (FolderDialog* folderDialog);
	virtual bool	GetFolderLocation (IO::Location* retLocation) = 0;
	virtual bool	SetLocation (const IO::Location* location) = 0;

	inline FolderDialog*	GetFolderDialog ();
	//backway calls context data pull
	inline IO::Location*	GetLocation (void);
	inline const IO::Location*	GetRootLocation (void) const;

	//backway calls
	inline void				ProcessSelectionChange (const IO::Location newLocation);
};


inline FolderDialog*	FolderDialogImpl::GetFolderDialog ()
{
	return static_cast<FolderDialog*> (systemDialog);
}


inline IO::Location*	FolderDialogImpl::GetLocation (void)
{
	return &(GetFolderDialog ()->location);
}


inline const IO::Location*	FolderDialogImpl::GetRootLocation (void) const
{
	//TODOMD
	return nullptr;
}

// ... backway calls ...........................................................

inline void	FolderDialogImpl::ProcessSelectionChange (const IO::Location newLocation)
{
	GetFolderDialog ()->ProcessSelectionChange (newLocation);
}


}	// namespace DG

#endif
