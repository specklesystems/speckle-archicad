
// *****************************************************************************
//
//                              Interface Container
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined CONTAINER_HPP
#define CONTAINER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "TypeTraits.hpp"
#include "EnumerationTraits.hpp"



// ============================ Interface Container ============================

namespace GS {

template <class Type>
class Container {
public:
	using ValueType = Type;		// type of the value the container stores

protected:
	template <class T>
	struct MakeConstPtr {
		typedef T ConstType;
	};

	template <class T>
	struct MakeConstPtr<T*> {
		typedef const T* ConstType;
	};
};


enum FromBeginSelector {
	FromBegin
};


enum ToEndSelector {
	ToEnd
};


template <class Container>
void	SelectSmallerAndLargerContainer (Container& cont1, Container& cont2, Container*& smallerCont, Container*& largerCont)
{
	if (cont1.GetSize () <= cont2.GetSize ()) {
		smallerCont = &cont1;
		largerCont  = &cont2;
	} else {
		smallerCont = &cont2;
		largerCont  = &cont1;
	}
}


}	// namespace GS
// ____________________________ Interface Container ____________________________


#endif
