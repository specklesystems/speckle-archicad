
// *****************************************************************************
//
//                      Application termination management
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined APPLICATIONTERMINATION_HPP
#define APPLICATIONTERMINATION_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"


// -----------------------------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ApplicationTerminationObserver {
public:
	virtual	~ApplicationTerminationObserver ();

	virtual void	SeriousErrorEncountered (const GS::Utf8Char* errorCategoryGuid, const GS::Utf8Char* errorDescriptionGuid, const GS::Utf8Char* errorDescription) = 0;
	virtual void	ApplicationTerminated	(const GS::Utf8Char* errorCategoryGuid, const GS::Utf8Char* terminateReasonGuid, const GS::Utf8Char* terminateReason, bool applicationError) = 0;
};

void	GSROOT_DLL_EXPORT RegisterApplicationTerminationObserver   (ApplicationTerminationObserver* observer);
void	GSROOT_DLL_EXPORT UnregisterApplicationTerminationObserver (ApplicationTerminationObserver* observer);

void	GSROOT_DLL_EXPORT SendApplicationTerminated	  (const GS::Utf8Char* errorCategoryGuid, const GS::Utf8Char* terminateReasonGuid, const GS::Utf8Char* terminateReason, bool applicationError = true);
void	GSROOT_DLL_EXPORT SendSeriousErrorEncountered (const GS::Utf8Char* errorCategoryGuid, const GS::Utf8Char* errorDescriptionGuid, const GS::Utf8Char* errorDescription);

}	// namespace GS


#endif
