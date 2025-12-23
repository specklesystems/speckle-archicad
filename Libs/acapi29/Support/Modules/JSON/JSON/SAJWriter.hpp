
// *****************************************************************************
//
// Declaration of SAJWriter class
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef JSON_SAJWRITER_HPP
#define JSON_SAJWRITER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "JSON/JSONExport.hpp"
#include "JSON/JSONException.hpp"
#include "JSON/Value.hpp"

#include "OBinaryChannel.hpp"


namespace JSON {

// -------------------------------- SAJWriter ----------------------------------

class JSON_API SAJWriter {

private:
	void*		m_writerImp;

public:
	SAJWriter (GS::OBinaryChannel& destination, bool formatOutput = false, int numberOfDigits = 10);
	virtual ~SAJWriter ();

	// Common operations
	SAJWriter&	WriteNull ();
	SAJWriter&	Write (bool value);
	SAJWriter&	Write (Int8 value);
	SAJWriter&	Write (UInt8 value);
	SAJWriter&	Write (Int16 value);
	SAJWriter&	Write (UInt16 value);
	SAJWriter&	Write (Int32 value);
	SAJWriter&	Write (UInt32 value);
	SAJWriter&	Write (Int64 value);
	SAJWriter&	Write (UInt64 value);
	SAJWriter&	Write (double value);
	SAJWriter&	Write (const GS::UniString& value);
	SAJWriter&	Write (const char* value);
	SAJWriter&	Write (const ValueRef& value);

	// Array operations
	SAJWriter&	WriteStartArray ();
	SAJWriter&	WriteEndArray ();

	// Object operations
	SAJWriter&	WriteStartObject ();
	SAJWriter&	WriteEndObject ();

	SAJWriter&	WriteStartObjectMember (const GS::UniString& name);
	SAJWriter&	WriteStartArrayMember (const GS::UniString& name);

	SAJWriter&	WriteMemberName (const GS::UniString& name);

	SAJWriter&	WriteNullMember (const GS::UniString& name);
	SAJWriter&	WriteMember (const GS::UniString& name, bool value);
	SAJWriter&	WriteMember (const GS::UniString& name, Int8 value);
	SAJWriter&	WriteMember (const GS::UniString& name, UInt8 value);
	SAJWriter&	WriteMember (const GS::UniString& name, Int16 value);
	SAJWriter&	WriteMember (const GS::UniString& name, UInt16 value);
	SAJWriter&	WriteMember (const GS::UniString& name, Int32 value);
	SAJWriter&	WriteMember (const GS::UniString& name, UInt32 value);
	SAJWriter&	WriteMember (const GS::UniString& name, Int64 value);
	SAJWriter&	WriteMember (const GS::UniString& name, UInt64 value);
	SAJWriter&	WriteMember (const GS::UniString& name, double value);
	SAJWriter&	WriteMember (const GS::UniString& name, const GS::UniString& value);
	SAJWriter&	WriteMember (const GS::UniString& name, const char* value);
	SAJWriter&	WriteMember (const GS::UniString& name, const ValueRef& value);

	SAJWriter&	Write (const std::function<SAJWriter& (SAJWriter&)>& writer);

	template <class T, class Container>
	SAJWriter&	Write (const Container& items, const std::function<SAJWriter& (SAJWriter&, const T&)>& itemWriter)
	{
		if (DBERROR (itemWriter == nullptr)) {
			throw GS::IllegalArgumentException ("Failed to write json with write function: function is null", __FILE__, __LINE__);
		}

		SAJWriter* writer = this;

		for (auto it = items.Begin (); it != nullptr; ++it) {
			writer = &itemWriter (*writer, *it);
		}

		return *writer;
	}

	bool		CheckEnd ();

protected:
	SAJWriter ();
	void			Init (GS::OBinaryChannel& destination, bool formatOutput = false, int numberOfDigits = 10);
	virtual	void	Flush ();

private:
	SAJWriter& operator= (const SAJWriter& source);	// disabled
	SAJWriter (const SAJWriter& source);			// disabled

	void		CheckStarted ();
	void		CheckCanWritePrimitiveValue ();
	void		CheckCanWriteContainer ();
	void		CheckCanWriteMemberName ();

};

// ----------------------------- SAJStringWriter -------------------------------

class JSON_API SAJStringWriter: public SAJWriter {

private:
	void*		m_stringWriter;

public:
	SAJStringWriter (GS::UniString& destination, bool formatOutput = false, int numberOfDigits = 10);
	virtual ~SAJStringWriter ();

protected:
	virtual	void	Flush () override;

private:
	SAJStringWriter& operator= (const SAJStringWriter& source);	// disabled
	SAJStringWriter (const SAJStringWriter& source);			// disabled

};

}

#endif
