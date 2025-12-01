// *********************************************************************************************************************
// Description:		A class representing an error code (GSErrCode) with optional error message (UniString) and error
//					object (ObjectState).
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef ERRORSTATUS_HPP
#define ERRORSTATUS_HPP

#pragma once


#include "OptionalOnHeap.hpp"

namespace GS { class ObjectState; }
namespace GS { class String; }
namespace GS { class UniString; }


namespace GS {


// === class ErrorStatus ===============================================================================================

class GSROOT_DLL_EXPORT ErrorStatus {
private:
	GSErrCode					errorCode;
	OptionalOnHeap<UniString>	errorMessage;
	OptionalOnHeap<ObjectState>	errorObject;

public:
	ErrorStatus ();

	ErrorStatus (GSErrCode errorCode);
	ErrorStatus (const UniString& errorMessage);
	ErrorStatus (UniString&& errorMessage);
	ErrorStatus (const char* errorMessage);
	ErrorStatus (const String& errorMessage);
	ErrorStatus (const ObjectState& errorObject);
	ErrorStatus (ObjectState&& errorObject);
	ErrorStatus (bool) = delete;

	ErrorStatus (GSErrCode errorCode, const UniString& errorMessage);
	ErrorStatus (GSErrCode errorCode, UniString&& errorMessage);
	ErrorStatus (GSErrCode errorCode, const ObjectState& errorObject);
	ErrorStatus (GSErrCode errorCode, ObjectState&& errorObject);
	ErrorStatus (const UniString& errorMessage, const ObjectState& errorObject);
	ErrorStatus (const UniString& errorMessage, ObjectState&& errorObject);
	ErrorStatus (UniString&& errorMessage, const ObjectState& errorObject);
	ErrorStatus (UniString&& errorMessage, ObjectState&& errorObject);

	ErrorStatus (GSErrCode errorCode, const UniString& errorMessage, const ObjectState& errorObject);
	ErrorStatus (GSErrCode errorCode, const UniString& errorMessage, ObjectState&& errorObject);
	ErrorStatus (GSErrCode errorCode, UniString&& errorMessage, const ObjectState& errorObject);
	ErrorStatus (GSErrCode errorCode, UniString&& errorMessage, ObjectState&& errorObject);

	ErrorStatus (const ErrorStatus& source);
	ErrorStatus (ErrorStatus&& source);
	~ErrorStatus ();

	ErrorStatus&		operator= (const ErrorStatus& source);
	ErrorStatus&		operator= (ErrorStatus&& source);

	ErrorStatus&		operator= (GSErrCode newErrorCode);
	ErrorStatus&		operator= (const UniString& newErrorMessage);
	ErrorStatus&		operator= (const ObjectState& newErrorObject);
	ErrorStatus&		operator= (bool) = delete;

	bool				operator== (GSErrCode rightOp) const;
	bool				operator!= (GSErrCode rightOp) const;

	void				Clear ();

	void				Set (GSErrCode newErrorCode);
	void				Set (const UniString& newErrorMessage);
	void				Set (UniString&& newErrorMessage);
	void				Set (const ObjectState& newErrorObject);
	void				Set (ObjectState&& newErrorObject);
	void				Set (bool) = delete;

	void				Set (GSErrCode newErrorCode, const UniString& newErrorMessage);
	void				Set (GSErrCode newErrorCode, UniString&& newErrorMessage);
	void				Set (GSErrCode newErrorCode, const ObjectState& newErrorObject);
	void				Set (GSErrCode newErrorCode, ObjectState&& newErrorObject);
	void				Set (const UniString& newErrorMessage, const ObjectState& newErrorObject);
	void				Set (const UniString& newErrorMessage, ObjectState&& newErrorObject);
	void				Set (UniString&& newErrorMessage, const ObjectState& newErrorObject);
	void				Set (UniString&& newErrorMessage, ObjectState&& newErrorObject);

	void				Set (GSErrCode newErrorCode, const UniString& newErrorMessage, const ObjectState& newErrorObject);
	void				Set (GSErrCode newErrorCode, const UniString& newErrorMessage, ObjectState&& newErrorObject);
	void				Set (GSErrCode newErrorCode, UniString&& newErrorMessage, const ObjectState& newErrorObject);
	void				Set (GSErrCode newErrorCode, UniString&& newErrorMessage, ObjectState&& newErrorObject);

	void				DeleteErrorMessage ();
	void				DeleteErrorObject ();

	ErrorStatus&		SetErrorCode (GSErrCode newErrorCode);
	ErrorStatus&		SetErrorCode (bool) = delete;
	ErrorStatus&		SetErrorMessage (const UniString& newErrorMessage);
	ErrorStatus&		SetErrorMessage (UniString&& newErrorMessage);
	ErrorStatus&		SetErrorObject (const ObjectState& newErrorObject);
	ErrorStatus&		SetErrorObject (ObjectState&& newErrorObject);

	bool				IsOK () const;
	bool				IsError () const;

	bool				HasErrorMessage () const;
	bool				HasErrorObject () const;

	GSErrCode			GetErrorCode () const;
	const UniString&	GetErrorMessage () const& gs_lifebound;
	UniString&&			GetErrorMessage () && gs_lifebound;
	const ObjectState&	GetErrorObject () const& gs_lifebound;
	ObjectState&&		GetErrorObject () && gs_lifebound;
};


// === ErrorStatus inline methods ======================================================================================

inline bool		ErrorStatus::operator== (GSErrCode rightOp) const
{
	return errorCode == rightOp;
}


inline bool		ErrorStatus::operator!= (GSErrCode rightOp) const
{
	return errorCode != rightOp;
}


inline bool		ErrorStatus::IsOK () const
{
	return errorCode == NoError;
}


inline bool		ErrorStatus::IsError () const
{
	return errorCode != NoError;
}


}	// namespace GS


#endif
