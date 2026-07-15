#pragma once

#include "IBrowserAdapter.h"
#include "DGBrowser.hpp"

class ArchiCadBrowserAdapter : public IBrowserAdapter
{
private:
	DG::Browser* _browser;

#ifdef __APPLE__
	bool _macCompatibilityObjectRegistered = false;
	void RegisterMacCefSharpCompatibilityObject();
#endif

public:
	ArchiCadBrowserAdapter(DG::Browser* browser);

	void RegisterBinding(Binding* binding) override;
	void ExecuteJS(const std::string& command) override;
	void LoadURL(const std::string& url) override;
};
