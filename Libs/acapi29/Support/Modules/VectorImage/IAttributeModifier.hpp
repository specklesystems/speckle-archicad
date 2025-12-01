#ifndef IATTRIBUTEMODIFIER_HPP
#define IATTRIBUTEMODIFIER_HPP

#pragma once

#include "VectorImageExport.h"

class Sy_HotType;
class Sy_LinType;
class Sy_PolyLinType;
class Sy_ArcType;
class Sy_TextType;
class Sy_RichTextType;
class Sy_HatchType;
class HatchObject;
class Sy_SplineType;
class Sy_PixMapType;
class Sy_PointCloudType;

namespace VI {

class VI_DLL_CLASS_EXPORT IAttributeModifier
{
public:
	virtual ~IAttributeModifier ();

	virtual void Modify (Sy_HotType&		hots)								const = 0;
	virtual void Modify (Sy_LinType&		line)								const = 0;
	virtual void Modify (Sy_PolyLinType&	polyLine)							const = 0;
	virtual void Modify (Sy_ArcType&		arc)								const = 0;
	virtual void Modify (Sy_TextType&		text)								const = 0;
	virtual void Modify (Sy_RichTextType&	richText)							const = 0;
	virtual void Modify (Sy_HatchType&		hatchRef, HatchObject& hatch)		const = 0;
	virtual void Modify (Sy_SplineType&		spline)								const = 0;
	virtual void Modify (Sy_PixMapType&		pixMap)								const = 0;
	virtual void Modify (Sy_PointCloudType&	pointCloud)							const = 0;
};

}

#endif