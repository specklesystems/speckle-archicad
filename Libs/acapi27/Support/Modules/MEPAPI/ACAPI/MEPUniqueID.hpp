#ifndef GS_ACAPI_MEP_UNIQUEID_HPP
#define GS_ACAPI_MEP_UNIQUEID_HPP

#include "MEPAPIExport.hpp"

#include "ACAPI/UniqueID.hpp"


namespace ACAPI::MEP {

/** @since Archicad 27
	@ingroup MEP
*/
class MEPAPI_EXPORT UniqueID : public ACAPI::UniqueID {
public:
	UniqueID (const GS::Guid&, const API_Token&);
};

} // ACAPI::MEP


namespace std {

/// @private
template <>
struct hash<ACAPI::MEP::UniqueID> {
	std::size_t operator()(const ACAPI::MEP::UniqueID& uniqueId) const
	{
		return uniqueId.GetGuid ().GetHashValue () ^ uniqueId.GetToken ().GenerateHashValue ();
	}
};

}

#endif // GS_ACAPI_MEP_UNIQUEID_HPP