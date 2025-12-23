
// *****************************************************************************
//
//                                Class FontFamilyEnumerator
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	TP
//
// SG compatible
//
// *****************************************************************************


#if !defined FONTFAMILYENUMERATOR_HPP
#define FONTFAMILYENUMERATOR_HPP


// --------------------------------- Includes ----------------------------------

#include "Object.hpp"
#include "FontFamily.hpp"

// ============================ Class FontFamilyEnumerator ==============================

namespace TE {

class TE_DLL_EXPORT FontFamilyEnumerator : public GS::Object {

protected:
	FontFamilyEnumerator ();
	~FontFamilyEnumerator ();

public:
	virtual void	FamilyFound (const FontFamily& family) = 0;

	virtual void	FamilyGroupFound (const FontFamily& /*regularFamily*/) {}
	virtual void	FamilyGroupEntered (const FontFamily& /*regularFamily*/) {}
	virtual void	FamilyGroupExited (const FontFamily& /*regularFamily*/) {}

	virtual void	CollectionFound (GS::UniString& /*collectionName*/) {}
	virtual void	CollectionEntered (GS::UniString& /*collectionName*/) {}
	virtual void	CollectionExited (GS::UniString& /*collectionName*/) {}
};


}	// namespace TE
// ___________________________ Class FontFamilyEnumerator ___________________________

#endif
