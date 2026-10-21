// *****************************************************************************
// File:
//
// Description:
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef DGSTATUSBAR_HPP
#define DGSTATUSBAR_HPP

// --- Includes ----------------------------------------------------------------

#include "Array.hpp"

#include "DGUtility.hpp"
#include "DG.h"
#include "EventObserver.hpp"
#include "EventSource.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace DG {
	class StatusBar;
	class StatusBarFactory;
	class StatusBarImpl;
	class StatusBarPanelImpl;
	class StatusBarPanelItemImpl;
	class ItemContextMenuEvent;
}


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {


// --- StatusBarObserver -----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT StatusBarObserver: public GS::EventObserver
{
friend class StatusBar;

public:
	StatusBarObserver ();
   ~StatusBarObserver ();

	virtual void	ContextMenuRequested (const StatusBar& es, const DG::NativePoint& coord);
	virtual void	StatusBarVisibilityChanged (const StatusBar& es);
};


// --- StatusBar -------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT StatusBar: public GS::EventSource
{
friend class FrameWindowImpl;
friend class StatusBarImpl;

public:
	static const GS::Guid  StatusBarGuid;

private:
	StatusBarImpl*	impl;

private:
	StatusBar (const StatusBar&);
	const StatusBar& operator= (const StatusBar&);

private:
	StatusBar ();
	void				ProcessContextMenuRequest (const DG::NativePoint& coord);

public:
	virtual ~StatusBar ();

	void				Attach (StatusBarObserver& observer);
	void				Detach (StatusBarObserver& observer);

	StatusBarFactory*	GetFactory (void);
	short				GetHeight (void) const;
	short				GetPanelHeight (void) const;	// Retrieve default height for statusbar panels

	void				SetVisibility (bool show);
	bool				IsVisible (void) const;

	void				SetText (const GS::UniString& text);

	void				SetTemporaryText (const GS::UniString& text);
	void				RemoveTemporaryText ();
};


// --- StatusBarPanel --------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT StatusBarPanel
{
private:
	unsigned short	width;

private:
	StatusBarPanelImpl*	impl;
	StatusBar&			statusBar;

private:
	StatusBarPanel ();
	StatusBarPanel (const StatusBarPanel&);
	const StatusBarPanel& operator=(const StatusBarPanel&);

public:
	StatusBarPanel (StatusBar&, unsigned short widthIn);
	virtual ~StatusBarPanel ();

	StatusBar&				GetStatusBar (void);
	DG::Rect				GetRect (void) const;
	void					SetWidth (unsigned short widthIn);

	virtual void			Clicked ();
	virtual void			DoubleClicked ();
	virtual GS::UniString	GetHelp ();
	virtual	void			ContextMenuRequested (const DG::NativePoint& point, bool* processed);
};


// --- StatusBarPanelItem ----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT StatusBarPanelItem
{
private:
	DG::Rect				rect;

protected:
	StatusBarPanelItemImpl*	impl;

private:
	StatusBarPanelItem ();
	StatusBarPanelItem (const StatusBarPanelItem&);
	const StatusBarPanelItem& operator=(const StatusBarPanelItem&);

protected:
	explicit StatusBarPanelItem (const DG::Rect& rectIn);
	virtual ~StatusBarPanelItem ();

public:
	DG::Rect	GetRect (void) const;
	void		SetRect (const DG::Rect& rectIn);
	void		Redraw ();
};


// --- StatusBarPanelUserItem ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT StatusBarPanelUserItem : public StatusBarPanelItem
{
private:
	StatusBarPanelUserItem ();
	StatusBarPanelUserItem (const StatusBarPanelUserItem&);
	const StatusBarPanelUserItem& operator=(const StatusBarPanelUserItem&);

public:
	StatusBarPanelUserItem (StatusBarPanel&, const DG::Rect&);
	virtual ~StatusBarPanelUserItem ();

	virtual void DrawItem (void* drawContext, const DG::Rect& rect);
};


// --- StatusBarPanelTextItem ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT StatusBarPanelTextItem : public StatusBarPanelItem
{
private:
	StatusBarPanelTextItem ();
	StatusBarPanelTextItem (const StatusBarPanelTextItem&);
	const StatusBarPanelTextItem& operator=(const StatusBarPanelTextItem&);

public:
	StatusBarPanelTextItem (StatusBarPanel&, const DG::Rect&);
	virtual ~StatusBarPanelTextItem ();

	virtual void SetText (const GS::UniString&);
};


// --- StatusBarPanelIconItem ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT StatusBarPanelIconItem : public StatusBarPanelItem
{
private:
	StatusBarPanelIconItem ();
	StatusBarPanelIconItem (const StatusBarPanelIconItem&);
	const StatusBarPanelIconItem& operator=(const StatusBarPanelIconItem&);

public:
	StatusBarPanelIconItem (StatusBarPanel&, const DG::Rect&);
	virtual ~StatusBarPanelIconItem ();

	virtual void SetIcon (const DG::Icon& icon);
};


}	// namespace DG


#endif
