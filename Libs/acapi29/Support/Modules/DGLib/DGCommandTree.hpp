#ifndef GS_DG_DGCOMMANDTREE_HPP
#define GS_DG_DGCOMMANDTREE_HPP

#include "DGCommandDescriptor.hpp"
#include "RandomContainerIterator.hpp"

namespace DG {

class CommandTreeItemList;

class DG_DLL_EXPORT CommandTreeItem {
public:
	virtual	~CommandTreeItem ();

	virtual Command					GetCommand		() const = 0;
	virtual CommandDescriptor*		GetCmdDesc		() const = 0;

	virtual bool					IsSeparator		() const = 0;
	virtual	bool					IsDynamic		() const = 0;

	virtual bool					CanHaveSubItems	() const = 0;
	virtual CommandTreeItemList*	GetSubItems		() = 0;
};


class DG_DLL_EXPORT CommandTreeItemList {
public:
	using ValueType		= CommandTreeItem;
	using Iterator		= GS::RandomContainerIterator<CommandTreeItemList>;
	using ConstIterator	= GS::ConstRandomContainerIterator<CommandTreeItemList>;

	virtual ~CommandTreeItemList ();

	virtual UIndex					GetSize		() const = 0;
	virtual CommandTreeItem&		operator[]	(UIndex index) = 0;
	virtual const CommandTreeItem&	operator[]	(UIndex index) const = 0;
	virtual void					RemoveItem	(UIndex index) = 0;
	virtual void					UnwrapItem	(UIndex index) = 0;

	Iterator	Begin	();
	Iterator	End		();

	ConstIterator Begin () const;
	ConstIterator End	() const;
};

}

#endif