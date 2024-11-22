// =============================================================================
// Description:		  MeshBody    
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (MODELMESHBODY_HPP)
#define MODELMESHBODY_HPP


// ----------------------- Includes --------------------------------------------
#include "GSModelerExport.h"
#include "Vertex.hpp"
#include "ModelVector.hpp"
#include "Box3DData.h"
#include "Polygon.hpp"
#include "SharedPtr.hpp"
#include "CoordinateSystem.hpp"

// ----------------------- Predeclarations -------------------------------------

namespace ModelerAPI {
	class Vertex;
	class Vector;
	class Polygon;
	class MeshBodyRelay;
	class Edge;
	class Color;
	class Texture;
	struct TextureCoordinateSystem;
}


// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {

class GSMODELER_DLL_EXPORT  MeshBody {
	friend class ModelerAPI::MeshBodyRelay;
	
private:
	GS::ConstSharedPtr<ModelerAPI::MeshBodyRelay>	relay;

public:
	MeshBody ();
	MeshBody (const MeshBody& other);
	~MeshBody ();

	ModelerAPI::MeshBody&			operator= (const MeshBody& other);

	bool							IsWireBody (void) const;
	bool							IsSurfaceBody (void) const;
	bool							IsSolidBody (void) const;
	bool							IsClosed (void) const;
	bool							IsVisibleIfContour (void) const;
	bool							HasSharpEdge (void) const;
	bool							AlwaysCastsShadow (void) const;
	bool							NeverCastsShadow (void) const;
	bool							DoesNotReceiveShadow (void) const;

	Box3D							GetBounds (const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;
	Int32							GetVertexCount (void) const;
	Int32							GetEdgeCount (void) const;
	Int32							GetPolygonCount (void) const;
	bool							HasColor () const;
	void							GetColor(ModelerAPI::Color* color) const;
	void							GetColorIndex (ModelerAPI::AttributeIndex& iCol) const;
	void							GetMaterial (ModelerAPI::Material *material) const;
	void							GetMaterialIndex (ModelerAPI::AttributeIndex& iMat) const;
	void							GetTexture (ModelerAPI::Texture *texture) const;
	void							GetTextureIndex (ModelerAPI::AttributeIndex& iTex) const;
	Int32							GetPolygonVectorCount (void) const;
	void							GetVertex (Int32 vertexIndex, ModelerAPI::Vertex* vertex, const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;
	bool							GetVertexHardFlag (Int32 vertexIndex) const;
	void							GetEdge (Int32 edgeIndex, ModelerAPI::Edge* edge) const;
	void							GetPolygon (Int32 polygonIndex, ModelerAPI::Polygon* polygon) const;
	void							GetVector (Int32 bodyVectorIndex, ModelerAPI::Vector* vector, const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;

	const TextureCoordinateSystem*	GetTextureCoordinateSystem (void) const;
};


} // namespace ModelerAPI


#endif
