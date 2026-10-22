
// *****************************************************************************
//
//                                Class Font
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined FONT_HPP
#define FONT_HPP


// --------------------------------- Includes ----------------------------------

#include "TEBase.hpp"
#include "CH.hpp"
#include "FontFamily.hpp"
#include "IFont.hpp"
#include <math.h>

// ============================== Class Font ==============================

namespace TE {

class TE_DLL_EXPORT Font : public IFont {
private:
	Int32			mStyle;
	FontFamily		mFamily;
	double			mSize;
	bool			mIntegrity;

public:
	inline	Font (void);
	inline	Font (const IFont& source);
	inline	Font (const Font& source);

	virtual ~Font(void);

	inline	Font&	operator= (const IFont& source);
	inline	Font&	operator= (const Font& source);

	inline	bool operator== (const IFont& rightOp) const;
	inline	bool operator== (const Font& rightOp) const;
	inline	bool operator!= (const IFont& rightOp) const;
	inline	bool operator!= (const Font& rightOp) const;

	virtual	double	GetSize (void) const override { return  mSize; };
	inline	double	GetTypoSize (void) const { return GetSize (); }
	inline	double	GetCapISize (void) const;
	inline	double	GetAscent (void) const;
	inline	double	GetDescent (void) const;
	inline	double	GetLeading (void) const;

	GS::UniString	GetPSFontName (void) const;
	virtual	Int32	GetStyle (void) const override { return  mStyle; }
	virtual	FontFamily*	GetFontFamily (void) override { return &mFamily; }
	virtual	const FontFamily*	GetFontFamily (void) const override { return &mFamily; }

	inline	void	Set (double size, Int32 style, const GS::UniString& fontName, GSCharCode charCode = CC_Legacy);
	inline void		Set (const TE::FontFamily& family);

	inline	void	SetSize (double size);
	inline	void	SetTypoSize (double size) { return SetSize (size); }
	inline	void	SetCapISize (double size);
	inline	void	SetStyle (Int32 style);
	inline	void	SetFontName (const GS::UniString& fontName, GSCharCode charCode = CC_Legacy);
	inline	bool	IsIntegrate (void) const;
	inline	void	SetIntegrity (bool integrate);

// Object interface
	virtual GSErrCode	Read (GS::IChannel& ic, GSCharCode charCode = CC_Legacy, IOMode ioMode = NormalMode);
	virtual	GSErrCode	Write (GS::OChannel& oc, IOMode ioMode = NormalMode) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const;
};

inline	Font::Font (void)
: mStyle (IFont::normal), mSize (12.0), mIntegrity (true)
{
}

inline	Font::Font (const IFont& source)
: mFamily (*source.GetFontFamily ()), mIntegrity (true)
{
	mStyle = source.GetStyle ();
	mSize = source.GetSize ();
}

inline	Font::Font (const Font& source)
: mFamily (source.mFamily), mIntegrity (true)
{
	mStyle = source.mStyle;
	mSize = source.mSize;
}

inline	Font&	Font::operator= (const Font& source)
{
	if (&source != this) {
		mFamily    = source.mFamily;
		mStyle     = source.mStyle;
		mSize      = source.mSize;
		mIntegrity = source.mIntegrity;
	}
	return *this;
}

inline	Font&	Font::operator= (const IFont& source)
{
	if (&source != this) {
		SetSize (source.GetSize ());
		SetStyle (source.GetStyle ());
		Set (*source.GetFontFamily ());
	}
	return *this;
}

inline	bool Font::operator== (const IFont& rightOp) const
{
	if (&rightOp == this)
		return true;

	return (rightOp.GetSize () == GetSize () &&
			rightOp.GetStyle () == mStyle &&
			*rightOp.GetFontFamily () == mFamily);
}

inline	bool Font::operator== (const Font& rightOp) const
{
	if (&rightOp == this)
		return true;

	return (rightOp.mSize == mSize &&
			rightOp.mStyle == mStyle &&
			rightOp.mFamily == mFamily);
}

inline	bool Font::operator!= (const IFont& rightOp) const
{
	return !(operator== (rightOp));
}

inline	bool Font::operator!= (const Font& rightOp) const
{
	if (&rightOp == this)
		return false;

	return (rightOp.mSize != mSize ||
			rightOp.mStyle != mStyle ||
			rightOp.mFamily != mFamily);
}


inline	double	Font::GetCapISize (void) const
{
	return mFamily.GetCapISize (mSize);
}

inline	double	Font::GetAscent (void) const
{
	return mFamily.GetAscent (mSize);
}

inline	double	Font::GetDescent (void) const
{
	return mFamily.GetDescent (mSize);
}

inline	double	Font::GetLeading (void) const
{
	return mFamily.GetLeading (mSize);
}

inline	void	Font::Set (double size, Int32 style, const GS::UniString& fontName, GSCharCode charCode)
{
	SetSize (size);
	SetStyle (style);
	SetFontName (fontName, charCode);
}

inline void		Font::Set (const TE::FontFamily& family)
{
	if (mFamily != family) {
		mFamily = family;
		SetIntegrity (false);
	}
}

inline	void	Font::SetSize (double size)
{
	if (fabs (mSize - size) > 0.00000001) {
		mSize = size;
		if (mSize < 0)
			mSize = -mSize;
		SetIntegrity (false);
	}
}

inline	void	Font::SetCapISize (double size)
{
	double tmpSize = mFamily.GetTypoSize (size);
	if (fabs (mSize - tmpSize) > 0.00000001) {
		mSize = tmpSize;
		SetIntegrity (false);
	}
}

inline	void	Font::SetStyle (Int32 style)
{
	if (mStyle != style) {
		mStyle = style;
		SetIntegrity (false);
	}
}

inline	void	Font::SetFontName (const GS::UniString& fontName, GSCharCode charCode)
{
	FontFamily tmpFamily (fontName, charCode);
	Set (tmpFamily);
}

inline	bool	Font::IsIntegrate (void) const
{
	return mIntegrity;
}

inline	void	Font::SetIntegrity (bool integrate)
{
	mIntegrity = integrate;
}

}	// namespace TE
// ______________________________ Class Font ______________________________

#endif
