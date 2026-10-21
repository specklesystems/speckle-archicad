
// *****************************************************************************
//
//                                Class RichText
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined RICHTEXT_HPP
#define RICHTEXT_HPP

// --------------------------------- Includes ----------------------------------

#include "GSNew.hpp"
#include "UniString.hpp"
#include "Paragraph.hpp"
#include "IRichText.hpp"
#include "Array.hpp"
#include <math.h>

// ============================== Class RichText ==============================

//!!!!The base class (IRichText) contains rich text handler functions too.
//
//	For example:
//		virtual	long			GetNumOfLines (void) const;
//		virtual bool			ParagraphIndexFromPos (long charPos, long* paragraphIndex) const;
//		virtual bool			RunIndexFromPos (long charPos, long *paragraphIndex, long* runIndex) const;
//		virtual	void			SimpleToRich (const GS::UniString& content, const short* lStarts= nullptr, long lineNum = 0);
//		virtual	long			CopyAsSimple (GS::UniString* content, short* lStarts, EOLType typeOfParSeparator = EOL_CR) const;
//		virtual void			ConvertToANSI (IParagraph* copyOfUniParagraph) const;

namespace TE {

class CharStyle;


class TE_DLL_EXPORT RichText : public IRichText {

private:
	double			mRotAngle;
	double			mWidthFactor;
	double			mCharSpaceFactor;
	double			mDefTab;
	Int32			mCharCode;	// do not use this for string encoding. only for font information
	GS::UniString	mContent;
	bool			mIntegrity;

	GS::ArrayFB <Paragraph, 1>	mParagraphs;

public:
	RichText ();
	RichText (const IRichText& source);
	RichText (const RichText& source);

	~RichText (void) {}

	RichText&	operator= (const IRichText& source);
	RichText&	operator= (const RichText& source);

//	Begin IRichText implementation

	virtual	GS::UniString&			GetContent (void)		override { return mContent; }
	virtual	const GS::UniString&	GetContent (void) const	override { return mContent; }
	virtual void					SetContent (const GS::UniString& content) override
	{
		mContent = content;
		mIntegrity = false;
	}

	virtual double		GetRotAngle (void) const override { return mRotAngle; }
	virtual double		GetWidthFactor (void) const override { return mWidthFactor; }
	virtual double		GetCharSpaceFactor (void) const override { return mCharSpaceFactor; }
	virtual GSCharCode	GetGSCharCode (void) const override { return static_cast <GSCharCode> (mCharCode); }
	double				GetDefaultTab (void) const override;
	bool				GetLineWidths (Int32 paragraphIndex, GS::Array <double>* lineLengths) override;
	bool				GetLineWidths (Int32 paragraphIndex, GS::Array <double>* lineLengths) const override;

	virtual Int32		GetNumOfParagraphs (void) const override { return mParagraphs.GetSize (); }
	virtual IParagraph*	GetParagraph (Int32 paragraphIndex) override { return &mParagraphs [paragraphIndex]; }
	virtual const IParagraph*	GetParagraph (Int32 paragraphIndex) const override { return &mParagraphs [paragraphIndex]; }
	virtual void				SetNumOfParagraphs (Int32 numOfParagraphs) override
	{
		mParagraphs.SetSize (numOfParagraphs);
		mIntegrity = false;
	}

	virtual void	SetParagraph (Int32 paragraphIndex, const IParagraph& paragraph) override { mParagraphs [paragraphIndex] = paragraph; }
	virtual void	AddParagraph (const IParagraph& paragraph) override
	{
		mParagraphs.Push (paragraph);
		mIntegrity = false;
	}

//	End IRichText implementation

	inline void			SetRotAngle (double rotAngle);
	inline void			SetWidthFactor (double widthFactor);
	inline void			SetCharSpaceFactor (double charSpaceFactor);
	inline void			SetGSCharCode (GSCharCode charCode);
	inline void			SetDefaultTab (double defTab);

// Object interface
	virtual	GSErrCode	Read	(GS::IChannel& ic);
	virtual	GSErrCode	Write	(GS::OChannel& oc) const;

// Other
	void				SetStyle (const TE::CharStyle& style);
};

inline void		RichText::SetRotAngle (double rotAngle)
{
	mRotAngle = rotAngle;
}

inline void		RichText::SetWidthFactor (double widthFactor)
{
	if (fabs (mWidthFactor - widthFactor) > 0.0000001) {
		mWidthFactor = widthFactor;
		mIntegrity = false;
	}
}

inline void		RichText::SetCharSpaceFactor (double charSpaceFactor)
{
	if (fabs (mCharSpaceFactor - charSpaceFactor) > 0.0000001) {
		mCharSpaceFactor = charSpaceFactor;
		mIntegrity = false;
	}
}

inline void		RichText::SetDefaultTab (double defTab)
{
	mDefTab = defTab;
}

inline void	RichText::SetGSCharCode (GSCharCode charCode)
{
	DBASSERT (charCode != CC_UTF8 && charCode != CC_Default);	// M-261: because mCharCode is for font information not for string charCode.
	mCharCode = static_cast <Int32> (charCode);
}

}	// namespace TE
// ______________________________ Class RichText ______________________________

#endif
