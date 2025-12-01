
// *****************************************************************************
//
// Declaration of HeaderBuilder class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HEADERBUILDER_HPP
#define COMMUNICATION_HEADERBUILDER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/HeaderElement.hpp"


// --- HeaderBuilder class -------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API HeaderBuilder {

// Nested classes:
private:
	class HeaderElementBuilder {

	// Friend classes:
	friend class HeaderBuilder;

	// Type definitions:
	private:
		typedef GS::PagedArray<HeaderParameter> HeaderParameters;

	// Data members:
	private:
		HeaderBuilder*			m_parent;

		HeaderParameters		m_parameters;

		GS::UniString			m_value;
		GS::UniString			m_name;

	// Construction / destruction:
	private:
		explicit HeaderElementBuilder (HeaderBuilder* parent, const GS::UniString& name, const GS::UniString& value);
		
	// Operations:
	public:
		HeaderElementBuilder&	AddParameter (const GS::UniString& name, const GS::UniString value);
		HeaderElementBuilder&	AddParameter (const GS::UniString& name);


		HeaderElementBuilder&	AddElement (const GS::UniString& name, const GS::UniString& value);
		HeaderElementBuilder&	AddElement (const GS::UniString& name) const;

		GS::UniString			Build ();

	// Implementation:
	private:
		HeaderElement			BuildHeaderElement ();

	};

// Type definitions:
private:
	typedef GS::PagedArray<HeaderElementBuilder> HeaderElementBuilders;

// Data members:
private:
	HeaderElementBuilders		m_headerElementBuilders;

// Operations:
public:
	HeaderElementBuilder&		AddElement (const GS::UniString& name, const GS::UniString& value);
	HeaderElementBuilder&		AddElement (const GS::UniString& name);

	GS::UniString				Build ();

};

}

#endif // COMMUNICATION_HEADERBUILDER_HPP