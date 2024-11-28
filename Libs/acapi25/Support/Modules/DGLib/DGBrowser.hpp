// *********************************************************************************************************************
// File:			DGBrowser.hpp
//
// Description:		Browser Control Classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	VM
// *********************************************************************************************************************

#ifndef DGBROWSER_HPP
#define DGBROWSER_HPP

// --- Includes --------------------------------------------------------------------------------------------------------

#include "DGBrowserEventArgs.hpp"
#include "DGDefs.h"
#include "DGEventNotifier.hpp"
#include "DGItemProperty.hpp"
#include "DGPanel.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace DG {
	class Browser;
	class BrowserImpl;
	class JSObject;
	class JSValue;
}

// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {

// --- BrowserBase -----------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserBase: public BrowserNotifyHandler,
								 public virtual DG::DefaultEventTargetProvider
{
	GS::Ref<BrowserImpl> impl;

protected:
	virtual void	URLChanged (const BrowserURLChangeArg& eventArg) override;
	virtual bool	URLWillChange (const BrowserURLChangeArg& eventArg) override;
	virtual void	OnPageSourceVisited (const BrowserPageSourceArg& eventArg) override;
	virtual void	OnLoadingStateChange (const BrowserLoadingStateChangeArg& eventArg) override;
	virtual void	OnLoadError (const BrowserLoadErrorArg& eventArg) override;
	virtual bool	BeforeDownload (const BrowserBeforeDownloadArg& eventArg) override;
	virtual bool	OnDownloading (const BrowserDownloadingArg& eventArg) override;
	virtual void	OnFinalFind (const BrowserFinalFindArg& eventArg) override;
	virtual bool	KeyboardEventOccured (const BrowserKeyboardEventArg& eventArg) override;
	virtual void	ContentHeightChanged (const BrowserHeightChangedArg& eventArg) override;

	void			CreateBaseImpl (Item* parent = nullptr);

public:
	BrowserBase	();
	virtual ~BrowserBase ();

	BrowserBase (const BrowserBase&) = delete;
	BrowserBase& operator= (const BrowserBase&) = delete;

	EventNotifier<BrowserBase, const BrowserURLChangeArg> onUrlChanged;
	EventNotifier<BrowserBase, const BrowserURLChangeArg, bool, true> onUrlWillChange;
	EventNotifier<BrowserBase, const BrowserPageSourceArg> onPageSourceVisited;
	EventNotifier<BrowserBase, const BrowserLoadingStateChangeArg> onLoadingStateChange;
	EventNotifier<BrowserBase, const BrowserLoadErrorArg> onLoadError;
	EventNotifier<BrowserBase, const BrowserBeforeDownloadArg, bool, true> onBeforeDownload;
	EventNotifier<BrowserBase, const BrowserDownloadingArg, bool, true> onDownloading;
	EventNotifier<BrowserBase, const BrowserFinalFindArg> onFinalFind;
	EventNotifier<BrowserBase, const BrowserKeyboardEventArg, bool, false> onKeyboardEvent;
	EventNotifier<BrowserBase, const BrowserHeightChangedArg> onContentHeightChanged;

	void	SetUpForNativeWindow (void* window, const DG::Rect& rect);

	void	LoadURL (const GS::UniString& url);
	void	LoadHTML (const GS::UniString& htmlStr);

	void 	GoBack ();
	void 	GoForward ();

	void 	Reload ();
	void	ReloadIgnoreCache ();
	void 	StopLoad ();

	void	DeleteCookies (const GS::UniString& url, const GS::UniString& cookieName);
	void	DeleteAllCookies ();

	void 	Print ();

	void	DisableContextMenu ();
	void	EnableContextMenu ();
	void	SetContextMenuStatus (const bool status);

	void	SetScrollBarVisibility (const bool visible);

	void	DisableNavigation (const bool disabled);

	int		FindStart (int sessionId, const GS::UniString& txt, bool forward, bool matchCase);
	int		FindNext (int sessionId, bool forward);
	void	FindStop (int sessionId);
	bool	ExecuteJS (const GS::UniString& jsCode);
	bool	ExecuteJSFunctionWithParameters (GS::Ref<JSObject> onObject, GS::Ref<JSFunction> jsFunction, GS::Ref<JSBase> parameters);
	bool	RegisterJSObject (GS::Ref<DG::JSObject> obj);
	bool	RegisterAsynchJSObject (GS::Ref<DG::JSObject> obj);
	void	UnregisterJSObject (GS::Ref<DG::JSObject> obj);
	void	UnregisterJSObject (const GS::UniString& name);

	void	EnableContentHeightChangedEvent (bool enable);

	void*	GetNativeObjectRef ();
};


// --- Browser ---------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT Browser: public Item,
							 public BrowserBase
{
private:
	void	CreateImpl ();

public:
	Browser	(const Rect& rect);

	Browser	(const Panel& panel, short item);
	Browser	(const Panel& panel, const Rect& rect);
	virtual ~Browser ();

	GSErrCode	Store (GS::ObjectState& os) const;
};


// --- FreeBrowser -----------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT FreeBrowser: public BrowserBase
{
public:
	FreeBrowser	();
	virtual EventTarget* GetDefaultEventTarget () const override;
	virtual ~FreeBrowser ();
};

	bool	IsURLReachable (const GS::UniString& url);

}	// namespace DG

#endif
