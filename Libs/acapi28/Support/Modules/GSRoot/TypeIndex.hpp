// *********************************************************************************************************************
// Description:		Wrapper class for std::type_index
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// *********************************************************************************************************************

#ifndef TYPEINDEX_HPP
#define TYPEINDEX_HPP

#pragma once


#include <typeindex>
#include "HashCommon.hpp"


namespace GS {


// === class TypeIndex =================================================================================================

class TypeIndex : public std::type_index {
public:
	TypeIndex (const std::type_info& typeInfo);

	ULong	GenerateHashValue () const;
};


// === TypeIndex inline methods ========================================================================================

inline TypeIndex::TypeIndex (const std::type_info& typeInfo) :
	std::type_index (typeInfo)
{
}


inline ULong	TypeIndex::GenerateHashValue () const
{
	return GS::CalculateHashValue (static_cast<UInt64> (hash_code ()));
}


}	// namespace GS


#endif
