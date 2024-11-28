
// *****************************************************************************
//
// Declaration of ProgressListener interface
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_PROGRESSLISTENER_HPP
#define COMMUNICATION_CHANNELS_PROGRESSLISTENER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"



// --- ProgressListener class --------------------------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API ProgressListener {

// Construction / destruction:
protected:
			 ProgressListener ();
			 ProgressListener (const ProgressListener&);
public:
	virtual ~ProgressListener ();

// Operator overloading:
protected:
	const ProgressListener&		operator = (const ProgressListener&);

// Operations:
public:
	virtual void				Progress (GS::UInt64 progress) = 0;

};

////////////////////////////////////////////////////////////////////////////////
// ProgressListener inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ProgressListener::ProgressListener ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ProgressListener::ProgressListener (const ProgressListener&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ProgressListener&	ProgressListener::operator = (const ProgressListener&)
{
	return *this;
}

}
}

#endif // COMMUNICATION_CHANNELS_PROGRESSLISTENER_HPP