// *****************************************************************************
// Migration table for libpart migration
//
// Namespace:		LPF
// Contact person:	KSK
//
// [SG compatible]
// *****************************************************************************

#ifndef MIGRATIONTABLE_HPP
#define MIGRATIONTABLE_HPP

#pragma once


// from GSRoot
#include	"HashTable.hpp"
#include	"UniString.hpp"

// from GSMSections
#include	"GSMSectionsExport.h"

#define Curr_MigrationTableSectionVersion	1 // 0: initial version, no version, 1: name, autoMigration added

class GSMSECTIONS_CPP_DLL_EXPORT MigrationTableValue {
public:
	Int32			version;
	GS::UniString	name;
	bool			autoMigration;

	MigrationTableValue ();
	~MigrationTableValue (void) {}

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};

class GSMSECTIONS_CPP_DLL_EXPORT MigrationTable {
public:
	typedef GS::HashTable<GS::Guid, MigrationTableValue>	MigrationData;
	typedef MigrationData::ValueIterator		Iterator;
	typedef MigrationData::ConstValueIterator	ConstIterator;
	typedef MigrationData::PairIterator			PairIterator;
	typedef MigrationData::ConstPairIterator	ConstPairIterator;

private:

	MigrationData table;

public:

	MigrationTable () {}
	MigrationTable (const MigrationData& table);
	~MigrationTable (void) {}

	void Put (const GS::Guid& mainGuid, Int32 version, GS::UniString name, bool autoMigration);

	bool IsEmpty () const { return table.IsEmpty (); }

	Iterator		Begin ();
	Iterator		End ();
	ConstIterator	Begin () const;
	ConstIterator	End () const;
	PairIterator		BeginPairs ();
	PairIterator		EndPairs ();
	ConstPairIterator	BeginPairs () const;
	ConstPairIterator	EndPairs () const;

	GSErrCode				ReadOldVersion_0 (GS::IChannel& ic);
	GSErrCode				Read (GS::IChannel& ic, short sectVersion = Curr_MigrationTableSectionVersion);
	GSErrCode				Write (GS::OChannel& oc) const;
};


#endif
