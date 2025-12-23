#ifndef NurbsAttributes_h__
#define NurbsAttributes_h__

#pragma once

#include "ModelMeshBody.hpp"
#include "ModelVector.hpp"
#include "TextureCoordinate.hpp"

#include "GSUtilsDefs.h"


namespace ModelerAPI
{

struct NurbsVertexAttributes {
public:
	enum class Hardness : GS::UChar {
		Soft,
		Hard	// vertex defines a break in shading
	};


	Hardness hardness;
};

struct NurbsEdgeAttributes {
public:
	using Color = short;
	enum class Visibility : GS::UChar { Visible, Invisible, VisibleIfContour };
	enum class Smoothness : GS::UChar { Sharp, Smooth };


	Visibility	visibility : 2;
	Smoothness	smoothness : 1;
	Color	color;
};


struct NurbsFaceAttributes {
public:
	//using Material = short;
	using Pen = short;

	GSAttributeIndex		material;
	Pen						segmentationPen;	// pen index for segmentation edges (created inside the face)
	TextureCoordinateSystem	textureCoordSys;	// should be valid if @textureWrapping is not W_FROMBODY
};

struct DirectedFaceIndex {
	UInt32	face;
	bool	reversed;
};

struct DirectedTrimIndex {
	UInt32	trim;
	bool	reversed;
};

} // namespace ModelerAPI
#endif // NurbsAttributes_h__