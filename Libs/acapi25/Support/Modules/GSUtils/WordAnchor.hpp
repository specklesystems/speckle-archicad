#ifndef WORD_ANCHOR_HPP
#define WORD_ANCHOR_HPP

#pragma once

#include "Object.hpp"
#include "ClassInfo.hpp"

#include "GSUtilsExport.h"

class GSUTILS_DLL_EXPORT_CPP WordAnchor : public GS::Object {
	DECLARE_CLASS_INFO

public:
	enum class Horizontal {
		Left,
		Middle,
		Right
	};
	enum class Vertical {
		Bottom,
		Middle,
		Top
	};
	enum class Reference {
		FirstRow,
		TextBoxWithOffset,
		LastRow,
		TextBox
	};
private:
	Vertical	vertical;
	Reference	reference;
	Horizontal	horizontal;

public:
	WordAnchor ();
	WordAnchor (Vertical inVertical, Horizontal inHorizontal);
	WordAnchor (Vertical inVertical, Reference inReference, Horizontal inHorizontal);

	Vertical	GetVertical () const;
	Reference	GetReference () const;
	Horizontal	GetHorizontal () const;

	void		MirrorHorizontal ();
	void		MirrorVertical ();

	static WordAnchor		ConvertFromAC22Value (char legacyValue);
	static char				ConvertToAC22Value (const WordAnchor& value);
	static WordAnchor		ConvertFromGDLValue (char gdlValue);
	static char				ConvertToGDLValue (const WordAnchor& value);
	static WordAnchor		ConvertFromCornerId (char cornerId);
	static char				ConvertToCornerId (const WordAnchor& value);

	bool					operator== (const WordAnchor& other) const;
	bool					operator!= (const WordAnchor& other) const;

	virtual GSErrCode		Read (GS::IChannel& ic) override;
	virtual GSErrCode		Write (GS::OChannel& oc) const override;

	GSErrCode				ReadXML (GS::XMLIChannel& ic);
	GSErrCode				WriteXML (GS::XMLOChannel& oc) const;

private:
	GSErrCode				ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode				WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
};

#endif