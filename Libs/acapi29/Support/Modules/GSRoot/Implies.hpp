// *********************************************************************************************************************
// Description:		GS::Implies () represents a missing boolean operator, the implication.
//					Caveat: This is a plain function, so all arguments must be calculated before calling it. As a
//					consequence there is no lazy evaluation (short-circuiting).
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef GS_IMPLIES_HPP
#define GS_IMPLIES_HPP


namespace GS {


constexpr bool	Implies (bool a, bool b)
{
	return !a || b;
}


}	// namespace GS


#endif
