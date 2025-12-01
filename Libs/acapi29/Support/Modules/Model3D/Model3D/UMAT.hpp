// *********************************************************************************************************************
// Description:		UMAT record with some fundamental methods
//
// Module:			GDL
// Namespace:
// Contact person:	BA, FE, FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_GDL_UMAT_HPP)
#define GS_GDL_UMAT_HPP

#pragma once

// from GSUtils
#include	"GSPix.h"	// GS_RGBColor

// from GSRoot
#include	"Variant.hpp"

// from CADInfrastructureBase
#include	"ADBAttributeIndex.hpp"

// from Model3D
#include	"Model3D/Model3DExport.h"
#include	"Model3D/PropList.hpp"

struct UMAT_41;
struct UMAT_455;

typedef GS::Variant<ADB::AttributeIndex, Int32> UMatGenFrom;

class MODEL3D_CPP_DLL_EXPORT UMAT {
	static GS::ClassInfo classInfo;

private:
	GS::UniString		m_name;
	short				m_mtype;			/* material type					[0..7]		*/	\
	GS_RGBColor			m_surfaceRGB;		/* surface color								*/	\
	short				m_ambientPc;		/* ambient reflection				[0..100]	*/	\
	short				m_diffusePc;		/* diffuse reflection				[0..100]	*/	\
	short				m_specularPc;		/* specular reflection				[0..100]	*/	\
	short				m_transpPc;		/* transparency						[0..100]	*/	\
	short				m_shine;			/* shininess * 100					[0..10000]	*/	\
	short				m_transpAtt;		/* transparency attenuation * 100	[0..400]	*/	\
	GS_RGBColor			m_specularRGB;	/* specular color								*/	\
	GS_RGBColor			m_emissionRGB;	/* emission color								*/	\
	short				m_emissionAtt;	/* emission attenuation * 100		[0..65535]	*/
	UMatGenFrom			m_genfrom;		/* > 0: AC_MATER ; < 0: COLOR ; = 0: GDL	*/
	Int32				m_iufil;
	short				m_fillCol;		/* Color number of defined 3D hatch
													(0 <= Use BODY color)	*/
	Int32					m_irtxt;			/* MSIZE_VERSION > 4009	*/
	float					m_cosa;
	float					m_sina;
	Modeler::PropertyList	m_props;
	Int32					m_checkSum;
	Int32					m_dummy3;
	Int32					m_dummy4;

	short					m_genfrom_dummy;
	short					m_iufil_dummy;

public:
	UMAT ();
	~UMAT ();

	GSErrCode	Read  (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;

private:
	GSErrCode	ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode	WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode	ReadVersion3 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode	WriteVersion3 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

public:
	// A read function that can process the old (MSIZE_VERSION < 4042) version-frame-less writes.
	GSErrCode	DeprecatedRead  (GS::IChannel& ic, Int32 msizeVersion);

	void		WriteXML (GS::XMLOChannel& outXML) const;
	void		ReadXML	 (GS::XMLIChannel& inXML);

	void		ConvertFromUmat41 (const UMAT_41* aumat41);
	void		ConvertFromUmat455 (const UMAT_455* aumat455);

	const GS::UniString&	GetName () const { return m_name; }
	short					GetType () const { return m_mtype; }
	const GS_RGBColor&		GetSurfaceColor () const { return m_surfaceRGB; }
	short					GetAmbientReflection () const { return m_ambientPc; }
	short					GetDiffuseReflection () const { return m_diffusePc; }
	short					GetSpecularReflection () const { return m_specularPc; }
	const GS_RGBColor&		GetSpecularColor () const { return m_specularRGB; }
	short					GetTransparency () const { return m_transpPc; }
	short					GetTransparencyAttenuation () const { return m_transpAtt; }
	short					GetShining () const { return m_shine; }
	const GS_RGBColor&		GetEmissionColor () const { return m_emissionRGB; }
	short					GetEmissionAttenuation () const { return m_emissionAtt; }
	Int32					GetTextureIdx () const	{ return m_irtxt;  }
	void					GetTextureRotationAngle (double* cosa, double* sina) const { DBASSERT (cosa != nullptr && sina != nullptr); *cosa = m_cosa; *sina = m_sina; }
	double					GetTextureRotationCosA () const { return m_cosa; }
	double					GetTextureRotationSinA () const { return m_sina; }
	Int32					GetFillIdx () const { return m_iufil; }
	short					GetFillColorIdx () const { return m_fillCol; }
	
	bool					IsVBMaterial () const { return m_genfrom.Is<ADB::AttributeIndex> (); }
	bool					IsGDLMaterial () const { return m_genfrom.Is<Int32> () && m_genfrom.Get<Int32> () == 0; }
	bool					IsColorMaterial () const { return m_genfrom.Is<Int32> () && m_genfrom.Get<Int32> () < 0; }

	const ADB::AttributeIndex& GetVBMaterialIndex () const { return m_genfrom.Get<ADB::AttributeIndex> (); }
	Int32					   GetColorOrGDLMaterialIndex () const { return m_genfrom.Get<Int32> (); }
	const UMatGenFrom&		   GetGenerationMode () const { return m_genfrom; }

	void					SetVBMaterialIndex (const ADB::AttributeIndex& index);
	void					SetColorIndex (Int32 index);
	void					SetGDLGenerated ();

	void					QuickWriteIndex (GS::OChannel& oc) const;
	void					QuickReadIndex (GS::IChannel& ic);

	const Modeler::PropertyList& GetExtraParameters () const { return m_props; }
	Int32		GetExtraParametersChecksum () const { return m_checkSum; }

	void		SetName (const GS::UniString& name);
	void		SetType (short mtype) { m_mtype = mtype; }
	void		SetSurfaceColor (const GS_RGBColor& color) { m_surfaceRGB = color; }
	void		SetAmbientReflection (short newValue) { m_ambientPc = newValue; }
	void		SetDiffuseReflection (short newValue) { m_diffusePc = newValue; }
	void		SetSpecularReflection (short newValue) { m_specularPc = newValue; }
	void		SetSpecularColor (const GS_RGBColor& newColor) { m_specularRGB = newColor; }
	void		SetTransparency (short newValue) { m_transpPc = newValue; }
	void		SetTransparencyAttenuation (short newValue) { m_transpAtt = newValue; }
	void		SetShining (short newValue) { m_shine = newValue; }
	void		SetEmissionColor (const GS_RGBColor& newColor) { m_emissionRGB = newColor; }
	void		SetEmissionAttenuation (short newValue) { m_emissionAtt = newValue; }
	void		SetTextureIdx (Int32 irtxt)	{ m_irtxt = irtxt; }
	void		SetTextureRotationAngle (double cosa, double sina) { m_cosa = static_cast<float> (cosa); m_sina = static_cast<float> (sina); }
	void		SetupTexture (Int32 irtxt, double angleDEG); 
	void		SetFillIdx (Int32 newIdx) { m_iufil = newIdx; }
	void		SetFillColorIdx (short newIdx) { m_fillCol = newIdx; }

	void		SetExtraParameters (const Modeler::PropertyList& parameters);
	void		ClearExtraParameters ();

	void		Setup (	 const GS::Variant<ADB::AttributeIndex, Int32>& genfrom,
						 const char* name,
						 short mtype /*materialType*/,
						 const GS_RGBColor&	surfaceRGB, /*surface color*/
						 GSAttributeIndex iufil,
						 short fillCol);

};


#endif
