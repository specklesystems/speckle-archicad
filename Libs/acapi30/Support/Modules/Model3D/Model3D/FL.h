/****************************************************************************/
/*																			*/
/*							PROTOTYPES FOR FL... ROUTINES					*/
/*																			*/
/****************************************************************************/

#ifndef	_FL_H_
#define	_FL_H_

#pragma once

#include	"Model3D/Model3DPrivExp.h"

#include	"Array.hpp"
#include	"Model3D/ModelerAttributes.hpp"
#include	"SharedPtr.hpp"
#include	"Model3D/model.h"

namespace GS {
	class IChannel;
	class OChannel;
}

namespace Modeler {
	class MeshBody;
	class Elem;
	class CandidateMeshBody;
	class Model3DViewer;
	typedef GS::SharedPtr<CandidateMeshBody>		CandidateMeshBodyPtr;
}

class LGHT;

/*================================	TYPES		============================*/


/*================================	PROTOTYPES	============================*/

MODEL3D_PRIVATE_EXPORT
void MOD3D_PRIV	FLWriteModel (
						GS::OChannel&						oChannel,
						const Modeler::Model3DViewer&		modelViewer,
						const Modeler::Attributes::Viewer&	attrViewer);	// throws exception


MODEL3D_DLL_EXPORT
void	MODEL3D_CALL FLReadModel (
						GS::IChannel&								iChannel,
						GS::Array<Modeler::CandidateMeshBodyPtr>&		bodies,
						GS::Array<LGHT>&							lights,
						GS::Array<UMAT>&							uumat,
						GS::Array<RTXT>&							urtxt,
						GS::Array<UFIL>&							uufil,
						GS::PlatformSign							inplatform,
						short										matmode,
						short										gmode,
						bool										withBkg,
						MSIZ&										msiz);


MODEL3D_PRIVATE_EXPORT
void MOD3D_PRIV FLUpdateAttributeIndices (
						GS::Array<Modeler::CandidateMeshBodyPtr>&	bodies,
						const MSIZ*								msiz,
						short									color,
						const Int32*							iimat,
						const Int32*							iitxt,
						Int32									omrtxt //original texture count
						);
#endif
