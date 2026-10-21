#ifndef GS_ACAPI_MEP_ELECTRICAL_PANEL_DEFAULT_HPP
#define GS_ACAPI_MEP_ELECTRICAL_PANEL_DEFAULT_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"
#include "MEPElementDefault.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IElectricalPanelDefaultImpl; }


/**
 * @brief The ElectricalPanelDefault contains the necessary non-geometric data for creating an ElectricalPanel element.
 * @since Archicad 30
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElectricalPanelDefault final : public ElementDefault {
	ElectricalPanelDefault (std::shared_ptr<Impl::IElectricalPanelDefaultImpl>);
	static Result<ElectricalPanelDefault> Create (const API_Token&);

protected:
	friend class ACAPI::Impl::ObjectCreator;

public:
	friend Result<ElectricalPanelDefault> CreateElectricalPanelDefault ();
	friend MEPAPI_EXPORT Result<ElectricalPanelDefault> CreateElectricalPanelDefault (const ACAPI::ElementDefault&);

	/**
	 * @brief Places an ElectricalPanel element based on this Default.
	 * @param coordinate The coordinate where the ElectricalPanel will be placed.
	 * @param orientation The orientation of the ElectricalPanel.
	 * @param requiredId The guid to be set for the ElectricalPanel - optional parameter.
	 * @return If executed with success, returns the newly placed ElectricalPanel's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const API_Coord3D& coordinate, const Orientation& orientation, const std::optional<API_Guid>& requiredId = std::nullopt) const;

	/** @return Returns the panel name. */
	GS::UniString GetPanelName () const;

	/** @return Returns the circuit name prefix. */
	GS::UniString GetCircuitNamePrefix () const;

	/** @return Returns the circuit id style index. */
	short GetCircuitIdStyle () const;

	/** @return Returns the number of circuit defaults. */
	uint32_t GetCircuitDefaultCount () const;
};


/**
 * @brief Creates an ElectricalPanelDefault.
 * @ingroup MEP
 * @return If able, returns a copy of Archicad's current Default of the ElectricalPanel tool, otherwise Error.
 */
inline Result<ElectricalPanelDefault> CreateElectricalPanelDefault ()
{
	return ElectricalPanelDefault::Create (ACAPI_GetToken ());
}


/**
 * @brief Creates an ElectricalPanelDefault from the given base element default.
 * @param defaultElem The base element default which will be converted to an ElectricalPanelDefault.
 * @ingroup MEP
 * @return If the given base element default refers to an ElectricalPanel, returns a copy of the ElectricalPanelDefault, otherwise Error.
 */
MEPAPI_EXPORT Result<ElectricalPanelDefault> CreateElectricalPanelDefault (const ACAPI::ElementDefault& defaultElem);


} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_ELECTRICAL_PANEL_DEFAULT_HPP */
