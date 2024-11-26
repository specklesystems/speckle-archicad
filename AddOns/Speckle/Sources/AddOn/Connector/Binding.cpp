#include "Binding.h"
#include "Base64GuidGenerator.h"


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

void Binding::SetResult(const std::string& methodId, const nlohmann::json& data)
{
	CacheResult(methodId, data);
	ResponseReady(methodId);
}

void Binding::Send(const std::string& methodName, const nlohmann::json& data)
{
	std::string guid = Base64GuidGenerator::NewGuid();
	std::string methodId = guid + "_" + methodName;

	CacheResult(methodId, data);
	EmitResponseReady(methodName, methodId);
}

void Binding::SendByBrowser(const std::string& sendMethodId, const nlohmann::json& data)
{
	Send("sendByBrowser", data);
	ResponseReady(sendMethodId);
}

nlohmann::json Binding::GetResult(const std::string& methodId)
{
	try
	{
		return results.at(methodId);
	}
	catch (const std::exception&)
	{
		return {};
	}
}

void Binding::CacheResult(const std::string& methodId, const nlohmann::json& result)
{
	results[methodId] = result;
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
	_browserAdapter->ExecuteJS(command.c_str());
}

void Binding::ClearResult(const std::string& methodId)
{
	results.erase(methodId);
}

void Binding::SetToastNotification(const ToastNotification& toast)
{
	Send("setGlobalNotification", toast);
}
