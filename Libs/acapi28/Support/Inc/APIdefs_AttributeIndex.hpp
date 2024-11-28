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


/**
 * @brief Index reference to an attribute.
 * @class API_AttributeIndex
 * @ingroup Dialog
 * @remarks &nbsp;In version 23, the short type attribute index references are replaced with this new type definition.
 */
class API_AttributeIndex
{
public:
/**
 * @brief Comparison operator.
 * @param rightOp The value to compare.
 * @return True if the given parameter is equal to the index.
 */
	bool	operator== (const API_AttributeIndex& rightOp) const
	{
		return (attributeIndex == rightOp.attributeIndex);
	}

/**
 * @brief Comparison operator.
 * @param rightOp The index to compare.
 * @return True if the given parameter is not equal to the index.
 */
	bool	operator!= (const API_AttributeIndex& rightOp) const
	{
		return !operator== (rightOp);
	}
/** @return Returns the attribute index as Int32 */
	Int32	ToInt32_Deprecated () const
	{
		return attributeIndex;
	}

/**
 * @brief Generate a hash value that's why API_AttributeIndex can be used with GS::HashTable.
 * @return Generated hash value.
 */
	ULong	GenerateHashValue () const 
	{
		return attributeIndex;
	}

/**
 * @brief Read the attribute index from the given channel.
 * @param ic Input channel.
 * @return Returns NoError if the reading was successful, otherwise with error.
 */
	GSErrCode	ReadAsInt32 (GS::IChannel& ic) 
	{
		return ic.Read (attributeIndex);
	}

/**
 * @brief Write the attribute index to the given channel.
 * @param oc Output channel.
 * @return Returns NoError if the writing was successful, otherwise with error.
 */
	GSErrCode	WriteAsInt32 (GS::OChannel& oc) const 
	{
		return oc.Write (attributeIndex);
	}

/** @return Returns the attribute index as GS::UniString. */
	GS::UniString	ToUniString () const
	{
		return GS::ValueToUniString (attributeIndex);
	}

/** @return Returns true if the attribute index is more than zero. */
	bool	IsPositive () const
	{
		return attributeIndex > 0;
	}

/** @return Returns true if the attribute index is less than zero. */
	bool	IsNegative () const
	{
		return attributeIndex < 0;
	}

private:
	friend	API_AttributeIndex	ACAPI_CreateAttributeIndex (Int32 index);

	Int32	attributeIndex;

};

/**
 * @brief A wrapper function to create an @ref API_AttributeIndex from its GS equivalent.
 * @ingroup Attribute
 * @since Archicad 27
 * @param index [in] The attribute index to convert.
 * @return The API equivalent.
 */
inline API_AttributeIndex ACAPI_CreateAttributeIndex (Int32 index)
{
	API_AttributeIndex attributeIndex;
	attributeIndex.attributeIndex  = index;
	return attributeIndex;
}


static_assert (GS::IsTriviallyCopyable<API_AttributeIndex>);
static_assert (sizeof (API_AttributeIndex) == sizeof (Int32));

static const API_AttributeIndex	APIInvalidAttributeIndex			= ACAPI_CreateAttributeIndex (0);
static const API_AttributeIndex	APIApplicationLayerAttributeIndex	= ACAPI_CreateAttributeIndex (1);
static const API_AttributeIndex	APISolidLineAttributeIndex			= ACAPI_CreateAttributeIndex (1);


#endif
