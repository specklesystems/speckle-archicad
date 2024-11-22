#ifndef ACAPI_UNIQUEID_HPP
#define ACAPI_UNIQUEID_HPP

#include "ArchicadAPIExport.hpp"
#include "APIdefs_Registration.h"


namespace ACAPI {

inline namespace v1 {

/** @brief A unique identifier for API objects. It contains the GUID of the element and the Token of the AddOn which instantiated the element.
	@ingroup APIInfrastructure
	@class UniqueID
*/

class ARCHICADAPI_EXPORT UniqueID {
	GS::Guid guid;
	API_Token token;
public:
	UniqueID (const GS::Guid&, const API_Token&);
	/// @brief Returns the unique identifier of the element.
	/// @return The unique identifier of the element.
	const GS::Guid& GetGuid () const;
	/// @brief Returns the unique identifier of the AddOn which created this instance.
	/// @return The unique identifier of the AddOn which created this instance.
	const API_Token& GetToken () const;

	bool operator== (const UniqueID&) const;
	bool operator!= (const UniqueID&) const;
	bool operator<  (const UniqueID&) const;
};

} // namespace v1

} // namespace ACAPI


namespace std {

//! @cond Doxygen_Suppress
template <>
struct hash<ACAPI::UniqueID> {
	std::size_t operator()(const ACAPI::UniqueID& uniqueId) const
	{
		return uniqueId.GetGuid ().GetHashValue () ^ uniqueId.GetToken ().GenerateHashValue ();
	}
};
//! @endcond

} // std

#endif /* ACAPI_UNIQUEID_HPP */
