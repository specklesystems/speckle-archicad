// *********************************************************************************************************************
// VBUtils coord limitations
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	NN
//
// *********************************************************************************************************************

#if !defined (VB_COORD_LIMIT_H)
#define VB_COORD_LIMIT_H

#pragma once

// from VBUtils
#include "VBUtilsExport.hpp"

// from Geometry
#include "Vector3D.hpp"

class Box3D;

namespace VBUtil {

double	VBUTILS_DLL_EXPORT GetMaxCoordValue		();
double	VBUTILS_DLL_EXPORT GetMaxZCoordValue	();
void	VBUTILS_DLL_EXPORT SetDoubleInvalid		(double& d);

bool	VBUTILS_DLL_EXPORT CheckDouble		(const double d);
bool	VBUTILS_DLL_EXPORT CheckZValue		(const double z);

bool	VBUTILS_DLL_EXPORT CheckCoord		(const Coord&	coord);
bool	VBUTILS_DLL_EXPORT CheckCoord3D		(const Coord3D& coord);

bool	VBUTILS_DLL_EXPORT CheckBox3D		(const Box3D& box);

void	VBUTILS_DLL_EXPORT CorrigateBox3D	(const Box3D& inBox, Box3D& outBox);
void	VBUTILS_DLL_EXPORT CorrigateBox3D	(Box3D& box);

void	VBUTILS_DLL_EXPORT UnionBox3D		(const Box3D& inBox1, const Box3D& inBox2, Box3D& outBox);
void	VBUTILS_DLL_EXPORT InsetBox3D		(Box3D& box, const double dx, const double dy, const double dz);


} // namespace VBUtil

#endif
