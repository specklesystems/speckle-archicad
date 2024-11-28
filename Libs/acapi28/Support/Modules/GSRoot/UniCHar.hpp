
// *****************************************************************************
//
//                                 Class UniChar
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined UNICHAR_HPP
#define UNICHAR_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "CH.hpp"
#include "HashCommon.hpp"

// from STL
#include <string_view>


// =============================== Class UniChar ===============================

namespace GS {

class GSROOT_DLL_EXPORT UniChar {
public:
	using Layout = Utf16Char;	// defines the physical layout of Unicode characters

private:
	Layout uniChar = 0;	// stores a Unicode character

	static Layout	CharToUnicode (char c);
	static char		UnicodeToChar (Layout u);

	enum NormalizationFormType {
		NormalizationFormD,			// Canonical Decomposition
		NormalizationFormC,			// Canonical Decomposition, followed by Canonical Composition
		NormalizationFormKD,		// Compatibility Decomposition
		NormalizationFormKC			// Compatibility Decomposition, followed by Canonical Composition
	};

	static void		ConvertToUnicodeNormalizationForm (const Layout* source, USize sourceLength, NormalizationFormType nf, Layout** result, USize* resultLength);

public:
		// Constructors

	UniChar () = default;

	constexpr UniChar (Layout u);
	constexpr UniChar (char16_t u);

	UniChar (char c);
	UniChar (unsigned char c);

	UniChar&	operator= (Layout u);
	UniChar&	operator= (char16_t u);
	UniChar&	operator= (char c);
	UniChar&	operator= (unsigned char c);

		// Conversion

	operator Layout () const;
	operator char16_t () const;
	operator char () const;
	operator unsigned char () const;

	enum OnConversionError { ReplaceWithFillers, IndicateError };

	static USize		GetUnicodeLength (const char* str, USize length, GSCharCode charCode = CC_Default);
	static bool			ANSIToUnicode	 (const char* source, USize sourceLength, Layout* result, USize resultLength, GSCharCode charCode = CC_Default);
	static bool			ANSIToUnicode	 (std::string_view source, Layout* result, USize resultLength, GSCharCode charCode = CC_Default);

	static USize		GetANSILength	 (const Layout* str, USize length, GSCharCode charCode = CC_Default, OnConversionError onConversionError = ReplaceWithFillers);
	static bool			UnicodeToANSI	 (const Layout* source, USize sourceLength, char* result, USize resultLength, GSCharCode charCode = CC_Default, OnConversionError onConversionError = ReplaceWithFillers);

	static void			ConvertToDecomposed				 (const Layout* source, USize sourceLength, Layout** result, USize* resultLength);
	static void			ConvertToComposed				 (const Layout* source, USize sourceLength, Layout** result, USize* resultLength);
	static void			ConvertToCompatibilityDecomposed (const Layout* source, USize sourceLength, Layout** result, USize* resultLength);
	static void			ConvertToCompatibilityComposed	 (const Layout* source, USize sourceLength, Layout** result, USize* resultLength);

	static bool			IsUnicodeCompatible (char c);
	static bool			IsANSICompatible	(Layout u);

		// Hash value generation

	ULong				GenerateHashValue () const;

		// Comparing

	GSROOT_DLL_EXPORT friend bool	operator== (const UniChar& leftOp, const UniChar& rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniChar& leftOp, Layout rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (Layout leftOp, const UniChar& rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniChar& leftOp, char16_t rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (char16_t leftOp, const UniChar& rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniChar& leftOp, char rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (char leftOp, const UniChar& rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniChar& leftOp, unsigned char rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (unsigned char leftOp, const UniChar& rightOp);

	GSROOT_DLL_EXPORT friend bool	operator!= (const UniChar& leftOp, const UniChar& rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniChar& leftOp, Layout rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (Layout leftOp, const UniChar& rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniChar& leftOp, char16_t rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (char16_t leftOp, const UniChar& rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniChar& leftOp, char rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (char leftOp, const UniChar& rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniChar& leftOp, unsigned char rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (unsigned char leftOp, const UniChar& rightOp);

	enum CompareResult { Less, Equal, Greater };
	static CompareResult	Compare (const Layout* leftOp, USize leftOpLength, const Layout* rightOp, USize rightOpLength, CaseComparison caseComparison = CaseSensitive);

	   // Classification

	bool	IsASCII				(void) const;
	bool	IsDigit				(void) const;
	bool	IsASCIIDigit		(void) const;
	bool	IsASCIIHexaDigit	(void) const;
	bool	IsAlpha				(void) const;
	bool	IsAlphaNumeric		(void) const;
	bool	IsWhiteSpace		(void) const;
	bool	IsPunctuation		(void) const;
	bool	IsControl			(void) const;
	bool	IsLower				(void) const;
	bool	IsASCIILower		(void) const;
	bool	IsUpper				(void) const;
	bool	IsASCIIUpper		(void) const;


		// Conversion

	int		GetASCIIDigitValue (void) const;
	int		GetASCIIHexaDigitValue (void) const;

		// Manipulation

	enum Case { Lower, Upper };
	static USize	ComputeCaseConvertedLength (const Layout* str, USize length, Case cs);
	static bool		ConvertCase (const Layout* source, USize sourceLength, Layout* result, USize resultLength, Case cs);
};

}	// namespace GS


constexpr GS::UniChar::UniChar (Layout u):
	uniChar (u)
{
}


constexpr GS::UniChar::UniChar (char16_t u):
	uniChar (static_cast<Layout> (u))
{
}


inline GS::UniChar&		GS::UniChar::operator= (Layout u)
{
	uniChar = u;

	return *this;
}


inline GS::UniChar&		GS::UniChar::operator= (char16_t u)
{
	uniChar = static_cast<Layout> (u);

	return *this;
}


inline GS::UniChar::operator GS::UniChar::Layout () const
{
	return uniChar;
}


inline GS::UniChar::operator char16_t () const
{
	return static_cast<char16_t> (uniChar);
}


inline bool	GS::UniChar::IsUnicodeCompatible (char c)
{
#if defined (WINDOWS)
	return (c >= 0);
#endif

#if defined macintosh
	return (c >= 0 && c != '\\');		// in japanese code page won character is used in place of backslash character which is mapped to different Unicode character value
#endif

#if defined (__linux__)
	return (c >= 0);
#endif
}


inline bool	GS::UniChar::IsANSICompatible (Layout u)
{
#if defined (WINDOWS)
	return (u <= 127);
#endif

#if defined macintosh
	return (u <= 127 && u != '\\');		// backslash character is mapped to different ANSI character value on japanese code page
#endif

#if defined (__linux__)
	return (u <= 127);
#endif
}


inline ULong	GS::UniChar::GenerateHashValue () const
{
	return GS::CalculateHashValue (uniChar);
}


inline bool		GS::operator== (const UniChar& leftOp, const UniChar& rightOp)
{
	return (leftOp.uniChar == rightOp.uniChar);
}


inline bool		GS::operator== (const UniChar& leftOp, UniChar::Layout rightOp)
{
	return (leftOp.uniChar == rightOp);
}


inline bool		GS::operator== (UniChar::Layout leftOp, const UniChar& rightOp)
{
	return (leftOp == rightOp.uniChar);
}


inline bool		GS::operator== (const UniChar& leftOp, char16_t rightOp)
{
	return (leftOp.uniChar == static_cast<UniChar::Layout> (rightOp));
}


inline bool		GS::operator== (char16_t leftOp, const UniChar& rightOp)
{
	return (static_cast<UniChar::Layout> (leftOp) == rightOp.uniChar);
}


inline bool		GS::operator!= (const UniChar& leftOp, const UniChar& rightOp)
{
	return (leftOp.uniChar != rightOp.uniChar);
}


inline bool		GS::operator!= (const UniChar& leftOp, UniChar::Layout rightOp)
{
	return (leftOp.uniChar != rightOp);
}


inline bool		GS::operator!= (UniChar::Layout leftOp, const UniChar& rightOp)
{
	return (leftOp != rightOp.uniChar);
}


inline bool		GS::operator!= (const UniChar& leftOp, char16_t rightOp)
{
	return (leftOp.uniChar != static_cast<UniChar::Layout> (rightOp));
}


inline bool		GS::operator!= (char16_t leftOp, const UniChar& rightOp)
{
	return (static_cast<UniChar::Layout> (leftOp) != rightOp.uniChar);
}


// _______________________________ Class UniChar _______________________________


using namespace std::string_view_literals;


#endif
