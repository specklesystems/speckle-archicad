#ifndef GS_ACAPI_MEP_BEND_HPP
#define GS_ACAPI_MEP_BEND_HPP

#include "MEPAPIExport.hpp"
#include "MEPElementBase.hpp"

// ACAPI
#include "ACAPI/Result.hpp"

#include <optional>

namespace ACAPI::MEP {

namespace v1 {


class BendDefault;


/**
 * @brief The Bend can connect two straight RoutingSegments with the same dimensions but different directions.
 * @details This type of element can be placed in RoutingNodes.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test/New MEP
 * 		Getters @snippet QueryElementsAndDefaults.cpp Bend-Getters-Example
 * 		Labeling @snippet LabelingElements.cpp Bend-Labeling-Example
 */
class MEPAPI_EXPORT Bend final : public ElementBase {
	Bend (const UniqueID&);
public:
	~Bend ();

	/**
	 * @brief Returns a Bend.
	 * @param uniqueId The UniqueID of the requested Bend.
	 * @return If the uniqueId belongs to a Bend, returns the object associated to it, otherwise Error.
	 */
	static Result<Bend>	Get (const UniqueID& uniqueId);

	/** @return Returns the insulation thickness if the Bend has insulation, otherwise std::nullopt. Bend of cable carrier domain cannot have insulation. */
	std::optional<double> GetInsulationThickness () const;

	/** @return Returns the width of the Bend. */
	double GetWidth () const;

	/** @return Returns the height of the Bend. */
	double GetHeight () const;

	/** @return Returns the shape of the Bend. */
	ConnectorShape GetShape () const;

	/** @return Returns the radius of the Bend. */
	double GetRadius () const;

	/**
	 * @brief The radius of the Bend is calculated with the help of this value in the case of rectangular Duct and Cable Carrier.
	 * @return Returns the factor radius of the Bend in the case of rectangular Duct and Cable Carrier, otherwise Error.
	 */
	Result<double> GetFactorRadius () const;

	/** @return Returns the UniqueID of the RoutingNode that it belongs to. */
	UniqueID GetRoutingNodeId () const;

	/** @return Returns the domain of the Bend. */
	Domain GetDomain () const;

	/** @return Returns a BendDefault with the parameters of the object it was called for. */
	BendDefault PickUpDefault () const;

	/** @return Returns the UniqueID of the PreferenceTable if a circular DuctBend or a PipeBend, in the case of rectangular DuctBend and CableCarrierBend returns Error. */
	Result<UniqueID> GetPreferenceTable () const;
};

} // v1

using v1::Bend;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_BEND_HPP*/