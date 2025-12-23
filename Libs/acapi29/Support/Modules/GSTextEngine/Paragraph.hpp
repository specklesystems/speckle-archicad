// *****************************************************************************
//
//                                Class Paragraph
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined PARAGRAPH_HPP
#define PARAGRAPH_HPP


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "Tab.hpp"
#include "Run.hpp"
#include "IParagraph.hpp"
#include "Array.hpp"
#include <math.h>


// ============================== Class Paragraph ==============================

namespace TE {

class CharStyle;

typedef	GS::ArrayFB	<double, 1>	LineWidthArray;

class TE_DLL_EXPORT Paragraph : public IParagraph	{
private:
	Int32	mFrom;
	Int32	mRange;
	Int32	mJustification;
	double	mFirstIndent;
	double	mIndent;
	double	mRightIndent;
	double	mLineSpacing;
	bool	mIntegrity;

	GS::ArrayFB <Int32, 1>	mEolPositions;
	LineWidthArray			mLineWidths;
	GS::ArrayFB <Run,  1>	mRuns;
	GS::ArrayFB <Tab,  1>	mTabs;

public:
	Paragraph (void);
	Paragraph (const IParagraph& source);
	Paragraph (const Paragraph& source);

	~Paragraph (void) {}

	Paragraph&	operator= (const IParagraph& source);
	Paragraph&	operator= (const Paragraph& source);

//	Begin IParagraph implementation

	virtual Int32	GetFirstPos (void) const override { return mFrom; }
	virtual Int32	GetRange	(void) const  override { return mRange; }

	virtual void		SetFirstPos (Int32 firstPos) override
	{
		if (mFrom != firstPos) {
			mFrom = firstPos;
			SetIntegrity (false);
		}
	}

	virtual void		SetRange (Int32 range) override
	{
		if (mRange != range) {
			mRange = range;
			SetIntegrity (false);
		}
	}

	virtual Int32	GetJustification (void) const override { return mJustification; }
	virtual double	GetFirstIndent (void) const override { return mFirstIndent; }
	virtual double	GetIndent (void) const override { return mIndent; }
	virtual double	GetRightIndent (void) const override { return mRightIndent; }
	virtual double	GetLineSpacing (void) const override { return mLineSpacing; }

	virtual Int32	GetTabNum (void) const override { return mTabs.GetSize (); }
	// From left to right, 0 based
	virtual ITab*	GetTab (Int32 tabIndex) override { return &mTabs [tabIndex]; }
	virtual const ITab*	GetTab (Int32 tabIndex) const override { return &mTabs [tabIndex]; }

	virtual void	SetNumOfLines (Int32 numOfLines) override
	{
		if (mEolPositions.GetSize () != static_cast <USize> (numOfLines)) {
			mEolPositions.SetSize (numOfLines);
			SetIntegrity (false);
		}
	}

	// lineNum: 0 based
	virtual void	SetEolPos (Int32 lineNum, Int32 eolPos) override
	{
		if (mEolPositions [lineNum] != eolPos) {
			mEolPositions [lineNum] = eolPos;
			SetIntegrity (false);
		}
	}

	virtual Int32	GetNumOfLines (void) const override { return mEolPositions.GetSize () > 0 ? mEolPositions.GetSize () : 1; }
	virtual Int32	GetEolPos (Int32 lineNum) const override
	{
		if (GetNumOfLines () == 1) {
			return (mRange > 0 ? mRange - 1 : 0);
		}
		return mEolPositions[lineNum];
	}

	virtual bool		LineWidthsIsAvailable (void) const override { return	(!mLineWidths.IsEmpty () && IsIntegrate ()); }
	virtual double	GetLineWidth (Int32 lineNum) const override
	{
		if (static_cast <USize>(lineNum) < mLineWidths.GetSize ()) {
			return mLineWidths [lineNum];
		}
		DBASSERT (lineNum == lineNum);
		return 0.0;
	}

	virtual Int32	GetNumOfRuns (void) const override { return mRuns.GetSize (); }
	// runNum: 0 based
	virtual IRun*	GetRun (Int32 runIndex) override { return  &mRuns [runIndex]; }
	virtual const IRun*	GetRun (Int32 runIndex) const override { return  &mRuns [runIndex]; }
	virtual void		SetNumOfRuns (Int32 numOfRuns) override
	{
		if (mRuns.GetSize () != static_cast <USize> (numOfRuns)) {
			mRuns.SetSize (numOfRuns);
			SetIntegrity (false);
		}
	}

	// runNum: 0 based
	virtual void	SetRun (Int32 runIndex, const IRun& run) override { mRuns [runIndex] = run; }
	virtual void	AddRun (const IRun& run) override
	{
		mRuns.Push (run);
		SetIntegrity (false);
	}

	bool			IsIntegrate (void) const override;

//	End IParagraph implementation

	void			SetIntegrity (bool integrate);

	inline void		SetJustification (Int32 justification);
	inline void		SetFirstIndent (double firstIndent);
	inline void		SetIndent (double indent);
	inline void		SetRightIndent (double rightIndent);
	inline void		SetLineSpacing (double lineSpacing);

	inline void		SetTabNum (Int32 numOfTabs);
	// From left to right, 0 based
	inline void		SetTab (Int32 tabIndex, const ITab& tab);
	void			Clear (void);
	inline void		AddTab (double pos, Int32 type = ITab::left);
	inline void		AddEolPos (Int32 eolPos);

	inline LineWidthArray* GetLineWidths (void);
	inline const LineWidthArray* GetLineWidths (void) const;

// Object interface
	inline	GSErrCode	Read	(GS::IChannel& ic);
	inline	GSErrCode	Write	(GS::OChannel& oc) const;

// Other
	void	SetStyle (const TE::CharStyle& style);

};

inline void		Paragraph::SetJustification (Int32 justification)
{
	if (mJustification != justification) {
		mJustification = justification;
		SetIntegrity (false);
	}
}

inline void		Paragraph::SetFirstIndent (double firstIndent)
{
	if (fabs (mFirstIndent - firstIndent) > 0.0000001) {
		mFirstIndent = firstIndent;
		SetIntegrity (false);
	}
}

inline void		Paragraph::SetIndent (double indent)
{
	if (fabs (mIndent - indent) > 0.0000001) {
		mIndent = indent;
		SetIntegrity (false);
	}
}

inline void		Paragraph::SetLineSpacing (double lineSpacing)
{
	if (fabs (mLineSpacing - lineSpacing) > 0.0000001) {
		mLineSpacing = lineSpacing;
		SetIntegrity (false);
	}
}

inline void		Paragraph::SetTabNum (Int32 numOfTabs)
{
	if (mTabs.GetSize () != static_cast <USize> (numOfTabs)) {
		mTabs.SetSize (numOfTabs);
		SetIntegrity (false);
	}
}

inline void		Paragraph::SetTab (Int32 tabIndex, const ITab& tab)
{
	mTabs [tabIndex] = tab;
}

inline void		Paragraph::AddTab (double pos, Int32 type)
{
	Tab	t;
	t.Set (pos, type);
	mTabs.Push (t);
}

inline void		Paragraph::AddEolPos (Int32 eolPos)
{
	mEolPositions.Push (eolPos);
	SetIntegrity (false);
}

inline void		Paragraph::SetRightIndent (double rightIndent)
{
	if (fabs (mRightIndent - rightIndent) > 0.0000001) {
		mRightIndent = rightIndent;
		SetIntegrity (false);
	}
}

inline LineWidthArray*	Paragraph::GetLineWidths (void)
{
	return  &mLineWidths;
}

inline const LineWidthArray*	Paragraph::GetLineWidths (void) const
{
	return  &mLineWidths;
}

inline	GSErrCode	Paragraph::Read	(GS::IChannel& ic)
{
	ic.Read (mFrom);
	ic.Read (mRange);
	ic.Read (mJustification);
	ic.Read (mFirstIndent);
	ic.Read (mIndent);
	ic.Read (mRightIndent);
	ic.Read (mLineSpacing);
	ic.Read (mIntegrity);

	USize	  size;
	GSErrCode errorCode = ic.Read (size);
	mEolPositions.SetSize (size);
	for (UIndex i = 0; i < size && errorCode == NoError; i++) {
		errorCode = ic.Read (mEolPositions[i]);
	}
	errorCode = ic.Read (size);
	mLineWidths.SetSize (size);
	for (UIndex i = 0; i < size && errorCode == NoError; i++) {
		errorCode = ic.Read (mLineWidths[i]);
	}
	errorCode = ic.Read (size);
	mRuns.SetSize (size);
	for (UIndex i = 0; i < size && errorCode == NoError; i++) {
		errorCode = mRuns[i].Read (ic);
	}
	errorCode = ic.Read (size);
	mTabs.SetSize (size);
	for (UIndex i = 0; i < size && errorCode == NoError; i++) {
		errorCode = mTabs[i].Read (ic);
	}

	return ic.GetInputStatus ();
}


inline	GSErrCode	Paragraph::Write	(GS::OChannel& oc) const
{
	oc.Write (mFrom);
	oc.Write (mRange);
	oc.Write (mJustification);
	oc.Write (mFirstIndent);
	oc.Write (mIndent);
	oc.Write (mRightIndent);
	oc.Write (mLineSpacing);
	oc.Write (mIntegrity);

	USize	  size = mEolPositions.GetSize ();
	oc.Write (size);
	for (UIndex i = 0; i < size; i++) {
		oc.Write (mEolPositions[i]);
	}
	size = mLineWidths.GetSize ();
	oc.Write (size);
	for (UIndex i = 0; i < size; i++) {
		oc.Write (mLineWidths[i]);
	}
	size = mRuns.GetSize ();
	oc.Write (size);
	for (UIndex i = 0; i < size; i++) {
		mRuns[i].Write (oc);
	}
	size = mTabs.GetSize ();
	oc.Write (size);
	for (UIndex i = 0; i < size; i++) {
		mTabs[i].Write (oc);
	}

	return oc.GetOutputStatus ();
}


}	// namespace TE
// ______________________________ Class Paragraph ______________________________

#endif
