// *****************************************************************************
//
// Declaration of JSON exception class
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef JSON_JSONEXCEPTION_HPP
#define JSON_JSONEXCEPTION_HPP

// --------------------------------- Includes ----------------------------------

#include "JSON/JSONExport.hpp"

	// fron GSRoot
#include "GSException.hpp"

	// fron InputOutput
#include "UniString.hpp"


namespace JSON {

DECLARE_EXCEPTION_CLASS (JSONException, GS::GeneralException, Error, JSON_API)

class JSON_API MandatoryMemberNotFoundException: public JSONException {

	// Data members:
private:
	GS::UniString	m_memberName;

	// Construction / destruction:
public:
	MandatoryMemberNotFoundException (const GS::UniString& message,
									  const GS::UniString& memberName,
									  const char* fileName,
									  UInt32 lineNumber);

	virtual ~MandatoryMemberNotFoundException ();

	// Operations:
public:
	GS::UniString				GetMemberName () const;

	// Exception overrides:
public:
	virtual const char*			GetName () const;
	virtual GS::Exception*		Clone () const;
};


class JSON_API CastException: public JSONException {

	// Data members:
private:
	GS::UniString	m_expectedTypeName;
	GS::UniString	m_currentTypeName;

	// Construction / destruction:
public:
	CastException (const GS::UniString& message,
				   GS::UniString expectedTypeName,
				   GS::UniString currentTypeName,
				   const char* fileName,
				   UInt32 lineNumber);

	virtual ~CastException ();

	// Operations:
public:
	GS::UniString				GetExpectedTypeName () const;
	GS::UniString				GetCurrentTypeName () const;

	// Exception overrides:
public:
	virtual const char*			GetName () const;
	virtual GS::Exception*		Clone () const;
};


class JSON_API ValidationException: public JSONException {

	// Data members:
private:
	GS::UniString	m_invalidSchema;
	GS::UniString	m_invalidKeyword;
	GS::UniString	m_invalidDocument;

	// Construction / destruction:
public:
	ValidationException (const GS::UniString& message,
						 GS::UniString invalidSchema,
						 GS::UniString invalidKeyword,
						 GS::UniString invalidDocument,
						 const char* fileName,
						 UInt32 lineNumber);

	virtual ~ValidationException ();

	// Operations:
public:
	GS::UniString				GetInvalidSchema () const;
	GS::UniString				GetInvalidKeyword () const;
	GS::UniString				GetInvalidDocument () const;

	// Exception overrides:
public:
	virtual const char*			GetName () const;
	virtual GS::Exception*		Clone () const;
};


}

#endif
