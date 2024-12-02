// *********************************************************************************************************************
// Description:		The class template GS::Variant represents a type-safe union. 
//					An instance of GS::Variant at any given time holds a value of one of its alternative types.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, KiP
//
// *********************************************************************************************************************


#ifndef GS_VARIANT_HPP
#define GS_VARIANT_HPP

#pragma once


#include "BaseAlgorithms.hpp"
#include "Channel.hpp"
#include "GSDebug.hpp"
#include "HashCommon.hpp"
#include "NatVisTypes.hpp"
#include "ParameterPackTraits.hpp"



namespace GS {


// === Implementation details for Variant ==============================================================================

namespace ImpVariant {


template <class... Types>
struct FunctionTable;


}	// namespace ImpVariant


// === class Variant ===================================================================================================

template <class... Types>
class Variant : private NatVis::NatVisTypes<Variant<Types...>, Types...> {
private:
	static constexpr UInt64		BufferSize  = GS::Max (sizeof (Types)...);
	static constexpr UInt64		BufferAlign = GS::Max (alignof (Types)...);

	alignas (BufferAlign) char	buffer[BufferSize];
	UInt8						typeIndex;

	static_assert (ParameterPack<Types...>::Size >= 2,  "At least two types should be provided.");
	static_assert (ParameterPack<Types...>::Size <= 20, "At most 20 types should be provided.");
	static_assert (ParameterPack<Types...>::IsDecayed,  "'Types...' should be decayed.");
	static_assert (ParameterPack<Types...>::IsUnique,   "'Types...' should be unique.");

	using FunctionTable = ImpVariant::FunctionTable<Types...>;

	template <int Dummy, class... Ts>
	static constexpr bool	AllHaveOperatorEquals    = Conjunction<HasOperatorEquals<Ts>...>;

	template <int Dummy, class... Ts>
	static constexpr bool	AllHaveGenerateHashValue = Conjunction<HasGenerateHashValue<Ts>...>;

	template <class Type>
	static constexpr bool	Contains    = ParameterPack<Types...>::template Contains<Type>;

	template <class Type>
	static constexpr UInt8	TypeToIndex = ParameterPack<Types...>::template FindFirst<Type>;	// called only when 'Type' is found

	template <class Type>
	using IsEnabledType = EnableIf<Contains<Decay<Type>>>;			// if this condition holds, Decay<Type> is not the same as Variant

public:
	Variant (const Variant& source);
	Variant (Variant&& source);

	template <class Type, class = IsEnabledType<Type>>
	Variant (Type&& value);

	template <class Type, class... Args>
	Variant (std::in_place_type_t<Type>, Args&&... args);

	~Variant ();

	Variant&	operator= (const Variant& source);
	Variant&	operator= (Variant&& source);

	template <class Type, class = IsEnabledType<Type>>
	Variant&	operator= (Type&& value);

	template <class Type, class... Args>
	void		New (Args&&... args);

	template <class Type>	bool			Is () const;
	template <class Type>	Type&			Get () & gs_lifebound;
	template <class Type>	Type&&			Get () && gs_lifebound;
	template <class Type>	const Type&		Get () const& gs_lifebound;

	template <class Type, class = IsEnabledType<Type>>
	bool		operator== (const Type& rightOp) const;

	template <class Type, class = IsEnabledType<Type>>
	bool		operator!= (const Type& rightOp) const;

	template <int Dummy = 0, class = EnableIf<AllHaveOperatorEquals<Dummy, Types...>>>
	bool		operator== (const Variant& rightOp) const;

	bool		operator!= (const Variant& rightOp) const;

	template <int Dummy = 0, class = EnableIf<AllHaveGenerateHashValue<Dummy, Types...>>>
	ULong		GenerateHashValue () const;

	template <class Functor>
	decltype (auto)		Call (Functor&& functor);

	template <class Functor>
	decltype (auto)		Call (Functor&& functor) const;

	GSErrCode	Read  (IChannel& ic);
	GSErrCode	Write (OChannel& oc) const;
};


// === Variant methods =================================================================================================

template <class... Types>
Variant<Types...>::Variant (const Variant& source)
{
	typeIndex = source.typeIndex;
	FunctionTable::CopyConstruct (typeIndex, &buffer, &source.buffer);
}


template <class... Types>
Variant<Types...>::Variant (Variant&& source)
{
	typeIndex = source.typeIndex;
	FunctionTable::MoveConstruct (typeIndex, &buffer, &source.buffer);
}


template <class... Types>
template <class Type, class /*= IsEnabledType<Type>*/>
Variant<Types...>::Variant (Type&& value)
{
	typeIndex = TypeToIndex<Decay<Type>>;
	::new (buffer) Decay<Type> (std::forward<Type> (value));
}


template <class... Types>
template <class Type, class... Args>
Variant<Types...>::Variant (std::in_place_type_t<Type>, Args&&... args)
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");
	static_assert (Contains<Type>, "'Type' should be one of 'Types...'.");

	typeIndex = TypeToIndex<Type>;
	::new (buffer) Type { std::forward<Args> (args)... };
}


template <class... Types>
Variant<Types...>::~Variant ()
{
	FunctionTable::Destroy (typeIndex, &buffer);
}


template <class... Types>
Variant<Types...>&		Variant<Types...>::operator= (const Variant& source)
{
	if (typeIndex == source.typeIndex) {
		FunctionTable::CopyAssign (typeIndex, &buffer, &source.buffer);
	} else {
		FunctionTable::Destroy (typeIndex, &buffer);
		typeIndex = source.typeIndex;
		FunctionTable::CopyConstruct (typeIndex, &buffer, &source.buffer);
	}

	return *this;
}


template <class... Types>
Variant<Types...>&		Variant<Types...>::operator= (Variant&& source)
{
	if (typeIndex == source.typeIndex) {
		FunctionTable::MoveAssign (typeIndex, &buffer, &source.buffer);
	} else {
		FunctionTable::Destroy (typeIndex, &buffer);
		typeIndex = source.typeIndex;
		FunctionTable::MoveConstruct (typeIndex, &buffer, &source.buffer);
	}

	return *this;
}


template <class... Types>
template <class Type, class /*= IsEnabledType<Type>*/>
Variant<Types...>&		Variant<Types...>::operator= (Type&& value)
{
	if (typeIndex == TypeToIndex<Decay<Type>>) {
		reinterpret_cast<Decay<Type>&> (buffer) = std::forward<Type> (value);
	} else {
		FunctionTable::Destroy (typeIndex, &buffer);
		typeIndex = TypeToIndex<Decay<Type>>;
		::new (buffer) Decay<Type> (std::forward<Type> (value));
	}

	return *this;
}


template <class... Types>
template <class Type, class... Args>
void	Variant<Types...>::New (Args&&... args)
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");
	static_assert (Contains<Type>, "'Type' should be one of 'Types...'.");

	FunctionTable::Destroy (typeIndex, &buffer);
	typeIndex = TypeToIndex<Type>;
	::new (buffer) Type { std::forward<Args> (args)... };
}


template <class... Types>
template <class Type>
bool	Variant<Types...>::Is () const
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");
	static_assert (Contains<Type>, "'Type' should be one of 'Types...'.");

	return typeIndex == TypeToIndex<Type>;
}


template <class... Types>
template <class Type>
Type&	Variant<Types...>::Get () &
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");
	static_assert (Contains<Type>, "'Type' should be one of 'Types...'.");

	DBASSERT (Is<Type> ());

	return reinterpret_cast<Type&> (buffer);
}


template <class... Types>
template <class Type>
const Type&		Variant<Types...>::Get () const&
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");
	static_assert (Contains<Type>, "'Type' should be one of 'Types...'.");

	DBASSERT (Is<Type> ());

	return reinterpret_cast<const Type&> (buffer);
}


template <class... Types>
template <class Type>
Type&&	Variant<Types...>::Get () &&
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");
	static_assert (Contains<Type>, "'Type' should be one of 'Types...'.");

	DBASSERT (Is<Type> ());

	return std::move (reinterpret_cast<Type&> (buffer));
}


template <class... Types>
template <class Type, class /*= IsEnabledType<Type>*/>
bool	Variant<Types...>::operator== (const Type& rightOp) const
{
	return Is<Decay<Type>> () && Get<Decay<Type>> () == rightOp;
}


template <class... Types>
template <class Type, class /*= IsEnabledType<Type>*/>
bool	Variant<Types...>::operator!= (const Type& rightOp) const
{
	return !operator== (rightOp);
}


template <class... Types>
template <int Dummy /*= 0*/, class /*= EnableIf<AllHaveOperatorEquals<Dummy, Types...>>*/>
bool	Variant<Types...>::operator== (const Variant& rightOp) const
{
	return typeIndex == rightOp.typeIndex &&
		   FunctionTable::IsEqual (typeIndex, &buffer, &rightOp.buffer);
}


template <class... Types>
bool	Variant<Types...>::operator!= (const Variant& rightOp) const
{
	return !operator== (rightOp);
}


template <class... Types>
template <int Dummy /*= 0*/, class /*= EnableIf<AllHaveGenerateHashValue<Dummy, Types...>>*/>
ULong	Variant<Types...>::GenerateHashValue () const
{
	return FunctionTable::GenerateHashValue (typeIndex, &buffer);
}


template <class... Types>
template <class Functor>
decltype (auto)		Variant<Types...>::Call (Functor&& functor)
{
	return FunctionTable::Call (typeIndex, &buffer, std::forward<Functor> (functor));
}


template <class... Types>
template <class Functor>
decltype (auto)		Variant<Types...>::Call (Functor&& functor) const
{
	return FunctionTable::Call (typeIndex, &buffer, std::forward<Functor> (functor));
}


template <class... Types>
GSErrCode	Variant<Types...>::Read (IChannel& ic)
{
	static_assert (Conjunction<IsDefaultConstructible<Types>...>, "All 'Types...' have to be default-constructible for Read ().");

	UInt8 readTypeIndex;

	const GSErrCode err = ic.Read (readTypeIndex);
	if (err != NoError)
		return err;

	if (DBERROR (readTypeIndex >= ParameterPackSize<Types...>))
		return Error;

	if (typeIndex != readTypeIndex) {
		FunctionTable::Destroy (typeIndex, &buffer);
		typeIndex = readTypeIndex;
		FunctionTable::DefaultConstruct (typeIndex, &buffer);
	}

	return FunctionTable::Read (typeIndex, ic, &buffer);
}


template <class... Types>
GSErrCode	Variant<Types...>::Write (OChannel& oc) const
{
	const GSErrCode err = oc.Write (typeIndex);
	if (err != NoError)
		return err;

	return FunctionTable::Write (typeIndex, oc, &buffer);
}


// === Implementation details for Variant ==============================================================================

namespace ImpVariant {


template <class Type, class... Types>
struct FunctionTable<Type, Types...> {
	static void		DefaultConstruct (UInt8 typeIndex, void* ptr)
	{
		if (typeIndex == 0)
			FunctionTable<Type>::DefaultConstruct (typeIndex, ptr);
		else
			FunctionTable<Types...>::DefaultConstruct (typeIndex - 1, ptr);
	}

	static void		Destroy (UInt8 typeIndex, void* ptr)
	{
		if (typeIndex == 0)
			FunctionTable<Type>::Destroy (typeIndex, ptr);
		else
			FunctionTable<Types...>::Destroy (typeIndex - 1, ptr);
	}

	static void		CopyConstruct (UInt8 typeIndex, void* target, const void* source)
	{
		if (typeIndex == 0)
			FunctionTable<Type>::CopyConstruct (typeIndex, target, source);
		else
			FunctionTable<Types...>::CopyConstruct (typeIndex - 1, target, source);
	}

	static void		CopyAssign (UInt8 typeIndex, void* target, const void* source)
	{
		if (typeIndex == 0)
			FunctionTable<Type>::CopyAssign (typeIndex, target, source);
		else
			FunctionTable<Types...>::CopyAssign (typeIndex - 1, target, source);
	}

	static void		MoveConstruct (UInt8 typeIndex, void* target, void* source)
	{
		if (typeIndex == 0)
			FunctionTable<Type>::MoveConstruct (typeIndex, target, source);
		else
			FunctionTable<Types...>::MoveConstruct (typeIndex - 1, target, source);
	}

	static void		MoveAssign (UInt8 typeIndex, void* target, void* source)
	{
		if (typeIndex == 0)
			FunctionTable<Type>::MoveAssign (typeIndex, target, source);
		else
			FunctionTable<Types...>::MoveAssign (typeIndex - 1, target, source);
	}

	static bool		IsEqual (UInt8 typeIndex, const void* leftOp, const void* rightOp)
	{
		if (typeIndex == 0)
			return FunctionTable<Type>::IsEqual (typeIndex, leftOp, rightOp);
		else
			return FunctionTable<Types...>::IsEqual (typeIndex - 1, leftOp, rightOp);
	}

	static ULong	GenerateHashValue (UInt8 typeIndex, const void* ptr)
	{
		if (typeIndex == 0)
			return FunctionTable<Type>::GenerateHashValue (typeIndex, ptr);
		else
			return FunctionTable<Types...>::GenerateHashValue (typeIndex - 1, ptr);
	}

	template <class Functor>
	static decltype (auto)		Call (UInt8 typeIndex, void* ptr, Functor&& functor)
	{
		if (typeIndex == 0)
			return FunctionTable<Type>::Call (typeIndex, ptr, std::forward<Functor> (functor));
		else
			return FunctionTable<Types...>::Call (typeIndex - 1, ptr, std::forward<Functor> (functor));
	}

	template <class Functor>
	static decltype (auto)		Call (UInt8 typeIndex, const void* ptr, Functor&& functor)
	{
		if (typeIndex == 0)
			return FunctionTable<Type>::Call (typeIndex, ptr, std::forward<Functor> (functor));
		else
			return FunctionTable<Types...>::Call (typeIndex - 1, ptr, std::forward<Functor> (functor));
	}

	static GSErrCode	Read (UInt8 typeIndex, IChannel& ic, void* ptr)
	{
		if (typeIndex == 0)
			return FunctionTable<Type>::Read (typeIndex, ic, ptr);
		else
			return FunctionTable<Types...>::Read (typeIndex - 1, ic, ptr);
	}

	static GSErrCode	Write (UInt8 typeIndex, OChannel& oc, const void* ptr)
	{
		if (typeIndex == 0)
			return FunctionTable<Type>::Write (typeIndex, oc, ptr);
		else
			return FunctionTable<Types...>::Write (typeIndex - 1, oc, ptr);
	}
};


template <class Type>
struct FunctionTable<Type> {
	static void		DefaultConstruct (UInt8 /*typeIndex*/, void* ptr)
	{
		::new (ptr) Type ();
	}

	static void		Destroy (UInt8 /*typeIndex*/, void* ptr)
	{
		reinterpret_cast<Type*> (ptr)->~Type ();
	}

	static void		CopyConstruct (UInt8 /*typeIndex*/, void* target, const void* source)
	{
		::new (target) Type (*reinterpret_cast<const Type*> (source));
	}

	static void		CopyAssign (UInt8 /*typeIndex*/, void* target, const void* source)
	{
		*reinterpret_cast<Type*> (target) = *reinterpret_cast<const Type*> (source);
	}

	static void		MoveConstruct (UInt8 /*typeIndex*/, void* target, void* source)
	{
		::new (target) Type (std::move (*reinterpret_cast<Type*> (source)));
	}

	static void		MoveAssign (UInt8 /*typeIndex*/, void* target, void* source)
	{
		*reinterpret_cast<Type*> (target) = std::move (*reinterpret_cast<Type*> (source));
	}

	static bool		IsEqual (UInt8 /*typeIndex*/, const void* leftOp, const void* rightOp)
	{
		return *reinterpret_cast<const Type*> (leftOp) == *reinterpret_cast<const Type*> (rightOp);
	}

	static ULong	GenerateHashValue (UInt8 /*typeIndex*/, const void* ptr)
	{
		return GS::CalculateHashValue (*reinterpret_cast<const Type*> (ptr));
	}

	template <class Functor>
	static decltype (auto)		Call (UInt8 /*typeIndex*/, void* ptr, Functor&& functor)
	{
		return std::forward<Functor> (functor) (*reinterpret_cast<Type*> (ptr));
	}

	template <class Functor>
	static decltype (auto)		Call (UInt8 /*typeIndex*/, const void* ptr, Functor&& functor)
	{
		return std::forward<Functor> (functor) (*reinterpret_cast<const Type*> (ptr));
	}

	static GSErrCode	Read (UInt8 /*typeIndex*/, IChannel& ic, void* ptr)
	{
		return ic.Read (*reinterpret_cast<Type*> (ptr));
	}

	static GSErrCode	Write (UInt8 /*typeIndex*/, OChannel& oc, const void* ptr)
	{
		return oc.Write (*reinterpret_cast<const Type*> (ptr));
	}
};


}	// namespace ImpVariant


}	// namespace GS


#endif
