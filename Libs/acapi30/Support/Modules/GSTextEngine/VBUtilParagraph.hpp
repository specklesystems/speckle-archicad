
// *****************************************************************************
//
//                                Class Paragraph
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined VBUTILPARAGRAPH_HPP
#define VBUTILPARAGRAPH_HPP


// --------------------------------- Includes ----------------------------------

#include "Object.hpp"
#include "VBUtilTab.hpp"
#include "VBUtilRun.hpp"
#include "IParagraph.hpp"
#include "Array.hpp"
#include "TEBase.hpp"
#include <math.h>

namespace VBUtil { class RichText; }

// ============================== Class Paragraph ==============================

namespace GS {
	class	XMLOChannel;
	class	XMLIChannel;
}

namespace VBUtil {

typedef	GS::ArrayFB	<double, 2>	LineWidthArray;

class TE_DLL_EXPORT Paragraph : public TE::IParagraph, public GS::Object {
	DECLARE_CLASS_INFO

	friend class VBUtil::RichText;

private:
	Int32	mFrom;
	Int32	mRange;
	Int32	mJustification;
	double	mFirstIndentInModelUnit;
	double	mIndentInModelUnit;
	double	mRightIndentInModelUnit;
	double	mLineSpacingInModelUnit;
	bool	mIntegrity;

	GS::ArrayFB <Int32, 2>			mEolPositions;
	LineWidthArray					mLineWidthsInModelUnit;
	GS::ArrayFB <VBUtil::Run, 1>	mRuns;
	GS::ArrayFB <VBUtil::Tab, 1>	mTabs;

	VBUtil::RichText*				mParent;

//  TE:IParagraph implementation [--------------------------
	void				SetRun (Int32 runIndex, const TE::IRun& run) override;
	void				AddRun (const TE::IRun& run) override;
// ] TE:IParagraph implementation --------------------------

public:
	Paragraph (void);
	Paragraph (const VBUtil::Paragraph& source);
	Paragraph (VBUtil::Paragraph&& source);

	~Paragraph (void) {}

	Paragraph&	operator= (const VBUtil::Paragraph& source);
	Paragraph&	operator= (VBUtil::Paragraph&& source);

//  TE:IParagraph implementation [--------------------------

	virtual	Int32		GetFirstPos (void) const override;
	virtual	Int32		GetRange (void) const  override;

	virtual	void		SetFirstPos (Int32 firstPos) override;
	virtual	void		SetRange (Int32 range) override;

	virtual	Int32		GetJustification (void) const override;
	double				GetFirstIndent (void) const override;
	double				GetIndent (void) const override;
	double				GetRightIndent (void) const override;
	double				GetLineSpacing (void) const override;

	virtual	Int32		GetTabNum (void) const override;
	// From left to right, 0 based
	virtual	TE::ITab*	GetTab (Int32 tabIndex) override;
	virtual	const TE::ITab*	GetTab (Int32 tabIndex) const override;

	virtual	void		SetNumOfLines (Int32 numOfLines) override;
	// lineNum: 0 based
	virtual	void		SetEolPos (Int32 lineNum, Int32 eolPos) override;
	virtual	Int32		GetNumOfLines (void) const override;
	virtual	Int32		GetEolPos (Int32 lineNum) const override;
	bool				GetLineAbsPos (Int32 lineIndex, Int32* from, Int32* lineRange) const;
	GS::UniString		GetLine (Int32 lineIndex) const;

	virtual bool		LineWidthsIsAvailable (void) const override;
	virtual double		GetLineWidth (Int32 lineNum) const override;

	virtual	Int32		GetNumOfRuns (void) const override;
	// runNum: 0 based
	virtual	TE::IRun*		GetRun (Int32 runIndex) override;
	virtual	const TE::IRun*	GetRun (Int32 runIndex) const override;
	virtual void			SetNumOfRuns (Int32 numOfRuns) override;
	// runNum: 0 based
	virtual bool			IsIntegrate (void) const override;

// ] TE:IParagraph implementation --------------------------

	void				SetRun (Int32 runIndex, const VBUtil::Run& run);
	void				AddRun (const VBUtil::Run& run);

	void				SetIntegrity (bool integrate);

	inline	double		GetFirstIndentDirect (void) const;
	inline	double		GetIndentDirect (void) const;
	inline	double		GetRightIndentDirect (void) const;

	inline	double		GetLineSpacingDirect (void) const;


	inline	VBUtil::Tab*	GetTabDirect (Int32 tabIndex);
	inline	const VBUtil::Tab*	GetTabDirect (Int32 tabIndex) const;
	inline	VBUtil::Run*	GetRunDirect (Int32 runIndex);
	inline	const VBUtil::Run*	GetRunDirect (Int32 runIndex) const;

	inline	void		SetJustification (Int32 justification);

	inline	void		SetFirstIndent (double firstIndentInModelUnit);
	inline	void		SetIndent (double indentInModelUnit);
	inline	void		SetRightIndent (double rightIndent);

	inline	void		SetLineSpacing (double lineSpacingInModelUnit);

	void				SetTabNum (Int32 numOfTabs);
	// From left to right, 0 based
	inline	void		SetTab (Int32 tabIndex, const VBUtil::Tab& tab);

	void				Clear (void);
	void				AddTab (double posInModelUnit, Int32 type = TE::ITab::left);
	inline	void		AddEolPos (Int32 eolPos);

	inline LineWidthArray* GetLineWidthsDirect (void);
	inline const LineWidthArray* GetLineWidthsDirect (void) const;

	void				ScaleDown (double scale);

// Object interface
	virtual	GSErrCode	Read		(GS::IChannel& ic) override;
	virtual	GSErrCode	Write		(GS::OChannel& oc) const override;
			GSErrCode	WriteXML	(GS::XMLOChannel& ox) const;
			GSErrCode	ReadXML		(GS::XMLIChannel& ix);
// For isolated state IO
			GSErrCode	Read		(GS::IChannel& ic, TE::IOMode ioMode);
			GSErrCode	Write		(GS::OChannel& oc, TE::IOMode ioMode) const;
};

inline	Int32	Paragraph::GetFirstPos (void) const
{
	return mFrom;
}

inline	Int32	Paragraph::GetRange (void) const
{
	return mRange;
}

inline	Int32	Paragraph::GetJustification (void) const
{
	return mJustification;
}

inline	double	Paragraph::GetFirstIndentDirect (void) const
{
	return mFirstIndentInModelUnit;
}

inline	double	Paragraph::GetIndentDirect (void) const
{
	return mIndentInModelUnit;
}

inline	double	Paragraph::GetRightIndentDirect (void) const
{
	return mRightIndentInModelUnit;
}

inline	double	Paragraph::GetLineSpacingDirect (void) const
{
	return mLineSpacingInModelUnit;
}

inline	Int32	Paragraph::GetTabNum (void) const
{
	return mTabs.GetSize ();
}

inline	TE::ITab*	Paragraph::GetTab (Int32 tabIndex)
{
	return GetTabDirect (tabIndex);
}

inline	const TE::ITab*	Paragraph::GetTab (Int32 tabIndex) const
{
	return GetTabDirect (tabIndex);
}

inline	VBUtil::Tab*	Paragraph::GetTabDirect (Int32 tabIndex)
{
	return &mTabs [tabIndex];
}

inline	const VBUtil::Tab*	Paragraph::GetTabDirect (Int32 tabIndex) const
{
	return &mTabs [tabIndex];
}

inline	void	Paragraph::SetNumOfLines (Int32 numOfLines)
{
	if (mEolPositions.GetSize () != static_cast <USize> (numOfLines)) {
		mEolPositions.SetSize (numOfLines);
		SetIntegrity (false);
	}
}

inline	void	Paragraph::SetEolPos (Int32 lineNum, Int32 eolPos)
{
	if (mEolPositions [lineNum] != eolPos) {
		mEolPositions [lineNum] = eolPos;
		SetIntegrity (false);
	}
}

inline	Int32	Paragraph::GetNumOfLines (void) const
{
	return mEolPositions.GetSize () > 0 ? mEolPositions.GetSize () : 1;
}
	
inline	Int32	Paragraph::GetEolPos (Int32 lineNum) const
{
	if (GetNumOfLines () == 1) {
		return (mRange > 0 ? mRange - 1 : 0);
	}
	return mEolPositions [lineNum];
}

inline	Int32	Paragraph::GetNumOfRuns (void) const
{
	return mRuns.GetSize ();
}

inline	TE::IRun*	Paragraph::GetRun (Int32 runIndex)
{
	return GetRunDirect (runIndex);
}

inline	const TE::IRun*	Paragraph::GetRun (Int32 runIndex) const
{
	return GetRunDirect (runIndex);
}

inline	VBUtil::Run*	Paragraph::GetRunDirect (Int32 runIndex)
{
	return  &mRuns [runIndex];
}

inline	const VBUtil::Run*	Paragraph::GetRunDirect (Int32 runIndex) const
{
	return  &mRuns [runIndex];
}

inline	void	Paragraph::SetFirstPos (Int32 firstPos)
{
	if (mFrom != firstPos) {
		mFrom = firstPos;
		SetIntegrity (false);
	}
}

inline	void	Paragraph::SetRange (Int32 range)
{
	if (mRange != range) {
		mRange = range;
		SetIntegrity (false);
	}
}

inline	void	Paragraph::SetJustification (Int32 justification)
{
	if (mJustification != justification) {
		mJustification = justification;
		SetIntegrity (false);
	}
}

inline	void	Paragraph::SetFirstIndent (double firstIndentInModelUnit)
{
	if (fabs (mFirstIndentInModelUnit - firstIndentInModelUnit) > 0.0000001) {
		mFirstIndentInModelUnit = firstIndentInModelUnit;
		SetIntegrity (false);
	}
}

inline	void	Paragraph::SetIndent (double indentInModelUnit)
{
	if (fabs (mIndentInModelUnit - indentInModelUnit) > 0.00000001) {
		mIndentInModelUnit = indentInModelUnit;
		SetIntegrity (false);
	}
}

inline void		Paragraph::SetRightIndent (double rightIndentInModelUnit)
{
	if (fabs (mRightIndentInModelUnit - rightIndentInModelUnit) > 0.0000001) {
		mRightIndentInModelUnit = rightIndentInModelUnit;
		SetIntegrity (false);
	}
}

inline	void	Paragraph::SetLineSpacing (double lineSpacingInModelUnit)
{
	if (fabs (mLineSpacingInModelUnit - lineSpacingInModelUnit) > 0.0000001) {
		mLineSpacingInModelUnit = lineSpacingInModelUnit;
		SetIntegrity (false);
	}
}

inline	void	Paragraph::SetTab (Int32 tabIndex, const VBUtil::Tab& tab)
{
	mTabs [tabIndex] = tab;
}

inline	void	Paragraph::AddEolPos (Int32 eolPos)
{
	mEolPositions.Push (eolPos);
	SetIntegrity (false);
}

inline LineWidthArray*	Paragraph::GetLineWidthsDirect (void)
{
	return  &mLineWidthsInModelUnit;
}

inline const LineWidthArray*	Paragraph::GetLineWidthsDirect (void) const
{
	return  &mLineWidthsInModelUnit;
}

inline bool		Paragraph::LineWidthsIsAvailable (void) const
{
	return	(!mLineWidthsInModelUnit.IsEmpty () && IsIntegrate ());
}

}	// namespace VBUtil
// ______________________________ Class Paragraph ______________________________

#endif
