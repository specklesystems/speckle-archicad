#include "BrowserBridge.h"
#include "BridgeDiagnostics.h"

std::unique_ptr<BrowserBridge> BrowserBridge::instance = nullptr;

BrowserBridge& BrowserBridge::GetInstance()
{
	if (instance == nullptr)
		instance = std::unique_ptr<BrowserBridge>(new BrowserBridge());

	return *instance;
}

void BrowserBridge::InitBrowserBridge(IBrowserAdapter* browserAdapter)
{
	BridgeDiagnostics::Reset();
	_browserAdapter = browserAdapter;
	BridgeDiagnostics::Write("browser-load-ui");
	LoadUI();

	accountsBridge = std::make_unique<AccountBridge>(browserAdapter);
	baseBridge = std::make_unique<BaseBridge>(browserAdapter);
	configBridge = std::make_unique<ConfigBridge>(browserAdapter);
	selectionBridge = std::make_unique<SelectionBridge>(browserAdapter);
	sendBridge = std::make_unique<SendBridge>(browserAdapter);
	receiveBridge = std::make_unique<ReceiveBridge>(browserAdapter);
	testBridge = std::make_unique<TestBridge>(browserAdapter);	
	BridgeDiagnostics::Write("browser-bridges-ready");

	// The remote DUI can finish its one-time connector detection before the
	// asynchronous native objects become visible. Reload once after every
	// binding has been accepted so the fresh JavaScript context sees them all.
	BridgeDiagnostics::Write("browser-reload-ui-after-bindings");
	LoadUI();
}

void BrowserBridge::LoadUI()
{
	if (_browserAdapter == nullptr)
		return;

	_browserAdapter->LoadURL("https://dui.speckle.systems/");
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

ReceiveBridge& BrowserBridge::GetReceiveBridge()
{
    if (!receiveBridge)
        throw std::runtime_error("ReceiveBridge not initialized");

    return *receiveBridge;
}

TestBridge& BrowserBridge::GetTestBridge()
{
    if (!testBridge)
        throw std::runtime_error("TestBridge not initialized");

    return *testBridge;
}
