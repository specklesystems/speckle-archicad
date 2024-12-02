#ifndef ADDON_UPDATE_CHECKER_INFORMATION_HPP
#define ADDON_UPDATE_CHECKER_INFORMATION_HPP

#include "GSUtilsExport.h"

// from GSRoot
#include "UniString.hpp"

namespace GSUtils {

struct QueryTypeIds {
	Int32 xmlId;
	Int32 htmlId;

	QueryTypeIds (Int32 xmlId, Int32 htmlId) : xmlId (xmlId), htmlId (htmlId) {}
};


class GSUTILS_DLL_EXPORT_CPP AddOnUpdateCheckerInformation {
public:
	AddOnUpdateCheckerInformation ();
	AddOnUpdateCheckerInformation (const AddOnUpdateCheckerInformation& information);
	~AddOnUpdateCheckerInformation ();

	bool GetIsAddOnAlreadyInstalled () const;
	void SetIsAddOnAlreadyInstalled (bool flag);

	GSType GetDeveloperId () const;
	void SetDeveloperId (GSType id);

	GSType GetAddonId () const;
	void SetAddonId (GSType id);

	const GS::UniString& GetGsSubType () const;
	void SetGsSubType (const GS::UniString& type);

	const GS::UniString& GetAddOnVersionXMLUrlPart () const;
	void SetAddOnVersionXMLUrlPart (const GS::UniString& addOnVersionUrl);

	const GS::UniString& GetAddOnVersionHTMLUrlPart () const;
	void SetAddOnVersionHTMLUrlPart (const GS::UniString& addOnVersionUrl);

	const GS::UniString& GetAddOnDisplayName () const;
	void SetAddOnDisplayName (const GS::UniString& displayNameForActionCenter);

private:
	bool isAddOnAlreadyInstalled;
	GSType developerId;
	GSType addonId;
	GS::UniString gsSubType;
	GS::UniString addOnVersionXMLUrlPart;
	GS::UniString addOnVersionHTMLUrlPart;
	GS::UniString addOnDisplayName;
};

}	// namespace GSUtils

#endif	// ADDON_UPDATE_CHECKER_INFORMATION_HPP
