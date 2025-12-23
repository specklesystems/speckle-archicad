
// *****************************************************************************
//
// Declaration and implementation of Singleton class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_SINGLETON_HPP
#define GS_SINGLETON_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Guard.hpp"
#include "SingletonLock.hpp"
#include "MemoryBarrier.hpp"



// --- StaticLocalInstantiationPolicy class ------------------------------------

namespace GS {

class StaticLocalInstantiationPolicy {

// Static implementation:
protected:
	template<typename T>
	static void		Create (T*& ptr);

};

////////////////////////////////////////////////////////////////////////////////
// StaticLocalInstantiationPolicy implementation

////////////////////////////////////////////////////////////////////////////////
// Static implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Create
// -----------------------------------------------------------------------------

template<typename T>
inline void		StaticLocalInstantiationPolicy::Create (T*& ptr)
{
	// Create an instance of the specified type, using a static local variable.
	// The instance will be destroyed by the system.

	static T instance;
	ptr = &instance;
}

}



// --- StaticInstantiationHelper class -----------------------------------------

namespace GS {

template<typename T>
class StaticInstantiationHelper {

// Friend classes:
friend class StaticInstantiationPolicy;

// Static data members:
private:
	static T		instance;

};

template <typename T>
T	StaticInstantiationHelper<T>::instance;

}



// --- StaticInstantiationPolicy class -----------------------------------------

namespace GS {

class StaticInstantiationPolicy {

// Static implementation:
protected:
	template<typename T>
	static void		Create (T*& ptr);

};

////////////////////////////////////////////////////////////////////////////////
// StaticInstantiationPolicy implementation

////////////////////////////////////////////////////////////////////////////////
// Static implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Create
// -----------------------------------------------------------------------------

template<typename T>
inline void		StaticInstantiationPolicy::Create (T*& ptr)
{
	// Create an instance of the specified type using a statically allocated
	// instance.

	ptr = &StaticInstantiationHelper<T>::instance;
}

}



// --- SingletonDestroyer class ------------------------------------------------

namespace GS {

template<typename T>
class SingletonDestroyer {

// Data members:
private:
	T*							m_singleton;

// Construction / destruction:
public:
	explicit SingletonDestroyer (T* singleton);
private:
			 SingletonDestroyer (const SingletonDestroyer&); // Disabled
public:
			~SingletonDestroyer ();

// Operator overloading:
private:
	const SingletonDestroyer&	operator = (const SingletonDestroyer&); // Disabled

};

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T>
inline SingletonDestroyer<T>::SingletonDestroyer (T* singleton) :
	m_singleton (singleton)
{
	DBASSERT (singleton != nullptr);
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<typename T>
inline SingletonDestroyer<T>::~SingletonDestroyer ()
{
	if (m_singleton != nullptr) {
		try {
			delete m_singleton;
		}
		catch (Exception&) {
			DBBREAK ();
		}
		catch (...) {
			DBBREAK ();
		}
	}

	m_singleton = nullptr;
}

}



// --- LazyInstantiationPolicy class -------------------------------------------

namespace GS {

class LazyInstantiationPolicy {

// Static implementation:
protected:
	template<typename T>
	static void		Create (T*& ptr);

};

////////////////////////////////////////////////////////////////////////////////
// LazyInstantiationPolicy implementation

////////////////////////////////////////////////////////////////////////////////
// Static implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Create
// -----------------------------------------------------------------------------

template<class T>
inline void		LazyInstantiationPolicy::Create (T*& ptr)
{
	// Create a new instance of the specified type, using new, that will be
	// destroyed by the associated static SingletonDestroyer instance.
	typedef SingletonDestroyer<T> SingletonDestroyerT;
	static SingletonDestroyerT destroyer (ptr = new T);
}

}



// --- Synchronized class ------------------------------------------------------

namespace GS {

class Synchronized {
};

}



// --- Unsynchronized class ----------------------------------------------------

namespace GS {

class Unsynchronized {
};

}




// --- Singleton class ---------------------------------------------------------

namespace GS {

template<typename T, typename InstantiationPolicy = LazyInstantiationPolicy, typename SynchronizationPolicy = Unsynchronized>
class Singleton : public InstantiationPolicy {

// Construction / destruction:
public:
	Singleton ();
private:
	Singleton (const Singleton&); // Disabled

// Operator overloading:
private:
	const Singleton&	operator = (const Singleton&); // Disabled

// Static operations:
public:
	static T&			GetInstance ();

};

////////////////////////////////////////////////////////////////////////////////
// Singleton implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<typename T, typename InstantiationPolicy, typename SynchronizationPolicy>
inline Singleton<T, InstantiationPolicy, SynchronizationPolicy>::Singleton ()
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Static operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetInstance
// -----------------------------------------------------------------------------

template<typename T, typename InstantiationPolicy, typename SynchronizationPolicy>
inline T&	Singleton<T, InstantiationPolicy, SynchronizationPolicy>::GetInstance ()
{
	// Note: the use of the static locale storage helps to avoid static construction
	// sequence issues. (regarding when the lock is created)

	static T* ptr = nullptr;

	if (ptr == nullptr) {
		InstantiationPolicy::Create (ptr);
	}

	DBASSERT (ptr != nullptr);

	return *ptr;
}

}


// --- Partial template specialization of Singleton class ----------------------

namespace GS {

template<typename T, typename InstantiationPolicy>
class Singleton<T, InstantiationPolicy, Synchronized> : public InstantiationPolicy {

// Static operations:
public:
	static T&			GetInstance ();

};

////////////////////////////////////////////////////////////////////////////////
// Singleton implementation

////////////////////////////////////////////////////////////////////////////////
// Static operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetInstance
// -----------------------------------------------------------------------------

template<typename T, typename InstantiationPolicy>
T&	Singleton<T, InstantiationPolicy, Synchronized>::GetInstance ()
{
	// Note: the use of the static locale storage helps to avoid static construction
	// sequence issues. (regarding when the lock is created)

	static T * volatile ptr = nullptr;

	// Note: the following code uses the double-checking algorithm to avoid
	// expensive locking.

	GS::MemoryBarrierForVolatile ();
	if (ptr == nullptr) {
		synchronized (SingletonLock::GetLock ()) {
			if (ptr == nullptr) {
				T* tmp = nullptr;
				InstantiationPolicy::Create (const_cast<T*&> (tmp));
				GS::MemoryBarrierForVolatile ();
				ptr = tmp;
			}
		}
	}

	DBASSERT (ptr != nullptr);

	return *const_cast<T*> (ptr);
}

}

#endif // GS_SINGLETON_HPP
