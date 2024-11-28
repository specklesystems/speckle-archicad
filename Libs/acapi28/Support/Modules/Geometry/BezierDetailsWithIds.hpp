#ifndef BEZIER_DETAIL_IDS_H_
#define BEZIER_DETAIL_IDS_H_

#include "BezierDetails.hpp"

namespace Geometry {

class GEOMETRY_DLL_EXPORT BezierDetailsWithIds {
private:

	BezierDetails details;
	GS::Array<UInt32> ids;
	UInt32 latestId = 0;

public:
	BezierDetailsWithIds () = default;
	BezierDetailsWithIds (const BezierDetails& details);

	const BezierDetailsWithIds& operator= (const BezierDetails& details);

	const Point2D*	GetCoordsPtr () const;
	const DirType*	GetDirsPtr () const;
	Int32			GetCoordsNum () const;

	void CopyAndMatch (const BezierDetails& other);

	void Append (const Point2D& point, const DirType& dir);
	void Prepend (const Point2D& point, const DirType& dir);

	void InsertAt (const Point2D& point, const DirType& dir, UInt32 index);
	void DeleteAt (UInt32 index);

	GS::Optional<Point2D> GetPoint (UInt32 index) const;
	GS::Optional<DirType> GetDir (UInt32 index) const;
	GS::Optional<UInt32>  GetId (UInt32 index) const;

	GS::Optional<Point2D> GetPointById (UInt32 id) const;
	GS::Optional<DirType> GetDirById (UInt32 id) const;
	GS::Optional<UInt32>  GetIndexById (UInt32 id) const;

	GS::Optional<UInt32> GetIdAtPoint (const Point2D& point) const;

	void ForEach (std::function<void (const Point2D&, const DirType&, UInt32)> func) const;

	bool IsClosed () const;
	void SetClosed (bool value);

	const BezierDetails& GetBezierDetails () const;
	void SetBezierDetails (const BezierDetails& details, bool match = false);

	void Clear ();

	GSErrCode	Read (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;

private:
	void ResetIds ();
	UInt32 GenId ();

	GS::Optional<UInt32> GetIdAtPoint (const GS::Array<Point2D>& inArray, const GS::Array<UInt32> inId, const Point2D& point) const;

	GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
};

}


#endif // BEZIER_DETAIL_IDS
