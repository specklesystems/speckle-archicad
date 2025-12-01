
// *****************************************************************************
//
// Declaration of Message interface
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGE_HPP
#define COMMUNICATION_MESSAGE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/HeaderIterator.hpp"
#include "Communication/ParameterIterator.hpp"



// --- Message class -----------------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API Message {

// Construction / destruction:
protected:
			 Message () = default;
			 Message (const Message&) = default;
public:
	virtual ~Message ();

// Operator overloading:
protected:
	Message&						operator = (const Message&) = default;

// Operations:
public:
	virtual void					SetId (const GS::UniString& id) = 0;
	virtual const GS::UniString&	GetId () const = 0;

	virtual GS::USize				GetHeaderCount () const = 0;

	virtual bool					GetFirstHeader (const GS::UniString& headerName, GS::UniString& headerValue) const;
	virtual bool					GetFirstHeader (const GS::UniString& headerName, Header& header) const = 0;

	virtual bool					GetLastHeader (const GS::UniString& headerName, GS::UniString& headerValue) const;
	virtual bool					GetLastHeader (const GS::UniString& headerName, Header& header) const = 0;

	virtual ConstHeaderIterator		GetHeaders (const GS::UniString& headerName) const = 0;
	virtual ConstHeaderIterator		GetHeaders () const = 0;

	virtual bool					RemoveHeaders (const GS::UniString& headerName) = 0;
	virtual bool					RemoveHeader (const Header& header) = 0;

	virtual void					AddHeader (const GS::UniString& headerName, const GS::UniString& headerValue) = 0;
	virtual void					AddHeader (const Header& header) = 0;

	virtual void					SetHeader (const GS::UniString& headerName, const GS::UniString& headerValue) = 0;
	virtual void					SetHeader (const Header& header) = 0;

	virtual void					ClearHeaders () = 0;

	virtual GS::USize				GetParameterCount () const = 0;

	virtual bool					GetFirstParameter (const GS::UniString& parameterName, GS::UniString& parameterValue) const;
	virtual bool					GetFirstParameter (const GS::UniString& parameterName, Parameter& parameter) const = 0;

	virtual bool					GetLastParameter (const GS::UniString& parameterName, GS::UniString& parameterValue) const;
	virtual bool					GetLastParameter (const GS::UniString& parameterName, Parameter& parameter) const = 0;

	virtual ConstParameterIterator	GetParameters (const GS::UniString& parameterName) const = 0;
	virtual ConstParameterIterator	GetParameters () const = 0;

	virtual bool					RemoveParameters (const GS::UniString& parameterName) = 0;
	virtual bool					RemoveParameter (const Parameter& parameter) = 0;

	virtual void					AddParameter (const GS::UniString& parameterName, const GS::UniString& parameterValue) = 0;
	void							AddParameter (const GS::UniString& parameterName, const GS::UniChar::Layout* parameterValue);
	void							AddParameter (const GS::UniString& parameterName, const char* parameterValue);
	template<class T> void			AddParameter (const GS::UniString& parameterName, T parameterValue);
	virtual void					AddParameter (const Parameter& parameter) = 0;

	virtual void					SetParameter (const GS::UniString& parameterName, const GS::UniString& parameterValue) = 0;
	void							SetParameter (const GS::UniString& parameterName, const GS::UniChar::Layout* parameterValue);
	void							SetParameter (const GS::UniString& parameterName, const char* parameterValue);
	template<class T> void			SetParameter (const GS::UniString& parameterName, T parameterValue);
	virtual void					SetParameter (const Parameter& parameter) = 0;

	virtual void					ClearParameters () = 0;

};

////////////////////////////////////////////////////////////////////////////////
// Message inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// AddParameter
// -----------------------------------------------------------------------------

inline void		Message::AddParameter (const GS::UniString& parameterName, const GS::UniChar::Layout* parameterValue)
{
	if (DBVERIFY (parameterValue != nullptr)) {
		AddParameter (parameterName, GS::UniString (parameterValue));
	}
}

// -----------------------------------------------------------------------------
// AddParameter
// -----------------------------------------------------------------------------

inline void		Message::AddParameter (const GS::UniString& parameterName, const char* parameterValue)
{
	if (DBVERIFY (parameterValue != nullptr)) {
		AddParameter (parameterName, GS::UniString (parameterValue));
	}
}

// -----------------------------------------------------------------------------
// AddParameter
// -----------------------------------------------------------------------------

template<class T>
inline void		Message::AddParameter (const GS::UniString& parameterName, T parameterValue)
{
	AddParameter (Parameter (parameterName, parameterValue));
}

// -----------------------------------------------------------------------------
// SetParameter
// -----------------------------------------------------------------------------

inline void		Message::SetParameter (const GS::UniString& parameterName, const GS::UniChar::Layout* parameterValue)
{
	if (DBVERIFY (parameterValue != nullptr)) {
		AddParameter (parameterName, GS::UniString (parameterValue));
	}
}

// -----------------------------------------------------------------------------
// SetParameter
// -----------------------------------------------------------------------------

inline void		Message::SetParameter (const GS::UniString& parameterName, const char* parameterValue)
{
	if (DBVERIFY (parameterValue != nullptr)) {
		AddParameter (parameterName, GS::UniString (parameterValue));
	}
}

// -----------------------------------------------------------------------------
// SetParameter
// -----------------------------------------------------------------------------

template<class T>
inline void		Message::SetParameter (const GS::UniString& parameterName, T parameterValue)
{
	SetParameter (Parameter (parameterName, parameterValue));
}

}

#endif // COMMUNICATION_MESSAGE_HPP