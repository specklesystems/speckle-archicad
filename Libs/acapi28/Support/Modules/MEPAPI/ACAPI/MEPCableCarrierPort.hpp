#ifndef GS_ACAPI_MEP_CABLECARRIER_PORT_HPP
#define GS_ACAPI_MEP_CABLECARRIER_PORT_HPP

#include "MEPAPIExport.hpp"
#include "MEPPortBase.hpp"

#include "ACAPI/Result.hpp"


namespace ACAPI::MEP {

namespace v1 {


/**
 * @brief The CableCarrierPort represents a connection point of a cable carrier.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PortBase "PortBase"
 */
class MEPAPI_EXPORT CableCarrierPort final : public PortBase {
	CableCarrierPort (const UniqueID&);

public:
	~CableCarrierPort ();

	/**
	 * @brief Returns a CableCarrierPort.
	 * @param uniqueId The UniqueID of the requested CableCarrierPort.
	 * @return If the uniqueId belongs to a CableCarrierPort, returns the object associated to it, otherwise Error.
	 */
	static Result<CableCarrierPort> Get (const UniqueID& uniqueId);
};


} // v1

using v1::CableCarrierPort;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_PIPING_PORT_HPP*/