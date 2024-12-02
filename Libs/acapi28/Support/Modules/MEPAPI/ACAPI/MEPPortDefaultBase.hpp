#ifndef GS_ACAPI_MEP_PORT_DEFAULT_BASE_HPP
#define GS_ACAPI_MEP_PORT_DEFAULT_BASE_HPP

#include "MEPAPIExport.hpp"
#include "MEPEnums.hpp"
#include "MEPUniqueID.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"


namespace ACAPI::MEP {

namespace Impl { class IPortDefaultBaseImpl; }

namespace v1 {


/**
 * @brief Through this PortDefault you can access and configure the Ports of MEPElementDefaults before placement.
 * @since Archicad 28
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Getters @snippet QueryElementsAndDefaults.cpp ElementDefault-Getters-Example2
 */
class MEPAPI_EXPORT PortDefaultBase : public Object {
protected:
	/**
	 * @brief Constructs a PortBase with the given PortDefaultBase implementation.
	 * @param impl The PortDefaultBase implementation.
	 */
	PortDefaultBase (std::shared_ptr<Impl::IPortDefaultBaseImpl> impl);

public:
	class Modifier;

	/** @return Returns the name of the Port which you would see on the user interface. */
	GS::UniString GetName () const;

	/** @return Returns the width of the Port. */
	double GetWidth () const;

	/** @return Returns the shape of the Port. */
	ConnectorShape GetShape () const;

	/** @return Returns the AttributeIndex of the MEPSystem attribute to which it belongs. */
	API_AttributeIndex GetMEPSystem () const;

	/**
	 * @details The domain of the Port can differ from the domain of the element that it belongs to, for ex. in case of Equipments.
	 * @return Returns the domain of the Port.
	 */
	Domain GetDomain () const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


class MEPAPI_EXPORT PortDefaultBase::Modifier : public ACAPI::ModifierBase {
	PortDefaultBase& parent;
protected:
	/**
	 * @brief Constructs a Modifier with the given PortDefaultBase parent.
	 * @param parent The parent PortDefaultBase.
	 */
	Modifier (PortDefaultBase& parent);

public:
	~Modifier ();

	friend PortDefaultBase;

	/**
	 * @brief Sets the width of the port.
	 * @param width The value to be set.
	 */
	void SetWidth (double width);

	/**
	 * @brief Sets the shape of the port.
	 * @param shape The shape to be set.
	 */
	void SetShape (ConnectorShape shape);

	/**
	 * @brief Sets the MEPSystem attribute of a Port.
	 * @param attributeIndex The MEPSystem AttributeIndex to be set.
	 */
	void SetMEPSystem (const API_AttributeIndex& attributeIndex);
};


template <typename ModifierFunc>
Result<void> PortDefaultBase::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


} // v1

using v1::PortDefaultBase;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_PORT_DEFAULT_BASE_HPP*/