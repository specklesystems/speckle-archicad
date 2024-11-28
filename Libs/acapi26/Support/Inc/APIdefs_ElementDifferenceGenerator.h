// *********************************************************************************************************************
// API definitions - managing elements difference generator
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_ELEMENTDIFFERENCEGENERATOR_H)
#define	APIDEFS_ELEMENTDIFFERENCEGENERATOR_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// GSRoot
#include "HashSet.hpp"

// InputOutput
#include "Location.hpp"

// --- Compiler settings -----------------------------------------------------------------------------------------------


// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Predeclarations
// =============================================================================

// =============================================================================
// Function codes and parameter descriptions
//
// =============================================================================

typedef enum {
	APIDiff_ModificationStampBased		= 'MSBD',
	APIDiff_3DModelBased				= '3DMB',
	APIDiff_ContextBased				= 'CBSD'
} API_ElemDifferenceGeneratorTypeID;


typedef struct {
	GS::HashSet<API_Guid>		newElements;
	GS::HashSet<API_Guid>		modifiedElements;
	GS::HashSet<API_Guid>		deletedElements;
	bool						isEnvironmentChanged;
} API_ElemDifference;


typedef enum {
	APIDiffState_InFile = 1,
	APIDiffState_InMemory,
	APIDiffState_CurrentProject
} API_ElemDifferenceGeneratorStateType;


struct API_ElemDifferenceGeneratorState {
	API_ElemDifferenceGeneratorStateType	stateType;
	GSHandle								stateHdl;
	IO::Location							fileLocation;
	API_Guid								viewGuid;

	API_ElemDifferenceGeneratorState () : stateHdl (nullptr), stateType (APIDiffState_CurrentProject), viewGuid (APINULLGuid) {}
	API_ElemDifferenceGeneratorState (GSConstHandle handle) : stateHdl (nullptr), stateType (APIDiffState_InMemory), viewGuid (APINULLGuid) { BMHandleToHandle (handle, &stateHdl); }
	API_ElemDifferenceGeneratorState (const IO::Location& location) : stateHdl (nullptr), fileLocation (location), stateType (APIDiffState_InFile), viewGuid (APINULLGuid) {}
	~API_ElemDifferenceGeneratorState () { BMKillHandle (&stateHdl); }

	void	operator= (const API_ElemDifferenceGeneratorState& source)
	{
		viewGuid = source.viewGuid;
		stateType = source.stateType;
		fileLocation = source.fileLocation;
		BMKillHandle (&stateHdl);
		BMHandleToHandle (source.stateHdl, &stateHdl);
	}

	void	operator= (API_ElemDifferenceGeneratorState&& source)
	{
		viewGuid = source.viewGuid;
		stateType = source.stateType;
		fileLocation = source.fileLocation;
		BMKillHandle (&stateHdl);
		stateHdl = source.stateHdl;
		source.stateHdl = nullptr;
	}
};

#endif
