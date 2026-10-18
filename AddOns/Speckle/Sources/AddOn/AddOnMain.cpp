#include "APIEnvir.h"
#include "ACAPinc.h"
#include "BrowserPalette.h"
#include "Connector.h"
#include "CheckError.h"
#include "BrowserBridge.h"
#include "LoggerFactory.h"

static GSErrCode ProjectNotificationHandler(API_NotifyEventID notifID, Int32 /*param*/)
{
	switch (notifID) 
	{
		case APINotify_Open: CONNECTOR.GetHostAppEvents().ProjectOpened(); break;
		case APINotify_Close: CONNECTOR.GetHostAppEvents().ProjectClosed(); break;
		case APINotify_PreSave: CONNECTOR.GetHostAppEvents().ProjectSaving(); break;
		case APINotify_SendChanges: CONNECTOR.GetHostAppEvents().SendChanges(); break;
		case APINotify_ReceiveChanges: CONNECTOR.GetHostAppEvents().ReceiveChanges(); break;
	}

	return NoError;
}

static GSErrCode SelectionChangeHandler(const API_Neig* /*selElemNeig*/)
{
	CONNECTOR.GetHostAppEvents().SelectionChanged();

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

GSErrCode ACENV MenuCommandHandler(const API_MenuParams *menuParams)
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

API_AddonType ACENV CheckEnvironment(API_EnvirParams* envir)
{
	RSGetIndString(&envir->addOnInfo.name, 32000, 1, ACAPI_GetOwnResModule());
	RSGetIndString(&envir->addOnInfo.description, 32000, 2, ACAPI_GetOwnResModule());

	return APIAddon_Preload;
}

GSErrCode ACENV RegisterInterface(void)
{
	GSErrCode err = ACAPI_MenuItem_RegisterMenu(BrowserPaletteMenuResId, 0, MenuCode_UserDef, MenuFlag_Default);

	return err;
}

GSErrCode ACENV Initialize(void)
{
	try
	{
		CONNECTOR.InitConnector();
	}
	catch (const std::exception& ex)
	{
		GET_LOGGER("Connector")->Error(std::string("Connector initialization failed: ") + ex.what());
	}
	catch (...)
	{
		GET_LOGGER("Connector")->Error("Connector initialization failed: unknown exception");
	}

	GSErrCode err = NoError;
	
	err = ACAPI_MenuItem_InstallMenuHandler(BrowserPaletteMenuResId, MenuCommandHandler);
	if (err != NoError)
		return err;

	err = BrowserPalette::RegisterPaletteControlCallBack();
	if (err != NoError)
		return err;

	err = ACAPI_ProjectOperation_CatchProjectEvent(API_AllProjectNotificationMask, ProjectNotificationHandler);
	if (err != NoError)
		return err;

	err = ACAPI_Notification_CatchSelectionChange(SelectionChangeHandler);
	if (err != NoError)
		return err;
	
	try
	{
		BrowserPalette::CreateInstance();
		BROWSERBRIDGE.InitBrowserBridge(BrowserPalette::GetInstance().GetBrowserAdapter());
		BROWSERBRIDGE.LoadUI();
	}
	catch (const std::exception& ex)
	{
		GET_LOGGER("Connector")->Error(std::string("BrowserBridge initialization failed: ") + ex.what());
	}
	catch (...)
	{
		GET_LOGGER("Connector")->Error("BrowserBridge initialization failed: unknown exception");
	}

	try
	{
		CONNECTOR.GetHostAppEvents().ProjectOpened += []() {
			CONNECTOR.GetModelCardDatabase().LoadModelsFromStorage();
			BROWSERBRIDGE.GetBaseBridge().OnDocumentChanged();
		};

		CONNECTOR.GetHostAppEvents().ProjectClosed += []() {
			CONNECTOR.GetModelCardDatabase().ClearModels();
			BROWSERBRIDGE.GetBaseBridge().OnDocumentChanged();
		};

		CONNECTOR.GetHostAppEvents().SelectionChanged += []() {
			BROWSERBRIDGE.GetSelectionBridge().OnSelectionChanged();
		};
	}
	catch (const std::exception& ex)
	{
		GET_LOGGER("Connector")->Error(std::string("Connector event handler initialization failed: ") + ex.what());
	}
	catch (...)
	{
		GET_LOGGER("Connector")->Error("Connector event handler initialization failed: unknown exception");
	}

	return NoError;
}

GSErrCode ACENV	FreeData(void)
{
	return NoError;
}
