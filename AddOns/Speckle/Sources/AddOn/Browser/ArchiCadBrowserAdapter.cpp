#include "ArchiCadBrowserAdapter.h"
#include "Binding.h"
#include "RunMethodEventArgs.h"

namespace
{
	GS::UniString GetStringFromJavaScriptVariable(GS::Ref<JS::Base> jsVariable)
	{
		GS::Ref<JS::Value> jsValue = GS::DynamicCast<JS::Value>(jsVariable);
		if (DBVERIFY(jsValue != nullptr && jsValue->GetType() == JS::Value::STRING))
			return jsValue->GetString();

		return GS::EmptyUniString;
	}

	std::vector<std::string> GetStringArrayFromJavaScriptArray(GS::Ref<JS::Base> jsVariable)
	{
		std::vector<std::string> values;

		GS::Ref<JS::Array> jsArr = GS::DynamicCast<JS::Array>(jsVariable);
		auto item = jsArr->GetItemArray()[0];

		for (const auto item : jsArr->GetItemArray())
		{
			GS::Ref<JS::Value> jsValue = GS::DynamicCast<JS::Value>(item);
			if (DBVERIFY(jsValue != nullptr && jsValue->GetType() == JS::Value::STRING))
				values.push_back(jsValue->GetString().ToCStr().Get());
		}

		return values;
	}

	template<class Type>
	GS::Ref<JS::Base> ConvertToJavaScriptVariable(const Type& cppVariable)
	{
		return new JS::Value(cppVariable);
	}

	template<class Type>
	GS::Ref<JS::Base> ConvertToJavaScriptVariable(const GS::Array<Type>& cppArray)
	{
		GS::Ref<JS::Array> newArray = new JS::Array();
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
	JS::Object* jsObject = new JS::Object(binding->GetName().c_str());

	jsObject->AddItem(new JS::Function("GetBindingsMethodNames", [this, binding](GS::Ref<JS::Base>) {
		GS::Array<GS::UniString> methodNames;
		for (const auto& name : binding->GetMethodNames())
			methodNames.Push(name.c_str());

		return ConvertToJavaScriptVariable(methodNames);
	}));

	jsObject->AddItem(new JS::Function("RunMethod", [this, binding](GS::Ref<JS::Base> param) {
		auto args = GetStringArrayFromJavaScriptArray(param);

		nlohmann::json data{};
		try
		{
			auto parsedJson = nlohmann::json::parse(args[2]);
			if (parsedJson.size() > 0)
			{
				std::string rawString = parsedJson[0];
				data = nlohmann::json::parse(rawString);
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

	jsObject->AddItem(new JS::Function("GetCallResult", [this, binding](GS::Ref<JS::Base> param) {
		auto methodId = GetStringFromJavaScriptVariable(param);
		auto methodIdCstr = methodId.ToCStr().Get();
		auto result = binding->GetResult(methodIdCstr);

		std::string resultJson = "";
		if (result != nullptr)
		{
			resultJson = result->dump();
		}
		binding->ClearResult(methodIdCstr);

		auto jsval = new JS::Value(resultJson.c_str());
		return jsval;
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
