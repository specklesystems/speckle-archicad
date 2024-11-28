
// *****************************************************************************
//
// Declaration of ParameterIterator class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_PARAMETERITERATOR_HPP
#define COMMUNICATION_PARAMETERITERATOR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Parameter.hpp"

	// from GSRoot
#include "ForwardIterator.hpp"



// --- ParameterIterator class -------------------------------------------------

namespace Communication {

typedef GS::ConstForwardIterator<Parameter> ConstParameterIterator;

}

#endif // COMMUNICATION_PARAMETERITERATOR_HPP