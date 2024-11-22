
// *****************************************************************************
//
//                                 Class CString
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined CSTRING_HPP
#define CSTRING_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

// from GSRoot
#include "BM.hpp"

// =============================== Class CString ===============================

namespace IO {

namespace CLib {
	IO_DLL_EXPORT	USize	StrLength (const char* cStr);
	IO_DLL_EXPORT	char*	StrCopy (char* destination, const char* source);
	IO_DLL_EXPORT	char*	StrCatenate (char* destination, const char* source);
}


template <USize bufferSize = 16>
class CString {
private:
	char	buffer[bufferSize];	// buffer of fixed size for smaller strings
	char*	cStr;				// if it is not nullptr then points to the stored string (used for longer strings)
	bool	isValid;			// indicates whether is object's state valid

	void	Set (const char* str);

public:
		// Constructors

	inline CString ();
	inline CString (const char* str);
	inline CString (const CString& source);
	inline ~CString ();
	inline CString&	operator= (const char* str);
	inline CString&	operator= (const CString& source);

		// User interface

	inline GSErrCode	GetStatus (void) const;

	inline void			Set (UIndex idx, char c);

	inline GSErrCode	Append (const char* str);
	inline void			Clear  (void);

	inline	operator const char* () const;
};



template <USize bufferSize>
inline CString<bufferSize>::CString ()
{
	buffer[0] = '\0';
	cStr = nullptr;
	isValid = true;
}


template <USize bufferSize>
inline CString<bufferSize>::CString (const char* str)
{
	DBASSERT (str != nullptr);

	buffer[0] = '\0';
	cStr = nullptr;
	isValid = true;

	Set (str);
}


template <USize bufferSize>
inline CString<bufferSize>::CString (const CString& source)
{
	DBASSERT (&source != nullptr);

	buffer[0] = '\0';
	cStr = nullptr;
	isValid = source.isValid;

	if (isValid)
		Set (source);
}


template <USize bufferSize>
inline CString<bufferSize>::~CString ()
{
	if (cStr != nullptr)
		BMpFree (cStr);
}


template <USize bufferSize>
inline CString<bufferSize>&		CString<bufferSize>::operator= (const char* str)
{
	IOASSERT (str != nullptr, *this);

	isValid = true;

	Set (str);

	return *this;
}


template <USize bufferSize>
inline CString<bufferSize>&		CString<bufferSize>::operator= (const CString& source)
{
	IOASSERT (&source != nullptr, *this);

	if (this != &source) {
		isValid = source.isValid;
		if (isValid)
			Set (source);
	}

	return *this;
}


template <USize bufferSize>
GSErrCode	CString<bufferSize>::GetStatus (void) const
{
	return (isValid ? NoError : ErrMemoryFull);
}


template <USize bufferSize>
inline void		CString<bufferSize>::Set (UIndex idx, char c)
{
	// DBASSERT (idx < CLib::StrLength (*this));	// no index checking is performed because it is too slow
	DBASSERT (c != '\0');

	if (cStr != nullptr)
		cStr[idx] = c;
	else
		buffer[idx] = c;
}


template <USize bufferSize>
inline GSErrCode	CString<bufferSize>::Append (const char* str)
{
	IOASSERT (str != nullptr, Error);

	if (!isValid)
		return ErrMemoryFull;

	const char* oldContent = *this;

	USize newLength = CLib::StrLength (oldContent) + CLib::StrLength (str);
	char* newCStr = nullptr;

	if (newLength + 1 <= bufferSize) {
		CLib::StrCatenate (buffer, str);
	} else {
		newCStr = BMpAll ((newLength + 1) * sizeof (char));
		if (newCStr == nullptr) {
			isValid = false;
			return ErrMemoryFull;
		}

		CLib::StrCopy (newCStr, oldContent);
		CLib::StrCatenate (newCStr, str);
	}

	if (cStr != nullptr)
		BMpFree (cStr);
	cStr = newCStr;

	return NoError;
}


template <USize bufferSize>
inline void		CString<bufferSize>::Clear (void)
{
	isValid = true;

	if (cStr != nullptr) {
		BMpFree (cStr);
		cStr = nullptr;
	}
	buffer[0] = '\0';
}


template <USize bufferSize>
inline CString<bufferSize>::operator const char* () const
{
	IOASSERT (isValid, nullptr);

	return (cStr != nullptr) ? cStr : buffer;
}


template <USize bufferSize>
void	CString<bufferSize>::Set (const char* str)
{
	USize strLen = CLib::StrLength (str);

	if (cStr != nullptr) {
		if (CLib::StrLength (cStr) >= strLen) {
			CLib::StrCopy (cStr, str);
			return;
		} else {
			BMpFree (cStr);
			cStr = nullptr;
		}
	}

	if (strLen >= bufferSize) {
		cStr = BMpAll ((strLen + 1) * sizeof (char));
		if (cStr == nullptr) {
			isValid = false;
			return;
		}
		CLib::StrCopy (cStr, str);
	} else {
		CLib::StrCopy (buffer, str);
	}
}

}	// namespace IO
// _______________________________ Class CString _______________________________


#endif
