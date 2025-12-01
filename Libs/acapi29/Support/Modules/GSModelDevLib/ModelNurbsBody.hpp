#ifndef ModelNurbsBody_h__
#define ModelNurbsBody_h__

#pragma once

#include "NurbsAttributes.hpp"
#include "Interval.hpp"
#include "ModelNurbsVertex.hpp"
#include "ModelNurbsEdge.hpp"
#include "ModelNurbsTrim.hpp"
#include "ModelNurbsLoop.hpp"
#include "ModelNurbsFace.hpp"
#include "ModelNurbsShell.hpp"
#include "ModelNurbsLump.hpp"
#include "ModelMeshBody.hpp"
#include "CoordinateSystem.hpp"

#include "GSUtilsDefs.h"
#include "GSRoot.hpp"
#include "SharedPtr.hpp"

class Box3D;
namespace Geometry
{
class NurbsCurve2D;
class NurbsCurve3D;
class NurbsSurface;
} // namespace Geometry

namespace ModelerAPI
{
class NurbsBodyRelay;
} // namespace ModelerAPI

namespace ModelerAPI
{
	class NurbsBodyRelay;

class GSMODELER_DLL_EXPORT NurbsBody
{
	friend class ModelerAPI::NurbsBodyRelay;
private:
	GS::ConstSharedPtr<ModelerAPI::NurbsBodyRelay> relay;
public:
	NurbsBody ();
	NurbsBody (const ModelerAPI::NurbsBody& other);
	~NurbsBody();

	Box3D							GetBounds		(const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World)		const;
	ModelerAPI::NurbsBody&			operator=		(const ModelerAPI::NurbsBody& other);

	ModelerAPI::AttributeIndex		GetEdgePenIdx	()				const;
	ModelerAPI::Color				GetEdgePen		()				const;
	ModelerAPI::AttributeIndex		GetMaterialIdx	()				const;
	ModelerAPI::Material			GetMaterial		()				const;

	bool							AlwaysCastsShadow	()			const;
	bool							NeverCastsShadow()				const;
	bool							DoesNotReceiveShadow()			const;
	Interval						GetSmoothness	()				const;

	TextureCoordinateSystem			GetTextureCoordSys	()			const;

	UInt32							GetVertexCount	()				const;
	NurbsVertex						GetVertex		(UInt32 index, const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World)	const;
	UInt32							GetEdgeCount	()				const;
	NurbsEdge						GetEdge			(UInt32 index, const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World)	const;
	UInt32							GetTrimCount	()				const;
	NurbsTrim						GetTrim			(UInt32 index)	const;
	UInt32							GetLoopCount	()				const;
	NurbsLoop						GetLoop			(UInt32 index)	const;
	UInt32							GetFaceCount	()				const;
	NurbsFace						GetFace			(UInt32 index, const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World)	const;
	UInt32							GetShellCount	()				const;
	NurbsShell						GetShell		(UInt32 index)	const;
	UInt32							GetLumpCount	()				const;
	NurbsLump						GetLump			(UInt32 index)	const;
	UInt32							GetCurve2DCount	()				const;
	Geometry::NurbsCurve2D			GetCurve2D		(UInt32 index)	const;
	UInt32							GetCurve3DCount	()				const;
	Geometry::NurbsCurve3D			GetCurve3D		(UInt32 index, const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World)	const;
	UInt32							GetSurfaceCount	()				const;
	Geometry::NurbsSurface			GetSurface		(UInt32 index, const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World)	const;

	NurbsVertexAttributes		GetVertexAttributes	(UIndex index)	const;
	NurbsEdgeAttributes			GetEdgeAttributes	(UIndex index)	const;
	NurbsFaceAttributes			GetFaceAttributes	(UIndex index)	const;
};

} // namespace ModelerAPI
#endif // ModelNurbsBody_h__