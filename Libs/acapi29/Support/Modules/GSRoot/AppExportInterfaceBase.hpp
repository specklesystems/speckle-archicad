// *********************************************************************************************************************
// Base class for exporting interfaces from an application to its modules
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SA
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APPEXPORTINTERFACEBASE_H)
#define APPEXPORTINTERFACEBASE_H

#pragma once

#include "GSRootExport.hpp"

namespace GS {

// --- Type definitions	------------------------------------------------------------------------------------------------
class GSROOT_DLL_EXPORT AppExportInterfaceBase {
public:
	AppExportInterfaceBase ();
	virtual ~AppExportInterfaceBase ();
};
}	// namespace GSRoot

#endif
