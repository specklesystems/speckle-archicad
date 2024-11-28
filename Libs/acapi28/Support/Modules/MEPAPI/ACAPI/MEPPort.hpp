#ifndef GS_ACAPI_MEP_PORT_HPP
#define GS_ACAPI_MEP_PORT_HPP

#include "MEPAPIExport.hpp"
#include "MEPPortBase.hpp"

#include "ACAPI/Result.hpp"


namespace ACAPI::MEP {

namespace v1 {


/**
 * @brief The Port represents an instantiable PortBase. Through this object you can reference to the three domain's ports in a common way.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PortBase "PortBase"
 */
class MEPAPI_EXPORT Port final : public PortBase {
	Port (std::shared_ptr<Impl::IPortBaseImpl>);

public:
	~Port ();

	/**
	 * @brief Returns a Port.
	 * @param uniqueId The UniqueID of the requested Port.
	 * @return If the uniqueId belongs to a Port, returns the object associated to it, otherwise Error.
	 */
	static Result<Port> Get (const UniqueID& uniqueId);
};


} // v1

using v1::Port;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_PORT_HPP*/