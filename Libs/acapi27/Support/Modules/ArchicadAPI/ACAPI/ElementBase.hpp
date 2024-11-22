#ifndef ACAPI_ELEMENTBASE_HPP
#define ACAPI_ELEMENTBASE_HPP

#include "ArchicadAPIExport.hpp"
#include "ACAPI/Object.hpp"
#include "UniqueID.hpp"

namespace ACAPI {
namespace Impl {
	class ElementDefaultImpl;
}

inline namespace v1 {


/// @brief A base class for all elements.
/// @ingroup Element
class ARCHICADAPI_EXPORT ElementBase : public Object
{
protected:
	ElementBase (std::shared_ptr<Impl::ObjectImpl> impl);

public:
	UniqueID	GetElemId () const;
};

}

}

#endif // ACAPI_ELEMENTBASE_HPP