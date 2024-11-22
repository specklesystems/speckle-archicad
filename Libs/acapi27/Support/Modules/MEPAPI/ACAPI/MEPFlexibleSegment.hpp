#ifndef GS_ACAPI_MEP_FLEXIBLE_SEGMENT_HPP
#define GS_ACAPI_MEP_FLEXIBLE_SEGMENT_HPP

#include "MEPAPIExport.hpp"

#include "MEPModifiableElementBase.hpp"
#include "MEPFlexibleSegmentDefault.hpp"


namespace ACAPI::MEP {

inline namespace v1 {

/** @brief In contrast to rigid segments flexible duct is not a connection of multiple elements (straight segments and bends), instead a type of ducting pipe that could easily be bent in different angles.
	@since Archicad 27
	@ingroup MEP
	@par Example code snippet from Test / New MEP
		Getters @snippet QueryElementsAndDefaults.cpp FlexibleSegment-Getters-Example
		Modification @snippet ModifyElements.cpp FlexibleSegment-Modification-Example
*/
class MEPAPI_EXPORT FlexibleSegment final : public ModifiableElementBase {
	FlexibleSegment (const UniqueID & uniqueId);

public:
	~FlexibleSegment ();

	class Modifier;

	/** @brief Returns a FlexibleSegment.
		@param uniqueId The UniqueID of the requested FlexibleSegment.
		@return If the uniqueId belongs to a FlexibleSegment, returns the object associated to it, otherwise Error.
	*/
	static Result<FlexibleSegment> Get (const UniqueID& uniqueId);

	/** @brief Picks up the Default from the FlexibleSegment.
		@return Returns a FlexibleSegmentDefault with the parameters of the object it was called for.
	*/
	FlexibleSegmentDefault	PickUpDefault () const;

	/** @return Returns the width of the FlexibleSegment. */
	double	GetWidth () const;

	/** @return Returns the height of the FlexibleSegment. */
	double	GetHeight () const;

	/** @return Returns the control points of the FlexibleSegment.*/
	std::vector<API_Coord3D> GetControlPoints () const;

	/** @brief Returns the domain of the FlexibleSegment.
		@return The returned domain could only be ventilation.
	*/
	Domain	GetDomain () const;

	/** @brief Executes the passed modifier scope in an Undoable command.
		@param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
		@param undoString The text which appears in the undo queue of Archicad after executing the command.
		@return Returns an error if the process of modification fails for some reason, otherwise nothing.
	*/
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT FlexibleSegment::Modifier : public ModifiableElementBase::Modifier {
	FlexibleSegment& parent;

	Modifier (FlexibleSegment&);
	virtual ~Modifier ();

public:
	friend FlexibleSegment;

	/** @brief Injects the Default settings into the FlexibleSegment.
		@param flexibleSegmentDefault The Default what will be injected.
		@return Returns an error if the injection fails for some reason, otherwise nothing.
	*/
	Result<void> Inject (const FlexibleSegmentDefault& flexibleSegmentDefault);

	/** @brief Sets the control points of the FlexibleSegment.
	   @param points The points to be set.
	*/
	void		 SetControlPoints (const std::vector<API_Coord3D>& points);

	/** @brief Sets the width of the FlexibleSegment.
		@param width The value to be set.
		@return Returns an error if the width is not positive, otherwise nothing.
	*/
	Result<void> SetWidth (double width);

	/** @brief Sets the height of the FlexibleSegment.
		@param height The value to be set.
		@return Returns an error if the height is not positive, otherwise nothing.
	*/
	Result<void>  SetHeight (double height);
};


template <typename ModifierFunc>
Result<void> FlexibleSegment::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}

} // v1

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_FLEXIBLE_SEGMENT_HPP*/