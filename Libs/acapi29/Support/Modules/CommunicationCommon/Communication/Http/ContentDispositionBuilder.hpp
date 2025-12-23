
// *****************************************************************************
//
// Declaration of ContentDispositionBuilder class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_CONTENTDISPOSITIONBUILDER_HPP
#define COMMUNICATION_HTTP_CONTENTDISPOSITIONBUILDER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ContentDisposition.hpp"



// --- ContentDispositionBuilder class -----------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API ContentDispositionBuilder {

// Type definitions:
private:
	typedef GS::PagedArray<HeaderParameter> ParameterList;

// Data members:
private:
	GS::UniString					m_dispositionType;

	ParameterList					m_parameters;

// Operations:
public:
	ContentDispositionBuilder&		WithAttachmentDispositionType ();
	ContentDispositionBuilder&		WithInlineDispositionType ();

	ContentDispositionBuilder&		WithDispositionType (const GS::UniString& dispositionType);

	ContentDispositionBuilder&		WithParameter (const GS::UniString& parameterName, const GS::UniString& value);

	ContentDispositionBuilder&		WithFilename (const GS::UniString& filename);

	ContentDisposition				Build ();

};

}
}

#endif // COMMUNICATION_HTTP_CONTENTDISPOSITIONBUILDER_HPP