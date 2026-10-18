// *********************************************************************************************************************
// File:			DGVisitorUtility.hpp
//
// Description:		Visitor utility class
//
// *********************************************************************************************************************

#ifndef DGVISITORUTILITY_HPP
#define DGVISITORUTILITY_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "Definitions.hpp"

#include <type_traits>
#include <functional>


namespace DG {

namespace VisitorUtility {

enum ApplyContinuation { Interrupt, Continue };

template <class Visitor, class Element>
ApplyContinuation	ApplyOnElement (const Visitor& visitor, Element& element)
{
	using ResultType = std::invoke_result_t<Visitor, Element&>;
	if constexpr (std::is_same_v<ApplyContinuation, ResultType>) {
		return std::invoke (visitor, element);
	} else if constexpr (std::is_same_v<void, ResultType>) {
		std::invoke (visitor, element);
		return ApplyContinuation::Continue;
	} else {
		// Using "AlwaysFalse<>" makes the condition dependent. Using "false" would make the program ill-formed.
		static_assert (GS::AlwaysFalse<Element>, "Unexpected instantiation of ApplyOnElement.");
	}
}

} // namespace VisitorUtility

} // namespace DG

#endif
