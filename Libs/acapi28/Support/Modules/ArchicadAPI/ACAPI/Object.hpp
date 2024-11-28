#ifndef ACAPI_OBJECT_HPP
#define ACAPI_OBJECT_HPP

#include "ACAPI/ArchicadAPIExport.hpp"

#include <memory>
#include "GSGuid.hpp"
#include "API_Guid.hpp"

using API_Token = API_Guid;

/**
 * @brief Returns the token associated with the AddOn.
 * @ingroup AddOnIdentification
 * @return The token associated with the add-on.
 * @remarks It is not guaranteed that this function will always return the same value. Always obtain your
 * 			token by calling this function on demand.
 */
API_Token ACAPI_GetToken ();

//! @cond Doxygen_Suppress
namespace ACAPI::Impl { 
	class UsageLogger;
	class ObjectImpl; 

	template <class T>
	class ImplAccessor;
}
//! @endcond

namespace ACAPI {

namespace v1 {

/**
 * @brief A base class for all ACAPI objects. Purely technical.
 * @ingroup APIInfrastructure
 * @class Object
 */
class ARCHICADAPI_EXPORT Object {
	friend class Impl::UsageLogger;

	template <class T>
	friend class Impl::ImplAccessor;

protected:
	/**
	 * @brief Impl object given by constructor.
	 */
	std::shared_ptr<Impl::ObjectImpl> mImpl;

	/**
	 * @brief Default destructor.
	 */
	~Object ();

public:
	/**
	 * @brief Constructs a new object.
	 * @param impl Impl instance of the object.
	 */
	Object (std::shared_ptr<Impl::ObjectImpl> impl);

	/**
	 * @brief Get the token for this object.
	 * @return The token for this object.
	 */
	const API_Token& GetToken () const;
};

} // namespace v1

using namespace v1;

} // namespace ACAPI


#endif /* ACAPI_OBJECT_HPP */
