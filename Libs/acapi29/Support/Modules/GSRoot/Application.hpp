// *****************************************************************************
//
//						         Thread related classes
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MD
//
// SG compatible
//
// *****************************************************************************

#ifndef THREAD_HPP
#define THREAD_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "MessageTarget.hpp"

namespace GS {

// ------------------------------ Predeclarations ------------------------------

class MessageTarget;


// =============================== Class Application ===========================

class GSROOT_DLL_EXPORT Application : public MessageTarget
{

friend int GSROOT_DLL_EXPORT Main (void);

private:
	static Application*		instance;

protected:
	Application ();
	virtual					~Application ();
	virtual int				Run (void);

public:
	virtual bool			Init (void) = 0;
	virtual void			Exit (void) = 0;

	virtual bool			IsIdle (void) const;

	static Application*		GetInstance ();
};

}	// namespace GS
#endif
