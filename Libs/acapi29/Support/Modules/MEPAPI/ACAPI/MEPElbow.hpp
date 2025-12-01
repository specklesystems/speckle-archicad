#ifndef GS_ACAPI_MEP_ELBOW_HPP
#define GS_ACAPI_MEP_ELBOW_HPP

#include "MEPAPIExport.hpp"
#include "MEPElementBase.hpp"

// ACAPI
#include "ACAPI/Result.hpp"

#include <optional>

namespace ACAPI::MEP {


class ElbowDefault;


/**
 * @brief The Elbow can connect two straight RoutingSegments with the same dimensions but different directions.
 * @details This type of element can be placed in RoutingNodes.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test/New MEP
 * 		Getters @snippet QueryElementsAndDefaults.cpp Elbow-Getters-Example
 * 		Labeling @snippet LabelingElements.cpp Elbow-Labeling-Example
 */
class MEPAPI_EXPORT Elbow final : public ElementBase {
	Elbow (const UniqueID&);
public:
	~Elbow ();

	/**
	 * @brief Returns an Elbow.
	 * @param uniqueId The UniqueID of the requested Elbow.
	 * @return If the uniqueId belongs to an Elbow, returns the object associated to it, otherwise Error.
	 */
	static Result<Elbow>	Get (const UniqueID& uniqueId);

	/** @return Returns the insulation thickness if the Elbow has insulation, otherwise std::nullopt. Elbow of cable carrier domain cannot have insulation. */
	std::optional<double> GetInsulationThickness () const;

	/** @return Returns the width of the Elbow. */
	double GetWidth () const;

	/** @return Returns the height of the Elbow. */
	double GetHeight () const;

	/** @return Returns the shape of the Elbow. */
	ConnectorShape GetShape () const;

	/** @return Returns the radius of the Elbow. */
	double GetRadius () const;

	/**
	 * @brief The radius of the Elbow is calculated with the help of this value in the case of rectangular Duct and Cable Carrier.
	 * @return Returns the factor radius of the Elbow in the case of rectangular Duct and Cable Carrier, otherwise Error.
	 */
	Result<double> GetFactorRadius () const;

	/** @return Returns the UniqueID of the RoutingNode that it belongs to. */
	UniqueID GetRoutingNodeId () const;

	/** @return Returns the domain of the Elbow. */
	Domain GetDomain () const;

	/** @return Returns an ElbowDefault with the parameters of the object it was called for. */
	ElbowDefault PickUpDefault () const;

	/** @return Returns the UniqueID of the PreferenceTable if a circular DuctElbow or a PipeElbow, in the case of rectangular DuctElbow and CableCarrierElbow returns Error. */
	Result<UniqueID> GetPreferenceTable () const;
};

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_ELBOW_HPP*/