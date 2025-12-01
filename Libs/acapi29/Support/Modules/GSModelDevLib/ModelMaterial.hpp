// =============================================================================
// Description:		  Material    
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (MODELMATERIAL_HPP)
#define MODELMATERIAL_HPP

// ----------------------- Includes --------------------------------------------
#include "ModelColor.hpp"
#include "GSModelerExport.h"
#include "SharedPtr.hpp"
#include "GSUtilsDefs.h"

// ----------------------- Predeclarations -------------------------------------
namespace ModelerAPI {
	class IMaterialRelay;
	class Texture;
	class ParameterList;
	class AttributeIndex;
}

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {


class GSMODELER_DLL_EXPORT Material {
public:
	enum Type {
		General		= 0,
		Simple		= 1,
		Matte		= 2,
		Metal		= 3,
		Plastic		= 4,
		Glass		= 5,
		Glowing		= 6,
		Constant	= 7
	};

private:
	GS::SharedPtr<ModelerAPI::IMaterialRelay>	relay;  //ez marad nem const, de vigyazni kell, hogy csak masolaton dolgozzon.

public:
	Material ();
	Material (const GS::SharedPtr<ModelerAPI::IMaterialRelay>& relay);
	Material (const Material& other);
	Material (Material&& other);
	~Material ();

	Material&						operator= (const Material& other);
	Material&						operator= (Material&& other);
	bool							operator== (const Material& other) const;
	bool							operator!= (const Material& other) const	{ return !(*this == other); }
	bool							operator< (const Material& other) const;
	
	ULong							GenerateHashValue () const;
	Type							GetType () const;
	GS::UniString					GetName () const;
	Color							GetSurfaceColor () const;
	double							GetAmbientReflection () const;
	double							GetDiffuseReflection () const;
	double							GetSpecularReflection () const;
	Color							GetSpecularColor () const;
	double							GetTransparency () const;
	double							GetTransparencyAttenuation () const;
	double							GetShining () const;
	Color							GetEmissionColor () const;
	double							GetEmissionAttenuation () const;
	void							GetTextureIndex (ModelerAPI::AttributeIndex& iText) const;
	bool							HasTexture () const; 
	void							GetTextureName (char* str) const;
	GS::UniString					GetTextureName () const;
	double							GetTextureRotationAngle () const;
	void							GetFillIndex (ModelerAPI::AttributeIndex& iFill) const;
	void							GetFillColorIndex (ModelerAPI::AttributeIndex& iFillColor) const;
	void							GetTexture (Texture* texture) const;
	Int32							GetExternalReference (void) const;
	void							GetExtraParameters (ModelerAPI::ParameterList* parameters) const;

	void							SetType (Type type);
	void							SetName (char* str);
	void							SetName (const GS::UniString& name);
	void							SetSurfaceColor (Color color);
	void							SetAmbientReflection (double reflection);
	void							SetDiffuseReflection (double reflection);
	void							SetSpecularReflection (double reflection);
	void							SetSpecularColor (Color color);
	void							SetTransparency (double transparency);
	void							SetTransparencyAttenuation (double attenuation);
	void							SetShining (double shining);
	void							SetEmissionColor (Color color);
	void							SetEmissionAttenuation (double attenuation);
	void							SetTextureName (char* str);
	void							SetTextureName (const GS::UniString& name);
	void							SetTextureWidth (double widht);
	void							SetTextureHeight (double height);
	void							SetTextureRotationAngle (double angle);
	void							SetTextureStatus (short status);
	void							SetFillIndex (const ModelerAPI::AttributeIndex& index);
	void							SetFillColorIndex (short index);
	void							SetExtraParameters (ModelerAPI::ParameterList* parameters);
};


}


#endif
