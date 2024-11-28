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


/**
 * @brief Represents a `GS::Guid` in the API layer.
 * @ingroup APIInfrastructure
 * @struct API_Guid
 * @remarks API_Guid is essentially a `GS::Guid`. It has the same size and structure and only exists because of certain C++ language limitations: namely that a union (like @ref API_Element) cannot contain a class that has a constructor or destructor. Since @ref API_Elem_Head needs to contain a Guid member, and it cannot be a `GS::Guid`, the @ref API_Guid structure was introduced.
 * 			This means that you should treat @ref API_Guid structures as `GS::Guid` in your code, and use the following provided functions to convert between the two:
 * 			```cpp
 * 			inline GS::Guid APIGuid2GSGuid (API_Guid guid);
 * 			inline const GS::Guid APIGuid2GSGuid (const API_Guid guid);
 * 			inline API_Guid GSGuid2APIGuid (GS::Guid guid);
 * 			inline const API_Guid GSGuid2APIGuid (const GS::Guid guid);
 * 			```
 * 			All these functions do two things:
 * 			- check that @ref API_Guid and `GS::Guid` are the same size at compile time and
 * 			- reinterpret_cast the input @ref API_Guid reference to a `GS::Guid` reference, or vice versa.
 * 			There are comparison operators (==,!=, <, >=, >, >=) defined to compare @c API_Guids with each other or with `GS::Guid` s.
 * 			There's also a macro called APINULLGuid for the @ref API_Guid representation of the GS::NULLGuid constant.
 * 			From Archicad 12 you are able to use @ref API_Guid for GS::HashTable key because it has GenerateHashValue method.
 */
struct API_Guid {
//! @cond Doxygen_Suppress
	UInt32			time_low;
	unsigned short	time_mid;
	unsigned short	time_hi_and_version;
	unsigned char	clock_seq_hi_and_reserved;
	unsigned char	clock_seq_low;
	unsigned char	node[6];
//! @endcond

/**
 * @brief Generate a hash value that's why API_Guid can be used with GS::HashTable.
 * @return Generated hash value.
 */
	ULong			GenerateHashValue () const;
};														// same structure as GS::Guid

static_assert (sizeof (API_Guid) == sizeof (GS::Guid), "sizeof (API_Guid) != sizeof (GS::Guid)");		// (API_Guid always reinterpret_cast to GS::Guid)

// --- Inline funtions	------------------------------------------------------------------------------------------------

/**
 * @brief Converting from API_Guid to a GS::Guid.
 * @param guid The API_Guid to convert.
 * @return Converted guid.
 * @ingroup Conversion
 */
inline GS::Guid& APIGuid2GSGuid (API_Guid& guid)
{
	return reinterpret_cast<GS::Guid&> (guid);
}

/**
 * @brief Converting from API_Guid to GS::Guid.
 * @param guid The API_Guid to convert.
 * @return Converted guid.
 * @ingroup Conversion
 */
inline const GS::Guid& APIGuid2GSGuid (const API_Guid& guid)
{
	return reinterpret_cast<const GS::Guid&> (guid);
}

/**
 * @brief Converting from GS::Guid to API_Guid.
 * @param guid The GS::Guid to convert.
 * @return Converted guid.
 * @ingroup Conversion
 */
inline API_Guid& GSGuid2APIGuid (GS::Guid& guid)
{
	return reinterpret_cast<API_Guid&> (guid);
}

/**
 * @brief Converting from GS::Guid to API_Guid.
 * @param guid The GS::Guid to convert.
 * @return Converted guid.
 * @ingroup Conversion
 */
inline const API_Guid& GSGuid2APIGuid (const GS::Guid& guid)
{
	return reinterpret_cast<const API_Guid&> (guid);
}

/**
 * @brief Converting from a string to an API_Guid.
 * @param str String representation of guid.
 * @return Converted guid.
 * @ingroup Conversion
 */
inline API_Guid APIGuidFromString (const char* str)
{
	return GSGuid2APIGuid (GS::Guid (str));
}

/**
 * @brief Converting the API_Guid to a GS::UniString.
 * @param guid The API_Guid to convert.
 * @return Guid represented in GS::UniString.
 * @ingroup Conversion
 */
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

/// @return Generating an API_Guid
/// @ingroup APIInfrastructure
inline API_Guid GenerateAPIGuid ()
{
	return GSGuid2APIGuid (GS::Guid::GenerateGuid);
}


/**
 * @brief Represents an empty API guid.
 * @ingroup APIInfrastructure
 * @var APINULLGuid
 */
constexpr API_Guid APINULLGuid = {};
/// @brief A special API guid for undefined behavior
#define APIUndefinedGuid	(GSGuid2APIGuid (GS::Guid ("E9C06C46-F7E2-4023-8435-9242864B1041")))

// ---------------------------------------------------------------------------------------------------------------------


#endif	// API_GUID_HPP
