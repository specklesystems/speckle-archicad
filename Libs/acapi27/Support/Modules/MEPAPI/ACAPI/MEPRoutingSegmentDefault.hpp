#ifndef GS_ACAPI_MEP_ROUTING_SEGMENT_DEFAULT_HPP
#define GS_ACAPI_MEP_ROUTING_SEGMENT_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"
#include "MEPEnums.hpp"

// ACAPI
#include "ACAPI/ElementDefault.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"


namespace ACAPI::MEP {

namespace Impl { class IRoutingSegmentDefaultImpl; }

inline namespace v1 {

class RoutingSegment;
class RigidSegmentDefault;

/** @brief The RoutingSegmentDefault contains the necessary non-geometric data for creating and modifying a Routing Segment.
	@ingroup MEP
	@since Archicad 27
	@ingroup MEP
	@par Example code snippet from Test / New MEP
		Take a look at @ref RoutingElementDefault "RoutingElementDefault"
		RoutingSegmentDefault Modification @snippet ModifyElements.cpp RoutingSegmentDefault-Modification-Example
*/
class MEPAPI_EXPORT RoutingSegmentDefault : public ACAPI::ElementDefault {
protected:
	RoutingSegmentDefault (std::shared_ptr<Impl::IRoutingSegmentDefaultImpl>);
	static Result<RoutingSegmentDefault> Create (const API_Token&, Domain);

	friend class RoutingElement;
	friend class RoutingElementDefault;
	friend class RoutingSegment;

public:
	class Modifier;
	friend Result<RoutingSegmentDefault>	CreateRoutingSegmentDefault (Domain);
	
	/** @brief Returns the RigidSegmentDefault of the RoutingSegmentDefault. */
	RigidSegmentDefault						GetRigidSegmentDefault () const;

	/** @brief Returns the width of Cross Section in the Routing Segment. */
	double									GetCrossSectionWidth () const;

	/** @brief Returns the height of Cross Section in the Routing Segment. */
	double									GetCrossSectionHeight () const;

	/** @brief Returns the shape of Cross Section in the Routing Segment. */
	ConnectorShape							GetCrossSectionShape () const;

	/** @brief Returns the domain of the default. */
	Domain									GetDomain () const;

	/** @return Returns the UniqueID of the PreferenceTable is associated with. */
	UniqueID								GetPreferenceTableId () const;

	/** @brief Executes the given modifier scope in a NotUndoable command.
		@param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
		@return Returns an error if the process of modification fails for some reason, otherwise nothing.
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

	/** @brief Sets the RigidSegment to the RoutingSegmentDefault.
		@param rigidSegmentDefault The value to be set.
	*/
	void	SetRigidSegmentDefault (const RigidSegmentDefault& rigidSegmentDefault) const;

	/** @brief Sets the width of Cross Section in the RoutingSegmentDefault.
		@param width The value to be set.
	*/
	void	SetCrossSectionWidth (double width);

	/** @brief Sets the width of Cross Section in the RoutingSegmentDefault.
		@param height The value to be set.
	*/
	void	SetCrossSectionHeight (double height);

	/** @brief Sets the shape of Cross Section in the RoutingSegmentDefault.
		@param shape The value to be set.
	*/
	void	SetCrossSectionShape (ConnectorShape shape);

	/** @brief Sets the PreferenceTable of the RoutingSegmentDefault.
		@param uniqueId The UniqueID of the PreferenceTable.
		@return Returns an error if the parameter does not identify a PreferenceTable, otherwise nothing.
	*/
	Result<void>	SetPreferenceTableId (const UniqueID& uniqueId);
};


/** @brief Creates a RoutingSegmentDefault
	@ingroup MEP
	@param domain The Domain of the requested RoutingSegmentDefault.
	@return If able, returns a copy of Archicad's current Default of the RoutingSegment from the Routing tool for the domain defined by the parameter, otherwise Error.
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

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_ROUTING_SEGMENT_DEFAULT_HPP*/