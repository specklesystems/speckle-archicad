#ifndef GS_ACAPI_MEP_ROUTING_SEGMENT_DEFAULT_HPP
#define GS_ACAPI_MEP_ROUTING_SEGMENT_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"
#include "MEPEnums.hpp"

// ACAPI
#include "ACAPI/ElementDefault.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IRoutingSegmentDefaultImpl; }

namespace v1 {

class RoutingSegment;
class RigidSegmentDefault;

/**
 * @brief The RoutingSegmentDefault contains the necessary non-geometric data for creating and modifying a Routing Segment.
 * @ingroup MEP
 * @since Archicad 27
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref RoutingElementDefault "RoutingElementDefault"
 * 		RoutingSegmentDefault Modification @snippet ModifyElements.cpp RoutingSegmentDefault-Modification-Example
 */
class MEPAPI_EXPORT RoutingSegmentDefault : public ACAPI::ElementDefault {
protected:

	friend class ACAPI::Impl::ObjectCreator;

	/**
	 * @brief Constructs a RoutingSegmentDefault with the given implementation.
	 * @param impl The given implementation.
	 */
	RoutingSegmentDefault (std::shared_ptr<Impl::IRoutingSegmentDefaultImpl> impl);

	/**
	 * @brief Creates a RoutingSegmentDefault with the given token and domain.
	 * @param token The given token.
	 * @param domain The given domain.
	 * @return The result of the creation with the created RoutingSegmentDefault.
	 */
	static Result<RoutingSegmentDefault> Create (const API_Token& token, Domain domain);

public:
	class Modifier;
	friend Result<RoutingSegmentDefault> CreateRoutingSegmentDefault (Domain);
	
	/** @return Returns the RigidSegmentDefault of the RoutingSegmentDefault. */
	RigidSegmentDefault GetRigidSegmentDefault () const;

	/** @return Returns the width of the RoutingSegmentDefault. */
	double GetCrossSectionWidth () const;

	/** @return Returns the height of the RoutingSegmentDefault. */
	double GetCrossSectionHeight () const;

	/** @return Returns the shape of the RoutingSegmentDefault. */
	ConnectorShape GetCrossSectionShape () const;

	/** @return Returns error if the Cross Section shape is Rectangular, otherwise the referenceId of the Circular Cross Section in the RoutingSegmentDefault. */
	Result<uint32_t> GetCrossSectionReferenceId () const;

	/** @return Returns the domain of the default. */
	Domain GetDomain () const;

	/** @return Returns the UniqueID of the PreferenceTable is associated with. */
	UniqueID GetPreferenceTableId () const;

	/** @return Returns the anchor position of the RoutingSegmentDefault. */
	API_AnchorID GetAnchor () const;

	/** @return Returns the offset from the reference line along the X-axis of cross-section's plane */
	double GetReferenceLineOffsetX () const;

	/** @return Returns the offset from the reference line along the Y-axis of cross-section's plane */
	double GetReferenceLineOffsetY () const;

	/** @return Returns the wall thickness of the RoutingSegmentDefault. The RigidSegmentDefault's Port will use this value as well. */
	double GetWallThickness () const;

	/** @return Returns the connection style used by the RigidSegmentDefault's Ports. */
	ConnectionStyle GetConnectionStyle () const;

	/** @return Returns the size of the flange (width for Ventilation, diameter for Piping) if the connection style is Flanged. */
	std::optional<double> GetFlangeSize () const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


class MEPAPI_EXPORT RoutingSegmentDefault::Modifier : public ACAPI::ModifierBase {
	RoutingSegmentDefault& parent;
	Modifier (RoutingSegmentDefault&);
	virtual ~Modifier ();

public:
	friend RoutingSegmentDefault;

	/**
	 * @brief Sets the RigidSegment to the RoutingSegmentDefault.
	 * @param rigidSegmentDefault The value to be set.
	 */
	void SetRigidSegmentDefault (const RigidSegmentDefault& rigidSegmentDefault) const;

	/**
	 * @brief Sets the width of the RoutingSegmentDefault.
	 * @param width The value to be set.
	 * @return Returns error if the Cross Section Shape is Circular, otherwise nothing.
	 */
	Result<void> SetCrossSectionWidth (double width);

	/** 
		@brief Sets the width of the RoutingSegmentDefault.
		@param height The value to be set.
		@return Returns error if the Cross Section Shape is Circular, otherwise nothing.
	 */
	Result<void> SetCrossSectionHeight (double height);

	/**
	 * @brief Sets the shape of the RoutingSegmentDefault.
	 * @param shape The value to be set.
	 * @return Returns error if the shape is not supported by the RoutingSegment, otherwise nothing.
	 */
	Result<void> SetCrossSectionShape (ConnectorShape shape);

	/**
	 * @brief Sets the referenceId of Circular Cross Section in the RoutingSegmentDefault.
	 * @param referenceId The referenceId of the row from the Segment PreferenceTable. Only the valid row's ReferenceId can be set.
	 * @return Returns an error if the Cross Section Shape is not Circular or the referenceId is not a valid row of the actual preferenceTable, otherwise nothing.
	 */
	Result<void> SetCrossSectionReferenceId (uint32_t referenceId);

	/**
	 * @brief Sets the PreferenceTable of the RoutingSegmentDefault.
	 * @param uniqueId The UniqueID of the PreferenceTable.
	 * @return Returns an error if the parameter does not identify a PreferenceTable, otherwise nothing.
	 */
	Result<void> SetPreferenceTableId (const UniqueID& uniqueId);

	/**
		@brief Sets the anchor position of the RoutingSegmentDefault.
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
	 * @brief Sets the wall thickness of the RoutingSegmentDefault.
	 * @param thickness The value to be set.
	 * @return Returns an error if the RoutingSegmentDefault's wall thickness is controlled by its PreferenceTable, otherwise nothing.
	 */
	Result<void> SetWallThickness (double thickness);

	/**
	 *  @brief Sets the connection style of the RoutingSegmentDefault.
	 *  @param connectionStyle The value to be set.
	 *	@return Returns an error if the RoutingSegmentDefault's domain does not support the provided connection style, otherwise nothing.
	 */
	Result<void> SetConnectionStyle (ConnectionStyle connectionStyle);

	/**
	 * @brief Sets the flange size (width for Ventilation, diameter for Piping) of the RoutingSegment if its connection style is Flanged.
	 * @param flangeSize The value to be set.
	 * @return Returns an error if the RoutingSegment's connection style is not Flanged, otherwise nothing.
	 */
	Result<void> SetFlangeSize (double flangeSize);
};


/**
 * @brief Creates a RoutingSegmentDefault
 * @ingroup MEP
 * @param domain The Domain of the requested RoutingSegmentDefault.
 * @return If able, returns a copy of Archicad's current Default of the RoutingSegment from the RoutingElement tool for the domain defined by the parameter, otherwise Error.
 */
inline Result<RoutingSegmentDefault> CreateRoutingSegmentDefault (Domain domain)
{
	return RoutingSegmentDefault::Create (ACAPI_GetToken (), domain);
}


template <typename ModifierFunc>
Result<void> RoutingSegmentDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}

} // v1

using v1::RoutingSegmentDefault;
using v1::CreateRoutingSegmentDefault;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_ROUTING_SEGMENT_DEFAULT_HPP*/