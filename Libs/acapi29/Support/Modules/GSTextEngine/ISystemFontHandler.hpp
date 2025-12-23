
// *****************************************************************************
//
//                                Class ISystemFontHandler
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	TP
//
// SG compatible
//
// *****************************************************************************


#if !defined ISYSTEMFONTHANDLER_HPP
#define ISYSTEMFONTHANDLER_HPP


// --------------------------------- Includes ----------------------------------
#include "TEBase.hpp"
#include "Array.hpp"
#include "CH.hpp"

// ==================== Interface ISystemFontHandler ====================

namespace TE {

class FontFamilyInfo;

class TE_DLL_EXPORT ISystemFontHandler {
public:
    virtual ~ISystemFontHandler ();
	virtual const FontFamilyInfo* FamilyFound (const TE::FontFamilyInfo& familyInfo, const GS::Array<GS::UniString>* fullNames, const GS::Array<GS::UniString>* familyNames) = 0;
	virtual void AddToAllScripts (const GS::UniString& scriptName, GSCharCode charCode) = 0;
	virtual void AddToEnglishScripts (const GS::UniString& scriptName, GSCharCode charCode) = 0;
	virtual void ComplementWithPSName (const GS::UniString& localName, const GS::UniString& psName) = 0;
};


}	// namespace TE
// ____________________ Interface ISystemFontHandler ____________________

#endif
