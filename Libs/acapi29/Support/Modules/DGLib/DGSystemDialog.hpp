// *****************************************************************************
// File:			DGSystemDialog.hpp
//
// Description:		Common dialog base
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	MD
//
// SG compatible
// *****************************************************************************

#ifndef DGSYSTEMDIALOG_HPP
#define DGSYSTEMDIALOG_HPP

#pragma once


// --- C++ interface -----------------------------------------------------------

// --- Includes ----------------------------------------------------------------

#include "Event.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"

#include "DGUtility.hpp"

#include "FileTypeManager.hpp"
#include "DGDialog.hpp"			//DG::Panel


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class SystemDialog;
	class SystemDialogImpl;

	class SystemDialogPanel;
	class SystemDialogPanelImpl;
}


namespace DG {

// --- Class declarations ------------------------------------------------------

// --- SystemDialogEvent -------------------------------------------------------
class DG_DLL_EXPORT SystemDialogEvent: public GS::Event
{
	friend class SystemDialog;					// To access protected constructor

protected:
	SystemDialogEvent (SystemDialog* source);

public:
	~SystemDialogEvent ();

	SystemDialog*	GetSource (void) const;
};


// --- SystemDialogOpenEvent -----------------------------------------------------

class DG_DLL_EXPORT SystemDialogOpenEvent: public SystemDialogEvent
{
	friend class SystemDialog;					// To access protected constructor

protected:
	SystemDialogOpenEvent (SystemDialog* source, const DG::EventArg& msgData);

public:
	~SystemDialogOpenEvent ();
};


// --- SystemDialogCloseRequestEvent ---------------------------------------------

class DG_DLL_EXPORT SystemDialogCloseRequestEvent: public SystemDialogEvent
{
	friend class SystemDialog;					// To access protected constructor

protected:
	SystemDialogCloseRequestEvent (SystemDialog* source, const DG::EventArg& msgData);

public:
	~SystemDialogCloseRequestEvent ();
};


// --- SystemDialogCloseEvent ----------------------------------------------------

class DG_DLL_EXPORT SystemDialogCloseEvent: public SystemDialogEvent
{
	friend class SystemDialog;					// To access protected constructor

protected:
	SystemDialogCloseEvent (SystemDialog* source, const DG::EventArg& msgData);

public:
	~SystemDialogCloseEvent ();
};


// --- SystemDialogObserver ----------------------------------------------------

class DG_DLL_EXPORT SystemDialogObserver: public GS::EventObserver
{
	friend class SystemDialog;					// To access protected observer methods

	virtual void	Opened (const SystemDialogOpenEvent& ev);
	virtual	void	CloseRequested (const SystemDialogCloseRequestEvent& ev, bool* accept);
	virtual void	Closed (const SystemDialogCloseEvent& ev);
};


// --- SystemDialog ------------------------------------------------------------

class DG_DLL_EXPORT SystemDialog: public GS::EventSource
{
	friend class SystemDialogImpl;
	friend class SystemDialogPanel;		// SetCustomPanel

protected:
	SystemDialogImpl* pImpl;

	GS::UniString	defaultTitle;
	GS::UniString	defaultHeader;
	GS::UniString	okButtonText;
	GS::UniString	cancelButtonText;

	bool			isHeaderSet;

	SystemDialog ();

	virtual short	ProcessOpenEvent (const DG::EventArg& msgData); // nem long BM
	virtual short	ProcessCloseRequestEvent (const DG::EventArg& msgData);
	virtual short	ProcessCloseEvent (const DG::EventArg& msgData);

public:
	enum Response {
		Accept,
		Cancel
	};


	~SystemDialog ();

	// Dialog methods
	bool			Invoke (void);
	void			PostCloseRequest (Response response);
	void			SetTitle (const GS::UniString& title);
	void			SetHeader (const GS::UniString& title);
	void			SetOKButtonText (const GS::UniString& text);
#if defined (WINDOWS)
	void			SetCancelButtonText (const GS::UniString& text);
#endif
	// Dialog customization methods
	void			Attach (SystemDialogObserver& observer);
	void			Detach (SystemDialogObserver& observer);

	bool				SetCustomPanel (SystemDialogPanel* tab);
//	SystemDialogPanel*	GetCustomPanel (void) const;

	void*			GetDialogWindow (void) const;
};


// --- SystemDialogImpl --------------------------------------------------------

class SystemDialogImpl
{
	friend class SystemDialog;
protected:
	virtual ~SystemDialogImpl ();

	SystemDialog*	systemDialog;
	virtual bool	ActivateImpl (	const GS::UniString&		defaultTitle,
									const GS::UniString&		defaultHeader,
									const GS::UniString&		okButtonText,
									const GS::UniString&		cancelButtonText) = 0;

	virtual void	SetTitleImpl (const GS::UniString& title) = 0;

	virtual void	PostCloseRequest (SystemDialog::Response response) = 0;
	virtual bool	IsActive (void) = 0;
	virtual bool	SetCustomPanel (SystemDialogPanelImpl* customPanelImpl) = 0;
	virtual void*	GetDialogWindow (void) const = 0;

	//backway calls
	short			ProcessOpenEvent (const DG::EventArg& msgData)	// nem long BM
	{
		return systemDialog->ProcessOpenEvent (msgData);
	};

	short			ProcessCloseRequestEvent (const DG::EventArg& msgData)
	{
		return systemDialog->ProcessCloseRequestEvent (msgData);
	};

	short			ProcessCloseEvent (const DG::EventArg& msgData)
	{
		return systemDialog->ProcessCloseEvent (msgData);
	};
};


// --- SystemDialogPanel ------------------------------------------------------------

class DG_DLL_EXPORT SystemDialogPanel: public Panel
{
	friend class SystemDialog; // SetCustomPanel

private:
	SystemDialogPanelImpl* pImpl;
	SystemDialog* fileDialog;

	SystemDialogPanel (const SystemDialogPanel& panel);				// Disable
	SystemDialogPanel&	operator= (const SystemDialogPanel& panel);	// Disable

public:
	SystemDialogPanel (SystemDialog* fileDialog, GSResModule dialResModule, short resID, GSResModule dialIconResModule);
	virtual ~SystemDialogPanel ();

	SystemDialog*	GetMainDialog (void);
	void*			GetMainDialogWindow (void) const;

	bool	IsSystemDialog (void) const;
};


class SystemDialogPanelImpl
{
	friend class SystemDialogPanel;

public:
	SystemDialogPanel*	panel; // TODOMD

protected:
	SystemDialogPanelImpl (SystemDialogPanel* iniFileDialogPanel) { panel = iniFileDialogPanel; };

	static SystemDialogPanelImpl* CreateImpl (SystemDialogPanel* fileDialogPanel);

	virtual short	CreateDummyDlg (GSResModule dialResModule, short resID, GSResModule dialIconResModule) = 0;

public:
	virtual ~SystemDialogPanelImpl ();

	virtual	short	GetDummyDialID (void) = 0;
};


}	// namespace DG

#endif
