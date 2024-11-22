#pragma once

#include <string>

class Binding;

class IBrowserAdapter 
{
public:
	virtual ~IBrowserAdapter() = default;

	virtual void RegisterBinding(Binding* binding) = 0;
	virtual void ExecuteJS(const std::string& command) = 0;
	virtual void LoadURL(const std::string& url) = 0;
};
