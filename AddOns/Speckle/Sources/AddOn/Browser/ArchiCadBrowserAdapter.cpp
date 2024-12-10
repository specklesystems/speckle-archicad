#include "ArchiCadBrowserAdapter.h"
#include "Binding.h"
#include "RunMethodEventArgs.h"
#include "JsonFileWriter.h"

#if defined(AC28)
using JSBase = JS::Base;
using JSArray = JS::Array;
using JSValue = JS::Value;
using JSFunction = JS::Function;
using JSObject = JS::Object;
#elif defined(AC27)
using JSBase = JS::Base;
using JSArray = JS::Array;
using JSValue = JS::Value;
using JSFunction = JS::Function;
using JSObject = JS::Object;
#elif defined(AC26)
using JSBase = DG::JSBase;
using JSArray = DG::JSArray;
using JSValue = DG::JSValue;
using JSFunction = DG::JSFunction;
using JSObject = DG::JSObject;
#endif

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
		auto item = jsArr->GetItemArray()[0];

		for (const auto item : jsArr->GetItemArray())
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

void ArchiCadBrowserAdapter::RegisterBinding(Binding* binding)
{
	JSObject* jsObject = new JSObject(binding->GetName().c_str());

	jsObject->AddItem(new JSFunction("GetBindingsMethodNames", [this, binding](GS::Ref<JSBase>) {
		GS::Array<GS::UniString> methodNames;
		for (const auto& name : binding->GetMethodNames())
			methodNames.Push(name.c_str());

		return ConvertToJavaScriptVariable(methodNames);
	}));

	jsObject->AddItem(new JSFunction("RunMethod", [this, binding](GS::Ref<JSBase> param) {
		auto args = GetStringArrayFromJavaScriptArray(param);

		std::vector<nlohmann::json> data;
		try
		{
			auto parsedJson = nlohmann::json::parse(args[2]);
			for (int i = 0; i < parsedJson.size(); i++)
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

		binding->RunMethodRequested(RunMethodEventArgs(binding, args[0], args[1], data));
		return ConvertToJavaScriptVariable(true);
	}));

	jsObject->AddItem(new JSFunction("GetCallResult", [this, binding](GS::Ref<JSBase> param) {
		auto methodId = GetStringFromJavaScriptVariable(param);
		auto methodIdCstr = methodId.ToCStr().Get();
		auto result = binding->GetResult(methodIdCstr);
		std::string resultJson = result.dump();		
		binding->ClearResult(methodIdCstr);

		return new JSValue(resultJson.c_str());
	}));

	_browser->RegisterAsynchJSObject(jsObject);
}

void ArchiCadBrowserAdapter::ExecuteJS(const std::string& command)
{
	_browser->ExecuteJS(command.c_str());
}

void ArchiCadBrowserAdapter::LoadURL(const std::string& url)
{
	_browser->LoadURL(url.c_str());
}
