// *********************************************************************************************************************
// Description:		Model version table
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef MODELVERSIONTABLE_HPP
#define MODELVERSIONTABLE_HPP

#pragma once


#include "HashTable.hpp"
#include "ClassInfo.hpp"
#include "SerializationContext.hpp"


// === class ModelVersionTable =========================================================================================

namespace GS {

class GSROOT_DLL_EXPORT ModelVersionTable {
public:
	enum Completeness { Complete, Partial };

private:
	HashTable<const ClassInfo*, ClassVersion> classVersions;
	Completeness	completeness = Complete;

public:
	ModelVersionTable (Completeness	completeness = Complete);

	void			AddVersion (const ClassInfo* classInfo, const ClassVersion& classVersion);
	ClassVersion	GetVersion (const ClassInfo* classInfo) const;
	bool			Contains   (const ClassInfo* classInfo) const;

	bool			IsEmpty () const;

	bool			IsComplete () const;
	bool			IsPartial () const;
};


GSROOT_DLL_EXPORT extern const SerializationContext::Pointer	ModelVersionTableContext;

}	// namespace GS

// === class ModelVersionTable =========================================================================================


#endif
