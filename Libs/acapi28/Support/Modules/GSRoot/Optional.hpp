// *********************************************************************************************************************
// Description:		The class template GS::Optional manages an optional contained value, i.e. a value that may or may
//					not be present.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef GS_OPTIONAL_HPP
#define GS_OPTIONAL_HPP

#pragma once


#include "TypeTraits.hpp"
#include "NoValueSelector.hpp"
#include "HashCommon.hpp"
#include "GSAssertCore.hpp"
#include "Channel.hpp"


namespace GS {


// === class Optional ==================================================================================================

template <class Type>
class Optional final {
private:
	alignas (Type) char		buffer[sizeof (Type)];
	bool					hasValue;

	static_assert (IsDecayed<Type>, "'Type' should be decayed.");

	template <class T>	friend class Optional;

	template <class SourceType>
	using IsEnabledSourceType = EnableIf<!IsSame<Decay<SourceType>, Optional> && IsConvertible<SourceType, Type>>;

	using NatVisType = Type;

public:
	Optional ();
	Optional (NoValueSelector);
	Optional (const Type& value);
	Optional (Type&& value);

	template <class SourceType, class = IsEnabledSourceType<SourceType>>
	Optional (SourceType&& value);

	template <class... Args>
	Optional (std::in_place_t, Args&&... args);

	Optional (const Optional& source);
	Optional (Optional&& source);
	template <class SourceType>  Optional (const Optional<SourceType>& source);
	template <class SourceType>  Optional (Optional<SourceType>&& source);
	~Optional ();

	void			operator= (NoValueSelector);
	void			operator= (const Type& newValue);
	void			operator= (Type&& newValue);

	template <class SourceType, class = IsEnabledSourceType<SourceType>>
	void			operator= (SourceType&& newValue);

	void			operator= (const Optional& source);
	void			operator= (Optional&& source);
	template <class SourceType> void  operator= (const Optional<SourceType>& source);
	template <class SourceType> void  operator= (Optional<SourceType>&& source);

	template <class... Args>
	void			New (Args&&... args);

	void			Clear ();
	Type			Pop ();

	bool			IsEmpty () const;
	bool			HasValue () const;

	Type&			Get () & gs_lifebound;
	Type&&			Get () && gs_lifebound;
	const Type&		Get () const& gs_lifebound;

	const Type&		Get (const Type& defaultValue gs_lifebound) const& gs_lifebound;
	Type&&			Get (Type&& defaultValue gs_lifebound) && gs_lifebound;

	Type*			GetPtr () gs_lifebound;
	const Type*		GetPtr () const gs_lifebound;

	Type&			operator* () & gs_lifebound;
	Type&&			operator* () && gs_lifebound;
	const Type&		operator* () const& gs_lifebound;

	Type*			operator-> () gs_lifebound;
	const Type*		operator-> () const gs_lifebound;

	GSErrCode		Read  (IChannel& ic);
	GSErrCode		Write (OChannel& oc) const;
};


// === Optional methods ================================================================================================

template <class Type>
Optional<Type>::Optional () :
	hasValue (false)
{
}


template <class Type>
Optional<Type>::Optional (NoValueSelector) :
	hasValue (false)
{
}


template <class Type>
Optional<Type>::Optional (const Type& value) :
	hasValue (true)
{
	::new (buffer) Type (value);
}


template <class Type>
Optional<Type>::Optional (Type&& value) :
	hasValue (true)
{
	::new (buffer) Type (std::move (value));
}


template <class Type>
template <class SourceType, class /*= IsEnabledSourceType<SourceType>*/>
Optional<Type>::Optional (SourceType&& value) :
	hasValue (true)
{
	::new (buffer) Type (std::forward<SourceType> (value));
}


template <class Type>
template <class... Args>
Optional<Type>::Optional (std::in_place_t, Args&&... args) :
	hasValue (true)
{
	::new (buffer) Type { std::forward<Args> (args)... };
}


template <class Type>
Optional<Type>::Optional (const Optional& source) :
	hasValue (source.hasValue)
{
	if (source.hasValue)
		::new (buffer) Type (reinterpret_cast<const Type&> (source.buffer));
}


template <class Type>
Optional<Type>::Optional (Optional&& source) :
	hasValue (source.hasValue)
{
	if (source.hasValue) {
		::new (buffer) Type (reinterpret_cast<Type&&> (source.buffer));
		reinterpret_cast<Type&&> (source.buffer).~Type ();
		source.hasValue = false;
	}
}


template <class Type>
template <class SourceType>
Optional<Type>::Optional (const Optional<SourceType>& source) :
	hasValue (source.hasValue)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	if (source.hasValue)
		::new (buffer) Type (reinterpret_cast<const SourceType&> (source.buffer));
}


template <class Type>
template <class SourceType>
Optional<Type>::Optional (Optional<SourceType>&& source) :
	hasValue (source.hasValue)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	if (source.hasValue) {
		::new (buffer) Type (reinterpret_cast<SourceType&&> (source.buffer));
		reinterpret_cast<SourceType&&> (source.buffer).~SourceType ();
		source.hasValue = false;
	}
}


template <class Type>
Optional<Type>::~Optional ()
{
	if (hasValue)
		reinterpret_cast<Type&> (buffer).~Type ();
}


template <class Type>
void	Optional<Type>::operator= (NoValueSelector)
{
	Clear ();
}


template <class Type>
void	Optional<Type>::operator= (const Type& newValue)
{
	if (hasValue) {
		reinterpret_cast<Type&> (buffer) = newValue;
	} else {
		::new (buffer) Type (newValue);
		hasValue = true;
	}
}


template <class Type>
void	Optional<Type>::operator= (Type&& newValue)
{
	if (hasValue) {
		reinterpret_cast<Type&> (buffer) = std::move (newValue);
	} else {
		::new (buffer) Type (std::move (newValue));
		hasValue = true;
	}
}


template <class Type>
template <class SourceType, class /*= IsEnabledSourceType<SourceType>*/>
void	Optional<Type>::operator= (SourceType&& newValue)
{
	if (hasValue) {
		reinterpret_cast<Type&> (buffer) = std::forward<SourceType> (newValue);
	} else {
		::new (buffer) Type (std::forward<SourceType> (newValue));
		hasValue = true;
	}
}


template <class Type>
void	Optional<Type>::operator= (const Optional& source)
{
	if (hasValue && source.hasValue) {
		reinterpret_cast<Type&> (buffer) = reinterpret_cast<const Type&> (source.buffer);
	} else if (hasValue && !source.hasValue) {
		reinterpret_cast<Type&> (buffer).~Type ();
		hasValue = false;
	} else if (!hasValue && source.hasValue) {
		::new (buffer) Type (reinterpret_cast<const Type&> (source.buffer));
		hasValue = true;
	}
}


template <class Type>
void	Optional<Type>::operator= (Optional&& source)
{
	if (hasValue && source.hasValue) {
		reinterpret_cast<Type&> (buffer) = reinterpret_cast<Type&&> (source.buffer);
		reinterpret_cast<Type&&> (source.buffer).~Type ();
		source.hasValue = false;
	} else if (hasValue && !source.hasValue) {
		reinterpret_cast<Type&> (buffer).~Type ();
		hasValue = false;
	} else if (!hasValue && source.hasValue) {
		::new (buffer) Type (reinterpret_cast<Type&&> (source.buffer));
		reinterpret_cast<Type&&> (source.buffer).~Type ();
		source.hasValue = false;
		hasValue = true;
	}
}


template <class Type>
template <class SourceType>
void	Optional<Type>::operator= (const Optional<SourceType>& source)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	if (hasValue && source.hasValue) {
		reinterpret_cast<Type&> (buffer) = reinterpret_cast<const SourceType&> (source.buffer);
	} else if (hasValue && !source.hasValue) {
		reinterpret_cast<Type&> (buffer).~Type ();
		hasValue = false;
	} else if (!hasValue && source.hasValue) {
		::new (buffer) Type (reinterpret_cast<const SourceType&> (source.buffer));
		hasValue = true;
	}
}


template <class Type>
template <class SourceType>
void	Optional<Type>::operator= (Optional<SourceType>&& source)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	if (hasValue && source.hasValue) {
		reinterpret_cast<Type&> (buffer) = reinterpret_cast<SourceType&&> (source.buffer);
		reinterpret_cast<SourceType&&> (source.buffer).~SourceType ();
		source.hasValue = false;
	} else if (hasValue && !source.hasValue) {
		reinterpret_cast<Type&> (buffer).~Type ();
		hasValue = false;
	} else if (!hasValue && source.hasValue) {
		::new (buffer) Type (reinterpret_cast<SourceType&&> (source.buffer));
		reinterpret_cast<SourceType&&> (source.buffer).~SourceType ();
		source.hasValue = false;
		hasValue = true;
	}
}


template <class Type>
template <class... Args>
void	Optional<Type>::New (Args&&... args)
{
	Clear ();

	::new (buffer) Type { std::forward<Args> (args)... };
	hasValue = true;
}


template <class Type>
void	Optional<Type>::Clear ()
{
	if (hasValue) {
		reinterpret_cast<Type&> (buffer).~Type ();
		hasValue = false;
	}
}


template <class Type>
Type	Optional<Type>::Pop ()
{
	Type value = std::move (Get ());
	Clear ();
	return value;
}


template <class Type>
bool	Optional<Type>::IsEmpty () const
{
	return !hasValue;
}


template <class Type>
bool	Optional<Type>::HasValue () const
{
	return hasValue;
}


template <class Type>
Type&		Optional<Type>::Get () &
{
	PRECOND_DB (hasValue);

	return reinterpret_cast<Type&> (buffer);
}


template <class Type>
const Type&		Optional<Type>::Get () const&
{
	PRECOND_DB (hasValue);

	return reinterpret_cast<const Type&> (buffer);
}


template <class Type>
Type&&		Optional<Type>::Get () &&
{
	PRECOND_DB (hasValue);

	return std::move (reinterpret_cast<Type&> (buffer));
}


template <class Type>
const Type&		Optional<Type>::Get (const Type& defaultValue) const&
{
	if (hasValue)
		return reinterpret_cast<const Type&> (buffer);
	else
		return defaultValue;
}


template <class Type>
Type&&		Optional<Type>::Get (Type&& defaultValue) &&
{
	if (hasValue)
		return std::move (reinterpret_cast<Type&> (buffer));
	else
		return std::move (defaultValue);
}


template <class Type>
Type*	Optional<Type>::GetPtr ()
{
	return HasValue () ? &Get () : nullptr;
}


template <class Type>
const Type*	Optional<Type>::GetPtr () const
{
	return HasValue () ? &Get () : nullptr;
}


template <class Type>
Type&		Optional<Type>::operator* () &
{
	PRECOND_DB (hasValue);

	return reinterpret_cast<Type&> (buffer);
}


template <class Type>
const Type&		Optional<Type>::operator* () const&
{
	PRECOND_DB (hasValue);

	return reinterpret_cast<const Type&> (buffer);
}


template <class Type>
Type&&		Optional<Type>::operator* () &&
{
	PRECOND_DB (hasValue);

	return std::move (reinterpret_cast<Type&> (buffer));
}


template <class Type>
Type*		Optional<Type>::operator-> ()
{
	PRECOND_DB (hasValue);

	return reinterpret_cast<Type*> (buffer);
}


template <class Type>
const Type*		Optional<Type>::operator-> () const
{
	PRECOND_DB (hasValue);

	return reinterpret_cast<const Type*> (buffer);
}


template <class Type>
GSErrCode	Optional<Type>::Read (IChannel& ic)
{
	GSErrCode err;

	bool readHasValue;
	err = ic.Read (readHasValue);
	if (err != NoError)
		return err;

	if (readHasValue) {
		if (IsEmpty ())
			New ();

		err = ic.Read (Get ());
		if (err != NoError)
			return err;
	} else {
		Clear ();
	}

	return NoError;
}


template <class Type>
GSErrCode	Optional<Type>::Write (OChannel& oc) const
{
	GSErrCode err;
	
	err = oc.Write (HasValue ());
	if (err != NoError)
		return err;

	if (HasValue ()) {
		err = oc.Write (Get ());
		if (err != NoError)
			return err;
	}

	return NoError;
}


// === global functions ================================================================================================

template <class LeftType>
bool	operator== (const Optional<LeftType>& leftOp, NoValueSelector)
{
	return leftOp.IsEmpty ();
}


template <class LeftType, class RightType, class = EnableIf<HasOperatorEquals<LeftType, RightType>>>
bool	operator== (const Optional<LeftType>& leftOp, const RightType& rightOp)
{
	return leftOp.HasValue () && *leftOp == rightOp;
}


template <class LeftType, class RightType, class = EnableIf<HasOperatorEquals<LeftType, RightType>>>
bool	operator== (const LeftType& leftOp, const Optional<RightType>& rightOp)
{
	return rightOp.HasValue () && leftOp == *rightOp;
}


template <class LeftType, class RightType, class = EnableIf<HasOperatorEquals<LeftType, RightType>>>
bool	operator== (const Optional<LeftType>& leftOp, const Optional<RightType>& rightOp)
{
	return leftOp.HasValue () == rightOp.HasValue () && (!leftOp.HasValue () || *leftOp == *rightOp);
}


template <class LeftType>
bool	operator!= (const Optional<LeftType>& leftOp, NoValueSelector rightOp)
{
	return !(leftOp == rightOp);
}


template <class LeftType, class RightType>
bool	operator!= (const Optional<LeftType>& leftOp, const RightType& rightOp)
{
	return !(leftOp == rightOp);
}


template <class LeftType, class RightType>
bool	operator!= (const LeftType& leftOp, const Optional<RightType>& rightOp)
{
	return !(leftOp == rightOp);
}


template <class LeftType, class RightType>
bool	operator!= (const Optional<LeftType>& leftOp, const Optional<RightType>& rightOp)
{
	return !(leftOp == rightOp);
}


template <class Type, class = EnableIf<HasGenerateHashValue<Type>>>
ULong	GenerateHashValue (const Optional<Type>& op)
{
	if (op.HasValue ())
		return GS::CalculateHashValue (*op);
	else
		return 0;
}


template <class Type>
Optional<Type>	ToOptional (const Type* ptr)
{
	return (ptr != nullptr) ? *ptr : Optional<Type> ();
}


}	// namespace GS


#endif
