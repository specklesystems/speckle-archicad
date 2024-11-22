#pragma once

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
public:
	BrowserBridge(IBrowserAdapter* browserAdapter);
	
private:
	std::unique_ptr<AccountBridge> accountsBridge;
	std::unique_ptr<BaseBridge> baseBridge;
	std::unique_ptr<ConfigBridge> configBridge;
	std::unique_ptr<SelectionBridge> selectionBridge;
	std::unique_ptr<SendBridge> sendBridge;
	std::unique_ptr<TestBridge> testBridge;
};
