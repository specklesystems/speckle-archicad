#if !defined APICORE_ATTRIBUTEINDEX_HPP
#define APICORE_ATTRIBUTEINDEX_HPP

#pragma once

#include "ADBAttributeIndex.hpp"
#include "Definitions.hpp"
#include "StringConversion.hpp"


//! @cond Doxygen_Suppress
class API_AttributeIndex;
API_AttributeIndex ACAPI_CreateAttributeIndex (Int32 index);
//! @endcond

/** @brief Index reference to an attribute.
	@class API_AttributeIndex
	@ingroup Dialog
	@remarks &nbsp;In version 23, the short type attribute index references are replaced with this new type definition.
*/
class API_AttributeIndex
{
public:
	bool	operator== (const API_AttributeIndex& rightOp) const
	{
		return (attributeIndex == rightOp.attributeIndex);
	}

	bool	operator!= (const API_AttributeIndex& rightOp) const
	{
		return !operator== (rightOp);
	}

	Int32	ToInt32_Deprecated () const
	{
		return attributeIndex;
	}

	ULong	GenerateHashValue () const 
	{
		return attributeIndex;
	}

	GSErrCode	ReadAsInt32 (GS::IChannel& ic) 
	{
		return ic.Read (attributeIndex);
	}
	GSErrCode	WriteAsInt32 (GS::OChannel& oc) const 
	{
		return oc.Write (attributeIndex);
	}

	GS::UniString	ToUniString () const
	{
		return GS::ValueToUniString (attributeIndex);
	}
	
	bool	IsPositive () const
	{
		return attributeIndex > 0;
	}
	bool	IsNegative () const
	{
		return attributeIndex < 0;
	}

private:
	friend	API_AttributeIndex	ACAPI_CreateAttributeIndex (Int32 index);

	Int32	attributeIndex;

};

/** @brief A wrapper function to create an @ref API_AttributeIndex from its GS equivalent.
	@ingroup Attribute
	@since Archicad 27
	@param index [in] The attribute index to convert.
	@return The API equivalent.
*/
inline API_AttributeIndex ACAPI_CreateAttributeIndex (Int32 index)
{
	API_AttributeIndex attributeIndex;
	attributeIndex.attributeIndex  = index;
	return attributeIndex;
}


static_assert (GS::IsPod<API_AttributeIndex>, "API_AttributeIndex should be POD type.");
static_assert (sizeof (API_AttributeIndex) == sizeof (Int32), "sizeof (API_AttributeIndex) != sizeof (Int32)");

static const API_AttributeIndex	APIInvalidAttributeIndex			= ACAPI_CreateAttributeIndex (0);
static const API_AttributeIndex	APIApplicationLayerAttributeIndex	= ACAPI_CreateAttributeIndex (1);
static const API_AttributeIndex	APISolidLineAttributeIndex		= ACAPI_CreateAttributeIndex (1);


#endif
