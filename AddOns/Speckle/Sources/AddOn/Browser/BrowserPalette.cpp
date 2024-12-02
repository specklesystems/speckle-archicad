#include "BrowserPalette.h"
#include "ArchiCadBrowserAdapter.h"

static const GS::Guid	paletteGuid ("{B8461D5C-DB5C-45EB-9047-3303212F04AD}");
GS::Ref<BrowserPalette>	BrowserPalette::instance;


static GSErrCode CatchProjectEvent(GSFlags eventTypes, APIProjectEventHandlerProc* handlerProc)
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_ProjectOperation_CatchProjectEvent(eventTypes, handlerProc);
#elif defined(AC27)
	err = ACAPI_ProjectOperation_CatchProjectEvent(eventTypes, handlerProc);
#elif defined(AC26)
	err = ACAPI_Notify_CatchProjectEvent(eventTypes, handlerProc);
#elif defined(AC25)
	err = ACAPI_Notify_CatchProjectEvent(eventTypes, handlerProc);
#endif

	return err;
}

static GSErrCode GetMenuItemFlags(API_MenuItemRef* menuItem = nullptr, GSFlags* flags = nullptr)
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_MenuItem_GetMenuItemFlags(menuItem, flags);
#elif defined(AC27)
	err = ACAPI_MenuItem_GetMenuItemFlags(menuItem, flags);
#elif defined(AC26)
	err = ACAPI_Interface(APIIo_GetMenuItemFlagsID, menuItem, flags);
#elif defined(AC25)
	err = ACAPI_Interface(APIIo_GetMenuItemFlagsID, menuItem, flags);
#endif

	return err;
}

static GSErrCode SetMenuItemFlags(API_MenuItemRef* menuItem = nullptr, GSFlags* flags = nullptr)
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_MenuItem_SetMenuItemFlags(menuItem, flags);
#elif defined(AC27)
	err = ACAPI_MenuItem_SetMenuItemFlags(menuItem, flags);
#elif defined(AC26)
	err = ACAPI_Interface(APIIo_SetMenuItemFlagsID, menuItem, flags);
#elif defined(AC25)
	err = ACAPI_Interface(APIIo_SetMenuItemFlagsID, menuItem, flags);
#endif

	return err;
}

static GSErrCode ACENV NotificationHandler (API_NotifyEventID notifID, Int32 /*param*/)
{
	switch (notifID) {
		case APINotify_Quit:
			BrowserPalette::DestroyInstance ();
			break;
	}

	return NoError;
}

BrowserPalette::BrowserPalette () :
	DG::Palette (ACAPI_GetOwnResModule (), BrowserPaletteResId, ACAPI_GetOwnResModule (), paletteGuid),
	dgBrowser(GetReference (), BrowserId)
{
	CatchProjectEvent (APINotify_Quit, NotificationHandler);
	Attach (*this);
	BeginEventProcessing ();
	browserAdapter = std::make_unique<ArchiCadBrowserAdapter>(&dgBrowser);
}

BrowserPalette::~BrowserPalette ()
{
	EndEventProcessing ();
}

bool BrowserPalette::HasInstance ()
{
	return instance != nullptr;
}

void BrowserPalette::CreateInstance ()
{
	DBASSERT (!HasInstance ());
	instance = new BrowserPalette ();
	ACAPI_KeepInMemory (true);
}

BrowserPalette&	BrowserPalette::GetInstance ()
{
	DBASSERT (HasInstance ());
	return *instance;
}

void BrowserPalette::DestroyInstance ()
{
	instance = nullptr;
}

void BrowserPalette::Show ()
{
	DG::Palette::Show ();
	SetMenuItemCheckedState(true);
}

void BrowserPalette::Hide ()
{
	DG::Palette::Hide ();
	SetMenuItemCheckedState(false);
}

void BrowserPalette::SetMenuItemCheckedState (bool isChecked)
{
	API_MenuItemRef	itemRef = {};
	GSFlags	itemFlags = {};

	itemRef.menuResID = BrowserPaletteMenuResId;
	itemRef.itemIndex = BrowserPaletteMenuItemIndex;

	GetMenuItemFlags(&itemRef, &itemFlags);
	if (isChecked)
		itemFlags |= API_MenuItemChecked;
	else
		itemFlags &= ~API_MenuItemChecked;
	SetMenuItemFlags(&itemRef, &itemFlags);
}

void BrowserPalette::PanelResized (const DG::PanelResizeEvent& ev)
{
	BeginMoveResizeItems ();
	dgBrowser.Resize (ev.GetHorizontalChange (), ev.GetVerticalChange ());
	EndMoveResizeItems ();
}

void BrowserPalette::PanelCloseRequested (const DG::PanelCloseRequestEvent&, bool* accepted)
{
	Hide ();
	*accepted = true;
}

IBrowserAdapter* BrowserPalette::GetBrowserAdapter()
{
	return browserAdapter.get();
}

GSErrCode ACENV	BrowserPalette::PaletteControlCallBack (Int32, API_PaletteMessageID messageID, GS::IntPtr param)
{
	switch (messageID) {
		case APIPalMsg_OpenPalette:
			if (!HasInstance ())
				CreateInstance ();
			GetInstance ().Show ();
			break;

		case APIPalMsg_ClosePalette:
			if (!HasInstance ())
				break;
			GetInstance ().Hide ();
			break;

		/*
		case APIPalMsg_HidePalette_Begin:
			if (HasInstance () && GetInstance ().IsVisible ())
				GetInstance ().Hide ();
			break;

		case APIPalMsg_HidePalette_End:
			if (HasInstance () && !GetInstance ().IsVisible ())
				GetInstance ().Show ();
			break;

		case APIPalMsg_DisableItems_Begin:
			if (HasInstance () && GetInstance ().IsVisible ())
				GetInstance ().DisableItems ();
			break;

		case APIPalMsg_DisableItems_End:
			if (HasInstance () && GetInstance ().IsVisible ())
				GetInstance ().EnableItems ();
			break;
		*/

		case APIPalMsg_IsPaletteVisible:
			*(reinterpret_cast<bool*> (param)) = HasInstance () && GetInstance ().IsVisible ();
			break;

		default:
			break;
	}

	return NoError;
}

GSErrCode BrowserPalette::RegisterPaletteControlCallBack ()
{
	return ACAPI_RegisterModelessWindow (
					GS::CalculateHashValue (paletteGuid),
					PaletteControlCallBack,
					API_PalEnabled_FloorPlan + API_PalEnabled_Section + API_PalEnabled_Elevation +
					API_PalEnabled_InteriorElevation + API_PalEnabled_3D + API_PalEnabled_Detail +
					API_PalEnabled_Worksheet + API_PalEnabled_Layout + API_PalEnabled_DocumentFrom3D,
					GSGuid2APIGuid (paletteGuid));
}
