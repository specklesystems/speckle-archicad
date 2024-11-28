#ifndef ACAPI_CUTTINGPLANE_HPP
#define ACAPI_CUTTINGPLANE_HPP

#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

#include "Poly2DTypes.hpp"
#include <vector>

#include "APIdefs_ErrorCodes.h"

namespace GS { class UniString; }
namespace ACAPI { namespace Impl { class CuttingPlaneImpl; } }

namespace ACAPI {

namespace Cutaway {

namespace v1 {

/**
 * @brief Information regarding cut polygons.
 * @struct API_CutPolygonInfo
 * @ingroup CuttingPlaneManagement
 */
struct API_CutPolygonInfo {
	/**
	 * @brief The polygons of the cutting surface
	 * @var cuttingSurfacePolygons
	 */
	std::vector<Geometry::MultiPolygon2D> cuttingSurfacePolygons;


	/**
	 * @brief The size of the cutting polygon
	 * @var area
	 */
	double area;
};


/**
 * @brief CuttingPlane if the representation of the cutting plane settings.
 * @ingroup CuttingPlaneManagement
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT CuttingPlane : public Object
{
friend class Impl::CuttingPlaneImpl;
	friend ACAPI::Result<CuttingPlane> GetCuttingPlane ();
	explicit CuttingPlane (const API_Token& token);

public:

	/**
	 * @brief
	 * @ingroup CuttingPlaneManagement
	 * @return Returns whether the 3D Cutaway is enabled.
	 */
	ACAPI::Result<bool> Is3DCutawayEnabled  () const;

	/**
	 * @brief
	 * @ingroup CuttingPlaneManagement
	 * @param status True if the Cutaway should be enabled, false if it should be disabled.
	 * @return Turns the 3D Cutaway on/off.
	 */
	ACAPI::Result<void> Set3DCutawayStatus (bool status) const;

	/**
	 * @brief
	 * @ingroup CuttingPlaneManagement
	 * @return Returns whether the Cutting Planes are visible.
	 */
	ACAPI::Result<bool>	AreCuttingPlanesVisible () const;

	/**
	 * @brief
	 * @ingroup CuttingPlaneManagement
	 * @param visible True if the Cutting Planes should be visible, false if not.
	 * @return Shows or hides the Cutting Planes.
	 */
	ACAPI::Result<void> SetCuttingPlanesVisibility  (bool visible) const;
};

/**
 * @brief
 * @ingroup CuttingPlaneManagement
 * @return Gets the entity representing the cutting plane.
 */
inline ACAPI::Result<CuttingPlane> GetCuttingPlane ()
{
	return Ok (CuttingPlane (ACAPI_GetToken ()));
}

}	 // namespace v1

using namespace v1;

}	 // namespace Cutaway

}	 // namespace ACAPI


#endif /* ACAPI__LM_CUTTINGPLANE_HPP */