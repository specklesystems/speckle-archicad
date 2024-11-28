
#include "IElemDefaultsWrapper.hpp"

// API
#include "ACAPinc.h"
#include "APIPrivateIntf.hpp"

// VBElements
#include "IElemDatabase.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

// --- Type definitions ------------------------------------------------------------------------------------------------


// --- Variable definitions --------------------------------------------------------------------------------------------

// --- Function definitions --------------------------------------------------------------------------------------------

// =====================================================================================================================
//
// Main Function group
//
// =====================================================================================================================

Extensions::Utilities::IElemDefaultsWrapper::IElemDefaultsWrapper () :
	savedElemDefaults (nullptr)
{
	ACAPI_Internal (APIInternal_StoreCurrentElemDefaultsID, &savedElemDefaults);
}


Extensions::Utilities::IElemDefaultsWrapper::~IElemDefaultsWrapper ()
{
	ACAPI_Internal (APIInternal_RestoreCurrentElemDefaultsID, &savedElemDefaults);
}