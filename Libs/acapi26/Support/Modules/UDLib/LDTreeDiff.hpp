#ifndef GS_UD_LD_TREE_DIFF_HPP
#define GS_UD_LD_TREE_DIFF_HPP

#pragma once

#include "UDDefinitions.hpp"
#include "GSGuid.hpp"
#include "HashSet.hpp"
#include "HashTable.hpp"
#include "SkipSet.hpp"
#include "SkipMap.hpp"
#include "LDListDiff.hpp"
#include "OptionalOnHeap.hpp"
#include <memory>

namespace UD {
namespace ListDiff {

class UD_DLL_EXPORT TreeDiffable : public ListDiffable {
	virtual bool		IsEqualToDiffableObject (const ListDiffable& object) const override;

public:
	virtual GS::Guid							GetDiffIdentifier () const override = 0;
	virtual bool								IsEqualToDiffableObject (const TreeDiffable& object) const = 0;
	virtual GS::Array<std::shared_ptr<const TreeDiffable>>		GetDiffableChildren () const = 0;
	virtual ~TreeDiffable ();
};


struct UD_DLL_EXPORT TreeResult {
	struct Update {
		bool hasTopLevelChanges;
		GS::OptionalOnHeap<TreeResult> childrenDiff;
	};
	GS::SkipSet<UInt64>				inserts;
	GS::SkipSet<UInt64>				deletes;
	GS::SkipMap<UInt64, Update>		updates;
	GS::HashSet<Move>	moves;

	bool	HasChanges () const;
};


UD_DLL_EXPORT
TreeResult	TreeDiffing (const GS::Array<std::shared_ptr<const TreeDiffable>>& oldItems,
						 const GS::Array<std::shared_ptr<const TreeDiffable>>& newItems);

} // namespace ListDiff
} // namespace UD

#endif
