// *********************************************************************************************************************
// Description:		GRAPHISOFT Guid
//
// Namespace:		GS
// Contact person:	HK
//
// [SG compatible]
// *********************************************************************************************************************


#ifndef GSGUID_HPP
#define GSGUID_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GRoot
#include "Definitions.hpp"
#include "Channel.hpp"

// from Standard Library
#include <iosfwd>

#if defined (macintosh) && !__OBJC2__
	#if defined(IV)		// in /usr/include/obj/objc.h
		#undef IV
	#endif
#endif

namespace GS {

// =====================================================================================================================
// Predeclarations
// =====================================================================================================================

class IChannelX;
class OChannelX;
class UniString;
class String;

template <class Type> struct ObjectStateTypeConversion;


// =====================================================================================================================
// Type definitions
// =====================================================================================================================

enum {
	GUIDInternalError = GuidErrors + 1,
	GUIDInvalidString = GuidErrors + 2
};

// ---------------------------------------------------------------------------------------------------------------------
// Guid class
// ---------------------------------------------------------------------------------------------------------------------

// Do not make any functions of Guid virtual!

class GSROOT_DLL_EXPORT Guid {
protected:
	UInt32			time_low;
	unsigned short	time_mid;
	unsigned short	time_hi_and_version;
	unsigned char	clock_seq_hi_and_reserved;
	unsigned char	clock_seq_low;
	unsigned char	node[6];

public:
	enum GenerateGuidSelector { GenerateGuid };

	Guid ();
	Guid (GenerateGuidSelector);

	explicit Guid (const char* string);
	explicit Guid (const GS::UniString& string);

	GSErrCode		Generate (void);
	void			Clear (void);
	GSErrCode		ConvertToString (char* string) const;
	UniString		ToUniString (void) const;
	String			ToString (void) const;
	GSErrCode		ConvertFromString (const char* string);
	GSErrCode		ConvertFromString (const Utf16Char* string);
	GSErrCode		ConvertFromString (const GS::UniString& string);
	GSErrCode		ConvertFromPrefixString (const char* string);
	GSErrCode		ConvertFromPrefixString (const Utf16Char* string);
	GSErrCode		ConvertFromPrefixString (const GS::UniString& string);
	Guid			Invert () const;

	bool			IsEqual (const Guid& rightOp) const;
	bool			IsNull (void) const;
	Int32			Compare (const Guid& rightOp) const;
	bool			HasPrefix (UInt32 prefix) const;

	bool			operator== (const Guid& rightOp) const;
	bool			operator!= (const Guid& rightOp) const;
	bool			operator<  (const Guid& rightOp) const;
	bool			operator>  (const Guid& rightOp) const;
	bool			operator<= (const Guid& rightOp) const;
	bool			operator>= (const Guid& rightOp) const;

	unsigned short	GetHashValue (void) const;
	GS_FORCE_INLINE ULong	GenerateHashValue () const;

	UInt32			GetPrefix (void) const;
	void			SetPrefix (UInt32 prefix);

	void			IV (GS::PlatformSign inplatform);
	void			IV (GS::PlatformSign inplatform, GS::PlatformSign toplatform);

	inline GSErrCode	Read  (IChannel& ic);
	inline GSErrCode	Write (OChannel& oc) const;
	void				Read  (IChannelX& ic);
	void				Write (OChannelX& oc) const;
	GSErrCode			ReadAsText  (IChannel& ic);
	GSErrCode			WriteAsText (OChannel& oc) const;

	GSErrCode			ReadStructured  (IChannel& ic);
	GSErrCode			WriteStructured (OChannel& oc) const;

	GS_FORCE_INLINE GSErrCode	ReadBinary  (IChannel& ic);
	GS_FORCE_INLINE GSErrCode	WriteBinary (OChannel& oc) const;

	template<typename T>
	static bool		IsGuidString (const T& string);
	static void		GenerateDeterministicGuids (void);
	static void		RestartDeterministicGuidGenerator (void);

// Debug

	GSROOT_DLL_EXPORT friend std::ostream&	operator<< (std::ostream&, Guid);
};


static_assert (sizeof (Guid) == 2 * sizeof (Int64), "sizeof (Guid) != 2 * sizeof (Int64)");			// method implementations rely on this


enum {
	GUIDStringLength =	sizeof (Guid) * 2 +	4		// number of hex digits + number of separators characters
};


template <>
struct GSROOT_DLL_EXPORT ObjectStateTypeConversion<Guid> {
	static constexpr bool isConvertible = true;

	typedef UniString ConvertedType;

	static GSErrCode	 Convert (const Guid& id, UniString& idString);
	static GSErrCode	 Convert (const UniString& idString, Guid& id);
};


inline Guid::Guid ()
{
	Int64* i = reinterpret_cast<Int64*> (this);

	i[0] = 0;
	i[1] = 0;
}


inline Guid::Guid (GenerateGuidSelector)
{
	Generate ();
}


inline void		Guid::Clear (void)
{
	Int64* i = reinterpret_cast<Int64*> (this);

	i[0] = 0;
	i[1] = 0;
}


inline bool		Guid::IsEqual (const Guid& rightOp) const
{
	return (*this == rightOp);
}


inline bool		Guid::IsNull (void) const
{
	const Int64* i = reinterpret_cast<const Int64*> (this);

	return (i[0] == 0 && i[1] == 0);
}


inline bool		Guid::operator== (const Guid& rightOp) const
{
	const Int64* i = reinterpret_cast<const Int64*> (this);
	const Int64* ri = reinterpret_cast<const Int64*> (&rightOp);

	return (i[0] == ri[0] && i[1] == ri[1]);
}


inline bool		Guid::operator!= (const Guid& rightOp) const
{
	return !(*this == rightOp);
}


inline bool		Guid::operator< (const Guid& rightOp) const
{
	return Compare (rightOp) < 0;
}


inline bool		Guid::operator> (const Guid& rightOp) const
{
	return Compare (rightOp) > 0;
}


inline bool		Guid::operator<= (const Guid& rightOp) const
{
	return Compare (rightOp) <= 0;
}


inline bool		Guid::operator>= (const Guid& rightOp) const
{
	return Compare (rightOp) >= 0;
}


inline GSErrCode	Guid::Read (GS::IChannel& ic)
{
	return ic.Read (*this);
}


inline GSErrCode	Guid::Write (GS::OChannel& oc) const
{
	return oc.Write (*this);
}


GS_FORCE_INLINE GSErrCode	Guid::ReadBinary (IChannel& ic)
{
	return ic.ReadBin (reinterpret_cast<char*> (this), sizeof (Guid));
}


GS_FORCE_INLINE GSErrCode	Guid::WriteBinary (OChannel& oc) const
{
	return oc.WriteBin (reinterpret_cast<const char*> (this), sizeof (Guid));
}


template<typename T>
bool Guid::IsGuidString (const T& string)
{
	return GS::Guid ().ConvertFromString (string) == NoError;
}


// ---------------------------------------------------------------------------------------------------------------------
// Global operators and functions
// ---------------------------------------------------------------------------------------------------------------------

inline OChannel&	operator<< (OChannel& oc, const Guid& guid)
{
	char buffer[50];	// it has space for later format-changing
	buffer[0] = 0;
	guid.ConvertToString (buffer);
	oc << buffer;
	return oc;
}


GS_FORCE_INLINE ULong	Guid::GenerateHashValue () const
{
	static_assert (sizeof (GS::Guid) == 4 * sizeof (ULong), "sizeof (GS::Guid) != 4 * sizeof (ULong)");

	const ULong* g = reinterpret_cast<const ULong*> (this);

	return (g[0] + g[1] + g[2] + g[3]);		// resulting deviation is not the best, but is fast and can be inlined
}


GSROOT_DLL_EXPORT extern const Guid	NULLGuid;

} // namespace GS


#endif
