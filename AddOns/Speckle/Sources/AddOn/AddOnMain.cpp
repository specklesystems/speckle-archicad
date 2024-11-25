#include "APIEnvir.h"
#include "ACAPinc.h"
#include "BrowserPalette.hpp"
#include "Connector.h"
#include "AccountDatabase.h"
#include "ModelCardDatabase.h"
#include "HostToSpeckleConverter.h"
#include "SpeckleToHostConverter.h"
#include "ArchiCadDataStorage.h"


static const std::string MODELCARD_ADDONOBJECT_NAME = "SpeckleModelCardAddOnObjectName_v1";


static GSErrCode ProjectNotificationHandler(API_NotifyEventID notifID, Int32 /*param*/)
{
	switch (notifID) 
	{
		case APINotify_Open: CONNECTOR.hostAppEvents->ProjectOpened(); break;
		case APINotify_PreSave: CONNECTOR.hostAppEvents->ProjectSaved(); break;
	}

	return NoError;
}

static GSErrCode SelectionChangeHandler(const API_Neig* /*selElemNeig*/)
{
	CONNECTOR.hostAppEvents->SelectionChanged();

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
	CONNECTOR.dataStorage = std::make_unique<ArchiCadDataStorage>();

	// TODO make a function of this
	auto data = CONNECTOR.dataStorage->LoadData(MODELCARD_ADDONOBJECT_NAME);
	CONNECTOR.modelCardDatabase->LoadModelsFromJson(data);

	CONNECTOR.hostAppEvents->ProjectOpened += []()
	{
		// TODO: data name string to const var
		auto data = CONNECTOR.dataStorage->LoadData(MODELCARD_ADDONOBJECT_NAME);
		CONNECTOR.modelCardDatabase->LoadModelsFromJson(data);
	};

	CONNECTOR.hostAppEvents->ProjectSaved += []()
	{
		// TODO: data name string to const var
		auto data = CONNECTOR.modelCardDatabase->GetModelsAsJson();
		CONNECTOR.dataStorage->SaveData(data, MODELCARD_ADDONOBJECT_NAME);
	};

	// TODO error handling
	GSErrCode err;
	err = ACAPI_MenuItem_InstallMenuHandler(BrowserPaletteMenuResId, MenuCommandHandler);
	err = BrowserPalette::RegisterPaletteControlCallBack();
	err = ACAPI_ProjectOperation_CatchProjectEvent(API_AllProjectNotificationMask, ProjectNotificationHandler);
	err = ACAPI_Notification_CatchSelectionChange(SelectionChangeHandler);

	// this call is necessary to subscribe event listeners in the bridge constructors
	// call this after CONNECTOR.hostAppEvents is initialized
	BrowserPalette::CreateInstance();

	return err;
}

GSErrCode __ACENV_CALL	FreeData(void)
{
	return NoError;
}
