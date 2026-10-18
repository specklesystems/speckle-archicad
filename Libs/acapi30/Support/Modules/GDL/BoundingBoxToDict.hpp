#ifndef	BOUNDING_BOX_TO_DICT_HPP
#define	BOUNDING_BOX_TO_DICT_HPP

#pragma once

#include "GDLExport.h"
#include "GDLDictionary.hpp"

class Box2DData;

namespace GDL {

class GDL_DLL_EXPORT BoundingBoxToDict
{
private:
	const Box2DData&	boundingBox;

public:
	BoundingBoxToDict (const Box2DData& openingPolygon);

	Dictionary		operator () () const;
};

}

#endif	//BOUNDING_BOX_TO_DICT_HPP