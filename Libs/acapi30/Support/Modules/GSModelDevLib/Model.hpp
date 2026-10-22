// =============================================================================
// Description:		  Model    
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (MODEL_HPP)
#define MODEL_HPP


// ----------------------- Includes --------------------------------------------
#include "ModelColor.hpp"
#include "Box3DData.h"
#include "GSModelerExport.h"
#include "SharedPtr.hpp"
#include <optional>

// ----------------------- Predeclarations -------------------------------------

namespace Modeler {
	class ModStamp;
}

namespace ModelerAPI {
	class MeshBody;
	class Element;
	class Light;
	class Material;
	class ModelRelay;
	class Texture;
	class AttributeIndex;
}

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {


	class GSMODELER_DLL_EXPORT Model 
	{
		friend class ModelRelay;
	public:
		enum SpecialLightType {
			AmbientLightType = 1,
			CameraLightType = 2,
			SunLightType = 3
		};

	private:
		GS::ConstSharedPtr<ModelerAPI::ModelRelay>		relay;

	public:
		Model ();
		Model (const Model& other);
		~Model ();

		Model&								operator= (const Model& other);
		bool								operator== (const Model& other) const;
		bool								operator!= (const Model& other) const	{ return !(*this == other); }
		bool								operator< (const Model& other) const;
		
		ULong								GenerateHashValue () const;
		Box3D								GetBounds (void) const;
		Int32								GetElementCount (void) const;
		Int32								GetColorCount (void) const;
		Int32								GetMaterialCount (void) const;
		Int32								GetTextureCount (void) const;
		Int32								GetFillCount (void) const;
		Int32								GetLightCount (void) const;
		std::optional<Int32>				GetElementIndex (const GS::Guid& guid) const;
		void								GetElement (Int32 elementIndex, Element* element) const;
		void								GetColor (const ModelerAPI::AttributeIndex& colorIndex, Color* color) const;
		void								GetMaterial (const ModelerAPI::AttributeIndex& materialIndex, Material* material) const;
		void								GetTexture (const ModelerAPI::AttributeIndex& textureIndex, Texture* texture) const;
		void								GetTexture (const char* textureFileName, Texture* texture) const;
		void								GetTexture (const GS::UniString& textureFileName, Texture* texture) const;
		bool								IsTextureUsed (const AttributeIndex& textureIndex) const;
		void								GetLight (Int32 lightIndex, Light* light) const;
		void								GetLight (SpecialLightType	type, Light* light) const;
		GS::Guid							GetGuid (void) const;
	};


} // namespace ModelerAPI


#endif
