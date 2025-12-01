#if !defined _CONTENTIDGENERATOR_HPP_
#define _CONTENTIDGENERATOR_HPP_

#pragma once

// GSRoot
#include "Definitions.hpp"
#include "MemoryOChannel32.hpp"
#include "GSGuid.hpp"

// GSUtils
#include "StructureComponentId.hpp"

namespace Extensions {

namespace Utility {


class ContentSerializer
{
public:
	virtual ~ContentSerializer (void);

	virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const = 0;
};


class ContentIdGenerator
{
public:
	ContentIdGenerator (void);
	virtual ~ContentIdGenerator (void);

	GS::Guid Generate (const ContentSerializer& contentSerializer) const;

	static GS::Guid Generate (const GS::Guid& guid);
	static GS::Guid Generate (const GS::Guid& guid1, const GS::Guid& guid2);
	static GS::Guid Generate (const GS::Array<GS::Guid>& guids);
	static GS::Guid Generate (const GS::UniString& string);

	static GS::Guid Generate (const GS::Guid& guid, const UIndex& index);
	static GS::Guid Generate (const GS::Guid& guid1, const GS::Guid& guid2, const UIndex& index);
	static GS::Guid Generate (const tm& time, const GS::UniString& id);
	static GS::Guid Generate (short r, short g, short b);
	static GS::Guid Generate (Int32 intVal, short shortVal);

	static GS::Guid Generate (const GS::Guid& guid, const StructureComponentId& structureComponentId, bool flag);
	static GS::Guid Generate (const GS::Guid& guid1, const GS::Guid& guid2, const StructureComponentId& structureComponentId);

	static GS::Guid Generate (const GS::Guid& guid1, const GS::UniString& string);
	static GS::Guid Generate (const GS::Guid& guid1, const GS::Guid& guid2, const GS::UniString& string);

	template<class ContentType>
	static GS::Guid Generate (const GS::Array<ContentType>& arrayOfContents);

	static GS::Guid GenerateWithClassInfo (const GS::Guid& classInfoId, const GS::Guid& ifcGuid);
};


} //Utility

} //Extensions


/*static*/
template<class ContentType>
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const GS::Array<ContentType>& arrayOfContents)
{
	class: public Extensions::Utility::ContentSerializer
	{
	public:
		const GS::Array<ContentType>* arrayOfContents;

	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			for (const auto& content : *arrayOfContents) {
				oc.Write (content);
			}

			return NoError;
		}
	} contentSerializer;

	contentSerializer.arrayOfContents = &arrayOfContents;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate (contentSerializer);
}


#endif //_CONTENTIDGENERATOR_HPP_
