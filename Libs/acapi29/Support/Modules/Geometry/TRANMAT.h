#if !defined (TRANMAT_H)
#define TRANMAT_H

#pragma once

/*================================	CONSTANTS	============================*/

#define	TR_IDENT		0x0001
#define	TR_DET_1		0x0002
#define	TR_SINGULAR		0x0004
#define	TR_MIRROR		0x0040

#define	TR_TRANSL_ONLY	0x0008
#define	TR_SCALE_ONLY	0x0010
#define	TR_ROTATE_ONLY	0x0020

#define	TR_TRANSL_INCL	0x0080
#define	TR_SCALE_INCL	0x0100

#define	TR_UNDECOMPOSED	0x1000

#include "Matrix34.hpp"
#include "TMB.h"
#include "Matrix3.hpp"
#include "GeometricDefinitions.h"
#include "Definitions.hpp"
#include "ObjectState.hpp"
#include "Channel.hpp"

struct GEOMETRY_DLL_EXPORT TRANMAT {
private:
	enum IdentitySelector {
		IdentityMatrixSelector
	};

	enum TranslationSelector {
		TranslationMatrixSelector
	};

	enum ScaleSelector {
		ScaleMatrixSelector
	};

	constexpr TRANMAT (IdentitySelector);
	constexpr TRANMAT (TranslationSelector, double x, double y, double z);
	constexpr TRANMAT (ScaleSelector, double x, double y, double z);

public:
	short	status;
	short	dummy1;
	short	dummy2;
	short	dummy3;
	Geometry::Matrix34 tmx;

public:
	constexpr TRANMAT ();
	inline explicit TRANMAT (const Geometry::Matrix34& mat);

	static constexpr	TRANMAT		CreateIdentity		();
 	static constexpr	TRANMAT		CreateTranslation	(double x, double y, double z);
	static inline		TRANMAT		CreateRotation		(const UnitVector_3D& axis, double angle);
 	static inline		TRANMAT		CreateRotationX		(double angle);
 	static inline		TRANMAT		CreateRotationY		(double angle);
 	static inline		TRANMAT		CreateRotationZ		(double angle);
 	static constexpr	TRANMAT		CreateScaling		(double x, double y, double z);

 	void			FillStatus ();
	void			FillStatus2D ();

	inline const Geometry::Matrix34&	GetMatrix	() const { return tmx; }
	inline void							SetMatrix	(const Geometry::Matrix34& other);

	inline Vector3D						GetOffset3D () const { return tmx.GetOffsetVector3d (); }
	inline void							SetOffset3D	(const Vector3D& vec); // sets TR_TRANSL_INCL status

	inline bool			IsIdentity			() const;
	inline bool			IsSingular			() const;
	inline bool			IsTranslationOnly	() const;
	inline bool			IsRotationOnly		() const;
	inline bool			IsScalingOnly		() const;
	inline bool			HasMirror			() const;
	inline bool			HasTranslation		() const;
	inline bool			HasScaling			() const;

	inline GSErrCode		Read	(GS::IChannel& ic);
	inline GSErrCode		Write	(GS::OChannel& oc) const;

	GSErrCode Store (GS::ObjectState& os) const;
	GSErrCode Restore (const GS::ObjectState& os);
};



GEOMETRY_DLL_EXPORT bool operator== (const TRANMAT& lhs, const TRANMAT& rhs);

constexpr TRANMAT::TRANMAT () :
	status (0),
	dummy1 (0),
	dummy2 (0),
	dummy3 (0),
	tmx ()
{
}


inline TRANMAT::TRANMAT (const Geometry::Matrix34& mat) :
	status (0),
	dummy1 (0),
	dummy2 (0),
	dummy3 (0),
	tmx (mat)
{
	FillStatus ();
}


constexpr TRANMAT::TRANMAT (IdentitySelector) :
	/* Laci: TRANSL miert kellett itt ??   vv940404 */
	status (TR_IDENT | TR_DET_1 | TR_TRANSL_ONLY | TR_TRANSL_INCL),
	dummy1 (0),
	dummy2 (0),
	dummy3 (0),
	tmx (Geometry::Matrix34::CreateIdentity ())
{
}


constexpr TRANMAT::TRANMAT (TranslationSelector, double x, double y, double z) :
	status (TR_DET_1 | TR_TRANSL_ONLY | TR_TRANSL_INCL | ((x == 0.0 && y == 0.0 && z == 0.0) ? TR_IDENT : 0)),
	dummy1 (0),
	dummy2 (0),
	dummy3 (0),
	tmx (Geometry::Matrix34::CreateTranslation (Vector3D (x, y, z)))
{
}


constexpr TRANMAT::TRANMAT (ScaleSelector, double x, double y, double z) :
	status (TR_SCALE_INCL | TR_SCALE_ONLY),
	dummy1 (0),
	dummy2 (0),
	dummy3 (0),
	tmx (Geometry::Matrix34::CreateScaling (x, y, z))
{
}


constexpr TRANMAT	TRANMAT::CreateIdentity ()
{
	return TRANMAT (IdentityMatrixSelector);
}


constexpr TRANMAT	TRANMAT::CreateTranslation (double x, double y, double z)
{
	return TRANMAT (TranslationMatrixSelector, x, y, z);
}


namespace Geometry {
constexpr TRANMAT IdentityTranMat = TRANMAT::CreateIdentity ();
}

inline TRANMAT	TRANMAT::CreateRotation (const UnitVector_3D& axis, double angle)
{
	BASTRAN rottran;
	TMBCalcRottran (axis, angle, &rottran);

	Geometry::Matrix33  matr33 (Vector3D (rottran.tmx[0], rottran.tmx[3], rottran.tmx[6]),
								Vector3D (rottran.tmx[1], rottran.tmx[4], rottran.tmx[7]),
								Vector3D (rottran.tmx[2], rottran.tmx[5], rottran.tmx[8]));

	TRANMAT tran;
	tran.tmx.SetMatrix33 (matr33, Vector3D (0.0, 0.0, 0.0));
	tran.FillStatus ();

	return tran;
}

inline TRANMAT	TRANMAT::CreateRotationX (double angle)
{
	if (angle == 0.0)
		return Geometry::IdentityTranMat;

	TRANMAT tran;
	tran.tmx = Geometry::Matrix34::CreateRotationX (angle);

	tran.status = TR_ROTATE_ONLY;

	tran.dummy1 = 0;
	tran.dummy2 = 0;
	tran.dummy3 = 0;

	return tran;
}


inline TRANMAT	TRANMAT::CreateRotationY (double angle)
{
	if (angle == 0.0)
		return Geometry::IdentityTranMat;

	TRANMAT tran;
	tran.tmx = Geometry::Matrix34::CreateRotationY (angle);

	tran.status = TR_ROTATE_ONLY;

	tran.dummy1 = 0;
	tran.dummy2 = 0;
	tran.dummy3 = 0;

	return tran;
}


inline TRANMAT	TRANMAT::CreateRotationZ (double angle)
{
	if (angle == 0.0)
		return Geometry::IdentityTranMat;

	TRANMAT tran;
	tran.tmx = Geometry::Matrix34::CreateRotationZ (angle);

	tran.status = TR_ROTATE_ONLY;

	tran.dummy1 = 0;
	tran.dummy2 = 0;
	tran.dummy3 = 0;

	return tran;
}


constexpr TRANMAT	TRANMAT::CreateScaling (double x, double y, double z)
{
	return TRANMAT (ScaleMatrixSelector, x, y, z);
}


inline void	TRANMAT::SetMatrix (const Geometry::Matrix34& other)
{
	tmx = other;
	FillStatus ();
}


inline void	TRANMAT::SetOffset3D (const Vector3D& vec)
{
	tmx.SetOffsetVector3d (vec);
	if (!vec.IsNear (Vector3D (0.0, 0.0, 0.0))) {
		if (IsIdentity ()) {
			status |= TR_TRANSL_ONLY;
			status &= ~TR_IDENT;
		}
		status |= TR_TRANSL_INCL;
	} else {
		status &= ~TR_TRANSL_INCL;
		status &= ~TR_TRANSL_ONLY;
	}
}


inline bool		TRANMAT::IsIdentity () const
{
	return (status & TR_IDENT) != 0;
}


inline bool		TRANMAT::IsSingular () const
{
	return (status & TR_SINGULAR) != 0;
}


inline bool		TRANMAT::IsTranslationOnly () const
{
	return (status & TR_TRANSL_ONLY) != 0;
}


inline bool		TRANMAT::IsRotationOnly () const
{
	return (status & TR_ROTATE_ONLY) != 0;
}


inline bool		TRANMAT::IsScalingOnly () const
{
	return (status & TR_SCALE_ONLY) != 0;
}


inline bool		TRANMAT::HasMirror () const
{
	return (status & TR_MIRROR) != 0;
}


inline bool		TRANMAT::HasTranslation () const
{
	return (status & TR_TRANSL_INCL) != 0;
}


inline bool		TRANMAT::HasScaling () const
{
	return (status & TR_SCALE_INCL) != 0;
}


inline GSErrCode	TRANMAT::Read (GS::IChannel& ic)
{
	GSErrCode err = ic.Read (status);
	if (err == NoError)
		err = tmx.Read_array (ic);
	return err;
}


inline GSErrCode	TRANMAT::Write (GS::OChannel& oc) const
{
	GSErrCode err = oc.Write (status);
	if (err == NoError)
		err = tmx.Write_array (oc);
	return err;
}

#endif
