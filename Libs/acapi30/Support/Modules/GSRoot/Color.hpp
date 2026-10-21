// *********************************************************************************************************************
// File:			Color.hpp
//
// Description:		Color class
// Module:			GSRoot
// Namespace:		Gfx
// Contact person:	BM
//
// *********************************************************************************************************************

#ifndef COLOR_HPP
#define COLOR_HPP

#pragma once


#include "Channel.hpp"
#include "XMLChannel.hpp"
#include "GSRootExport.hpp"
#include "ObjectState.hpp"


namespace Gfx {


// === Constants =======================================================================================================

inline constexpr UInt8  Opaque         = MaxUInt8;
inline constexpr UInt8  MaxAlpha       = MaxUInt8;
inline constexpr UShort OpaqueUShort   = MaxUShort;
inline constexpr UShort MaxAlphaUShort = MaxUShort;
inline constexpr float  OpaqueFloat    = 1.0f;
inline constexpr float  MaxAlphaFloat  = 1.0f;


// === class Color =====================================================================================================

class GSROOT_DLL_EXPORT Color {
public:
	enum UShortSelector { AsUShort };
	enum FloatSelector { AsFloat };

	static const Color	Transparent;

	static const Color	Black;
	static const Color	DarkGray;
	static const Color	Gray;
	static const Color	LightGray;
	static const Color	White;

	static const Color	Red;
	static const Color	Green;
	static const Color	Blue;

	static const Color	Cyan;
	static const Color	Magenta;
	static const Color	Yellow;

	constexpr Color ();
	constexpr Color (UInt8 r, UInt8 g, UInt8 b, UInt8 a = Opaque);
	Color (UShortSelector, UShort r, UShort g, UShort b, UShort a = OpaqueUShort);
	Color (FloatSelector, float r, float g, float b, float a = OpaqueFloat);

	constexpr void	Set (UInt8 r, UInt8 g, UInt8 b, UInt8 a = Opaque);
	void			Set (UShortSelector, UShort r, UShort g, UShort b, UShort a = OpaqueUShort);
	void			Set (FloatSelector, float r, float g, float b, float a = OpaqueFloat);

	constexpr void	SetRed   (UInt8 r);
	constexpr void	SetGreen (UInt8 g);
	constexpr void	SetBlue  (UInt8 b);
	constexpr void	SetAlpha (UInt8 a);

	void			SetRed   (UShortSelector, UShort r);
	void			SetGreen (UShortSelector, UShort g);
	void			SetBlue  (UShortSelector, UShort b);
	void			SetAlpha (UShortSelector, UShort a);

	void			SetRed   (FloatSelector, float r);
	void			SetGreen (FloatSelector, float g);
	void			SetBlue  (FloatSelector, float b);
	void			SetAlpha (FloatSelector, float a);

	constexpr UInt8	GetRed   () const;
	constexpr UInt8	GetGreen () const;
	constexpr UInt8	GetBlue  () const;
	constexpr UInt8	GetAlpha () const;

	UShort			GetRed   (UShortSelector) const;
	UShort			GetGreen (UShortSelector) const;
	UShort			GetBlue  (UShortSelector) const;
	UShort			GetAlpha (UShortSelector) const;

	float			GetRed   (FloatSelector) const;
	float			GetGreen (FloatSelector) const;
	float			GetBlue  (FloatSelector) const;
	float			GetAlpha (FloatSelector) const;

	constexpr bool	IsTransparent () const;
	constexpr bool	IsOpaque () const;

	bool			operator== (const Color& rightOp) const = default;

	GSErrCode		Read		(GS::IChannel& ic);
	GSErrCode		Write		(GS::OChannel& oc) const;
	GSErrCode		Restore		(const GS::ObjectState& os);
	GSErrCode		Store		(GS::ObjectState& os) const;
	GSErrCode		ReadXML		(GS::XMLIChannel& ic);
	GSErrCode		WriteXML	(GS::XMLOChannel& oc) const;

	ULong			GenerateHashValue () const;

private:
	UInt8			red;
	UInt8			green;
	UInt8			blue;
	UInt8			alpha;
};


// === Color inline methods ============================================================================================

constexpr Color::Color () :
	red   (0),
	green (0),
	blue  (0),
	alpha (Opaque)
{
}


constexpr Color::Color (UInt8 r, UInt8 g, UInt8 b, UInt8 a) :
	red   (r),
	green (g),
	blue  (b),
	alpha (a)
{
}


constexpr void	Color::Set (UInt8 r, UInt8 g, UInt8 b, UInt8 a)
{
	SetRed   (r);
	SetGreen (g);
	SetBlue  (b);
	SetAlpha (a);
}


constexpr void	Color::SetRed (UInt8 r)
{
	red = r;
}


constexpr void	Color::SetGreen (UInt8 g)
{
	green = g;
}


constexpr void	Color::SetBlue (UInt8 b)
{
	blue = b;
}


constexpr void	Color::SetAlpha (UInt8 a)
{
	alpha = a;
}


constexpr UInt8	Color::GetRed () const
{
	return red;
}


constexpr UInt8	Color::GetGreen () const
{
	return green;
}


constexpr UInt8	Color::GetBlue () const
{
	return blue;
}


constexpr UInt8	Color::GetAlpha () const
{
	return alpha;
}


constexpr bool	Color::IsTransparent () const
{
	return alpha == 0;
}


constexpr bool	Color::IsOpaque () const
{
	return alpha == Opaque;
}


inline ULong	Color::GenerateHashValue () const
{
	return ((ULong) red << 24) | ((ULong) green << 16) | ((ULong) blue << 8) | alpha;
}


// === Global functions ================================================================================================

GSROOT_DLL_EXPORT Color		MixColors (const Color& color1, const Color& color2, double amountOfColor1 = 0.5);


}	// namespace Gfx


#endif
