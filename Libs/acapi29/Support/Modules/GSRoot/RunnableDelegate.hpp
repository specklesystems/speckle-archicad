
// *****************************************************************************
//
// Declaration of RunnableDelegate class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_RUNNABLEDELEGATE_HPP
#define GS_RUNNABLEDELEGATE_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "Runnable.hpp"



// --- RunnableDelegate class --------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT RunnableDelegate : public Runnable {

// Data members:
private:
	Runnable*					m_delegate;

// Construction / destruction:
public:
	explicit RunnableDelegate (Runnable* delegate);
private:
			 RunnableDelegate (const RunnableDelegate&); // Disabled

// Operator overloading:
private:
	const RunnableDelegate&		operator = (const RunnableDelegate&); // Disabled

// Runnable interface implementation:
public:
	virtual	void				Run () override;

};

}

#endif // GS_RUNNABLEDELEGATE_HPP
