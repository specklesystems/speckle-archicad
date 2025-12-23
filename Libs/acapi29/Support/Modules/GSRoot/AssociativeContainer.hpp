
// *****************************************************************************
//
//                        Interface AssociativeContainer
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ASSOCIATIVECONTAINER_HPP
#define ASSOCIATIVECONTAINER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Container.hpp"
#include "Pair.hpp"


// ====================== Interface AssociativeContainer =======================

namespace GS {

template <class Key, class Value>
class AssociativeContainer : public Container<Pair<Key, Value>> {
public:
	using AssociatedKeyType		= Key;    	// type of the index the associative container is searchable by
	using AssociatedValueType	= Value;	// type of the value the associative container stores
};

}	// namespace GS


#endif
