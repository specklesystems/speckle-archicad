#include "Binding.h"


Binding::Binding(const std::string& name, const std::vector<std::string>& methodNames, IBrowserAdapter* browserAdapter)
    : _name(name), _methodNames(methodNames), _browserAdapter(browserAdapter)
{
	_browserAdapter->RegisterBinding(this);
}

std::string Binding::GetName() const
{
	return _name;
}

std::vector<std::string> Binding::GetMethodNames() const
{
	return _methodNames;
}

void Binding::SetResult(const std::string& key, nlohmann::json value)
{
	CacheResult(key, value);
	ResponseReady(key);
}

nlohmann::json Binding::GetResult(const std::string& key)
{
	try
	{
		return results.at(key);
	}
	catch (const std::exception&)
	{
		return {};
	}
}

void Binding::CacheResult(const std::string& key, const nlohmann::json& result)
{
	results[key] = result;
}

void Binding::ResponseReady(const std::string methodId)
{
	std::string command = _name + ".responseReady('" + methodId + "')";
	_browserAdapter->ExecuteJS(command.c_str());
}

void Binding::EmitResponseReady(const std::string methodName, const std::string methodId)
{
	std::string command = _name + ".emitResponseReady('" + methodName + "', '" + methodId + "')";
	_browserAdapter->ExecuteJS(command.c_str());
}

void Binding::Emit(const std::string eventName)
{
	std::string command = _name + ".emit('" + eventName + "')";
}

void Binding::ClearResult(const std::string& key)
{
	results.erase(key);
}
