
// *****************************************************************************
//
//                                Interface IRun
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined IRUN_HPP
#define IRUN_HPP


// --------------------------------- Includes ----------------------------------

#include "ICharStyle.hpp"

// ============================== Interface IRun ==============================

namespace TE {


class TE_DLL_EXPORT IRun {
public:

	virtual ~IRun (void);

	// first character position
	virtual	Int32		GetFirstPos (void) const = 0;
	virtual	Int32		GetRange (void) const = 0;
	virtual	ICharStyle*	GetStyle (void) = 0;
	virtual	const ICharStyle*	GetStyle (void) const = 0;
	virtual	void		SetFirstPos (Int32 from) = 0;
	virtual	void		SetRange (Int32 range) = 0;
};

}	// namespace TE
// ______________________________ Interface IRun ______________________________

#endif
