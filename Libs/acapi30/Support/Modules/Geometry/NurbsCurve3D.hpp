
#ifndef NURBSCURVE3D_H
#define NURBSCURVE3D_H

#include "NurbsCurveBase.hpp"
#include "NurbsCurve2D.hpp"
#include "Box3DData.h"
#include "Vector3D.hpp"

namespace Geometry {
	class GEOMETRY_DLL_EXPORT NurbsCurve3D : public Geometry::NurbsCurveBase <Point3D, Box3D, Vector3D> {
		DECLARE_ROOT_CLASS_INFO
	public:

		using CoordinateType = Point3D;
		using BoxDataType = Box3D;
		using VectorType = Vector3D;

		NurbsCurve3D () = default;
		NurbsCurve3D (const GS::Array<Point3D>& controlPoints_, UInt32 degree_);
		NurbsCurve3D (const GS::Array<Point3D>& controlPoints_, const GS::Array<double>& knotvector_, const GS::Array<double>& weights_ = GS::Array<double>());
		NurbsCurve3D (const Geometry::NurbsCurve2D& n2, double z = 1.0); //For debug // by default embeds into the z = 1 plane

		virtual GSErrCode Read		(GS::IChannel& ic) override;
		virtual GSErrCode Write		(GS::OChannel& oc) const override;
		virtual GSErrCode ReadXML	(GS::XMLIChannel& ic) override;
		virtual GSErrCode WriteXML	(GS::XMLOChannel& oc) const override;

		void	DumpSegmentedGDL (UInt32 subdivCount) const;

		static const char* XMLTag_NurbsCurve3D;
	};
} //namespace Geometry
#endif