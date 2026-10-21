#ifndef ACAPI_DOMAIN_AVAILABILITY_HPP
#define ACAPI_DOMAIN_AVAILABILITY_HPP


#include "ArchicadAPIExport.hpp"

#include "ACAPI/Object.hpp"



namespace ACAPI {


enum class Domain {
	Architecture,
	MEP
};


/**
 * @brief Checks whether the domain is available for the running application.
 * @ingroup APIInfrastructure
 * @since Archicad 29
 * @param domain The desired domain to check.
 * @return bool True if the domain is available, false otherwise.
 */
ARCHICADAPI_EXPORT bool IsDomainAvailable (Domain domain);


} // namespace ACAPI


#endif