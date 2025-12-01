
#include "DGJSBaseJSONValueConversion.hpp"

namespace Extensions {

namespace Utilities {

JSON::ValueRef ConvertDGJSBaseToJSONValue (const GS::Ref<JS::Base>& jsBase)
{
	JS::Object* objectJS = dynamic_cast<JS::Object*> ((JS::Base*)jsBase);
	if (objectJS != nullptr) {
		JSON::ObjectValueRef objectJSON = new JSON::ObjectValue ();
		for (const auto& member : objectJS->GetItemTable ()) {

			objectJSON->AddValue (member.key, ConvertDGJSBaseToJSONValue (member.value));
		}
		return objectJSON;
	}
	JS::Array* arrayJs = dynamic_cast<JS::Array*> ((JS::Base*)jsBase);
	if (arrayJs != nullptr) {
		JSON::ArrayValueRef arrayJSON = new JSON::ArrayValue ();
		for (const auto& item : arrayJs->GetItemArray ()) {
			arrayJSON->AddValue (ConvertDGJSBaseToJSONValue (item));
		}
		return arrayJSON;
	}
	JS::Value* valueJs = dynamic_cast<JS::Value*> ((JS::Base*)jsBase);
	if (valueJs != nullptr) {
		JSON::ValueRef primitiveJSON;
		switch (valueJs->GetType ()) {
		case JS::Value::DEFAULT:
			primitiveJSON = new JSON::NullValue ();
			break;
		case JS::Value::BOOL:
			primitiveJSON = new JSON::BoolValue (valueJs->GetBool ());
			break;
		case JS::Value::INTEGER:
			primitiveJSON = new JSON::NumberValue (valueJs->GetInteger ());
			break;
		case JS::Value::UINTEGER:
			primitiveJSON = new JSON::NumberValue (valueJs->GetUInteger ());
			break;
		case JS::Value::DOUBLE:
			primitiveJSON = new JSON::NumberValue (valueJs->GetDouble ());
			break;
		case JS::Value::STRING:
			primitiveJSON = new JSON::StringValue (valueJs->GetString ());
			break;
		default:
			DBBREAK ();
		}
		return primitiveJSON;
	}
	JS::Function* functionJs = dynamic_cast<JS::Function*> ((JS::Base*)jsBase);
	if (functionJs != nullptr) {
		DBBREAK_STR ("function is not interpreted in JSON object");
	}

	DBBREAK ();
	return nullptr;
}


GS::Ref<JS::Base> ConvertJSONValueToDGJSBase (const JSON::ValueRef value)
{
	if (value == nullptr)
		return nullptr;

	GS::Ref<JS::Base> jsValue;
	switch (value->GetType ()) {
	case JSON::Value::NullType: {
		jsValue = new JS::Value ();
		break;
	}
	case JSON::Value::BoolType: {
		jsValue = new JS::Value (JSON::BoolValue::Cast (value)->Get ());
		break;
	}
	case JSON::Value::ObjectType: {
		GS::Ref<JS::Object> objectJS = new JS::Object ();
		JSON::ObjectValueRef objectJson = JSON::ObjectValue::Cast (value);
		for (GS::UIndex index = 0; index < objectJson->GetSize (); ++index) {
			objectJS->AddItem (objectJson->GetName (index), ConvertJSONValueToDGJSBase (objectJson->Get (index)));
		}
		jsValue = objectJS;
		break;
	}
	case JSON::Value::ArrayType: {
		GS::Ref<JS::Array> arrayJS = new JS::Array ();
		JSON::ArrayValueRef arrayJson = JSON::ArrayValue::Cast (value);
		for (GS::UIndex index = 0; index < arrayJson->GetSize (); ++index) {
			arrayJS->AddItem (ConvertJSONValueToDGJSBase (arrayJson->Get (index)));
		}
		jsValue = arrayJS;
		break;
	}
	case JSON::Value::StringType: {
		jsValue = new JS::Value (JSON::StringValue::Cast (value)->Get ());
		break;
	}
	case JSON::Value::NumberType: {
		JSON::NumberValueRef numberValue = JSON::NumberValue::Cast (value);
		if (numberValue->IsDouble ()) {
			jsValue = new JS::Value (numberValue->GetDouble ());
		} else if (numberValue->IsUInt32 ()) {
			jsValue = new JS::Value (numberValue->GetUInt32 ());
		} else if (numberValue->IsInt32 ()) {
			jsValue = new JS::Value (numberValue->GetInt32 ());
		}
		break;
	}
	default:
		DBBREAK ();
		break;
	}

	return jsValue;
}

}
}

