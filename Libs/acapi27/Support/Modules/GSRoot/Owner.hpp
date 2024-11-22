
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
#include "StandardTypeTraits.hpp"

// ================================ Class Owner ================================

namespace GS {

template <class Type>
class Owner {
private:
	Type* ptr;

	template <class T>	friend class Owner;		// to allow different Owner<T> to access each other's members

public:
	Owner (): ptr (nullptr)							{}
	Owner (std::nullptr_t): ptr (nullptr)			{}
	explicit Owner (Type* ptr): ptr (ptr)			{}

	template <class DerivedType>
	explicit Owner (DerivedType* ptr): ptr (ptr)	{}

	Owner (const Owner&)							= delete;
	Owner (Owner&& source)							{ ptr = source.ptr; source.ptr = nullptr; }

	template <class DerivedType>
	Owner (Owner<DerivedType>&& source)				{ ptr = source.ptr; source.ptr = nullptr; }

	Owner&	operator= (const Owner&)				= delete;
	void	operator= (Owner&& source)				{ delete ptr; ptr = source.ptr; source.ptr = nullptr; }

	template <class DerivedType>
	void	operator= (Owner<DerivedType>&& source)	{ delete ptr; ptr = source.ptr; source.ptr = nullptr; }

	void	Move (Owner& source)					{ delete ptr; ptr = source.ptr; source.ptr = nullptr; }

	~Owner ()										{ delete ptr; GS_DEBUG_ONLY (ptr = reinterpret_cast<Type*> (BadPointer)); }

	Type&		operator* ()						{ return *ptr; }
	const Type&	operator* () const					{ return *ptr; }
	Type*		operator-> ()						{ return ptr; }
	const Type*	operator-> () const					{ return ptr; }

	bool	operator== (const Type* rightOp) const	{ return (ptr == rightOp); }
	bool	operator!= (const Type* rightOp) const	{ return (ptr != rightOp); }

	Owner&&	Pass (void)								{ return static_cast<Owner&&> (*this); }

	Type*		Get (void)							{ return ptr; }
	const Type*	Get (void) const					{ return ptr; }

	Type*	Release (void)							{ Type* result = ptr; ptr = nullptr; return result; }

	void	Delete (void)							{ delete ptr; ptr = nullptr; }
};


template <class Type>
Owner<Type>		Pass (Type* ptr)
{
	return Owner<Type> (ptr);
}


template <class Type, class... Args, class = EnableIf<!IsArray<Type>>>
Owner<Type> NewOwned (Args&&... args)
{
	return Owner<Type> (new Type (std::forward<Args> (args)...));
}


template <class Type>
class Owner<Type[]> {
private:
	Type* array;

	template <class T>	friend class Owner;		// to allow different Owner<T> to access each other's members

public:
	Owner (): array (nullptr)						{}
	Owner (std::nullptr_t): array (nullptr)			{}
	explicit Owner (Type* array): array (array)		{}

	template <class DerivedType>
	explicit Owner (DerivedType* array): array (array)	{}

	Owner (const Owner&)							= delete;
	Owner (Owner&& source)							{ array = source.array; source.array = nullptr; }

	template <class DerivedType>
	Owner (Owner<DerivedType>&& source)				{ array = source.array; source.array = nullptr; }

	Owner&	operator= (const Owner&)				= delete;
	void	operator= (Owner&& source)				{ delete [] array; array = source.array; source.array = nullptr; }

	template <class DerivedType>
	void	operator= (Owner<DerivedType>&& source)	{ delete [] array; array = source.array; source.array = nullptr; }

	void	Move (Owner& source)					{ delete [] array; array = source.array; source.array = nullptr; }

	~Owner ()										{ delete [] array; GS_DEBUG_ONLY (array = reinterpret_cast<Type*> (BadPointer)); }

	Type&		operator* ()						{ return *array; }
	const Type&	operator* () const					{ return *array; }
	Type*		operator-> ()						{ return array; }
	const Type*	operator-> () const					{ return array; }

	Type&		operator[] (UInt64 idx)				{ return array[idx]; }
	const Type&	operator[] (UInt64 idx) const		{ return array[idx]; }

	bool	operator== (const Type* rightOp) const	{ return (array == rightOp); }
	bool	operator!= (const Type* rightOp) const	{ return (array != rightOp); }

	Owner&&	Pass (void)								{ return static_cast<Owner&&> (*this); }

	Type*		Get (void)							{ return array; }
	const Type*	Get (void) const					{ return array; }

	Type*	Release (void)							{ Type* result = array; array = nullptr; return result; }

	void	Delete (void)							{ delete [] array; array = nullptr; }
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

	return Owner<ArrayType> (new Type[count]);
}


}	// namespace GS


using GS::Owner;
using GS::Pass;
using GS::PassArray;
using GS::NewOwned;


#endif
