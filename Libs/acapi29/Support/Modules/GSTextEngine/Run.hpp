
// *****************************************************************************
//
//                                Class Run
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined RUN_HPP
#define RUN_HPP


// --------------------------------- Includes ----------------------------------

#include "CharStyle.hpp"
#include "IRun.hpp"

// ============================== Class Run ==============================

namespace TE {


class TE_DLL_EXPORT Run : public IRun {
private:
	Int32		mFrom;
	Int32		mRange;
	CharStyle	mStyle;
	bool		mIntegrity;

public:
	inline	Run (void);
	inline	Run (const IRun& source);
	inline	Run (const Run& source);

	virtual ~Run (void);

	inline	Run&	operator= (const IRun& source);
	inline	Run&	operator= (const Run& source);

//	Begin IRun implementation
	// first character position
	virtual	Int32		GetFirstPos (void) const override { return mFrom; } 	// first character position
	virtual Int32		GetRange (void) const override { return mRange; }
	virtual	ICharStyle*	GetStyle (void) override { return &mStyle; }
	virtual	const ICharStyle*	GetStyle (void) const override { return &mStyle; }
	virtual	void		SetFirstPos (Int32 from) override 
	{
		if (mFrom != from) {
			mFrom = from;
			SetIntegrity (false);
		}
	}

	virtual	void		SetRange (Int32 range) override
	{
		if (mRange != range) {
			mRange = range;
			SetIntegrity (false);
		}
	}

//	End IRun implementation

	inline	void		Set (Int32 from, Int32 range, const ICharStyle& style);
	inline	void		SetStyle (const ICharStyle& style);
	inline	bool		IsIntegrate (void) const;
	inline	void		SetIntegrity (bool integrate);

// Object interface
	inline	GSErrCode	Read	(GS::IChannel& ic);
	inline	GSErrCode	Write	(GS::OChannel& oc) const;
};

inline	Run::Run (void)
: mFrom (0), mRange (0), mIntegrity (true)
{
}

inline	Run::Run (const IRun& source)
: mStyle (*source.GetStyle ()), mIntegrity (true)
{
	mFrom = source.GetFirstPos ();
	mRange = source.GetRange ();
}

inline	Run::Run (const Run& source)
: mStyle (source.mStyle), mIntegrity (true)
{
	mFrom = source.mFrom;
	mRange = source.mRange;
}

inline	Run&	Run::operator= (const Run& source)
{
	if (&source != this) {
		mFrom      = source.mFrom;
		mRange     = source.mRange;
		mStyle     = source.mStyle;
		mIntegrity = source.mIntegrity;
	}
	return *this;
}

inline	Run&	Run::operator= (const IRun& source)
{
	if (&source != this) {
		Set (source.GetFirstPos (), source.GetRange (), *source.GetStyle ());
	}
	return *this;
}

inline	void	Run::Set (Int32 from, Int32 range, const ICharStyle& style)
{
	SetFirstPos (from);
	SetRange (range);
	SetStyle (style);
}

inline	void	Run::SetStyle (const ICharStyle& style)
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

inline	GSErrCode	Run::Read	(GS::IChannel& ic)
{
	ic.Read (mFrom);
	ic.Read (mRange);
	mStyle.Read (ic);
	ic.Read (mIntegrity);

	return ic.GetInputStatus ();
}


inline	GSErrCode	Run::Write	(GS::OChannel& oc) const
{
	oc.Write (mFrom);
	oc.Write (mRange);
	mStyle.Write (oc);
	oc.Write (mIntegrity);

	return oc.GetOutputStatus ();
}


}	// namespace TE
// ______________________________ Class Run ______________________________

#endif
