// *********************************************************************************************************************
// Description:		UFIL is the description of a fill attribute
//
// Module:			GSModeler
// Namespace:
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (UFIL_HPP)
#define UFIL_HPP

// from GSRoot
#include	"Array.hpp"
#include	"CH.hpp"
#include	"Owner.hpp"
#include	"Variant.hpp"

// from GSUtils
#include	"GSUtilsDefs.h"

// from Model3D
#include	"Model3D/Model3DExport.h"
#include	"GDLAttributes.h"

//from Pattern
#include	"FillData.hpp"

// from CADInfrastructureBase
#include	"ADBAttributeIndex.hpp"

struct OmittedUFILParts {
	Int32		ffide, nfide;
};

typedef GS::Variant<ADB::AttributeIndex, Int32> UFilGenFrom;

class MODEL3D_CPP_DLL_EXPORT UFIL {
	static GS::ClassInfo classInfo;

	static const UInt32	NameSize_old = 32;

private:	
	GS::UniString					cname;
	STATW							status;
	UFilGenFrom						genfrom;		/* > 0: AC_FILL ; = 0: GDL	*/
	GX::Pattern::FillData			fillData; 

public:
	UFIL ();

	const GS::UniString&			GetName () const		{ return cname; }
	STATW							GetStatus () const		{ return status; }
	const GX::Pattern::FillData*	GetFillData () const	{ return &fillData; }
	void							GetFillDef (GS::Owner<FillRecord>& filldefRecord) const;
	UInt32							GetFillDefSize () const;

	bool							IsVBFill () const { return genfrom.Is<ADB::AttributeIndex> (); }
	bool							IsGDLFill () const { return genfrom.Is<Int32> () && genfrom.Get<Int32> () == 0; }

	const ADB::AttributeIndex&		GetVBFillIndex () const { return genfrom.Get<ADB::AttributeIndex> (); }
	Int32							GetGDLFillIndex () const { return genfrom.Get<Int32> (); }
	const UFilGenFrom&				GetGenerationMode () const { return genfrom; }

	void							SetVBFillIndex (const ADB::AttributeIndex& index);
	void							SetGDLGenerated ();

	void							SetName (const GS::UniString& cname)	{ this->cname = cname; }
	void							SetStatus (STATW status)	{ this->status = status; }
	void							SetFillData (const GX::Pattern::FillData* fillDataInit);
	void							SetFillDef (const FillRecord* fillDefInit);

	GSErrCode						Read  (GS::IChannel& ic);
	GSErrCode						Write (GS::OChannel& oc) const;

	void							WriteXML (GS::XMLOChannel& outXML) const;
	void							ReadXML	 (GS::XMLIChannel& inXML);

	// Read for old version-frame-less writes.
	GSErrCode						DeprecatedRead_NoFillDescriptor  (GS::IChannel& ic, Int32 msizeVersion, OmittedUFILParts& omittedUFILParts);

private:
	GSErrCode						ReadVersion2		(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode						ReadVersion3		(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode						ReadVersion4		(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode						WriteVersion4		(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode						ReadVersion5		(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode						WriteVersion5		(GS::OChannel& oc, const GS::OutputFrame& frame) const;
};

#endif
