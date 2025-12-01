// *********************************************************************************************************************
// File:			DGNativeContexts.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
// *********************************************************************************************************************

#ifndef DGNATIVECONTEXTS_HPP
#define DGNATIVECONTEXTS_HPP

// --- Includes --------------------------------------------------------------------------------------------------------

#include "DGGraphixDefinitions.hpp"					// DGGRAPHIX_DLL_EXPORT
#include "NativeContext.hpp"

namespace DG {
	class UserItemUpdateEvent;
	class FileDialogPreviewUpdateEvent;
	class ListBoxItemUpdateEvent;
	class ListBoxTabItemUpdateEvent;
	class ListViewUpdateEvent;
	class ItemUpdateEventArg;
}


namespace NewDisplay {

class DGGRAPHIX_DLL_EXPORT UserItemUpdateNativeContext: public NativeContext
{
public:
	UserItemUpdateNativeContext (const DG::UserItemUpdateEvent&);
	UserItemUpdateNativeContext (const DG::FileDialogPreviewUpdateEvent&);
	explicit UserItemUpdateNativeContext (const DG::ItemUpdateEventArg* updateItemData);

	~UserItemUpdateNativeContext ();
};

class DGGRAPHIX_DLL_EXPORT ListBoxUpdateEventContext: public NativeContext
{
public:
	ListBoxUpdateEventContext (const DG::ListBoxItemUpdateEvent&);
	ListBoxUpdateEventContext (const DG::ListBoxTabItemUpdateEvent&);
	explicit ListBoxUpdateEventContext (const DG::ItemUpdateEventArg* updateItemData);

	~ListBoxUpdateEventContext ();
};

class DGGRAPHIX_DLL_EXPORT ListViewUpdateEventContext: public NativeContext
{
public:
	ListViewUpdateEventContext (const DG::ListViewUpdateEvent&);
	explicit ListViewUpdateEventContext (const DG::ItemUpdateEventArg* updateItemData);

	~ListViewUpdateEventContext ();
};


}

#endif
