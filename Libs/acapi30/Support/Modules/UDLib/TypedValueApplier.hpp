#ifndef TYPED_VALUE_APPLIER_HPP
#define TYPED_VALUE_APPLIER_HPP

namespace UD {

template<typename Type>
class TypedValueApplier
{
public:
	virtual ~TypedValueApplier ();
	virtual void ApplyNewValue (Type newValue) const = 0;
};

template<typename Type>
TypedValueApplier<Type>::~TypedValueApplier () {}

}

#endif