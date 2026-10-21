// *********************************************************************************************************************
// File:			ElemComparisonFlags.hpp
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	BeA
//
// *********************************************************************************************************************


#ifndef MODELER_ELEMCOMPARISONFLAGS_HPP
#define MODELER_ELEMCOMPARISONFLAGS_HPP

#pragma once


// from GSRoot
#include "FlagSupport.hpp"


namespace Modeler {


enum class ElemComparisonFlags {		// describes what to include when comparing Modeler::Elem objects
	GenId		= 0b00000001,
	ElemGuid	= 0b00000010,
	Layer		= 0b00000100
};

ENABLE_FLAG_SUPPORT (ElemComparisonFlags);

static constexpr ElemComparisonFlags ElemComparisonFlags_None			= ElemComparisonFlags (0b00000000);
static constexpr ElemComparisonFlags ElemComparisonFlags_All			= ElemComparisonFlags (0b00000111);
static constexpr ElemComparisonFlags ElemComparisonFlags_WithoutGenId	= ElemComparisonFlags_All & ~ElemComparisonFlags::GenId;


}	// namespace Modeler


#endif
