
// *****************************************************************************
//
//                  Classes String, StringFB, String32, String256
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined STRING_HPP
#define STRING_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "GSDebug.hpp"
#include "GSException.hpp"
#include "FastLogger.hpp"
#include "CH.hpp"


// ============================== Class String ===============================


namespace GS {

class GSROOT_DLL_EXPORT String {
private:
	static ClassInfo	classInfo;

	char*	string;			// pointer to the allocated string buffer (if it is not nullptr)
	USize	capacity;		// capacity of the allocated string buffer in characters
	USize	length;			// length of the string in characters
	bool	ownsBuffer;		// indicates whether can be the string buffer deleted at the first
							// reallocation (or at destruction if no reallocation has been performed)
							// because it can be an external buffer set (or owned) by the user

	bool	Init (USize initialLength);

	void	EnsureCapacity (USize minCharCount);

	//*************************************** Ritt ****************************************************
	int				CheckedScanf  (const char* format, const char** formatStrs, ...) const;
	static String	CheckedPrintf (const char* format, const char** formatStrs, ...);
	//*************************************** Ritt ****************************************************

	static char*	AllocateBuffer (USize length);
	static void		DeleteBuffer   (char* buffer);

public:
		// Types

	enum OwnershipType { OriginalOwnership, PassOwnership };

		// Constructors

	String ();
	String (const char* cStr);
	String (const unsigned char* pStr);
	String (char* stringBuffer, USize bufferCapacity, OwnershipType ot = OriginalOwnership);
	String (const String& source);
	String (String&& source);
   ~String ();
	String&	operator= (const char* cStr);
	String&	operator= (const unsigned char* pStr);
	String&	operator= (const String& source);
	String&	operator= (String&& source);

		// User interface

	inline char&	operator[] (UIndex idx);
	inline char		operator[] (UIndex idx) const;

	String			operator() (UIndex from, USize range);
	const String	operator() (UIndex from, USize range) const;

	String			GetSubstring (UIndex from, USize range);
	const String	GetSubstring (UIndex from, USize range) const;

	String			GetPrefix (USize range);
	const String	GetPrefix (USize range) const;

	String			GetSuffix (USize range);
	const String	GetSuffix (USize range) const;

	inline char		GetLast (void) const;

	GSErrCode		Append (char c);
	GSErrCode		Append (const GS::String& str);
	GSErrCode		Append (const char* cStr);
	GSErrCode		Append (const char* chars, USize charCount);

	GSROOT_DLL_EXPORT friend String	operator+ (const String&  leftOp, const String&  rightOp);
	GSROOT_DLL_EXPORT friend String	operator+ (const String&  leftOp, const char* rightOp);
	GSROOT_DLL_EXPORT friend String	operator+ (const char* leftOp, const String&  rightOp);

	String&			operator+= (char ch);
	String&			operator+= (const char* str);
	String&			operator+= (const String& str);

	void			Pad	(USize toLength, char filler);

	void			Fill (char c, UIndex from = 0, USize range = MaxUSize);

	void			Delete (UIndex idx);

	void			Clear  (void);

	void			Swap   (String& rightOp);

	GSErrCode		SetLength (USize newLength);
	inline USize	GetLength (void) const;
	inline bool		IsEmpty	  (void) const;

	enum CaseComparison { CaseSensitive, CaseInsensitive };
	bool	IsEqual (const String& rightOp, CaseComparison caseComparison = CaseSensitive) const;

	enum CompareResult { Less, Equal, Greater };
	CompareResult	Compare (const String& rightOp, CaseComparison caseComparison = CaseSensitive) const;
	bool			IsLess  (const String& rightOp, CaseComparison caseComparison = CaseSensitive) const;

	inline bool		BeginsWith (char c) const;
	bool			BeginsWith (const String& str) const;
	inline bool		EndsWith   (char c) const;
	bool			EndsWith   (const String& str) const;

	inline void		SetToUpperCase (UIndex from = 0, USize range = MaxUSize);
	inline void		SetToLowerCase (UIndex from = 0, USize range = MaxUSize);

	inline String	ToUpperCase (UIndex from = 0, USize range = MaxUSize) const;
	inline String	ToLowerCase (UIndex from = 0, USize range = MaxUSize) const;


	//*************************************** Ritt Delete Begin ****************************************************
	GSErrCode		Format (const char* cStr, ...);
	//*************************************** Ritt Delete End ****************************************************

	//*************************************** Ritt ****************************************************
	template<class Type1>
	USize	SScanf (const char* format, Type1* par1) const
	{
		const char* formatStrs[2] = { GetScanfFormatCStrOf (par1), nullptr };
		return CheckedScanf (format, formatStrs, par1);
	}

	template<class Type1, class... Types>
	USize	SScanf (const char* format, Type1* par1, Types*... pars) const
	{
		const char* formatStrs[] = { GetScanfFormatCStrOf (par1), GetScanfFormatCStrOf (pars)..., nullptr };
		return CheckedScanf (format, formatStrs, par1, pars...);
	}

	template<class Type1>
	static String	SPrintf (const char* format, Type1 par1)
	{
		const char* formatStrs[2] = { GetPrintfFormatCStrOf (par1), nullptr };
		return CheckedPrintf (format, formatStrs, par1);
	}

	template<class Type1, class... Types>
	static String	SPrintf (const char* format, Type1 par1, Types... pars)
	{
		const char* formatStrs[] = { GetPrintfFormatCStrOf (par1), GetPrintfFormatCStrOf (pars)..., nullptr };
		return CheckedPrintf (format, formatStrs, par1, pars...);
	}

	//*************************************** Ritt ****************************************************

	bool	operator== (const String& rightOp) const;
	bool	operator== (const char* rightOp) const;
	bool	operator!= (const String& rightOp) const;
	bool	operator!= (const char* rightOp) const;
	bool    operator<  (const String& rightOp) const;

	const char*				ToCStr (void) const;

		// I/O

	GSErrCode	Read  (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;

		// Other

	ULong	GenerateHashValue (void) const;

		// Debug & test

	void	Print (OChannel& oc) const;
};


GSROOT_DLL_EXPORT String	operator+ (const String&  leftOp, const String&  rightOp);
GSROOT_DLL_EXPORT String	operator+ (const String&  leftOp, const char* rightOp);
GSROOT_DLL_EXPORT String	operator+ (const char* leftOp, const String&  rightOp);


GS_FORCE_INLINE void	Append (GS::FastLogger::LogComposer& logComposer, const String& string)
{
	logComposer.Append (string.ToCStr (), string.GetLength ());
}


inline char&	String::operator[] (UIndex idx)
{
	if (idx >= length) {	// length in the invalid state is 0
		DBBREAK ();
		throw IllegalArgumentException ("String::operator[]: illegal index", __FILE__, __LINE__);
	}

	return string[idx];
}


inline char		String::operator[] (UIndex idx) const
{
	if (idx >= length) {	// length in the invalid state is 0
		DBBREAK ();
		throw IllegalArgumentException ("String::operator[]: illegal index", __FILE__, __LINE__);
	}

	return string[idx];
}


inline char		String::GetLast (void) const
{
	if (DBERROR (length == 0))
		throw PreconditionException ("String::GetLast (): empty string", __FILE__, __LINE__);

	return string[length - 1];
}


inline USize	String::GetLength (void) const
{
	return length;	// length in the invalid state is 0
}


inline bool		String::IsEmpty	(void) const
{
	return (length == 0);	// length in the invalid state is 0
}


inline bool		GS::String::BeginsWith (char c) const
{
	if (IsEmpty ())
		return false;

	return (string[0] == c);

}


inline bool		GS::String::EndsWith (char c) const
{
	if (IsEmpty ())
		return false;

	return (string[length - 1] == c);
}


inline void		GS::String::SetToUpperCase (UIndex from, USize range)
{
	USize nChars = range != MaxUSize ? range : (length - from);
	if (from + nChars > length) {
		DBBREAK ();
		throw IllegalArgumentException ("String::SetToUpperCase: illegal range", __FILE__, __LINE__);
	}

	CHtoUpper (&string[from], nChars);
}


inline void		GS::String::SetToLowerCase (UIndex from, USize range)
{
	USize nChars = range != MaxUSize ? range : (length - from);
	if (from + nChars > length) {
		DBBREAK ();
		throw IllegalArgumentException ("String::SetToLowerCase: illegal range", __FILE__, __LINE__);
	}

	CHtoLower (&string[from], nChars);
}


inline GS::String		GS::String::ToUpperCase (UIndex from, USize range) const
{
	GS::String newString (*this);
	newString.SetToUpperCase (from, range);
	return newString;
}


inline GS::String		GS::String::ToLowerCase (UIndex from, USize range) const
{
	GS::String newString (*this);
	newString.SetToLowerCase (from, range);
	return newString;
}


// ______________________________ Class String _______________________________


// ============================= Class StringFB ==============================

template <USize bufferSize>
class StringFB: public String {
private:
	char	stringBuffer[bufferSize];	// fix buffer for the string

public:
		// Constructors

	inline StringFB ();
	inline StringFB (const char* cStr);
	inline StringFB (const unsigned char* pStr);
	inline StringFB (const StringFB& source);	// MSDEV 6.0: the following constructor is not sufficient
	inline StringFB (const String& source);
	inline ~StringFB ();
	inline StringFB&	operator= (const char* cStr);
	inline StringFB&	operator= (const unsigned char* pStr);
	inline StringFB&	operator= (const StringFB& source);
	inline StringFB&	operator= (const String& source);
};

typedef StringFB<32>	String32;
typedef StringFB<256>	String256;



template <USize bufferSize>
inline StringFB<bufferSize>::StringFB ():
	String (stringBuffer, bufferSize)
{
}


template <USize bufferSize>
inline StringFB<bufferSize>::StringFB (const char* cStr):
	String (stringBuffer, bufferSize)
{
	String::operator= (cStr);
}


template <USize bufferSize>
inline StringFB<bufferSize>::StringFB (const unsigned char* pStr):
String (stringBuffer, bufferSize)
{
	String::operator= (pStr);
}


template <USize bufferSize>
inline StringFB<bufferSize>::StringFB (const StringFB& source):
	String (stringBuffer, bufferSize)
{
	String::operator= (source);
}


template <USize bufferSize>
inline StringFB<bufferSize>::StringFB (const String& source):
	String (stringBuffer, bufferSize)
{
	String::operator= (source);
}


template <USize bufferSize>
inline StringFB<bufferSize>::~StringFB ()
{
}


template <USize bufferSize>
inline StringFB<bufferSize>&	StringFB<bufferSize>::operator= (const char* cStr)
{
	String::operator= (cStr);
	return *this;
}


template <USize bufferSize>
inline StringFB<bufferSize>&	StringFB<bufferSize>::operator= (const unsigned char* pStr)
{
	String::operator= (pStr);
	return *this;
}


template <USize bufferSize>
inline StringFB<bufferSize>&	StringFB<bufferSize>::operator= (const StringFB& source)
{
	String::operator= (source);
	return *this;
}


template <USize bufferSize>
inline StringFB<bufferSize>&	StringFB<bufferSize>::operator= (const String& source)
{
	String::operator= (source);
	return *this;
}

}	// namespace GS
// _____________________________ Class StringFB ______________________________


#endif
