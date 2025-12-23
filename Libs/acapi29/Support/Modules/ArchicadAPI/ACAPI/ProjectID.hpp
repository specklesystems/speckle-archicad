#ifndef ACAPI_PROJECT_ID_HPP
#define ACAPI_PROJECT_ID_HPP

#include "ACAPI/Object.hpp"

namespace IO { class Location; }

namespace ACAPI {

/**
 * @brief Unique identifier of the project. Useful for usage logging.
 * @ingroup APIInfrastructure
 * @since Archicad 29
 * @param projectLocation should be the location of the project.
 * @return GS::UniString A string representing the unique identifier of the project.
 * @remark You can get the projectLocation from ACAPI_ProjectOperation_Project.
 */
ARCHICADAPI_EXPORT GS::UniString GetCEIPProjectID (const IO::Location& projectLocation);

} // namespace ACAPI	
#endif
