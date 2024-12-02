
// *****************************************************************************
//
//                                Class CharStyle
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined CHARSTYLE_HPP
#define CHARSTYLE_HPP


// --------------------------------- Includes ----------------------------------

#include "Font.hpp"
#include "ICharStyle.hpp"

// ============================== Class CharStyle ==============================

namespace TE {

class TE_DLL_EXPORT CharStyle : public ICharStyle {
private:
	void*		mUserData;
	Int32		mEffects;
	Gfx::Color	mColor;
	Font		mFont;
	bool		mIntegrity;

public:
	inline	CharStyle (void);
	inline	CharStyle (const ICharStyle& source);
	inline	CharStyle (const CharStyle& source);

	virtual	~CharStyle (void);

	inline	CharStyle&	operator= (const ICharStyle& source);
	inline	CharStyle&	operator= (const CharStyle& source);

	inline	bool operator== (const ICharStyle& rightOp) const;
	inline	bool operator== (const CharStyle& rightOp) const;
	inline	bool operator!= (const ICharStyle& rightOp) const;
	inline	bool operator!= (const CharStyle& rightOp) const;

	virtual Int32		GetEffects (void) const override { return mEffects; }
	virtual	Gfx::Color*	GetColor (void) override { return &mColor; }
	virtual	const Gfx::Color* GetColor (void) const override { return &mColor; }
	virtual	IFont*		GetFont (void) override { return &mFont; }
	virtual	const IFont*	GetFont (void) const override { return &mFont; }
	virtual	void*		GetUserData (void) const override { return mUserData; }

	inline 	void		Set (Int32 effects, const Gfx::Color& color, const IFont& font);
	inline 	void		SetEffects (Int32 effects);
	inline	void		SetColor (const Gfx::Color& color);
	inline	void		SetFont (const IFont& font);
	inline	void		SetUserData (void* uDat);
	inline	bool		IsIntegrate (void) const;
	inline	void		SetIntegrity (bool integrate);

// Object interface
	inline	GSErrCode	Read	(GS::IChannel& ic);
	inline	GSErrCode	Write	(GS::OChannel& oc) const;
};

inline	CharStyle::CharStyle (void)
: mUserData (0), mEffects (0), mIntegrity (true)
{
}

inline	CharStyle::CharStyle (const ICharStyle& source)
: mColor (*source.GetColor ()), mFont (*source.GetFont ()), mIntegrity (true)
{
	mEffects = source.GetEffects ();
	mUserData = source.GetUserData ();
}

inline	CharStyle::CharStyle (const CharStyle& source)
: mColor (source.mColor), mFont (source.mFont), mIntegrity (true)
{
	mEffects = source.mEffects;
	mUserData = source.mUserData;
}

inline	CharStyle&	CharStyle::operator= (const CharStyle& source)
{
	if (&source != this) {
		mColor     = source.mColor;
		mFont      = source.mFont;
		mEffects   = source.mEffects;
		mUserData  = source.mUserData;
		mIntegrity = source.mIntegrity;
	}
	return *this;
}

inline	CharStyle&	CharStyle::operator= (const ICharStyle& source)
{
	if (&source != this) {
		Set (source.GetEffects (), *source.GetColor (), *source.GetFont ());
		SetUserData (source.GetUserData ());
	}
	return *this;
}

inline	bool CharStyle::operator== (const ICharStyle& rightOp) const
{
	if (&rightOp == this)
		return true;
	return (mEffects == rightOp.GetEffects () &&
			mFont == *rightOp.GetFont () &&
			mColor == *rightOp.GetColor ());
}

inline	bool CharStyle::operator== (const CharStyle& rightOp) const
{
	if (&rightOp == this)
		return true;
	return (mEffects == rightOp.mEffects &&
			mFont    == rightOp.mFont &&
			mColor   == rightOp.mColor);
}

inline	bool CharStyle::operator!= (const ICharStyle& rightOp) const
{
	return !(operator== (rightOp));
}

inline	bool CharStyle::operator!= (const CharStyle& rightOp) const
{
	if (&rightOp == this)
		return false;
	return (mEffects != rightOp.mEffects ||
			mFont    != rightOp.mFont ||
			mColor   != rightOp.mColor);
}

inline 	void	CharStyle::Set (Int32 effects, const Gfx::Color& color, const IFont& font)
{
	SetEffects (effects);
	SetColor (color);
	SetFont (font);
}

inline 	void	CharStyle::SetEffects (Int32 effects)
{
	if (mEffects != effects) {
		mEffects = effects;
		SetIntegrity (false);
	}
}

inline	void	CharStyle::SetColor (const Gfx::Color& color)
{
	mColor.SetRed (color.GetRed ());
	mColor.SetGreen (color.GetGreen ());
	mColor.SetBlue (color.GetBlue ());
	mColor.SetAlpha (color.GetAlpha ());
}

inline	void	CharStyle::SetFont (const IFont& font)
{
	mFont = font;
}

inline	void	CharStyle::SetUserData (void* uDat)
{
	mUserData = uDat;
}

inline	bool	CharStyle::IsIntegrate (void) const
{
	if (!mIntegrity)
		return false;

	return mFont.IsIntegrate ();
}

inline	void	CharStyle::SetIntegrity (bool integrate)
{
	mIntegrity = integrate;
	if (integrate) {
		mFont.SetIntegrity (integrate);
	}
}


inline	GSErrCode	CharStyle::Read	(GS::IChannel& ic)
{
	ic.Read (mEffects);
	UChar r, g, b;
	ic.Read (r);
	ic.Read (g);
	ic.Read (b);
	mColor.Set (r, g, b);
	mFont.Read (ic);
	Int32	dummy;
	ic.Read (dummy);
	mUserData = 0;
	ic.Read (mIntegrity);

	return ic.GetInputStatus ();
}


inline	GSErrCode	CharStyle::Write	(GS::OChannel& oc) const
{
	oc.Write (mEffects);
	oc.Write (mColor.GetRed ());
	oc.Write (mColor.GetGreen ());
	oc.Write (mColor.GetBlue ());

	mFont.Write (oc);
	oc.Write ((Int32) 0);				// mUserData, for compatibility
	oc.Write (mIntegrity);

	return oc.GetOutputStatus ();
}


}	// namespace TE
// ______________________________ Class CharStyle ______________________________

#endif
