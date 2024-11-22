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
#include	"MemoryBarrier.hpp"

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

	// For reference counting
	inline void SharedObject::AddRef () const
	{
		AtomicIncrement ((Int32*) &refCount);
	}


	// For reference counting
	inline void SharedObject::Release () const
	{
		DBASSERT (refCount > 0);
		if (AtomicDecrement ((Int32*) &refCount) == 0) {
			delete this;
		}
	}


}	// namespace GS

#endif

