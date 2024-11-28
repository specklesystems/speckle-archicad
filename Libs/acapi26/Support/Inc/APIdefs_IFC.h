// *********************************************************************************************************************
// API definitions - miscellaneous
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_IFC_H)
#define	APIDEFS_IFC_H

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "API_Guid.hpp"
#include "APIdefs_ElementDifferenceGenerator.h"
#include "Array.hpp"
#include "HashTable.hpp"

// --- Compiler settings -----------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

// --- Type definitions	------------------------------------------------------------------------------------------------

// =============================================================================
// IFC Partial Model
// =============================================================================


typedef struct {
	GS::HashTable<API_Guid, API_Guid>			containmentTable;
	GS::HashTable<API_Guid, API_Guid>			relFillsTable;
	GS::HashTable<API_Guid, API_Guid>			relVoidsTable;
	GS::HashSet<GS::Pair<API_Guid, API_Guid>>	assignmentTable;
	GS::HashTable<API_Guid, API_Guid>			typeProductTable;
} API_IFCRelationshipData;


typedef struct {
	API_ElemDifferenceGeneratorState	elemDifferenceGeneratorState;
	API_Guid							environmentChecksum;
	API_IFCRelationshipData				ifcRelationshipData;
	GS::HashTable<API_Guid, API_Guid>	elementIDToIFCGlobalId;
} API_IFCDifferenceGeneratorState;


typedef struct {
	API_Guid							ifcGlobalId;
	API_Guid							elementID;
} API_IFCEntityDescriptor;


typedef struct {
	GS::Array<API_IFCEntityDescriptor>		newIFCEntities;
	GS::Array<API_IFCEntityDescriptor>		modifiedIFCEntities;
	GS::Array<API_IFCEntityDescriptor>		deletedIFCEntities;
	bool									isValid;
} API_IFCDifference;


// ---------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif