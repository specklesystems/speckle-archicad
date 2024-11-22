// *********************************************************************************************************************
// Description:		GRAPHISOFT Resource Manager
//
// Namespaces:		-
// Contact persons:	SzaM
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef STRINGRESOURCELOADER_HPP
#define	STRINGRESOURCELOADER_HPP

#pragma once

// --- Predeclarations	------------------------------------------------------------------------------------------------


// --- Includes	--------------------------------------------------------------------------------------------------------

#include "ResourceLoader.hpp"

#include "HashTable.hpp"
#include "Optional.hpp"

// =====================================================================================================================
// Interface definition
// =====================================================================================================================

namespace RS {

class RS_DLL_EXPORT StringResourceLoader : public ResourceLoader
{
	typedef GS::HashTable <GS::UniString, GS::UniString> ResIdStringListCache;
	typedef GS::HashTable <GS::UniString, ResIdStringListCache> ResIdStringCache;
	typedef GS::HashTable <GSResModule, ResIdStringCache> ResModulesResIdStringCache;

	mutable ResModulesResIdStringCache resModulesResIdStringCache;

private:
	StringResourceLoader ();
	bool ContainsStringInCache (GSResModule module, const GS::UniString& resourceID, const GS::UniString& stringID) const;
	bool ContainsModuleInCache (GSResModule module) const;
	bool ContainsStringResourceIdInCache (GSResModule module, const GS::UniString& resourceID) const;

public:
	static StringResourceLoader& Get ();
	virtual ~StringResourceLoader ();

	GS::Optional<GS::UniString>		Load (GSResModule module, const GS::UniString& resourceID, const GS::UniString& stringID) const;
};

}

#endif	// STRINGRESOURCELOADER_HPP
