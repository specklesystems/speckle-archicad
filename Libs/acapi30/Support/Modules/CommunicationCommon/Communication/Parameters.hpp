
// *****************************************************************************
//
// Declaration of Parameters class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_PARAMETERS_HPP
#define COMMUNICATION_PARAMETERS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/ParameterIterator.hpp"

	// from GSRoot
#include "HashTable.hpp"



// --- Parameters class --------------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API Parameters {

// Type definitions:
private:
	typedef GS::HashTable<GS::UniString, GS::PagedArray<Parameter> > ParameterMap;

// Data members:
private:
	ParameterMap				m_parameters;

// Operations:
public:
	GS::USize					GetSize () const;

	bool						GetFirstParameter (const GS::UniString& parameterName, Parameter& parameter) const;
	bool						GetLastParameter (const GS::UniString& parameterName, Parameter& parameter) const;

	ConstParameterIterator		GetParameters (const GS::UniString& parameterName) const;
	ConstParameterIterator		GetParameters () const;

	bool						RemoveParameters (const GS::UniString& parameterName);
	bool						RemoveParameter (const Parameter& parameter);

	void						AddParameter (const GS::UniString& parameterName, const GS::UniString& parameterValue);
	void						AddParameter (const Parameter& parameter);

	void						SetParameter (const GS::UniString& parameterName, const GS::UniString& parameterValue);
	void						SetParameter (const Parameter& parameter);

	void						Clear ();

};

}

#endif // COMMUNICATION_PARAMETERS_HPP