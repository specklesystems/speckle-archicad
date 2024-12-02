
// *****************************************************************************
//
//                                Class FontFamily
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined FONTFAMILY_HPP
#define FONTFAMILY_HPP


// --------------------------------- Includes ----------------------------------

#include "GSRoot.hpp"
#include "CH.hpp"
#include "Object.hpp"
#include "ObjectState.hpp"

#include "TEBase.hpp"
#include "TextEngineDefs.h"
#include "ForwardIterator.hpp"
#include <cstddef>


namespace GS {
	class UniString;
}

// ============================== Class FontFamily ==============================

namespace TE {

class FontFamilyInfo;
class TextOutUtils;

class TE_DLL_EXPORT FontFamily : public GS::Object {
	DECLARE_CLASS_INFO

public:
	enum SortMode { Unsort, DefaultSort, SortByName, SortByMac };
	enum StackingMode { Uninitialized, Stackable, NonStackable };
	
	typedef GS::ConstForwardIterator<GSCharCode>	CharCodeIterator;

private:
	const FontFamilyInfo*	content;

public:
				FontFamily ();
	explicit	FontFamily (const FontFamilyInfo* ffi);
	explicit	FontFamily (const GS::UniString& name, GSCharCode charCode = CC_Legacy);
				FontFamily (std::nullptr_t, const GS::UniString& macFontIdentifier);		// nullptr_t hogy meg tudja kulonboztetni a masik unistringestol
				FontFamily (const FontFamily& family);

	~FontFamily ();

	FontFamily&				operator= (const FontFamily& source);
	bool					operator== (const FontFamily& rightOp) const;
	bool					operator!= (const FontFamily& rightOp) const { return !(*this == rightOp); }

	const GS::UniString&	GetLocalName (void)	const;
	const GS::UniString&	GetActualLocalName (void) const;
	bool					GetFontNameWidthScriptName (GSCharCode charCode, GS::UniString& fontName) const;
	const GS::UniString&	GetMacFontIdentifier (void) const;
	const GS::UniString&	GetFamilyGroupName (void) const;
	const GS::UniString&	GetMacTypefaceName (void) const;

	double					GetMaxCharWidth (double typoSize) const;
	UShort					GetSpaceIndex (void) const;				// glyp index of " " (space) char

	double					GetCapISize (double typoSize) const;
	double					GetTypoSize (double capISize) const;

	double					GetAscent (double typoSize) const;
	double					GetDescent (double typoSize) const;
	double					GetLeading (double typoSize) const;

	ULong					GetEncodingsNum (void) const;
	GSCharCode				GetEncoding (UIndex index) const;
	CharCodeIterator		EnumerateEncodings (void) const;
	GSCharCode				GetFirstEncoding (void) const;
	ULong					GenerateHashValue () const;

	bool					IsSubstituted (void) const;

	GS::Int32				GetFamilyGroupID (void) const;		// mac only
	GS::Int32				GetFamilyMemberID (void) const;		// mac only
	GS::Int32				GetSuitValue (void) const;			// mac only

	double					GetAveCharWidth (double typoSize) const; //for FontHandler only
	UInt32					GetLangInfo (void) const;				 //for TextOutUtilsonly: fontfeature flags (Win speed)

	GSErrCode				Read (GS::IChannel& ic, GSCharCode	charCode = CC_Legacy, IOMode ioMode = NormalMode);
	GSErrCode				Write (GS::OChannel& oc, IOMode ioMode = NormalMode) const;

	virtual	GSErrCode		WriteXML (GS::XMLOChannel& oc) const;
	virtual	GSErrCode		ReadXML  (GS::XMLIChannel& ic);

	virtual GS::ErrorStatus	Store (GS::ObjectState& os) const override;

	static void				BeginInputSession (StackingMode pStackable = NonStackable);
	static void				EndInputSession (void);
	static void				BeginOutputSession (StackingMode pStackable = NonStackable);
	static void				EndOutputSession (void);

	static void				SetTEModeForWriteContentForChecksum (bool mode);


	struct [[nodiscard]] InputSessionScope {

		InputSessionScope (StackingMode mode = NonStackable)	{ BeginInputSession (mode); }
		~InputSessionScope ()									{ EndInputSession (); }
	};

	struct [[nodiscard]] OutputSessionScope {

		OutputSessionScope (StackingMode mode = NonStackable)	{ BeginOutputSession (mode); }
		~OutputSessionScope ()									{ EndOutputSession (); }
	};
};


}	// namespace TE
// ______________________________ Class FontFamily ______________________________

#endif
