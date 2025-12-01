
// *****************************************************************************
//
//                                Class TextEngine
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined TEXTENGINE_HPP
#define TEXTENGINE_HPP


// --------------------------------- Includes ----------------------------------

#include "Array.hpp"
#include "HashTable.hpp"
#include "UniString.hpp"

#include "TEBase.hpp"
#include "ISystemFontHandler.hpp"

#include "Font.hpp"
#include "IRichText.hpp"
#include "DrawableDevice.hpp"
#include "FontFamilyEnumerator.hpp"
#include "FontFamilySubstituter.hpp"
#include "FontRegistryObserver.hpp"
#include "IOutlineBuilder.hpp"
#include "IGreekOutlineBuilder.hpp"
#include "IPlainTextBuilder.hpp"
#include "EventSource.hpp"
#include "Owner.hpp"


namespace IO {
class Location;
}

namespace TE {

class TextEngine;
class ITextEngineImp;
class FontFamilyInfo;
class FontFamilyInfoContainer;
class MacTextEngine;
class FontFamilySubstituterChain;
class FontIDContainer;

// ============================== Class TextEngine ==============================

TE_DLL_EXPORT extern TextEngine&	textEngine;	// single global textEngine instance


class TE_DLL_EXPORT TextEngine :	public ISystemFontHandler
{
	friend class MacTextEngine;
	friend class FontFamily;
	friend class TESet;

public:

	// struct for the func call GetVerticalTextExtents
	struct TextExtents {
				TextExtents (void) : fBaseLine (0), fHighestPix (0), fHighestCapI (0), lBaseLine (0), lLowestPix  (0) {};
		double fBaseLine;
		double fHighestPix;
		double fHighestCapI;
		double lBaseLine;
		double lLowestPix;
	};	// struct TextExtents

private:

		volatile bool									isInitialized; //for lazy init

		GS::Owner<ITextEngineImp>						imp;
		GS::Owner<FontFamilyInfoContainer>				fontFamilyInfoContainer;
		GS::Owner<FontIDContainer>						fontIDContainer;
		GS::Owner<FontFamilySubstituterChain>			substitutersChain;
		
		static TextEngine								singleton;		// singleton instance - don't use this instance directly!


								TextEngine ();

								TextEngine (const TextEngine& source);					// disabled
								TextEngine& operator= (const TextEngine& source);		// disabled

		bool					IsInitialized () const;
		void					InitializeIfNeed (void) const; // for lazy Init
		GSErrCode				InitScripts (void);

		void					DoEnumerateSystemFonts (void);

		const FontFamilyInfo*	CreateMissingFontFamilyInfo (const GS::UniString& localName, const GS::UniString& englishFullName, const GS::UniString& englishFamilyName, GSCharCode charCode) const;
		void					AddCharCodeToFontFamilyInfo (const FontFamilyInfo* ffi, const GSCharCode charCode) const;

		const FontFamilyInfo*	Substitute (const GS::UniString& name, GSCharCode charCode, bool* wasDefSubtitution) const;

		const FontFamilyInfo*	SearchForIO (FontFamilyInfo& info) const ;

		bool					GetDefaultFontFamilyInfo (const FontFamilyInfo** familyInfo, GSCharCode charCode = CC_Legacy) const;
		void					FillDefContent ();

		const FontFamilyInfo*	GetFontFamilyInfo (const GS::UniString& name, GSCharCode charCode) const;
		const FontFamilyInfo*	GetFontFamilyByMacFontIdentifier (const GS::UniString& macFontIdentifier) const;

		GS::Array <const FontFamilyInfo*>	GetSortedFontFamilyInfos (FontFamily::SortMode mode) const;


		// ISystemFontHandler
		virtual const FontFamilyInfo* FamilyFound (const FontFamilyInfo& familyInfo, const GS::Array<GS::UniString>* fullNames, const GS::Array<GS::UniString>* familyNames) override;
		virtual void AddToAllScripts (const GS::UniString& scriptName, GSCharCode charCode) override;
		virtual void AddToEnglishScripts (const GS::UniString& scriptName, GSCharCode charCode) override;
		virtual void ComplementWithPSName (const GS::UniString& localName, const GS::UniString& psName) override;

public:
							~TextEngine ();
	
	void					Init () const;

	void					Enumerate (FontFamilyEnumerator& fontFamilyEnumerator, FontFamily::SortMode mode = FontFamily::Unsort) const;
	void					EnumerateCollections (FontFamilyEnumerator& fontFamilyEnumerator, FontFamily::SortMode mode = FontFamily::Unsort) const;
	void					EnumerateFamilyGroup (FontFamilyEnumerator& fontFamilyEnumerator, FontFamily* aGroupMember, FontFamily::SortMode mode = FontFamily::Unsort) const;

	bool					GetDefaultFontFamily (FontFamily& ff, GSCharCode charCode = CC_Legacy) const;

	void					AddFontFamilySubstituter (FontFamilySubstituter* sub);
	void					DeleteFontFamilySubstituter (FontFamilySubstituter* sub);

	void					InitTemplateLocalizationTool (const IO::Location* loc);
	void					DestroyTemplateLocalizationTool ();
	bool					IsTemplateLocalizationOnProgress () const;
	bool					ReplaceSubstitutedFontNames (GS::UniString& str);
	bool					ReplaceSubstitutedFontScript (const GS::UniString& fontName, GSCharCode& charCode);
	bool					GetSubstitutedFontScript (GSCharCode& charCode);
	void					PrintSubstitutedFonts (void) const;

	bool					GetSimpleFontName (const GS::UniString& ansiFName, GS::UniString* simpleName, GSCharCode* charCode) const;

	bool					FontNameContainsScriptName (const GS::UniString& fontName, GS::UniString* rootName, GS::UniString* scriptName, GSCharCode* charCode) const;

	bool					GetEncodingName (GSCharCode charCode, GS::UniString* encodingName) const;

	void					SortFontFamilies (GS::Array <FontFamily>& array, FontFamily::SortMode mode = FontFamily::DefaultSort) const;

	bool					FontFromPostScriptFontName (const GS::UniString& psFontName, TE::Font* teFont) const;

	void					FontFamilyToId (const FontFamily& fontFamily, GSCharCode charCode, short* outFontId) const;
	bool					FontIdToFamily (short fontID, FontFamily* outFontFamily, GSCharCode* outCharCode) const;
	bool					FontNameToID (const GS::UniString& name, short *outID) const;
	bool					FontIDToName (short fontID, GS::UniString& outFontName);

	void					GetCharCodeAndFaceName (short fontId, GSCharCode* outCharCode, GS::UniString& outFaceName);
	Int32					GetSystemFontIDCount ();
	short					GetFontId (Int32 index) const;
	Int32					GetFontIndex (short fontId) const;
	Int32					GetFontIDCount () const;

	// Notification

	void					Attach (FontRegistryObserver& observer);
	void					Detach (FontRegistryObserver& observer);

	// Text processing options

	void					SetReadingOrder (bool rightToLeft);
	bool					IsReadingOrderRTL (void) const;

	void					SetAntialiased (bool antialiased);
	bool					IsAntialiased (void) const;

	// GS::UniString based text processing

	virtual Int32			MeasurePlainText (const GS::UniString& uString, const IFont& iFont, double* width);
	virtual Int32			DrawPlainText (const DrawableDevice& device, const GS::UniString& uString, const IFont& iFont,
								double baseLineX, double baseLineY, double angle, double scalefactor = 1.0);
	virtual Int32			DrawPlainMLText (const DrawableDevice& device, const GS::UniString& uString, const IFont& iFont,
								Int32 just, double top, double left, double width, double height, double angle, double scalefactor = 1.0);
	virtual Int32			OutlinePlainText (const GS::UniString& uString, const IFont& iFont, double baseLineX,
								double baseLineY, double angle, IOutlineBuilder& iBuilder);
	virtual Int32			TruncatePlainText (GS::UniString& uString, const IFont& iFont, double width, bool with3Dots = false, bool* changed = nullptr);

	// IRichText based text processing

	enum					Options {NoOpt = 0, BaseLine = 1};

	virtual Int32			GetHighestRunsCharStyle (const IRichText& rText, const ICharStyle*& iCharStyle);
	virtual Int32			CalcLineBreaks (IRichText& rText, double width);
	virtual Int32			MeasureRichText (const IRichText& rText, double* width, double* height, Int32 paragraphIndex = -1);
	virtual Int32			MeasureRichText (const IRichText& rText, GS::Array<double>& lineWidths, GS::Array<double>& lineHeights, Int32 paragraphIndex = -1);
	virtual Int32			MeasureParagraphLines (const IRichText& rText, Int32 paragraphIndex, GS::Array <double>* lineLengths);
	virtual Int32			DrawRichText (const DrawableDevice& device, const IRichText& rText,
								double left, double top, double width, Int32 options = NoOpt, double zoom = 1.0, double scalefactor = 1.0);
	virtual Int32			GreekDrawRichText (const DrawableDevice& device, const IRichText& rText,
								double left, double top, double width, Int32 options = NoOpt, double zoom = 1.0);
	virtual Int32			OutlineRichText (const IRichText& rText, double left, double top, double width, IOutlineBuilder& iBuilder, Int32 options = NoOpt);
	virtual Int32			GreekOutlineRichText (const IRichText& rText, double left, double top, double width, IGreekOutlineBuilder& iGreekBuilder, Int32 options = NoOpt, double zoom = 1.0);
	virtual Int32			DecomposeRichText (const IRichText& rText, double left, double top, double width, IPlainTextBuilder& iPTBuilder);

	virtual Int32			GetVerticalTextExtents (const IRichText& rText, TextExtents* textExtents);

};

}	// namespace TE
// ______________________________ Class TextEngine ______________________________

#endif
