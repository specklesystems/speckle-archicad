#ifndef GS_ACAPI_MEP_MODIFIABLE_ELEMENT_HPP
#define GS_ACAPI_MEP_MODIFIABLE_ELEMENT_HPP

#include "MEPAPIExport.hpp"
#include "MEPModifiableElementBase.hpp"

#include "ACAPI/Result.hpp"


namespace ACAPI::MEP {

namespace v1 {

/**
 * @brief The Modifiable Element represents an instantiable ModifiableElementBase.
 * @since Archicad 27
 * @ingroup MEP
 */
class MEPAPI_EXPORT ModifiableElement final : public ModifiableElementBase {
	ModifiableElement (std::shared_ptr<Impl::IElementBaseImpl>);

public:
	~ModifiableElement ();

	/**
	 * @brief Returns a Modifiable Element.
	 * @param uniqueId The UniqueID of the requested Element.
	 * @return If the uniqueId belongs to an Element, returns the object associated to it, otherwise Error.
	 */
	static Result<ModifiableElement> Get (const UniqueID& uniqueId);
};


} // v1

using v1::ModifiableElement;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_MODIFIABLE_ELEMENT_HPP*/