#ifndef GS_ACAPI_MEP_ELEMENT_HPP
#define GS_ACAPI_MEP_ELEMENT_HPP

#include "MEPAPIExport.hpp"
#include "MEPElementBase.hpp"

#include "ACAPI/Result.hpp"


namespace ACAPI::MEP {

namespace v1 {


/**
 * @brief The Element represents an instantiable ElementBase.
 * @since Archicad 27
 * @ingroup MEP
 */
class MEPAPI_EXPORT Element final : public ElementBase {
	Element (std::shared_ptr<Impl::IElementBaseImpl>);

public:
	~Element ();

	/**
	 * @brief Returns an Element.
	 * @param uniqueId The UniqueID of the requested Element.
	 * @return If the uniqueId belongs to an Element, returns the object associated to it, otherwise Error.
	 */
	static Result<Element> Get (const UniqueID& uniqueId);
};


} // v1

using v1::Element;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_ELEMENT_HPP*/