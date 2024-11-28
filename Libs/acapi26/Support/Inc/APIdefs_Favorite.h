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

struct API_Favorite {
	GS::UniString											name;
	API_Element												element;

	GS::Optional<API_ElementMemo>							memo;
	GS::Optional<API_Element>								elementMarker;
	GS::Optional<API_ElementMemo>							memoMarker;
	GS::Optional<GS::Array<API_Property>>					properties;
	GS::Optional<GS::Array<GS::Pair<API_Guid, API_Guid>>>	classifications;
	GS::Optional<GS::Array<API_ElemCategoryValue>>			elemCategoryValues;
	GS::Optional<API_FavoriteFolderHierarchy>				folder;
	GS::Optional<GS::Array<API_SubElement>>					subElements;

	API_Favorite (const GS::UniString& name = GS::EmptyUniString):
		name (name)
	{
		element = {};
	}
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
