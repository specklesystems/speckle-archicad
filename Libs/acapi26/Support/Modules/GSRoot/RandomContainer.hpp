
// *****************************************************************************
//
//                           Interface RandomContainer
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined RANDOMCONTAINER_HPP
#define RANDOMCONTAINER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Container.hpp"
#include "GSDebug.hpp"


// ========================= Interface RandomContainer =========================

namespace GS {

template <class Type>
class RandomContainer : public Container<Type> {};


template <class Cont>
struct RandomContainerRange {
	Cont&		container;
	UIndex      rangeBegin;
	UIndex      rangeEnd;

	RandomContainerRange (Cont& container, UIndex rangeBegin, UIndex rangeEnd) : container (container), rangeBegin (rangeBegin), rangeEnd (rangeEnd) { DBASSERT (rangeBegin <= rangeEnd); }

	auto begin () { return container.Begin () + rangeBegin; }
	auto end ()   { return container.Begin () + rangeEnd; }
};


template <class Cont>
struct RandomContainerConstRange {
	const Cont&     container;
	UIndex          rangeBegin;
	UIndex          rangeEnd;

	RandomContainerConstRange (const Cont& container, UIndex rangeBegin, UIndex rangeEnd) : container (container), rangeBegin (rangeBegin), rangeEnd (rangeEnd) { DBASSERT (rangeBegin <= rangeEnd); }

	auto begin () { return container.Begin () + rangeBegin; }
	auto end ()   { return container.Begin () + rangeEnd; }
};


template <class Cont>
struct RandomContainerReverseRange {
	Cont&		container;

	RandomContainerReverseRange (Cont& container) : container (container) { }

	auto begin () { return container.ReverseBegin (); }
	auto end ()   { return container.ReverseEnd (); }
};


template <class Cont>
struct RandomContainerReverseConstRange {
	const Cont&     container;

	RandomContainerReverseConstRange (const Cont& container) : container (container) { }

	auto begin () { return container.ReverseBegin (); }
	auto end ()   { return container.ReverseEnd (); }
};


}	// namespace GS


#endif
