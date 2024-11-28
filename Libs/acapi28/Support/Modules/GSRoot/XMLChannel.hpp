// *****************************************************************************
//
//									XML Channel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	CsP
//
// SG compatible
//
// *****************************************************************************

#ifndef	XMLCHANNEL_HPP
#define	XMLCHANNEL_HPP

#include "Definitions.hpp"
#include "Array.hpp"
#include "UniString.hpp"
#include "StringConversion.hpp"

#include <cstddef>

namespace IO {
	class Location;
}

namespace GS {
	class UniString;
	class Guid;

// =============================================================================
//									Types
// =============================================================================

enum XMLNoTopLevelTagType {
	XMLNoTopLevelTag
};

enum XMLTokenType {
	XMLStartTag		= 0x01,
	XMLEndTag		= 0x02,
	XMLOtherTag		= 0x40,
	XMLUnknownTag	= 0x80
};


// =============================================================================
//									XMLOChannel
// =============================================================================

class GSROOT_DLL_EXPORT XMLOChannel {
public:
	enum FloatingPointOutputType	{ Default, FixedPoint, Scientific	};
	enum ErrorStatus				{ Ok, Warning, Error, FatalError	};
private:
	FloatingPointOutputType			m_floatingPointType;
	UIndex							m_precision;									// digits after decimal point, 0 means all

public:
	XMLOChannel	();

	virtual ~XMLOChannel ();

	virtual void		SetXMLShemaVersion (const GS::ClassVersion& shemaVersion)					= 0;
	virtual void		GetXMLShemaVersion (GS::ClassVersion& shemaVersion)							= 0;

	virtual bool		GetLocation (IO::Location& fileLoc)											= 0;

	virtual GSErrCode	WriteStartDocument ()														= 0;
	virtual GSErrCode	WriteEndDocument ()															= 0;

	virtual GSErrCode	WriteStartElement (const char* tagName)										= 0;
	virtual GSErrCode	WriteEndElement	()															= 0;

	virtual GSErrCode	WriteXML (const char* tagName, char c)										= 0;
	virtual GSErrCode	WriteXML (const char* tagName, unsigned char c)								= 0;
	virtual GSErrCode	WriteXML (const char* tagName, bool b);
	virtual GSErrCode	WriteXML (const char* tagName, short s)										= 0;
	virtual GSErrCode	WriteXML (const char* tagName, unsigned short s)							= 0;
	virtual GSErrCode	WriteXML (const char* tagName, int i)										= 0;
	virtual GSErrCode	WriteXML (const char* tagName, unsigned int i)								= 0;
	virtual GSErrCode	WriteXML (const char* tagName, long l)										= 0;
	virtual GSErrCode	WriteXML (const char* tagName, unsigned long l)								= 0;
	virtual GSErrCode	WriteXML (const char* tagName, Int64 i)										= 0;
	virtual GSErrCode	WriteXML (const char* tagName, UInt64 i)									= 0;
	virtual GSErrCode	WriteXML (const char* tagName, float f)										final;
	virtual GSErrCode	WriteXML (const char* tagName, double d)									final;
	virtual GSErrCode	WriteXML (const char* tagName, const char* cStr, UInt32 length = 0);
	virtual GSErrCode	WriteXML (const char* tagName, const GS::UniString& uStr)					= 0;
	virtual GSErrCode	WriteXML (const char* tagName, const GS::Guid& guid)						= 0;

	virtual GSErrCode	WriteXMLTextNode (char c);
	virtual GSErrCode	WriteXMLTextNode (unsigned char c);
	virtual GSErrCode	WriteXMLTextNode (bool b);
	virtual GSErrCode	WriteXMLTextNode (short s);
	virtual GSErrCode	WriteXMLTextNode (unsigned short s);
	virtual GSErrCode	WriteXMLTextNode (int i);
	virtual GSErrCode	WriteXMLTextNode (unsigned int i);
	virtual GSErrCode	WriteXMLTextNode (long l);
	virtual GSErrCode	WriteXMLTextNode (unsigned long l);
	virtual GSErrCode	WriteXMLTextNode (Int64 i);
	virtual GSErrCode	WriteXMLTextNode (UInt64 i);
	virtual GSErrCode	WriteXMLTextNode (float f)													final;
	virtual GSErrCode	WriteXMLTextNode (double d)													final;
	virtual GSErrCode	WriteXMLTextNode (const char* cStr, UInt32 length = 0);
	virtual GSErrCode	WriteXMLTextNode (const GS::UniString& uStr)								= 0;

	virtual GSErrCode	WriteXMLCDATABinToHex (const char* data, UInt32 dataLen);
	GSErrCode			WriteXMLCDATABinToHex (const std::byte* data, UInt32 dataLen);
	virtual GSErrCode	WriteXMLCDATABinToHex (GSHandle data);

	virtual GSErrCode	WriteXMLCDATAString (const char* cStr, UInt32 length = 0);
	virtual GSErrCode	WriteXMLCDATAString (const GS::UniString& uStr)								= 0;

	virtual GSErrCode	WriteXMLVersionAttr (const GS::ClassVersion& cv)							= 0;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, char c)									= 0;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, unsigned char c)						= 0;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, bool b);
	virtual GSErrCode	WriteXMLAttr (const char* attrName, short s)								= 0;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, unsigned short s)						= 0;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, float f)								final;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, double d)								final;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, const char* cStr, UInt32 length = 0);
	virtual GSErrCode	WriteXMLAttr (const char* attrName, Int32 i)								= 0;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, UInt32 i)								= 0;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, Int64 i)								= 0;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, UInt64 i)								= 0;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, const GS::UniString& uStr)				= 0;
	virtual GSErrCode	WriteXMLAttr (const char* attrName, const GS::Guid& guid)					= 0;

	virtual GSErrCode	WriteComment (const GS::UniString& commentText)								= 0;

	void				SetFloatingPointPrecision (FloatingPointOutputType type, UIndex precision)	{ m_floatingPointType = type; m_precision = precision; }

	virtual void		AddMessage			(const GS::UniString& msg)								= 0;
	virtual Int32		GetNumberOfMessage	(void)													= 0;
	virtual void		GetMessage			(Int32 msgIdx, GS::UniString& msg, Int32& lineNum)		= 0;

	virtual ErrorStatus	GetErrorStatus		(void)													= 0;
	virtual void		ClearErrorStatus	(void)													= 0;

	virtual void		SetAutoTabsHint		(bool value);
	virtual void		SetReplaceCR		(bool set);
	virtual bool		GetReplaceCR		(void);
};


// =============================================================================
//									XMLIChannel
// =============================================================================

class GSROOT_DLL_EXPORT XMLIChannel {
public:
	enum ErrorStatus { Ok, Warning, Error, FatalError };

	virtual ErrorStatus		GetErrorStatus		(void) = 0;
	virtual void			ClearErrorStatus	(void) = 0;

	virtual ~XMLIChannel ();

	virtual void SetXMLShemaVersion (const GS::ClassVersion& shemaVersion)	= 0;
	virtual void GetXMLShemaVersion (GS::ClassVersion& shemaVersion) = 0;

	virtual bool		GetLocation		(IO::Location& fileLoc)		= 0;

	virtual XMLTokenType	GetTokenType			(void)	= 0;
	virtual XMLTokenType	GetNextTokenType		(void)	= 0;

	virtual XMLTokenType	GetTokenTypeName		(GS::UniString& name)	= 0;
	virtual XMLTokenType	GetNextTokenTypeName	(GS::UniString& name)	= 0;

	virtual GSErrCode	ReadStartElement (const char* tagName)		= 0;
	virtual GSErrCode	ReadEndElement	(const char* tagName)		= 0;
	virtual GSErrCode	ReadToken (unsigned int tokenType)			= 0;

	virtual bool		HasXMLTag (const char* tagName)					= 0;
	virtual GSErrCode	ReadXML (const char* tagName, char& c)			= 0;
	virtual GSErrCode	ReadXML (const char* tagName, unsigned char& c)	= 0;
	virtual GSErrCode	ReadXML (const char* tagName, bool& b)			= 0;
	virtual GSErrCode	ReadXML (const char* tagName, short& s)			= 0;
	virtual GSErrCode	ReadXML (const char* tagName, unsigned short& s)	= 0;
	virtual GSErrCode	ReadXML (const char* tagName, int& i)			= 0;
	virtual GSErrCode	ReadXML (const char* tagName, unsigned int& i)	= 0;
	virtual GSErrCode	ReadXML (const char* tagName, long& l)			= 0;
	virtual GSErrCode	ReadXML (const char* tagName, unsigned long& l)	= 0;
	virtual GSErrCode	ReadXML (const char* tagName, Int64& i)			= 0;
	virtual GSErrCode	ReadXML (const char* tagName, UInt64& i)		= 0;
	virtual GSErrCode	ReadXML (const char* tagName, float& f)			= 0;
	virtual GSErrCode	ReadXML (const char* tagName, double& d)		= 0;
	virtual GSErrCode	ReadXML (const char* tagName, char* cStr, UInt32 length)		= 0;
	virtual GSErrCode	ReadXML (const char* tagName, GS::UniString& uStr)= 0;
	virtual GSErrCode	ReadXML (const char* tagName, GS::Guid& guid)	= 0;
	virtual GSErrCode	ReadXMLCDATAHexToBin (char* data, UInt32 dataLen);
	GSErrCode			ReadXMLCDATAHexToBin (std::byte* data, UInt32 dataLen);
	virtual GSErrCode	ReadXMLCDATAHexToBin (GSHandle data);
	virtual GSErrCode	ReadXMLCDATAString (char* cStr, UInt32 length = 0);
	virtual GSErrCode	ReadXMLCDATAString (GS::UniString& uStr);

	virtual bool		HasXMLAttr (const char* attrName)						= 0;
	virtual GSErrCode	ReadXMLVersionAttr (GS::ClassVersion& cv)				= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, char& c)				= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, unsigned char& c)	= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, bool& b)				= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, short& s)			= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, unsigned short& s)	= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, float& f)			= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, double& d)			= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, char* cStr, UInt32 length)	= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, Int32& i)			= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, UInt32& i)			= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, Int64& i)			= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, UInt64& i)			= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, GS::UniString& uStr)	= 0;
	virtual GSErrCode	ReadXMLAttr (const char* attrName, GS::Guid& guid)		= 0;

	virtual GS::PlatformSign	GetChannelPlatform (void)						= 0;
	virtual void				SetChannelPlatform (GS::PlatformSign platform)	= 0;

	virtual UInt32		GetActLineNumber	()									= 0;
	virtual void		AddMessage			(const GS::UniString& msg)			= 0;
	virtual Int32		GetNumberOfMessage	(void)								= 0;
	virtual void		GetMessage			(Int32 msgIdx, GS::UniString& msg, Int32& lineNum)	= 0;
};


// =============================================================================
//									XMLDocument
// =============================================================================

class GSROOT_DLL_EXPORT XMLDocument {
private:
	GS::XMLOChannel& ox;

private:
	XMLDocument& operator= (const XMLDocument&); 	// disabled
public:
	XMLDocument (GS::XMLOChannel& oc) : ox (oc)	{ ox.WriteStartDocument (); }
	~XMLDocument ()								{ ox.WriteEndDocument ();	}
};


// =============================================================================
//									XMLTag
// =============================================================================

class GSROOT_DLL_EXPORT XMLTag {
private:
	GS::XMLOChannel& ox;

public:
	class GSROOT_DLL_EXPORT XMLAttribute {
		private:
			char* name;
			char* value;
		public:
			XMLAttribute   ();
			XMLAttribute   (const char *attrName, const char* attrValue);
			XMLAttribute   (const XMLTag::XMLAttribute& source);
			XMLTag::XMLAttribute& operator=	(const XMLTag::XMLAttribute& source);
			~XMLAttribute  ();
			const char* GetName  () const;
			const char* GetValue () const;
	};

	typedef GS::Array<XMLAttribute> XMLAttributeList;
private:
	XMLTag& operator= (const XMLTag&);		// disabled
public:
	XMLTag (GS::XMLOChannel& oc, const char* tagName, const XMLAttributeList* attrList = nullptr);
	~XMLTag ();
};

// =============================================================================
//									XMLITag
// =============================================================================

class GSROOT_DLL_EXPORT XMLITag {
private:
	GS::XMLIChannel& ix;
	GS::UniString tokenName;

private:
	XMLITag& operator= (const XMLITag&);		// disabled

public:
	XMLITag (GS::XMLIChannel& ic, const char* tagName);
	~XMLITag ();

	bool IsNextChildStartTag ();
	bool IsNextChildStartTag (GS::UniString& name);
	bool IsNextChildTagName (const GS::UniString& name);
};

// =============================================================================
//							Read/WriteXML functions
// =============================================================================

inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, char& c)				{ return ic.ReadXML (tagName, c); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, unsigned char& c)	{ return ic.ReadXML (tagName, c); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, bool& b)				{ return ic.ReadXML (tagName, b); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, short& s)			{ return ic.ReadXML (tagName, s); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, unsigned short& s)	{ return ic.ReadXML (tagName, s); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, int& i)				{ return ic.ReadXML (tagName, i); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, unsigned int& i)		{ return ic.ReadXML (tagName, i); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, long& l)				{ return ic.ReadXML (tagName, l); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, unsigned long& l)	{ return ic.ReadXML (tagName, l); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, Int64& l)			{ return ic.ReadXML (tagName, l); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, UInt64& l)			{ return ic.ReadXML (tagName, l); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, float& f)			{ return ic.ReadXML (tagName, f); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, double& d)			{ return ic.ReadXML (tagName, d); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, char* cStr, UInt32 length)	{ return ic.ReadXML (tagName, cStr, length); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, GS::UniString& uStr)			{ return ic.ReadXML (tagName, uStr); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, GS::Guid& guid)				{ return ic.ReadXML (tagName, guid); }

inline GSErrCode	ReadCDATA (GS::XMLIChannel& ic, const char* tagName, char* data, UInt32 dataLen) {
	GS::XMLITag tag (ic, tagName);
	return ic.ReadXMLCDATAHexToBin (data, dataLen);
}

inline GSErrCode	ReadCDATA (GS::XMLIChannel& ic, const char* tagName, GSHandle data) {
	GS::XMLITag tag (ic, tagName);
	return ic.ReadXMLCDATAHexToBin (data);
}

template <class Type>
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Type& arg) { return arg.ReadXML (ic); }

template <class Type>
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* tagName, Type& arg) { return arg.ReadXML (ic, tagName); }

template <class Type, class EnumerableType, class = Enumerable<EnumerableType>>
GSErrCode	ReadArrayXML (GS::XMLIChannel& ix, EnumerableType& enumerableType, const char* mainTagName,
						  const std::function<GSErrCode (GS::XMLIChannel&, Type&)>& reader)
{
	ix.ReadStartElement (mainTagName);

	GS::XMLTokenType tokenType = ix.GetNextTokenType ();

	GSErrCode err = NoError;
	auto inserter = GetInserter (enumerableType);

	while (tokenType != XMLEndTag && err == NoError) {
		Type item;
		err = reader (ix, item);

		if (err != NoError)
			return err;

		inserter (std::move (item));
		tokenType = ix.GetNextTokenType ();
	}

	if (err == NoError) {
		err = ix.ReadEndElement (mainTagName);
	}

	return err;
}


template <class KeyType, class ValueType>
GSErrCode ReadHashTableXML (GS::XMLIChannel& ix, GS::HashTable<KeyType, ValueType>& table, const char* mainTagName, const char* entryTagName,
						const std::function<GSErrCode (GS::XMLIChannel&, KeyType&, ValueType&)>& reader)
{
	ix.ReadStartElement (mainTagName);

	GS::XMLTokenType tokenType = ix.GetNextTokenType ();

	GSErrCode err = NoError;
	while (tokenType == GS::XMLStartTag && err == NoError) {
		err = ix.ReadStartElement (entryTagName);
		KeyType key;
		ValueType value;
		if (err == NoError) {
			err = reader (ix, key, value);
		}
		if (err == NoError) {
			table.Add (key, value);
			err = ix.ReadEndElement (entryTagName);
			tokenType = ix.GetNextTokenType ();
		}
	}
	if (err == NoError) {
		err = ix.ReadEndElement (mainTagName);
	}
	return err;
}

inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, char c)				{ return oc.WriteXML (tagName, c); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, unsigned char c)	{ return oc.WriteXML (tagName, c); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, bool b)				{ return oc.WriteXML (tagName, b); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, short s)			{ return oc.WriteXML (tagName, s); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, unsigned short s)	{ return oc.WriteXML (tagName, s); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, int i)				{ return oc.WriteXML (tagName, i); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, unsigned int i)		{ return oc.WriteXML (tagName, i); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, long l)				{ return oc.WriteXML (tagName, l); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, unsigned long l)	{ return oc.WriteXML (tagName, l); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, Int64 l)			{ return oc.WriteXML (tagName, l); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, UInt64 l)			{ return oc.WriteXML (tagName, l); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, float f)			{ return oc.WriteXML (tagName, f); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, double d)			{ return oc.WriteXML (tagName, d); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, const char* cStr, UInt32 length)	{ return oc.WriteXML (tagName, cStr, length); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, const GS::UniString& uStr)			{ return oc.WriteXML (tagName, uStr); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, const GS::Guid& guid)				{ return oc.WriteXML (tagName, guid); }

inline GSErrCode	WriteCDATA (GS::XMLOChannel& oc, const char* tagName, const char* data, Int32 dataLen) {
	GS::XMLTag tag (oc, tagName);
	return oc.WriteXMLCDATABinToHex (data, dataLen);
}

inline GSErrCode	WriteCDATA (GS::XMLOChannel& oc, const char* tagName, GSHandle data) {
	GS::XMLTag tag (oc, tagName);
	return oc.WriteXMLCDATABinToHex (data);
}

template <class Type>
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Type& arg) { return arg.WriteXML (oc); }

template <class Type>
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName, const Type& arg) { return arg.WriteXML (oc, tagName); }

template <class Type, class EnumerableType, class = Enumerable<EnumerableType>>
static GSErrCode WriteArrayXML (GS::XMLOChannel& ox, const EnumerableType& enumerableType, const char* mainTagName,
								const std::function<GSErrCode (GS::XMLOChannel&, const Type&)>& writer)
{
	ox.WriteStartElement (mainTagName);

	GSErrCode err = NoError;
	for (const auto& item : enumerableType) {
		err = writer (ox, item);
		if (err != NoError)
			return err;
	}

	err = ox.WriteEndElement ();
	if (err != NoError)
		return err;

	return err;
}

template <class KeyType, class ValueType>
GSErrCode WriteHashTableXML (GS::XMLOChannel& ox, const GS::HashTable<KeyType, ValueType>& table, const char* mainTagName, const char* entryTagName,
							const std::function<GSErrCode (GS::XMLOChannel&, const KeyType&, const ValueType&)>& writer)
{
	ox.WriteStartElement (mainTagName);

	GSErrCode err = NoError;
	for (auto it = table.EnumeratePairs (); it != nullptr && err == NoError; ++it) {
		err = ox.WriteStartElement (entryTagName);
		if (err == NoError) {
			err = writer (ox, it->key, it->value);
		}
		if (err == NoError) {
			err = ox.WriteEndElement ();
		}
	}
	if (err == NoError) {
		err = ox.WriteEndElement ();
	}
	return err;
}

}	// namespace GS

#endif	// XMLCHANNEL_HPP
