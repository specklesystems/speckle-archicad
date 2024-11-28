#ifndef GS_ACAPI_MEP_BRANCH_DEFAULT_HPP
#define GS_ACAPI_MEP_BRANCH_DEFAULT_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"
#include "MEPElementDefault.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IBranchDefaultImpl; }

namespace v1 {


/**
 * The BranchDefault contains the necessary non-geometric data for creating a Branch element.
 * @since Archicad 27
 * @ingroup MEP
 */
class MEPAPI_EXPORT BranchDefault : public ElementDefault {
	BranchDefault (std::shared_ptr<Impl::IBranchDefaultImpl>);
	static Result<BranchDefault> Create (const API_Token&, Domain);

protected:
	friend class ACAPI::Impl::ObjectCreator;

public:
	friend Result<BranchDefault> CreateBranchDefault (Domain);
};


/**
 * @brief Creates a BranchDefault
 * @ingroup MEP
 * @details After creating and customizing a BranchDefault, it needs to be set as Archicad's default in order to use it during the upcoming RoutingElement connections.
 * @param domain The Domain of the requested BranchDefault.
 * @return If able, returns a copy of Archicad's current Default of the Branch tool for the domain defined by the parameter, otherwise Error
 */
inline Result<BranchDefault> CreateBranchDefault (Domain domain)
{
	return BranchDefault::Create (ACAPI_GetToken (), domain);
}


} // v1

using v1::BranchDefault;
using v1::CreateBranchDefault;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_BRANCH_DEFAULT_HPP