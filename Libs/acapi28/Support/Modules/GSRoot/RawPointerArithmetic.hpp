// *********************************************************************************************************************
// File:			RawPointerArithmetic.hpp
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************

#ifndef RAWPOINTERARITHMETIC_HPP
#define RAWPOINTERARITHMETIC_HPP

#pragma once


#include "Definitions.hpp"


namespace GS {


inline IntPtr	GetRawDifference (const void* from, const void* to)
{
	return reinterpret_cast<const char*> (to) - reinterpret_cast<const char*> (from);
}


template <class ToType>
ToType*		AddRawOffset (void* from, IntPtr offset)
{
	if (from == nullptr)
		return nullptr;
	else
		return reinterpret_cast<ToType*> (reinterpret_cast<char*> (from) + offset);
}


template <class ToType>
const ToType*	AddRawOffset (const void* from, IntPtr offset)
{
	if (from == nullptr)
		return nullptr;
	else
		return reinterpret_cast<const ToType*> (reinterpret_cast<const char*> (from) + offset);
}


}	// namespace GS


#endif
