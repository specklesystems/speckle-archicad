#pragma once

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "DGModule.hpp"
#include "DGBrowser.hpp"

#include "IBrowserAdapter.h"
#include "BrowserBridge.h"

#include <memory>

#define BrowserPaletteResId 32500
#define BrowserPaletteMenuResId 32500
#define BrowserPaletteMenuItemIndex 1


class BrowserPalette final : public DG::Palette, public DG::PanelObserver
{
protected:
	enum { BrowserId = 1 };

	DG::Browser dgBrowser;

	// this adapter will provide an interface for Bindings to register their JSObjects, and function names
	// without needing to include GS dependencies in the Binding class
	std::unique_ptr<IBrowserAdapter> browserAdapter;
	std::unique_ptr<BrowserBridge> browserBridge;

	void SetMenuItemCheckedState (bool);
	virtual void PanelResized (const DG::PanelResizeEvent& ev) override;
	virtual	void PanelCloseRequested (const DG::PanelCloseRequestEvent& ev, bool* accepted) override;

	static GSErrCode __ACENV_CALL PaletteControlCallBack (Int32 paletteId, API_PaletteMessageID messageID, GS::IntPtr param);

	static GS::Ref<BrowserPalette> instance;

	BrowserPalette ();

public:
	virtual ~BrowserPalette ();

	static bool HasInstance ();
	static void	CreateInstance ();
	static BrowserPalette& GetInstance ();
	static void	DestroyInstance ();

	void Show ();
	void Hide ();
	IBrowserAdapter* GetBrowserAdapter();

	static GSErrCode RegisterPaletteControlCallBack ();
};
