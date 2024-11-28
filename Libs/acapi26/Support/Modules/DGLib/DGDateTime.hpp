// *****************************************************************************
// File:			DGDateTime.hpp
//
// Description:		DateTime classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGDATETIME_HPP
#define DGDATETIME_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRoot.hpp"

#include "DGItemProperty.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class DateTime;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- DateTimeChangeEvent -----------------------------------------------------

class DG_DLL_EXPORT DateTimeChangeEvent: public ItemChangeEvent
{
friend class DateTimeObserver;				// To access protected constructor

private:
	GSTime	previousTime;

protected:
	explicit DateTimeChangeEvent (const ItemChangeEvent& ev);

public:
	~DateTimeChangeEvent ();

	DateTime*	GetSource (void) const;

	GSTime	GetPreviousTime (void) const;
};


// --- DateTimeObserver --------------------------------------------------------

class DG_DLL_EXPORT DateTimeObserver: public ItemObserver
{
protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;

	virtual void	DateTimeChanged (const DateTimeChangeEvent& ev);

public:
	DateTimeObserver ();
   ~DateTimeObserver ();
};


// --- DateTime ----------------------------------------------------------------

class DG_DLL_EXPORT DateTime: public Item,
							  public ItemFontProperty,
							  public FocusableProperty,
							  public ItemFocusNotifier<DateTime>
{
protected:
	DateTime ();
	DateTime (const Panel& panel, short item);

public:
	~DateTime ();

	void	Attach (DateTimeObserver& observer);
	void	Detach (DateTimeObserver& observer);

	void	SetMin (Int32 min);
	void	SetMax (Int32 max);
	void	SetValue (Int32 value);

	Int32	GetMin (void) const;
	Int32	GetMax (void) const;
	Int32	GetValue (void) const;

    virtual GSErrCode Store (GS::ObjectState& os) const override;
};


// --- DateControl -------------------------------------------------------------

class DG_DLL_EXPORT DateControl: public DateTime
{
public:
	DateControl (const Panel& panel, short item);
	DateControl (const Panel& panel, const Rect& rect);
   ~DateControl ();
};


// --- TimeControl -------------------------------------------------------------

class DG_DLL_EXPORT TimeControl: public DateTime
{
public:
	TimeControl (const Panel& panel, short item);
	TimeControl (const Panel& panel, const Rect& rect);
   ~TimeControl ();
};


// --- CalendarControl ---------------------------------------------------------

class DG_DLL_EXPORT CalendarControl: public DateTime
{
public:
	CalendarControl (const Panel& panel, short item);
	CalendarControl (const Panel& panel, const Rect& rect);
   ~CalendarControl ();
};

}	// namespace DG

#endif
