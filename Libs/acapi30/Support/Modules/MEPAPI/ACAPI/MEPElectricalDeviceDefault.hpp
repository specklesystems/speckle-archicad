#ifndef GS_ACAPI_MEP_ELECTRICAL_DEVICE_DEFAULT_HPP
#define GS_ACAPI_MEP_ELECTRICAL_DEVICE_DEFAULT_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"
#include "MEPElementDefault.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IElectricalDeviceDefaultImpl; }


/**
 * @brief The ElectricalDeviceDefault contains the necessary non-geometric data for creating an ElectricalDevice element.
 * @since Archicad 30
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElectricalDeviceDefault final : public ElementDefault {
	ElectricalDeviceDefault (std::shared_ptr<Impl::IElectricalDeviceDefaultImpl>);
	static Result<ElectricalDeviceDefault> Create (const API_Token&);

protected:
	friend class ACAPI::Impl::ObjectCreator;

public:
	friend Result<ElectricalDeviceDefault> CreateElectricalDeviceDefault ();
	friend MEPAPI_EXPORT Result<ElectricalDeviceDefault> CreateElectricalDeviceDefault (const ACAPI::ElementDefault&);

	/**
	 * @brief Places an ElectricalDevice element based on this Default.
	 * @param coordinate The coordinate where the ElectricalDevice will be placed.
	 * @param orientation The orientation of the ElectricalDevice.
	 * @param requiredId The guid to be set for the ElectricalDevice - optional parameter.
	 * @return If executed with success, returns the newly placed ElectricalDevice's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const API_Coord3D& coordinate, const Orientation& orientation, const std::optional<API_Guid>& requiredId = std::nullopt) const;

	/** @return Returns the load classification name. */
	GS::UniString GetLoadClassificationName () const;

	/** @return Returns the apparent power in VA. */
	uint32_t GetApparentPower () const;

	/** @return Returns whether the apparent power is enabled. */
	bool GetApparentPowerEnabled () const;
};


/**
 * @brief Creates an ElectricalDeviceDefault.
 * @ingroup MEP
 * @return If able, returns a copy of Archicad's current Default of the ElectricalDevice tool, otherwise Error.
 */
inline Result<ElectricalDeviceDefault> CreateElectricalDeviceDefault ()
{
	return ElectricalDeviceDefault::Create (ACAPI_GetToken ());
}


/**
 * @brief Creates an ElectricalDeviceDefault from the given base element default.
 * @param defaultElem The base element default which will be converted to an ElectricalDeviceDefault.
 * @ingroup MEP
 * @return If the given base element default refers to an ElectricalDevice, returns a copy of the ElectricalDeviceDefault, otherwise Error.
 */
MEPAPI_EXPORT Result<ElectricalDeviceDefault> CreateElectricalDeviceDefault (const ACAPI::ElementDefault& defaultElem);


} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_ELECTRICAL_DEVICE_DEFAULT_HPP */
