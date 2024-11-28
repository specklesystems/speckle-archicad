// *****************************************************************************
// ExtendedPen  - possibility to override pen color
//
// Module:			GSUtils
// Namespace:		GSUtil
//
// *****************************************************************************

#if !defined (EXTENDEDPEN_HPP)
#define EXTENDEDPEN_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
#include "GSUtilsExport.h"

#include "Channel.hpp"
#include "XMLChannel.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

enum {
	AC_FirstPattern		= 32000,

	AC_GrayPattern      = AC_FirstPattern + 1,
	AC_BlackPattern     = AC_FirstPattern + 2,		/* sm043 100% heccs for Rooms */
	AC_WhitePattern     = AC_FirstPattern + 3,
	AC_SpecGrayPattern  = AC_FirstPattern + 4,
	AC_LightGrayPattern = AC_FirstPattern + 5,
	AC_DarkGrayPattern  = AC_FirstPattern + 6,

	AC_LastPattern		= AC_FirstPattern + 6,

	AC_NoPattern        = 32767
};

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace VBAttr {

enum SetMode {
	ClearColorOverride		= 0,
	KeepColorOverride		= 1
};

class GSUTILS_DLL_EXPORT_CPP ExtendedPen
{
	friend GSErrCode	Store	(GS::ObjectState& os, const ExtendedPen& pen);
	friend GSErrCode	Restore (const GS::ObjectState& os, ExtendedPen& pen);
public:
	explicit ExtendedPen ();
	explicit ExtendedPen (short penIndex);
	explicit ExtendedPen (short penIndex, short colorOverridePenIndex);
	ExtendedPen (const ExtendedPen& source);

	void		Set						(short penIndex, short colorOverridePenIndex);
	void		SetIndex				(short penIndex, SetMode mode = ClearColorOverride);
	void		SetColorIndex			(short colorOverridePenIndex);

	short		GetIndex				() const;
	short		GetColorIndex			() const;
	short		GetEffectiveColorIndex	() const;

	bool		IsColorOverridden		() const;
	bool		IsEqual					(const ExtendedPen& source) const;

	bool		operator==				(const ExtendedPen& source) const;
	bool		operator!=				(const ExtendedPen& source) const;

	GSErrCode	Read (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;

	GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tag);
	GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tag) const;

	GSErrCode	ReadXML (GS::XMLIChannel& ic);
	GSErrCode	WriteXML (GS::XMLOChannel& oc) const;

	GSErrCode	Store (GS::ObjectState& os) const;
	GSErrCode	Restore (const GS::ObjectState& os);

protected:
	short		penAtttributeIndex;
	short		colorOverridePenAtttributeIndex;
};

} // namespace VBAttr


#endif
