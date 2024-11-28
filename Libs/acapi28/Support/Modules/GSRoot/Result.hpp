// *********************************************************************************************************************
// Description:		The class template Result contains a value, or an error.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef RESULT_HPP
#define RESULT_HPP

#pragma once


#include "Variant.hpp"


namespace GS {


// === Implementation details for Result ===============================================================================

namespace ImpResult {


template <class SourceType>
class ErrorSource {};


}	// namespace ImpResult


// === class Result<ValueType, ErrorType> ==============================================================================

template <class ValueType, class ErrorType = GS::ErrorType>
class Result {
private:
	static_assert (IsDecayed<ValueType>, "'ValueType' should be decayed.");
	static_assert (IsDecayed<ErrorType>, "'ErrorType' should be decayed.");

	Variant<ValueType, ErrorType>	variant;

	static ValueType	SelectType (const ValueType&);		// not defined
	static ErrorType	SelectType (const ErrorType&);		// not defined

	template <class SourceType>
	using IsEnabledSourceType = EnableIf<!IsSame<Decay<SourceType>, Result>>;

public:
	template <class SourceType, class = IsEnabledSourceType<SourceType>>
	Result (SourceType&& valueOrErrorSource);

	Result (NoErrorType) = delete;

	template <class SourceType, class = IsEnabledSourceType<SourceType>>
	void				operator= (SourceType&& valueOrErrorSource);

	void				operator= (NoErrorType) = delete;

	bool				IsOK () const;
	bool				IsError () const;

	bool				ContainsValue (const ValueType& value) const;
	bool				ContainsError (const ErrorType& error) const;

	ValueType&			operator* () & gs_lifebound;
	ValueType&&			operator* () && gs_lifebound;
	const ValueType&	operator* () const& gs_lifebound;

	ValueType*			operator-> () gs_lifebound;
	const ValueType*	operator-> () const gs_lifebound;

	ErrorType&			GetError () & gs_lifebound;
	ErrorType&&			GetError () && gs_lifebound;
	const ErrorType&	GetError () const& gs_lifebound;
};


// === class Result<Type, Type> ========================================================================================

template <class Type>
class Result<Type, Type> {
private:
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");

	bool	isOK;
	Type	result;

	template <class SourceType>
	using IsEnabledSourceType = EnableIf<!IsSame<Decay<SourceType>, Result>>;

	template <class SourceType>
	static SourceType&&		ForwardAs (ImpResult::ErrorSource<SourceType>& errorSource);

public:
	template <class SourceType, class = IsEnabledSourceType<SourceType>>
	Result (SourceType&& valueSource);

	template <class SourceType>
	Result (ImpResult::ErrorSource<SourceType>& errorSource);

	Result (NoErrorType) = delete;

	template <class SourceType, class = IsEnabledSourceType<SourceType>>
	void			operator= (SourceType&& valueSource);

	template <class SourceType>
	void			operator= (ImpResult::ErrorSource<SourceType>& errorSource);

	void			operator= (NoErrorType) = delete;

	bool			IsOK () const;
	bool			IsError () const;

	bool			ContainsValue (const Type& value) const;
	bool			ContainsError (const Type& error) const;

	Type&			operator* () &		gs_lifebound;
	const Type&		operator* () const&	gs_lifebound;
	Type&&			operator* () &&		gs_lifebound;

	Type*			operator-> ()		gs_lifebound;
	const Type*		operator-> () const	gs_lifebound;

	Type&			GetError () &		gs_lifebound;
	const Type&		GetError () const&	gs_lifebound;
	Type&&			GetError () &&		gs_lifebound;
};


// === Global functions ================================================================================================

template <class SourceType>
ImpResult::ErrorSource<SourceType>&		AsError (SourceType&& errorSource)
{
	return (ImpResult::ErrorSource<SourceType>&) (errorSource);
}


// === Result<ValueType, ErrorType> inline methods =====================================================================

template <class ValueType, class ErrorType>
template <class SourceType, class /*= IsEnabledSourceType<SourceType>*/>
Result<ValueType, ErrorType>::Result (SourceType&& valueOrErrorSource) :
	variant (std::in_place_type<decltype (SelectType (valueOrErrorSource))>,
			 std::forward<SourceType> (valueOrErrorSource))
{
}


template <class ValueType, class ErrorType>
template <class SourceType, class /*= IsEnabledSourceType<SourceType>*/>
void	Result<ValueType, ErrorType>::operator= (SourceType&& valueOrErrorSource)
{
	using SelectedType = decltype (SelectType (valueOrErrorSource));

	if (variant.template Is<SelectedType> ())
		variant.template Get<SelectedType> () = std::forward<SourceType> (valueOrErrorSource);
	else
		variant.template New<SelectedType> (std::forward<SourceType> (valueOrErrorSource));
}


template <class ValueType, class ErrorType>
bool	Result<ValueType, ErrorType>::IsOK () const
{
	return variant.template Is<ValueType> ();
}


template <class ValueType, class ErrorType>
bool	Result<ValueType, ErrorType>::IsError () const
{
	return variant.template Is<ErrorType> ();
}


template <class ValueType, class ErrorType>
bool	Result<ValueType, ErrorType>::ContainsValue (const ValueType& value) const
{
	return variant == value;
}


template <class ValueType, class ErrorType>
bool	Result<ValueType, ErrorType>::ContainsError (const ErrorType& error) const
{
	return variant == error;
}


template <class ValueType, class ErrorType>
ValueType&	Result<ValueType, ErrorType>::operator* () &
{
	return variant.template Get<ValueType> ();
}


template <class ValueType, class ErrorType>
const ValueType&	Result<ValueType, ErrorType>::operator* () const&
{
	return variant.template Get<ValueType> ();
}


template <class ValueType, class ErrorType>
ValueType&&		Result<ValueType, ErrorType>::operator* () &&
{
	return std::move (variant).template Get<ValueType> ();
}


template <class ValueType, class ErrorType>
ValueType*	Result<ValueType, ErrorType>::operator-> ()
{
	return &operator* ();
}


template <class ValueType, class ErrorType>
const ValueType*	Result<ValueType, ErrorType>::operator-> () const
{
	return &operator* ();
}


template <class ValueType, class ErrorType>
ErrorType&	Result<ValueType, ErrorType>::GetError () &
{
	return variant.template Get<ErrorType> ();
}


template <class ValueType, class ErrorType>
const ErrorType&	Result<ValueType, ErrorType>::GetError () const&
{
	return variant.template Get<ErrorType> ();
}


template <class ValueType, class ErrorType>
ErrorType&&		Result<ValueType, ErrorType>::GetError () &&
{
	return std::move (variant).template Get<ErrorType> ();
}


// === Result<Type, Type> inline methods ===============================================================================

template <class Type>
template <class SourceType, class /*= IsEnabledSourceType<SourceType>*/>
Result<Type, Type>::Result (SourceType&& valueSource) :
	isOK   (true),
	result (std::forward<SourceType> (valueSource))
{
	static_assert (GS::IsConvertible<SourceType, Type>, "'SourceType' should be convertible to 'Type'.");
}


template <class Type>
template <class SourceType>
Result<Type, Type>::Result (ImpResult::ErrorSource<SourceType>& errorSource) :
	isOK   (false),
	result (ForwardAs<SourceType> (errorSource))
{
}


template <class Type>
template <class SourceType, class /*= IsEnabledSourceType<SourceType>*/>
void	Result<Type, Type>::operator= (SourceType&& valueSource)
{
	isOK   = true;
	result = std::forward<SourceType> (valueSource);
}


template <class Type>
template <class SourceType>
void	Result<Type, Type>::operator= (ImpResult::ErrorSource<SourceType>& errorSource)
{
	isOK   = false;
	result = ForwardAs<SourceType> (errorSource);
}


template <class Type>
bool	Result<Type, Type>::IsOK () const
{
	return isOK;
}


template <class Type>
bool	Result<Type, Type>::IsError () const
{
	return !isOK;
}


template <class Type>
bool	Result<Type, Type>::ContainsValue (const Type& value) const
{
	return IsOK () && result == value;
}


template <class Type>
bool	Result<Type, Type>::ContainsError (const Type& error) const
{
	return IsError () && result == error;
}


template <class Type>
Type&	Result<Type, Type>::operator* () &
{
	DBASSERT (IsOK ());
	return result;
}


template <class Type>
const Type&		Result<Type, Type>::operator* () const&
{
	DBASSERT (IsOK ());
	return result;
}


template <class Type>
Type&&		Result<Type, Type>::operator* () &&
{
	DBASSERT (IsOK ());
	return std::move (result);
}


template <class Type>
Type*	Result<Type, Type>::operator-> ()
{
	return &operator* ();
}


template <class Type>
const Type*		Result<Type, Type>::operator-> () const
{
	return &operator* ();
}


template <class Type>
Type&	Result<Type, Type>::GetError () &
{
	DBASSERT (IsError ());
	return result;
}


template <class Type>
const Type&		Result<Type, Type>::GetError () const&
{
	DBASSERT (IsError ());
	return result;
}


template <class Type>
Type&&		Result<Type, Type>::GetError () &&
{
	DBASSERT (IsError ());
	return std::move (result);
}


template <class Type>
template <class SourceType>
SourceType&&	Result<Type, Type>::ForwardAs (ImpResult::ErrorSource<SourceType>& errorSource)
{
	static_assert (!IsSame<Decay<SourceType>, Result>, "Do not use GS::AsError (res), where 'res' is a GS::Result.");

	return std::forward<SourceType> (reinterpret_cast<SourceType&> (errorSource));
}


}	// namespace GS


#endif
