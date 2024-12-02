#ifndef GS_ACAPI_MEP_RIGID_SEGMENT_DEFAULT_HPP
#define GS_ACAPI_MEP_RIGID_SEGMENT_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPEnums.hpp"
#include "MEPElementDefault.hpp"
#include "MEPUniqueID.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IRigidSegmentDefaultImpl; }

namespace v1 {


class RigidSegment;


/**
 * @brief The RigidSegmentDefault contains the necessary non-geometric data for creating a RigidSegment element.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref RoutingElementDefault "RoutingElementDefault" and @ref RoutingSegmentDefault "RoutingSegmentDefault"
 */
class MEPAPI_EXPORT RigidSegmentDefault final : public ElementDefault {
	RigidSegmentDefault (std::shared_ptr<Impl::IRigidSegmentDefaultImpl>);
	static Result<RigidSegmentDefault>	Create (const API_Token&, Domain);

protected:
	friend class ACAPI::Impl::ObjectCreator;

public:
	friend class RigidSegmentUIManager;
	friend Result<RigidSegmentDefault>	CreateRigidSegmentDefault (Domain);

	/** @return Returns the width of the RigidSegment. */
	double GetWidth () const;

	/** @return Returns the height of the RigidSegment. */
	double GetHeight () const;

	/** @return Returns the shape of the RigidSegment. */
	ConnectorShape GetShape () const;
};


/**
 * @brief Creates a RigidSegmentDefault
 * @ingroup MEP
 * @param domain The Domain of the requested RigidSegmentDefault.
 * @return If able, returns a copy of Archicad's current Default of the RigidSegment from the RoutingElement tool for the domain defined by the parameter, otherwise Error.
 */
inline Result<RigidSegmentDefault> CreateRigidSegmentDefault (Domain domain)
{
	return RigidSegmentDefault::Create (ACAPI_GetToken (), domain);
}


} // v1

using v1::RigidSegmentDefault;
using v1::CreateRigidSegmentDefault;

} // ACAPI::MEP

#endif /* GS_ACAPI_MEP_RIGID_SEGMENT_DEFAULT_HPP */