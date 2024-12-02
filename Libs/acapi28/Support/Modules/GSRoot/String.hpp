
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
#include "FastLogger.hpp"
#include "CH.hpp"

// from Standard Library
#include <iosfwd>
#include <string_view>


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

	void			Init (USize initialLength);

	int				CheckedScanf  (const char* format, const char** formatStrs, ...) const;
	static String	CheckedPrintf (const char* format, const char** formatStrs, ...);

	static char*	AllocateBuffer (USize length);
	static void		DeleteBuffer   (char* buffer);

protected:
	enum ConstructWithFixBufferSelector { ConstructWithFixBuffer };

	String (ConstructWithFixBufferSelector, char* stringBuffer, USize bufferCapacity);

public:
		// Constructors

	String ();
	String (const char* cStr);
	String (std::string_view str);
	String (const unsigned char* pStr);
	String (const String& source);
	String (String&& source);
   ~String ();
	String&	operator= (const char* cStr);
	String&	operator= (std::string_view str);
	String&	operator= (const unsigned char* pStr);
	String&	operator= (const String& source);
	String&	operator= (String&& source);

		// User interface

	char&			operator[] (UIndex idx) gs_lifebound;
	char			operator[] (UIndex idx) const;

	String			operator() (UIndex from, USize range) const;

	String			GetSubstring (UIndex from, USize range) const;

	String			GetPrefix (USize range) const;

	String			GetSuffix (USize range) const;

	char			GetLast (void) const;

	void			Append (char c);
	void			Append (const char* cStr);
	void			Append (std::string_view str);
	void			Append (const String& str);
	void			Append (const char* chars, USize charCount);

	GSROOT_DLL_EXPORT friend bool	operator== (const String& leftOp, const String&    rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const String& leftOp, const char*      rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const String& leftOp, std::string_view rightOp);

	GSROOT_DLL_EXPORT friend String	operator+  (const String&    leftOp, const String&    rightOp);
	GSROOT_DLL_EXPORT friend String	operator+  (const String&    leftOp, const char*      rightOp);
	GSROOT_DLL_EXPORT friend String	operator+  (const char*      leftOp, const String&    rightOp);
	GSROOT_DLL_EXPORT friend String	operator+  (const String&    leftOp, std::string_view rightOp);
	GSROOT_DLL_EXPORT friend String	operator+  (std::string_view leftOp, const String&    rightOp);

	String&			operator+= (char c);
	String&			operator+= (const char* cStr);
	String&			operator+= (std::string_view str);
	String&			operator+= (const String& str);

	void			Pad	(USize toLength, char filler);

	void			Fill (char c, UIndex from = 0, USize range = MaxUSize);

	void			Delete (UIndex idx);

	void			Clear  (void);

	void			Swap   (String& rightOp);

	void			SetLength (USize newLength);
	USize			GetLength (void) const;
	bool			IsEmpty	  (void) const;

	void			EnsureCapacity (USize minCharCount);

	bool			IsEqual (const String& rightOp, CaseComparison caseComparison = CaseSensitive) const;

	enum CompareResult { Less, Equal, Greater };
	CompareResult	Compare (const String& rightOp, CaseComparison caseComparison = CaseSensitive) const;
	bool			IsLess  (const String& rightOp, CaseComparison caseComparison = CaseSensitive) const;

	bool			BeginsWith (char c) const;
	bool			BeginsWith (const String& str) const;
	bool			EndsWith   (char c) const;
	bool			EndsWith   (const String& str) const;

	void			SetToUpperCase (UIndex from = 0, USize range = MaxUSize);
	void			SetToLowerCase (UIndex from = 0, USize range = MaxUSize);

	String			ToUpperCase (UIndex from = 0, USize range = MaxUSize) const;
	String			ToLowerCase (UIndex from = 0, USize range = MaxUSize) const;

	template<class Type1>
	USize			SScanf (const char* format, Type1* par1) const
	{
		const char* formatStrs[2] = { GetScanfFormatCStrOf (par1), nullptr };
		return CheckedScanf (format, formatStrs, par1);
	}

	template<class Type1, class... Types>
	USize			SScanf (const char* format, Type1* par1, Types*... pars) const
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

	const char*			ToCStr (void) const gs_lifebound;

	std::string_view	ToStringView (void) const gs_lifebound;

		// I/O

	GSErrCode		Read  (GS::IChannel& ic);
	GSErrCode		Write (GS::OChannel& oc) const;

		// Other

	ULong			GenerateHashValue (void) const;

		// Debug & test

	GSROOT_DLL_EXPORT friend std::ostream&	operator<< (std::ostream&, const String&);
};


GSROOT_DLL_EXPORT bool		operator== (const String&    leftOp, const String&    rightOp);
GSROOT_DLL_EXPORT bool		operator== (const String&    leftOp, const char*      rightOp);
GSROOT_DLL_EXPORT bool		operator== (const char*      leftOp, const String&    rightOp);
GSROOT_DLL_EXPORT bool		operator== (const String&    leftOp, std::string_view rightOp);
GSROOT_DLL_EXPORT bool		operator== (std::string_view leftOp, const String&    rightOp);

GSROOT_DLL_EXPORT bool		operator!= (const String&    leftOp, const String&    rightOp);
GSROOT_DLL_EXPORT bool		operator!= (const String&    leftOp, const char*      rightOp);
GSROOT_DLL_EXPORT bool		operator!= (const char*      leftOp, const String&    rightOp);
GSROOT_DLL_EXPORT bool		operator!= (const String&    leftOp, std::string_view rightOp);
GSROOT_DLL_EXPORT bool		operator!= (std::string_view leftOp, const String&    rightOp);

GSROOT_DLL_EXPORT bool		operator<  (const String&    leftOp, const String&    rightOp);
GSROOT_DLL_EXPORT bool		operator<  (const String&    leftOp, const char*      rightOp);
GSROOT_DLL_EXPORT bool		operator<  (const char*      leftOp, const String&    rightOp);
GSROOT_DLL_EXPORT bool		operator<  (const String&    leftOp, std::string_view rightOp);
GSROOT_DLL_EXPORT bool		operator<  (std::string_view leftOp, const String&    rightOp);

GSROOT_DLL_EXPORT String	operator+  (const String&    leftOp, const String&    rightOp);
GSROOT_DLL_EXPORT String	operator+  (const String&    leftOp, const char*      rightOp);
GSROOT_DLL_EXPORT String	operator+  (const char*      leftOp, const String&    rightOp);
GSROOT_DLL_EXPORT String	operator+  (const String&    leftOp, std::string_view rightOp);
GSROOT_DLL_EXPORT String	operator+  (std::string_view leftOp, const String&    rightOp);


GS_FORCE_INLINE void	Append (GS::FastLogger::LogComposer& logComposer, const String& string)
{
	logComposer.Append (string.ToCStr (), string.GetLength ());
}


inline char&	String::operator[] (UIndex idx)
{
	DBASSERT (idx < length);

	return string[idx];
}


inline char		String::operator[] (UIndex idx) const
{
	DBASSERT (idx < length);

	return string[idx];
}


inline char		String::GetLast (void) const
{
	DBASSERT (length != 0);

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
	DBASSERT (from + nChars <= length);

	CHtoUpper (&string[from], nChars);
}


inline void		GS::String::SetToLowerCase (UIndex from, USize range)
{
	USize nChars = range != MaxUSize ? range : (length - from);
	DBASSERT (from + nChars <= length);

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


inline std::string_view		GS::String::ToStringView (void) const
{
	return { ToCStr (), GetLength () };
}


// ______________________________ Class String _______________________________


// ============================= Class StringFB ==============================

template <USize BufferSize>
class StringFB: public String {
private:
	char	stringBuffer[BufferSize];	// fix buffer for the string

public:
		// Constructors

	StringFB ();
	StringFB (const char* cStr);
	StringFB (std::string_view str);
	StringFB (const unsigned char* pStr);
	StringFB (const StringFB& source);	// MSDEV 6.0: the following constructor is not sufficient
	StringFB (const String& source);
	StringFB (String&&);

	StringFB&	operator= (const char* cStr);
	StringFB&	operator= (std::string_view str);
	StringFB&	operator= (const unsigned char* pStr);
	StringFB&	operator= (const StringFB& source);
	StringFB&	operator= (const String& source);
	StringFB&	operator= (String&&);
};

typedef StringFB<32>	String32;
typedef StringFB<256>	String256;



template <USize BufferSize>
StringFB<BufferSize>::StringFB ():
	String (ConstructWithFixBuffer, stringBuffer, BufferSize)
{
}


template <USize BufferSize>
StringFB<BufferSize>::StringFB (const char* cStr):
	String (ConstructWithFixBuffer, stringBuffer, BufferSize)
{
	String::operator= (cStr);
}


template <USize BufferSize>
StringFB<BufferSize>::StringFB (std::string_view str):
	String (ConstructWithFixBuffer, stringBuffer, BufferSize)
{
	String::operator= (str);
}


template <USize BufferSize>
StringFB<BufferSize>::StringFB (const unsigned char* pStr):
String (ConstructWithFixBuffer, stringBuffer, BufferSize)
{
	String::operator= (pStr);
}


template <USize BufferSize>
StringFB<BufferSize>::StringFB (const StringFB& source):
	String (ConstructWithFixBuffer, stringBuffer, BufferSize)
{
	String::operator= (source);
}


template <USize BufferSize>
StringFB<BufferSize>::StringFB (const String& source):
	String (ConstructWithFixBuffer, stringBuffer, BufferSize)
{
	String::operator= (source);
}


template <USize BufferSize>
StringFB<BufferSize>::StringFB (String&& source):
	String (ConstructWithFixBuffer, stringBuffer, BufferSize)
{
	String::operator= (std::move (source));
}


template <USize BufferSize>
StringFB<BufferSize>&	StringFB<BufferSize>::operator= (const char* cStr)
{
	String::operator= (cStr);
	return *this;
}


template <USize BufferSize>
StringFB<BufferSize>&	StringFB<BufferSize>::operator= (std::string_view str)
{
	String::operator= (str);
	return *this;
}


template <USize BufferSize>
StringFB<BufferSize>&	StringFB<BufferSize>::operator= (const unsigned char* pStr)
{
	String::operator= (pStr);
	return *this;
}


template <USize BufferSize>
StringFB<BufferSize>&	StringFB<BufferSize>::operator= (const StringFB& source)
{
	String::operator= (source);
	return *this;
}


template <USize BufferSize>
StringFB<BufferSize>&	StringFB<BufferSize>::operator= (const String& source)
{
	String::operator= (source);
	return *this;
}


template <USize BufferSize>
StringFB<BufferSize>&	StringFB<BufferSize>::operator= (String&& source)
{
	String::operator= (std::move (source));
	return *this;
}


}	// namespace GS
// _____________________________ Class StringFB ______________________________


using namespace std::string_view_literals;


#endif
