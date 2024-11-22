#include "APIEnvir.h"
#include "ACAPinc.h"
#include "BrowserPalette.hpp"
#include "Connector.h"
#include "AccountDatabase.h"
#include "ModelCardDatabase.h"
#include "HostToSpeckleConverter.h"
#include "SpeckleToHostConverter.h"


static GSErrCode NotificationHandler(API_NotifyEventID notifID, Int32 /*param*/)
{
	switch (notifID) 
	{
		// TODO
		case APINotify_Open: CONNECTOR.hostAppEvents->ProjectOpened("Apple"); break;
	}

	return NoError;
}

static GSErrCode SelectionChangeHandler(const API_Neig* /*selElemNeig*/)
{
	// TODO
	CONNECTOR.hostAppEvents->SelectionChanged("Banana");

	return NoError;
}

static void	ShowOrHideBrowserPalette()
{
	if (BrowserPalette::HasInstance() && BrowserPalette::GetInstance().IsVisible()) 
	{
		BrowserPalette::GetInstance().Hide();
	}
	else 
	{
		if (!BrowserPalette::HasInstance())
		{
			BrowserPalette::CreateInstance();
		}
		BrowserPalette::GetInstance().Show();
	}
}

GSErrCode __ACENV_CALL MenuCommandHandler(const API_MenuParams *menuParams)
{
	switch (menuParams->menuItemRef.menuResID) 
	{
		case BrowserPaletteMenuResId:
			switch (menuParams->menuItemRef.itemIndex) 
			{
				case BrowserPaletteMenuItemIndex:
					ShowOrHideBrowserPalette();
					break;
				default:				
					break;
			}
			break;
		default:
			break;
	}

	return NoError;
}

API_AddonType __ACENV_CALL CheckEnvironment(API_EnvirParams* envir)
{
	RSGetIndString(&envir->addOnInfo.name, 32000, 1, ACAPI_GetOwnResModule());
	RSGetIndString(&envir->addOnInfo.description, 32000, 2, ACAPI_GetOwnResModule());

	return APIAddon_Preload;
}

GSErrCode __ACENV_CALL RegisterInterface(void)
{
	GSErrCode err = ACAPI_MenuItem_RegisterMenu(BrowserPaletteMenuResId, 0, MenuCode_UserDef, MenuFlag_Default);

	return err;
}

GSErrCode __ACENV_CALL Initialize(void)
{
	// TODO: make these safer to use, throw exception on nullptr
	CONNECTOR.accountDatabase = std::make_unique<AccountDatabase>();
	CONNECTOR.modelCardDatabase = std::make_unique<ModelCardDatabase>();
	CONNECTOR.hostToSpeckleConverter = std::make_unique<HostToSpeckleConverter>();
	CONNECTOR.speckleToHostConverter = std::make_unique<SpeckleToHostConverter>();
	CONNECTOR.hostAppEvents = std::make_unique<HostAppEvents>();

	GSErrCode err = ACAPI_MenuItem_InstallMenuHandler(BrowserPaletteMenuResId, MenuCommandHandler);
	err = BrowserPalette::RegisterPaletteControlCallBack();
	err = ACAPI_ProjectOperation_CatchProjectEvent(API_AllProjectNotificationMask, NotificationHandler);
	err = ACAPI_Notification_CatchSelectionChange(SelectionChangeHandler);

	BrowserPalette::CreateInstance();

	return err;
}

GSErrCode __ACENV_CALL	FreeData(void)
{
	return NoError;
}
