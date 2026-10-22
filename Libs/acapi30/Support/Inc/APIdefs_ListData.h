// *********************************************************************************************************************
// API definitions - managing listing data
//
// Module:			API
// Namespace:		-
// *********************************************************************************************************************

#if !defined (APIDEFS_LISTDATA_H)
#define	APIDEFS_LISTDATA_H

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Base.h"


// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// =============================================================================
// Listing data set
//
// =============================================================================

/**
 * @brief Representation of a listdata set.
 * @struct API_ListDataSetType
 * @ingroup OldListing
 * @remarks This structure is used when you get information about a set of the listing database. See the @ref ACAPI_OldListing_GetSet function.
 */
struct API_ListDataSetType {

/**
 * @brief Index of the set of the listing database
 * @var setIndex
 */
	Int32							setIndex;

/**
 * @brief Index of components library part
 * @var compLibInd
 */
	Int32							compLibInd;

/**
 * @brief Index of the descriptors library part
 * @var descLibInd
 */
	Int32							descLibInd;

/**
 * @brief Index of the units library part
 * @var unitLibInd
 */
	Int32							unitLibInd;

/**
 * @brief Index of the keys library part
 * @var keyLibInd
 */
	Int32							keyLibInd;

/**
 * @brief Index of the criteria library part
 * @var critLibInd
 */
	Int32							critLibInd;

/**
 * @brief Index of the list setup library part
 * @var listSetupLibInd
 */
	Int32							listSetupLibInd;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Name of the set of the listing database
 * @var setName
 */
	char							setName[API_NameLen];

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[16];

};


// =============================================================================
// Listing data types and common header
//
// =============================================================================

/**
 * @brief Possible types of a listdata item.
 * @ingroup OldListing
 * @remarks This enum is used when you get information about the listing database or use @c API_ListData. See
 * 			the @ref ACAPI_OldListing_Get, @ref ACAPI_OldListing_GetLocal, @ref ACAPI_OldListing_Search,
 * @ref ACAPI_OldListing_GetNum functions.
 */
typedef enum {
	/** A dummy value (0). */
	API_ZombieListDataID,

	/** Denotes a key listdata. */
	API_KeyID,

	/**  Denotes an unit listdata. */
	API_UnitID,

	/** Denotes a component listdata. */
	API_Obsolete_ComponentID,

	/** Denotes a descriptor listdata. */
	API_DescriptorID

} API_ListDataID;


/**
 * @brief Contains common information related to all listing component types.
 * @struct API_ListData_Head
 * @ingroup OldListing
 * @remarks This structure contains general information about a listdata.
 * 			Below you can find the types of the list data:
 * 			|Value|Meaning|
 * 			|-----|-------|
 * 			| @c API_ZombieListDataID | A dummy value (0). |
 * 			| @c API_KeyID | Denotes a key listdata. |
 * 			| @c API_UnitID | Denotes an unit listdata. |
 * 			| @c API_Obsolete_ComponentID | Denotes a component listdata. |
 * 			| @c API_DescriptorID | Denotes a descriptor listdata. |
 * @ref ACAPI_OldListing_Get, @ref ACAPI_OldListing_GetLocal, @ref ACAPI_OldListing_Search
 */
struct API_ListData_Head {

/**
 * @brief Type of the listdata
 * @var typeID
 */
	API_ListDataID					typeID;

/**
 * @brief Index of the list data set the component is in
 * @var setIndex
 */
	Int32							setIndex;

/**
 * @brief Index of the listdata in the set
 * @var index
 */
	Int32							index;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

};


// =============================================================================
// Key
//
// =============================================================================

/**
 * @brief Description of a key.
 * @struct API_KeyType
 * @ingroup OldListing
 * @remarks This structure is used when you get or search a key in the listing database. See the @ref ACAPI_OldListing_Get and @ref ACAPI_OldListing_Search functions.
 */
struct API_KeyType {

/**
 * @brief Contains the header information, including type, setIndex and index.
 * @var head
 */
	API_ListData_Head				head;

/**
 * @brief Key code.
 * @var code
 */
	char							code[API_DBCodeLen];

/**
 * @brief Name of the key.
 * @var name
 */
	char							name[API_DBNameLen];

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[8];

};


// =============================================================================
// Unit
//
// =============================================================================

/**
 * @brief Description of a unit.
 * @struct API_UnitType
 * @ingroup OldListing
 * @remarks This structure is used when you retrieve or search for a unit in the listing database. See the
 * @ref ACAPI_OldListing_Get and @ref ACAPI_OldListing_Search functions.
 */
struct API_UnitType {

/**
 * @brief Contains the header information, including type, setIndex and index.
 * @var head
 */
	API_ListData_Head				head;

/**
 * @brief Unit code.
 * @var code
 */
	char							code[API_DBCodeLen];

/**
 * @brief Unit name.
 * @var name
 */
	char							name[API_DBCodeLen];

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[8];

};


// =============================================================================
// Component
//
// =============================================================================

#define APIUnitRef_Piece			1
#define APIUnitRef_Length			2
#define APIUnitRef_Surface_A		3
#define APIUnitRef_Volume			4
#define APIUnitRef_Surface_B		5
#define APIUnitRef_Surface_C		6

/**
 * @brief Description of a component.
 * @struct API_Obsolete_ComponentType
 * @ingroup OldListing
 * @remarks This structure is obsolete. Use the new component API instead.
 *          This structure is used when you want to get the components of an element. These components are in the property objects of the element. See the @ref ACAPI_Element_GetComponents_Obsolete function.
 *          This structure is used when you get or search a component in the listing database. See the @ref ACAPI_OldListing_Get, @ref ACAPI_OldListing_GetLocal and @ref ACAPI_OldListing_Search functions.
 */
struct API_Obsolete_ComponentType {

/**
 * @brief Contains the header information, including type, setIndex and index.
 * @var head
 */
	API_ListData_Head				head;

/**
 * @brief Component code.
 * @var code
 */
	char							code[API_DBCodeLen];

/**
 * @brief Component key code.
 * @var keycode
 */
	char							keycode[API_DBCodeLen];

/**
 * @brief Component name.
 * @var name
 */
	char							name[API_DBNameLen];

/**
 * @brief Component unit code.
 * @var unitcode
 */
	char							unitcode[API_DBCodeLen];

/**
 * @brief Component's database set name.
 * @var dbSetName
 */
	char							dbSetName[API_DBCodeLen];

/**
 * @brief quantity (value) of the component
 * @var quantity
 */
	double							quantity;

/**
 * @brief unit type, see the APIUnitRef_xxx defines.
 * @var unitRef
 */
	short							unitRef;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[7];

};


// =============================================================================
// Descriptor
//
// =============================================================================

/**
 * @brief Description of a descriptor.
 * @struct API_DescriptorType
 * @ingroup OldListing
 * @remarks This structure is used when you get or search a descriptor in the listing database. See the @ref ACAPI_OldListing_Get, @ref ACAPI_OldListing_GetLocal and @ref ACAPI_OldListing_Search functions.
 *          Remember to dispose of the `name` handle when you are done.
 */
struct API_DescriptorType {

/**
 * @brief Contains the header information, including type, set index and index.
 * @var head
 */
	API_ListData_Head				head;

/**
 * @brief Descriptor code.
 * @var code
 */
	char							code[API_DBCodeLen];

/**
 * @brief Descriptor key code.
 * @var keycode
 */
	char							keycode[API_DBCodeLen];

/**
 * @brief Descriptor database set name.
 * @var dbSetName
 */
	char							dbSetName[API_DBCodeLen];

/**
 * @brief name of the descriptor
 * @var name
 */
	char							**name;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[9];

};


// =============================================================================
// General data
//
// =============================================================================

/**
 * @brief The representation of a listdata.
 * @union API_ListData
 * @ingroup OldListing
 * @remarks This union is used when you get or search in the listing database. See the @ref ACAPI_OldListing_Get,
 * @ref ACAPI_OldListing_GetLocal, @ref ACAPI_OldListing_Search functions.
 */
union API_ListData {

/**
 * @brief A common header for all the listdata types. It contains information which applies to all the listdata types.
 * @var header
 */
	API_ListData_Head				header;


/**
 * @brief a key listdata
 * @var key
 */
	API_KeyType						key;

/**
 * @brief an unit listdata
 * @var unit
 */
	API_UnitType					unit;

/**
 * @brief a component listdata
 * @var component
 */
	API_Obsolete_ComponentType		component;

/**
 * @brief a descriptor listdata
 * @var descriptor
 */
	API_DescriptorType				descriptor;

};


// ---------------------------------------------------------------------------------------------------------------------

#endif
