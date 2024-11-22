// *********************************************************************************************************************
// Description:		Conversion of an XML DOM
//
// Module:			GSXMLUtils
// Namespace:		GSXML
// Contact person:	KKr
//
// SG compatible
// *********************************************************************************************************************

#include "Definitions.hpp"
#include "GSXMLUtilsExport.hpp"

#ifndef	_GSXML_DOM_CONVERSION_HPP_
#define	_GSXML_DOM_CONVERSION_HPP_

namespace GS {
	class ObjectState;
	class UniString;
	class XMLIChannel;
	class XMLOChannel;
}

namespace xercesc_3_0 {
	class DOMNode;
}

namespace xercesc = xercesc_3_0;

namespace GSXML {

class GSXMLUTILS_EXPORT TypeInfoProvider {
public:
	enum TagValueSelector {
		FieldNames,
		TypeNames
	};

	TypeInfoProvider ();
	virtual ~TypeInfoProvider ();

	virtual bool			 AreListsHomogeneous () const { return false; }
	virtual TagValueSelector GetTagContent		 () const { return FieldNames; }
	virtual const char*		 GetAttributeName	 () const = 0;

	virtual const char* GetBoolTypeName			 () const = 0;
	virtual const char* GetIntTypeName			 () const = 0;
	virtual const char* GetUIntTypeName			 () const = 0;
	virtual const char* GetRealTypeName			 () const = 0;
	virtual const char* GetStringTypeName		 () const = 0;
	virtual const char* GetObjectTypeName		 () const = 0;
	virtual const char* GetListTypeName			 () const = 0;
	virtual const char* GetListValueTag			 () const { return nullptr; }
	virtual const char* GetListSubtypeAttribute  () const { return nullptr; }
};

GSXMLUTILS_EXPORT GSErrCode	CreateFromObjectState (const GS::ObjectState& objectState, GS::UniString&   destination, const TypeInfoProvider* attributeProvider = nullptr);
GSXMLUTILS_EXPORT GSErrCode	CreateFromObjectState (const GS::ObjectState& objectState, GS::XMLOChannel&	destination, const TypeInfoProvider* attributeProvider = nullptr);

GSXMLUTILS_EXPORT GSErrCode ConvertToObjectState (const xercesc::DOMNode* xmlDocument, GS::ObjectState& objectState, const TypeInfoProvider* attributeProvider = nullptr);
GSXMLUTILS_EXPORT GSErrCode ConvertToObjectState (const GS::UniString&	  xmlDocument, GS::ObjectState& objectState, const TypeInfoProvider* attributeProvider = nullptr);
GSXMLUTILS_EXPORT GSErrCode ConvertToObjectState (GS::XMLIChannel&		  xmlDocument, GS::ObjectState& objectState, const TypeInfoProvider* attributeProvider = nullptr);

} // namespace GSXML



#endif