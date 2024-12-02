// *****************************************************************************
//
//                                Class UniString
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
//
//
// *****************************************************************************


#if !defined UNISTRING_HPP
#define UNISTRING_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Object.hpp"
#include "UniCHar.hpp"
#include "uchar_t.hpp"
#include "TSRefCounter.hpp"
#include "GSException.hpp"
#include "FastLogger.hpp"
#include "NullableSelector.hpp"

// from Standard Library
#include <cstdarg>
#include <cstddef>
#include <iosfwd>
#include <string_view>

// ============================== Class UniString ==============================

// UniString is reference counted. This raises some problems in multi-threaded environment.
// To avoid them the following rule is obeyed throughout the implementation:
//     No string will operate on a buffer that is shared (it should be detached first).
// Moreover as UniString's external interface is not thread-safe, user should serialize
// concurrent accesses to the same string objects.
// Consequently:
//     - A shared buffer can be read (const operations)
//     - A shared buffer can not be deleted
//     - In the copy constructor the source buffer will not be deleted because at least the
//       source string will hold it.
//     - Inside any operation if the buffer's reference counter is 1 then the buffer will
//       remain unshared until the operation itself modifies it (because there are no more
//       references to the buffer and the same string can not participate in another operation)
// In the implementation:
//     - It is sufficient to serialize accesses to the reference counter
//     - After the AboutToModify method is called the buffer is surely unshared

namespace GS {

class String;

inline const uchar_t*	GetScanfFormatUStrOf (const void* par)		{ static uchar_t formats [] = {'%','T', 0 , 0 }; return par == nullptr ? L ("") : formats; }
inline const uchar_t*	GetPrintfFormatUStrOf(const GS::UniString&) { static uchar_t formats[] = { '%','T', 0 , 0 }; return formats; }

class GSROOT_DLL_EXPORT UniString: public Object {
	DECLARE_CLASS_INFO

public:
	class Substring;
	class ConstSubstring;
	class Concatenation;

private:
	struct SharedBuffer;

	SharedBuffer*	content;	// shared buffer storing content of the string

		// Implementation classes and structures

	struct SharedBuffer {
		USize			length;			// length of the string in UniChar::Layout units
		USize			capacity;		// capacity of the allocated buffer in UniChar::Layout units
		TSRefCounter	refCounter;		// stores number of references to this shared buffer
		char			reserved[2];	// padding reserved for the future use
		UniChar::Layout	string[1];		// buffer storing content of the string (extends beyond of the SharedBuffer)

		inline SharedBuffer ();
		inline SharedBuffer (USize initialLength, USize initialCapacity, Int32 initialRefCounter);
	};

	static SharedBuffer&	EmptyBuffer ();	// represents the empty string

	class GSROOT_DLL_EXPORT UniCharRef {
	private:
		UniString*	target;	// target of the reference
		UIndex		idx;	// index of the referred character

	public:
		UniCharRef (UniString* targetString, UIndex targetCharIdx): target (targetString), idx (targetCharIdx) {}

			// UniChar interface delegation

		UniCharRef&		operator= (const UniCharRef& ucr) { target->SetChar (idx, ucr); return *this; }
		UniCharRef&		operator= (const UniChar& uc)	  { target->SetChar (idx, uc); return *this;  }
		UniCharRef&		operator= (UniChar::Layout uc)	  { target->SetChar (idx, uc); return *this;  }
		UniCharRef&		operator= (char c)				  { target->SetChar (idx, c); return *this;   }
		UniCharRef&		operator= (unsigned char c)		  { target->SetChar (idx, c); return *this;   }

		operator UniChar () const		 { return target->GetChar (idx); }
		operator UniChar::Layout () const { return target->GetChar (idx); }
		operator char () const			 { return target->GetChar (idx); }
		operator unsigned char () const	 { return target->GetChar (idx); }

		friend bool	operator== (const UniCharRef& leftOp, const UniCharRef& rightOp) { return (leftOp.target->GetChar (leftOp.idx) == rightOp.target->GetChar (rightOp.idx)); }
		friend bool	operator== (const UniCharRef& leftOp, const UniChar& rightOp)    { return (leftOp.target->GetChar (leftOp.idx) == rightOp);  }
		friend bool	operator== (const UniChar& leftOp, const UniCharRef& rightOp)    { return (leftOp == rightOp.target->GetChar (rightOp.idx)); }
		friend bool	operator== (const UniCharRef& leftOp, UniChar::Layout rightOp)   { return (leftOp.target->GetChar (leftOp.idx) == rightOp);  }
		friend bool	operator== (UniChar::Layout leftOp, const UniCharRef& rightOp)   { return (leftOp == rightOp.target->GetChar (rightOp.idx)); }
		friend bool	operator== (const UniCharRef& leftOp, char rightOp) 			 { return (leftOp.target->GetChar (leftOp.idx) == rightOp);  }
		friend bool	operator== (char leftOp, const UniCharRef& rightOp) 			 { return (leftOp == rightOp.target->GetChar (rightOp.idx)); }
		friend bool	operator== (const UniCharRef& leftOp, unsigned char rightOp) 	 { return (leftOp.target->GetChar (leftOp.idx) == rightOp);  }
		friend bool	operator== (unsigned char leftOp, const UniCharRef& rightOp) 	 { return (leftOp == rightOp.target->GetChar (rightOp.idx)); }

		friend bool	operator!= (const UniCharRef& leftOp, const UniCharRef& rightOp) { return (leftOp.target->GetChar (leftOp.idx) != rightOp.target->GetChar (rightOp.idx)); }
		friend bool	operator!= (const UniCharRef& leftOp, const UniChar& rightOp)    { return (leftOp.target->GetChar (leftOp.idx) != rightOp);  }
		friend bool	operator!= (const UniChar& leftOp, const UniCharRef& rightOp)    { return (leftOp != rightOp.target->GetChar (rightOp.idx)); }
		friend bool	operator!= (const UniCharRef& leftOp, UniChar::Layout rightOp)   { return (leftOp.target->GetChar (leftOp.idx) != rightOp);  }
		friend bool	operator!= (UniChar::Layout leftOp, const UniCharRef& rightOp)   { return (leftOp != rightOp.target->GetChar (rightOp.idx)); }
		friend bool	operator!= (const UniCharRef& leftOp, char rightOp) 			 { return (leftOp.target->GetChar (leftOp.idx) != rightOp);  }
		friend bool	operator!= (char leftOp, const UniCharRef& rightOp) 			 { return (leftOp != rightOp.target->GetChar (rightOp.idx)); }
		friend bool	operator!= (const UniCharRef& leftOp, unsigned char rightOp) 	 { return (leftOp.target->GetChar (leftOp.idx) != rightOp);  }
		friend bool	operator!= (unsigned char leftOp, const UniCharRef& rightOp) 	 { return (leftOp != rightOp.target->GetChar (rightOp.idx)); }

		bool		IsDigit				(void) const { return target->GetChar (idx).IsDigit ();				}
		bool		IsASCIIHexaDigit	(void) const { return target->GetChar (idx).IsASCIIHexaDigit ();	}
		bool		IsAlpha				(void) const { return target->GetChar (idx).IsAlpha ();				}
		bool		IsAlphaNumeric		(void) const { return target->GetChar (idx).IsAlphaNumeric ();		}
		bool		IsWhiteSpace		(void) const { return target->GetChar (idx).IsWhiteSpace ();		}
		bool		IsPunctuation		(void) const { return target->GetChar (idx).IsPunctuation ();		}
		bool		IsControl			(void) const { return target->GetChar (idx).IsControl ();			}
		bool		IsLower				(void) const { return target->GetChar (idx).IsLower ();				}
		bool		IsASCIILower		(void) const { return target->GetChar (idx).IsASCIILower ();		}
		bool		IsUpper				(void) const { return target->GetChar (idx).IsUpper ();				}
		bool		IsASCIIUpper		(void) const { return target->GetChar (idx).IsASCIIUpper ();		}
	};

	class GSROOT_DLL_EXPORT CStr {
	private:
		enum { BufferSize = 256 };

		char*	content;			// stores content of the C string
		USize	length;				// length of the C string
		char	buffer[BufferSize];	// buffer for smaller C strings

		CStr&	operator= (const CStr& source) = delete;	// disabled
		CStr (const CStr& source) = delete;					// disabled

		friend class UniString;

	public:
		explicit CStr (USize strLength);

		CStr (CStr&& source);
	   ~CStr ();

		operator			const char*  (void) const gs_lifebound { return content; }
		const char*			Get          (void) const gs_lifebound { return content; }
		USize				GetLength    (void) const			   { return length; }
		std::string_view	ToStringView (void) const gs_lifebound { return { content, length }; }
	};

	class GSROOT_DLL_EXPORT UStr {
	private:
		UniChar::Layout*	content;		// stores content of the plain Unicode string
		bool				ownsContent;	// indicates whether the UStr owns its content

		UStr&	operator= (const UStr& source) = delete;	// disabled
		UStr (const UStr& source) = delete; 				// disabled

	public:
		explicit UStr (UniChar::Layout* content, bool ownsContent);

		UStr (UStr&& source);
	   ~UStr ();

		operator const UniChar::Layout* () const gs_lifebound { return content; }
		const UniChar::Layout*  Get (void) const gs_lifebound { return content; }
	};

	static bool	UniStringHandleTextForPrintf (void* pointer, uchar_t *&s, int& s_len);
	static bool	UniStringHandleTextForScanf  (void* pointer, int status, const uchar_t *s, int s_len);

	static UniString	PrintfImpl (const uchar_t* format, std::va_list arg);
	
	static UniString	PrintfFwd (const char* format, ...);
	static UniString	PrintfFwd (const uchar_t* format, ...);

	int		CheckedScanf (const UniChar::Layout* format, const UniChar::Layout** formatStrs, ...) const;
	int		CheckedScanf (const UniString& format, const UniChar::Layout** formatStrs, ...) const;
	int		CheckedScanf (const char* format, const UniChar::Layout** formatStrs, ...) const;
	static UniString	CheckedPrintf (const UniChar::Layout* format, const UniChar::Layout** formatStrs, ...);
	static UniString	CheckedPrintf (const UniString& format, const UniChar::Layout** formatStrs, ...);
	static UniString	CheckedPrintf (const char* format, const UniChar::Layout** formatStrs, ...);

	void	Init (const char* chars, USize logicalLength, USize physicalLength, GSCharCode charCode);

	void	Set (const char* chars, USize logicalLength, USize physicalLength, GSCharCode charCode);
	void	Set (const UniString& source);

	static UIndex	FindFirstIn	   (const UniChar::Layout* source, USize sourceLength, const UniChar::Layout* charSet, USize charCount);
	static UIndex	FindLastIn	   (const UniChar::Layout* source, USize sourceLength, const UniChar::Layout* charSet, USize charCount);
	static UIndex	FindFirstNotIn (const UniChar::Layout* source, USize sourceLength, const UniChar::Layout* charSet, USize charCount);
	static UIndex	FindLastNotIn  (const UniChar::Layout* source, USize sourceLength, const UniChar::Layout* charSet, USize charCount);

	static USize		CountLogicalLength  (std::string_view, GSCharCode charCode);
	static USize		CountPhysicalLength (const char* cStr);
	static void			CountLengths        (const char* cStr, USize* logicalLength, USize* physicalLength, GSCharCode charCode);
	static USize		CountLength         (const UniChar::Layout* uStr);

	static Concatenation	Concatenate (void) { return Concatenation (); }

	static bool		IsEqual (const UniString& leftOp,      const UniString&       rightOp);
	static bool		IsEqual (const UniString& leftOp,      const char*            rightOp);
	static bool		IsEqual (const UniString& leftOp,      const UniChar::Layout* rightOp);
	static bool		IsEqual (const UniString& leftOp,      const Substring&       rightOp);
	static bool		IsEqual (const UniString& leftOp,      const ConstSubstring&  rightOp);
	static bool		IsEqual (const UniString& leftOp,      std::u16string_view    rightOp);
	static bool		IsEqual (const UniString& leftOp,      std::string_view       rightOp);
	static bool		IsEqual (const Substring& leftOp,      const char*            rightOp);
	static bool		IsEqual (const Substring& leftOp,      const UniChar::Layout* rightOp);
	static bool		IsEqual (const Substring& leftOp,      const Substring&       rightOp);
	static bool		IsEqual (const Substring& leftOp,      const ConstSubstring&  rightOp);
	static bool		IsEqual (const Substring& leftOp,      std::u16string_view    rightOp);
	static bool		IsEqual (const Substring& leftOp,      std::string_view       rightOp);
	static bool		IsEqual (const ConstSubstring& leftOp, const char*            rightOp);
	static bool		IsEqual (const ConstSubstring& leftOp, const UniChar::Layout* rightOp);
	static bool		IsEqual (const ConstSubstring& leftOp, const ConstSubstring&  rightOp);
	static bool		IsEqual (const ConstSubstring& leftOp, std::u16string_view    rightOp);
	static bool		IsEqual (const ConstSubstring& leftOp, std::string_view       rightOp);

		// Modification signaling

	inline void		AboutToModify (void);
	inline void		AboutToModify (USize minCapacity);
	inline void		AboutToInsert (USize charCount);
	inline void		AboutToDelete (void);

		// Capacity management (can be called only when the buffer is not shared)

	void			IncreaseCapacity (USize minCapacity);
	void			DecreaseCapacity (USize minCapacity);
	void			AdjustCapacity   (USize minCapacity);
	void			Reallocate	     (USize newCapacity);

		// SharedBuffer management

	void			SetBuffer     (SharedBuffer* newContent);
	void			DetachBuffer  (void);
	void			DetachBuffer  (USize newCapacity);
	void			ReleaseBuffer (void);

	static SharedBuffer*	AllocateBuffer		(USize capacity);
	static SharedBuffer*	ShareEmptyBuffer	(void);
	static SharedBuffer*	CopyBuffer			(const SharedBuffer* source);
	static SharedBuffer*	CopyBuffer			(const SharedBuffer* source, USize newCapacity);
	static void				DeleteBuffer		(SharedBuffer* buffer);

	static USize			CapacityToBufferSize (USize capacity);
	static USize			BufferSizeToCapacity (USize bufferSize);

		// Utility

	static void				CopyUnicode    (UniChar::Layout* target, const char16_t*        source, USize length);
	static void				CopyUnicode    (UniChar::Layout* target, const UniChar::Layout* source, USize length);
	static void				MoveUnicode    (UniChar::Layout* target, const UniChar::Layout* source, USize length);

	static bool				CompareUnicode (const UniChar::Layout* source1, const UniChar::Layout* source2, USize length);
	static bool				CompareUnicode (const UniChar::Layout* source1, const char16_t* source2, USize length);

	template <class T>
	static T	ToVarArg (const T t)
	{
		return t;
	}

	static const void*	ToVarArg (const GS::UniString& t)
	{
		return t.ToPrintf ();
	}
public:
		// Implementation classes and structures

	class GSROOT_DLL_EXPORT Substring {
	private:
		UniString*	base;	// base string of the substring
		UIndex		from;	// offset of the substring in the base string
		USize		range;	// length of the substring

		Substring (UniString& base, UIndex from, USize range);

		friend class UniString;

	public:
		Substring&	operator= (const Substring& source);
		Substring&	operator= (const ConstSubstring& source);
		Substring&	operator= (UniChar uc);
		Substring&	operator= (const UniString& str);
		Substring&	operator= (const UniChar::Layout* uStr);
		Substring&	operator= (const char* cStr);
	};

	class GSROOT_DLL_EXPORT ConstSubstring {
	private:
		const UniString*	base;	// base string of the constant substring
		UIndex				from;	// offset of the constant substring in the base string
		USize				range;	// length of the constant substring

		ConstSubstring (const UniString& base, UIndex from, USize range);

		friend class UniString;
		friend class Substring;
	};

	class GSROOT_DLL_EXPORT Concatenation {
	private:
		enum OperandType { TUniChar, TUniString, TUStr, TCStr, TSubstring, TConstSubstring, TView16, TView };	// possible operand types of the concatenation

		struct Operand {	// stores an operand of the concatenation
			OperandType		type;
			union {
				UniChar::Layout			uc;
				const UniString*		str;
				const UniChar::Layout*	uStr;
				const char*				cStr;
				const Substring*		substr;
				const ConstSubstring*	constSubstr;
				std::u16string_view		sv16;
				std::string_view		sv = {};
			};

			Operand () {}
		};

		enum { MaxOperands = 10 };

		UniString*	subResult;				// subresult of long (with more than MaxOperands operands) concatenations
		Operand		operands[MaxOperands];	// operands of the concatenation
		USize		operandCount;			// number of operands

		Concatenation ();

		friend class UniString;

	public:
		Concatenation (const Concatenation& source);
		Concatenation&	operator= (const Concatenation& source);
	   ~Concatenation ();

		Concatenation&	operator+ (UniChar                rightOp);
		Concatenation&	operator+ (const UniString&       rightOp);
		Concatenation&	operator+ (const UniChar::Layout* rightOp);
		Concatenation&	operator+ (const char*            rightOp);
		Concatenation&	operator+ (const Substring&       rightOp);
		Concatenation&	operator+ (const ConstSubstring&  rightOp);
		Concatenation&	operator+ (std::u16string_view    rightOp);
		Concatenation&	operator+ (std::string_view       rightOp);
	};

		// Constructors

	UniString ();

	UniString (const UniChar::Layout* uStr);
	UniString (const UniChar::Layout* uStr, NullableSelector);
	UniString (const UniChar::Layout* uChars, USize charCount);

	UniString (const char* cStr, NullableSelector, GSCharCode charCode = CC_Default);
	UniString (const char* cStr, GSCharCode charCode = CC_Default);
	UniString (const char* chars, USize charCount, GSCharCode charCode = CC_Default);

	UniString (std::u16string_view str);
	UniString (std::string_view str, GSCharCode = CC_Default);

	UniString (const UniString& source, UIndex sourceFrom = 0, USize sourceRange = MaxUSize);
	UniString (UniString&& source);

	UniString (const Substring& source);
	UniString (const ConstSubstring& source);
	UniString (const Concatenation& source);

	UniString (const String& string);

	template<typename... Args>
	static UniString	Printf (const char* formatString, Args... args);
	template<typename... Args>
	static UniString	Printf (const UniChar::Layout* formatString, Args... args);
	template<typename... Args>
	static UniString	Printf (const UniString& formatString, Args... args);

	UniString&	operator= (const UniChar::Layout* uStr);
	UniString&	operator= (const char* cStr);
	UniString&	operator= (std::u16string_view str);
	UniString&	operator= (std::string_view str);
	UniString&	operator= (const UniString& source);
	UniString&	operator= (UniString&& source);
	UniString&	operator= (const Substring& source);
	UniString&	operator= (const ConstSubstring& source);
	UniString&	operator= (const Concatenation& source);
	UniString&	operator= (const String& source);

	UniString&	Assign (const UniChar::Layout* uChars, USize charCount);
	UniString&	Assign (const char* cStr, GSCharCode charCode = CC_Default);
	UniString&	Assign (const char* chars, USize charCount, GSCharCode charCode = CC_Default);
	UniString&	Assign (std::u16string_view str);
	UniString&	Assign (std::string_view str, GSCharCode charCode = CC_Default);
	UniString&	Assign (const UniString& source, UIndex sourceFrom = 0, USize sourceRange = MaxUSize);

	void		Swap (UniString& source);

	virtual ~UniString () override;

	virtual UniString*		Clone (void) const override;

		// Character access

	UniCharRef	operator[] (UIndex idx) gs_lifebound;
	UniChar		operator[] (UIndex idx) const;

	UniChar		GetChar (UIndex idx) const;
	void		SetChar (UIndex idx, UniChar uc);

	UniChar		GetLast (void) const;

		// Substring access

	Substring		operator() (UIndex from, USize range) gs_lifebound;
	ConstSubstring	operator() (UIndex from, USize range) const gs_lifebound;
	Substring		operator() (UniChar leftSeparator, UniChar rightSeparator, UIndex from = 0, USize range = MaxUIndex) gs_lifebound;
	ConstSubstring	operator() (UniChar leftSeparator, UniChar rightSeparator, UIndex from = 0, USize range = MaxUIndex) const gs_lifebound;

	Substring		GetSubstring (UIndex from, USize range) gs_lifebound;
	ConstSubstring	GetSubstring (UIndex from, USize range) const gs_lifebound;
	Substring		GetSubstring (UniChar leftSeparator, UniChar rightSeparator, UIndex from = 0, USize range = MaxUIndex) gs_lifebound;
	ConstSubstring	GetSubstring (UniChar leftSeparator, UniChar rightSeparator, UIndex from = 0, USize range = MaxUIndex) const gs_lifebound;

	Substring		GetPrefix (USize range) gs_lifebound;
	ConstSubstring	GetPrefix (USize range) const gs_lifebound;

	Substring		GetSuffix (USize range) gs_lifebound;
	ConstSubstring	GetSuffix (USize range) const gs_lifebound;

	enum EmptyPartProcessing {
		KeepEmptyParts,
		SkipEmptyParts
	};

	template <USize BufferCapacity = 8>
	ArrayFB<UniString, BufferCapacity>	Split (const UniString& separatorString) const;
	UInt32								Split (const UniString& separatorString, const std::function<void (const UniString&)>& processor) const;

	template <USize BufferCapacity = 8>
	ArrayFB<UniString, BufferCapacity>	Split (const UniString& separatorCharSet, EmptyPartProcessing emptyPartProcessing) const;
	UInt32								Split (const UniString& separatorCharSet, EmptyPartProcessing emptyPartProcessing, const std::function<void (const UniString&)>& processor) const;

	UInt32								Split (const UniString& separatorString, Array<UniString>* parts) const;
	UInt32								Split (const UniString& separatorCharSet, EmptyPartProcessing emptyPartProcessing, Array<UniString>* parts) const;

	void	SetSubstring (UIndex from, USize range, UniChar uc);
	void	SetSubstring (UIndex from, USize range, const UniString& str, UIndex strFrom = 0, USize strRange = MaxUSize);
	void	SetSubstring (UIndex from, USize range, const UniChar::Layout* uStr);
	void	SetSubstring (UIndex from, USize range, const UniChar::Layout* uChars, USize charCount);
	void	SetSubstring (UIndex from, USize range, const char* cStr, GSCharCode charCode = CC_Default);
	void	SetSubstring (UIndex from, USize range, const char* chars, USize charCount, GSCharCode charCode = CC_Default);

		// Inserting, appending and filling

	void	Insert (UIndex to, UniChar uc);
	void	Insert (UIndex to, const UniString& str, UIndex strFrom = 0, USize strRange = MaxUSize);

	void	Append (UniChar uc);
	void	Append (const UniString& str, UIndex strFrom = 0, USize strRange = MaxUSize);
	void	Append (const UniChar::Layout* uStr);
	void	Append (const UniChar::Layout* uChars, USize charCount);
	void	Append (const char* cStr, GSCharCode charCode = CC_Default);
	void	Append (const char* chars, USize charCount, GSCharCode charCode = CC_Default);
	void	Append (std::u16string_view str);
	void	Append (std::string_view str, GSCharCode charCode = CC_Default);

	UniString&	operator+= (UniChar uc);
	UniString&	operator+= (const UniString& str);
	UniString&	operator+= (const UniChar::Layout* uStr);
	UniString&	operator+= (const char* cStr);
	UniString&	operator+= (std::u16string_view str);
	UniString&	operator+= (std::string_view str);

	GSROOT_DLL_EXPORT friend Concatenation	operator+ (UniChar leftOp, UniChar                rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (UniChar leftOp, const UniString&       rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (UniChar leftOp, const UniChar::Layout* rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (UniChar leftOp, const char*            rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (UniChar leftOp, const Substring&       rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (UniChar leftOp, const ConstSubstring&  rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (UniChar leftOp, std::u16string_view    rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (UniChar leftOp, std::string_view       rightOp);

	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniString& leftOp, UniChar                rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniString& leftOp, const UniString&       rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniString& leftOp, const UniChar::Layout* rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniString& leftOp, const char*            rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniString& leftOp, const Substring&       rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniString& leftOp, const ConstSubstring&  rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniString& leftOp, std::u16string_view    rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniString& leftOp, std::string_view       rightOp);

	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniChar::Layout* leftOp, UniChar               rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniChar::Layout* leftOp, const UniString&      rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniChar::Layout* leftOp, const Substring&      rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniChar::Layout* leftOp, const ConstSubstring& rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniChar::Layout* leftOp, std::u16string_view   rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const UniChar::Layout* leftOp, std::string_view      rightOp);

	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const char* leftOp, UniChar               rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const char* leftOp, const UniString&      rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const char* leftOp, const Substring&      rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const char* leftOp, const ConstSubstring& rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const char* leftOp, std::u16string_view   rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const char* leftOp, std::string_view      rightOp);

	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const Substring& leftOp, UniChar                rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const Substring& leftOp, const UniString&       rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const Substring& leftOp, const UniChar::Layout* rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const Substring& leftOp, const char*            rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const Substring& leftOp, const Substring&       rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const Substring& leftOp, const ConstSubstring&  rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const Substring& leftOp, std::u16string_view    rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const Substring& leftOp, std::string_view       rightOp);

	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const ConstSubstring& leftOp, UniChar                rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const ConstSubstring& leftOp, const UniString&       rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const ConstSubstring& leftOp, const UniChar::Layout* rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const ConstSubstring& leftOp, const char*            rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const ConstSubstring& leftOp, const Substring&       rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const ConstSubstring& leftOp, const ConstSubstring&  rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const ConstSubstring& leftOp, std::u16string_view    rightOp);
	GSROOT_DLL_EXPORT friend Concatenation	operator+ (const ConstSubstring& leftOp, std::string_view       rightOp);

	void	Pad (USize toLength, UniChar filler);

	void	Fill (UniChar uc, UIndex from = 0, USize range = MaxUSize);

		// Deleting

	void	Delete		(UIndex idx);
	void	Delete		(UIndex from, USize range);
	void	DeleteFirst (void);
	UIndex	DeleteFirst (UniChar uc, UIndex from = 0, USize range = MaxUSize);
	UIndex	DeleteFirst	(const UniString& str, UIndex from = 0, USize range = MaxUSize);
	void	DeleteLast  (void);
	UIndex	DeleteLast	(UniChar uc);
	UIndex	DeleteLast	(const UniString& str);
	void	DeleteAll	(UniChar uc, UIndex from = 0, USize range = MaxUSize);
	void	DeleteAll	(const UniString& str, UIndex from = 0, USize range = MaxUSize);

	void	TrimLeft  (void);
	void	TrimLeft  (UniChar uc);
	void	TrimRight (void);
	void	TrimRight (UniChar uc);
	void	Trim      (void);
	void	Trim      (UniChar uc);

	void	Clear (void);
	void	ClearContent (void);

		// Length and capacity management

	void	SetLength (USize newLength);
	void	SetLength (USize newLength, UniChar filler);
	void	Truncate  (USize newLength);
	USize	GetLength (void) const;
	bool	IsEmpty	  (void) const;

	void	SetCapacity	(USize newCapacity);
	USize	GetCapacity	(void) const;

		// Comparing

	GSROOT_DLL_EXPORT friend bool	operator== (const UniString& leftOp, const UniString&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniString& leftOp, const char*            rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniString& leftOp, const UniChar::Layout* rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniString& leftOp, const Substring&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniString& leftOp, const ConstSubstring&  rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniString& leftOp, std::u16string_view    rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniString& leftOp, std::string_view       rightOp);

	GSROOT_DLL_EXPORT friend bool	operator== (const char* leftOp, const UniString&      rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const char* leftOp, const Substring&      rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const char* leftOp, const ConstSubstring& rightOp);

	GSROOT_DLL_EXPORT friend bool	operator== (const UniChar::Layout* leftOp, const UniString&      rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniChar::Layout* leftOp, const Substring&      rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const UniChar::Layout* leftOp, const ConstSubstring& rightOp);

	GSROOT_DLL_EXPORT friend bool	operator== (const Substring& leftOp, const UniString&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const Substring& leftOp, const char*            rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const Substring& leftOp, const UniChar::Layout* rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const Substring& leftOp, const Substring&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const Substring& leftOp, const ConstSubstring&  rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const Substring& leftOp, std::u16string_view    rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const Substring& leftOp, std::string_view       rightOp);

	GSROOT_DLL_EXPORT friend bool	operator== (const ConstSubstring& leftOp, const UniString&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const ConstSubstring& leftOp, const char*            rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const ConstSubstring& leftOp, const UniChar::Layout* rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const ConstSubstring& leftOp, const Substring&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const ConstSubstring& leftOp, const ConstSubstring&  rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const ConstSubstring& leftOp, std::u16string_view    rightOp);
	GSROOT_DLL_EXPORT friend bool	operator== (const ConstSubstring& leftOp, std::string_view       rightOp);

	GSROOT_DLL_EXPORT friend bool	operator!= (const UniString& leftOp, const UniString&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniString& leftOp, const char*            rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniString& leftOp, const UniChar::Layout* rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniString& leftOp, const Substring&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniString& leftOp, const ConstSubstring&  rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniString& leftOp, std::u16string_view    rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniString& leftOp, std::string_view       rightOp);

	GSROOT_DLL_EXPORT friend bool	operator!= (const char* leftOp, const UniString&      rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const char* leftOp, const Substring&      rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const char* leftOp, const ConstSubstring& rightOp);

	GSROOT_DLL_EXPORT friend bool	operator!= (const UniChar::Layout* leftOp, const UniString&      rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniChar::Layout* leftOp, const Substring&      rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const UniChar::Layout* leftOp, const ConstSubstring& rightOp);

	GSROOT_DLL_EXPORT friend bool	operator!= (const Substring& leftOp, const UniString&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const Substring& leftOp, const char*            rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const Substring& leftOp, const UniChar::Layout* rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const Substring& leftOp, const Substring&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const Substring& leftOp, const ConstSubstring&  rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const Substring& leftOp, std::u16string_view    rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const Substring& leftOp, std::string_view       rightOp);

	GSROOT_DLL_EXPORT friend bool	operator!= (const ConstSubstring& leftOp, const UniString&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const ConstSubstring& leftOp, const char*            rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const ConstSubstring& leftOp, const UniChar::Layout* rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const ConstSubstring& leftOp, const Substring&       rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const ConstSubstring& leftOp, const ConstSubstring&  rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const ConstSubstring& leftOp, std::u16string_view    rightOp);
	GSROOT_DLL_EXPORT friend bool	operator!= (const ConstSubstring& leftOp, std::string_view       rightOp);

	bool	operator<  (const UniString& rightOp) const;
	bool	operator<= (const UniString& rightOp) const;
	bool	operator>  (const UniString& rightOp) const;
	bool	operator>= (const UniString& rightOp) const;

	bool	IsEqual (const UniString& rightOp, CaseComparison caseComparison = CaseSensitive) const;

	enum CompareResult { Less, Equal, Greater };
	CompareResult	Compare (const UniString& rightOp, CaseComparison caseComparison = CaseSensitive) const;
	bool			IsLess  (const UniString& rightOp, CaseComparison caseComparison = CaseSensitive) const;
		// Find and replace

	bool	Contains (UniChar uc, UIndex from = 0, USize range = MaxUSize) const;
	bool	Contains (const UniString& str, UIndex from = 0, USize range = MaxUSize) const;

	UIndex	FindFirst (UniChar uc, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindFirst (const UniString& str, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindLast  (UniChar uc) const;
	UIndex	FindLast  (const UniString& str) const;
	void	Find	  (UniChar uc, const std::function<void (UIndex index)>& processor) const;
	void	Find	  (const UniString& str, const std::function<void (UIndex index)>& processor) const;

	UIndex	FindFirstIn	(const UniString& str, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindFirstIn	(const char* cStr, UIndex from = 0, USize range = MaxUSize, GSCharCode charCode = CC_Default) const;
	UIndex	FindLastIn	(const UniString& str) const;
	UIndex	FindLastIn	(const char* cStr, GSCharCode charCode = CC_Default) const;

	UIndex	FindFirstNotIn (const UniString& str, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindFirstNotIn (const char* cStr, UIndex from = 0, USize range = MaxUSize, GSCharCode charCode = CC_Default) const;
	UIndex	FindLastNotIn  (const UniString& str ) const;
	UIndex	FindLastNotIn  (const char* cStr, GSCharCode charCode = CC_Default) const;

	bool	BeginsWith (UniChar uc) const;
	bool	BeginsWith (const UniString& str) const;
	bool	EndsWith   (UniChar uc) const;
	bool	EndsWith   (const UniString& str) const;

	UIndex	ReplaceFirst (UniChar oldChar, UniChar newChar, UIndex from = 0, USize range = MaxUSize);
	UIndex	ReplaceFirst (const UniString& oldStr, const UniString& newStr, UIndex from = 0, USize range = MaxUSize);
	UIndex	ReplaceLast  (UniChar oldChar, UniChar newChar);
	UIndex	ReplaceLast  (const UniString& oldStr, const UniString& newStr);
	USize	ReplaceAll   (UniChar oldChar, UniChar newChar, UIndex from = 0, USize range = MaxUSize);
	USize	ReplaceAll   (const UniString& oldStr, const UniString& newStr, UIndex from = 0, USize range = MaxUSize);

	USize	Count (UniChar uc, UIndex from = 0, USize range = MaxUSize) const;
	USize	Count (const UniString& str, UIndex from = 0, USize range = MaxUSize) const;

		// Character specific manipulation

	void		SetToUpperCase (UIndex from = 0, USize range = MaxUSize);
	void		SetToLowerCase (UIndex from = 0, USize range = MaxUSize);

	UniString	ToUpperCase (UIndex from = 0, USize range = MaxUSize) const;
	UniString	ToLowerCase (UIndex from = 0, USize range = MaxUSize) const;

		// Parsing

	bool	IsASCII (void) const;

	template<typename FormatType, class Type1>
	USize	SScanf (FormatType format, Type1* par1) const
	{
		const UniChar::Layout* formatStrs[2] = {GetScanfFormatUStrOf (par1), nullptr};
		return CheckedScanf (format, formatStrs, par1);
	}

	template<typename FormatType, class Type1, class... Types>
	USize	SScanf (FormatType format, Type1* par1, Types*... pars) const
	{
		const UniChar::Layout* formatStrs[] = { GetScanfFormatUStrOf (par1), GetScanfFormatUStrOf (pars)..., nullptr };
		return CheckedScanf (format, formatStrs, par1, pars...);
	}

	template<typename FormatType, class... Types>
	static UniString	SPrintf (FormatType format, Types... pars)
	{
		const UniChar::Layout* formatStrs[] = { GetPrintfFormatUStrOf (pars)..., nullptr };
		return CheckedPrintf (format, formatStrs, ToVarArg (pars)...);
	}

		// Conversion

	enum OnConversionError { ReplaceWithFillers, ThrowException };

	UStr	ToUStr (UIndex from = 0, USize range = MaxUSize) const gs_lifebound;
	CStr	ToCStr (UIndex from = 0, USize range = MaxUSize, GSCharCode charCode = CC_Default, OnConversionError onConversionError = ReplaceWithFillers) const;
	CStr	ToCStr (GSCharCode charCode) const;

	UniString	ToDecomposed (void) const;
	UniString	ToComposed (void) const;
	UniString	ToCompatibilityDecomposed (void) const;
	UniString	ToCompatibilityComposed (void) const;

	// Copies string to a newly allocated Layout/UTF8 buffer
	UniChar::Layout*	CopyUStr (UIndex from = 0, USize range = MaxUSize) const;	// Returned pointer should be deleted by the caller -> delete[]
	char*				CopyUTF8 (UIndex from = 0, USize range = MaxUSize, OnConversionError onConversionError = ReplaceWithFillers) const;	// Returned pointer should be deleted by the caller -> delete[]

	const void*		ToPrintf (void) const gs_lifebound;
	void*			ToScanf  (void) gs_lifebound;

		// I/O

	virtual	GSErrCode	Read  (IChannel& ic) override;
	virtual	GSErrCode	Write (OChannel& oc) const override;

		// Other

	ULong	GenerateHashValue (void) const;

		// Debug

	virtual void	Print	   (OChannel& oc) const override;
	virtual bool	CheckState (void) const override;

	GSROOT_DLL_EXPORT friend std::ostream&	operator<< (std::ostream&, const UniString&);
};

GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (UniChar leftOp, UniChar                          rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (UniChar leftOp, const UniString&                 rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (UniChar leftOp, const UniChar::Layout*           rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (UniChar leftOp, const char*                      rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (UniChar leftOp, const UniString::Substring&      rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (UniChar leftOp, const UniString::ConstSubstring& rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (UniChar leftOp, std::u16string_view              rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (UniChar leftOp, std::string_view                 rightOp);

GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString& leftOp, UniChar                          rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString& leftOp, const UniString&                 rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString& leftOp, const UniChar::Layout*           rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString& leftOp, const char*                      rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString& leftOp, const UniString::Substring&      rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString& leftOp, const UniString::ConstSubstring& rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString& leftOp, std::u16string_view              rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString& leftOp, std::string_view                 rightOp);

GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniChar::Layout* leftOp, UniChar                          rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniChar::Layout* leftOp, const UniString&                 rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniChar::Layout* leftOp, const UniString::Substring&      rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniChar::Layout* leftOp, const UniString::ConstSubstring& rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniChar::Layout* leftOp, std::u16string_view              rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniChar::Layout* leftOp, std::string_view                 rightOp);

GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const char* leftOp, UniChar                          rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const char* leftOp, const UniString&                 rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const char* leftOp, const UniString::Substring&      rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const char* leftOp, const UniString::ConstSubstring& rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const char* leftOp, std::u16string_view              rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const char* leftOp, std::string_view                 rightOp);

GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::Substring& leftOp, UniChar                          rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::Substring& leftOp, const UniString&                 rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::Substring& leftOp, const UniChar::Layout*           rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::Substring& leftOp, const char*                      rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::Substring& leftOp, const UniString::Substring&      rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::Substring& leftOp, const UniString::ConstSubstring& rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::Substring& leftOp, std::u16string_view              rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::Substring& leftOp, std::string_view                 rightOp);

GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::ConstSubstring& leftOp, UniChar                          rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::ConstSubstring& leftOp, const UniString&                 rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::ConstSubstring& leftOp, const UniChar::Layout*           rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::ConstSubstring& leftOp, const char*                      rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::ConstSubstring& leftOp, const UniString::Substring&      rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::ConstSubstring& leftOp, const UniString::ConstSubstring& rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::ConstSubstring& leftOp, std::u16string_view              rightOp);
GSROOT_DLL_EXPORT UniString::Concatenation	operator+ (const UniString::ConstSubstring& leftOp, std::string_view                 rightOp);

GSROOT_DLL_EXPORT extern const UniString EmptyUniString;

GS_FORCE_INLINE void		Append (FastLogger::LogComposer& logComposer, const UniString& string);

GSROOT_DLL_EXPORT String	LogAssertSubject (FastLogger::LogComposer& logComposer, const UniString& subject);


inline UniString::UniString ()
{
	content = ShareEmptyBuffer ();
}


inline UniString::UniString (UniString&& source):
	content (source.content)
{
	source.content = nullptr;
}


inline UniString::UniCharRef	UniString::operator[] (UIndex idx)
{
	REF_CHECK (idx < content->length);

	return UniCharRef (this, idx);
}


inline UniChar	UniString::operator[] (UIndex idx) const
{
	REF_CHECK (idx < content->length);

	return content->string[idx];
}


inline UniChar	UniString::GetChar (UIndex idx) const
{
	REF_CHECK (idx < content->length);

	return content->string[idx];
}


inline void		UniString::SetChar (UIndex idx, UniChar uc)
{
	REF_CHECK (idx < content->length);

	AboutToModify ();

	content->string[idx] = uc;
}


inline UniChar	UniString::GetLast (void) const
{
	REF_CHECK (content->length > 0);

	return content->string[content->length - 1];
}


inline UniString&	UniString::operator+= (UniChar uc)
{
	Append (uc);

	return *this;
}


inline UniString&	UniString::operator+= (const UniString& str)
{
	NULL_REF_CHECK (str);

	Append (str);

	return *this;
}


inline UniString&	UniString::operator+= (const UniChar::Layout* uStr)
{
	NULL_PTR_CHECK (uStr);

	Append (uStr);

	return *this;
}


inline UniString&	UniString::operator+= (const char* cStr)
{
	NULL_PTR_CHECK (cStr);

	Append (cStr, CC_Default);

	return *this;
}


inline UniString&	UniString::operator+= (std::u16string_view str)
{
	Append (str);

	return *this;
}


inline UniString&	UniString::operator+= (std::string_view str)
{
	Append (str, CC_Default);

	return *this;
}


template <USize BufferCapacity>
ArrayFB<UniString, BufferCapacity> UniString::Split (const UniString& separatorString) const
{
	ArrayFB<UniString, BufferCapacity> parts;
	Split (separatorString, GetInserter (parts));

	return parts;
}


template <USize BufferCapacity>
ArrayFB<UniString, BufferCapacity> UniString::Split (const UniString& separatorCharSet, EmptyPartProcessing emptyPartProcessing) const
{
	ArrayFB<UniString, BufferCapacity> parts;
	Split (separatorCharSet, emptyPartProcessing, GetInserter (parts));

	return parts;
}


inline USize	UniString::GetLength (void) const
{
	return content->length;
}


inline bool		UniString::IsEmpty	(void) const
{
	return (content->length == 0);
}


inline bool		UniString::BeginsWith (UniChar uc) const
{
	if (content->length == 0)
		return false;

	return (content->string[0] == uc);
}


inline bool		UniString::EndsWith (UniChar uc) const
{
	if (content->length == 0)
		return false;

	return (content->string[content->length - 1] == uc);
}


inline void		UniString::AboutToModify (void)
{
	if (content->refCounter > static_cast<Int32> (1))
		DetachBuffer ();
}


inline void		UniString::AboutToModify (USize minCapacity)
{
	if (content->refCounter > static_cast<Int32> (1))
		DetachBuffer (minCapacity);
	else
		AdjustCapacity (minCapacity);
}


inline void		UniString::AboutToInsert (USize charCount)
{
	if (content->refCounter > static_cast<Int32> (1))
		DetachBuffer (content->length + charCount);
	else
		IncreaseCapacity (content->length + charCount);
}


inline void		UniString::AboutToDelete (void)
{
	if (content->refCounter > static_cast<Int32> (1))
		DetachBuffer ();
}


inline void		UniString::SetBuffer (SharedBuffer* newContent)
{
	ReleaseBuffer ();

	content = newContent;
}


inline void		UniString::DetachBuffer (void)
{
	SetBuffer (CopyBuffer (content));
}


inline void		UniString::DetachBuffer (USize newCapacity)
{
	SetBuffer (CopyBuffer (content, newCapacity));
}


inline void		UniString::ReleaseBuffer (void)
{
	if (content != nullptr) {
		if (content->refCounter.UnsafeDecrementIf1 () == 0)
			DeleteBuffer (content);

		content = nullptr;
	}
}


template<typename... Args>
UniString	UniString::Printf (const char* formatString, Args... args)
{
	return PrintfFwd (formatString, args...);
}


template<typename... Args>
UniString	UniString::Printf (const UniString& formatString, Args... args)
{
	return PrintfFwd (formatString.ToUStr (), args...);
}

template<typename... Args>
UniString	UniString::Printf (const UniChar::Layout* formatString, Args... args)
{
	return PrintfFwd (formatString, args...);
}


GS_FORCE_INLINE void	Append (FastLogger::LogComposer& logComposer, const UniString& string)
{
	logComposer.Append (string.ToCStr ().Get ());
}


} // namespace GS


#endif
