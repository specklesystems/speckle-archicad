// *****************************************************************************
// File:			IAPIAttrUIData.hpp
//
// Description:		Attribute Settings custom panel data and observer API interface
//
// Namespace:		VBAD
//
// SG compatible
// *****************************************************************************

#ifndef IAPIATTRUIDATA_HPP
#define IAPIATTRUIDATA_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "GSRoot.hpp"
#include "VBElemDialogsExport.hpp"

namespace VBAD {

class IAPIAttrUIDataObserver;

// -----------------------------------------------------------------------------
// Class:		IAPIAttrUIData
//
// Description:	Data structure for the addon
// -----------------------------------------------------------------------------

class VBELEMDIALOGS_DLL_EXPORT IAPIAttrUIData
{
public:
		virtual ~IAPIAttrUIData ();

		virtual	void	AttachObserver (IAPIAttrUIDataObserver* observer) = 0;
		virtual	void	DetachObserver (IAPIAttrUIDataObserver* observer) = 0;

		virtual	void	SetUserData (const void* APIUserData) = 0;
		virtual	void	GetUserData (void* APIUserData) = 0;
		virtual	void	GetAPIAttribute (void* APIAttributeData) = 0;
};

class APIAttributeFieldMask
{
private:
	bool	originalFieldsChanged;
	bool	regDataChanged;

public:
	APIAttributeFieldMask () { originalFieldsChanged = regDataChanged = false; };

	void		SetAll (void) { originalFieldsChanged = regDataChanged = true; };

	void		SetOriginalFieldsChanged	(bool val) { originalFieldsChanged = val; };
	void		SetRegDataChanged			(bool val) { regDataChanged = val; };

	bool		GetOriginalFieldsChanged	(void)	const	 { return originalFieldsChanged; };
	bool		GetRegDataChanged			(void)	const	 { return regDataChanged; };
};


// -----------------------------------------------------------------------------
// Class:		IAPIAttrUIDataObserver
//
// Description:	Observer for the addon
// -----------------------------------------------------------------------------

class VBELEMDIALOGS_DLL_EXPORT IAPIAttrUIDataObserver : public GS::EventObserver
{
public:
		virtual 		~IAPIAttrUIDataObserver ();

		virtual	void	APIAttributeChanged	(const APIAttributeFieldMask& fieldMask) = 0;
};

}	// namespace VBAD

#endif
