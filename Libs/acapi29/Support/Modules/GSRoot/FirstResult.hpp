
// *****************************************************************************
//
//                            Class FirstResult
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FIRSTRESULT_HPP
#define FIRSTRESULT_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "Optional.hpp"


// =============================================================================

namespace GS {

template <typename Result>
class FirstResult {
private:
	Optional<Result> result;

public:
	bool HasValue () const;
	template <typename Function>
	Result&  Get (const Function& function);
};


template <typename Result>
bool FirstResult<Result>::HasValue () const
{
	return result.HasValue ();
}


template <typename Result>
template <typename Function>
Result&  FirstResult<Result>::Get (const Function& function)
{
	if (!result.HasValue ()) {
		result.New (function ());
	}

	return result.Get ();
}

}	// namespace GS


#endif
