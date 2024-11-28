// *********************************************************************************************************************
// Description:		GRAPHISOFT String Utilities
//
// Namespace:		-
// Contact person:	MM,BB,PM
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (UNICODE_HPP)
#define	UNICODE_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GRoot
#include	"Definitions.hpp"
#include	"CH.hpp"
#include	"GSRootExport.hpp"

namespace GS {

namespace Unicode {

	GSROOT_DLL_EXPORT extern bool	strictUTF8CharacterValidityHandling;
	

	class GSROOT_DLL_EXPORT ConversionError {
	public:
		enum {
			UnnamedError		=  0,	//Regen a 0 hiba volt, most csak akkor 0, ha 0 nChars-t adsz meg parameterul.
			TargetExhausted		= -1,	//Target buffer not big enough.
			SourceIllegal		= -2,
			SourceExhausted		= -3
		};

		static bool	HasError		(const Int32 result);
		static bool	IsSuccessful	(const Int32 result);
	};


	GSROOT_DLL_EXPORT Int32	UTF16ToUTF8 (const Utf16Char* pWChars, Int32 nWChars, Utf8Char* pChars, Int32 maxChars, bool strictConversion = true);
	GSROOT_DLL_EXPORT Int32	UTF8ToUTF16 (const Utf8Char* pChars, Int32 nChars, Utf16Char* pWChars, Int32 maxWChars, bool strictConversion = true);
	GSROOT_DLL_EXPORT bool	IsLegalUTF8String (const Utf8Char * pChars, Int32 nChars);

	GSROOT_DLL_EXPORT Int32	OS_UTF16ToUTF8 (const Utf16Char* pWChars, Int32 nWChars, Utf8Char* pChars, Int32 maxChars);
	GSROOT_DLL_EXPORT Int32	OS_UTF8ToUTF16 (const Utf8Char* pChars, Int32 nChars, Utf16Char* pWChars, Int32 maxWChars);

	GSROOT_DLL_EXPORT bool	IsLegalUTF8Character	(const Utf8Char *source, int length);

	class GSROOT_DLL_EXPORT ConvertUTF8ToUTF16 {
	private:
		static const USize	StaticBufferSize	= 260;

		GS::Utf16Char		staticStringBuffer[StaticBufferSize];
		Int32				bufferSize;

		GS::Utf16Char*		stringBufferPtr;
		Int32				stringLength;			//conversion returns with this value

	public:
		explicit ConvertUTF8ToUTF16 (const GS::Utf8Char* string, const Int32 nChars = GS::CStringLen);
		~ConvertUTF8ToUTF16 ();

		operator const GS::Utf16Char* () const;
		Int32 GetLength () const { return stringLength; }

	private:
		inline bool	IsUseDynamicBuffer () const { return (stringBufferPtr != staticStringBuffer && stringBufferPtr != nullptr); }
	};


	//////////////////////////////////////////////////////////////////////////
	namespace UTF16 {
		//has no public function yet
	} //namespace UTF16


	//////////////////////////////////////////////////////////////////////////
	namespace UTF8 {

		typedef unsigned char Utf8UnsignedChar;

		const size_t BOMLength = 3;

		class TrailingBytesForUTF8 {
			/*
			 * Index into the table below with the first byte of a UTF-8 sequence to
			 * get the number of trailing bytes that are supposed to follow it.
			 */
			static const char trailingBytesForUTF8[256];

		public:
			static inline char Get (const Utf8Char character) {
				Utf8UnsignedChar unsignedCharacter = static_cast<const Utf8UnsignedChar>(character);
				if (unsignedCharacter < 192)
					return 0;
				else if (unsignedCharacter < 224)
					return 1;
				else if (unsignedCharacter < 240)
					return 2;
				else if (unsignedCharacter < 248)
					return 3;
				else if (unsignedCharacter < 252)
					return 4;
				else
					return 5;
//					return trailingBytesForUTF8[ static_cast<const Utf8UnsignedChar>(character) ]; 
			}
			static inline char Get (const Utf8UnsignedChar character) { 
				if (character < 192)
					return 0;
				else if (character < 224)
					return 1;
				else if (character < 240)
					return 2;
				else if (character < 248)
					return 3;
				else if (character < 252)
					return 4;
				else
					return 5;
//					return trailingBytesForUTF8[ character ]; 
			}
		};
		
		GSROOT_DLL_EXPORT bool				IsAlpha				(const Utf8Char* aChar);
		GSROOT_DLL_EXPORT bool				IsDigit				(const Utf8Char* aChar);
		GSROOT_DLL_EXPORT bool				IsHexaDigit			(const Utf8Char* aChar);
		GSROOT_DLL_EXPORT bool				IsAlnum				(const Utf8Char* aChar);

		GSROOT_DLL_EXPORT bool				HasBOM				(const Utf8Char* pCString);

		GSROOT_DLL_EXPORT void				ToLower				(Utf8Char* pChars, Int32 nChars = CStringLen);
		GSROOT_DLL_EXPORT void 				ToUpper				(Utf8Char* pChars, Int32 nChars = CStringLen);

		GSROOT_DLL_EXPORT const Utf8Char* 	GetNextCharPtr		(const Utf8Char* pCString);
		GSROOT_DLL_EXPORT Utf8Char* 		GetNextCharPtr		(Utf8Char* pCString);
		GSROOT_DLL_EXPORT const Utf8Char* 	GetLastCharPtr		(const Utf8Char* pCString);
		GSROOT_DLL_EXPORT Utf8Char* 		GetLastCharPtr		(Utf8Char* pCString);

		GSROOT_DLL_EXPORT const Utf8Char*	SearchCharLeftPtr	(const Utf8Char* searchFor, const Utf8Char* pCString, Int32 nChars = CStringLen);
		GSROOT_DLL_EXPORT Utf8Char* 		SearchCharLeftPtr	(Utf8Char* searchFor, Utf8Char* pCString, Int32 nChars = CStringLen);
		GSROOT_DLL_EXPORT const Utf8Char*	SearchCharRightPtr	(const Utf8Char* searchFor, const Utf8Char* pCString, Int32 nChars = CStringLen);
		GSROOT_DLL_EXPORT Utf8Char* 		SearchCharRightPtr	(Utf8Char* searchFor, Utf8Char* pCString, Int32 nChars = CStringLen);
		GSROOT_DLL_EXPORT const Utf8Char* 	SearchSubstring		(const Utf8Char* pCSubString, const Utf8Char* pCString, CaseComparison cs = CaseSensitive);
		GSROOT_DLL_EXPORT Utf8Char* 		SearchSubstring		(const Utf8Char* pCSubString, Utf8Char* pCString, CaseComparison cs = CaseSensitive);

		GSROOT_DLL_EXPORT Int32				Truncate			(	const Utf8Char*	sourceCString,			// Zero terminated source string
																	Utf8Char*		targetCString,			// pointer to the target, can be equal with sourceCString
																	Int32			targetSize				// the size of target buffer
																	);										// RETURNS:	the size of the resulted string (without the 0 byte)(not the character count, the Utf8Char count)

		GSROOT_DLL_EXPORT Int32				CompareCStrings		(const Utf8Char* p1, const Utf8Char* p2, const CaseComparison cs = CaseSensitive);
		GSROOT_DLL_EXPORT Int32				CompareStrings		(const Utf8Char* p1, const Int32 n1, const Utf8Char* p2, const Int32 n2, const CaseComparison cs = CaseSensitive);
		GSROOT_DLL_EXPORT bool				IsEqualCStrings		(const Utf8Char* p1, const Utf8Char* p2, const CaseComparison cs = CaseSensitive);
		
		GSROOT_DLL_EXPORT Int32				Copy				(const Utf8Char* source, Utf8Char* target, Int32 targetSize = CStringLen);
		
	} //namespace UTF8

} //namespace Unicode

} //namespace GS

#endif
