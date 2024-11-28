#pragma once

namespace UD {

template<typename Type>
class TypedValueApplier;

typedef TypedValueApplier<bool> BoolValueApplier;
typedef TypedValueApplier<double> DoubleValueApplier;
typedef TypedValueApplier<GS::UniString> StringValueApplier;

}