// *****************************************************************************
// CopyrightInfo
//
// Namespace:		-
// Contact person:	PT
//
// [SG compatible]
// *****************************************************************************

#ifndef	COPYRIGHTINFO_HPP
#define	COPYRIGHTINFO_HPP

#pragma once


#include	"GSMSectionsExport.h"
#include	"UniString.hpp"


class GSMSECTIONS_CPP_DLL_EXPORT CopyrightInfo {

public:

	CopyrightInfo ();

	const GS::UniString&	GetAuthor			(void) const;
	const GS::UniString&	GetLicenseType		(void) const;
	const GS::UniString&	GetLicenseVersion	(void) const;
	const GS::UniString&	GetComment			(void) const;
	static short			GetVersion			(void);

	void	SetAuthor			(const GS::UniString& author);
	void	SetLicenseType		(const GS::UniString& licenseType);
	void	SetLicenseVersion	(const GS::UniString& licenseVersion);
	void	SetComment			(const GS::UniString& comment);

	GSErrCode	Read	(GS::IChannel& ic);
	GSErrCode	Write	(GS::OChannel& oc) const;

private:

	GS::UniString		author;
	GS::UniString		licenseType;
	GS::UniString		licenseVersion;
	GS::UniString		comment;

};


#endif
