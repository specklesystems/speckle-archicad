// *****************************************************************************
// MPI Add-On interface types
// GSUtils, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MPIINTERFACETYPES_HPP)
#define MPIINTERFACETYPES_HPP

// ----------------------- Includes --------------------------------------------

#include "MPIInterfaceBaseTypes.hpp"


// ----------------------- Types -----------------------------------------------

namespace MPI {

typedef void* MPI_ADD_ON_CALL GetInterfaceFunc (Int32 type, Int32 version);

enum {
	ModelInterfaceType			= 101,
	ElementInterfaceType		= 102,
	BodyInterfaceType			= 103,
	EdgeInterfaceType			= 104,
	PolygonInterfaceType		= 105,
	ConvexPolygonInterfaceType	= 106,
	MaterialInterfaceType		= 107,
	TextureInterfaceType		= 108,
	LightInterfaceType			= 109,
	ParameterListInterfaceType	= 110,
	ParameterInterfaceType		= 111,
	ArrayParameterInterfaceType	= 112,

	RenderingInterfaceType			= 201,
	ModelViewInterfaceType			= 202,
	MaterialDialogInterfaceType		= 203,
	AddOnManagerInterfaceType		= 204,
	RenderingDialogInterfaceType	= 205,
	PixelMapCodecType				= 206,
	ProtectionInfoInterfaceType		= 207,

	CameraInterfaceType				= 301,
	GSPixelMapInterfaceType			= 302,
	ProcessControlInterfaceType		= 303,
	RenderingSettingsInterfaceType	= 304,
	ModelViewSettingsInterfaceType	= 305,
	LibraryAccessInterfaceType		= 306
};

} // namespace MPI

#endif
