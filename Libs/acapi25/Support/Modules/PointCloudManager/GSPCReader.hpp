// *********************************************************************************************************************
// Description:		Implementation of IStreamingPointSource, which reads the GSPC point cloud data file format.
//					For the details of the file format, see 
//					http://wiki/w/B-298_Displaying_Point_Clouds_on_Floor_Plan/Overall_Model#Point_cloud_f.C3.A1jlok_form.C3.A1tuma
//					
// Module:			PointCloudManager
// Namespace:		PointCloud
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#ifndef	GSPCREADER_HPP
#define	GSPCREADER_HPP

// from PointCloud
#include "IStreamingPointCloudSource.hpp"

// from PointCloudManager
#include "ContentIDReader.hpp"
#include "PointCloudManagerDefinitions.hpp"

namespace PointCloud {


// ---------------------------------------------------------------------------------------------------------------------
// File header data type.
// ---------------------------------------------------------------------------------------------------------------------
struct GSPCHeader
{
public:
	static const UInt32 FirstVersion	= 1;
	static const UInt32 CurrentVersion	= 2;

	static const USize	SignatureSize	= 4;

	char signature[SignatureSize];
	UInt32 version;

	// Creates an invalid header.
	GSPCHeader ();

	GSErrCode Read (GS::IChannel& ic);

	// Returns if the header is a valid GSPC file header.
	bool IsValid () const
	{
		return version >= FirstVersion
			&& version <= CurrentVersion
			&& !DeprecatedVersion ()

			&& signature[0] == 'G'
			&& signature[1] == 'S'
			&& signature[2] == 'P'
			&& signature[3] == 'C';
	}

	// version 1 is deprecated since it does not contain the bounding box
	bool DeprecatedVersion () const
	{
		return version == 1;
	}
};


// ---------------------------------------------------------------------------------------------------------------------
// GSPC File format reader.
// ---------------------------------------------------------------------------------------------------------------------
class POINTCLOUDMANAGER_DLL_EXPORT GSPCReader: public IStreamingPointCloudSource
{
public:
	GSPCReader (const IO::Location& fileLocation);
	virtual ~GSPCReader ();

	bool				IsValidFile		() const;
	PC::Box				GetBoundingBox	() const;

	virtual	UInt32		GetNumberOfPoints () const			override;
	virtual	bool		DoStreaming (Callback& callback)	override;

	PC::ContentId		GetContentId () const;

private:
	GSPCHeader			fileHeader;
	USize				numberOfPoints;
	PC::Box				boundingBox;

	PC::ContentId		contentId;
	ContentIDReader		reader;

	GSErrCode	ParseFile	(IStreamingPointCloudSource::Callback& callback);
	GSErrCode	ReadHeaders (GS::IChannel& ic);

	template <typename ExtendedHeaderT>
	GSErrCode	ReadExtendedHeader (ExtendedHeaderT& outExtendedHeader, UInt64& remainingDataSize, GS::IChannel& ic);
};

} // namespace PointCloud

#endif // GSPCREADER_HPP