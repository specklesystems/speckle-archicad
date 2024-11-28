
// *****************************************************************************
//
//                                Class CharStyle
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined VBUTILCHARSTYLE_HPP
#define VBUTILCHARSTYLE_HPP

// --------------------------------- Includes ----------------------------------
#include "Object.hpp"
#include "VBUtilFont.hpp"
#include "ICharStyle.hpp"
#include "TEBase.hpp"
#include "IConvertPen.hpp"

// ============================== Class CharStyle ==============================

namespace GS {
	class XMLOChannel;
	class XMLIChannel;
}

namespace VBUtil {

class	RichText;
class	PenConvObjectGuard;

class TE_DLL_EXPORT CharStyle : public TE::ICharStyle, public GS::Object {
	DECLARE_CLASS_INFO

	friend class VBUtil::RichText;
	friend class VBUtil::PenConvObjectGuard;

	static	void				SetPenConvObj (IConvertPen*	convObj);
	static	const IConvertPen*	GetPenConvObj (void);

private:

	void*			mUserData;
	Int32			mEffects;
	Gfx::Color		mColor;
	VBUtil::Font	mFont;
	Int32			mPenId;
	bool			mIntegrity;

public:
	inline	CharStyle (void);
	inline	CharStyle (const VBUtil::CharStyle& source);

	~CharStyle (void);

	inline	CharStyle&	operator= (const VBUtil::CharStyle& source);
	inline	bool operator== (const VBUtil::CharStyle& rightOp) const;
	inline	bool operator!= (const VBUtil::CharStyle& rightOp) const;

//  TE:ICharStyle implementation [--------------------------
	virtual	Int32		GetEffects (void) const override;
	Gfx::Color*			GetColor (void) override;
	const Gfx::Color*	GetColor (void) const override;
	virtual	TE::IFont*	GetFont (void) override;
	virtual const TE::IFont*	GetFont (void) const override;
	virtual	void*		GetUserData (void) const override;

// ] TE:ICharStyle implementation --------------------------

	inline	VBUtil::Font*	GetFontDirect (void) const;
	inline	Int32		GetPenId (void) const;

	inline	void		Set (Int32 effects, const Gfx::Color& color, const VBUtil::Font& font);
	inline	void		Set (Int32 effects, Int32	penID, const VBUtil::Font& font);
	inline	void		SetEffects (Int32 effects);
	inline	void		SetColor (const Gfx::Color& color);
	inline	void		SetUserData (void* uDat);
	inline	void		SetFont (const VBUtil::Font& font);
	void				SetPenId (Int32	penID);

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

inline	CharStyle::CharStyle (void)
: mUserData (0), mEffects (0), mPenId (0), mIntegrity (true)
{
}

inline	CharStyle::CharStyle (const VBUtil::CharStyle& source)
: mColor (source.mColor), mFont (source.mFont), mIntegrity (true)
{
	mEffects = source.mEffects;
	mUserData = source.mUserData;
	mPenId = source.mPenId;
}

inline	CharStyle&	CharStyle::operator= (const VBUtil::CharStyle& source)
{
	if (&source != this) {
		SetEffects (source.GetEffects ());
		SetColor (*source.GetColor ());
		SetFont (*source.GetFontDirect ());
		SetUserData (source.GetUserData ());
		SetPenId (source.GetPenId ());
	}
	return *this;
}

inline	bool CharStyle::operator== (const VBUtil::CharStyle& rightOp) const
{
	if (&rightOp == this)
		return true;

	return (mEffects == rightOp.GetEffects () &&
			mPenId == rightOp.GetPenId () &&
			mFont == *rightOp.GetFontDirect ());
}

inline	bool CharStyle::operator!= (const VBUtil::CharStyle& rightOp) const
{
	return !(operator== (rightOp));
}

inline	Int32	CharStyle::GetEffects (void) const
{
	return mEffects;
}

inline	TE::IFont*	CharStyle::GetFont (void)
{
	return GetFontDirect ();
}

inline	const TE::IFont*	CharStyle::GetFont (void) const
{
	return GetFontDirect ();
}

inline	VBUtil::Font*	CharStyle::GetFontDirect (void) const
{
	return const_cast <VBUtil::Font*> (&mFont);
}

inline	void	CharStyle::Set (Int32 effects, const Gfx::Color& color, const VBUtil::Font& font)
{
	SetEffects (effects);
	SetColor (color);
	SetFont (font);
}

inline	void	CharStyle::Set (Int32 effects, Int32	penID, const VBUtil::Font& font)
{
	SetEffects (effects);
	SetPenId (penID);
	SetFont (font);
}

inline	void	CharStyle::SetEffects (Int32 effects)
{
	if (mEffects != effects) {
		mEffects = effects;
		SetIntegrity (false);
	}
}

inline	void	CharStyle::SetColor (const Gfx::Color& color)
{
	mColor.Set (color.GetRed (), color.GetGreen (), color.GetBlue (), color.GetAlpha ());
}

inline	void	CharStyle::SetFont (const VBUtil::Font& font)
{
	mFont = font;
}

inline	void	CharStyle::SetUserData (void* uDat)
{
	mUserData = uDat;
}

inline	void*	CharStyle::GetUserData (void) const
{
	return mUserData;
}

inline	Int32	CharStyle::GetPenId (void) const
{
	return	mPenId;
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

}	// namespace VBUtil
// ______________________________ Class CharStyle ______________________________

#endif
