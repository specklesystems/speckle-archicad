#ifndef	SYMB_POS_FROM_SURVEY_POINT_TO_DICT_HPP
#define	SYMB_POS_FROM_SURVEY_POINT_TO_DICT_HPP

#pragma once

#include "GDLExport.h"
#include "GDLDictionary.hpp"
#include "Matrix34.hpp"
#include "Vector3D.hpp"

namespace GDL {

class GDL_DLL_EXPORT SymbPosFromSurveyPointToDict
{
private:
	Geometry::Point3D symbPosFromSurveyPoint;

public:
	SymbPosFromSurveyPointToDict (const Geometry::Matrix34& transformToSurveyPointCoordinateSystem, const Geometry::Point3D& positionFromProjectOrigin);

	Dictionary		operator () () const;

	static Dictionary	CreateDefaultValue ();
};

}

#endif	//SYMB_POS_FROM_SURVEY_POINT_TO_DICT_HPP