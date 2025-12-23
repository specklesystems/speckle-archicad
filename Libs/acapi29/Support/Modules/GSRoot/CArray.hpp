// *********************************************************************************************************************
// Description:		C Array Utility Functions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, KKr
//
// *********************************************************************************************************************

#ifndef CARRAY_HPP
#define CARRAY_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "GSDebug.hpp"
#include "Inserter.hpp"


// =============================================================================

namespace GS {

template <class Type, size_t N>
class CArrayInserter {
private:
	Type*			array;
	mutable UInt32	i = 0;

public:
	using DecayedFirstArgumentType = Type;

	explicit CArrayInserter (Type* array) :
		array (array)
	{
	}

	void	operator() (const Type& value) const
	{
		DBASSERT (i < N);
		array[i] = value;
		++i;
	}

	void	operator() (Type&& value) const
	{
		DBASSERT (i < N);
		array[i] = std::move (value);
		++i;
	}
};


template <class Type, size_t N>
auto	GetInserter (Type (&array)[N])
{
	return CArrayInserter<Type, N> (array);
}

} // namespace GS

#endif
