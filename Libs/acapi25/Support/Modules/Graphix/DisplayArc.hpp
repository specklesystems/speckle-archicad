#ifndef DISPLAYARC_HPP
#define DISPLAYARC_HPP

// from GSRoot
#include "Point.hpp"
#include "Rect.hpp"

// from Graphix
#include "GraphixDefinitions.hpp"

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
	const GS::Point<float> center;

	const float xRadius;
	const float yRadius;

	const GS::Point<float> begCoordinate;
	const GS::Point<float> endCoordinate;

	float begAngle;
	float deltaAngle; //sign of the deltaAngle determines the direction of the arc

	const bool isFullEllipse;

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

	GS::Rect<float>						GetFullEllipseBoundingRect	() const;
	const GS::Array<GS::Point<float>>	GetSegmentation				(UInt32 pointNum) const;

	DisplayArc				Scale (float scaleFactor) const;

private:
	const GS::Point<float>	GetPointFromAngle (float angle) const;

public:
	enum Reflection {
		NotReflected = 0,
		Reflected	 = 1
	};

	enum class MatchingPointInterpretation {
		AsZeroLengthArc = 0,
		AsFullArc = 1
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