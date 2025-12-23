// *****************************************************************************
// GS::UnID is the world wide unique identifier of a LibPart.
//
// Namespace:		GS
// Contact person:	FGY
//
// SG compatible
// *****************************************************************************

#if !defined (GSUNID_HPP)
#define GSUNID_HPP

#pragma once

// from GSRoot
#include "GSGuid.hpp"
#include "XMLChannel.hpp"
#include "UniCHar.hpp"

#ifndef	GSUTILSEXPORT_H
	#include "GSUtilsExport.h"
#endif


// --- Defines	--------------------------------------------------------------------------------------------------------

#define XMLTag_MainGuid			"MainGuid"
#define XMLTag_RevGuid			"RevGuid"

namespace GS {

class UnID {

public:
	friend GS::OChannel& operator<< (GS::OChannel& oc, const UnID& guid);

private:
	GS::Guid	mainGuid;
	GS::Guid	revGuid;

public:
	UnID () = default;
	UnID (const GS::Guid& srcMainGuid, const GS::Guid& srcRevGuid);

	explicit UnID (const char* srcText);

	const GS::Guid&	GetMainGuid () const;
	const GS::Guid&	GetRevGuid () const;

	GSErrCode		Generate (void);
	GSErrCode		GenerateVariation (void);
	void			Clear (void);
	void			ClearRevPart (void);
	GSErrCode		ConvertToString (char *) const;
	GS::UniString	ToUniString () const;
	GSErrCode		ConvertFromString (const char *);
	GSErrCode		ConvertFromString (const GS::UniString&);

	bool			IsEqual (const UnID& b) const;
	Int32			Compare (const UnID& b) const;
	bool			IsMainPartEqual (const UnID& b) const;
	Int32			CompareMainPart (const UnID& b) const;

	ULong			GetHashValue () const;

	void            IV (GS::PlatformSign inplatform);
	void            IV (GS::PlatformSign inplatform, GS::PlatformSign toplatform);

	GSErrCode		Read (GS::IChannel& ic);
	GSErrCode		Write (GS::OChannel& oc) const;

	GSErrCode		ReadXML (GS::XMLIChannel& ic, const char* xmlTag = nullptr);
	GSErrCode		WriteXML (GS::XMLOChannel& oc, const char* xmlTag = nullptr) const;
	ULong			GenerateHashValue () const;
};


inline ULong UnID::GenerateHashValue () const
{
	return GetHashValue ();
}


inline UnID::UnID (const GS::Guid& srcMainGuid, const GS::Guid& srcRevGuid) :
	mainGuid (srcMainGuid),
	revGuid  (srcRevGuid)
{
}


inline UnID::UnID (const char* srcText) :
	mainGuid (),
	revGuid  ()
{
	ConvertFromString (srcText);
}


inline const GS::Guid&	UnID::GetMainGuid () const
{
	return mainGuid;
}


inline const GS::Guid&	UnID::GetRevGuid () const
{
	return revGuid;
}


inline GSErrCode UnID::Generate (void)
{
	GSErrCode	err = mainGuid.Generate ();
	if (err == NoError)
		err = revGuid.Generate ();
	return err;
}


inline GSErrCode UnID::GenerateVariation (void)
{
	return revGuid.Generate ();
}


inline void UnID::Clear (void)
{
	mainGuid.Clear ();
	revGuid.Clear ();
}


inline void UnID::ClearRevPart (void)
{
	revGuid.Clear ();
}


inline void UnID::IV (GS::PlatformSign inplatform)
{
	mainGuid.IV (inplatform);
	revGuid.IV (inplatform);
}


inline void UnID::IV (GS::PlatformSign inplatform, GS::PlatformSign toplatform)
{
	mainGuid.IV (inplatform, toplatform);
	revGuid.IV (inplatform, toplatform);
}


inline ULong UnID::GetHashValue () const
{
	return (((UInt32)mainGuid.GetHashValue ()) << 16) + revGuid.GetHashValue ();
}


inline GSErrCode UnID::Read (GS::IChannel& ic)
{
	GSErrCode errCode = mainGuid.Read (ic);
	if (errCode == NoError)
		errCode = revGuid.Read (ic);
	return errCode;
}


inline GSErrCode UnID::Write (GS::OChannel& oc) const
{
	GSErrCode errCode = mainGuid.Write (oc);
	if (errCode != NoError)
		return errCode;

	errCode = revGuid.Write (oc);
	if (errCode != NoError)
		return errCode;

	return NoError;
}


inline GSErrCode UnID::ReadXML (GS::XMLIChannel& ic, const char* xmlTag)
{
	GSErrCode errCode = ic.ReadXML (XMLTag_MainGuid, mainGuid);
	if (errCode == NoError) {
		if (xmlTag == nullptr)
			errCode = ic.ReadXML (XMLTag_RevGuid, revGuid);
		else
			errCode = ic.ReadXML (const_cast<char*>(xmlTag), revGuid);
	}
	return errCode;
}


inline GSErrCode UnID::WriteXML (GS::XMLOChannel& oc, const char* xmlTag) const
{
	GSErrCode errCode = oc.WriteXML (XMLTag_MainGuid, mainGuid);
	if (errCode == NoError) {
		if (xmlTag == nullptr)
			errCode = oc.WriteXML (XMLTag_RevGuid, revGuid);
		else
			errCode = oc.WriteXML (const_cast<char*>(xmlTag), revGuid);
	}

	return errCode;
}


inline bool UnID::IsEqual (const UnID& unid2) const
{
	bool isEqual = mainGuid.IsEqual (unid2.mainGuid);
	if (isEqual)
			isEqual = revGuid.IsEqual (unid2.revGuid);
	return isEqual;
}


inline Int32 UnID::Compare (const UnID& unid2) const
{
	Int32 cmp = mainGuid.Compare (unid2.mainGuid);
	if (cmp == 0)
			cmp = revGuid.Compare (unid2.revGuid);
	return cmp;
}


inline Int32 UnID::CompareMainPart (const UnID& unid2) const
{
	Int32 cmp = mainGuid.Compare (unid2.mainGuid);
	return cmp;
}


inline bool UnID::IsMainPartEqual (const UnID& unid2) const
{
	bool isEqual = mainGuid.IsEqual (unid2.mainGuid);
	return isEqual;
}


inline GSErrCode UnID::ConvertToString (char * uiStr) const
{
	*uiStr++ = '{';
	mainGuid.ConvertToString (uiStr);
	uiStr += strlen (uiStr);
	strcpy (uiStr, "}-{");
	uiStr += 3;
	revGuid.ConvertToString (uiStr);
	uiStr += strlen (uiStr);
	strcpy (uiStr, "}");

	return NoError;
}


inline GS::UniString UnID::ToUniString () const
{
	return GS::UniString ("{") + mainGuid.ToUniString () + "}-{" + revGuid.ToUniString () + "}";
}


inline GSErrCode UnID::ConvertFromString (const char* uiStr)
{
	GS::Guid		main, rev;
	char			guidStr[60];
	const Int32		strLen = sizeof (guidStr) / sizeof (guidStr[0]);
	Int32			i;

	while (*uiStr == ' ' || *uiStr == '\t')
		uiStr++;

	if (*uiStr++ != '{')
		return Error;

	for (i = 0; i < strLen - 1 && *uiStr != 0 && *uiStr != '}'; i++, uiStr++)
		guidStr[i] = *uiStr;
	if (*uiStr != '}')
		return Error;
	guidStr[i] = 0;

	if (main.ConvertFromString (guidStr) != NoError)
		return Error;

	if (*(++uiStr)++ != '-' || *uiStr++ != '{')
		return Error;

	for (i = 0; i < strLen - 1 && *uiStr != 0 && *uiStr != '}'; i++, uiStr++)
		guidStr[i] = *uiStr;
	if (*uiStr != '}')
		return Error;
	guidStr[i] = 0;

	if (rev.ConvertFromString (guidStr) != NoError)
		return Error;

	mainGuid = main;
	revGuid = rev;

	return NoError;
}

inline GSErrCode UnID::ConvertFromString (const GS::UniString& str)
{
	return ConvertFromString (str.ToCStr().Get());
}

inline bool operator== (const UnID& unid1, const UnID& unid2)
{
	return	unid1.IsEqual (unid2);
}

inline bool operator!= (const UnID& unid1, const UnID& unid2)
{
	return	!(unid1 == unid2);
}

inline GS::OChannel& operator<< (GS::OChannel& oc, const UnID& unid)
{
	char s[200];
	s[0] = 0;
	unid.ConvertToString (s);
	oc << s;
	return oc;
}


GSUTILS_DLL_EXPORT const UnID NULLUnID;
GSUTILS_DLL_EXPORT const Guid DummyRevID;

}	// namespace GS

#endif
