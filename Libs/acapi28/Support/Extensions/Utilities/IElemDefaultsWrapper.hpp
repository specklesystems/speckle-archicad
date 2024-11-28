
#if !defined (IELEMDEFAULTSWRAPPER_HPP)
#define IELEMDEFAULTSWRAPPER_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace EDB {
	class IElemDefaults;
}

// --- Constant definitions --------------------------------------------------------------------------------------------

// --- Type definitions ------------------------------------------------------------------------------------------------

namespace Extensions {

namespace Utilities {

// =================== Class IElemDefaultsWrapper =====================
//
// Class for temporary switching the effective ElemDefaults of currDef via API
//
//==========================================================================

class IElemDefaultsWrapper {
public:
	IElemDefaultsWrapper ();
	virtual ~IElemDefaultsWrapper ();

private:
	EDB::IElemDefaults*		savedElemDefaults;
};


}	// namespace Utilities

}	// namespace Extensions


// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


#endif // IELEMDEFAULTSWRAPPER_HPP
