#ifndef ACAPI_OBJECT_HPP
#define ACAPI_OBJECT_HPP

#include "ArchicadAPIExport.hpp"

#include <memory>
#include "GSGuid.hpp"
#include "API_Guid.hpp"

using API_Token = API_Guid;

//! @cond Doxygen_Suppress
namespace ACAPI::Impl { 
	class UsageLogger;
	class ObjectImpl; 

	template <class T>
	class ImplAccessor;
}
//! @endcond

namespace ACAPI {

inline namespace v1 {

/** @brief A base class for all ACAPI objects. Purely technical.
	@ingroup APIInfrastructure
	@class Object
*/
class ARCHICADAPI_EXPORT Object {
	friend class Impl::UsageLogger;

	template <class T>
	friend class Impl::ImplAccessor;

protected:
	std::shared_ptr<Impl::ObjectImpl> mImpl;
	~Object ();

public:
	Object (std::shared_ptr<Impl::ObjectImpl> impl);
	const API_Token& GetToken () const;
};

} // namespace v1

} // namespace ACAPI


#endif /* ACAPI_OBJECT_HPP */
