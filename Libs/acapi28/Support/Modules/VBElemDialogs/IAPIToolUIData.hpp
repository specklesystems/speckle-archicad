// *****************************************************************************
// File:			IAPIToolUIData.hpp
//
// Description:		Element Settings custom panel data and observer API interface
//
// Namespace:		TBUI
//
// SG compatible
// *****************************************************************************

#ifndef IAPITOOLUIDATA_HPP
#define IAPITOOLUIDATA_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "GSRoot.hpp"
#include "VBElemDialogsExport.hpp"
#include "EventObserver.hpp"

namespace TBUI {

class IAPIToolUIDataObserver;
class ToolBoxItemUIData;

// -----------------------------------------------------------------------------
// Class:		IAPIToolUIData
//
// Description:	Data structure for the addon
// -----------------------------------------------------------------------------

class VBELEMDIALOGS_DLL_EXPORT IAPIToolUIData
{
public:
		virtual			   ~IAPIToolUIData ();

		virtual	void		AttachObserver (IAPIToolUIDataObserver* observer) = 0;
		virtual	void		DetachObserver (IAPIToolUIDataObserver* observer) = 0;

		virtual	void		SetUserData (const void* APIUserData) = 0;
		virtual	void		GetUserData (void* APIUserData) = 0;
		virtual	void		GetAPIElement (void* APIElemData, void* APIElemMemoData = nullptr) = 0;
		virtual	GSErrCode	SetAPIElement (void* APIElemData, const void * elemMask, void* APIElemMemoData = nullptr, Int32 memoMask = 0) = 0;
		virtual GSErrCode	GetAPIElementProperties (void* APIElemPropData) = 0;		// GS::Array<API_Property>* APIElemPropData
		virtual GSErrCode	SetAPIElementProperties (const void* APIElemPropData) = 0;	// const GS::Array<API_Property>* APIElemPropData
		virtual void		ApplyToGlobalDefault (void) = 0;

		virtual	ToolBoxItemUIData*		GetUIData (void) const = 0;
};


class APIElemDefaultFieldMask
{
private:
	bool	originalFieldsChanged;
	bool	regDataChanged;
	bool	propertiesChanged;

public:
	APIElemDefaultFieldMask () { originalFieldsChanged = regDataChanged = propertiesChanged = false; };

	void		SetAll (void) { originalFieldsChanged = regDataChanged = propertiesChanged = true; };

	void		SetOriginalFieldsChanged	(bool val) { originalFieldsChanged = val; };
	void		SetRegDataChanged			(bool val) { regDataChanged = val; };
	void		SetPropertiesChanged		(bool val) { propertiesChanged = val; };

	bool		GetOriginalFieldsChanged	(void)	const	 { return originalFieldsChanged; };
	bool		GetRegDataChanged			(void)	const	 { return regDataChanged; };
	bool		GetPropertiesChanged		(void)	const	 { return propertiesChanged; };
};

// -----------------------------------------------------------------------------
// Class:		IAPIToolUIDataObserver
//
// Description:	Observer for the addon
// -----------------------------------------------------------------------------

class VBELEMDIALOGS_DLL_EXPORT IAPIToolUIDataObserver : public GS::EventObserver
{
public:
		virtual 		~IAPIToolUIDataObserver ();

		virtual	void	APIElementChanged	(const APIElemDefaultFieldMask& fieldMask) = 0;
};

}	// namespace TBUI

#endif
