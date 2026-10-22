// *********************************************************************************************************************
// 
// HTTPClient MapContent implementations
//
// Contact person:	EP
//
// *********************************************************************************************************************

#ifndef GS_HTTPCLIENT_MULTI_PART_DATA_CONTENT_BUILDER_HPP
#define GS_HTTPCLIENT_MULTI_PART_DATA_CONTENT_BUILDER_HPP

//from GSRoot
#include "HashTable.hpp"
#include "OBinaryChannel.hpp"
#include "String.hpp"
#include "Variant.hpp"

// from module
#include "Content.hpp"

namespace HTTPClient {

namespace StandardContentTypes {

extern const HTTPCLIENT_EXPORTED GS::UniString MultipartFormData;

} // namespace StandardContentTypes

class HTTPCLIENT_EXPORTED MultipartFormDataContentBuilder {
public:
    struct HTTPCLIENT_EXPORTED FileContent {
        GS::UniString   m_fileName;
        GS::String      m_contentType;
        GS::RawData     m_data;
    };

using PartValue = GS::Variant<GS::UniString, GS::RawData, FileContent>;

public:
    MultipartFormDataContentBuilder (GS::Owner<GS::Array<GS::Pair<GS::String, PartValue>>> map);
    MultipartFormDataContentBuilder (GS::Array<GS::Pair<GS::String, PartValue>>&& map);
    MultipartFormDataContentBuilder ();

	void AddPart (const GS::String& name, const GS::UniString& value);
	void AddPart (const GS::String& name, const GS::RawData& value);
	void AddPart (const GS::String& name, const FileContent& value);

	Content GetContent () const;

private:
	void WriteBoundaryLine (GS::OBinaryChannel& oc) const;
    void WriteCloseBoundaryLine (GS::OBinaryChannel& oc) const;
	void WriteContentDispositionHeader (GS::OBinaryChannel& oc, const GS::String& name, const GS::Optional<GS::UniString>& fileName = GS::NoValue) const;
	void WriteContentTypeHeader (GS::OBinaryChannel& oc, const GS::String& contentType) const;

	void WritePart (GS::OBinaryChannel& oc, const GS::String& name, const GS::UniString& value) const;
    void WritePart (GS::OBinaryChannel& oc, const GS::String& name, const GS::RawData& value) const;
    void WritePart (GS::OBinaryChannel& oc, const GS::String& name, const FileContent& value) const;

private:
    GS::Owner<GS::Array<GS::Pair<GS::String, PartValue>>> m_parts;
    const std::string m_boundary;
};

} // namespace HTTPClient

#endif