// =============================================================================
// Description:		  Polygon    
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (POLYGON_HPP)
#define POLYGON_HPP

// ----------------------- Includes --------------------------------------------
#include "GSModelerExport.h"
#include "SharedPtr.hpp"
#include "CoordinateSystem.hpp"

// ----------------------- Predeclarations -------------------------------------
namespace ModelerAPI {
	class Model;
	class Material; 
	class Texture; 
	class ConvexPolygon;
	class PolygonRelay;
	class Vertex;
	class Vector;
	class TextureCoordinate;
	class Transformation;
	class AttributeIndex;
}

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {


class GSMODELER_DLL_EXPORT Polygon {
	friend class PolygonRelay;

private:
	GS::SharedPtr<ModelerAPI::PolygonRelay>		relay;
	
public:
	Polygon ();
	Polygon (const ModelerAPI::Polygon& other);
	~Polygon ();

	ModelerAPI::Polygon&				operator= (const ModelerAPI::Polygon& other);

	bool								IsInvisible (void) const;
	bool								IsVisibleIfContour (void) const;
	bool								IsComplex (void) const;
	bool								IsGravity (void) const;
	Int32								GetEdgeCount (void) const;
	Int32								GetNormalVectorIndex (void) const;


	void								GetMaterial (ModelerAPI::Material* material) const;
	void								GetMaterialIndex (ModelerAPI::AttributeIndex& iMat) const;

	void								GetMaterialTexture (ModelerAPI::Texture* texture) const;
	void								GetPolygonTexture (ModelerAPI::Texture* texture) const;

	void								GetMaterialTextureIndex (ModelerAPI::AttributeIndex& iText) const;
	void								GetPolygonTextureIndex (ModelerAPI::AttributeIndex& iText) const;
	bool								HasMaterialTexture () const;
	bool								HasPolygonTexture () const;

	Int32								GetEdgeIndex (Int32 edgeIndex) const;
	Int32								GetVertexIndex (Int32 vertexIndex) const;
	Int32								GetConvexPolygonCount (void) const;
	ModelerAPI::Vector					GetNormalVectorByVertex (Int32 polygonVertexIndex, const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;
	void								GetConvexPolygon (Int32 polygonIndex, ModelerAPI::ConvexPolygon* polygon) const;
	void								GetTextureCoordinate (const ModelerAPI::Vertex* positionInWorldCS, ModelerAPI::TextureCoordinate* textureCoordinate) const;
	Int32								GetPolygonId () const;
};


} // namespace ModelerAPI


#endif
