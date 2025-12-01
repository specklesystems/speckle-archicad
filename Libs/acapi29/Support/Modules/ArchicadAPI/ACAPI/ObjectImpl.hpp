#ifndef GS_ACAPI_OBJECTIMPL_HPP
#define GS_ACAPI_OBJECTIMPL_HPP

#include "ACAPI/ArchicadAPIExport.hpp"

#include "APIdefs_Registration.h"
#include "ACAPI/Object.hpp"

#define GETPARENTIMPL(parentClassName) parentClassName& impl = static_cast<parentClassName&> (*parent.mImpl)

#define GETCONSTIMPL(className) const className& impl = static_cast<const className&> (*mImpl)

#define GETIMPL(className) className& impl = static_cast<className&> (*mImpl)

namespace ACAPI::Impl {

/**
 * @brief ObjectImpl is the base class for all the implementation classes.
 * @ingroup APIInfrastructure
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT ObjectImpl  {
protected:
	/**
	 * @brief The token used by the implementation.
	 * @var token
	 */
	const API_Token token;

public:
	/**
	 * @brief Constructs an object of the ObjectImpl class.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @param token The token used by the implementation.
	 */
	ObjectImpl (const API_Token& token);
	virtual ~ObjectImpl ();

	/**
	 * @brief You can get the token that's used by the implementation.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return Returns the token as API_Token used by the implementation.
	 */
	const API_Token& GetToken () const { return token; }
};


} // namespace ACAPI::Impl


#endif /* GS_ACAPI_OBJECTIMPL_HPP */
