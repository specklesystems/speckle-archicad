#include "BrowserBridge.h"

BrowserBridge::BrowserBridge(IBrowserAdapter* browserAdapter)
{
	accountsBridge = std::make_unique<AccountBridge>(browserAdapter);
	baseBridge = std::make_unique<BaseBridge>(browserAdapter);
	configBridge = std::make_unique<ConfigBridge>(browserAdapter);
	selectionBridge = std::make_unique<SelectionBridge>(browserAdapter);
	sendBridge = std::make_unique<SendBridge>(browserAdapter);
	testBridge = std::make_unique<TestBridge>(browserAdapter);

	browserAdapter->LoadURL("https://boisterous-douhua-e3cefb.netlify.app/");
}
