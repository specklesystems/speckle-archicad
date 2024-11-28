
// *****************************************************************************
//
// Declaration of HeaderIterator class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HEADERITERATOR_HPP
#define COMMUNICATION_HEADERITERATOR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Header.hpp"

	// from GSRoot
#include "ForwardIterator.hpp"



// --- HeaderIterator class ----------------------------------------------------

namespace Communication {

typedef GS::ConstForwardIterator<Header> ConstHeaderIterator;

}

#endif // COMMUNICATION_HEADERITERATOR_HPP