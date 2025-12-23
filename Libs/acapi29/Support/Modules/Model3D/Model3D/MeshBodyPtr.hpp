// *********************************************************************************************************************
// Description:		Ptr to Spatial information of one or more volumes
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_MESHBODY_PTR_HPP)
#define GS_MODELER_MESHBODY_PTR_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"SharedPtr.hpp"

namespace Modeler {
	class 	MeshBody;

	typedef GS::ConstSharedPtr<MeshBody>		ConstMeshBodyPtr;
	typedef GS::SharedPtr<MeshBody>				MeshBodyPtr;

}	// namespace Modeler


#endif
