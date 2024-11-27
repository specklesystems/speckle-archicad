#pragma once

#define BROWSERBRIDGE BrowserBridge::GetInstance()

#include "IBrowserAdapter.h"
#include "IHostToSpeckleConverter.h"
#include "ISpeckleToHostConverter.h"
#include "IDataStorage.h"
#include "AccountDatabase.h"
#include "ModelCardDatabase.h"

#include "AccountBridge.h"
#include "BaseBridge.h"
#include "ConfigBridge.h"
#include "SelectionBridge.h"
#include "SendBridge.h"
#include "TestBridge.h"

class BrowserBridge
{
private:
	BrowserBridge() {};
	static std::unique_ptr<BrowserBridge> instance;
	IBrowserAdapter* _browserAdapter;

	std::unique_ptr<AccountBridge> accountsBridge;
	std::unique_ptr<BaseBridge> baseBridge;
	std::unique_ptr<ConfigBridge> configBridge;
	std::unique_ptr<SelectionBridge> selectionBridge;
	std::unique_ptr<SendBridge> sendBridge;
	std::unique_ptr<TestBridge> testBridge;

public:
	BrowserBridge(BrowserBridge& other) = delete;
	void operator=(const BrowserBridge&) = delete;

	static BrowserBridge& GetInstance();

	void InitBrowserBridge(IBrowserAdapter* browserAdapter);
	void LoadUI();
	
	AccountBridge& GetAccountBridge();
	BaseBridge& GetBaseBridge();
	ConfigBridge& GetConfigBridge();
	SelectionBridge& GetSelectionBridge();
	SendBridge& GetSendBridge();
	TestBridge& GetTestBridge();
};
