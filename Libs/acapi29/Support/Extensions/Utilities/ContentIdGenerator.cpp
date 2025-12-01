#include "ContentIdGenerator.hpp"

// GSRoot
#include "MD5Channel.hpp"
#include "MemoryIChannel32.hpp"
#include "SetPlatformProtocol.hpp"
#include "UniString.hpp"


Extensions::Utility::ContentSerializer::~ContentSerializer (void)
{
}


Extensions::Utility::ContentIdGenerator::ContentIdGenerator (void)
{
}


Extensions::Utility::ContentIdGenerator::~ContentIdGenerator (void)
{
}


GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const Extensions::Utility::ContentSerializer& contentSerializer) const
{
	IO::MD5Channel md5Channel;
	IO::SetPlatformOProtocol (md5Channel, GS::Win_Platform_Sign);

	GSErrCode errorCode = contentSerializer.WriteContentForIdGeneration(md5Channel);
	if (errorCode != NoError) {
		DBBREAK ();

		GS::Guid guid;
		guid.Generate();

		return guid;
	}

	MD5::FingerPrint fingerPrint;
	md5Channel.Finish (&fingerPrint);

	GS::MemoryIChannel32 mic (reinterpret_cast<const char*> (&fingerPrint.data), sizeof (fingerPrint.data));
	IO::SetPlatformIProtocol (mic, GS::Win_Platform_Sign);
	GS::Guid guid;
	guid.Read (mic);

	return guid;
}


/* static */
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const GS::Guid& guid)
{
	GS::Array<GS::Guid> guids;
	guids.Push(guid);

	return Generate(guids);
}


/* static */
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const GS::Guid& guid1, const GS::Guid& guid2)
{
	GS::Array<GS::Guid> guids;
	guids.Push(guid1);
	guids.Push(guid2);

	return Generate(guids);
}


/* static */
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const GS::Array<GS::Guid>& guids)
{
	if (guids.IsEmpty ())
		return GS::NULLGuid;

	class : public Extensions::Utility::ContentSerializer
	{
	public:
		GS::Array<GS::Guid> guids;

	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			for (const auto& guid : guids)
				guid.Write(oc);

			return NoError;
		}
	} contentSerializer;

	contentSerializer.guids = guids;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate(contentSerializer);
}


/* static */
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const GS::UniString& str)
{
	class: public Extensions::Utility::ContentSerializer
	{
	public:
		GS::UniString str;

	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			str.Write (oc);
			return NoError;
		}
	} contentSerializer;

	contentSerializer.str = str;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate (contentSerializer);
}


/* static */
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const GS::Guid& guid1, const UIndex& index)
{
	class: public Extensions::Utility::ContentSerializer
	{
	public:
		GS::Guid guid1;
		UIndex index;

	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			guid1.Write (oc);
			oc.Write (index);

			return NoError;
		}
	} contentSerializer;

	contentSerializer.guid1 = guid1;
	contentSerializer.index = index;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate (contentSerializer);
}


/* static */
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const GS::Guid& guid1, const GS::Guid& guid2, const UIndex& index)
{
	class: public Extensions::Utility::ContentSerializer
	{
	public:
		GS::Guid guid1;
		GS::Guid guid2;
		UIndex index;

	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			guid1.Write (oc);
			guid2.Write (oc);
			oc.Write (index);

			return NoError;
		}
	} contentSerializer;

	contentSerializer.guid1 = guid1;
	contentSerializer.guid2 = guid2;
	contentSerializer.index = index;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate (contentSerializer);
}


/*static*/
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const tm& time, const GS::UniString& id)
{
	class: public Extensions::Utility::ContentSerializer
	{
	public:
		tm time;
		GS::UniString id;
	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			oc.Write (time.tm_sec);
			oc.Write (time.tm_min);
			oc.Write (time.tm_hour);
			oc.Write (time.tm_mday);
			oc.Write (time.tm_mon);
			oc.Write (time.tm_year);
			oc.Write (time.tm_wday);
			oc.Write (time.tm_yday);
			oc.Write (time.tm_isdst);
			id.Write (oc);

			return NoError;
		}
	} contentSerializer;

	contentSerializer.time = time;
	contentSerializer.id = id;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate (contentSerializer);
}


/*static*/
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (short r, short g, short b)
{
	class: public Extensions::Utility::ContentSerializer
	{
	public:
		short r, g, b;

	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			oc.Write (r);
			oc.Write (g);
			oc.Write (b);

			return NoError;
		}
	} contentSerializer;

	contentSerializer.r = r;
	contentSerializer.g = g;
	contentSerializer.b = b;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate (contentSerializer);
}


/*static*/
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (Int32 intVal, short shortVal)
{
	class: public Extensions::Utility::ContentSerializer
	{
	public:
		Int32 intVal;
		short shortVal;

	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			oc.Write (intVal);
			oc.Write (shortVal);

			return NoError;
		}
	} contentSerializer;

	contentSerializer.intVal = intVal;
	contentSerializer.shortVal = shortVal;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate (contentSerializer);
}


GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const GS::Guid& guid, const StructureComponentId& structureComponentId, bool flag)
{
	class : public Extensions::Utility::ContentSerializer
	{
	public:
		GS::Guid guid;
		StructureComponentId structureComponentId;
		bool flag;

	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			guid.Write (oc);
			structureComponentId.Write (oc);
			oc.Write (flag);

			return NoError;
		}
	} contentSerializer;

	contentSerializer.guid = guid;
	contentSerializer.structureComponentId = structureComponentId;
	contentSerializer.flag = flag;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate (contentSerializer);
}



GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const GS::Guid& guid1, const GS::Guid& guid2, const StructureComponentId& structureComponentId)
{
	class : public Extensions::Utility::ContentSerializer
	{
	public:
		GS::Guid guid1;
		GS::Guid guid2;
		
		StructureComponentId structureComponentId;

	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			guid1.Write (oc);
			guid2.Write (oc);
			structureComponentId.Write (oc);

			return NoError;
		}
	} contentSerializer;

	contentSerializer.guid1 = guid1;
	contentSerializer.guid2 = guid2;
	contentSerializer.structureComponentId = structureComponentId;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate (contentSerializer);
}


/* static */
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const GS::Guid& guid, const GS::UniString& string)
{
	class: public Extensions::Utility::ContentSerializer
	{
	public:
		GS::Guid guid;
		GS::UniString string;

	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			guid.Write (oc);
			string.Write (oc);

			return NoError;
		}
	} contentSerializer;

	contentSerializer.guid = guid;
	contentSerializer.string = string;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate (contentSerializer);
}


/* static */
GS::Guid Extensions::Utility::ContentIdGenerator::Generate (const GS::Guid& guid1, const GS::Guid& guid2, const GS::UniString& string)
{
	class: public Extensions::Utility::ContentSerializer
	{
	public:
		GS::Guid guid1;
		GS::Guid guid2;
		GS::UniString string;

	public:
		virtual GSErrCode WriteContentForIdGeneration (GS::OChannel& oc) const
		{
			guid1.Write (oc);
			guid2.Write (oc);
			string.Write (oc);

			return NoError;
		}
	} contentSerializer;

	contentSerializer.guid1 = guid1;
	contentSerializer.guid2 = guid2;
	contentSerializer.string = string;

	Extensions::Utility::ContentIdGenerator contentIdGenerator;
	return contentIdGenerator.Generate (contentSerializer);
}


/* static */
GS::Guid Extensions::Utility::ContentIdGenerator::GenerateWithClassInfo (const GS::Guid& classInfoId, const GS::Guid& ifcGuid)
{
	return Extensions::Utility::ContentIdGenerator::Generate (classInfoId, ifcGuid);
}