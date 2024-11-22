#ifndef GS_ACAPI_MEP_ELEMENT_DEFAULT_HPP
#define GS_ACAPI_MEP_ELEMENT_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPEnums.hpp"

#include "ACAPI/Result.hpp"
#include "ACAPI/ElementDefault.hpp"
#include "ACAPI/ModifyScope.hpp"

#include <optional>
#include <utility>


namespace ACAPI::MEP {

namespace Impl { class IElementDefaultImpl; }

inline namespace v1 {


/** @brief The ElementDefault contains the necessary non-geometric data for creating a MEP element.
	@ingroup MEP 
	@since Archicad 27
	@ingroup MEP
	@par Example code snippets from Test / New MEP
		Getters @snippet QueryElementsAndDefaults.cpp ElementDefault-Getters-Example
		@snippet QueryElementsAndDefaults.cpp ElementDefault-Getters-Example2
*/
class MEPAPI_EXPORT ElementDefault : public ACAPI::ElementDefault {
protected:
	ElementDefault (std::shared_ptr<Impl::IElementDefaultImpl> impl);

public:
	class Modifier;
	/** @return Returns the insulation thickness if the ElementDefault has insulation, otherwise std::nullopt. ElementDefaults of cable carrier domain cannot have insulation. */
	std::optional<double>	GetInsulationThickness () const;

	/** @return Returns the number of ports. */
	uint32_t				GetPortCount () const;

	/** @param portIdx The zero based Index of the Port.
		@return Returns error if index is out of range, otherwise returns the shape of the Port of the ElementDefault.
	*/
	Result<ConnectorShape>	GetShapeOfPort (uint32_t portIdx) const;

	/** @return Returns the domain of the ElementDefault. */
	Domain					GetDomain () const;

	/** @return Returns the main GUID of the referenced Library Part. */
	API_Guid				GetObjectId () const;

	/** @brief Executes the given modifier scope in a NotUndoable command.
		@param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
		@return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


class MEPAPI_EXPORT ElementDefault::Modifier : public ACAPI::ModifierBase {
	ElementDefault& parent;

protected:
	Modifier (ElementDefault&);
	virtual ~Modifier ();

public:
	friend ElementDefault;

	/** @brief Removes the insulation.*/
	void			RemoveInsulation ();

	/** @brief Sets the thickness of insulation on the ElementDefault.
		@param insulationThickness The value to be set.
		@return Returns an error if the Element is of cable carrier domain, otherwise nothing.
	*/
	Result<void>	SetInsulationThickness (double insulationThickness);
	
	/** @brief Sets the referenced library part of the ElementDefault.
		@param libraryPartId The main GUID of the library part.
	*/
	void	SetObjectId (const API_Guid& libraryPartId);
};


template<class ModifierFunc>
Result<void> ElementDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


} // v1

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_ELEMENT_DEFAULT_HPP*/