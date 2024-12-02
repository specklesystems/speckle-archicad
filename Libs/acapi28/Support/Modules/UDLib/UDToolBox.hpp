// *****************************************************************************
// File:			UDToolBox.hpp
//
// Description:		Toolbox related classes
//
// Project:			GRAPHISOFT User Dialog Module (UDLib)
//
// Namespace:		UD
//
// Contact person:	MD
//
// SG compatible
// *****************************************************************************

#ifndef UDTOOLBOX_HPP
#define UDTOOLBOX_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include <xercesc/util/XercesDefs.hpp>

#include "Array.hpp"
#include "Event.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"
#include "UniString.hpp"

#include "UDDefinitions.hpp"

#include "DGCommandDescriptor.hpp"
#include "DGDialog.hpp"


// --- Predeclarations ---------------------------------------------------------

XERCES_CPP_NAMESPACE_BEGIN
class DOMElement;
XERCES_CPP_NAMESPACE_END

namespace UD {
	class ToolBox;
	class ToolBoxImpl;
	class ToolBoxGroup;
	class ToolBoxItem;
}

namespace DG  {
	class Command;
	class CommandLayoutSerializer;
	class CommandLayoutDeserializer;
	class ListViewPressedEvent;
	class SingleSelListView;
}


namespace UD {

// --- Class declarations ------------------------------------------------------

// --- ToolBoxObserver ---------------------------------------------------------

class UD_DLL_EXPORT ToolBoxObserver: public GS::EventObserver
{
	friend class ToolBox;

protected:
	virtual void	ToolBoxOpened (const ToolBox& toolBox);
	virtual void	ToolBoxClosed (const ToolBox& toolBox, bool onRequest);
	virtual void	ToolBoxContextMenuRequested (const ToolBox& toolBox, const DG::PanelContextMenuEvent& ev,
												 bool* needHelp, bool* processed);
	virtual void	ToolBoxItemPressed			(const ToolBox& toolBox, const DG::ListViewPressedEvent& ev);

public:
	ToolBoxObserver ();
   ~ToolBoxObserver ();
};


// --- ToolBox -----------------------------------------------------------------

class UD_DLL_EXPORT ToolBox: private GS::EventSource
{
	friend	class ToolBoxGroup;
	friend	class ToolBoxItem;
	friend	ToolBoxImpl*	ToolBox_GetImpl (ToolBox*);
	friend	class ToolBoxImpl;

public:
	// inner class definitions

	// ConstIterator
	typedef GS::Array<ToolBoxGroup*>::ConstIterator		ConstIterator;

public:
	// enumerations
	static const GS::Guid guid;

private:
	// attributes
	GS::UniString					title;

	// relations
	GS::Array<ToolBoxGroup*>		groups;

	// implementation
	ToolBoxImpl*					impl;

	// position
	mutable DG::NativePoint			position;
	short							initialHeight;

	bool							doLayoutInit;

	mutable UIndex					lastSelectedItem;

	static bool						disableAllLayout;
	bool							changedByTheUser;
	bool							isInCustomState;

	void			Init					(void);
	ToolBoxImpl*	GetImpl					(void);
	void			AdjustLastSelected		(void) const;

	// observer notifications

	// disable copy
					ToolBox					(const ToolBox& source);

	bool			SetGroupVisibility		(const ConstIterator& iterator, bool visibility) const;
	void			RebuildImpl				(void);

	// private interface for the bridge
	void			ProcessImplDestroyed			(void);
	void			ProcessOpenEvent				(void);
	void			ProcessCloseEvent				(void);
	short			ProcessCloseRequestEvent		(void);
	void			ProcessItemClickedEvent			(void* data);
	void			ProcessItemDoubleClickedEvent	(void* data);
	void			ProcessContextMenuRequested		(const DG::PanelContextMenuEvent& ev, bool* needHelp,
													 bool* processed);
	void			ProcessItemPressedEvent			(const DG::ListViewPressedEvent& ev);
	GS::UniString	GetItemShortcut					(void* data);

public:
	// constructors / destructors
					ToolBox					(const GS::UniString& title);
	virtual		   ~ToolBox 				();

	void			Attach 					(ToolBoxObserver& observer);
	void			Detach 					(ToolBoxObserver& observer);

	// accessors
	GS::UniString	GetId					(void) const;
	GS::UniString	GetTitle				(void) const;
	void			SetTitle				(const GS::UniString& title);

	void			Create					(void);
	void			Destroy					(void);
	bool			IsCreated				(void) const;

	void			Show					(DG::NativePoint pPosition = DG::NativePoint ());
	void			Hide					(void);
	bool			IsVisible				(void) const;

	void			InitDefaultLayout		(const DG::NativePoint& position, short height);

	void			PrevTool				(void);
	void			NextTool				(void);
	void			PressTool				(void);

	void			DisableUpdate			(void);
	void			EnableUpdate			(void);
	bool			IsUpdateEnabled			(void);

	static void		DisableAllUpdate		(void);
	static void		EnableAllUpdate			(void);

	bool			IsChangedByTheUser		(void) const;

	void			SetCustomState			(bool isCustomState);
	bool			IsInCustomState			(void) const;

	// group operations
	void			AddToolBoxGroup			(const GS::UniString& name);
	void			InsertToolBoxGroup		(const ConstIterator& iterator, const GS::UniString& name);
	void			MoveToolBoxGroup		(const ConstIterator& from, const ConstIterator& to);
	void			RemoveToolBoxGroup		(const ConstIterator& iterator);
	void			ExpandGroup				(const ToolBoxGroup* group);

	ConstIterator	Enumerate				(const ToolBoxGroup* group = nullptr) const;
	ConstIterator	Begin					(void) const;
	ConstIterator	End						(void) const;

	//
	void			DeepCopy				(const ToolBox& source);
	GSErrCode		XMLWrite				(xercesc::DOMElement* parent, int level) const;
	GSErrCode		XMLRead					(const xercesc::DOMElement* parent);
	//GSErrCode		XMLReadVersion1			(const xercesc::DOMElement* parent);
	//GSErrCode		XMLReadVersion2			(const xercesc::DOMElement* parent);

	GSErrCode		Read					(GS::IChannel& ic, const GS::ClassVersion& version);
	//GSErrCode		ReadVersion1			(GS::IChannel& ic);
	//GSErrCode		ReadVersion2			(GS::IChannel& ic);
	GSErrCode		Write					(GS::OChannel& oc) const;

	DG::Palette*	GetImplPalette			(void);

	void			ApplyConstraints		(void);

	virtual bool	IsHoverNeeded			(const DG::SingleSelListView& listView, short listItemIndex) const;
	void			FreezeHover				(void);
	void			UnFreezeHover			(void);
};


// --- ToolBoxGroup ------------------------------------------------------------

class UD_DLL_EXPORT ToolBoxGroup : public DG::CommandDescriptorObserver
{
	friend	class ToolBox;
	friend	class ToolBoxItem;

public:
	// enumerations
	enum Style {
		SmallIconWithText,
		SmallIconOnly
	};

private:
	//impl
	UIndex							index;
	mutable	char*					implData;
	mutable USize					implDataSize;

	// attributes
	const ToolBox*					parentToolBox;
	GS::UniString					name;
	bool							visible;
	Style							style;
	bool							openToMax;
	bool							closable;

	// relations
	GS::Array<ToolBoxItem*>			items;

	// disable copy
				ToolBoxGroup	(const ToolBoxGroup& source);
				ToolBoxGroup& operator= (const ToolBoxGroup& source);


	void			DeepCopy			(const ToolBoxGroup& source);
	void			RebuildItemImpl		(void);

	// private interface for the bridge

protected:
	// CommandDescriptorObserver methods
	virtual	void	CheckChanged		(const DG::CommandDescriptorCheckEvent& ev) override;
	virtual	void	EnableChanged		(const DG::CommandDescriptorEnableEvent& ev) override;
	virtual	void	TextChanged			(const DG::CommandDescriptorTextEvent& ev) override;
	virtual	void	CmdDescDeleting		(const DG::CommandDescriptorDeleteEvent& ev) override;

public:
	// inner class definitions

	// ConstIterator
	typedef GS::Array<ToolBoxItem*>::ConstIterator	ConstIterator;

	// constructors / destructors
				ToolBoxGroup	(const ToolBox& toolbox, const GS::UniString& name);
	virtual	   ~ToolBoxGroup ();

	// accessors
	GS::UniString	GetId					(void) const;
	GS::UniString	GetName					(void) const;
	void			SetName					(const GS::UniString& name);
	bool			IsVisible				(void) const;
	Style			GetStyle				(void) const;
	void			SetStyle				(Style style);
	bool			IsOpenToMax				(void) const;
	void			SetOpenToMax			(bool openToMax);
	bool			IsClosable				(void) const;
	void			SetClosable				(bool closable);

	// item operations
	void			AddToolBoxItem			(const DG::Command& command);
	void			InsertToolBoxItem		(const ConstIterator& iterator, const DG::Command& command);
	void			RemoveToolBoxItem		(const ConstIterator& iterator);

	ConstIterator	Enumerate				(const DG::Command& command) const;
	ConstIterator	Begin					(void) const;
	ConstIterator	End						(void) const;

	// serialization
	GSErrCode		XMLWrite				(xercesc::DOMElement* parent, int level) const;
	GSErrCode		XMLRead					(const xercesc::DOMElement* parent);
	//GSErrCode		XMLReadVersion1			(const xercesc::DOMElement* parent);
	//GSErrCode		XMLReadVersion2			(const xercesc::DOMElement* parent);

	GSErrCode		Read					(GS::IChannel& ic, const GS::ClassVersion& version);
	//GSErrCode		ReadVersion1			(GS::IChannel& ic);
	//GSErrCode		ReadVersion2			(GS::IChannel& ic);
	GSErrCode		Write					(GS::OChannel& oc) const;

	GSErrCode		RetrieveImplData		(void) const;
	GSErrCode		ApplyImplData			(void);
};


// === ToolBoxItem class ===============================================================================================

// --- Declaration -----------------------------------------------------------------------------------------------------

class UD_DLL_EXPORT ToolBoxItem
{
	friend class ToolBoxGroup;

private:
	const ToolBoxGroup&		parentGroup;
	UIndex					index;

	DG::Command				command;

							ToolBoxItem (const ToolBoxItem& source);	// disable
	ToolBoxItem&			operator= (const ToolBoxItem& source);
							ToolBoxItem	 ();							// for Array

public:
							ToolBoxItem (const ToolBoxGroup& group, const DG::Command& command);
	virtual					~ToolBoxItem ();

	const DG::Command&		GetCommand (void) const;
};


// === ToolBoxCommandDescriptor class ==================================================================================

// --- Declaration -----------------------------------------------------------------------------------------------------

class UD_DLL_EXPORT ToolBoxCommandDescriptor : public DG::CommandDescriptor
{
private:
	DG::Icon			largeIcon;
	GS::UniString			contextHelpAnchor;

						ToolBoxCommandDescriptor (const ToolBoxCommandDescriptor& source);		// disable

public:
						ToolBoxCommandDescriptor (const DG::Command& command, const GS::UniString& text,
												  const DG::Icon& smallIcon, const DG::Icon& largeIcon,
												  const GS::UniString& category = GS::UniString(), const GS::UniString& contextHelp = GS::UniString(),
												  bool visible = true);
						~ToolBoxCommandDescriptor ();

	inline DG::Icon		GetSmallIcon (void) const;
	inline DG::Icon		GetLargeIcon (void) const;

	inline const GS::UniString&	GetContextHelpAnchor (void) const;
};


// --- Inline implementations ------------------------------------------------------------------------------------------

inline DG::Icon		ToolBoxCommandDescriptor::GetSmallIcon (void) const
{
	return GetIcon ();
}


inline DG::Icon		ToolBoxCommandDescriptor::GetLargeIcon (void) const
{
	return largeIcon;
}


inline const GS::UniString&	ToolBoxCommandDescriptor::GetContextHelpAnchor (void) const
{
	return contextHelpAnchor;
}

}	// namespace UD

#endif
