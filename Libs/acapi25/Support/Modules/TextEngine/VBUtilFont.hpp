
// *****************************************************************************
//
//                                Class Font
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined VBUTILFONT_HPP
#define VBUTILFONT_HPP


// --------------------------------- Includes ----------------------------------

#include "Object.hpp"
#include "FontFamily.hpp"
#include "IFont.hpp"
#include "TEBase.hpp"
#include <math.h>

namespace VBUtil { class RichText; }

// ============================== Class Font ==============================

namespace GS {
	class	XMLOChannel;
	class	XMLIChannel;
}

namespace VBUtil {

class TE_DLL_EXPORT Font : public TE::IFont, public GS::Object {
	DECLARE_CLASS_INFO

	friend class VBUtil::RichText;

private:
	Int32				mStyle;
	TE::FontFamily		mFamily;
	double				mSizeinModelUnit;
	VBUtil::RichText*	mParent;
	bool				mIntegrity;

public:
	Font (void);
	Font (const VBUtil::Font& source);

	~Font (void);

	inline Font&	operator= (const VBUtil::Font& source);
	inline	bool operator== (const VBUtil::Font& rightOp) const;
	inline	bool operator!= (const VBUtil::Font& rightOp) const;

//  TE:IFont implementation [--------------------------

	// return font size in typogr. unit
	virtual double			GetSize (void) const override;

	virtual Int32			   	  GetStyle (void) const override;
	virtual TE::FontFamily*		  GetFontFamily (void) override;
	virtual const TE::FontFamily* GetFontFamily (void) const override;

// ] TE:IFont implementation --------------------------

	// return font size in model unit (mm or pt)
	inline double			GetSizeDirect (void) const;

	inline void			Set (double sizeInModelUnit, Int32 style, const GS::UniString& fontName, GSCharCode charCode = CC_Legacy);
	inline void			Set (double sizeInModelUnit, Int32 style, const TE::FontFamily& family);
	inline void			Set (const VBUtil::Font& source);
	inline void			Set (const TE::FontFamily& family);

	inline void			SetSize (double sizeInModelUnit);

	inline void			SetStyle (Int32 style);
	inline void			SetFontName (const GS::UniString& fontName, GSCharCode charCode = CC_Legacy);

	void				GetFontName (GS::UniString* fontName) const;

	inline	void		ScaleDown (double scale);
	double				GetCapISize (double typoSize = 0.0) const;
	double				GetAscent (double typoSize = 0.0) const;
	double				GetDescent (double typoSize = 0.0) const;
	double				GetLeading (double typoSize = 0.0) const;
	void				GetEditPars (double* lineHeightInModelUnit, double* ascentInModelUnit = nullptr,
									 double* descentInModelUnit = nullptr, double* leadingInModelUnit = nullptr) const;

	inline	bool		IsIntegrate (void) const;
	inline	void		SetIntegrity (bool integrate);

// Object interface
	virtual	GSErrCode	Read		(GS::IChannel& ic) override;
	virtual	GSErrCode	Write		(GS::OChannel& oc) const override;
			GSErrCode	WriteXML	(GS::XMLOChannel& ox) const;
			GSErrCode	ReadXML		(GS::XMLIChannel& ix);
// For isolated state IO
			GSErrCode	Read		(GS::IChannel& ic, TE::IOMode ioMode);
			GSErrCode	Write		(GS::OChannel& oc, TE::IOMode ioMode) const;
};

inline	Font&	Font::operator= (const VBUtil::Font& source)
{
	if (&source != this) {
		Set (source.GetSizeDirect (), source.GetStyle (), source.mFamily);
	}
	return *this;
}

inline	bool Font::operator== (const VBUtil::Font& rightOp) const
{
	if (&rightOp == this)
		return true;

	return (rightOp.GetSizeDirect () == mSizeinModelUnit &&
			rightOp.GetStyle () == mStyle &&
			*rightOp.GetFontFamily () == mFamily);

}

inline	bool Font::operator!= (const VBUtil::Font& rightOp) const
{
	return !(operator== (rightOp));
}

inline	double	Font::GetSizeDirect (void) const
{
	return  mSizeinModelUnit;
}

inline	Int32	Font::GetStyle (void) const
{
	return  mStyle;
}

inline	TE::FontFamily*	Font::GetFontFamily (void)
{
	return &mFamily;
}

inline	const TE::FontFamily*	Font::GetFontFamily (void) const
{
	return static_cast <const TE::FontFamily*> (&mFamily);
}

inline	void	Font::Set (double sizeInModelUnit, Int32 style, const GS::UniString& fontName, GSCharCode charCode)
{
	SetSize (sizeInModelUnit);
	SetStyle (style);
	SetFontName (fontName, charCode);
}

inline void		Font::Set (double sizeInModelUnit, Int32 style, const TE::FontFamily& family)
{
	SetSize (sizeInModelUnit);
	SetStyle (style);
	Set (family);
}

inline void		Font::Set (const VBUtil::Font& source)
{
	operator= (source);
}

inline void		Font::Set (const TE::FontFamily& family)
{
	if (mFamily != family) {
		mFamily = family;
		SetIntegrity (false);
	}
}

inline	void	Font::SetSize (double sizeInModelUnit)
{
	if (fabs (mSizeinModelUnit - sizeInModelUnit) > 0.0000001) {
		mSizeinModelUnit = sizeInModelUnit;
		if (mSizeinModelUnit < 0)
			mSizeinModelUnit = -mSizeinModelUnit;
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
	TE::FontFamily tmpFamily (fontName, charCode);
	Set (tmpFamily);
}

inline	void	Font::ScaleDown (double scale)
{
	mSizeinModelUnit *= scale;
	SetIntegrity (false);
}

inline	bool	Font::IsIntegrate (void) const
{
	return mIntegrity;
}

inline	void	Font::SetIntegrity (bool integrate)
{
	mIntegrity = integrate;
}

}	// namespace VBUtil

// ______________________________ Class Font ______________________________

#endif
