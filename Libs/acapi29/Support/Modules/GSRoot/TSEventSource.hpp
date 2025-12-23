
// *****************************************************************************
//
//                              Class EventSource
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	CSZ
//
// SG compatible
//
// *****************************************************************************


#if !defined TSEVENTSOURCE_HPP
#define TSEVENTSOURCE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "Array.hpp"
#include "ThreadingDebug.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace GS {
	namespace TS {
		class EventObserver;
	}
}


// ============================= Class EventSource =============================

namespace GS { namespace TS {

class GSROOT_DLL_EXPORT EventSource : public NonThreadSafeClass {

	friend class EventObserver;

private:
	typedef ArrayFB<EventObserver*, 1>	TEventObserverContainer;
	TEventObserverContainer				eventObservers;

	static ULong						maxItem;

protected:
	class	ObserverEnumerator;
	std::function<void ()> CheckThreadFunction = [&] () { FUNCTIONCALLEDCHECKTHREAD (); };

protected:
	EventSource (const EventSource& source);
//#if !defined (__GNUC__) || ((__GNUC__ > 3) || (__GNUC_MINOR__ > 1))  // FM: Bug in GCC 3.1 problem with operator= and inheritance.
	EventSource&	operator= (const EventSource& source);
//#endif

protected:
	EventSource ();
	virtual	~EventSource ();

	void	Attach (EventObserver& observer);
	void	Detach (EventObserver& observer);

	ObserverEnumerator	EnumerateObservers (void) const;

private:
	void AddObserver (EventObserver& observer);

protected:
	// derivable interface
	virtual void	_Attach (EventObserver& observer);
	virtual void	_Detach (EventObserver& observer);
};


class GSROOT_DLL_EXPORT EventSource::ObserverEnumerator : private NonThreadSafeClass {
private:
	const EventSource*	owner;			// owner of the enumerator
	UIndex				currentIndex;	// index of the current connection (MaxUIndex indicates end)
	EventObserver*		currentItem;

public:
	explicit	ObserverEnumerator (const EventSource& owner);
				ObserverEnumerator (const ObserverEnumerator& source);
				~ObserverEnumerator ();

	EventObserver&	operator* () const;
	template <class OBSERVER_TYPE>
	OBSERVER_TYPE&	Get () const
	{
		OBSERVER_TYPE* observer = dynamic_cast<OBSERVER_TYPE*>(&(operator* ()));
		DBASSERT (observer != nullptr);
		return *observer;
	}

	ObserverEnumerator&		operator++ ();

	bool		operator== (std::nullptr_t) const;
	bool		operator!= (std::nullptr_t) const;
};

}	// namespace TS
}	// namespace GS

// _____________________________ Class EventSource _____________________________


inline void		GS::TS::EventSource::Attach (EventObserver& observer)
{
	_Attach (observer);
}


inline void		GS::TS::EventSource::Detach (EventObserver& observer)
{
	_Detach (observer);
}


#endif
