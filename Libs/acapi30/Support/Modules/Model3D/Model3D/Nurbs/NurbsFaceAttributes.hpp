#if !defined(NURBSFACEATTRIBUTES_HPP)
#define NURBSFACEATTRIBUTES_HPP

#pragma once

#include "Model3D/Model3DExport.h"

// from GDL
#include "GDLWrapping.hpp"

// from Modeler
#include "Model3D/TextureCoordSys.hpp"
#include "Model3D/ModelerAttributes.hpp"

namespace GS {
	class XMLIChannel;
	class XMLOChannel;
}


namespace Modeler {
struct ModelILookup;
struct ModelOLookup;
class IAttributeReader;

class MODEL3D_DLL_EXPORT NurbsFaceAttributes {
public:
	//typedef short Material;
	typedef short Pen;
private:
	GSAttributeIndex	material;
	Pen					segmentationPen;	// pen index for segmentation edges (created inside the face)
	Wrapping			textureWrapping;	// valid wrappings are the same as on MeshBrep polygons except UV mappings
											// see TextureCoord.cpp: @CheckPolygonTextureWrapping
	TextureCoordSys		textureCoordSys;	// should be valid if @textureWrapping is not W_FROMBODY

public:
	NurbsFaceAttributes ();					// material member variable will be invalid!!!

	NurbsFaceAttributes (GSAttributeIndex		materialIn,
						 Pen					segmentationPenIn,
						 const Wrapping&		textureWrappingIn,
						 const TextureCoordSys&	textureCoordSysIn);

	NurbsFaceAttributes (GS::XMLIChannel& inXML, const char* tagName) { ReadXML (inXML, tagName); }

	GSAttributeIndex		GetMaterial					()	const	{ return material;			}
	short					GetSegmentationPen			()	const	{ return segmentationPen;	}
	const Wrapping&			GetTextureWrapping			()	const	{ return textureWrapping;	}
	const TextureCoordSys&	GetTextureCoordinateSystem	()	const	{ return textureCoordSys;	}
	bool					HasTextureCoordinateSystem	()	const;

	void					SetMaterialIndex (GSAttributeIndex mat)			{ material = mat; }
	void					SetSegmentationPen (short pen)					{ segmentationPen = pen; }
	void					SetTextureWrapping (const Wrapping& wrapping)	{ textureWrapping = wrapping; }
	void					TransformTextureCoordinateSystem (const TRANMAT& tran);

	bool Equals (const NurbsFaceAttributes& other, double eps) const {
		return	material == other.material &&
				segmentationPen == other.segmentationPen &&
				textureWrapping == other.textureWrapping &&
				AreTextureCoordSysEqual (textureCoordSys, other.textureCoordSys, eps);
	}

	void	Read		(GS::IChannel& ic);										// no version, no check
	void	QuickRead	(GS::IChannel& ic,
						ModelILookup& lookup,
						Modeler::Attributes::Modifier* attrModifier,
						const Modeler::IAttributeReader* attReader);			// no version, no check
	void	Write		(GS::OChannel& oc) const;								// no version, no check
	void	QuickWrite	(GS::OChannel& oc,
						ModelOLookup& lookup,
						const Modeler::Attributes::Viewer* attrViewer) const;	// no version, no check

	void	WriteXML (GS::XMLOChannel& outXML, const char* tagName)	const;
	void	ReadXML (GS::XMLIChannel& inXML, const char* tagName);
};

}		// namespace Modeler

#endif	// NURBSFACEATTRIBUTES_HPP
