// *********************************************************************************************************************
// Description:		FMAT record
//
// Module:			
// Namespace:
// Contact person:	AACS
//
// SG compatible
// *********************************************************************************************************************

#if !defined (FMAT_HPP)
#define FMAT_HPP

#pragma once
//From GSUtils: 
#include	"GSUtilsDefs.h"

struct FMAT {
	STATW		status;
	ADB::AttributeIndex	iufil;
	RGBfloat	f_surfaceRGB;		/* Surface color						*/
	RGBfloat	f_ambientRGB;		/* Ambience reflection					*/
	float		f_diffusePc;		/* Diffuse reflection					*/
	float		f_specularPc;		/* Specular reflection					*/
	float		f_transpPc;			/* Transparency							*/
	float		f_shine;			/* Shininess							*/
	float		f_transpAtt;		/* Transparency attenuation				*/
	RGBfloat	f_specularRGB;		/* Specular color						*/
	RGBfloat	f_emissionRGB;		/* Emission color						*/
	float		f_emissionAtt;		/* Emission attenuation					*/
	Int32		irtxt;
	float		cosa;
	float		sina;

	FMAT (void) :
	status (0),
		iufil (ADB::InvalidAttributeIndex),
		f_diffusePc (0.0f),
		f_specularPc (0.0f),
		f_transpPc (0.0f),
		f_shine (0.0f),
		f_transpAtt (0.0f),
		f_emissionAtt (0.0f),
		irtxt (0),
		cosa (0.0f),
		sina (0.0f)
	{
		f_surfaceRGB.f_red = f_surfaceRGB.f_green = f_surfaceRGB.f_blue = 0.0f;
		f_ambientRGB.f_red = f_ambientRGB.f_green = f_ambientRGB.f_blue = 0.0f;
		f_specularRGB.f_red = f_specularRGB.f_green = f_specularRGB.f_blue = 0.0f;
		f_emissionRGB.f_red = f_emissionRGB.f_green = f_emissionRGB.f_blue = 0.0f;
	}
};			/* 88 */


#endif
