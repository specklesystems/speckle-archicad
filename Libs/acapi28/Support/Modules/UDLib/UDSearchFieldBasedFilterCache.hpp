#ifndef GS_UD_SEARCHFIELDBASEDFILTERCACHE_HPP
#define GS_UD_SEARCHFIELDBASEDFILTERCACHE_HPP
#pragma once

#include "UDDefinitions.hpp"

//from GS
#include "UniString.hpp"

// from STL
#include <set>

namespace UD {

class UD_DLL_EXPORT SearchFieldBasedFilterCache {
private:
	std::set<GS::UniString> cachedSearchFieldWords;
	mutable std::set<GS::UniString> cachedAllowedStrings;

private:
	bool ContainsKeyWordsInAnyOrder (const GS::UniString& name) const;

public:
	void Reset (const GS::UniString& newSearchFieldText);
	bool IsAllowedBySearchFieldText (const GS::UniString& name) const;
	bool IsEmptySearchFieldText () const;
	bool IsContainedBySearchFieldText (const GS::UniString& text) const;
};


}

#endif  //GS_UD_SEARCHFIELDBASEDFILTERCACHE_HPP
