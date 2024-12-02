#ifndef SECTIONSTRINGCONTENT_HPP
#define SECTIONSTRINGCONTENT_HPP

#pragma once

#include "GSMSectionsExport.h"
#include "UniCHar.hpp"
#include "Object.hpp"

class StringSectionBase;
namespace LPF {
	struct SectionInfo;
}

class GSMSECTIONS_CPP_DLL_EXPORT StringSectionContentObject : public GS::Object
{
public:
	enum class PackedState
	{
		PackedForGSMFile,
		PackedForAPI,
		Unpacked
	};

	StringSectionContentObject ();
	StringSectionContentObject (const GS::UniString& string);
	StringSectionContentObject (const StringSectionContentObject& source);
	~StringSectionContentObject ();

	GS::UniString	GetUniString () const;
	GSErrCode		SetDataFromUniString (const GS::UniString& string);
	GSErrCode		GetDataInHandle (GSHandle* handle, PackedState expectedPackedState) const; //should be private in the long term...

	GSErrCode	Write (GS::OChannel& oc, GS::PlatformSign targetPlatform, LPF::SectionInfo& sectionInfo);
	GSErrCode	Read (GS::IChannel& ic, USize sectLen, LPF::SectionInfo& sectionInfo);

protected:
	GSErrCode	SetDataFromHandle (GSConstHandle handle, PackedState stateOfHandleText);

private:
	GSErrCode	SetDataFromUnpackedHandle (GSConstHandle handle);
	void		DeleteData ();

private:
	GS::UniChar::Layout* stringData;
	USize dataSize;

	friend class StringSectionBase;
};

class GSMSECTIONS_CPP_DLL_EXPORT GDLScriptContent : public StringSectionContentObject
{
public:
	GDLScriptContent ();
	GDLScriptContent (const GS::UniString& string);
	GDLScriptContent (const GDLScriptContent& source);

	virtual GS::Object*			Clone () const override;
	static GDLScriptContent*	SetUpFromHandle (GSConstHandle handle, PackedState stateOfHandleText, GSErrCode* errOut = nullptr); //this should be private in the long term... (or not exist at all..)
};

class GSMSECTIONS_CPP_DLL_EXPORT CommentSectionContent : public StringSectionContentObject
{
public:
	CommentSectionContent ();
	CommentSectionContent (const GS::UniString& string);
	CommentSectionContent (const CommentSectionContent& source);

	virtual GS::Object*				Clone () const override;
	static CommentSectionContent*	SetUpFromHandle (GSConstHandle handle, PackedState stateOfHandleText, GSErrCode* errOut = nullptr); //this should be private in the long term... (or not exist at all..)
};

#endif