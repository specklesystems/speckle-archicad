#ifndef DISPLAYARC_HPP
#define DISPLAYARC_HPP

// from GSRoot
#include "Point.hpp"
#include "Rect.hpp"

// from Graphix
#include "GraphixDefinitions.hpp"

namespace GS {
	class IChannel;
	class OChannel;
	class InputFrame;
	class OutputFrame;
}

namespace NewDisplay {
	
//////////////////////////////////////////////////////
//
//	Arc for graphix display
//
//	Supports ellipse arcs with only horizontal and vertical axes
//
//////////////////////////////////////////////////////


class GRAPHIX_DLL_EXPORT DisplayArc
{
private:
	GS::Point<float> center;

	float xRadius;
	float yRadius;

	GS::Point<float> begCoordinate;
	GS::Point<float> endCoordinate;

	float begAngle;
	float deltaAngle; //sign of the deltaAngle determines the direction of the arc

	bool isFullEllipse;

	DisplayArc (const GS::Point<float>& center, 
				const float				xRadius, 
				const float				yRadius);

	DisplayArc (const GS::Point<float>& center, 
				const float				xRadius, 
				const float				yRadius, 
				const GS::Point<float>& begCoordinate,
				const GS::Point<float>& endCoordinate,
				const float				begAngle,
				const float				deltaAngle,
				bool isFullEllipse = false);

	DisplayArc (const GS::Point<float>& center, 
				const float				xRadius, 
				const float				yRadius, 
				const float				begAngle,
				const float				deltaAngle);

	bool Precondition () const;

public:
	bool					IsFullEllipse	 () const;
	const GS::Point<float>& GetCenter		 () const;
	const GS::Point<float>& GetBegCoordinate () const;
	const GS::Point<float>& GetEndCoordinate () const;
	float					GetBegAngle		 () const;
	float					GetEndAngle		 () const;
	float					GetDeltaAngle	 () const;
	float					GetXRadius		 () const;
	float					GetYRadius		 () const;

	GS::Rect<float>					GetFullEllipseBoundingRect	() const;
	GS::Array<GS::Point<float>>		GetSegmentation				(UInt32 pointNum) const;

	DisplayArc		Scale	(float scaleFactor) const;

	GSErrCode		Read	(GS::IChannel& ic);
	GSErrCode		Write	(GS::OChannel& oc) const;

	bool			IsEqual	(const DisplayArc& other) const;

private:
	const GS::Point<float>	GetPointFromAngle (float angle) const;

	GSErrCode			ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

public:
	enum Reflection {
		NotReflected = 0,
		Reflected	 = 1,

		LastValue = Reflected
	};

	enum class MatchingPointInterpretation {
		AsZeroLengthArc = 0,
		AsFullArc = 1,

		LastValue = AsFullArc
	};

	static DisplayArc CreateFullCircle	(const GS::Point<float>& center, 
										 float radius);
	static DisplayArc CreateCircularArc (const GS::Point<float>& center, 
										 float radius,
										 float begAngle, 
										 float deltaAngle);
	static DisplayArc CreateFullEllipse	(const GS::Point<float>& center, 
										 float xRadius,
										 float yRadius);
	static DisplayArc CreateFullEllipse (float left, 
										 float top, 
										 float right, 
										 float bottom);
	static DisplayArc CreateEllipticArcWithEndPoints
										(const GS::Point<float>& center, 
										 float xRadius,
										 float yRadius,
										 const GS::Point<float>& begCoordinate, 
										 const GS::Point<float>& endCoordinate,
										 Reflection reflection,
										 MatchingPointInterpretation matchingPointInterpretation);
	static DisplayArc CreateEllipticArc (const GS::Point<float>& center, 
										 float xRadius,
										 float yRadius,
										 float begAngle,
										 float deltaAngle);
	static DisplayArc CreateEllipticArc (float left, 
										 float top, 
										 float right, 
										 float bottom, 
										 float begAngle, 
										 float deltaAngle);
private:
	//disabled methods
	
	DisplayArc ();
};

} // namespace NewDisplay

#endif // DISPLAYARC_HPP