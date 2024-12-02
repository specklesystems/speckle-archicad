#ifndef GS_ACAPI_MEP_ROUTING_SEGMENT_HPP
#define GS_ACAPI_MEP_ROUTING_SEGMENT_HPP

#include "MEPAPIExport.hpp"
#include "MEPEnums.hpp"
#include "MEPUniqueID.hpp"

// ACAPI
#include "ACAPI/ElementBase.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"

#include <optional>


namespace ACAPI::MEP {

namespace v1 {


class RoutingSegmentDefault;
class RigidSegmentDefault;


/**
 * @brief The RoutingSegment can contain Rigid Segment elements.
 * @details This type of element is placed between the corner points of RoutingElement.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Getters @snippet QueryElementsAndDefaults.cpp RoutingSegment-Getters-Example
 * 		Modification - Rectangular @snippet ModifyElements.cpp RoutingSegment-Rectangular-Modification-Example
 * 		Modification - Circular @snippet ModifyElements.cpp RoutingSegment-Circular-Modification-Example
 */
class MEPAPI_EXPORT RoutingSegment final : public ACAPI::ElementBase {
private:
	RoutingSegment (const UniqueID&);

public:
	~RoutingSegment ();

	class Modifier;

	/**
	 * @brief Returns a Routing Segment.
	 * @param uniqueId The UniqueID of the requested RoutingSegment.
	 * @return If the uniqueId belongs to a RoutingSegment, returns the object associated to it, otherwise Error.
	 */
	static Result<RoutingSegment> Get (const UniqueID& uniqueId);

	/** @return Returns the width of the RoutingSegment. */
	double GetCrossSectionWidth () const;

	/** @return Returns the height of the RoutingSegment. */
	double GetCrossSectionHeight () const;

	/** @return Returns the shape of the RoutingSegment. */
	ConnectorShape GetCrossSectionShape () const;
	
	/** @return Returns error if the Cross Section shape is Rectangular, otherwise the referenceId of the Circular Cross Section in the RoutingSegment. */
	Result<uint32_t> GetCrossSectionReferenceId () const;

	/** @return Returns the UniqueIDs of the RigidSegments contained by the RoutingSegment. */
	std::vector<UniqueID> GetRigidSegmentIds () const;

	/** @return Returns the UniqueID of the RoutingNode from which the RoutingSegment starts. */
	UniqueID GetBeginNodeId () const;

	/** @return Returns the UniqueID of the RoutingNode at which the RoutingSegment ends. */
	UniqueID GetEndNodeId () const;

	/** @return Returns the UniqueID of the RoutingElement that it belongs to. */
	UniqueID GetRoutingElementId () const;

	/** @return Returns the domain of  the RoutingSegment. */
	Domain GetDomain () const;

	/**
	 * @brief Picks up and returns the Default of the RoutingSegment.
	 * @return Returns a RoutingSegmentDefault with the parameters of the object it was called for.
	 */
	RoutingSegmentDefault PickUpDefault () const;

	/** @return Returns the default parameters of the uncustomized RigidSegments. */
	RigidSegmentDefault GetRigidSegmentDefaultParameters () const;

	/** @return Returns the UniqueID of the PreferenceTable is associated with. */
	UniqueID GetPreferenceTableId () const;

	/** @return Returns the anchor position of the RoutingSegment. */
	API_AnchorID GetAnchor () const;

	/** @return Returns the offset from the reference line along the X-axis of cross-section's plane. */
	double GetReferenceLineOffsetX () const;

	/** @return Returns the offset from the reference line along the Y-axis of cross-section's plane. */
	double GetReferenceLineOffsetY () const;

	/** @return Returns the wall thickness of the RoutingSegment. The RigidSegment's Port will use this value as well. */
	double GetWallThickness () const;

	/** @return Returns the connection style used by the RigidSegment's Ports. */
	ConnectionStyle GetConnectionStyle () const;

	/** @return Returns the size of the flange (width for Ventilation, diameter for Piping) if the connection style is Flanged. */
	std::optional<double> GetFlangeSize () const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT RoutingSegment::Modifier : public ACAPI::ModifierBase {
	RoutingSegment& parent;
	Modifier (RoutingSegment&);
	virtual ~Modifier ();

public:
	friend RoutingSegment;

	/**
	 * @brief Sets the width of the RoutingSegment.
	 * @param width The value to be set.
	 * @return Returns error if the Cross Section Shape is Circular, otherwise nothing.
	 */
	Result<void> SetCrossSectionWidth (double width);

	/**
	 * @brief Sets the height of the Routing Segment.
	 * @param height The value to be set.
	 * @return Returns error if the Cross Section Shape is Circular, otherwise nothing.
	 */
	Result<void> SetCrossSectionHeight (double height);

	/**
	 * @brief Sets the shape of the Routing Segment.
	 * @param shape The value to be set.
	 * @return Returns error if the shape is not supported by the RoutingSegment, otherwise nothing.
	 */
	Result<void> SetCrossSectionShape (ConnectorShape shape);

	/**
	 * @brief Sets the referenceId of Circular Cross Section in the Routing Segment.
	 * @param referenceId The referenceId of the row from the Segment PreferenceTable. Only the valid row's ReferenceId can be set.
	 * @return Returns an error if the Cross Section Shape is not Circular or the referenceId is not a valid row of the actual preferenceTable, otherwise nothing.
	 */
	Result<void> SetCrossSectionReferenceId (uint32_t referenceId);

	/**
	 * @brief Injects the given Default settings to the RoutingSegment.
	 * @param routingSegmentDefault The Default which will be injected.
	 * @return Returns an error if the injection fails for some reason, otherwise nothing.
	 */
	Result<void> Inject (const RoutingSegmentDefault& routingSegmentDefault);

	/**
	 * @brief Sets the parameters of the RigidSegments.
	 * @param rigidSegmentDefault The Default to be set. One should pay attention to the parameter, it has to belong to the same domain than the object it is called for.
	 * @return Returns an error in case of domain mismatch or if the set operation fails for some internal reason, otherwise nothing.
	 */
	Result<void> SetRigidSegmentDefaultParameters (const RigidSegmentDefault& rigidSegmentDefault);

	/**
	 * @brief Sets the PreferenceTable of the RoutingSegment.
	 * @param uniqueId The UniqueID of the PreferenceTable.
	 * @return Returns an error if the parameter does not identify a PreferenceTable, otherwise nothing.
	 */
	Result<void> SetPreferenceTableId (const UniqueID& uniqueId);

	/**
		@brief Sets the anchor position of the RoutingSegment.
		@param anchor The value to be set.
	 */
	void SetAnchor (API_AnchorID anchor);

	/**
		@brief Sets the offset from the reference line along the X-axis of cross-section's plane.
		@param offset The value to be set.
	 */
	void SetReferenceLineOffsetX (double offset);

	/**
		@brief Sets the offset from the reference line along the Y-axis of cross-section's plane.
		@param offset The value to be set.
	 */
	void SetReferenceLineOffsetY (double offset);

	/**
	 * @brief Sets the wall thickness of the RoutingSegment.
	 * @param thickness The value to be set.
	 * @return Returns an error if the RoutingSegment's wall thickness is controlled by its PreferenceTable, otherwise nothing.
	 */
	Result<void> SetWallThickness (double thickness);

	/**
	 *  @brief Sets the connection style of the RoutingSegment.
	 *  @param connectionStyle The value to be set.
	 *	@return Returns an error if the RoutingSegment's domain does not support the provided connection style, otherwise nothing.
	 */
	Result<void> SetConnectionStyle (ConnectionStyle connectionStyle);

	/**
	 * @brief Sets the flange size (width for Ventilation, diameter for Piping) of the RoutingSegment if its connection style is Flanged.
	 * @param flangeSize The value to be set.
	 * @return Returns an error if the RoutingSegment's connection style is not Flanged, otherwise nothing.
	 */
	Result<void> SetFlangeSize (double flangeSize);
};


template <typename ModifierFunc>
Result<void> RoutingSegment::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::RoutingSegment;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_ROUTING_SEGMENT_HPP*/