
// *****************************************************************************
//
//                            Class ObjectDisposer
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, AZS
//
// SG compatible
//
// *****************************************************************************


#if !defined OBJECTDISPOSER_HPP
#define OBJECTDISPOSER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "DefaultGarbageCollector.hpp"
#include "DisposeHandler.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace GS { class DisposableObject; }



// =========================== Class ObjectDisposer ============================

namespace GS {

class ObjectDisposer {
private:
	GarbageCollector*	gc;		// garbage collector used to register the given object for dispose
	DisposeHandler*		dh;		// dispose handler to be notified when the object is marked disposable

protected:
	inline ObjectDisposer ();
	inline ObjectDisposer (const ObjectDisposer& source);
	inline ObjectDisposer&	operator= (const ObjectDisposer& source);

	inline void		MarkAsDisposable (DisposableObject& obj);
	inline void		MarkAsFinished   (DisposableObject& obj);
	inline void		Unregister (DisposableObject& obj);

public:
	inline void		SetGarbageCollector (GarbageCollector& newGC);
	inline void		SetDefaultGarbageCollector (void);

	inline void		SetDisposeHandler (DisposeHandler& newDH);
};

}	// namespace GS



inline GS::ObjectDisposer::ObjectDisposer ()
{
	gc = nullptr;
	dh = nullptr;
}


inline GS::ObjectDisposer::ObjectDisposer (const GS::ObjectDisposer& /*source*/)
{
	// gc and dh should not be copied!

	gc = nullptr;
	dh = nullptr;
}


inline GS::ObjectDisposer&	GS::ObjectDisposer::operator= (const GS::ObjectDisposer& /*source*/)
{
	// gc and dh should not be copied!

	return *this;
}


inline void		GS::ObjectDisposer::MarkAsDisposable (DisposableObject& obj)
{
	if (dh != nullptr) {
		dh->DisposeRequested (obj);
		dh = nullptr;
	}

	if (gc != nullptr)
		gc->Register (&obj);	// Register should check for multiple registering!
}


inline void		GS::ObjectDisposer::MarkAsFinished (DisposableObject& obj)
{
	MarkAsDisposable (obj);
}


inline void		GS::ObjectDisposer::Unregister (DisposableObject& obj)
{
	if (gc != nullptr)
		gc->Unregister (&obj);
}


inline void		GS::ObjectDisposer::SetGarbageCollector (GarbageCollector& newGC)
{
	gc = &newGC;
}


inline void		GS::ObjectDisposer::SetDefaultGarbageCollector (void)
{
	gc = &defaultGarbageCollector;
}


inline void		GS::ObjectDisposer::SetDisposeHandler (DisposeHandler& newDH)
{
	dh = &newDH;
}
// ________________________ Interface GarbageCollector _________________________


#endif
