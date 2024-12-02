#ifndef ACAPI_ELEMENTBASE_HPP
#define ACAPI_ELEMENTBASE_HPP

#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/Object.hpp"
#include "UniqueID.hpp"
#include "Result.hpp"

namespace ACAPI {
namespace Impl {
	class ElementDefaultImpl;
}

namespace v1 {


/**
 * @brief A base class for all elements.
 * @ingroup Element
 */
class ARCHICADAPI_EXPORT ElementBase : public Object
{
protected:
	/**
	 * @brief Constructs a new ElementBase.
	 * @param impl Impl instance of the object.
	 */
	ElementBase (std::shared_ptr<Impl::ObjectImpl> impl);

public:
	/**
	 * @brief Get unique identifier of the ElementBase object.
	 * @return Unique identifier of the ElementBase object.
	 */
	UniqueID	GetElemId () const;

	/**
	* @brief Checks whether the element is editable.
	* @return Returns nothing if the element is editable, otherwise the error code and error message containing information about the reason.
	*/
	Result<void>	IsEditable () const;
};

}

using namespace v1;

}

#endif // ACAPI_ELEMENTBASE_HPP
