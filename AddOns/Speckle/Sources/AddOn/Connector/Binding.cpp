#include "Binding.h"
#include "Base64GuidGenerator.h"
#include "BridgeDiagnostics.h"
#include "Debug.h"
#include "ArchiCadApiException.h"

#ifdef __APPLE__
#include <dispatch/dispatch.h>

#include <memory>

namespace
{
    struct DeferredJavaScriptCommand
    {
        IBrowserAdapter* browserAdapter;
        std::string bindingName;
        std::string command;
    };

    void ExecuteDeferredJavaScriptCommand(void* context)
    {
        std::unique_ptr<DeferredJavaScriptCommand> deferred(
            static_cast<DeferredJavaScriptCommand*>(context));
        BridgeDiagnostics::Write(
            "response-ready execute binding=" + deferred->bindingName);
        deferred->browserAdapter->ExecuteJS(deferred->command);
    }

    void ExecuteJavaScriptAfterCurrentCallback(
        IBrowserAdapter* browserAdapter,
        const std::string& bindingName,
        const std::string& command)
    {
        auto* deferred = new DeferredJavaScriptCommand{
            browserAdapter, bindingName, command
        };
        dispatch_async_f(
            dispatch_get_main_queue(), deferred, ExecuteDeferredJavaScriptCommand);
    }
}
#endif

Binding::Binding(const std::string& name, const std::vector<std::string>& methodNames, IBrowserAdapter* browserAdapter, IBridge* bridge)
    : _name(name), _methodNames(methodNames), _browserAdapter(browserAdapter), _bridge(bridge)
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
	BridgeDiagnostics::Write(
		"set-result binding=" + _name + " type=" + data.type_name());
	CacheResult(methodId, data);
	ResponseReady(methodId);
}

void Binding::Send(const std::string& methodName, const nlohmann::json& data)
{
	std::string guid = Base64GuidGenerator::NewGuid();
	std::string methodId = guid + "_" + methodName;

	std::string s = "Send: " + methodId + " : " + data.dump() + "\n";
	Debug::Print(s);

	CacheResult(methodId, data);
	EmitResponseReady(methodName, methodId);
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

#ifdef __APPLE__
	// DUI registers its response promise immediately after RunMethod returns.
	// Defer the callback by one main-queue turn so a synchronous macOS bridge
	// cannot notify JavaScript before that promise exists.
	BridgeDiagnostics::Write("response-ready queue binding=" + _name);
	ExecuteJavaScriptAfterCurrentCallback(_browserAdapter, _name, command);
#else
	_browserAdapter->ExecuteJS(command.c_str());
#endif
}

void Binding::EmitResponseReady(const std::string methodName, const std::string methodId)
{
	std::string command = _name + ".emitResponseReady('" + methodName + "', '" + methodId + "')";
	_browserAdapter->ExecuteJS(command.c_str());
}

void Binding::Emit(const std::string eventName)
{
	std::string command = _name + ".emit('" + eventName + "')";

	std::string s = "Emit : " + eventName + "\n";
	Debug::Print(s);

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

void Binding::RunMethod(const RunMethodEventArgs& args)
{
	BridgeDiagnostics::Write(
		"run-method binding=" + _name + " method=" + args.methodName);
	try
	{
		_bridge->RunMethod(args);
	}
	catch (const ArchiCadApiException& acex)
	{
		SetToastNotification(
			ToastNotification{ ToastNotificationType::TOAST_DANGER , "Exception occured in the ArchiCAD API" , acex.what(), false });
		SetResult(args.methodId, nlohmann::json{ { "error", acex.what() } });
	}
	catch (const std::exception& stdex)
	{
		SetToastNotification(
			ToastNotification{ ToastNotificationType::TOAST_DANGER , "Exception occured" , stdex.what(), false });
		SetResult(args.methodId, nlohmann::json{ { "error", stdex.what() } });
	}
	catch (...)
	{
		SetToastNotification(
			ToastNotification{ ToastNotificationType::TOAST_DANGER , "Unknown exception occured" , "", false });
		SetResult(args.methodId, nlohmann::json{ { "error", "Unknown native connector error" } });
	}
}
