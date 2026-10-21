// *********************************************************************************************************************
// Description:		LineElim tree
//
// Module:			Visualization
// Contact person:	LG
//
// SG compatible
// *********************************************************************************************************************

#if !defined (LINE_ELIM_TREE_HPP)
#define LINE_ELIM_TREE_HPP

#pragma once


#include "Model3D/Model3D.hpp"

MODEL3D_DLL_EXPORT
void	MODEL3D_CALL LEGetGoodNormal (const Modeler::MeshBody& body,
					  Int32 edgeIdx,
					  const COORD3* bentWallOrigin,
					  COORD3* normal1, COORD3* normal2,
					  double* margin1, double* margin2,
					  GSAttributeIndex* iumat1, GSAttributeIndex* iumat2,
					  const TRANMAT& atran);


MODEL3D_DLL_EXPORT
void	MODEL3D_CALL LEGetOptions (bool	*turnOff,
								  bool	*slabHori,
								  bool	*checkMater,
								  bool	*skipGDL);

MODEL3D_DLL_EXPORT
void	MODEL3D_CALL	LESetOptions (bool	turnOff,
								  bool	slabHori,
								  bool	checkMater,
								  bool	skipGDL);


MODEL3D_DLL_EXPORT
bool	MODEL3D_CALL	LECheckPolyFit (const Modeler::MeshBody*	tBody2,
						Int32			edgeIdx,
						const TRANMAT&	tTran2,
						bool			wallBodyJ,
						bool			wallBodyI,
						const COORD3&	bentWallOrigo2,
						double			fMargin1,
						double			fMargin2,
						double			fMargin3,
						double			fMargin4,
						GSAttributeIndex	fimat1,
						GSAttributeIndex	fimat2,
						GSAttributeIndex	fimat3,
						GSAttributeIndex	fimat4,
						const COORD3&	fvect1,
						const COORD3&	fvect2,
						const COORD3&	fvect3,
						const COORD3&	fvect4);


MODEL3D_DLL_EXPORT
GSErrCode	MODEL3D_CALL	 LineElim (GS::ProcessControl& processControl, const Modeler::Model3DViewer& viewer, Modeler::ElimDataArray& data, const GS::HashTable<UIndex, bool> *elimElems);

#endif
