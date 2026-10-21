// *********************************************************************************************************************
// Description:		Hatch Transformation
//
// Module:			Pattern
// Namespace:		Pattern
// Contact person:	RA, KiP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (HATCHTRAN_HPP)
#define HATCHTRAN_HPP

#pragma once


#include "PatternExport.h"

#include "Point2D.hpp"
#include "Sector2DData.h"
#include "Matrix.hpp"


struct TRANMAT;
namespace Geometry {
class Transformation2D;
}

namespace GX {
namespace Pattern {

enum HatchTranType {
	Global		= 0,
	Rotated		= 1,
	Distorted	= 2,
	Centered	= 3
};

enum HatchTranFlags {
	XAxisGlobalOrigo	= 0x0001,
	YAxisGlobalOrigo	= 0x0002,
	GlobalOrigo			= 0x0003,
	UseInnerRadius		= 0x0004,
	GlobalOrientation	= 0x0008,

	FitX				= 0x0010,  // Need to rescale in X direction, the X vector length is the width of the pattern
	FitY				= 0x0020,  // Need to rescale in Y direction, the Y vector length is the height of the pattern
	KeepProportion		= 0x0040,  // The ReScale have to keep the Proportion

	FillAsClockwise		= 0x0100,
	AutoFillDirection	= 0x0200
};

#define	DistortedAndBadGradientDataVersion	1  // Wrong Gradient Vectors in matrix have to convert it
#define DistortedAndCentralVersion 2

class PATTERN_DLL_EXPORT HatchTran {
public:

	HatchTran ();

			void	Reset				(HatchTranType newType = Global);

			unsigned short	GetVersion	() const				{ return version; }
			void	SetVersion	(unsigned short newVersion) 	{ version = newVersion; }
			void	ConvertToNewStyle	(bool isRadialGradient, bool isLinearGradient);

			void	SetFitPattern		(double patternHeight);
			void	SetFitPattern		(double patternHeight, const Coord& start, double angle, bool mirror = false);
			void	SetFitCirclePattern (double patternHeight, const Coord& start, const Coord& origo, bool fillAsClockwise, bool mirror);
			void	SetFitCirclePattern (double patternHeight, const Coord& start, const Coord& origo, bool mirror = false);

			bool	NeedReScale () const				{ return (IsFlag (FitX) || IsFlag (FitY)); }
			void	ReScale				(double strokeX, double strokeY, double motifWidth, double motifHeight, double patternAngle);

			bool	UseLocalOrigo		()	const				{ return !IsFlag (GlobalOrigo); }
			bool	UseGlobalOrigo		() const				{ return IsFlag (GlobalOrigo); }
			void	UseLocalOrigo		(bool useLocalOrigo)	{ SetFlag (GlobalOrigo, !useLocalOrigo); }
			void	UseGlobalOrigo		(bool useGlobalOrigo)	{ SetFlag (GlobalOrigo, useGlobalOrigo); }

			bool	IsDistorted		() const		{ return ((HatchTranType)type == Distorted); }
			bool	IsGlobal		() const		{ return ((HatchTranType)type == Global); }
			bool	IsRotated		() const		{ return ((HatchTranType)type == Rotated); }
			bool	IsCentered		() const		{ return ((HatchTranType)type == Centered); }

			bool	IsFlag		(HatchTranFlags flag) const	{ return (flags & flag) == flag; }
			void	SetFlag		(HatchTranFlags flag)		{ flags |= flag; }
			void	SetFlag		(HatchTranFlags flag, bool setFlag)	{ if (setFlag) flags |= flag; else flags &= ~flag; }
			void	ClearFlag	(HatchTranFlags flag)		{ flags &= ~flag; }
			void	ResetFlags	()							{ flags = 0; }
			Int32	GetFlags	() const					{ return flags; }
			void	SetFlags	(Int32 newFlags)			{ flags = newFlags; }

			HatchTranType	GetType () const	{ return ((HatchTranType)type); }
			void			SetType (HatchTranType type);

			void	SetGlobal			();
			void	SetRotated			(double angle);
			void	SetDistorted		(const Geometry::Matrix<2,2,double>& matrix);
			void	SetCentered			(double radius, const Geometry::Matrix<2,2,double>& matrix);
			void	SetLinearGradient	(const Coord& origo, const Coord& position);
			void	SetRadialGradient	(const Coord& center, double innerR, double outerR);

			void	SetTrafo			(bool global,
										 bool distorted,
										 const Coord& origo,
										 const Geometry::Matrix<2,2,double>& matrix,
										 double gradientInnerRadius);

			void	SetTrafo			(bool distorted,
										 const Coord& origo,
										 const Geometry::Matrix<2,2,double>& matrix);

			void	SetTrafo			(Int32 newFlags,
										 const Coord& origo,
										 const Geometry::Matrix<2,2,double>& matrix,
										 double gradientInnerRadius,
										 bool rotated);

			Coord	GetLocalOrigo	() const							{ return origo; }
			Coord	GetOrigo		() const;
			void	SetOrigo		(const Coord& origo)				{ SetOrigo (origo.x, origo.y); }
			void	SetOrigo		(double x, double y);
			void	SetStartPos		(const Coord& startPos);
			Coord	GetStartPos		() const;

			Coord	GetCenterOrigo	() const;
			void	SetCenterOrigo	(const Coord& centerOrigo);

			void	ProjectOriginToYAxisAlongXAxis ();

			void	SetMatrix		(const Geometry::Matrix<2,2,double>& matrix);
			void	Setup			(const Sector& s1, const Sector& s2);
			void	ResetMatrix		();
			void	GetLocalMatrix	(Geometry::Matrix<2,2,double>& matrix) const;
			void	GetMatrix		(Geometry::Matrix<2,2,double>& matrix) const;

			double	GetXAxisAngle	() const;
			double	GetYAxisAngle	() const;

			void	GetXAxisVector	(Vector& vector) const;
			Vector	GetXAxisVector	() const							{ Vector vector; GetXAxisVector (vector); return vector; }
			void	SetXAxisVector	(const Vector& vector)				{ SetXAxisVector (vector.x, vector.y); }
			void	SetXAxisVector	(double x, double y);
			void	GetYAxisVector	(Vector& vector) const;
			Vector	GetYAxisVector	() const							{ Vector vector; GetYAxisVector (vector); return vector; }
			void	SetYAxisVector	(const Vector& vector)				{ SetYAxisVector (vector.x, vector.y); }
			void	SetYAxisVector	(double x, double y);

			double	GetXAxisLength	() const;
			void	SetXAxisLength	(double length);
			double	GetYAxisLength	() const;
			void	SetYAxisLength	(double length);

			void	GetXAxisEndPoint	(Coord& point, double scale = 1) const;
			Coord	GetXAxisEndPoint	(double scale = 1) const		{ Coord	point; GetXAxisEndPoint (point, scale); return point; }
			void	SetXAxisEndPoint	(const Coord& point, double scale = 1);
			void	GetYAxisEndPoint	(Coord& point, double scale = 1) const;
			Coord	GetYAxisEndPoint	(double scale = 1) const		{ Coord	point; GetYAxisEndPoint (point, scale); return point; }
			void	SetYAxisEndPoint	(const Coord& point, double scale = 1);

			void	SetLocalInnerRadius	(const double radius);
			void	SetInnerRadius		(const double radius);
			double	GetInnerRadius		() const;
			void	SetOuterRadius		(const double radius);
			double	GetOuterRadius		() const;

			void			SetMatrix			(const double (&m)[4])			{ for (ULong i = 0; i < 4; ++i) mtx[i] = m[i]; }
			const double*	GetMatrix			(void) const					{ return mtx; }
			double*			GetMatrix			(void)							{ return mtx; }

			void	Transform		(const Geometry::Transformation2D& tran, bool changeType);
			void	Transform		(const TRANMAT& tran, bool changeType);
			void	Move			(const Vector& offset, bool changeType)			{ Move (offset.x, offset.y, changeType); }
			void	Move			(double offsetX, double offsetY, bool changeType);
		 	void	Scale			(double scale, bool changeType)					{ Scale (scale, scale, changeType); }
			void	Scale			(double scaleX, double scaleY, bool changeType);
			void	Rotate			(double angle, bool changeType);
			void	Mirror			(bool xAxis, bool yAxis, bool changeType);

			void	ChangeXToOrtogonal	();
			void	ChangeYToOrgogonal	();

			bool	IsNear			(const HatchTran& other) const;

			bool	operator==		(const HatchTran& other) const;

			ULong	GenerateHashValue	() const;

			bool	Check				() const;
			bool	CheckGlobal			() const;
			bool	CheckRotated		() const;
			bool	CheckDistorted		() const;
			bool	CheckCentered		() const;
			bool	CheckRepresentableValues () const;

			bool	CheckAndFix			();

			void	IVSwap				(GS::PlatformSign inplatform, GS::PlatformSign toplatform);

			GSErrCode	WriteXML		(GS::XMLOChannel& oc) const;
			GSErrCode	ReadXML			(GS::XMLIChannel& ic);
			GSErrCode	Write			(GS::OChannel& oc) const;
			GSErrCode	Read			(GS::IChannel& ic);

public:
			bool	IsBadGradientDataVersion	() const			{ return (version <= DistortedAndBadGradientDataVersion); }

protected:
			unsigned short	type;
			unsigned short	version;
			Int32			flags;
			Coord			origo;						//2*double
			double			mtx[4];
			double			innerRadius;
};

} // namespace Pattern
} // namespace GX

#endif
