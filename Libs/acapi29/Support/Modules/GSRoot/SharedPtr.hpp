// *********************************************************************************************************************
// Description:		Counted shared pointer template
//
// Module:			GSRoot
// Namespace:		GS
//
// *********************************************************************************************************************

#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

#pragma once

#include "BaseAlgorithms.hpp"
#include "GSDebug.hpp"
#include "HashCommon.hpp"


namespace GS {

template <typename TPointee>
class ConstSharedPtr;

template <typename TPointee>
class SharedPtr {
	template <typename TOtherPointee>
	friend	class ConstSharedPtr;
	template <typename TOtherPointee>
	friend	class SharedPtr;

public:
	using Pointee = TPointee;

private:
	Pointee*	ptr;

public:
	SharedPtr ();
	SharedPtr (std::nullptr_t);
	template <typename TOtherPointee>
	SharedPtr (TOtherPointee* pointer);
	SharedPtr (const SharedPtr& source);
	template <typename TOtherPointee>
	SharedPtr (const SharedPtr<TOtherPointee>& source);
	template <typename TOtherPointee>
	SharedPtr (SharedPtr<TOtherPointee>&& source);
	enum IfRefCountNotZeroSelector {
		IfRefCountNotZero
	};
	template <typename TOtherPointee>
	SharedPtr (TOtherPointee* pointer, IfRefCountNotZeroSelector);

	template<typename OnDeleteT>
	void Clear (OnDeleteT&& onDeleteCallback);

	~SharedPtr ();

	ULong	GetRefCount () const;
	void	Swap (SharedPtr& rhs);

	SharedPtr& operator= (std::nullptr_t);
	template <typename TOtherPointee>
	SharedPtr& operator= (TOtherPointee* source);
	SharedPtr& operator= (const SharedPtr& source);
	template <typename TOtherPointee>
	SharedPtr& operator= (const SharedPtr<TOtherPointee>& source);
	template <typename TOtherPointee>
	SharedPtr& operator= (SharedPtr<TOtherPointee>&& source);

	Pointee* Get () const;

	Pointee* operator-> () const;
	Pointee& operator* () const;

	Pointee* GetPtr () const;

	const ConstSharedPtr<TPointee>&		AsConst () const;

	bool operator == (std::nullptr_t) const								{ return ptr == nullptr; }
	bool operator != (std::nullptr_t) const								{ return ptr != nullptr; }
	template <typename TOtherPointee>
	bool operator == (const TOtherPointee* rhs) const					{ return ptr == rhs; }
	template <typename TOtherPointee>
	bool operator != (const TOtherPointee* rhs) const					{ return ptr != rhs; }
	template <typename TOtherPointee>
	bool operator == (const ConstSharedPtr<TOtherPointee>& rhs) const	{ return ptr == rhs.ptr; }
	template <typename TOtherPointee>
	bool operator != (const ConstSharedPtr<TOtherPointee>& rhs) const	{ return ptr != rhs.ptr; }
	template <typename TOtherPointee>
	bool operator == (const SharedPtr<TOtherPointee>& rhs) const		{ return ptr == rhs.ptr; }
	template <typename TOtherPointee>
	bool operator != (const SharedPtr<TOtherPointee>& rhs) const		{ return ptr != rhs.ptr; }

	ULong	GenerateHashValue () const									{ return GS::CalculateHashValue (ptr); }
};


template <typename TPointee>
SharedPtr<TPointee>::SharedPtr () :
	ptr (nullptr)
{
}


template <typename TPointee>
SharedPtr<TPointee>::SharedPtr (std::nullptr_t) :
	ptr (nullptr)
{
}


template <typename TPointee>
template <typename TOtherPointee>
SharedPtr<TPointee>::SharedPtr (TOtherPointee* pointer) :
	ptr (pointer)
{
	if (ptr != nullptr)
		ptr->AddRef ();
}


template <typename TPointee>
SharedPtr<TPointee>::SharedPtr (const SharedPtr& source) :
	ptr (source.ptr)
{
	if (ptr != nullptr)
		ptr->AddRef ();
}


template <typename TPointee>
template <typename TOtherPointee>
SharedPtr<TPointee>::SharedPtr (const SharedPtr<TOtherPointee>& source) :
	ptr (source.ptr)
{
	if (ptr != nullptr)
		ptr->AddRef ();
}


template <typename TPointee>
template <typename TOtherPointee>
SharedPtr<TPointee>::SharedPtr (SharedPtr<TOtherPointee>&& source) :
	ptr (source.ptr)
{	
	source.ptr = nullptr;
}


template <typename TPointee>
template <typename TOtherPointee>
SharedPtr<TPointee>::SharedPtr (TOtherPointee* pointer, IfRefCountNotZeroSelector) :
	ptr (nullptr)
{
	if (pointer != nullptr && pointer->AddRefIfRefCountNotZero ()) {
		ptr = pointer;
	}
}


template <typename TPointee>
template <typename OnDeleteT>
void SharedPtr<TPointee>::Clear (OnDeleteT&& onDeleteCallback)
{
	Pointee* prevPtr = ptr;
	ptr = nullptr;

	if (prevPtr != nullptr) {
		prevPtr->template Release<Pointee> (std::forward<OnDeleteT> (onDeleteCallback));
	}
}


template <typename TPointee>
SharedPtr<TPointee>::~SharedPtr ()
{
	if (ptr != nullptr)
		ptr->Release ();
	ptr = nullptr;
}


template <typename TPointee>
ULong SharedPtr<TPointee>::GetRefCount () const
{
	return ptr == nullptr ? 0 : ptr->GetRefCount ();
}


template <typename TPointee>
void SharedPtr<TPointee>::Swap (SharedPtr& rhs)
{
	GS::Swap (ptr, rhs.ptr);
}


template <typename TPointee>
SharedPtr<TPointee>& SharedPtr<TPointee>::operator= (std::nullptr_t)
{
	SharedPtr thisTypeNullPtr;
	Swap (thisTypeNullPtr);
	return *this;
}


template <typename TPointee>
template <typename TOtherPointee>
SharedPtr<TPointee>& SharedPtr<TPointee>::operator= (TOtherPointee* source)
{
	if (ptr != source) {
		SharedPtr thisTypePtr (source);
		Swap (thisTypePtr);
	}
	return *this;
}


template <typename TPointee>
SharedPtr<TPointee>& SharedPtr<TPointee>::operator= (const SharedPtr& source)
{
	if (ptr != source.ptr) {
		SharedPtr thisTypePtr (source);
		Swap (thisTypePtr);
	}
	return *this;
}


template <typename TPointee>
template <typename TOtherPointee>
SharedPtr<TPointee>& SharedPtr<TPointee>::operator= (const SharedPtr<TOtherPointee>& source)
{
	if (ptr != source.ptr) {
		SharedPtr thisTypePtr (source);
		Swap (thisTypePtr);
	}
	return *this;
}


template <typename TPointee>
template <typename TOtherPointee>
SharedPtr<TPointee>& SharedPtr<TPointee>::operator= (SharedPtr<TOtherPointee>&& source)
{
	SharedPtr thisTypePtr (std::move (source));
	Swap (thisTypePtr);
	return *this;
}


template <typename TPointee>
typename SharedPtr<TPointee>::Pointee* SharedPtr<TPointee>::Get () const
{
	return ptr;
}


template <typename TPointee>
typename SharedPtr<TPointee>::Pointee* SharedPtr<TPointee>::operator-> () const
{
	return ptr;
}


template <typename TPointee>
typename SharedPtr<TPointee>::Pointee& SharedPtr<TPointee>::operator* () const
{
	return *ptr;
}


template <class TPointee>
inline typename SharedPtr<TPointee>::Pointee* SharedPtr<TPointee>::GetPtr () const
{
	return ptr;
}


template <typename TPointee>
class ConstSharedPtr {
	template <typename TOtherPointee>
	friend	class ConstSharedPtr;
	template <typename TOtherPointee>
	friend	class SharedPtr;

public:
	using Pointee = TPointee;

private:
	const Pointee*	ptr;

public:
	ConstSharedPtr ();

	ConstSharedPtr (std::nullptr_t);
	template <typename TOtherPointee>
	ConstSharedPtr (const TOtherPointee* pointer);
	ConstSharedPtr (const ConstSharedPtr& source);
	template <typename TOtherPointee>
	ConstSharedPtr (const ConstSharedPtr<TOtherPointee>& source);
	ConstSharedPtr (const SharedPtr<TPointee>& source);
	template <typename TOtherPointee>
	ConstSharedPtr (const SharedPtr<TOtherPointee>& source);
	template <typename TOtherPointee>
	ConstSharedPtr (ConstSharedPtr<TOtherPointee>&& source);
	ConstSharedPtr (SharedPtr<TPointee>&& source);
	template <typename TOtherPointee>
	ConstSharedPtr (SharedPtr<TOtherPointee>&& source);
	enum IfRefCountNotZeroSelector {
		IfRefCountNotZero
	};
	template <typename TOtherPointee>
	ConstSharedPtr (const TOtherPointee* pointer, IfRefCountNotZeroSelector);

	template<typename OnDeleteT>
	void Clear (OnDeleteT&& onDeleteCallback);

	~ConstSharedPtr ();

	ULong	GetRefCount () const;
	void	Swap (ConstSharedPtr& rhs);

	ConstSharedPtr& operator= (std::nullptr_t);
	template <typename TOtherPointee>
	ConstSharedPtr& operator= (const TOtherPointee* source);
	ConstSharedPtr& operator= (const ConstSharedPtr& source);
	template <typename TOtherPointee>
	ConstSharedPtr& operator= (const ConstSharedPtr<TOtherPointee>& source);
	template <typename TOtherPointee>
	ConstSharedPtr& operator= (ConstSharedPtr<TOtherPointee>&& source);
	template <typename TOtherPointee>
	ConstSharedPtr& operator= (const SharedPtr<TOtherPointee>& source);
	template <typename TOtherPointee>
	ConstSharedPtr& operator= (SharedPtr<TOtherPointee>&& source);

	const Pointee* Get () const;

	const Pointee* operator-> () const;
	const Pointee& operator* () const;

	const Pointee* GetPtr ();
	const Pointee* GetPtr () const;

	bool operator == (std::nullptr_t) const								{ return ptr == nullptr; }
	bool operator != (std::nullptr_t) const								{ return ptr != nullptr; }
	template <typename TOtherPointee>
	bool operator == (const TOtherPointee* rhs) const					{ return ptr == rhs; }
	template <typename TOtherPointee>
	bool operator != (const TOtherPointee* rhs) const					{ return ptr != rhs; }
	template <typename TOtherPointee>
	bool operator == (const ConstSharedPtr<TOtherPointee>& rhs) const	{ return ptr == rhs.ptr; }
	template <typename TOtherPointee>
	bool operator != (const ConstSharedPtr<TOtherPointee>& rhs) const	{ return ptr != rhs.ptr; }
	template <typename TOtherPointee>
	bool operator == (const SharedPtr<TOtherPointee>& rhs) const		{ return ptr == rhs.ptr; }
	template <typename TOtherPointee>
	bool operator != (const SharedPtr<TOtherPointee>& rhs) const		{ return ptr != rhs.ptr; }

	ULong GenerateHashValue () const									{ return GS::CalculateHashValue (ptr); }
};


template <typename TPointee>
ConstSharedPtr<TPointee>::ConstSharedPtr () :
	ptr (nullptr)
{
}


template <typename TPointee>
ConstSharedPtr<TPointee>::ConstSharedPtr (std::nullptr_t) :
	ptr (nullptr)
{
}


template <typename TPointee>
template <typename TOtherPointee>
ConstSharedPtr<TPointee>::ConstSharedPtr (const TOtherPointee* pointer) :
	ptr (pointer)
{
	if (ptr != nullptr)
		ptr->AddRef ();
}


template <typename TPointee>
ConstSharedPtr<TPointee>::ConstSharedPtr (const ConstSharedPtr& source) :
	ptr (source.ptr)
{
	if (ptr != nullptr)
		ptr->AddRef ();
}


template <typename TPointee>
template <typename TOtherPointee>
ConstSharedPtr<TPointee>::ConstSharedPtr (const ConstSharedPtr<TOtherPointee>& source) :
	ptr (source.ptr)
{
	if (ptr != nullptr)
		ptr->AddRef ();
}


template <typename TPointee>
ConstSharedPtr<TPointee>::ConstSharedPtr (const SharedPtr<TPointee>& source) :
	ptr (source.ptr)
{
	if (ptr != nullptr)
		ptr->AddRef ();
}


template <typename TPointee>
template <typename TOtherPointee>
ConstSharedPtr<TPointee>::ConstSharedPtr (const SharedPtr<TOtherPointee>& source) :
	ptr (source.ptr)
{
	if (ptr != nullptr)
		ptr->AddRef ();
}


template <typename TPointee>
template <typename TOtherPointee>
ConstSharedPtr<TPointee>::ConstSharedPtr (ConstSharedPtr<TOtherPointee>&& source) :
	ptr (source.ptr)
{
	source.ptr = nullptr;
}


template <typename TPointee>
ConstSharedPtr<TPointee>::ConstSharedPtr (SharedPtr<TPointee>&& source) :
	ptr (source.ptr)
{
	source.ptr = nullptr;
}


template <typename TPointee>
template <typename TOtherPointee>
ConstSharedPtr<TPointee>::ConstSharedPtr (SharedPtr<TOtherPointee>&& source) :
	ptr (source.ptr)
{
	source.ptr = nullptr;
}


template <typename TPointee>
template <typename TOtherPointee>
ConstSharedPtr<TPointee>::ConstSharedPtr (const TOtherPointee* pointer, IfRefCountNotZeroSelector) : ptr (nullptr)
{
	if (pointer != nullptr && pointer->AddRefIfRefCountNotZero ()) {
		ptr = pointer;
	}
}


template <typename TPointee>
template <typename OnDeleteT>
void ConstSharedPtr<TPointee>::Clear (OnDeleteT&& onDeleteCallback)
{
	const Pointee* prevPtr = ptr;
	ptr = nullptr;

	if (prevPtr != nullptr) {
		prevPtr->template Release<Pointee> (std::forward<OnDeleteT> (onDeleteCallback));
	}
}


template <typename TPointee>
ConstSharedPtr<TPointee>::~ConstSharedPtr ()
{
	if (ptr != nullptr)
		ptr->Release ();
	ptr = nullptr;
}


template <typename TPointee>
ULong ConstSharedPtr<TPointee>::GetRefCount() const
{
	return ptr == nullptr ? 0 : ptr->GetRefCount();
}


template <typename TPointee>
void ConstSharedPtr<TPointee>::Swap (ConstSharedPtr& rhs)
{
	GS::Swap (ptr, rhs.ptr);
}


template <typename TPointee>
ConstSharedPtr<TPointee>& ConstSharedPtr<TPointee>::operator= (std::nullptr_t)
{
	ConstSharedPtr thisTypeNullPtr;
	Swap (thisTypeNullPtr);
	return *this;
}


template <typename TPointee>
template <typename TOtherPointee>
ConstSharedPtr<TPointee>& ConstSharedPtr<TPointee>::operator= (const TOtherPointee* source)
{
	if (ptr != source) {
		ConstSharedPtr thisTypePtr (source);
		Swap (thisTypePtr);
	}
	return *this;
}


template <typename TPointee>
ConstSharedPtr<TPointee>& ConstSharedPtr<TPointee>::operator= (const ConstSharedPtr& source)
{
	if (ptr != source.ptr) {
		ConstSharedPtr thisTypePtr (source);
		Swap (thisTypePtr);
	}
	return *this;
}


template <typename TPointee>
template <typename TOtherPointee>
ConstSharedPtr<TPointee>& ConstSharedPtr<TPointee>::operator= (const ConstSharedPtr<TOtherPointee>& source)
{
	if (ptr != source.ptr) {
		ConstSharedPtr thisTypePtr (source);
		Swap (thisTypePtr);
	}
	return *this;
}


template <typename TPointee>
template <typename TOtherPointee>
ConstSharedPtr<TPointee>& ConstSharedPtr<TPointee>::operator= (ConstSharedPtr<TOtherPointee>&& source)
{
	ConstSharedPtr thisTypePtr (std::move (source));
	Swap (thisTypePtr);
	return *this;
}


template <typename TPointee>
template <typename TOtherPointee>
ConstSharedPtr<TPointee>& ConstSharedPtr<TPointee>::operator= (const SharedPtr<TOtherPointee>& source)
{
	if (ptr != source.ptr) {
		ConstSharedPtr thisTypePtr (source);
		Swap (thisTypePtr);
	}
	return *this;
}


template <typename TPointee>
template <typename TOtherPointee>
ConstSharedPtr<TPointee>& ConstSharedPtr<TPointee>::operator= (SharedPtr<TOtherPointee>&& source)
{
	ConstSharedPtr thisTypePtr (std::move (source));
	Swap (thisTypePtr);
	return *this;
}


template <typename TPointee>
const typename ConstSharedPtr<TPointee>::Pointee* ConstSharedPtr<TPointee>::Get () const
{
	return ptr;
}


template <typename TPointee>
const typename ConstSharedPtr<TPointee>::Pointee* ConstSharedPtr<TPointee>::operator-> () const
{
	return ptr;
}


template <typename TPointee>
const typename ConstSharedPtr<TPointee>::Pointee* ConstSharedPtr<TPointee>::GetPtr ()
{
	return ptr;
}


template <typename TPointee>
const typename ConstSharedPtr<TPointee>::Pointee& ConstSharedPtr<TPointee>::operator* () const
{
	return *ptr;
}


template <typename TPointee>
const typename ConstSharedPtr<TPointee>::Pointee* ConstSharedPtr<TPointee>::GetPtr () const
{
	return ptr;
}


template <typename TPointee>
const ConstSharedPtr<TPointee>& SharedPtr<TPointee>::AsConst () const
{
	return *reinterpret_cast<const ConstSharedPtr<TPointee> *> (this);
}


template <typename ToType, class FromType>
SharedPtr<ToType> StaticCast (const SharedPtr<FromType>& src)
{
	DBASSERT (src == nullptr || dynamic_cast<const ToType*> (src.Get ()) != nullptr);
	return SharedPtr<ToType> (static_cast<ToType*> (src.Get ()));
}


template <typename ToType, class FromType>
ConstSharedPtr<ToType> StaticCast (const ConstSharedPtr<FromType>& src)
{
	DBASSERT (src == nullptr || dynamic_cast<const ToType*> (src.Get ()) != nullptr);
	return ConstSharedPtr<ToType> (static_cast<const ToType*> (src.Get ()));
}


template <typename ToType, class FromType>
SharedPtr<ToType> DynamicCast (const SharedPtr<FromType>& src)
{
	return SharedPtr<ToType> (dynamic_cast<ToType*> (src.Get ()));
}


template <typename ToType, class FromType>
ConstSharedPtr<ToType> DynamicCast (const ConstSharedPtr<FromType>& src)
{
	return ConstSharedPtr<ToType> (dynamic_cast<const ToType*> (src.Get ()));
}


template <typename Type>
SharedPtr<Type> ConstCast (const ConstSharedPtr<Type> src)
{
	return SharedPtr<Type> (const_cast<Type*> (src.Get ()));
}

}		// namespace GS

#endif
