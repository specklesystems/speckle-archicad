// *********************************************************************************************************************
// File:			UDItemInfoQuery.hpp
//
// Description:		Support functions for the AutoTest system
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:
//
// Contact person:	VM, SzaM
// *********************************************************************************************************************

// --- Includes --------------------------------------------------------------------------------------------------------

#ifndef UDITEMINFOQUERY_HPP
#define UDITEMINFOQUERY_HPP

#pragma once

#include "ObjectState.hpp"
#include "UDDefinitions.hpp"

namespace UD {

class UD_DLL_EXPORT ItemSerializer
{
public:
	static ItemSerializer& Get ();
	void SerializeDialogItem (const GS::UniString& dialogId, const GS::UniString& itemId, GS::ObjectState& os) const;
};

class UD_DLL_EXPORT DialogSerializer
{
public:
	static DialogSerializer& Get ();
	void SerializeDialog (const GS::UniString& dialogId, GS::ObjectState& os) const;
};

}

#endif
