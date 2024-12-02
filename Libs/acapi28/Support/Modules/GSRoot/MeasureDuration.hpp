// *********************************************************************************************************************
//
// Contact person: MB, PR
//
// *********************************************************************************************************************

#ifndef GS_MEASUREDURATION_HPP
#define GS_MEASUREDURATION_HPP

#include "GSTime.hpp"


namespace GS {


// === MeasureDuration (in seconds) ====================================================================================

template <class Function>
double	MeasureDuration (const Function& function)
{
	const SteadyTime start = SteadyClock::now ();
	function ();
	const SteadyTime end = SteadyClock::now ();

	return Duration<double> (end - start).count ();
}


// === class DurationMeasurer (in seconds) =============================================================================

class DurationMeasurer {
private:
	SteadyTime start;

public:
	DurationMeasurer ();

	void	Restart ();
	double	GetDuration () const;
};


// === DurationMeasurer methods ========================================================================================

inline DurationMeasurer::DurationMeasurer ()
	: start { SteadyClock::now () }
{}


inline void		DurationMeasurer::Restart ()
{
	start = SteadyClock::now ();
}


inline double	DurationMeasurer::GetDuration () const
{
	const SteadyTime now = SteadyClock::now ();

	return Duration<double> (now - start).count ();
}


} // namespace GS


#endif
