
// *****************************************************************************
//
//                                Interface ITab
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined ITAB_HPP
#define ITAB_HPP


// --------------------------------- Includes ----------------------------------

#include "TEBase.hpp"

// ============================== Interface ITab ==============================

namespace TE {

class TE_DLL_EXPORT ITab {
public:
	enum TabType {left, right, center, decimalpoint};

	virtual ~ITab (void);

	virtual double	GetPosition (void) const = 0;
	virtual Int32	GetType (void) const = 0;
};

}	// namespace TE
// ______________________________ Interface ITab ______________________________

#endif
