#ifndef GS_UD_LD_LISTDIFF_HPP
#define GS_UD_LD_LISTDIFF_HPP

#pragma once

#include "UDDefinitions.hpp"
#include "GSGuid.hpp"
#include "HashSet.hpp"
#include "BiHashTable.hpp"

namespace UD {
namespace ListDiff {

class UD_DLL_EXPORT ListDiffable {
public:
	virtual GS::Guid	GetDiffIdentifier () const = 0;
	virtual bool		IsEqualToDiffableObject (const ListDiffable& object) const = 0;

	virtual ~ListDiffable ();
};


struct UD_DLL_EXPORT Move {
	Int64 from;
	Int64 to;

	bool	operator== (const Move& other) const;
	ULong	GenerateHashValue () const;
};

struct UD_DLL_EXPORT Result {
	GS::HashSet<UInt64>	inserts;
	GS::HashSet<UInt64>	deletes;
	GS::HashSet<UInt64>	updates;
	GS::HashSet<Move> moves;
	GS::BiHashTable<Int64, GS::Guid> oldMap;
	GS::BiHashTable<Int64, GS::Guid> newMap;

	bool	HasChanges () const;
};


UD_DLL_EXPORT
Result	ListDiffing (const GS::Array<const ListDiffable*>& oldArray,
					 const GS::Array<const ListDiffable*>& newArray);

} // namespace ListDiff
} // namespace UD


#endif
