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
	virtual bool	OnDragEnter (const BrowserDragEnterArg& eventArg) override;
	virtual bool	BeforeDownload (const BrowserBeforeDownloadArg& eventArg) override;
	virtual bool	OnDownloading (const BrowserDownloadingArg& eventArg) override;
	virtual void	OnFinalFind (const BrowserFinalFindArg& eventArg) override;
	virtual bool	KeyboardEventOccured (const BrowserKeyboardEventArg& eventArg) override;
	virtual void	ContentHeightChanged (const BrowserHeightChangedArg& eventArg) override;

	bool			ExecuteJSFunctionWithParameters (const GS::Ref<JSObject>& onObject, const GS::Ref<JSFunction>& jsFunction, const GS::Array<GS::Ref<JSBase>>& parameters);

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
	EventNotifier<BrowserBase, const BrowserDragEnterArg, bool, true> onDragEnter;
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

	template<typename... Parameters>
	bool	ExecuteJSFunction (const GS::Ref<JSObject>& onObject, const GS::Ref<JSFunction>& jsFunction, const Parameters&... parameter);
	template<>
	bool	ExecuteJSFunction (const GS::Ref<JSObject>& onObject, const GS::Ref<JSFunction>& jsFunction);
	bool	RegisterAsynchJSObject (GS::Ref<DG::JSObject> obj);

	void	EnableContentHeightChangedEvent (bool enable);

	void*	GetNativeObjectRef ();
};


template<typename ...Parameters>
inline bool BrowserBase::ExecuteJSFunction (const GS::Ref<JSObject>& onObject, const GS::Ref<JSFunction>& jsFunction, const Parameters&... parameters)
{
	GS::Array<GS::Ref<JSBase>> functionParameters {parameters...};
	return ExecuteJSFunctionWithParameters (onObject, jsFunction, functionParameters);
}


template<>
inline bool BrowserBase::ExecuteJSFunction (const GS::Ref<JSObject>& onObject, const GS::Ref<JSFunction>& jsFunction)
{
	return ExecuteJSFunctionWithParameters (onObject, jsFunction, {});
}


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
