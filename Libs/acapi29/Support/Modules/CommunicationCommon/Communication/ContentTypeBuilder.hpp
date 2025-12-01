
// *****************************************************************************
//
// Declaration of ContentTypeBuilder class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CONTENTTYPEBUILDER_HPP
#define COMMUNICATION_CONTENTTYPEBUILDER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/ContentType.hpp"



// --- ContentTypeBuilder class ------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API ContentTypeBuilder {

// Type definitions:
private:
	typedef GS::PagedArray<HeaderParameter> ParameterList;

// Data members:
private:
	ParameterList			m_parameters;

	GS::UniString			m_mediaType;
	GS::UniString			m_charset;

// Operations:
public:
	ContentTypeBuilder&		AddParameter (const GS::UniString& parameterName, const GS::UniString& value);

	ContentTypeBuilder&		SetMediaType (const GS::UniString& mediaType);
	ContentTypeBuilder&		SetCharset (const GS::UniString& charset);

	ContentType				Build ();

};

}

#endif // COMMUNICATION_CONTENTTYPEBUILDER_HPP