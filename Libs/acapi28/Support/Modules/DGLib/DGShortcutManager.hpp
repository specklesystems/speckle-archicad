// *****************************************************************************
// File:			DGShortcutManager.hpp
//
// Description:		Shortcut related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BLA, BL, MD
//
// SG compatible
// *****************************************************************************

#ifndef DGSHORTCUTMANAGER_HPP
#define DGSHORTCUTMANAGER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Array.hpp"
#include "GSGuid.hpp"
#include "GSException.hpp"

#include "DG.h"
#include "DGUtility.hpp"
#include "DGPanel.hpp"
#include "DGCommandEvent.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace xercesc_3_0 {
	class DOMElement;
}
namespace xercesc = xercesc_3_0;

namespace DG {
	class ShortcutManager;
	class ShortcutManagerImpl;
	class Shortcut;
	class ShortcutScheme;
	class ShortcutImpl;
	class ShortcutIterator;
	class ModifierKey;
	class CommandDescriptor;
}


namespace DG {

// --- Resource functions ------------------------------------------------------

DG_DLL_EXPORT GSErrCode	ReadShortcutResource (Int32 resID, ShortcutScheme* shortcutScheme, const GS::Guid& schemeContextGuid, GS::UniString* schemeContextName = nullptr);


// --- Class declarations ------------------------------------------------------

// --- ShortcutUsage -----------------------------------------------------------

class ShortcutUsage
{
private:
	Shortcut*					shortcut;
	GS::Guid					contextGuid;
	Command						command;
	mutable CommandDescriptor*	cmdDescCache;

public:
	ShortcutUsage ();
	ShortcutUsage (Shortcut* shortcut, const GS::Guid& contextGuid, const Command& command);
	ShortcutUsage (const ShortcutUsage& source);
   ~ShortcutUsage () {};

	Shortcut*			GetShortcut		(void) const;
	GS::Guid			GetContextGuid	(void) const;
	const Command&		GetCommand		(void) const;
	CommandDescriptor*	GetCmdDesc		(void) const;

	void				Refresh			(const CommandDescriptor* cmdDesc = nullptr);
};


// --- ShortcutScheme ----------------------------------------------------------

class DG_DLL_EXPORT ShortcutScheme : public GS::Object
{
	friend class ShortcutManager;
	friend class ShortcutIterator;

	DECLARE_CLASS_INFO
private:
	GS::Array<GS::Guid>				contextData;
	UIndex							currentContextIndex;

	GS::Array<Shortcut*>			shortcuts;
	GS::Array<ShortcutUsage>		usage;

	void							Init ();

public:
	class DG_DLL_EXPORT ContentMapper {
	public:
		virtual			~ContentMapper ();

		virtual bool	Map (const GS::Guid& contextToMap, GS::Guid* mappedContext) const = 0;
		virtual bool	Map (const DG::Command& commandToMap, DG::Command* mappedCommand) const = 0;
	};

private:
	using GS::Object::Read;
	using GS::Object::Write;

public:

	static		GS::UniString	GetContextMetaName (void);

								ShortcutScheme		();
								ShortcutScheme		(const ShortcutScheme& source);
							   ~ShortcutScheme		();

	ShortcutScheme&				operator=			(const ShortcutScheme& source);

	Shortcut*					CreateShortcut		(Key::Code key, ULong modifierFlags,
													 const Command& command,
													 const GS::Guid& contextGuid,
													 bool fixedShortcut = false,
													 bool systemShortcut = false);
	GSErrCode					DeleteShortcut		(const GS::Guid& contextGuid);
	GSErrCode					DeleteShortcut		(const Shortcut* shortcut, const CommandDescriptor* cmdDesc);
	GSErrCode					DeleteShortcut		(const Shortcut* shortcut, const CommandDescriptor* cmdDesc, const GS::Guid& contextGuid);
	GSErrCode					DeleteContent		(void);

	GSErrCode					RefreshShortcuts	(const CommandDescriptor* cmdDesc = nullptr);

	// context handling
	GSErrCode					SetActiveContext	(const GS::Guid& contextGuid);
	GS::Guid					GetActiveContext	(void) const;
	GS::Guid					GetGlobalContext	(void) const;
	GS::Guid					GetContextGuid		(UIndex index) const;
	USize						GetContextCount		(void) const;
	UIndex						FindContextGuid		(const GS::Guid& contextGuid) const;

	// search
	ShortcutIterator			GetActiveShortcutIterator	(const Shortcut* shortcut, const CommandDescriptor* cmdDesc) const;
	ShortcutIterator			GetActiveShortcutIterator	(const Shortcut* shortcut) const;
	ShortcutIterator			GetActiveShortcutIterator	(const CommandDescriptor* cmdDesc) const;
	ShortcutIterator			GetActiveShortcutIterator	(void) const;

	USize						GetActiveShortcutCount		(void) const;

	ShortcutIterator			GetShortcutIterator	(const Shortcut* shortcut, const GS::Guid& contextGuid, const CommandDescriptor* cmdDesc, bool exactContextMatch) const;
	ShortcutIterator			GetShortcutIterator	(const Shortcut* shortcut, const GS::Guid& contextGuid, const CommandDescriptor* cmdDesc) const;
	ShortcutIterator			GetShortcutIterator	(const Shortcut* shortcut, const CommandDescriptor* cmdDesc) const;

	// I/O
	GSErrCode					Write	(const GS::Guid& contextGuid, GS::OChannel& oc) const;
	GSErrCode					Read	(const GS::Guid& contextGuid, GS::IChannel& ic, bool merge = false, ContentMapper* contentMapper = nullptr);

	GSErrCode					XMLWriteContext	(const GS::Guid& contextGuid, xercesc::DOMElement* parent, int level) const;
	GSErrCode					XMLReadContext	(const xercesc::DOMElement* parent, bool merge = false, ContentMapper* contentMapper = nullptr);
};


// --- ShortcutManager ---------------------------------------------------------

class DG_DLL_EXPORT ShortcutManager
{
	friend class ShortcutScheme;
	friend class ShortcutUsage;

public:
	enum Mode {
		Char = 0,
		Key  = 1
	};

private:
	// static data
	ShortcutManagerImpl*				impl;
	GS::Array<const ModifierKey*>		modifiers;

	USize								specialKeyCount;
	GS::Array<GS::UniString>			specialKeyText;

	Mode								mode;

	ShortcutScheme*						currentShortcutScheme;

	ShortcutManager (const ShortcutManager& source);			// disable

	void								CleanUp	(void);

	GSErrCode							ImplDeleteShortcut	(ShortcutScheme* shortcutScheme, const Shortcut* shortcut);
	GSErrCode							ImplDeleteShortcut	(ShortcutScheme* shortcutScheme, const Shortcut* shortcut, const GS::Guid& contextGuid);
	GSErrCode							ImplCreateShortcut	(ShortcutScheme* shortcutScheme, const Shortcut* shortcut);
	GSErrCode							implRebuildShortcuts (ShortcutScheme* shortcutScheme);
	GSErrCode							ImplAfterInitialize	(ShortcutScheme* shortcutScheme);

public:
								ShortcutManager ();
							   ~ShortcutManager ();

	// initialize
	void						Init				(GS::UniString* specialKeys = nullptr,
													 GS::UniString* modifierKeys = nullptr,
													 ShortcutManager::Mode mode = ShortcutManager::Char);

	// utility function
	GS::Array<const ModifierKey*>	CreateModifierCollection	(ULong modifierFlags) const;

	// modifier handling
	const ModifierKey*			GetModifierKey		(Key::Modifier modifier) const;

	// special text handling
	GS::UniString				GetSpecialKeyText		(Key::Special specialKey) const;
	Key::Special				GetSpecialKeyFromText	(const GS::UniString& specialKeyText) const;

	// mode handling
	Mode						GetMode				(void) const;
	void						SetMode				(Mode mode);

	ShortcutScheme*				GetShortcutScheme	(void) const;
	void						SetShortcutScheme	(ShortcutScheme* shortcutScheme);
};


// --- Global instance ---------------------------------------------------------

extern DG_DLL_EXPORT ShortcutManager		shortcutManager;


// --- ShortcutIterator --------------------------------------------------------

class DG_DLL_EXPORT ShortcutIterator
{
	friend class ShortcutScheme;

private:
	bool						exactContextMatch;
	const ShortcutScheme*		shortcutScheme;
	const Shortcut*				shortcut;
	GS::Guid					contextGuid;
	const CommandDescriptor*	cmdDesc;

	UIndex					current;

	class DG_DLL_EXPORT X {};		// a type for safe comparison against nullptr

	ShortcutIterator (const ShortcutScheme* shortcutScheme, const Shortcut* shortcut, const GS::Guid& contextGuid, const CommandDescriptor* cmdDesc, bool exactContextMatch);

	void				SearchNext (void);
public:
	ShortcutIterator (const ShortcutIterator& source);
   ~ShortcutIterator () {};

	ShortcutIterator&	operator++ ();
	void				operator+= (int);

	bool				operator== (const X*) const;
	bool				operator!= (const X*) const;

	Shortcut*			GetCurrentShortcut		(void) const;
	GS::Guid			GetCurrentContextGuid	(void) const;
	const Command*		GetCurrentCommand		(void) const;
	CommandDescriptor*	GetCurrentCmdDesc		(void) const;
};


// --- ModifierKey -------------------------------------------------------------

class DG_DLL_EXPORT ModifierKey
{
	friend class ShortcutManager;

private:
	Key::Modifier	modifierFlag;

	ModifierKey (Key::Modifier modifier, const GS::UniString& displayText);
	ModifierKey (const ModifierKey& source);
   ~ModifierKey () {};

	GS::UniString		displayText;

public:
	GS::UniString	GetDisplayText	(void) const;
	Key::Modifier	GetModifierFlag	(void) const;
};


// --- Shortcut ----------------------------------------------------------------

class DG_DLL_EXPORT Shortcut : public GS::Object
{
	friend class			ShortcutScheme;
	friend ShortcutImpl*	Shortcut_GetImpl (Shortcut*);

	DECLARE_CLASS_INFO
private:
	ShortcutImpl*					impl;
	Key::Code						key;
	GS::Array<const ModifierKey*>	modifiers;
	bool							system;
	bool							fixed;

						Shortcut ();
						Shortcut (const Shortcut& source);

public:
	static GS::UniString	GetMetaName (void);

						Shortcut (Key::Code key, ULong modifierFlags);
					   ~Shortcut ();

	GS::UniString		GetDisplayText			(void) const;
	Key::Code			GetKey					(void) const;
	const ModifierKey*	GetModifierKey			(UIndex index) const;
	USize				GetModifierKeyCount		(void) const;
	ULong				GetModifierFlags		(void) const;
	bool				IsSystem				(void) const;
	bool				IsFixed					(void) const;

	// I/O
	GSErrCode			Write					(GS::OChannel& oc) const override;
	GSErrCode			Read					(GS::IChannel& ic) override;
	GSErrCode			ReadVersion1			(GS::IChannel& ic);
	GSErrCode			ReadVersion2					(GS::IChannel& ic);

	GSErrCode			XMLWrite				(xercesc::DOMElement* parent, int level) const;
	GSErrCode			XMLRead					(const xercesc::DOMElement* parent);
	GSErrCode			XMLReadVersion1			(const xercesc::DOMElement* parent);
	GSErrCode			XMLReadVersion2			(const xercesc::DOMElement* parent);

	bool				operator==	(const Shortcut& op) const;
};

}	// namespace DG

#endif
