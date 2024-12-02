// *********************************************************************************************************************
// Description:		Base Class for objects pointed by SharedPtr
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_SHAREDOBJECT_HPP)
#define GS_SHAREDOBJECT_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"GSRootExport.hpp"
#include	"Definitions.hpp"
#include	"SharedPtr.hpp"
#include	"Atomic.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS {

	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------

template<class TPointee>
class ConstSharedPtr;

template<class TPointee>
class SharedPtr;

class GSROOT_DLL_EXPORT SharedObject
{
private:
	mutable	ULong		refCount;				// for intrusive refcounted smart pointers (COM-like)

	template<typename DerivedT> friend class SharedPtr;
	template<typename DerivedT> friend class ConstSharedPtr;

	void	AddRef () const;
	void	Release () const;
	template<typename DerivedT, typename OnDeleteT>
	void	Release (OnDeleteT&& onDelete) const;


	bool	AddRefIfRefCountNotZero () const;

protected:
	ULong GetRefCount () const { return refCount; }

public:
	SharedObject () : refCount (0) {}
	SharedObject (const SharedObject&) : refCount (0) {}
	SharedObject& operator= (const SharedObject& /*src*/) { return *this; }

	virtual ~SharedObject ();

};

	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------

inline void SharedObject::AddRef () const
{
	AtomicIncrement ((Int32*) &refCount);
}


inline void SharedObject::Release () const
{
	DBASSERT (refCount > 0);
	if (AtomicDecrement ((Int32*) &refCount) == 0) {
		delete this;
	}
}

template<typename DerivedT, typename OnDeleteT>
inline void SharedObject::Release (OnDeleteT&& onDelete) const
{
	DBASSERT (refCount > 0);
	if (AtomicDecrement ((Int32*) &refCount) == 0) {
		onDelete (static_cast<DerivedT&> (const_cast<SharedObject&>(*this)));
		delete this;
	}
}

}	// namespace GS

#endif

