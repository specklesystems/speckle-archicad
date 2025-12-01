// *********************************************************************************************************************
// Description:		A class which can be implicitly initialized by an empty initializer-list. It is useful in overload
//					situations to resolve ambiguity.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef EMPTYINITIALIZERLIST_HPP
#define EMPTYINITIALIZERLIST_HPP

#pragma once


#include "Definitions.hpp"


namespace GS {


// === class Imp::NotInstantiable ======================================================================================

namespace Imp {

class NotInstantiable {
public:
	NotInstantiable () = delete;
};

}	// namespace Imp


// === class EmptyInitializerList ======================================================================================

using EmptyInitializerList = std::initializer_list<Imp::NotInstantiable>;


}	// namespace GS


#endif
