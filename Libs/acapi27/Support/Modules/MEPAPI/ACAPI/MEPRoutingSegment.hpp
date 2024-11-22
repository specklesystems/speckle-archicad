#ifndef GS_ACAPI_MEP_ROUTING_SEGMENT_HPP
#define GS_ACAPI_MEP_ROUTING_SEGMENT_HPP

#include "MEPAPIExport.hpp"
#include "MEPEnums.hpp"
#include "MEPUniqueID.hpp"

// ACAPI
#include "ACAPI/ElementBase.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"


namespace ACAPI::MEP {

inline namespace v1 {


class RoutingSegmentDefault;
class RigidSegmentDefault;


/** @brief The RoutingSegment can contain Rigid Segment elements.
	@details This type of element is placed between the corner points of RouteElement.
	@since Archicad 27
	@ingroup MEP
	@par Example code snippet from Test / New MEP
		Getters @snippet QueryElementsAndDefaults.cpp RoutingSegment-Getters-Example
		Modification @snippet ModifyElements.cpp RoutingSegment-Modification-Example
*/
class MEPAPI_EXPORT RoutingSegment final : public ACAPI::ElementBase {
private:
	RoutingSegment (const UniqueID&);

public:
	~RoutingSegment ();

	class Modifier;

	/** @brief Returns a Routing Segment.
		@param uniqueId The UniqueID of the requested RoutingSegment.
		@return If the uniqueId belongs to a RoutingSegment, returns the object associated to it, otherwise Error.
	*/
	static Result<RoutingSegment>	Get (const UniqueID& uniqueId);

	/** @return Returns the width of Cross Section in the RoutingSegment. */
	double							GetCrossSectionWidth () const;

	/** @return Returns the height of Cross Section in the RoutingSegment. */
	double							GetCrossSectionHeight () const;

	/** @return Returns the shape of Cross Section in the RoutingSegment. */
	ConnectorShape					GetCrossSectionShape () const;

	/** @return Returns the UniqueIDs of the RigidSegments contained by the RoutingSegment. */
	std::vector<UniqueID>			GetRigidSegmentIds () const;

	/** @return Returns the UniqueID of the RoutingNode from which the RoutingSegment starts. */
	UniqueID						GetBeginNodeId () const;

	/** @return Returns the UniqueID of the RoutingNode at which the RoutingSegment ends. */
	UniqueID						GetEndNodeId () const;

	/** @return Returns the UniqueID of the RoutingElement that it belongs to. */
	UniqueID						GetRoutingElementId () const;

	/** @return Returns the domain of  the RoutingSegment. */
	Domain							GetDomain () const;

	/** @brief Picks up and returns the Default of the RoutingSegment.
		@return Returns a RoutingSegmentDefault with the parameters of the object it was called for.
	*/
	RoutingSegmentDefault			PickUpDefault () const;

	/** @return Returns the default parameters of the uncustomized RigidSegments. */
	RigidSegmentDefault				GetRigidSegmentDefaultParameters () const;

	/** @return Returns the UniqueID of the PreferenceTable is associated with. */
	UniqueID						GetPreferenceTableId () const;

	/** @brief Executes the passed modifier scope in an Undoable command.
		@param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
		@param undoString The text which appears in the undo queue of Archicad after executing the command.
		@return Returns an error if the process of modification fails for some reason, otherwise nothing.
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

	/** @brief Sets the width of Cross Section in the Routing Segment.
		@param width The value to be set.
	*/
	void			SetCrossSectionWidth (double width);

	/** @brief Sets the width of Cross Section in the Routing Segment.
		@param height The value to be set.
	*/
	void			SetCrossSectionHeight (double height);

	/** @brief Sets the shape of Cross Section in the Routing Segment.
		@param shape The value to be set.
	*/
	void			SetCrossSectionShape (ConnectorShape shape);

	/** @brief Injects the given Default settings to the RoutingSegment.
		@param routingSegmentDefault The Default which will be injected.
		@return Returns an error if the injection fails for some reason, otherwise nothing.
	*/
	Result<void>	Inject (const RoutingSegmentDefault& routingSegmentDefault);

	/** @brief Sets the parameters of the RigidSegments.
		@param rigidSegmentDefault The Default to be set. One should pay attention to the parameter, it has to belong to the same domain than the object it is called for.
		@return Returns an error in case of domain mismatch or if the set operation fails for some internal reason, otherwise nothing.
	*/
	Result<void>	SetRigidSegmentDefaultParameters (const RigidSegmentDefault& rigidSegmentDefault);

	/** @brief Sets the PreferenceTable of the RoutingSegment.
		@param uniqueId The UniqueID of the PreferenceTable.
		@return Returns an error if the parameter does not identify a PreferenceTable, otherwise nothing.
	*/
	Result<void>	SetPreferenceTableId (const UniqueID& uniqueId);
};


template <typename ModifierFunc>
Result<void> RoutingSegment::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_ROUTING_SEGMENT_HPP*/