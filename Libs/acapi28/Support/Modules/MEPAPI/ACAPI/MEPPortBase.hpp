#ifndef GS_ACAPI_MEP_PORT_BASE_HPP
#define GS_ACAPI_MEP_PORT_BASE_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"
#include "MEPEnums.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"

#include <optional>


namespace ACAPI::MEP {

namespace Impl { class IPortBaseImpl; }

namespace v1 {


/**
 * @brief The Port is associated to an element and it represents a point between elements.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Getters @snippet QueryElementsAndDefaults.cpp Port-Getters-Example
 * 		Modification @snippet ModifyElements.cpp Port-Modification-Example
 */
class MEPAPI_EXPORT PortBase : public Object {
protected:
	/**
	 * @brief Constructs a PortBase with the given port base implementation.
	 * @param impl The port base implementation.
	 */
	PortBase (std::shared_ptr<Impl::IPortBaseImpl> impl);
	~PortBase ();

public:
	class Modifier;

	/** @return Checks if the Port still exists. */
	bool Exists () const;

	/** @return Returns the name of the port which you would see on the user interface. */
	GS::UniString GetName () const;


	/** @return Returns the orientation of the Port, which is based on a direction vector and a rotation vector. */
	Orientation	GetOrientation () const;

	/** @return Returns the width of the Port. */
	double GetWidth () const;

	/** @return Returns the height of the Port.	*/
	double GetHeight () const;

	/** @return Returns the shape of the Port. */
	ConnectorShape GetShape () const;

	/** @return Returns the middle point of the Port. */
	API_Coord3D	GetPosition () const;

	/**
	 * @details The domain of the port can differ from the domain of the element that it belongs to, for ex. in case of Equipments.
	 * @return Returns the domain of the Port.
	 */
	Domain GetDomain () const;

	/** @return Returns the AttributeIndex of the MEPSystem attribute to which it belongs. */
	API_AttributeIndex GetMEPSystem () const;

	/** @return Returns the UniqueID of the connected port, if there is any. */
	std::optional<UniqueID>	GetConnectedPortId () const;

	/** @return Returns the UniqueID of the connected MEP element, if there is any.	*/
	std::optional<UniqueID>	GetConnectedMEPElementId () const;

	/** @return Returns the UniqueID of the MEP element it belongs to. */
	UniqueID GetMEPElementId () const;

	/** @return Returns if the port is physically connected to another port. */
	bool IsPhysicallyConnected () const;

	/**
	 * @details Checks if the Port is physically connectable to another Port. Beside
	 * - Domain
	 * - MEP System
	 * - Position
	 * - Orientation
	 * which are only enough to obtain a logical connection, there are a few other Port settings that need to match perfectly in order to obtain a Port-Port physical connection
	 * and they are the following:
	 * - Shape
	 * - Dimensions
	 * - ConnectionType (this is a GDL parameter, so it can be checked and modified through @ref API_AddParType "API_AddParType")
	 * @param portId The UniqueID of the Port to check against.
	 * @return Returns an error if the parameter does not identify a Port, otherwise the result of the check.
	 */
	Result<bool> IsPhysicallyConnectable (const UniqueID& portId) const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @details Ports of RoutingElement subElements (RigidSegment, Bend, Transition) cannot be directly modified. Please use the RoutingElement's Segment and Node default
	 * parameters for customization.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT PortBase::Modifier : public ACAPI::ModifierBase {
	PortBase& parent;
protected:
	/**
	 * @brief Constructs a Modifier with the given port base parent.
	 * @param parent The parent port base.
	 */
	Modifier (PortBase& parent);

	/**
	 * @brief Finalizes the modifications.
	 */
	void FinalizeModification () override;

public:
	~Modifier ();

	friend PortBase;

	/**
	 * @brief Sets the width of the port.
	 * @param width The value to be set.
	 * @return Returns an error if you are trying to modify a Port of a Branch, otherwise nothing.
	 */
	Result<void> SetWidth (double width);

	/**
	 * @brief Sets the height of the port.
	 * @param height The value to be set.
	 * @return Returns an error if you are trying to modify a Port of a Branch, otherwise nothing.
	 */
	Result<void> SetHeight (double height);

	/**
	 * @brief Sets the shape of the port.
	 * @param shape The shape to be set.
	 * @return Returns an error if you are trying to modify a Port of a Branch, otherwise nothing.
	 */
	Result<void> SetShape (ConnectorShape shape);
	
	/**
	 * @brief Sets the MEPSystem attribute of a Port.
	 * @param attributeIndex The MEPSystem AttributeIndex to be set.
	 * @return Returns an error if you are trying to modify a Port of a Branch, otherwise nothing.
	 */
	Result<void> SetMEPSystem (const API_AttributeIndex& attributeIndex);
};


template <typename ModifierFunc>
Result<void> PortBase::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::PortBase;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_PORT_BASE_HPP*/