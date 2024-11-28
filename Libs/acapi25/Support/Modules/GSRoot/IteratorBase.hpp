
// *****************************************************************************
//
//                             Base class for iterators
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ITERATORBASE_HPP
#define ITERATORBASE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"



// ============================ Class IteratorBase =============================

namespace GS {

template <class T>
class IteratorBase {
public:
		// Definitions

	typedef T ValueType;	// type of the value iterator iterates on

	virtual ~IteratorBase () {}
};

}	// namespace GS
// ____________________________ Class IteratorBase _____________________________


#endif
