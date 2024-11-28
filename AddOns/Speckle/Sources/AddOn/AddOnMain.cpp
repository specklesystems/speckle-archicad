#include "APIEnvir.h"
#include "ACAPinc.h"
#include "BrowserPalette.h"
#include "Connector.h"
#include "CheckError.h"
#include "BrowserBridge.h"


static GSErrCode ProjectNotificationHandler(API_NotifyEventID notifID, Int32 /*param*/)
{
	switch (notifID) 
	{
		case APINotify_Open: CONNECTOR.GetHostAppEvents().ProjectOpened(); break;
		case APINotify_Close: CONNECTOR.GetHostAppEvents().ProjectClosed(); break;
		case APINotify_PreSave: CONNECTOR.GetHostAppEvents().ProjectSaving(); break;
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

static void LoadModelCardData()
{
	auto data = CONNECTOR.GetDataStorage().LoadData(Connector::MODELCARD_ADDONOBJECT_NAME);
	CONNECTOR.GetModelCardDatabase().LoadModelsFromJson(data);
}

static void SaveModelCardData()
{
	auto data = CONNECTOR.GetModelCardDatabase().GetModelsAsJson();
	CONNECTOR.GetDataStorage().SaveData(data, Connector::MODELCARD_ADDONOBJECT_NAME);
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
	catch (...)
	{
		// failed to init Connector
		// TODO send a message to the browser
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
	catch (...)
	{
		// failed to init BrowserBridge
		// TODO send a message to the browser
	}

	try
	{
		CONNECTOR.GetHostAppEvents().ProjectOpened += []() {
			LoadModelCardData();
			BROWSERBRIDGE.GetBaseBridge().OnDocumentChanged();
		};

		CONNECTOR.GetHostAppEvents().ProjectClosed += []() {
			CONNECTOR.GetModelCardDatabase().ClearModels();
			BROWSERBRIDGE.GetBaseBridge().OnDocumentChanged();
		};

		CONNECTOR.GetHostAppEvents().ProjectSaving += []() {
			SaveModelCardData();
		};

		CONNECTOR.GetHostAppEvents().SelectionChanged += []() {
			BROWSERBRIDGE.GetSelectionBridge().OnSelectionChanged();
		};
	}
	catch (...)
	{
		// failed to setup Connector event handlers
		// TODO send a message to the browser
	}

	return NoError;
}

GSErrCode ACENV	FreeData(void)
{
	return NoError;
}
