// *********************************************************************************************************************
// Description:		Interface Ref
//
// Module:			ObjectDatabase
// Namespace:		ODB
// Contact person:	MB, BIM
//
// *********************************************************************************************************************


#ifndef ODBIREF_HPP
#define ODBIREF_HPP

#pragma once


#include "ODBReference.hpp"
#include "RawPointerArithmetic.hpp"


namespace ODB {


// === class Imp::StaticCastSelector ===================================================================================

namespace Imp {

class StaticCastSelector {};

}


// === class CommonIRef ================================================================================================

template <class Interface>
class CommonIRef {
protected:
	CommonIRef ();

	template <template <class> class RefOrConstRef, class T>
	static GS::IntPtr		CalculateOffset (const RefOrConstRef<T>& source);

	template <template <class> class IRefOrConstIRef, class I>
	static GS::IntPtr		AdjustOffset (const IRefOrConstIRef<I>& source);

	template <template <class> class IRefOrConstIRef, class I>
	static GS::IntPtr		AdjustOffset (Imp::StaticCastSelector, const IRefOrConstIRef<I>& source);
};


// === CommonIRef methods ==============================================================================================


template <class Interface>
CommonIRef<Interface>::CommonIRef ()
{
	static_assert (GS::IsClass<Interface>, "'Interface' should be a class type.");
	static_assert (!IsObject<Interface>, "'Interface' is derived from ODB::Object. You should use ODB::Ref instead of ODB::IRef.");
}


template <class Interface>
template <template <class> class RefOrConstRef, class T>
GS::IntPtr	CommonIRef<Interface>::CalculateOffset (const RefOrConstRef<T>& source)
{
	static_assert (IsObject<T>, "'T' is not derived from ODB::Object.");
	static_assert (GS::IsCompatible<T, Interface>, "'T' is not derived from 'Interface'.");

	const Object*	 objectPointer    = source.GetConstMemoryAddress ();
	const Interface* interfacePointer = static_cast<const T*> (objectPointer);

	return GS::GetRawDifference (objectPointer, interfacePointer);
}


template <class Interface>
template <template <class> class IRefOrConstIRef, class I>
GS::IntPtr	CommonIRef<Interface>::AdjustOffset (const IRefOrConstIRef<I>& source)
{
	static_assert (GS::IsCompatible<I, Interface>, "'I' is not derived from 'Interface'.");

	const I*		 i                = GS::AddRawOffset<I> (source.ref.GetConstMemoryAddress (), source.offset);
	const Interface* interfacePointer = i;

	return source.offset + GS::GetRawDifference (i, interfacePointer);
}


template <class Interface>
template <template <class> class IRefOrConstIRef, class I>
GS::IntPtr	CommonIRef<Interface>::AdjustOffset (Imp::StaticCastSelector, const IRefOrConstIRef<I>& source)
{
	static_assert (!GS::IsCompatible<I, Interface>, "'Interface' is base of 'I'. No need to cast.");
	static_assert (GS::IsCompatible<Interface, I>, "Use ODB::DynamicCast () for unrelated types.");

	const I*		 i                = GS::AddRawOffset<I> (source.ref.GetConstMemoryAddress (), source.offset);
	const Interface* interfacePointer = static_cast<const Interface*> (i);

	DBASSERT (i == nullptr || dynamic_cast<const Interface*> (i) != nullptr);

	return source.offset + GS::GetRawDifference (i, interfacePointer);
}


// === IRef forward declarations =======================================================================================

template <class Interface> class IRef;
template <class Interface> class ConstIRef;

template <class Interface>							bool operator== (const IRef<Interface>& leftOp,		  std::nullptr_t);
template <class Interface>							bool operator== (const IRef<Interface>& leftOp,		  const IRef<Interface>& rightOp);
template <class Interface1, class Interface2>		bool operator== (const IRef<Interface1>& leftOp,	  const IRef<Interface2>& rightOp);
template <class Interface1, class Interface2>		bool operator== (const IRef<Interface1>& leftOp,	  const ConstIRef<Interface2>& rightOp);
template <class Interface1, class Interface2>		bool operator== (const ConstIRef<Interface1>& leftOp, const IRef<Interface2>& rightOp);
template <class Interface, class T>					bool operator== (const IRef<Interface>& leftOp,		  const Ref<T>& rightOp);
template <class Interface, class T>					bool operator== (const Ref<T>& leftOp,				  const IRef<Interface>& rightOp);
template <class Interface, class T>					bool operator== (const IRef<Interface>& leftOp,		  const ConstRef<T>& rightOp);
template <class Interface, class T>					bool operator== (const ConstRef<T>& leftOp,			  const IRef<Interface>& rightOp);

template <class Interface>							bool operator!= (const IRef<Interface>& leftOp,		  std::nullptr_t);
template <class Interface>							bool operator!= (const IRef<Interface>& leftOp,		  const IRef<Interface>& rightOp);
template <class Interface1, class Interface2>		bool operator!= (const IRef<Interface1>& leftOp,	  const IRef<Interface2>& rightOp);
template <class Interface1, class Interface2>		bool operator!= (const IRef<Interface1>& leftOp,	  const ConstIRef<Interface2>& rightOp);
template <class Interface1, class Interface2>		bool operator!= (const ConstIRef<Interface1>& leftOp, const IRef<Interface2>& rightOp);
template <class Interface, class T>					bool operator!= (const IRef<Interface>& leftOp,		  const Ref<T>& rightOp);
template <class Interface, class T>					bool operator!= (const Ref<T>& leftOp,				  const IRef<Interface>& rightOp);
template <class Interface, class T>					bool operator!= (const IRef<Interface>& leftOp,		  const ConstRef<T>& rightOp);
template <class Interface, class T>					bool operator!= (const ConstRef<T>& leftOp,			  const IRef<Interface>& rightOp);


// === class IRef ======================================================================================================

template <class Interface>
class IRef final : private CommonIRef<Interface> {
private:
	GS::IntPtr			offset = 0;				// must come first because of move constructor and move operator=
	Ref<Object>			ref;

	template <class I>							friend class CommonIRef;
	template <class I>							friend class IRef;
	template <class I>							friend class ConstIRef;
	template <class U1, class U2, class Choice>	friend class Imp::CastDispatcher;

	friend bool operator==<Interface> (const IRef& leftOp, std::nullptr_t);
	friend bool operator==<Interface> (const IRef& leftOp, const IRef& rightOp);
	template <class I1, class I2> friend bool	operator== (const IRef<I1>& leftOp,      const IRef<I2>& rightOp);
	template <class I1, class I2> friend bool	operator== (const IRef<I1>& leftOp,      const ConstIRef<I2>& rightOp);
	template <class I1, class I2> friend bool	operator== (const ConstIRef<I1>& leftOp, const IRef<I2>& rightOp);
	template <class I, class T>	  friend bool	operator== (const IRef<I>& leftOp,       const Ref<T>& rightOp);
	template <class I, class T>	  friend bool	operator== (const Ref<T>& leftOp,        const IRef<I>& rightOp);
	template <class I, class T>	  friend bool	operator== (const IRef<I>& leftOp,       const ConstRef<T>& rightOp);
	template <class I, class T>	  friend bool	operator== (const ConstRef<T>& leftOp,   const IRef<I>& rightOp);

	friend bool operator!=<Interface> (const IRef& leftOp, std::nullptr_t);
	friend bool operator!=<Interface> (const IRef& leftOp, const IRef& rightOp);
	template <class I1, class I2> friend bool	operator!= (const IRef<I1>& leftOp,      const IRef<I2>& rightOp);
	template <class I1, class I2> friend bool	operator!= (const IRef<I1>& leftOp,      const ConstIRef<I2>& rightOp);
	template <class I1, class I2> friend bool	operator!= (const ConstIRef<I1>& leftOp, const IRef<I2>& rightOp);
	template <class I, class T>	  friend bool	operator!= (const IRef<I>& leftOp,       const Ref<T>& rightOp);
	template <class I, class T>	  friend bool	operator!= (const Ref<T>& leftOp,        const IRef<I>& rightOp);
	template <class I, class T>	  friend bool	operator!= (const IRef<I>& leftOp,       const ConstRef<T>& rightOp);
	template <class I, class T>	  friend bool	operator!= (const ConstRef<T>& leftOp,   const IRef<I>& rightOp);

	using CommonIRef<Interface>::CalculateOffset;
	using CommonIRef<Interface>::AdjustOffset;

	template <class I>	IRef (Imp::StaticCastSelector, const IRef<I>& source);
	template <class I>	IRef (Imp::StaticCastSelector, IRef<I>&& source);
	IRef (GS::IntPtr offset, const Ref<Object>& ref);
	IRef (GS::IntPtr offset, Ref<Object>&& ref);

public:
	IRef ();
	IRef (std::nullptr_t);
	IRef (const IRef& source);
	IRef (IRef&& source);
	template <class I>	IRef (const IRef<I>& source);
	template <class I>	IRef (IRef<I>&& source);
	template <class T>	IRef (const Ref<T>& source);
	template <class T>	IRef (Ref<T>&& source);

	IRef&						operator= (std::nullptr_t);
	IRef&						operator= (const IRef& source);
	IRef&						operator= (IRef&& source);
	template <class I>	IRef&	operator= (const IRef<I>& source);
	template <class I>	IRef&	operator= (IRef<I>&& source);
	template <class T>	IRef&	operator= (const Ref<T>& source);
	template <class T>	IRef&	operator= (Ref<T>&& source);

	const Interface*			operator-> () const;
	const Interface&			operator*  () const;
	Interface*					operator() () const;
	Interface*					operator() (LogicalConstSelector) const;
	Interface*					operator() (ModificationAuthorizationControl control) const;

	Interface*					ToPtr	   () const;
	const Interface*			ToConstPtr () const;
	const Ref<Object>&			ToRef	   () const;
	const ConstRef<Object>&		ToConstRef () const;

	const ConstIRef<Interface>&	AsConst	   () const;

	operator const Ref<Object>&		 () const;
	operator const ConstRef<Object>& () const;

	ULong	GenerateHashValue () const;
};


// === IRef methods ====================================================================================================

template <class Interface>
IRef<Interface>::IRef ()
{
}


template <class Interface>
IRef<Interface>::IRef (std::nullptr_t)
{
}


template <class Interface>
IRef<Interface>::IRef (const IRef& source) :
	offset (source.offset),
	ref	   (source.ref)
{
}


template <class Interface>
IRef<Interface>::IRef (IRef&& source) :
	offset (source.offset),
	ref	   (std::move (source.ref))
{
}


template <class Interface>
template <class I>
IRef<Interface>::IRef (const IRef<I>& source) :
	offset (AdjustOffset (source)),
	ref	   (source.ref)
{
}


template <class Interface>
template <class I>
IRef<Interface>::IRef (IRef<I>&& source) :
	offset (AdjustOffset (source)),
	ref	   (std::move (source.ref))
{
}


template <class Interface>
template <class T>
IRef<Interface>::IRef (const Ref<T>& source) :
	offset (CalculateOffset (source)),
	ref	   (source)
{
}


template <class Interface>
template <class T>
IRef<Interface>::IRef (Ref<T>&& source) :
	offset (CalculateOffset (source)),
	ref	   (std::move (source))
{
}


template <class Interface>
template <class I>
IRef<Interface>::IRef (Imp::StaticCastSelector, const IRef<I>& source) :
	offset (AdjustOffset (Imp::StaticCastSelector (), source)),
	ref	   (source.ref)
{
}


template <class Interface>
template <class I>
IRef<Interface>::IRef (Imp::StaticCastSelector, IRef<I>&& source) :
	offset (AdjustOffset (Imp::StaticCastSelector (), source)),
	ref	   (std::move (source.ref))
{
}


template <class Interface>
IRef<Interface>::IRef (GS::IntPtr offset, const Ref<Object>& ref) :
	offset (offset),
	ref	   (ref)
{
}


template <class Interface>
IRef<Interface>::IRef (GS::IntPtr offset, Ref<Object>&& ref) :
	offset (offset),
	ref	   (std::move (ref))
{
}


template <class Interface>
IRef<Interface>&	IRef<Interface>::operator= (std::nullptr_t)
{
	offset = 0;
	ref	   = nullptr;

	return *this;
}


template <class Interface>
IRef<Interface>&	IRef<Interface>::operator= (const IRef& source)
{
	offset = source.offset;
	ref	   = source.ref;

	return *this;
}


template <class Interface>
IRef<Interface>&	IRef<Interface>::operator= (IRef&& source)
{
	offset = source.offset;
	ref	   = std::move (source.ref);

	return *this;
}


template <class Interface>
template <class I>
IRef<Interface>&	IRef<Interface>::operator= (const IRef<I>& source)
{
	offset = AdjustOffset (source);
	ref	   = source.ref;

	return *this;
}


template <class Interface>
template <class I>
IRef<Interface>&	IRef<Interface>::operator= (IRef<I>&& source)
{
	offset = AdjustOffset (source);
	ref	   = std::move (source.ref);

	return *this;
}


template <class Interface>
template <class T>
IRef<Interface>&	IRef<Interface>::operator= (const Ref<T>& source)
{
	offset = CalculateOffset (source);
	ref	   = source;

	return *this;
}


template <class Interface>
template <class T>
IRef<Interface>&	IRef<Interface>::operator= (Ref<T>&& source)
{
	offset = CalculateOffset (source);
	ref	   = std::move (source);

	return *this;
}


template <class Interface>
const Interface*	IRef<Interface>::operator-> () const
{
	return GS::AddRawOffset<Interface> (ref.operator-> (), offset);
}


template <class Interface>
const Interface&	IRef<Interface>::operator* () const
{
	return *GS::AddRawOffset<Interface> (std::addressof (*ref), offset);
}


template <class Interface>
Interface*	IRef<Interface>::operator() () const
{
	return GS::AddRawOffset<Interface> (ref(), offset);
}


template <class Interface>
Interface*	IRef<Interface>::operator() (LogicalConstSelector) const
{
	return GS::AddRawOffset<Interface> (ref(LogicalConst), offset);
}


template <class Interface>
Interface*	IRef<Interface>::operator() (ModificationAuthorizationControl control) const
{
	return GS::AddRawOffset<Interface> (ref(control), offset);
}


template <class Interface>
Interface*	IRef<Interface>::ToPtr () const
{
	return GS::AddRawOffset<Interface> (ref.ToPtr (), offset);
}


template <class Interface>
const Interface*	IRef<Interface>::ToConstPtr () const
{
	return GS::AddRawOffset<Interface> (ref.ToConstPtr (), offset);
}


template <class Interface>
const Ref<Object>&		IRef<Interface>::ToRef () const
{
	return ref;
}


template <class Interface>
const ConstRef<Object>&		IRef<Interface>::ToConstRef () const
{
	return ref.AsConst ();
}


template <class Interface>
const ConstIRef<Interface>&		IRef<Interface>::AsConst () const
{
	return reinterpret_cast<const ConstIRef<Interface>&> (*this);
}


template <class Interface>
IRef<Interface>::operator const Ref<Object>& () const
{
	return ref;
}


template <class Interface>
IRef<Interface>::operator const ConstRef<Object>& () const
{
	return ref.AsConst ();
}


template <class Interface>
ULong	IRef<Interface>::GenerateHashValue () const
{
	return GS::CalculateHashValue (ref);
}


// === IRef global functions ===========================================================================================

template <class Interface>
bool	operator== (const IRef<Interface>& leftOp, std::nullptr_t)
{
	return leftOp.ref == nullptr;
}


template <class Interface>
bool	operator== (const IRef<Interface>& leftOp, const IRef<Interface>& rightOp)
{
	return leftOp.ref == rightOp.ref;
}


template <class Interface1, class Interface2>
bool	operator== (const IRef<Interface1>& leftOp, const IRef<Interface2>& rightOp)
{
	return leftOp.ref == rightOp.ref;
}


template <class Interface, class T>
bool	operator== (const IRef<Interface>& leftOp, const Ref<T>& rightOp)
{
	return leftOp.ref == rightOp;
}


template <class Interface, class T>
bool	operator== (const Ref<T>& leftOp, const IRef<Interface>& rightOp)
{
	return leftOp == rightOp.ref;
}


template <class Interface, class T>
bool	operator== (const IRef<Interface>& leftOp, const ConstRef<T>& rightOp)
{
	return leftOp.ref == rightOp;
}


template <class Interface, class T>
bool	operator== (const ConstRef<T>& leftOp, const IRef<Interface>& rightOp)
{
	return leftOp == rightOp.ref;
}


template <class Interface>
bool	operator!= (const IRef<Interface>& leftOp, std::nullptr_t)
{
	return leftOp.ref != nullptr;
}


template <class Interface>
bool	operator!= (const IRef<Interface>& leftOp, const IRef<Interface>& rightOp)
{
	return leftOp.ref != rightOp.ref;
}


template <class Interface1, class Interface2>
bool	operator!= (const IRef<Interface1>& leftOp, const IRef<Interface2>& rightOp)
{
	return leftOp.ref != rightOp.ref;
}


template <class Interface, class T>
bool	operator!= (const IRef<Interface>& leftOp, const Ref<T>& rightOp)
{
	return leftOp.ref != rightOp;
}


template <class Interface, class T>
bool	operator!= (const Ref<T>& leftOp, const IRef<Interface>& rightOp)
{
	return leftOp != rightOp.ref;
}


template <class Interface, class T>
bool	operator!= (const IRef<Interface>& leftOp, const ConstRef<T>& rightOp)
{
	return leftOp.ref != rightOp;
}


template <class Interface, class T>
bool	operator!= (const ConstRef<T>& leftOp, const IRef<Interface>& rightOp)
{
	return leftOp != rightOp.ref;
}


// === ConstIRef forward declarations ==================================================================================


template <class Interface>							bool operator== (const ConstIRef<Interface>& leftOp,  std::nullptr_t);
template <class Interface>							bool operator== (const ConstIRef<Interface>& leftOp,  const ConstIRef<Interface>& rightOp);
template <class Interface1, class Interface2>		bool operator== (const ConstIRef<Interface1>& leftOp, const ConstIRef<Interface2>& rightOp);
template <class Interface1, class Interface2>		bool operator== (const ConstIRef<Interface1>& leftOp, const IRef<Interface2>& rightOp);
template <class Interface1, class Interface2>		bool operator== (const IRef<Interface1>& leftOp,	  const ConstIRef<Interface2>& rightOp);
template <class Interface, class T>					bool operator== (const ConstIRef<Interface>& leftOp,  const Ref<T>& rightOp);
template <class Interface, class T>					bool operator== (const Ref<T>& leftOp,				  const ConstIRef<Interface>& rightOp);
template <class Interface, class T>					bool operator== (const ConstIRef<Interface>& leftOp,  const ConstRef<T>& rightOp);
template <class Interface, class T>					bool operator== (const ConstRef<T>& leftOp,			  const ConstIRef<Interface>& rightOp);

template <class Interface>							bool operator!= (const ConstIRef<Interface>& leftOp,  std::nullptr_t);
template <class Interface>							bool operator!= (const ConstIRef<Interface>& leftOp,  const ConstIRef<Interface>& rightOp);
template <class Interface1, class Interface2>		bool operator!= (const ConstIRef<Interface1>& leftOp, const ConstIRef<Interface2>& rightOp);
template <class Interface1, class Interface2>		bool operator!= (const ConstIRef<Interface1>& leftOp, const IRef<Interface2>& rightOp);
template <class Interface1, class Interface2>		bool operator!= (const IRef<Interface1>& leftOp,	  const ConstIRef<Interface2>& rightOp);
template <class Interface, class T>					bool operator!= (const ConstIRef<Interface>& leftOp,  const Ref<T>& rightOp);
template <class Interface, class T>					bool operator!= (const Ref<T>& leftOp,				  const ConstIRef<Interface>& rightOp);
template <class Interface, class T>					bool operator!= (const ConstIRef<Interface>& leftOp,  const ConstRef<T>& rightOp);
template <class Interface, class T>					bool operator!= (const ConstRef<T>& leftOp,			  const ConstIRef<Interface>& rightOp);


// === class ConstIRef =================================================================================================

template <class Interface>
class ConstIRef final : private CommonIRef<Interface> {
private:
	GS::IntPtr			offset = 0;				// must come first because of move constructor and move operator=
	ConstRef<Object>	ref;

	template <class I>							friend class CommonIRef;
	template <class I>							friend class ConstIRef;
	template <class U1, class U2, class Choice>	friend class Imp::CastDispatcher;

	friend bool operator==<Interface> (const ConstIRef& leftOp, std::nullptr_t);
	friend bool operator==<Interface> (const ConstIRef& leftOp, const ConstIRef& rightOp);
	template <class I1, class I2> friend bool	operator== (const ConstIRef<I1>& leftOp, const ConstIRef<I2>& rightOp);
	template <class I1, class I2> friend bool	operator== (const ConstIRef<I1>& leftOp, const IRef<I2>& rightOp);
	template <class I1, class I2> friend bool	operator== (const IRef<I1>& leftOp,      const ConstIRef<I2>& rightOp);
	template <class I, class T>	  friend bool	operator== (const ConstIRef<I>& leftOp,  const Ref<T>& rightOp);
	template <class I, class T>	  friend bool	operator== (const Ref<T>& leftOp,        const ConstIRef<I>& rightOp);
	template <class I, class T>	  friend bool	operator== (const ConstIRef<I>& leftOp,  const ConstRef<T>& rightOp);
	template <class I, class T>	  friend bool	operator== (const ConstRef<T>& leftOp,   const ConstIRef<I>& rightOp);

	friend bool operator!=<Interface> (const ConstIRef& leftOp, std::nullptr_t);
	friend bool operator!=<Interface> (const ConstIRef& leftOp, const ConstIRef& rightOp);
	template <class I1, class I2> friend bool	operator!= (const ConstIRef<I1>& leftOp, const ConstIRef<I2>& rightOp);
	template <class I1, class I2> friend bool	operator!= (const ConstIRef<I1>& leftOp, const IRef<I2>& rightOp);
	template <class I1, class I2> friend bool	operator!= (const IRef<I1>& leftOp,      const ConstIRef<I2>& rightOp);
	template <class I, class T>	  friend bool	operator!= (const ConstIRef<I>& leftOp,  const Ref<T>& rightOp);
	template <class I, class T>	  friend bool	operator!= (const Ref<T>& leftOp,        const ConstIRef<I>& rightOp);
	template <class I, class T>	  friend bool	operator!= (const ConstIRef<I>& leftOp,  const ConstRef<T>& rightOp);
	template <class I, class T>	  friend bool	operator!= (const ConstRef<T>& leftOp,   const ConstIRef<I>& rightOp);

	using CommonIRef<Interface>::CalculateOffset;
	using CommonIRef<Interface>::AdjustOffset;

	template <class I>	ConstIRef (Imp::StaticCastSelector, const ConstIRef<I>& source);
	template <class I>	ConstIRef (Imp::StaticCastSelector, ConstIRef<I>&& source);
	ConstIRef (GS::IntPtr offset, const ConstRef<Object>& ref);
	ConstIRef (GS::IntPtr offset, ConstRef<Object>&& ref);

public:
	ConstIRef ();
	ConstIRef (std::nullptr_t);
	ConstIRef (const IRef<Interface>& source);
	ConstIRef (IRef<Interface>&& source);
	ConstIRef (const ConstIRef& source);
	ConstIRef (ConstIRef&& source);
	template <class I>	ConstIRef (const IRef<I>& source);
	template <class I>	ConstIRef (IRef<I>&& source);
	template <class I>	ConstIRef (const ConstIRef<I>& source);
	template <class I>	ConstIRef (ConstIRef<I>&& source);
	template <class T>	ConstIRef (const Ref<T>& source);
	template <class T>	ConstIRef (Ref<T>&& source);
	template <class T>	ConstIRef (const ConstRef<T>& source);
	template <class T>	ConstIRef (ConstRef<T>&& source);

	ConstIRef&						operator= (std::nullptr_t);
	ConstIRef&						operator= (const IRef<Interface>& source);
	ConstIRef&						operator= (IRef<Interface>&& source);
	ConstIRef&						operator= (const ConstIRef& source);
	ConstIRef&						operator= (ConstIRef&& source);
	template <class I>	ConstIRef&	operator= (const IRef<I>& source);
	template <class I>	ConstIRef&	operator= (IRef<I>&& source);
	template <class I>	ConstIRef&	operator= (const ConstIRef<I>& source);
	template <class I>	ConstIRef&	operator= (ConstIRef<I>&& source);
	template <class T>	ConstIRef&	operator= (const Ref<T>& source);
	template <class T>	ConstIRef&	operator= (Ref<T>&& source);
	template <class T>	ConstIRef&	operator= (const ConstRef<T>& source);
	template <class T>	ConstIRef&	operator= (ConstRef<T>&& source);

	const Interface*				operator-> () const;
	const Interface&				operator*  () const;

	const Interface*				ToPtr	   () const;
	const ConstRef<Object>&			ToRef	   () const;

	operator const ConstRef<Object>& () const;

	ULong	GenerateHashValue () const;
};


// === ConstIRef methods ===============================================================================================

template <class Interface>
ConstIRef<Interface>::ConstIRef ()
{
}


template <class Interface>
ConstIRef<Interface>::ConstIRef (std::nullptr_t)
{
}


template <class Interface>
ConstIRef<Interface>::ConstIRef (const IRef<Interface>& source) :
	offset (source.offset),
	ref	   (source.ref)
{
}


template <class Interface>
ConstIRef<Interface>::ConstIRef (IRef<Interface>&& source) :
	offset (source.offset),
	ref	   (std::move (source.ref))
{
}


template <class Interface>
ConstIRef<Interface>::ConstIRef (const ConstIRef& source) :
	offset (source.offset),
	ref	   (source.ref)
{
}


template <class Interface>
ConstIRef<Interface>::ConstIRef (ConstIRef&& source) :
	offset (source.offset),
	ref	   (std::move (source.ref))
{
}


template <class Interface>
template <class I>
ConstIRef<Interface>::ConstIRef (const IRef<I>& source) :
	offset (AdjustOffset (source)),
	ref	   (source.ref)
{
}


template <class Interface>
template <class I>
ConstIRef<Interface>::ConstIRef (IRef<I>&& source) :
	offset (AdjustOffset (source)),
	ref	   (std::move (source.ref))
{
}


template <class Interface>
template <class I>
ConstIRef<Interface>::ConstIRef (const ConstIRef<I>& source) :
	offset (AdjustOffset (source)),
	ref	   (source.ref)
{
}


template <class Interface>
template <class I>
ConstIRef<Interface>::ConstIRef (ConstIRef<I>&& source) :
	offset (AdjustOffset (source)),
	ref	   (std::move (source.ref))
{
}


template <class Interface>
template <class T>
ConstIRef<Interface>::ConstIRef (const Ref<T>& source) :
	offset (CalculateOffset (source)),
	ref	   (source)
{
}


template <class Interface>
template <class T>
ConstIRef<Interface>::ConstIRef (Ref<T>&& source) :
	offset (CalculateOffset (source)),
	ref	   (std::move (source))
{
}


template <class Interface>
template <class T>
ConstIRef<Interface>::ConstIRef (const ConstRef<T>& source) :
	offset (CalculateOffset (source)),
	ref	   (source)
{
}


template <class Interface>
template <class T>
ConstIRef<Interface>::ConstIRef (ConstRef<T>&& source) :
	offset (CalculateOffset (source)),
	ref	   (std::move (source))
{
}


template <class Interface>
template <class I>
ConstIRef<Interface>::ConstIRef (Imp::StaticCastSelector, const ConstIRef<I>& source) :
	offset (AdjustOffset (Imp::StaticCastSelector (), source)),
	ref	   (source.ref)
{
}


template <class Interface>
template <class I>
ConstIRef<Interface>::ConstIRef (Imp::StaticCastSelector, ConstIRef<I>&& source) :
	offset (AdjustOffset (Imp::StaticCastSelector (), source)),
	ref	   (std::move (source.ref))
{
}


template <class Interface>
ConstIRef<Interface>::ConstIRef (GS::IntPtr offset, const ConstRef<Object>& ref) :
	offset (offset),
	ref	   (ref)
{
}


template <class Interface>
ConstIRef<Interface>::ConstIRef (GS::IntPtr offset, ConstRef<Object>&& ref) :
	offset (offset),
	ref	   (std::move (ref))
{
}


template <class Interface>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (std::nullptr_t)
{
	offset = 0;
	ref	   = nullptr;

	return *this;
}


template <class Interface>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (const IRef<Interface>& source)
{
	offset = source.offset;
	ref	   = source.ref;

	return *this;
}


template <class Interface>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (IRef<Interface>&& source)
{
	offset = source.offset;
	ref	   = std::move (source.ref);

	return *this;
}


template <class Interface>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (const ConstIRef& source)
{
	offset = source.offset;
	ref	   = source.ref;

	return *this;
}


template <class Interface>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (ConstIRef&& source)
{
	offset = source.offset;
	ref	   = std::move (source.ref);

	return *this;
}


template <class Interface>
template <class I>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (const IRef<I>& source)
{
	offset = AdjustOffset (source);
	ref	   = source.ref;

	return *this;
}


template <class Interface>
template <class I>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (IRef<I>&& source)
{
	offset = AdjustOffset (source);
	ref	   = std::move (source.ref);

	return *this;
}


template <class Interface>
template <class I>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (const ConstIRef<I>& source)
{
	offset = AdjustOffset (source);
	ref	   = source.ref;

	return *this;
}


template <class Interface>
template <class I>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (ConstIRef<I>&& source)
{
	offset = AdjustOffset (source);
	ref	   = std::move (source.ref);

	return *this;
}


template <class Interface>
template <class T>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (const Ref<T>& source)
{
	offset = CalculateOffset (source);
	ref	   = source;

	return *this;
}


template <class Interface>
template <class T>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (Ref<T>&& source)
{
	offset = CalculateOffset (source);
	ref	   = std::move (source);

	return *this;
}


template <class Interface>
template <class T>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (const ConstRef<T>& source)
{
	offset = CalculateOffset (source);
	ref	   = source;

	return *this;
}


template <class Interface>
template <class T>
ConstIRef<Interface>&	ConstIRef<Interface>::operator= (ConstRef<T>&& source)
{
	offset = CalculateOffset (source);
	ref	   = std::move (source);

	return *this;
}


template <class Interface>
const Interface*	ConstIRef<Interface>::operator-> () const
{
	return GS::AddRawOffset<Interface> (ref.operator-> (), offset);
}


template <class Interface>
const Interface&	ConstIRef<Interface>::operator* () const
{
	return *GS::AddRawOffset<Interface> (std::addressof (*ref), offset);
}


template <class Interface>
const Interface*	ConstIRef<Interface>::ToPtr () const
{
	return GS::AddRawOffset<Interface> (ref.ToPtr (), offset);
}


template <class Interface>
const ConstRef<Object>&		ConstIRef<Interface>::ToRef () const
{
	return ref;
}


template <class Interface>
ConstIRef<Interface>::operator const ConstRef<Object>& () const
{
	return ref;
}


template <class Interface>
ULong	ConstIRef<Interface>::GenerateHashValue () const
{
	return GS::CalculateHashValue (ref);
}


// === ConstIRef global functions ======================================================================================

template <class Interface>
bool	operator== (const ConstIRef<Interface>& leftOp, std::nullptr_t)
{
	return leftOp.ref == nullptr;
}


template <class Interface>
bool	operator== (const ConstIRef<Interface>& leftOp, const ConstIRef<Interface>& rightOp)
{
	return leftOp.ref == rightOp.ref;
}


template <class Interface1, class Interface2>
bool	operator== (const ConstIRef<Interface1>& leftOp, const ConstIRef<Interface2>& rightOp)
{
	return leftOp.ref == rightOp.ref;
}


template <class Interface1, class Interface2>
bool	operator== (const ConstIRef<Interface1>& leftOp, const IRef<Interface2>& rightOp)
{
	return leftOp.ref == rightOp.ref;
}


template <class Interface1, class Interface2>
bool	operator== (const IRef<Interface1>& leftOp, const ConstIRef<Interface2>& rightOp)
{
	return leftOp.ref == rightOp.ref;
}


template <class Interface, class T>
bool	operator== (const ConstIRef<Interface>& leftOp, const Ref<T>& rightOp)
{
	return leftOp.ref == rightOp;
}


template <class Interface, class T>
bool	operator== (const Ref<T>& leftOp, const ConstIRef<Interface>& rightOp)
{
	return leftOp == rightOp.ref;
}


template <class Interface, class T>
bool	operator== (const ConstIRef<Interface>& leftOp, const ConstRef<T>& rightOp)
{
	return leftOp.ref == rightOp;
}


template <class Interface, class T>
bool	operator== (const ConstRef<T>& leftOp, const ConstIRef<Interface>& rightOp)
{
	return leftOp == rightOp.ref;
}


template <class Interface>
bool	operator!= (const ConstIRef<Interface>& leftOp, std::nullptr_t)
{
	return leftOp.ref != nullptr;
}


template <class Interface>
bool	operator!= (const ConstIRef<Interface>& leftOp, const ConstIRef<Interface>& rightOp)
{
	return leftOp.ref != rightOp.ref;
}


template <class Interface1, class Interface2>
bool	operator!= (const ConstIRef<Interface1>& leftOp, const ConstIRef<Interface2>& rightOp)
{
	return leftOp.ref != rightOp.ref;
}


template <class Interface1, class Interface2>
bool	operator!= (const ConstIRef<Interface1>& leftOp, const IRef<Interface2>& rightOp)
{
	return leftOp.ref != rightOp.ref;
}


template <class Interface1, class Interface2>
bool	operator!= (const IRef<Interface1>& leftOp, const ConstIRef<Interface2>& rightOp)
{
	return leftOp.ref != rightOp.ref;
}


template <class Interface, class T>
bool	operator!= (const ConstIRef<Interface>& leftOp, const Ref<T>& rightOp)
{
	return leftOp.ref != rightOp;
}


template <class Interface, class T>
bool	operator!= (const Ref<T>& leftOp, const ConstIRef<Interface>& rightOp)
{
	return leftOp != rightOp.ref;
}


template <class Interface, class T>
bool	operator!= (const ConstIRef<Interface>& leftOp, const ConstRef<T>& rightOp)
{
	return leftOp.ref != rightOp;
}


template <class Interface, class T>
bool	operator!= (const ConstRef<T>& leftOp, const ConstIRef<Interface>& rightOp)
{
	return leftOp != rightOp.ref;
}


// === casting =========================================================================================================

namespace Imp {


template <class I>
constexpr bool	IsInterface = GS::IsClass<I> && !IsObject<I>;


template <class ToInterface, class FromInterface>
class CastDispatcher<ToInterface, FromInterface, EnableIf<IsInterface<ToInterface> && IsInterface<FromInterface>>> {
public:
	static IRef<ToInterface>	StaticCast (const IRef<FromInterface>& fromIRef)
	{
		return IRef<ToInterface> (Imp::StaticCastSelector (), fromIRef);
	}


	static IRef<ToInterface>	StaticCast (IRef<FromInterface>&& fromIRef)
	{
		return IRef<ToInterface> (Imp::StaticCastSelector (), std::move (fromIRef));
	}


	static ConstIRef<ToInterface>	StaticCast (const ConstIRef<FromInterface>& fromIRef)
	{
		return ConstIRef<ToInterface> (Imp::StaticCastSelector (), fromIRef);
	}


	static ConstIRef<ToInterface>	StaticCast (ConstIRef<FromInterface>&& fromIRef)
	{
		return ConstIRef<ToInterface> (Imp::StaticCastSelector (), std::move (fromIRef));
	}


	static IRef<ToInterface>		DynamicCast (const IRef<FromInterface>& fromIRef)
	{
		static_assert (!GS::IsCompatible<FromInterface, ToInterface>, "'ToInterface' is base of 'FromInterface'. No need to cast.");

		const Object*		objectPointer = fromIRef.ref.GetConstMemoryAddress ();
		const ToInterface*	toPointer     = dynamic_cast<const ToInterface*> (objectPointer);

		if (toPointer == nullptr)
			return nullptr;
		else
			return IRef<ToInterface> (GS::GetRawDifference (objectPointer, toPointer), fromIRef.ref);
	}


	static IRef<ToInterface>		DynamicCast (IRef<FromInterface>&& fromIRef)
	{
		static_assert (!GS::IsCompatible<FromInterface, ToInterface>, "'ToInterface' is base of 'FromInterface'. No need to cast.");

		const Object*		objectPointer = fromIRef.ref.GetConstMemoryAddress ();
		const ToInterface*	toPointer     = dynamic_cast<const ToInterface*> (objectPointer);

		if (toPointer == nullptr)
			return nullptr;
		else
			return IRef<ToInterface> (GS::GetRawDifference (objectPointer, toPointer), std::move (fromIRef.ref));
	}


	static ConstIRef<ToInterface>		DynamicCast (const ConstIRef<FromInterface>& fromIRef)
	{
		static_assert (!GS::IsCompatible<FromInterface, ToInterface>, "'ToInterface' is base of 'FromInterface'. No need to cast.");

		const Object*		objectPointer = fromIRef.ref.GetConstMemoryAddress ();
		const ToInterface*	toPointer     = dynamic_cast<const ToInterface*> (objectPointer);

		if (toPointer == nullptr)
			return nullptr;
		else
			return ConstIRef<ToInterface> (GS::GetRawDifference (objectPointer, toPointer), fromIRef.ref);
	}


	static ConstIRef<ToInterface>		DynamicCast (ConstIRef<FromInterface>&& fromIRef)
	{
		static_assert (!GS::IsCompatible<FromInterface, ToInterface>, "'ToInterface' is base of 'FromInterface'. No need to cast.");

		const Object*		objectPointer = fromIRef.ref.GetConstMemoryAddress ();
		const ToInterface*	toPointer     = dynamic_cast<const ToInterface*> (objectPointer);

		if (toPointer == nullptr)
			return nullptr;
		else
			return ConstIRef<ToInterface> (GS::GetRawDifference (objectPointer, toPointer), std::move (fromIRef.ref));
	}


	static bool		IsType (const IRef<FromInterface>& fromIRef)
	{
		return DynamicCast (fromIRef) != nullptr;
	}


	static bool		IsType (const ConstIRef<FromInterface>& fromIRef)
	{
		return DynamicCast (fromIRef) != nullptr;
	}
};


template <class ToInterface, class FromType>
class CastDispatcher<ToInterface, FromType, EnableIf<IsInterface<ToInterface> && IsObject<FromType>>> {
public:
	static IRef<ToInterface>		StaticCast (const Ref<FromType>& /*fromRef*/)
	{
		static_assert (!GS::IsCompatible<FromType, ToInterface>, "'ToInterface' is base of 'FromType'. No need to cast.");
		static_assert (GS::AreRelated<FromType, ToInterface>, "Use ODB::DynamicCast () for unrelated types.");
		static_assert (GS::AlwaysFalse<FromType>, "");

		return {};
	}


	static IRef<ToInterface>		StaticCast (Ref<FromType>&& /*fromRef*/)
	{
		static_assert (!GS::IsCompatible<FromType, ToInterface>, "'ToInterface' is base of 'FromType'. No need to cast.");
		static_assert (GS::AreRelated<FromType, ToInterface>, "Use ODB::DynamicCast () for unrelated types.");
		static_assert (GS::AlwaysFalse<FromType>, "");

		return {};
	}


	static ConstIRef<ToInterface>		StaticCast (const ConstRef<FromType>& /*fromRef*/)
	{
		static_assert (!GS::IsCompatible<FromType, ToInterface>, "'ToInterface' is base of 'FromType'. No need to cast.");
		static_assert (GS::AreRelated<FromType, ToInterface>, "Use ODB::DynamicCast () for unrelated types.");
		static_assert (GS::AlwaysFalse<FromType>, "");

		return {};
	}


	static ConstIRef<ToInterface>		StaticCast (ConstRef<FromType>&& /*fromRef*/)
	{
		static_assert (!GS::IsCompatible<FromType, ToInterface>, "'ToInterface' is base of 'FromType'. No need to cast.");
		static_assert (GS::AreRelated<FromType, ToInterface>, "Use ODB::DynamicCast () for unrelated types.");
		static_assert (GS::AlwaysFalse<FromType>, "");

		return {};
	}


	static IRef<ToInterface>		DynamicCast (const Ref<FromType>& fromRef)
	{
		static_assert (!GS::IsCompatible<FromType, ToInterface>, "'ToInterface' is base of 'FromType'. No need to cast.");

		const Object*		objectPointer = fromRef.GetConstMemoryAddress ();
		const ToInterface*	toPointer     = dynamic_cast<const ToInterface*> (objectPointer);

		if (toPointer == nullptr)
			return nullptr;
		else
			return IRef<ToInterface> (GS::GetRawDifference (objectPointer, toPointer), fromRef.AsObject ());
	}


	static IRef<ToInterface>		DynamicCast (Ref<FromType>&& fromRef)
	{
		static_assert (!GS::IsCompatible<FromType, ToInterface>, "'ToInterface' is base of 'FromType'. No need to cast.");

		const Object*		objectPointer = fromRef.GetConstMemoryAddress ();
		const ToInterface*	toPointer     = dynamic_cast<const ToInterface*> (objectPointer);

		if (toPointer == nullptr)
			return nullptr;
		else
			return IRef<ToInterface> (GS::GetRawDifference (objectPointer, toPointer), std::move (const_cast<Ref<Object>&> (fromRef.AsObject ())));
	}


	static ConstIRef<ToInterface>		DynamicCast (const ConstRef<FromType>& fromRef)
	{
		static_assert (!GS::IsCompatible<FromType, ToInterface>, "'ToInterface' is base of 'FromType'. No need to cast.");

		const Object*		objectPointer = fromRef.GetConstMemoryAddress ();
		const ToInterface*	toPointer     = dynamic_cast<const ToInterface*> (objectPointer);

		if (toPointer == nullptr)
			return nullptr;
		else
			return ConstIRef<ToInterface> (GS::GetRawDifference (objectPointer, toPointer), fromRef.AsObject ());
	}


	static ConstIRef<ToInterface>		DynamicCast (ConstRef<FromType>&& fromRef)
	{
		static_assert (!GS::IsCompatible<FromType, ToInterface>, "'ToInterface' is base of 'FromType'. No need to cast.");

		const Object*		objectPointer = fromRef.GetConstMemoryAddress ();
		const ToInterface*	toPointer     = dynamic_cast<const ToInterface*> (objectPointer);

		if (toPointer == nullptr)
			return nullptr;
		else
			return ConstIRef<ToInterface> (GS::GetRawDifference (objectPointer, toPointer), std::move (const_cast<ConstRef<Object>&> (fromRef.AsObject ())));
	}


	static bool		IsType (const Ref<FromType>& fromRef)
	{
		return DynamicCast (fromRef) != nullptr;
	}


	static bool		IsType (const ConstRef<FromType>& fromRef)
	{
		return DynamicCast (fromRef) != nullptr;
	}
};


template <class ToType, class FromInterface>
class CastDispatcher<ToType, FromInterface, EnableIf<IsObject<ToType> && IsInterface<FromInterface>>> {
public:
	static const Ref<ToType>&		StaticCast (const IRef<FromInterface>& fromIRef)
	{
		static_assert (GS::AreRelated<FromInterface, ToType>, "Use ODB::DynamicCast () for unrelated types.");

		return Imp::CastDispatcher<ToType, Object>::StaticCast (fromIRef.ref);
	}


	static Ref<ToType>&&		StaticCast (IRef<FromInterface>&& fromIRef)
	{
		static_assert (GS::AreRelated<FromInterface, ToType>, "Use ODB::DynamicCast () for unrelated types.");

		return Imp::CastDispatcher<ToType, Object>::StaticCast (std::move (fromIRef.ref));
	}


	static const ConstRef<ToType>&		StaticCast (const ConstIRef<FromInterface>& fromIRef)
	{
		static_assert (GS::AreRelated<FromInterface, ToType>, "Use ODB::DynamicCast () for unrelated types.");

		return Imp::CastDispatcher<ToType, Object>::StaticCast (fromIRef.ref);
	}


	static ConstRef<ToType>&&		StaticCast (ConstIRef<FromInterface>&& fromIRef)
	{
		static_assert (GS::AreRelated<FromInterface, ToType>, "Use ODB::DynamicCast () for unrelated types.");

		return Imp::CastDispatcher<ToType, Object>::StaticCast (std::move (fromIRef.ref));
	}


	static const Ref<ToType>&		DynamicCast (const IRef<FromInterface>& fromIRef)
	{
		return Imp::CastDispatcher<ToType, Object>::DynamicCast (fromIRef.ref);
	}


	static Ref<ToType>		DynamicCast (IRef<FromInterface>&& fromIRef)
	{
		return Imp::CastDispatcher<ToType, Object>::DynamicCast (std::move (fromIRef.ref));
	}


	static const ConstRef<ToType>&		DynamicCast (const ConstIRef<FromInterface>& fromIRef)
	{
		return Imp::CastDispatcher<ToType, Object>::DynamicCast (fromIRef.ref);
	}


	static ConstRef<ToType>		DynamicCast (ConstIRef<FromInterface>&& fromIRef)
	{
		return Imp::CastDispatcher<ToType, Object>::DynamicCast (std::move (fromIRef.ref));
	}


	static bool		IsType (const IRef<FromInterface>& fromIRef)
	{
		return Imp::CastDispatcher<ToType, Object>::IsType (fromIRef.ref);
	}


	static bool		IsType (const ConstIRef<FromInterface>& fromIRef)
	{
		return Imp::CastDispatcher<ToType, Object>::IsType (fromIRef.ref);
	}
};


}	// namespace Imp


template <class ToType, class FromType>
decltype (auto)		StaticCast (const IRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (from);
}


template <class ToType, class FromType>
auto				StaticCast (IRef<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (std::move (from));
}


template <class ToType, class FromType>
decltype (auto)		StaticCast (const ConstIRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (from);
}


template <class ToType, class FromType>
auto				StaticCast (ConstIRef<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (std::move (from));
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (const IRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (from);
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (IRef<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (std::move (from));
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (const ConstIRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (from);
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (ConstIRef<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (std::move (from));
}


template <class ToType, class FromType>
bool	IsType (const IRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::IsType (from);
}


template <class ToType, class FromType>
bool	IsType (const ConstIRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::IsType (from);
}


template <class Interface>
IRef<Interface>			ConstCast (IRef<Interface> /*from*/)
{
	static_assert (GS::AlwaysFalse<Interface>, "No need to const cast an ODB::IRef, because it is already not const.");
	return {};
}


template <class Interface>
const IRef<Interface>&	ConstCast (const ConstIRef<Interface>& from)
{
	return reinterpret_cast<const IRef<Interface>&> (from);
}


template <class Interface>
IRef<Interface>&		ConstCast (ConstIRef<Interface>& from)
{
	return reinterpret_cast<IRef<Interface>&> (from);
}


template <class Interface>
IRef<Interface>			ConstCast (ConstIRef<Interface>&& from)
{
	return reinterpret_cast<IRef<Interface>&&> (from);
}


}	// namespace ODB


#endif
