// *********************************************************************************************************************
// API definitions - managing listing data
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_LISTDATA_H)
#define	APIDEFS_LISTDATA_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Base.h"


// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// =============================================================================
// Listing data set
//
// =============================================================================

typedef struct {
	Int32							setIndex;
	Int32							compLibInd;
	Int32							descLibInd;
	Int32							unitLibInd;
	Int32							keyLibInd;
	Int32							critLibInd;
	Int32							listSetupLibInd;
	Int32							filler_1;
	char							setName[API_NameLen];
	Int32							filler_2[16];
} API_ListDataSetType;


// =============================================================================
// Listing data types and common header
//
// =============================================================================

typedef enum {
	API_ZombieListDataID,

	API_KeyID,
	API_UnitID,
	API_Obsolete_ComponentID,
	API_DescriptorID
} API_ListDataID;


typedef struct {
	API_ListDataID					typeID;
	Int32							setIndex;					// ListData set index
	Int32							index;
	Int32							filler_1;
} API_ListData_Head;


// =============================================================================
// Key
//
// =============================================================================

typedef struct {
	API_ListData_Head				head;
	char							code[API_DBCodeLen];
	char							name[API_DBNameLen];
	Int32							filler_1[8];
} API_KeyType;


// =============================================================================
// Unit
//
// =============================================================================

typedef struct {
	API_ListData_Head				head;
	char							code[API_DBCodeLen];
	char							name[API_DBCodeLen];
	Int32							filler_1[8];
} API_UnitType;


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

typedef struct {
	API_ListData_Head				head;
	char							code[API_DBCodeLen];
	char							keycode[API_DBCodeLen];
	char							name[API_DBNameLen];
	char							unitcode[API_DBCodeLen];
	char							dbSetName[API_DBCodeLen];
	double							quantity;
	short							unitRef;
	short							filler_1;
	Int32							filler_2[7];
} API_Obsolete_ComponentType;


// =============================================================================
// Descriptor
//
// =============================================================================

typedef struct {
	API_ListData_Head				head;
	char							code[API_DBCodeLen];
	char							keycode[API_DBCodeLen];
	char							dbSetName[API_DBCodeLen];
	char							**name;
	Int32							filler_1[9];
} API_DescriptorType;


// =============================================================================
// General data
//
// =============================================================================

typedef union {
	API_ListData_Head				header;

	API_KeyType						key;
	API_UnitType					unit;
	API_Obsolete_ComponentType		component;
	API_DescriptorType				descriptor;
} API_ListData;


// ---------------------------------------------------------------------------------------------------------------------

#endif
