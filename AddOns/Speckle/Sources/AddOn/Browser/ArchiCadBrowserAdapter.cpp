#include "ArchiCadBrowserAdapter.h"
#include "Binding.h"
#include "BridgeDiagnostics.h"
#include "RunMethodEventArgs.h"

#include <stdexcept>

using JSBase = JS::Base;
using JSArray = JS::Array;
using JSValue = JS::Value;
using JSFunction = JS::Function;
using JSObject = JS::Object;

namespace
{
	GS::UniString GetStringFromJavaScriptVariable(GS::Ref<JSBase> jsVariable)
	{
		GS::Ref<JSValue> jsValue = GS::DynamicCast<JSValue>(jsVariable);
		if (DBVERIFY(jsValue != nullptr && jsValue->GetType() == JSValue::STRING))
			return jsValue->GetString();

		return GS::EmptyUniString;
	}

	std::vector<std::string> GetStringArrayFromJavaScriptArray(GS::Ref<JSBase> jsVariable)
	{
		std::vector<std::string> values;

		GS::Ref<JSArray> jsArr = GS::DynamicCast<JSArray>(jsVariable);
		if (jsArr == nullptr)
			return values;

		for (const auto& item : jsArr->GetItemArray())
		{
			GS::Ref<JSValue> jsValue = GS::DynamicCast<JSValue>(item);
			if (DBVERIFY(jsValue != nullptr && jsValue->GetType() == JSValue::STRING))
				values.push_back(jsValue->GetString().ToCStr().Get());
		}

		return values;
	}

	template<class Type>
	GS::Ref<JSBase> ConvertToJavaScriptVariable(const Type& cppVariable)
	{
		return new JSValue(cppVariable);
	}

	template<class Type>
	GS::Ref<JSBase> ConvertToJavaScriptVariable(const GS::Array<Type>& cppArray)
	{
		GS::Ref<JSArray> newArray = new JSArray();
		for (const Type& item : cppArray) {
			newArray->AddItem(ConvertToJavaScriptVariable(item));
		}
		return newArray;
	}
}


ArchiCadBrowserAdapter::ArchiCadBrowserAdapter(DG::Browser* browser) 
	: _browser(browser) {}

#ifdef __APPLE__
void ArchiCadBrowserAdapter::RegisterMacCefSharpCompatibilityObject()
{
	if (_macCompatibilityObjectRegistered)
		return;

	JSObject* cefSharp = new JSObject("CefSharp");
	cefSharp->AddItem(new JSFunction("BindObjectAsync", [](GS::Ref<JSBase>) {
		// Graphisoft has already injected the requested object. DUI awaits this
		// CefSharp API only as part of its Windows-oriented binding contract.
		return ConvertToJavaScriptVariable(true);
	}));

	const bool registered = _browser->RegisterAsynchJSObject(cefSharp);
	BridgeDiagnostics::Write(
		"register-compatibility name=CefSharp accepted=" +
		std::string(registered ? "true" : "false"));
	if (!registered)
		throw std::runtime_error("Archicad rejected the macOS CefSharp compatibility object");

	_macCompatibilityObjectRegistered = true;
}
#endif

void ArchiCadBrowserAdapter::RegisterBinding(Binding* binding)
{
#ifdef __APPLE__
	RegisterMacCefSharpCompatibilityObject();
#endif

	JSObject* jsObject = new JSObject(binding->GetName().c_str());

	jsObject->AddItem(new JSFunction("GetBindingsMethodNames", [binding](GS::Ref<JSBase>) {
		GS::Array<GS::UniString> methodNames;
		for (const auto& name : binding->GetMethodNames())
			methodNames.Push(name.c_str());

		return ConvertToJavaScriptVariable(methodNames);
	}));

	jsObject->AddItem(new JSFunction("RunMethod", [binding](GS::Ref<JSBase> param) {
		auto args = GetStringArrayFromJavaScriptArray(param);
		if (args.size() < 3)
		{
			BridgeDiagnostics::Write(
				"run-method-invalid-argument-count binding=" + binding->GetName() +
				" count=" + std::to_string(args.size()));
			return ConvertToJavaScriptVariable(false);
		}

		std::vector<nlohmann::json> data;
		try
		{
			auto parsedJson = nlohmann::json::parse(args[2]);
			for (size_t i = 0; i < parsedJson.size(); i++)
			{
				std::string rawString = parsedJson[i];
				data.push_back(nlohmann::json::parse(rawString));
			}
		}
		catch (...)
		{
			// failed to parse json
			// data will be an empty json object
		}
		binding->RunMethod(RunMethodEventArgs(binding, args[0], args[1], data));

		return ConvertToJavaScriptVariable(true);
	}));

	jsObject->AddItem(new JSFunction("GetCallResult", [binding](GS::Ref<JSBase> param) {
		auto methodId = GetStringFromJavaScriptVariable(param);
		auto methodIdCstr = methodId.ToCStr();
		auto result = binding->GetResult(methodIdCstr.Get());
		BridgeDiagnostics::Write(
			"get-call-result binding=" + binding->GetName() +
			" type=" + result.type_name());
		std::string resultJson = result.dump();		
		binding->ClearResult(methodIdCstr.Get());

		return new JSValue(resultJson.c_str());
	}));

	const bool registered = _browser->RegisterAsynchJSObject(jsObject);
	BridgeDiagnostics::Write(
		"register-binding name=" + binding->GetName() +
		" accepted=" + (registered ? "true" : "false"));
	if (!registered)
		throw std::runtime_error("Archicad rejected browser binding " + binding->GetName());
}

void ArchiCadBrowserAdapter::ExecuteJS(const std::string& command)
{
	const bool executed = _browser->ExecuteJS(command.c_str());
	BridgeDiagnostics::Write(
		"execute-js accepted=" + std::string(executed ? "true" : "false"));
}

void ArchiCadBrowserAdapter::LoadURL(const std::string& url)
{
	_browser->LoadURL(url.c_str());
}
