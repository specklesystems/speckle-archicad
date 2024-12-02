// *****************************************************************************
// File:			DGLowLevelKeyboardHandling.hpp
//
// Description:
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:
//
// SG compatible
// *****************************************************************************

#ifndef DGLOWLEVELKEYBOARDHANDLING_HPP
#define DGLOWLEVELKEYBOARDHANDLING_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DG.h"
#include "DGItem.hpp"
#include "DGUtility.hpp"
#include "ForwardIterator.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	namespace Key {
		class Code;
	}
	class LowLevelKeyboardHandler;
}

// --- Typedefs ----------------------------------------------------------------

namespace DG {
	typedef	GS::ForwardIterator<DG::LowLevelKeyboardHandler*> KeyboardHandlerIterator;
}

// --- Class declarations ------------------------------------------------------

namespace DG {

class DG_DLL_EXPORT LowLevelKeyboardHandler
{
public:
	virtual ~LowLevelKeyboardHandler ();

	virtual EventHandlerResultType KeyPressed (const DG::Key::Code& code, DG::Item** item);
	virtual EventHandlerResultType KeyPressed (const DG::Key::Modifier& modifier, DG::Item** item);

	virtual void KeyReleased (const DG::Key::Code& code);
	virtual void KeyReleased (const DG::Key::Modifier& modifier);

	static void InstallHandler (LowLevelKeyboardHandler& handler);
	static void RemoveHandler (LowLevelKeyboardHandler& handler);
	static bool IsHandlerInstalled (LowLevelKeyboardHandler& handler);
	static KeyboardHandlerIterator EnumerateHandlers ();
};


}	// namespace DG

#endif
