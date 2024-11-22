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
	CacheResult(key, std::make_unique<nlohmann::json>(value));
	ResponseReady(key);
}

std::unique_ptr<nlohmann::json> Binding::GetResult(const std::string& key)
{
	try
	{
		return std::move(results.at(key));
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
}

void Binding::CacheResult(const std::string& key, std::unique_ptr<nlohmann::json> value)
{
	results[key] = std::move(value);
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

void Binding::ClearResult(const std::string& key)
{
	results[key].release();
	results.erase(key);
}
