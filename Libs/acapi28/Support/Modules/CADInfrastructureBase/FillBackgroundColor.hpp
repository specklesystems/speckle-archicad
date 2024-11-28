// *****************************************************************************
// Generalized Fill background color.
// Contact: Antlia squad, BeA
// 
// *****************************************************************************

#ifndef GS_CADVISUALIZATION_FILLBACKGROUNDCOLOR_HPP
#define GS_CADVISUALIZATION_FILLBACKGROUNDCOLOR_HPP

// from CADVisualization
#include "CADInfrastructureExport.hpp"

// from GSRoot
#include "Variant.hpp"
#include "Color.hpp"


namespace CADVisualization {


class CADINFRASTRUCTURE_DLL_EXPORT FillBackgroundColor {
	GS::Variant<short, Gfx::Color> data;

public:
	FillBackgroundColor ();
	FillBackgroundColor (short penIndex);
	FillBackgroundColor (const Gfx::Color& color);
	FillBackgroundColor (const GS::Variant<short, Gfx::Color>& penOrColor);
	
	bool				IsPenColor ()  const	{ return data.Is<short> (); }
	bool				IsRGB ()	   const	{ return data.Is<Gfx::Color> (); }

	short				GetPenIndex () const	{ return data.Get<short> (); }
	const Gfx::Color&	GetRGB ()	   const	{ return data.Get<Gfx::Color> (); }

	bool				IsOpaque	() const;


	const GS::Variant<short, Gfx::Color>&	AsVariant () const	{ return data; }
	GS::Variant<short, Gfx::Color>&			AsVariant ()		{ return data; }
	operator GS::Variant<short, Gfx::Color>	()	const			{ return AsVariant (); }

	template<class T>	
	bool operator == (const T&						rhs)	const	{ return data == rhs;	   }
	bool operator == (const FillBackgroundColor&	rhs)	const	{ return data == rhs.data; }
	bool operator == (int							rhs)	const	{ return IsPenColor () && GetPenIndex () == rhs; }		// for literals

	template<class T>
	bool operator != (const T& rhs)			const	{ return !operator == (rhs); }

	ULong		GenerateHashValue ()		const	{ return data.GenerateHashValue (); }

	GSErrCode	Read  (GS::IChannel& ic);	
	GSErrCode	Write (GS::OChannel& oc) const;

	GSErrCode	ReadXML	 (GS::XMLIChannel& ic, const char* tagName);
	GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName) const;

	template <class T, class = GS::EnableIf<!GS::IsSame<T, FillBackgroundColor>>>
	friend bool operator == (const T& lhs, const FillBackgroundColor& color)
	{
		return color == lhs;
	}

	template <class T, class = GS::EnableIf<!GS::IsSame<T, FillBackgroundColor>>>
	friend bool operator != (const T& lhs, const FillBackgroundColor& color)
	{
		return color != lhs;
	}
};


}		// namespace CADVisualization

#endif	// GS_CADVISUALIZATION_FILLBACKGROUNDCOLOR_HPP