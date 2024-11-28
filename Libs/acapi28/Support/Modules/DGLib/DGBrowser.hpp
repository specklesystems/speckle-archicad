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
#include "Singleton.hpp"

#include "JavascriptEngine.hpp"
#include <set>

// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace DG {
	class Browser;
	class BrowserImpl;
}

// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {

// --- BrowserBase -----------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserBase: public JavascriptEngine,
								 public BrowserNotifyHandler,
								 public virtual DG::DefaultEventTargetProvider
{
	GS::Ref<BrowserImpl> impl;
public:
	enum class PreKeyEventResult : short {
		LetJavascriptToHandle = 0,
		Handled
	};
	enum class KeyEventResult : short {
		HandledByJavascript = 0,
		LetDGToHandle
	};
	enum class ContextMenuMode : short {
		Default,
		Custom,
		Disabled
	};

private:
	void RegisterContextMenuHandler ();
	void RegisterContextMenuEventHandler ();
	void RemoveContextMenuHandler ();
	void RemoveContextMenuEventHandler ();

	ContextMenuMode actualContextMenuMode;

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
	virtual void	ContentHeightChanged (const BrowserHeightChangedArg& eventArg) override;
	virtual bool	OnPreKeyEvent (const BrowserKeyboardEventArg& eventArg) override; 
	virtual bool	OnKeyEvent (BrowserKeyboardEventArg& eventArg) override;
	
	void			CreateBaseImpl (Item* parent = nullptr);
	virtual JavascriptEngineImpl* GetImpl () override;

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
	EventNotifier<BrowserBase, const BrowserHeightChangedArg> onContentHeightChanged;
	EventNotifier<BrowserBase, const BrowserContextMenuEventArg, bool, false> onContextMenu;

	// Called before a keyboard event is sent to the renderer
	EventNotifier<BrowserBase, const BrowserKeyboardEventArg, PreKeyEventResult> onPreKeyEvent;
	// Called after the renderer and JavaScript in the page has had a chance to handle the event
	EventNotifier<BrowserBase, const BrowserKeyboardEventArg, KeyEventResult> onKeyEvent;

	void	SetUpForNativeWindow (void* window, const DG::Rect& rect, const float cornerRadius = 0.0);

	void 	GoBack ();
	void 	GoForward ();

	virtual void	Copy ();
	virtual void	Cut ();
	virtual void	Paste ();

	void 	Reload ();
	void	ReloadIgnoreCache ();
	void 	StopLoad ();

	void	DeleteCookies (const GS::UniString& url, const GS::UniString& cookieName);
	void	DeleteAllCookies ();

	void 	Print ();

	void	SetContextMenuMode (const ContextMenuMode& mode);

	void	SetScrollBarVisibility (const bool visible);

	void	DisableNavigation (const bool disabled);

	int		FindStart (const GS::UniString& txt, bool forward, bool matchCase);
	int		FindNext (bool forward);
	void	FindStop ();

	void	EnableContentHeightChangedEvent (bool enable);

	void*	GetNativeObjectRef ();

	virtual bool IsLoading () const;

	virtual double	GetZoomLevel ();
	virtual void	SetZoomLevel (double zoomLevel);
	virtual void	DisableZooming ();
	virtual void	EnableZooming ();

	void	SetAllowSelfSignedCertificates (bool allowSelfSignedCertificates);
	bool	GetAllowSelfSignedCertificates () const;
};


// --- BrowserIdlenessObserver -----------------------------------------------------------------------------------------

class BrowserIdlenessObserver: public GS::Singleton<BrowserIdlenessObserver>,
							   public DG::EventTarget
{
	friend LazyInstantiationPolicy;

private:
	std::set<const BrowserBase*> observedBrowsers;

	BrowserIdlenessObserver ();
public:
	virtual void Observe (const BrowserBase* browser);
	virtual void Unobserve (const BrowserBase* browser);
	virtual bool IsAllBrowserIdle () const;
};


// --- Browser ---------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT Browser: public Item,
							 public FocusableProperty,
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
