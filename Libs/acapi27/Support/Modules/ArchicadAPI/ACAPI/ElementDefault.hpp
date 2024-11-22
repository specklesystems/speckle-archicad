#ifndef ACAPI_ELEMENTDEFAULT_HPP
#define ACAPI_ELEMENTDEFAULT_HPP

#include "ArchicadAPIExport.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

namespace ACAPI {

namespace Impl { class ElementDefaultImpl; }

inline namespace v1 {

/** @brief A base class for all element defaults.
 * @ingroup Element
 * @details This class represents the default state of Archicad elements. When an element 
 * is placed in Archicad, either from the API of from the UI, it always uses the Element Defaults as its default parameters.*/
class ARCHICADAPI_EXPORT ElementDefault : public Object
{
protected:
	ElementDefault (std::shared_ptr<Impl::ElementDefaultImpl> impl);

public:

	/** @brief Sets the locally prepared Default settings to the Archicad Default.
	*	@returns Error if Archicad could not apply the set of values to the Default.*/
	Result<void>	SetAsArchicadDefault () const;
};

}

}

#endif // ACAPI_ELEMENTDEFAULT_HPP