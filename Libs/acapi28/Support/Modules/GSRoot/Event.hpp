
// *****************************************************************************
//
//						         Class Event
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, AZS
//
// SG compatible
//
// *****************************************************************************


#if !defined EVENT_HPP
#define EVENT_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace GS { class EventSource; }



// ================================ Class Event ================================

namespace GS {

class GSROOT_DLL_EXPORT Event {
public:
	enum Status { Unprocessed, Processed };

private:
	EventSource*	source;		// source of the event
	Status			status;		// status of the event

protected:
	explicit Event (EventSource* eventSource, Status eventStatus = Unprocessed);

public:
	virtual	~Event ();

	virtual	Event*		Clone (void) const { return nullptr; }

	inline EventSource*	GetSource (void) const;
	inline Status		GetStatus (void) const;

	inline void			SetProcessed (void);
	inline bool			IsProcessed  (void) const;
};

}	// namespace GS


inline GS::EventSource*		GS::Event::GetSource (void) const
{
	return source;
}


inline GS::Event::Status	GS::Event::GetStatus (void) const
{
	return status;
}


inline void		GS::Event::SetProcessed (void)
{
	status = Processed;
}


inline bool		GS::Event::IsProcessed (void) const
{
	return (status == Processed);
}
// ________________________________ Class Event ________________________________


#endif
