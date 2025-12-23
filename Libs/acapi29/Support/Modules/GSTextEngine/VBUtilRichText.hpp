// *****************************************************************************
//
//                                Class RichText
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined VBUTILRICHTEXT_HPP
#define VBUTILRICHTEXT_HPP

// --------------------------------- Includes ----------------------------------

#include "Object.hpp"

#include "GSNew.hpp"
#include "UniString.hpp"
#include "VBUtilParagraph.hpp"
#include "IRichText.hpp"
#include "IConvertPen.hpp"
#include "Array.hpp"
#include "TEBase.hpp"
#include "CH.hpp"
#include <math.h>

// Undefine Windows Macros, we want to use "EnumFonts"

#if defined (WINDOWS)
#if defined (EnumFonts)
#undef EnumFonts
#endif
#endif

// ============================== Class RichText ==============================

namespace GS {
	class	XMLOChannel;
	class	XMLIChannel;
}

namespace VBUtil {

class	RichText;


class	TE_DLL_EXPORT IEnumRichTextObjects
{
public:
	enum EnumObjectID {eParagraphs, eRuns, eCharStyles, eFonts, eTabs};

private:
	EnumObjectID	enumType;

public:
	IEnumRichTextObjects (EnumObjectID enumObjType) : enumType (enumObjType) {}
	virtual ~IEnumRichTextObjects ();

	EnumObjectID	GetEnumType () const { return enumType; }
	virtual bool	EnumParagraphs (Int32 /*paragraphIndex*/, const VBUtil::Paragraph* /*paragraph*/) { return false; }
	virtual bool	EnumRuns (Int32 /*paragraphIndex*/, Int32 /*runIndex*/, const VBUtil::Run* /*run*/) { return false; }
	virtual bool	EnumStyles (Int32 /*paragraphIndex*/, Int32 /*runIndex*/, const VBUtil::CharStyle* /*style*/) { return false; }
	virtual bool	EnumFonts (Int32 /*paragraphIndex*/, Int32 /*runIndex*/, const VBUtil::Font* /*font*/) { return false; }
	virtual bool	EnumTabs (Int32 /*paragraphIndex*/, Int32 /*runIndex*/, const VBUtil::Tab* /*tab*/) { return false; }
};

//!!!!The base class (IRichText) contains rich text handler functions too.
//
//	For example:
//		virtual	Int32			GetNumOfLines (void) const;
//		virtual bool			ParagraphIndexFromPos (Int32 charPos, Int32* paragraphIndex) const;
//		virtual bool			RunIndexFromPos (Int32 charPos, Int32 *paragraphIndex, Int32* runIndex) const;
//		virtual	void			SimpleToRich (const GS::UniString& content, const short* lStarts= nullptr, Int32 lineNum = 0);
//		virtual	Int32			CopyAsSimple (GS::UniString* content, short* lStarts, EOLType typeOfParSeparator = EOL_CR) const;
//		virtual void			ConvertToANSI (IParagraph* copyOfUniParagraph) const;

class TE_DLL_EXPORT RichText : public TE::IRichText, public GS::Object {
	DECLARE_CLASS_INFO

	friend class VBUtil::Paragraph;

private:
	static double	mDefaultTab;
	static double	mDefaultTabScaled;
	double			mRotAngle;			/* Angle of text letters in rad */
	double			mWidthFactor;
	double			mCharSpaceFactor;
	double			mDefaultTabScaleDown;
	bool			mIsFixed;
	Int32			mCharCode;
	bool			mDefConversion;
	bool			mIntegrity;

	GS::UniString	mContent;
	GS::ArrayFB <VBUtil::Paragraph, 1>	mParagraphs;


	void			Associate (VBUtil::Paragraph* paragraph);
	inline	void	Associate (VBUtil::Tab* tab);
	inline	void	Associate (VBUtil::Run* run);

	VBUtil::CharStyle*			GetDefaultCharStyle (void);
	const VBUtil::CharStyle*	GetDefaultCharStyle (void) const;
	VBUtil::Paragraph*			GetDefaultParagraph (void);
	const VBUtil::Paragraph*	GetDefaultParagraph (void) const;

	VBUtil::Font*			GetFont (Int32 iParagraph, Int32 iRun) const;
	VBUtil::CharStyle*		GetCharStyle (Int32 iParagraph, Int32 iRun);
	const VBUtil::CharStyle*	GetCharStyle (Int32 iParagraph, Int32 iRun) const;
	bool					SetLineWidths (Int32 paragraphIndex, GS::Array <double>* tmplineLengths);

//  TE:IRichText implementation [--------------------------
	void	SetParagraph (Int32 paragraphIndex, const TE::IParagraph& paragraph) override;
	void	AddParagraph (const TE::IParagraph& paragraph) override;
// ] TE:IRichText implementation --------------------------

public:
	using	TE::IRichText::CreateParagraphs;
	//  ol - overlapped

	enum CheckErr { noErr = 0,
					pOverlap = 1,			// paragraph related errors
					pMissing = 2,
					pOverflow = 3,
					pImplicit = 4,
					pNoLine   = 5,
					pBadIndent = 6,

					rOverlap = 10,			// run related errors
					rMissing = 11,
					rOverflow = 12,
					rImplicit = 13,
					rBadPenId = 14,
					rBadSize = 15,
					rMissingFont = 16,

					eolOverlap = 20,		// end of line related errors

					tabOverlap = 30			// tab related errors
			  };


	RichText (void);
	RichText (const VBUtil::RichText& source);

	RichText (VBUtil::RichText&& source);

	RichText (const char* ansiContent);
	RichText (const char* ansiContent, const VBUtil::Paragraph& sampleParagraph);
	RichText (const GS::UniString& uniContent);
	RichText (const GS::UniString& uniContent, const VBUtil::Paragraph& sampleParagraph);

	~RichText (void) {}

	RichText&	operator= (const VBUtil::RichText& source);
	RichText&	operator= (VBUtil::RichText&& source);

	RichText&	operator+= (const  VBUtil::RichText& rText);

	void	Clear (bool clearParagraphs = true);
//  TE:IRichText implementation [--------------------------

	virtual	GS::UniString&	GetContent (void) override;
	virtual	const GS::UniString&	GetContent (void) const override;
	virtual	void	SetContent (const GS::UniString& content) override;

	virtual	double			GetRotAngle (void) const override;
	virtual	double			GetWidthFactor (void) const override;
	virtual	double			GetCharSpaceFactor (void) const override;
	virtual	double			GetDefaultTabScaleDown (void) const;
	virtual GSCharCode		GetGSCharCode (void) const override;
	virtual double			GetDefaultTab (void) const override;
	virtual bool			GetLineWidths (Int32 paragraphIndex, GS::Array <double>* lineLengths) override;
	virtual bool			GetLineWidths (Int32 paragraphIndex, GS::Array <double>* lineLengths) const override;

	virtual	Int32			GetNumOfParagraphs (void) const override;
	virtual	TE::IParagraph*	GetParagraph (Int32 paragraphIndex) override;
	virtual	const TE::IParagraph*	GetParagraph (Int32 paragraphIndex) const override;
	void	SetNumOfParagraphs (Int32 numOfParagraphs) override;

// ] TE:IRichText implementation --------------------------

	void	SetParagraph (Int32 paragraphIndex, const VBUtil::Paragraph& paragraph);
	void	AddParagraph (const VBUtil::Paragraph& paragraph);

	bool					LineWidthsIsAvailable () const;
	void					CalculateLineWidths ();
	void					SetIntegrity (bool integrate);

	GS::UniString		GetAllLines (bool delTrailSpaces, GS::UniChar eolSeparator = CharCR) const;

	bool				GetLinePos (Int32 lineIndex, Int32* from, Int32* lineRange) const;
	GS::UniString		GetLine (Int32 lineIndex, bool delTrailSpaces = false) const;

	void	CreateParagraphs (const VBUtil::Paragraph& sampleParagraph);

	inline	VBUtil::Paragraph*		GetParagraphDirect (Int32 paragraphIndex);
	inline	const VBUtil::Paragraph*		GetParagraphDirect (Int32 paragraphIndex) const;

	inline	void	SetRotAngle (double rotAngle);
	inline	void	SetWidthFactor (double widthFactor);
	inline	void	SetCharSpaceFactor (double charSpaceFactor);
	inline	void	SetDefaultTabScaleDown (double defaultTabScaleDown);
	inline	void	SetGSCharCode (GSCharCode charCode);

	inline	bool	IsFixed (void) const;
	inline	void	SetFixed (bool isFixed);

	void	SetDefaultColor  (const Gfx::Color color);
	const	Gfx::Color*	GetDefaultColor (void) const;

	void	SetDefaultPen  (Int32 penId);
	Int32	GetDefaultPen (void) const;

	void	SetDefaultEffects  (Int32 effects, Int32 mask = -1);
	Int32	GetDefaultEffects (void) const;

	void	SetDefaultFont (const VBUtil::Font& defFont);
	void	SetDefaultFont (const GS::UniString& fontName);

	void	GetDefaultFontName (GS::UniString *fontName) const;
	VBUtil::Font*	GetDefaultFont (void) const;

	void	SetDefaultSize (double size);
	double	GetDefaultSize (void) const;

	void	SetDefaultFontStyle (TE::IFont::FontStyle style, Int32 mask = -1);
	TE::IFont::FontStyle	GetDefaultFontStyle (void) const;

	void	SetDefaultJustification (TE::IParagraph::Justification	just);
	TE::IParagraph::Justification	GetDefaultJustification (void) const;

	void	SetDefaultLineSpacing (double lSpacingInModelUnit);
	double	GetDefaultLineSpacing (void) const;

	void			ScaleDown (double scale);

	void			Enumerate (IEnumRichTextObjects& enumObj) const;

	static	void	SetActDrawingScale (double scale);
	static	void	SetActWindowScale (double scale);
	static	void	SetActCustomScale (double scale);
	static	void	SaveActScales (void);
	static	void	SaveAndSetScales (double newDrawingScale, double newWindowScale, USize* level = nullptr);
	static	void	RestoreSavedScales (const USize* level = nullptr);

	static  void	SetDefaultTabs (double fixed, double scaled);

	inline	void	UseCustomConversion (void);
	inline	void	UseDefaultConversion (void);

	double	ModelUnit2Pixel (double dimensionInModelUnit) const;
	double	Pixel2ModelUnit (double dimensionInPixel) const;
	double	ModelUnit2TypoSize (const VBUtil::Font* font) const;
	double	TypoSize2ModelUnit (const VBUtil::Font* font, double typoSize) const;

	bool	GetExtentInPixel (double* height, double* width) const;
	bool	GetExtentInModelUnit (double* height, double* width) const;
	bool	CalcLineBreaks (double widthInModelUnit);

	RichText::CheckErr		CheckOnStructure (void) const;
	RichText::CheckErr		CheckOnStructure (double widthInModelUnit) const;

	static	void				SetPenConvObj (IConvertPen*	convObj);
	static	const IConvertPen*	GetPenConvObj (void);

	void	Append (const VBUtil::RichText& rText, Int32 fromParagraph = 0, Int32 numOfParagraph = 0);

	void	Reset (void);
	bool	IsMonoStyled (void) const;

// Object interface
	virtual	GSErrCode	Read	 (GS::IChannel& ic) override;
	virtual	GSErrCode	Write	 (GS::OChannel& oc) const override;
			GSErrCode	WriteXML (GS::XMLOChannel& ox) const;
			GSErrCode	ReadXML	 (GS::XMLIChannel& ix);
// For isolated state IO
			GSErrCode	Read	 (GS::IChannel& ic, TE::IOMode ioMode);
			GSErrCode	Write	 (GS::OChannel& oc, TE::IOMode ioMode) const;

	class TE_DLL_EXPORT SetActScalesGuard {
	private:
		USize level;
	public:
		SetActScalesGuard (double drawingScale, double windowScale) :
			level (0)
		{
			VBUtil::RichText::SaveAndSetScales (drawingScale, windowScale, &level);
		}

		~SetActScalesGuard ()
		{
			VBUtil::RichText::RestoreSavedScales (&level);
		}
	};

};

inline	GS::UniString&	RichText::GetContent (void)
{
	return mContent;
}

inline	const GS::UniString&	RichText::GetContent (void) const
{
	return mContent;
}

inline	double	RichText::GetRotAngle (void) const
{
	return mRotAngle;
}

inline	double	RichText::GetWidthFactor (void) const
{
	return mWidthFactor;
}

inline	double	RichText::GetCharSpaceFactor (void) const
{
	return mCharSpaceFactor;
}

inline	double	RichText::GetDefaultTabScaleDown (void) const
{
	return mDefaultTabScaleDown;
}

inline	Int32	RichText::GetNumOfParagraphs (void) const
{
	return mParagraphs.GetSize ();
}

inline	TE::IParagraph*	RichText::GetParagraph (Int32 paragraphIndex)
{
	return GetParagraphDirect (paragraphIndex);
}

inline	const TE::IParagraph*	RichText::GetParagraph (Int32 paragraphIndex) const
{
	return GetParagraphDirect (paragraphIndex);
}

inline	VBUtil::Paragraph*	RichText::GetParagraphDirect (Int32 paragraphIndex)
{
	return &mParagraphs [paragraphIndex];
}

inline	const VBUtil::Paragraph*	RichText::GetParagraphDirect (Int32 paragraphIndex) const
{
	return &mParagraphs [paragraphIndex];
}

inline	void	RichText::SetContent (const GS::UniString& content)
{
	mContent = content;
	mIntegrity = false;
}

inline	void	RichText::SetRotAngle (double rotAngle)
{
	mRotAngle = rotAngle;
}

inline	void	RichText::SetWidthFactor (double widthFactor)
{
	if (fabs (mWidthFactor - widthFactor) > 0.00000001) {
		mWidthFactor = widthFactor;
		mIntegrity = false;
	}
}

inline	void	RichText::SetCharSpaceFactor (double charSpaceFactor)
{
	if (fabs (mCharSpaceFactor - charSpaceFactor) > 0.00000001) {
		mCharSpaceFactor = charSpaceFactor;
		mIntegrity = false;
	}
}

inline	void	RichText::SetDefaultTabScaleDown (double defaultTabScaleDown)
{
	if (fabs (mDefaultTabScaleDown - defaultTabScaleDown) > 0.00000001) {
		mDefaultTabScaleDown = defaultTabScaleDown;
		mIntegrity = false;
	}
}

inline	bool	RichText::IsFixed (void) const
{
	return mIsFixed;
}

inline	void	RichText::SetFixed (bool isFixed)
{
	mIsFixed = isFixed;
}

inline	void	RichText::Associate (VBUtil::Tab* tab)
{
	tab->mParent = this;
}

inline	void	RichText::Associate (VBUtil::Run* run)
{
	((run->GetStyleDirect ())->GetFontDirect ())->mParent = this;
}

inline void	RichText::SetGSCharCode (GSCharCode charCode)
{
	mCharCode = static_cast <Int32> (charCode);
}

inline GSCharCode	RichText::GetGSCharCode (void) const
{
	return static_cast <GSCharCode> (mCharCode);
}

inline	void	RichText::UseCustomConversion (void)
{
	mDefConversion = false;
}

inline	void	RichText::UseDefaultConversion (void)
{
	mDefConversion = true;
}

}	// namespace VBUtil
// ______________________________ Class RichText ______________________________

#endif
