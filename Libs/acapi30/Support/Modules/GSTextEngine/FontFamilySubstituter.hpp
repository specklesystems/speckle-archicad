
// *****************************************************************************
//
//                                Class FontFamilySubstituter
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	TP
//
// SG compatible
//
// *****************************************************************************


#if !defined FONTFAMILYSUBSTITUTER_HPP
#define FONTFAMILYSUBSTITUTER_HPP


// --------------------------------- Includes ----------------------------------

#include "Object.hpp"
#include "UniString.hpp"
#include "Array.hpp"

#include "TEBase.hpp"


// ============================== Class FontFamilySubstituter ==============================

namespace TE {


class TE_DLL_EXPORT FontFamilySubstituter : public GS::Object {

public:
	struct FontPair {
		GS::UniString	missingFontName;
		GSCharCode		missingFontScriptCode;
		GS::UniString	associatedFontName;
	};
				FontFamilySubstituter ();
	virtual	   ~FontFamilySubstituter ();

	virtual void	GetFontPairs (GS::Array <FontPair>& fontPairs) = 0;
};

// ______________________________ Class FontFamilySubstituter ______________________________

}	// namespace TE

#endif
