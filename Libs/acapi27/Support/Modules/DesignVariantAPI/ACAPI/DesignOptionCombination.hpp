#ifndef GS_ACAPI_DESIGNOPTIONCOMBINATION_HPP
#define GS_ACAPI_DESIGNOPTIONCOMBINATION_HPP

#include "DesignOptionAPIExport.hpp"
#include "ACAPI/Object.hpp"

namespace ACAPI {

namespace Impl {
	class DesignOptionCombinationImpl;
	class DesignOptionCombinationViewSettingsImpl;
	class DesignOptionManagerImpl;
}

inline namespace v1 {

/** @brief A class that represents the design option combination of the view settings.
*	@since Archicad 27
*	@ingroup DesignOptions
*/
class DESIGNOPTIONAPI_EXPORT DesignOptionCombination : public Object {
	friend class Impl::DesignOptionCombinationViewSettingsImpl;
	friend class DesignOptionManager;
public:
	/** @returns The name of the combination. */
	GS::UniString GetName () const;

	/** @returns The guid of the combination. */
	GS::Guid GetGuid () const;

private:
	explicit DesignOptionCombination (std::shared_ptr<Impl::DesignOptionCombinationImpl> impl);
};

} // namespace v1

} // namespace ACAPI


#endif /* ACAPI_DESIGNOPTIONCOMBINATION_HPP */
