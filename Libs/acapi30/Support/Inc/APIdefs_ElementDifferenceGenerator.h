// *********************************************************************************************************************
// API definitions - managing elements difference generator
//
// Module:			API
// Namespace:		-
// *********************************************************************************************************************

#if !defined (APIDEFS_ELEMENTDIFFERENCEGENERATOR_H)
#define	APIDEFS_ELEMENTDIFFERENCEGENERATOR_H

#pragma once


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

/**
 * @brief Determines the type of the element difference generator method type.
 * @enum API_ElemDifferenceGeneratorTypeID
 * @ingroup DifferenceGenerator
 */
typedef enum {
/**
 * @brief Modification stamp based difference generator, operates only with file.
 */
	APIDiff_ModificationStampBased		= 'MSBD',

/**
 * @brief 3D model based difference generator.
 */
	APIDiff_3DModelBased				= '3DMB',

/**
 * @brief Project context based, gives a difference taking account of the connection between the elements.
 */
	APIDiff_ContextBased				= 'CBSD'
} API_ElemDifferenceGeneratorTypeID;


/**
 * @brief Common structure for the element difference generator components.
 * @struct API_ElemDifference
 * @ingroup DifferenceGenerator
 * @remarks This structure specifies element differences for the Element Difference Generator.
 *          You can get an element difference by the @ref ACAPI_DifferenceGenerator_GenerateDifference function.
 */
struct API_ElemDifference {

/**
 * @brief The new elements.
 * @var newElements
 */
	GS::HashSet<API_Guid>		newElements;

/**
 * @brief The modified elements.
 * @var modifiedElements
 */
	GS::HashSet<API_Guid>		modifiedElements;

/**
 * @brief The deleted elements.
 * @var deletedElements
 */
	GS::HashSet<API_Guid>		deletedElements;

/**
 * @brief True if any of the following is changed: the view or the settings of the view, project information or preferences, property definitions, geographical locations.
 * @var isEnvironmentChanged
 */
	bool						isEnvironmentChanged;

};


/**
 * @brief Determines the type of the element difference generator state type.
 * @enum API_ElemDifferenceGeneratorStateType
 * @ingroup DifferenceGenerator
 */
typedef enum {
/**
 * @brief The difference generator state will be saved in a file.
 */
	APIDiffState_InFile = 1,

/**
 * @brief The difference generator state will be saved in memory.
 */
	APIDiffState_InMemory,

/**
 * @brief To generate difference, use the current project.
 */
	APIDiffState_CurrentProject
} API_ElemDifferenceGeneratorStateType;


/**
 * @brief Common structure for the element difference generator state.
 * @struct API_ElemDifferenceGeneratorState
 * @ingroup DifferenceGenerator
 * @remarks This structure specifies the difference generator state.
 *          You can get an element state by the @ref ACAPI_DifferenceGenerator_GetState function, and use it in @ref ACAPI_DifferenceGenerator_GenerateDifference function.
 */
struct API_ElemDifferenceGeneratorState {

/**
 * @brief The type of the difference generator state.
 * @var stateType
 */
	API_ElemDifferenceGeneratorStateType	stateType;

/**
 * @brief The effective state of the difference generator, if the stateType is @c APIDiffState_InMemory.
 * @var stateHdl
 */
	GSHandle								stateHdl;

/**
 * @brief The path of the file, that will be used if the stateType is @c APIDiffState_InFile.
 * @var fileLocation
 */
	IO::Location							fileLocation;

/**
 * @brief The view guid, that will assure that the difference comes from used element change, not from the view settings. Used only in @c APIDiff_ContextBased generator.
 * @var viewGuid
 */
	API_Guid								viewGuid;

	API_ElemDifferenceGeneratorState () : stateHdl (nullptr), stateType (APIDiffState_CurrentProject), viewGuid (APINULLGuid) {}

/**
 * @brief Construct a new API_ElemDifferenceGeneratorState instance with the given stateHdl and set to @c APIDiffState_InMemory.
 * @param handle The effective state of the difference generator.
 */
	API_ElemDifferenceGeneratorState (GSConstHandle handle) : stateHdl (nullptr), stateType (APIDiffState_InMemory), viewGuid (APINULLGuid) { BMHandleToHandle (handle, &stateHdl); }

/**
 * @brief Construct a new API_ElemDifferenceGeneratorState instance with the given location and set to @c APIDiffState_InFile.
 * @param location The path of the file.
 */
	API_ElemDifferenceGeneratorState (const IO::Location& location) : stateHdl (nullptr), fileLocation (location), stateType (APIDiffState_InFile), viewGuid (APINULLGuid) {}
	~API_ElemDifferenceGeneratorState () { BMKillHandle (&stateHdl); }

/**
 * @brief Copy assignment operator (from a reference to another instance).
 * @param source The other API_ElemDifferenceGeneratorState instance.
 */
	void	operator= (const API_ElemDifferenceGeneratorState& source)
	{
		viewGuid = source.viewGuid;
		stateType = source.stateType;
		fileLocation = source.fileLocation;
		BMKillHandle (&stateHdl);
		BMHandleToHandle (source.stateHdl, &stateHdl);
	}

/**
 * @brief Move assignment operator (from a reference to another instance).
 * @param source The other API_ElemDifferenceGeneratorState instance.
 */
	void operator= (API_ElemDifferenceGeneratorState &&source)
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
