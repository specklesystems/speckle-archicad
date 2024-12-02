
// *****************************************************************************
//
// Declaration of Part interface
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http::Multipart
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_MULTIPART_PART_HPP
#define COMMUNICATION_HTTP_MULTIPART_PART_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Headers.hpp"

	// from GSRoot
#include "Ref.hpp"



// --- Part class --------------------------------------------------------------

namespace Communication {
namespace Http {
namespace Multipart {

class COMMUNICATIONCOMMON_API Part {

// Construction / destruction:
protected:
			 Part () = default;
			 Part (const Part&) = default;
public:
	virtual ~Part ();

// Operator overloading:
protected:
	Part&					operator = (const Part&) = default;

// Operations:
public:
	virtual const Headers&	GetHeaders () const = 0;

	virtual bool			Equals (const Part& rhs) const = 0;

	virtual Part*			Clone () const = 0;

};

typedef GS::Ref<Part> PartRef;

}
}
}

#endif // COMMUNICATION_HTTP_MULTIPART_PART_HPP