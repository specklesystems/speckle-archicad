// *********************************************************************************************************************
// Description:		Inherited user data identifier in elem
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	NAT
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODEL3D_BASEUSERDATA_HPP)
#define GS_MODEL3D_BASEUSERDATA_HPP

#pragma once
#include "Model3D/Model3DExport.h"

// from GSRoot
#include "Object.hpp"

struct TRANMAT;


namespace Modeler {

	class MODEL3D_DLL_EXPORT BaseUserData : public GS::Object {
		DECLARE_CLASS_INFO
	public:
		virtual ~BaseUserData (void);

		bool					operator != (const BaseUserData& rhs)						const	{ return !operator== (rhs); }

		virtual BaseUserData*	Clone (void)												const	override = 0;
		virtual void			Print (GS::OChannel& oc)									const	override = 0;
		virtual bool			operator== (const BaseUserData& rhs)						const	= 0;
		virtual ULong			GenerateHashValue (void)									const 	= 0;
		virtual GSErrCode		QuickWrite (GS::OChannel& oc)								const	= 0;
		virtual GSErrCode		QuickRead (GS::IChannel& ic)										= 0;
		virtual void			PrintAsTestCase (GS::OChannel& oc, const char* iVarName)	const	= 0;
		virtual void			WriteXML (GS::XMLOChannel& outXML)							const	= 0;
		virtual void			ReadXML (GS::XMLIChannel& inXML)									= 0;

		virtual BaseUserData*	Clone (const TRANMAT& /*trafo*/)							const { return Clone (); }
	};

	class MODEL3D_DLL_EXPORT BodyId : public BaseUserData {
		DECLARE_DYNAMIC_CLASS_INFO (BodyId)
	private:
		Int32	val;
	public:
		BodyId () : val (0) {}
		BodyId (const Int32& v) : val (v) {}
		virtual ~BodyId ();

		Int32					GetValue (void) const	{ return val; }

		virtual BodyId*			Clone (void)												const	override { return new BodyId (GetValue ()); }
		virtual void			Print (GS::OChannel& oc)									const	override { oc << "BodyId [" << GetValue () << "]"; }
		virtual bool			operator== (const BaseUserData& rhs)						const	override;
		virtual ULong			GenerateHashValue (void)									const	override { return val; }
		virtual GSErrCode		QuickWrite (GS::OChannel& oc)								const	override;
		virtual GSErrCode		QuickRead (GS::IChannel& ic)										override;
		virtual void			PrintAsTestCase (GS::OChannel& oc, const char* iVarName)	const	override;
		virtual void			WriteXML (GS::XMLOChannel& outXML)							const	override;
		virtual void			ReadXML (GS::XMLIChannel& inXML)									override;
	};
}

#endif
