#include "BrowserBridge.h"

std::unique_ptr<BrowserBridge> BrowserBridge::instance = nullptr;

BrowserBridge& BrowserBridge::GetInstance()
{
	if (instance == nullptr)
		instance = std::unique_ptr<BrowserBridge>(new BrowserBridge());

	return *instance;
}

void BrowserBridge::InitBrowserBridge(IBrowserAdapter* browserAdapter)
{
	_browserAdapter = browserAdapter;

	accountsBridge = std::make_unique<AccountBridge>(browserAdapter);
	baseBridge = std::make_unique<BaseBridge>(browserAdapter);
	configBridge = std::make_unique<ConfigBridge>(browserAdapter);
	selectionBridge = std::make_unique<SelectionBridge>(browserAdapter);
	sendBridge = std::make_unique<SendBridge>(browserAdapter);
	testBridge = std::make_unique<TestBridge>(browserAdapter);	
}

void BrowserBridge::LoadUI()
{
	//_browserAdapter->LoadURL("https://boisterous-douhua-e3cefb.netlify.app/");
	_browserAdapter->LoadURL("https://deploy-preview-3648--boisterous-douhua-e3cefb.netlify.app/");
}

AccountBridge& BrowserBridge::GetAccountBridge()
{
    if (!accountsBridge)
        throw std::runtime_error("AccountBridge not initialized");

    return *accountsBridge;
}

BaseBridge& BrowserBridge::GetBaseBridge()
{
    if (!baseBridge)
        throw std::runtime_error("BaseBridge not initialized");

    return *baseBridge;
}

ConfigBridge& BrowserBridge::GetConfigBridge()
{
    if (!configBridge)
        throw std::runtime_error("ConfigBridge not initialized");

    return *configBridge;
}

SelectionBridge& BrowserBridge::GetSelectionBridge()
{
    if (!selectionBridge)
        throw std::runtime_error("SelectionBridge not initialized");

    return *selectionBridge;
}

SendBridge& BrowserBridge::GetSendBridge()
{
    if (!sendBridge)
        throw std::runtime_error("SendBridge not initialized");

    return *sendBridge;
}

TestBridge& BrowserBridge::GetTestBridge()
{
    if (!testBridge)
        throw std::runtime_error("TestBridge not initialized");

    return *testBridge;
}
