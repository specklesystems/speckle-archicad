// *********************************************************************************************************************
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	KKr
//
// *********************************************************************************************************************

#ifndef MEASUREDURATION_HPP
#define MEASUREDURATION_HPP

#pragma once


#include "GSTime.hpp"


namespace GS {


// === MeasureDuration () ==============================================================================================

template <class Function>
double	MeasureDuration (const Function& function)
{
	const GSFineTicks start = TIGetFineTicks ();
	function ();
	const GSFineTicks end = TIGetFineTicks ();

	return static_cast<double> (end - start) / TIGetFineTicksPerSec ();
}


// === class DurationMeasurer ==========================================================================================

class DurationMeasurer {
private:
	GSFineTicks start;

public:
	DurationMeasurer ();

	void	Restart ();
	double	GetDuration () const;
};


// === DurationMeasurer methods ========================================================================================

inline DurationMeasurer::DurationMeasurer ()
{
	start = TIGetFineTicks ();
}


inline void		DurationMeasurer::Restart ()
{
	start = TIGetFineTicks ();
}


inline double	DurationMeasurer::GetDuration () const
{
	const GSFineTicks end = TIGetFineTicks ();

	return static_cast<double> (end - start) / TIGetFineTicksPerSec ();
}


}	// namespace GS


#endif
