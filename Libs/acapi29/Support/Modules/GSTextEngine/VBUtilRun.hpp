

// *****************************************************************************
//
//                                Class Run
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined VBUTILRUN_HPP
#define VBUTILRUN_HPP


// --------------------------------- Includes ----------------------------------
#include "Object.hpp"

#include "VBUtilCharStyle.hpp"
#include "IRun.hpp"
#include "TEBase.hpp"

// ============================== Class Run ==============================

namespace GS {
	class	XMLOChannel;
	class	XMLIChannel;
}

namespace VBUtil {


class TE_DLL_EXPORT Run : public TE::IRun, public GS::Object {
	DECLARE_CLASS_INFO

private:
	Int32				mFrom;
	Int32				mRange;
	VBUtil::CharStyle	mStyle;
	bool				mIntegrity;

public:
	inline Run (void);
	inline Run (const VBUtil::Run& source);

	virtual ~Run (void);

	inline Run&	operator= (const VBUtil::Run& source);

//  TE:IRun implementation [--------------------------

	// first character position
	virtual	Int32			GetFirstPos (void) const override;
	virtual	Int32			GetRange (void) const override;
	virtual	void			SetFirstPos (Int32 from) override;
	virtual	void			SetRange (Int32 range) override;
	virtual	TE::ICharStyle*	GetStyle (void) override;
	virtual	const TE::ICharStyle*	GetStyle (void) const override;

// ] TE:IRun implementation --------------------------

	inline	VBUtil::CharStyle*			GetStyleDirect (void);
	inline	const VBUtil::CharStyle*	GetStyleDirect (void) const;

	inline	void			Set (Int32 from, Int32 range, const VBUtil::CharStyle& style);
	inline	void			SetStyle (const VBUtil::CharStyle& style);

	inline  void			ScaleDown (double scale);

	inline	bool			IsIntegrate (void) const;
	inline	void			SetIntegrity (bool integrate);

// Object interface
	virtual	GSErrCode	Read		(GS::IChannel& ic) override;
	virtual	GSErrCode	Write		(GS::OChannel& oc) const override;
			GSErrCode	WriteXML	(GS::XMLOChannel& ox) const;
			GSErrCode	ReadXML		(GS::XMLIChannel& ix);
// For isolated state IO
			GSErrCode	Read		(GS::IChannel& ic, TE::IOMode ioMode);
			GSErrCode	Write		(GS::OChannel& oc, TE::IOMode ioMode) const;
};

inline Run::Run (void)
: mFrom (0), mRange (0), mIntegrity (true)
{
}

inline	Run::Run (const VBUtil::Run& source)
: mStyle (source.mStyle), mIntegrity (true)
{
	mFrom = source.mFrom;
	mRange = source.mRange;
}

inline Run&	Run::operator= (const VBUtil::Run& source)
{
	if (&source != this) {
		Set (source.GetFirstPos (), source.GetRange (), *source.GetStyleDirect ());
	}
	return *this;
}
	// first character position
inline	Int32	Run::GetFirstPos (void) const
{
	return mFrom;
}

inline	Int32	Run::GetRange (void) const
{
	return mRange;
}

inline	TE::ICharStyle*	Run::GetStyle (void)
{
	return GetStyleDirect ();
}

inline	const TE::ICharStyle*	Run::GetStyle (void) const
{
	return GetStyleDirect ();
}

inline	VBUtil::CharStyle*	Run::GetStyleDirect (void)
{
	return &mStyle;
}

inline	const VBUtil::CharStyle*	Run::GetStyleDirect (void) const
{
	return &mStyle;
}

inline	void	Run::Set (Int32 from, Int32 range, const VBUtil::CharStyle& style)
{
	SetFirstPos (from);
	SetRange (range);
	SetStyle (style);
}

inline	void	Run::SetFirstPos (Int32 from)
{
	if (mFrom != from) {
		mFrom = from;
		SetIntegrity (false);
	}
}

inline  void	Run::ScaleDown (double scale)
{
	(mStyle.GetFontDirect ())->ScaleDown (scale);
}

inline	void	Run::SetRange (Int32 range)
{
	if (mRange != range) {
		mRange = range;
		SetIntegrity (false);
	}
}

inline	void	Run::SetStyle (const VBUtil::CharStyle& style)
{
	mStyle = style;
}

inline	bool	Run::IsIntegrate (void) const
{
	if (!mIntegrity)
		return false;
	return mStyle.IsIntegrate ();
}

inline	void	Run::SetIntegrity (bool integrate)
{
	mIntegrity = integrate;
	if (integrate) {
		mStyle.SetIntegrity (integrate);
	}
}

}	// namespace VBUtil
// ______________________________ Class Run ______________________________

#endif
