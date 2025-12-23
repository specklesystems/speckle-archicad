#ifndef GS_ACAPI_MEP_ELEMENTBASE_HPP
#define GS_ACAPI_MEP_ELEMENTBASE_HPP


#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"
#include "MEPEnums.hpp"

#include "ACAPI/ElementBase.hpp"

#include <vector>


namespace ACAPI::MEP {

namespace Impl { class IElementBaseImpl; }


/**
 * @details It is a collection of common MEP attributes that can be handled through this parent entity.
 * @since Archicad 27
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElementBase : public ACAPI::ElementBase {
protected:
	/**
	 * @brief Constructs an ElementBase with an element base implementation.
	 * @param impl The element base implementation.
	 */
	ElementBase (std::shared_ptr<Impl::IElementBaseImpl> impl);
	~ElementBase ();

public:
	/** @return Checks if the element still exists.	*/
	bool					Exists () const;

	/** @return Returns the IDs of the element's ports.	*/
	std::vector<UniqueID>	GetPortIDs () const;

	/** @return Returns the UniqueIDs of the connected MEP elements. */
	std::vector<UniqueID>	GetDirectConnectedMEPElementIds () const;

	/** @return Returns the anchor point of the element. */
	API_Coord3D				GetAnchorPoint () const;

	/** @return Returns the orientation of the element, which is based on a direction vector and a rotation vector.	*/
	Orientation				GetOrientation () const;

	/** @return Returns the base rotation of the element in radians. */
	double					GetBaseRotation () const;

	/** @return Returns whether the element is reflected, 'true' if it is reflected, 'false' otherwise. */
	bool					GetReflected () const;

	/** @return Returns the main GUID of the referenced Library Part. */
	API_Guid				GetObjectId () const;

	/** @return Returns the referenced Library Part's size along the X axis. */
	double					GetObjectXSize () const;

	/** @return Returns the referenced Library Part's size along the Y axis. */
	double					GetObjectYSize () const;
};

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_ELEMENTBASE_HPP*/