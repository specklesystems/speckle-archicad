// *********************************************************************************************************************
// Description:		Ptr to Spatial information of one or more nurbs
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_NURBSBODY_PTR_HPP)
#define GS_MODELER_NURBSBODY_PTR_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"SharedPtr.hpp"

namespace Modeler {
	class 	NurbsBody;

	typedef GS::ConstSharedPtr<NurbsBody>		ConstNurbsBodyPtr;
	typedef GS::SharedPtr<NurbsBody>			NurbsBodyPtr; 
}	// namespace Modeler


#endif	// GS_MODELER_NURBSBODY_PTR_HPP
