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


/** @brief Contains IFC Entity relations which are specific for the IFC. The IFC Entities are represented by their GlobalId.
	@struct API_IFCRelationshipData
	@ingroup IFC
	@remarks This structure is used in @ref API_IFCDifferenceGeneratorState, @ref ACAPI_Markup_ImportFromBCF and @ref ACAPI_ProjectOperation_Save.
		The IFC containment tree (containmentTable) is in "child ->parent" format. Example: IfcBuilding ->IfcProject IfcSite ->IfcBuilding IfcBuildingStorey ->IfcBuilding IfcWall ->IfcBuildingStorey IfcBuildingElementPart ->IfcWall.
		The IFC assignmentTable set (assignmentTable) is in "child ->parent" format. Example: IfcWall ->IfcRelAssignsToGroup IfcRelAssignsToGroup ->IfcGroup.
		The IFC Type Products (typeProductTable) is in "child ->parent" format. Example: IfcWall ->IfcWallType.
*/
struct API_IFCRelationshipData {

/**	@brief IFC containment tree in "child->parent" format.
	@var containmentTable
*/
	GS::HashTable<API_Guid, API_Guid>			containmentTable;

/**	@brief Relationships between openings (Doors/Windows/Skylights) and IfcOpeningElements (voids).
	@var relFillsTable
*/
	GS::HashTable<API_Guid, API_Guid>			relFillsTable;

/**	@brief Relationships between IfcOpeningElements (voids) and their parent IfcWall or IfcSlab.
	@var relVoidsTable
*/
	GS::HashTable<API_Guid, API_Guid>			relVoidsTable;

/**	@brief IFC Assigment links, IfcGroup, IfcZone, IfcSystem, IfcRelAssignsToGroup and IfcRelServicesBuildings.
	@var assignmentTable
*/
	GS::HashSet<GS::Pair<API_Guid, API_Guid>>	assignmentTable;

/**	@brief IFC Type Products tree.
	@var typeProductTable
*/
	GS::HashTable<API_Guid, API_Guid>			typeProductTable;

};


/** @brief State used in IFCDifference Generator.
	@struct API_IFCDifferenceGeneratorState
	@ingroup IFC
	@since Archicad 26
*/
struct API_IFCDifferenceGeneratorState {

/**	@brief Element Difference Generator state.
	@var elemDifferenceGeneratorState
*/
	API_ElemDifferenceGeneratorState	elemDifferenceGeneratorState;

/**	@brief Environment checksum calculated from IFC Translator name, IFC Translator settings, IfcBuildingStorey core data, etc.
	@var environmentChecksum
*/
	API_Guid							environmentChecksum;

/**	@brief IFC Relationship Data.
	@var ifcRelationshipData
*/
	API_IFCRelationshipData				ifcRelationshipData;

/**	@brief ArchiCAD Guid and IFC Global Id table.
	@var elementIDToIFCGlobalId
*/
	GS::HashTable<API_Guid, API_Guid>	elementIDToIFCGlobalId;

};


/** @brief Contains IFC Global ID and Archicad ID of an IFC Entity.
	@struct API_IFCEntityDescriptor
	@ingroup IFC
*/
struct API_IFCEntityDescriptor {

/**	@brief IFC Global ID.
	@var ifcGlobalId
*/
	API_Guid							ifcGlobalId;

/**	@brief Archicad ID.
	@var elementID
*/
	API_Guid							elementID;

};


/** @brief Contains an IFC Difference.
	@struct API_IFCDifference
	@ingroup IFC
	@since Archicad 26
	@remarks This structure is used in @ref ACAPI_IFC_GetIFCDifference and @ref ACAPI_IFC_GetIFCDifferenceState.
*/
struct API_IFCDifference {

/**	@brief New IFC entities.
	@var newIFCEntities
*/
	GS::Array<API_IFCEntityDescriptor>		newIFCEntities;

/**	@brief Modified IFC entities.
	@var modifiedIFCEntities
*/
	GS::Array<API_IFCEntityDescriptor>		modifiedIFCEntities;

/**	@brief Deleted IFC entities.
	@var deletedIFCEntities
*/
	GS::Array<API_IFCEntityDescriptor>		deletedIFCEntities;

/**	 It is false if IFCDifference Generator result is indeterminate.
	@var isValid
*/
	bool									isValid;

};


// ---------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif