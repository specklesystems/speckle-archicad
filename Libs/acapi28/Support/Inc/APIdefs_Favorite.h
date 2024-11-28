// *********************************************************************************************************************
// API definitions - Favorite
//
// Module:			API
// Namespace:		-
// Contact person:	LT
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef APIDEFS_FAVORITE_H
#define	APIDEFS_FAVORITE_H

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Elements.h"
#include "APIdefs_Properties.h"
#include "APIdefs_Goodies.h"


// --- Compiler settings -----------------------------------------------------------------------------------------------


// --- Type definitions	------------------------------------------------------------------------------------------------

typedef GS::Array<GS::UniString> API_FavoriteFolderHierarchy;

/**
 * @brief A container for Favorite entry settings.
 * @struct API_Favorite
 * @ingroup Favorite
 * @since Archicad 25
 * @remarks In case of @ref ACAPI_Favorite_Get and @c ACAPI_Favorite_Change functions, you have to set the
 * 			name field for identifying the Favorite and set which optional fields do you want to retrieve/change. Remember
 * 			to call @ref ACAPI_DisposeElemMemoHdls for the `memo` and `memoMarker` fields if you set them and they are not needed
 * 			anymore. The `API_FavoriteFolderHierarchy` type is a typedef of `GS::Array <GS::UniString>`;. In Archicad 25
 * 			the `subElements` member was introduced.
 */
struct API_Favorite {

/**
 * @brief Unique name identifier of the Favorite.
 * @var name
 */
	GS::UniString											name;

/**
 * @brief The element settings of the Favorite.
 * @var element
 */
	API_Element												element;


/**
 * @brief (Optional) The element memo settings of the Favorite.
 * @var memo
 */
	GS::Optional<API_ElementMemo>							memo;

/**
 * @brief (Optional) The marker element settings of the Favorite.
 * @var elementMarker
 */
	GS::Optional<API_Element>								elementMarker;

/**
 * @brief (Optional) The marker element's memo settings of the Favorite.
 * @var memoMarker
 */
	GS::Optional<API_ElementMemo>							memoMarker;

/**
 * @brief (Optional) The properties of the Favorite.
 * @var properties
 */
	GS::Optional<GS::Array<API_Property>>					properties;

/**
 * @brief (Optional) The classification system and classification item pairs of the Favorite.
 * @var classifications
 */
	GS::Optional<GS::Array<GS::Pair<API_Guid, API_Guid>>>	classifications;

/**
 * @brief (Optional) The element categories of the Favorite.
 * @var elemCategoryValues
 */
	GS::Optional<GS::Array<API_ElemCategoryValue>>			elemCategoryValues;

/**
 * @brief (Optional) The folder of the Favorite.
 * @var folder
 */
	GS::Optional<API_FavoriteFolderHierarchy>				folder;

/**
 * @brief (Optional) The subelements of the Favorite (
 * @var subElements
 */
	GS::Optional<GS::Array<API_SubElement>>					subElements;

/**
 * @brief Construct a new API_Favorite object with the given name and zeroed-out element.
 * @param name Name of the favorite.
 */
	API_Favorite (const GS::UniString& name = GS::EmptyUniString):
		name (name)
	{

		element = {};
	}
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
