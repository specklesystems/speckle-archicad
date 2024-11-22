// =============================================================================
// Description:		  Process Control
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (PROCESSCONTROL_HPP)
#define PROCESSCONTROL_HPP


// ----------------------- Includes --------------------------------------------
#include "GSModelerExport.h"

// from GSRoot
#include "UniString.hpp"

// ----------------------- Class declaration -----------------------------------

namespace GS {
	class ProcessControl;
}

namespace ModelerAPI {


class GSMODELER_DLL_EXPORT ProcessControl {
	GS::ProcessControl& processControl;
public:
	ProcessControl (GS::ProcessControl& processControl);
	void	SetProcessName (const char* name);
	void	SetProcessName (const GS::UniString& name);
	bool	Canceled (void) const;
	void	WriteReport (const char* string);
	void	WriteReport (const GS::UniString& string);
	void	WriteError (const char* msg);
	void	WriteError (const GS::UniString& msg);
	short   GetReportLevel (void) const;
	GS::ProcessControl& GetProcessControl ();
};


} // namespace ModelerAPI


#endif
