#if !defined API_ATTRIBUTEINDEXUTILS_HPP
#define API_ATTRIBUTEINDEXUTILS_HPP

#if defined (_MSC_VER)
#pragma once
#endif

#include "APIdefs_Base.h"
#include "ADBAttributeIndex.hpp"

/**
 * @brief Converts an API_AttributeIndex to ADB::AttributeIndex
 * @ingroup Attribute
 * @since Archicad 27
 * @param apiIndex [in]
 * @return
 * 			- ADB::AttributeIndex
 */
inline ADB::AttributeIndex		API2AC_AttrIndex (const API_AttributeIndex& apiIndex)
{
	return ADB::CreateAttributeIndex (apiIndex.ToInt32_Deprecated ());
}


/**
 * @brief Converts an ADB::AttributeIndex to API_AttributeIndex
 * @ingroup Attribute
 * @since Archicad 27
 * @param acIndex [in]
 * @return
 * 			- API_AttributeIndex
 */
inline API_AttributeIndex		AC2API_AttrIndex (const ADB::AttributeIndex& acIndex)
{
	return ACAPI_CreateAttributeIndex (acIndex.ToGSAttributeIndex_Deprecated ());
}


#endif //  API_ATTRIBUTEINDEXUTILS_HPP
