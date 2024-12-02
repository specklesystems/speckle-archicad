// *****************************************************************************
//
// CommandEvent
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
// Namespace:		DG
// Contact person:	BLA
//
// SG compatible
//
// *****************************************************************************

#ifndef DGCOMMANDEVENT_HPP
#define DGCOMMANDEVENT_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "Event.hpp"
#include "UniString.hpp"

#include "DG.h"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class CommandDescriptor;
}


namespace DG {

// --- Enumerations ------------------------------------------------------------

enum SystemCommand {
	Invalid,
	About,
	Preferences,
	Copy,
	Cut,
	Paste,
	Quit
};


// --- Class declarations ------------------------------------------------------

// --- Command -----------------------------------------------------------------

class Command
{
private:
	ULong	developerId;
	ULong	productId;
	ULong	commandId;

public:
	inline		Command ();
	inline		Command (ULong commandId, ULong developerId = 0, ULong productId = 0);
			   ~Command () {}

	inline ULong			GetDeveloperId	(void) const;
	inline ULong			GetProductId	(void) const;
	inline ULong			GetCommandId	(void) const;

	inline GS::UniString	ToHelpAnchor	(void) const;

	inline GS::UniString	ToString		(void) const;
	inline void				Read			(const GS::UniString& string);

	inline bool				IsEmpty (void) const;

	inline bool				operator==	(const Command& op) const;
	inline bool				operator!=	(const Command& op) const;
	inline Command&			operator=	(const Command& source);

	inline ULong			GenerateHashValue () const;

	inline 	GSErrCode		Read  	(GS::IChannel& ic);
	inline	GSErrCode		Write 	(GS::OChannel& oc) const;
};


inline Command::Command () :
	developerId	(0),
	productId	(0),
	commandId	(0)
{
}


inline Command::Command (ULong commandIdParam, ULong developerIdParam/* = 0*/, ULong productIdParam/* = 0*/)	:
	developerId	(developerIdParam),
	productId	(productIdParam),
	commandId	(commandIdParam)
{
}


inline ULong		Command::GetDeveloperId (void) const
{
	return developerId;
}


inline ULong		Command::GetProductId (void) const
{
	return productId;
}


inline ULong	Command::GetCommandId (void) const
{
	return commandId;
}


inline GS::UniString	Command::ToHelpAnchor (void) const
{
	char anchorStr[256];
	sprintf (anchorStr, "CMD_%lu_0x%08lx_0x%08lx", (GS::ULongForStdio)commandId, (GS::ULongForStdio)developerId, (GS::ULongForStdio)productId);
	return GS::UniString (anchorStr);
}


inline GS::UniString	Command::ToString (void) const
{
	char buffer[128];
	sprintf (buffer, "%lu-0x%08lx-0x%08lx", (GS::ULongForStdio)commandId, (GS::ULongForStdio)developerId, (GS::ULongForStdio)productId);
	return GS::UniString (buffer);
}


inline void		Command::Read (const GS::UniString& string)
{
	if (GS::csscanf (string.ToUStr (), "%u-0x%x-0x%x", &commandId, &developerId, &productId) != 3)
		return;
}


inline bool		Command::IsEmpty (void) const
{
	return (commandId == 0 && developerId == 0 && productId == 0);
}


inline bool		Command::operator== (const Command& op) const
{
	return (commandId == op.commandId &&
			developerId == op.developerId &&
			productId == op.productId);
}


inline bool		Command::operator!= (const Command& op) const
{
	return !operator== (op);
}


inline Command&	Command::operator= (const Command& source)
{
	commandId		= source.commandId;
	developerId		= source.developerId;
	productId		= source.productId;

	return *this;
}


inline ULong  Command::GenerateHashValue () const
{
	ULong developerId = GetDeveloperId ();
	ULong productId   = GetProductId ();
	return ((developerId * 65599) + productId) * 65599 + GetCommandId ();
}


inline 	GSErrCode	Command::Read  (GS::IChannel& ic)
{
	ULong version;
	GSErrCode errorCode = ic.Read (version);
	if (errorCode != NoError || version != 0)
		return Error;

	errorCode = ic.Read (commandId);
	if (errorCode == NoError)
		errorCode = ic.Read (developerId);
	if (errorCode == NoError)
		errorCode = ic.Read (productId);

	return errorCode;
}


inline	GSErrCode	Command::Write 	(GS::OChannel& oc) const
{
	ULong version = 0;
	oc.Write (version);
	oc.Write (commandId);
	oc.Write (developerId);
	oc.Write (productId);

	return oc.GetOutputStatus ();
}


// --- CommandEvent ------------------------------------------------------------

class DG_DLL_EXPORT CommandEvent : public GS::Event
{
private:
	Command				command;
	CommandDescriptor*	commandDescriptor;

public:
	inline		CommandEvent (const Command& commandParam, CommandDescriptor* commandDescriptor);
			   ~CommandEvent ();

	virtual		CommandEvent*		Clone	(void) const override;

	inline const	Command&		GetCommand				(void) const;
	inline CommandDescriptor*		GetCommandDescriptor	(void) const;
};


inline CommandEvent::CommandEvent (const Command& commandParam, CommandDescriptor* commandDescriptorParam)
	:	Event				(nullptr),
		command				(commandParam),
		commandDescriptor	(commandDescriptorParam)
{
}


inline CommandEvent*	CommandEvent::Clone (void) const
{
	try {
		return new CommandEvent (*this);
	} catch (GS::OutOfMemoryException&) {
		return nullptr;
	}
}


inline const	Command& CommandEvent::GetCommand (void) const
{
	return command;
}


inline CommandDescriptor*	CommandEvent::GetCommandDescriptor (void) const
{
	return commandDescriptor;
}


// --- DoubleClickCommandEvent -------------------------------------------------

class DG_DLL_EXPORT DoubleClickCommandEvent : public CommandEvent
{
private:
	Command				command;

public:
	inline		DoubleClickCommandEvent (const Command& commandParam, CommandDescriptor* commandDescriptor);
			   ~DoubleClickCommandEvent ();

	virtual		DoubleClickCommandEvent*		Clone	(void) const override;
};


inline DoubleClickCommandEvent::DoubleClickCommandEvent (const Command& commandParam, CommandDescriptor* commandDescriptor)
	:	CommandEvent	(commandParam, commandDescriptor)
{
}


inline DoubleClickCommandEvent*	DoubleClickCommandEvent::Clone (void) const
{
	try {
		return new DoubleClickCommandEvent (*this);
	} catch (GS::OutOfMemoryException&) {
		return nullptr;
	}
}

}	// namespace DG


#endif
