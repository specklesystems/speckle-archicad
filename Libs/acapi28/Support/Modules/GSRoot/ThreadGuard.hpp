
// *****************************************************************************
//
// Declaration of ThreadGuard class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADGUARD_HPP
#define GS_THREADGUARD_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Thread.hpp"



// --- ThreadGuard class -------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT [[nodiscard]] ThreadGuard {

// Data members:
private:
	UInt32			m_cancelAfter; // Wait timeout before cancel [in ms]
	Thread&			m_thread;

// Construction / destruction:
public:
	explicit ThreadGuard (Thread& thread, UInt32 cancelAfter = 1000U) noexcept (true);
			 ThreadGuard (ThreadGuard&) = delete;
			~ThreadGuard () noexcept (true);

// Operator overloading:
public:
	ThreadGuard&	operator = (const ThreadGuard&) = delete;

};

}

#endif // GS_THREADGUARD_HPP