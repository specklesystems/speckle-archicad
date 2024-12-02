// *********************************************************************************************************************
// Description:		Selector for constructing an object from its constructor parameters in place.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	BIM
//
// *********************************************************************************************************************


#ifndef INPLACESELECTOR_HPP
#define INPLACESELECTOR_HPP

#pragma once


namespace GS {


// === Implementation details ==========================================================================================

namespace Imp {

class InPlacePrivate {};

}


// === Untyped "in place" selector =====================================================================================

using InPlaceSelector = void (&) (Imp::InPlacePrivate);


inline void		InPlace (Imp::InPlacePrivate)
{
}


// === Typed "in place" selector =======================================================================================

template <class Type>
using TypedInPlaceSelector = void (&) (Imp::InPlacePrivate, Type);


template <class Type>
inline void		InPlace (Imp::InPlacePrivate, Type)
{
}


}	// namespace GS


#endif
