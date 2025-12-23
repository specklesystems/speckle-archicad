#ifndef GS_ACAPI_MEP_ELEMENT_DEFAULT_HPP
#define GS_ACAPI_MEP_ELEMENT_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPEnums.hpp"
#include "MEPVentilationPortDefault.hpp"
#include "MEPPipingPortDefault.hpp"
#include "MEPCableCarrierPortDefault.hpp"

#include "ACAPI/Result.hpp"
#include "ACAPI/ElementDefault.hpp"
#include "ACAPI/ModifyScope.hpp"

#include <optional>
#include <utility>


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IElementDefaultImpl; }


/**
 * @brief The ElementDefault contains the necessary non-geometric data for creating a MEP element.
 * @ingroup MEP
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippets from Test / New MEP
 * 		Getters @snippet QueryElementsAndDefaults.cpp ElementDefault-Getters-Example
 * 		@snippet QueryElementsAndDefaults.cpp ElementDefault-Getters-Example2
 */
class MEPAPI_EXPORT ElementDefault : public ACAPI::ElementDefault {
protected:
	/**
	 * @brief Constructs an ElementDefault with the given element default implementation.
	 * @param impl The element default implementation.
	 */
	ElementDefault (std::shared_ptr<Impl::IElementDefaultImpl> impl);
	friend class ACAPI::Impl::ObjectCreator;

public:
	class Modifier;

	/** @return Returns the insulation thickness if the ElementDefault has insulation, otherwise std::nullopt. ElementDefaults of cable carrier domain cannot have insulation. */
	std::optional<double> GetInsulationThickness () const;

	/** @return Returns the number of ports. */
	uint32_t GetPortCount () const;

	/** @return Returns the domain of the ElementDefault. */
	Domain GetDomain () const;

	/** @return Returns the main GUID of the referenced Library Part. */
	API_Guid GetObjectId () const;

	/** 
	 * @param portIndex Zero-based index of Ports. 
	 * @return Returns an error if the index is out of range, otherwise the domain of the given Port.
	 */
	Result<Domain> GetDomainOfPort (uint32_t portIndex) const;

	/**
	 * @param portIndex Zero-based index of Ports.
	 * @return Returns an error if the index is out of range, or the corresponding Port is not of Ventilation domain.
	 */
	Result<VentilationPortDefault> GetVentilationPortDefault (uint32_t portIndex) const;

	/**
	 * @param portIndex Zero-based index of Ports.
	 * @return Returns an error if the index is out of range, or the corresponding Port is not of Piping domain.
	 */
	Result<PipingPortDefault> GetPipingPortDefault (uint32_t portIndex) const;

	/**
	 * @param portIndex Zero-based index of Ports.
	 * @return Returns an error if the index is out of range, or the corresponding Port is not of CableCarrier domain.
	 */
	Result<CableCarrierPortDefault> GetCableCarrierPortDefault (uint32_t portIndex) const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);

	/** @return Returns the referenced Library Part's size along the X axis. */
	double GetObjectXSize () const;

	/** @return Returns the referenced Library Part's size along the Y axis. */
	double GetObjectYSize () const;

	/** @return Returns the base rotation of the element in radians. */
	double GetBaseRotation () const;

	/** @return Returns whether the element is reflected, 'true' if it is reflected, 'false' otherwise. */
	bool GetReflected () const;
};


/**
 * @brief Modifier of the ElementDefault.
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElementDefault::Modifier : public ACAPI::ModifierBase {
	ElementDefault& parent;

	friend ElementDefault;
protected:
	/**
	 * @brief Constructs a Modifier with the given parent ElementDefault.
	 * @param parent The parent  ElementDefault.
	 */
	Modifier (ElementDefault& parent);
	virtual ~Modifier ();

public:

	/** @brief Removes the insulation.*/
	void RemoveInsulation ();

	/**
	 * @brief Sets the thickness of insulation on the ElementDefault.
	 * @param insulationThickness The value to be set.
	 * @return Returns an error if the Element is of cable carrier domain, otherwise nothing.
	 */
	Result<void> SetInsulationThickness (double insulationThickness);
	
	/**
	 * @brief Sets the referenced library part of the ElementDefault.
	 * @param libraryPartId The main GUID of the library part.
	 */
	void SetObjectId (const API_Guid& libraryPartId);

	/**
	 * @brief Sets the referenced library part's size along the X axis.
	 * @param size The value to be set.
	 * @return Returns an error if the size parameter is not positive.
	 */
	Result<void> SetObjectXSize (double size);

	/**
	 * @brief Sets the referenced library part's size along the Y axis.
	 * @param size The value to be set.
	 * @return Returns an error if the size parameter is not positive.
	 */
	Result<void> SetObjectYSize (double size);

	/**
	 * @brief Sets the base rotation of the ModifiableElement.
	 * @param rotation The base rotation to be set, in radians.
	 */
	void SetBaseRotation (double rotation);

	/**
	 * @brief Sets whether the ModifiableElement is reflected.
	 * @param reflected 'true' to make the element reflected, 'false' otherwise.
	 */
	void SetReflected (bool reflected);
};


template<class ModifierFunc>
Result<void> ElementDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_ELEMENT_DEFAULT_HPP*/