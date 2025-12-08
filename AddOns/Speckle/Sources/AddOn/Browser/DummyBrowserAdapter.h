#pragma once

#include "IBrowserAdapter.h"

class DummyBrowserAdapter : public IBrowserAdapter
{
public:
	DummyBrowserAdapter();

	void RegisterBinding(Binding* binding) override;
	void ExecuteJS(const std::string& command) override;
	void LoadURL(const std::string& url) override;
};
