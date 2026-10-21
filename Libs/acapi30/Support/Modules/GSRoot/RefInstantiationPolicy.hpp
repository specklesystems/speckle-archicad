
// *****************************************************************************
//
// Declaration and implementation of RefInstantiationPolicy<T> classes
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_REFINSTANTIATIONPOLICY_HPP
#define GS_REFINSTANTIATIONPOLICY_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Ref.hpp"



// --- RefStaticInstantiationPolicy<T, CounterT> class -------------------------

namespace GS {

template<class T, class CounterT = Counter>
class RefStaticInstantiationPolicy {

// Static data members:
private:
	static Ref<T, CounterT>		instance;

// Static implementation:
protected:
	static void					Create (Ref<T, CounterT>*& ptr);

};

////////////////////////////////////////////////////////////////////////////////
// RefStaticInstantiationPolicy inlines

////////////////////////////////////////////////////////////////////////////////
// Static member initialization
////////////////////////////////////////////////////////////////////////////////

template<class T, class CounterT>
GS::Ref<T, CounterT>	RefStaticInstantiationPolicy<T, CounterT>::instance;

////////////////////////////////////////////////////////////////////////////////
// Static implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Create
// -----------------------------------------------------------------------------

template<class T, class CounterT>
inline void		RefStaticInstantiationPolicy<T, CounterT>::Create (Ref<T, CounterT>*& ptr)
{
	instance = new T ();
	ptr = &instance;
}

}



// --- RefLazyInstantiationPolicy<T, CounterT> class ---------------------------

namespace GS {

template<class T, class CounterT>
class RefLazyInstantiationPolicy {

// Static implementation:
protected:
	static void		Create (Ref<T, CounterT>*& ptr);

};

////////////////////////////////////////////////////////////////////////////////
// RefLazyInstantiationPolicy inlines

////////////////////////////////////////////////////////////////////////////////
// Static implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Create
// -----------------------------------------------------------------------------

template<class T, class CounterT>
inline void		RefLazyInstantiationPolicy<T, CounterT>::Create (Ref<T, CounterT>*& ptr)
{
	static GS::Ref<T, CounterT> instance (new T ());
	ptr = &instance;
}

}

#endif // GS_REFINSTANTIATIONPOLICY_HPP
