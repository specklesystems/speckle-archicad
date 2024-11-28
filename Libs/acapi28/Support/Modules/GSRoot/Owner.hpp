
// *****************************************************************************
//
//                                  Class Owner
//
// Module:		   GSRoot
// Namespace:	   GS
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined OWNER_HPP
#define OWNER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "GSAssertCore.hpp"
#include "StandardTypeTraits.hpp"

// ================================ Class Owner ================================

namespace GS {

template <class Type>
class Owner {
private:
	Type* ptr = nullptr;

	template <class T> friend class Owner;

public:
	Owner () = default;
	Owner (std::nullptr_t)										{}
	explicit Owner (Type* ptr): ptr (ptr)						{}

	template <class DerivedType>
	explicit Owner (DerivedType* ptr): ptr (ptr)				{}

	Owner (const Owner&)										= delete;
	Owner (Owner&& source) noexcept								{ ptr = source.ptr; source.ptr = nullptr; }

	template <class DerivedType>
	Owner (Owner<DerivedType>&& source) noexcept				{ ptr = source.ptr; source.ptr = nullptr; }

	~Owner ()													{ delete ptr; GS_DEBUG_ONLY (ptr = reinterpret_cast<Type*> (BadPointer)); }

	Owner&			operator= (const Owner&)					= delete;
	void			operator= (Owner&& source)					{ delete ptr; ptr = source.ptr; source.ptr = nullptr; }

	template <class DerivedType>
	void			operator= (Owner<DerivedType>&& source)		{ delete ptr; ptr = source.ptr; source.ptr = nullptr; }

	Type&			operator* () gs_lifebound					{ PRECOND_DB (ptr != nullptr); return *ptr; }
	const Type&		operator* () const gs_lifebound				{ PRECOND_DB (ptr != nullptr); return *ptr; }

	Type*			operator-> () gs_lifebound					{ PRECOND_DB (ptr != nullptr); return ptr; }
	const Type*		operator-> () const gs_lifebound			{ PRECOND_DB (ptr != nullptr); return ptr; }

	bool			operator== (const Type* rightOp) const		{ return ptr == rightOp; }
	bool			operator!= (const Type* rightOp) const		{ return ptr != rightOp; }

	void			Move (Owner& source)						{ delete ptr; ptr = source.ptr; source.ptr = nullptr; }

	Owner&&			Pass (void)									{ return static_cast<Owner&&> (*this); }

	Type*			Get (void) gs_lifebound						{ return ptr; }
	const Type*		Get (void) const gs_lifebound				{ return ptr; }

	Type*			Release (void)								{ Type* result = ptr; ptr = nullptr; return result; }

	void			Delete (void)								{ delete ptr; ptr = nullptr; }
};


template <class Type>
Owner<Type>		Pass (Type* ptr)
{
	return Owner<Type> (ptr);
}


template <class Type, class... Args, class = EnableIf<!IsArray<Type>>>
Owner<Type>		NewOwned (Args&&... args)
{
	return Owner<Type> (new Type (std::forward<Args> (args)...));
}


/* ================================================================================================================== */


template <class Type>
class Owner<Type[]> {
private:
	Type* array = nullptr;

	template <class T> friend class Owner;

public:
	Owner () = default;
	Owner (std::nullptr_t)										{}
	explicit Owner (Type* array): array (array)					{}

	template <class DerivedType>
	explicit Owner (DerivedType* array): array (array)			{}

	Owner (const Owner&)										= delete;
	Owner (Owner&& source) noexcept								{ array = source.array; source.array = nullptr; }

	template <class DerivedType>
	Owner (Owner<DerivedType>&& source) noexcept				{ array = source.array; source.array = nullptr; }

	~Owner ()													{ delete [] array; GS_DEBUG_ONLY (array = reinterpret_cast<Type*> (BadPointer)); }

	Owner&			operator= (const Owner&)					= delete;
	void			operator= (Owner&& source)					{ delete[] array; array = source.array; source.array = nullptr; }

	template <class DerivedType>
	void			operator= (Owner<DerivedType>&& source)		{ delete[] array; array = source.array; source.array = nullptr; }

	Type&			operator[] (UInt64 idx) gs_lifebound		{ PRECOND_DB (array != nullptr); return array[idx]; }
	const Type&		operator[] (UInt64 idx) const gs_lifebound	{ PRECOND_DB (array != nullptr); return array[idx]; }

	bool			operator== (const Type* rightOp) const		{ return (array == rightOp); }
	bool			operator!= (const Type* rightOp) const		{ return (array != rightOp); }

	void			Move (Owner& source)						{ delete[] array; array = source.array; source.array = nullptr; }

	Owner&&			Pass (void)									{ return static_cast<Owner&&> (*this); }

	Type*			Get (void) gs_lifebound						{ return array; }
	const Type*		Get (void) const gs_lifebound				{ return array; }

	Type*			Release (void)								{ Type* result = array; array = nullptr; return result; }

	void			Delete (void)								{ delete[] array; array = nullptr; }
};


template <class Type>
Owner<Type[]>	PassArray (Type* array)
{
	return Owner<Type[]> (array);
}


template <class ArrayType, class = EnableIf<IsArray<ArrayType>>>
Owner<ArrayType>	NewOwned (const std::size_t count)
{
	using Type = RemoveExtent<ArrayType>;

	return Owner<ArrayType> (new Type[count] {});
}


}	// namespace GS


using GS::Owner;
using GS::Pass;
using GS::PassArray;
using GS::NewOwned;


#endif
