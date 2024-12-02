// *********************************************************************************************************************
// API definitions - API_Guid structure and inline conversion functions
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (API_GUID_HPP)
#define	API_GUID_HPP

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes	--------------------------------------------------------------------------------------------------------

#include "GSGuid.hpp"
#include "UniString.hpp"


// --- Type definitions	------------------------------------------------------------------------------------------------


struct API_Guid {
	UInt32			time_low;
	unsigned short	time_mid;
	unsigned short	time_hi_and_version;
	unsigned char	clock_seq_hi_and_reserved;
	unsigned char	clock_seq_low;
	unsigned char	node[6];
	ULong			GenerateHashValue () const;
};														// same structure as GS::Guid

static_assert (sizeof (API_Guid) == sizeof (GS::Guid), "sizeof (API_Guid) != sizeof (GS::Guid)");		// (API_Guid always reinterpret_cast to GS::Guid)

// --- Inline funtions	------------------------------------------------------------------------------------------------

inline GS::Guid& APIGuid2GSGuid (API_Guid& guid)
{
	return reinterpret_cast<GS::Guid&> (guid);
}

inline const GS::Guid& APIGuid2GSGuid (const API_Guid& guid)
{
	return reinterpret_cast<const GS::Guid&> (guid);
}

inline API_Guid& GSGuid2APIGuid (GS::Guid& guid)
{
	return reinterpret_cast<API_Guid&> (guid);
}

inline const API_Guid& GSGuid2APIGuid (const GS::Guid& guid)
{
	return reinterpret_cast<const API_Guid&> (guid);
}

inline API_Guid APIGuidFromString (const char* string)
{
	return GSGuid2APIGuid (GS::Guid (string));
}

inline GS::UniString APIGuidToString (const API_Guid& guid)
{
	return APIGuid2GSGuid (guid).ToUniString ();
}

inline bool operator== (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) == reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator== (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) == gsGuid);
}

inline bool operator== (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) == gsGuid);
}

inline bool operator!= (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) != reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator!= (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) != gsGuid);
}

inline bool operator!= (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) != gsGuid);
}

inline bool operator< (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) < reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator< (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (gsGuid < reinterpret_cast<const GS::Guid&> (apiGuid));
}

inline bool operator< (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) < gsGuid);
}

inline bool operator<= (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) <= reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator<= (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (gsGuid <= reinterpret_cast<const GS::Guid&> (apiGuid));
}

inline bool operator<= (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) <= gsGuid);
}

inline bool operator> (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) > reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator> (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (gsGuid > reinterpret_cast<const GS::Guid&> (apiGuid));
}

inline bool operator> (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) > gsGuid);
}

inline bool operator>= (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) >= reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator>= (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (gsGuid >= reinterpret_cast<const GS::Guid&> (apiGuid));
}

inline bool operator>= (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) >= gsGuid);
}

inline ULong API_Guid::GenerateHashValue () const
{
	return APIGuid2GSGuid (*this).GetHashValue ();
}

constexpr API_Guid APINULLGuid	({});
#define APIUndefinedGuid	(GSGuid2APIGuid (GS::Guid ("E9C06C46-F7E2-4023-8435-9242864B1041")))

// ---------------------------------------------------------------------------------------------------------------------


#endif	// API_GUID_HPP
