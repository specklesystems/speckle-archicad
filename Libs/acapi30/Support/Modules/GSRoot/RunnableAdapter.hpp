
// *****************************************************************************
//
// Declaration of RunnableAdapter class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_RUNNABLEADAPTER_HPP
#define GS_RUNNABLEADAPTER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Callable.hpp"
#include "RunnableTask.hpp"



// --- RunnableAdapter class ---------------------------------------------------

namespace GS {

class RunnableAdapter : public Callable {

// Data members:
private:
	RunnableTask			m_task;
	Object*					m_result;

// Construction / destruction:
public:
			 RunnableAdapter (const RunnableTask& runnable, Object* result);
			 RunnableAdapter (const RunnableAdapter& rhs);
	virtual ~RunnableAdapter ();

// Operator overloading:
public:
	const RunnableAdapter&	operator = (const RunnableAdapter& rhs);

// Callable interface implementation:
public:
	virtual Object*			Call () override;

};

}

#endif // GS_RUNNABLEADAPTER_HPP
