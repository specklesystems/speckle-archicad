// **********************************************************************************************
// File:			FloatingMenuManager.hpp
//
// Description:		The FloatingMenuManager keeps track of the active FloatingMenus. Used in GSAT
//
// Project:
//
// Namespace:
//
// Contact person:	TBa
// **********************************************************************************************

#ifndef FLOATINGMENUMANAGER_HPP
#define FLOATINGMENUMANAGER_HPP
#pragma once

#include "TransparentWindowLibDefinitions.hpp"

namespace FloatingWindow {

class FloatingMenu;

class TRANSPARENTWINDOWLIB_DLL_EXPORT FloatingMenuManager {
	friend class FloatingMenu;

private:
	GS::Array<const FloatingMenu*> activeMenus;

	FloatingMenuManager ();
	FloatingMenuManager (const FloatingMenuManager&); // disabled
	FloatingMenuManager& operator= (const FloatingMenuManager&); // disabled

	void AddMenu (const FloatingMenu* menu);
	void RemoveMenu (const FloatingMenu* menu);
	 
public:
	static FloatingMenuManager& Instance ();
	const GS::Array<const FloatingMenu*>& GetFloatingMenus () const;
};

} // FloatingWindow

#endif // FLOATINGMENUMANAGER_HPP
