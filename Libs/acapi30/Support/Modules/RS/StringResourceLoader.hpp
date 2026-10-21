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
	mutable GS::HashTable<GSResModule, GS::HashTable<GS::UniString, GS::HashTable<GS::UniString, GS::UniString>>>	resModulesResIdStringCache;
	mutable GS::HashTable<GSResModule, GS::HashTable<GS::UniString, GS::Array<GS::UniString>>>						resModulesResIdStringListCache;

private:
	StringResourceLoader ();

	virtual void OnDisposeModuleCaches (GSResModule module) override;

	GS::Optional<GS::Array<GS::Pair<GS::UniString, GS::UniString>>> LoadStrings (GSResModule module, const GS::UniString& resourceID) const;

public:
	static StringResourceLoader& Get ();
	virtual ~StringResourceLoader ();

	GS::Optional<GS::UniString>					Load			(GSResModule module, const GS::UniString& resourceID, const GS::UniString& stringID) const;
	GS::Optional<GS::Array<GS::UniString>>		LoadStringList	(GSResModule module, const GS::UniString& resourceID) const;
};

}

#endif	// STRINGRESOURCELOADER_HPP
