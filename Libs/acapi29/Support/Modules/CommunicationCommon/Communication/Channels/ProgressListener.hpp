
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
			 ProgressListener () = default;
			 ProgressListener (const ProgressListener&) = default;
public:
	virtual ~ProgressListener ();

// Operator overloading:
protected:
	ProgressListener&	operator = (const ProgressListener&) = default;

// Operations:
public:
	virtual void		Progress (GS::UInt64 progress) = 0;

};

}
}

#endif // COMMUNICATION_CHANNELS_PROGRESSLISTENER_HPP