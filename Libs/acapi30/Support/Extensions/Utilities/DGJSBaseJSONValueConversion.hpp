
#ifndef DGJSBASEJSONVALUECONVERSION_HPP
#define DGJSBASEJSONVALUECONVERSION_HPP
#pragma once

// JavascriptEngine
#include "JSValues.hpp"

// JSON
#include "JSON/Value.hpp"

namespace Extensions {

namespace Utilities {

JSON::ValueRef		ConvertDGJSBaseToJSONValue (const GS::Ref<JS::Base>& jsBase);
GS::Ref<JS::Base>	ConvertJSONValueToDGJSBase (const JSON::ValueRef value);

} // namespace Utilities

} // namespace Extensions


#endif
