// *********************************************************************************************************************
// Utility functions for XML serialization
//
// Module:			GSXML
// Namespace:		GSXML
// Contact person:	CsP
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef	_GSXMLINTERFACE_HPP_
#define	_GSXMLINTERFACE_HPP_

#pragma once

// from GSRoot
#include "Array.hpp"
#include "XMLChannel.hpp"
#include "GSException.hpp"
#include "Owner.hpp"

// from GSXML
#include "GSXMLUtilsExport.hpp"

namespace GSXML {
	
	class GSXMLUTILS_EXPORT XercescInitializer {
	public:
		XercescInitializer ();
		virtual ~XercescInitializer ();
	};

	static XercescInitializer xercescInitializer;
	
	DECLARE_EXCEPTION_CLASS (XMLIOChannelException, GS::RunTimeErrorException, ErrIO, GSXMLUTILS_EXPORT);
	DECLARE_EXCEPTION_CLASS (XMLOChannelException, XMLIOChannelException, ErrIO, GSXMLUTILS_EXPORT);
	DECLARE_EXCEPTION_CLASS (XMLIChannelException, XMLIOChannelException, ErrIO, GSXMLUTILS_EXPORT);
	
	enum class ExceptionPolicy {
		DontThrow, Throw
	};

	GSXMLUTILS_EXPORT GS::XMLOChannel*		CreateXMLOChannel (const char*				topLevelTagName,
															   const ExceptionPolicy	exceptionPolicy = ExceptionPolicy::DontThrow);
	GSXMLUTILS_EXPORT GS::XMLOChannel*		CreateXMLOChannel (const GS::XMLNoTopLevelTagType,
															   const ExceptionPolicy	exceptionPolicy = ExceptionPolicy::DontThrow);
	GSXMLUTILS_EXPORT GS::XMLOChannel*		CreateXMLOChannel (const IO::Location&		fileLoc,
															   const char*				topLevelTagName,
															   const ExceptionPolicy	exceptionPolicy = ExceptionPolicy::DontThrow);
	GSXMLUTILS_EXPORT GS::XMLOChannel*		CreateXMLOChannel (const IO::Location&		fileLoc,
															   const GS::XMLNoTopLevelTagType,
															   const ExceptionPolicy	exceptionPolicy = ExceptionPolicy::DontThrow);
	GSXMLUTILS_EXPORT void					DisposeXMLOChannel (GS::XMLOChannel*& oc);

	GSXMLUTILS_EXPORT GS::UniString			ExportOChannelToUniString (GS::XMLOChannel* oc);
	GSXMLUTILS_EXPORT void					ExportOChannel (GS::XMLOChannel* oc, std::function<void (const char*, USize)> doExport);

	class GSXMLUTILS_EXPORT XMLOChannelGuard {
		private:
			GS::XMLOChannel** oc;
			GS::Array<GS::UniString>* messsages;
		public:
			XMLOChannelGuard (GS::XMLOChannel** oc);
			XMLOChannelGuard (GS::XMLOChannel** oc, GS::Array<GS::UniString>* errorMesssages);
			~XMLOChannelGuard ();
	};


	template <class Type>
	GSErrCode	WriteToXMLFile (const IO::Location& xmlFileLoc, const Type& object);


//_____________________________________________________________________________________________________________________


	GSXMLUTILS_EXPORT GS::XMLIChannel*	CreateXMLIChannelFromMemory	(const GS::UniString&	xmlString,
																	 const char*			topLevelTagName,
																	 const ExceptionPolicy	exceptionPolicy = ExceptionPolicy::DontThrow);
	GSXMLUTILS_EXPORT GS::XMLIChannel*	CreateXMLIChannelFromMemory	(const GS::UniString&	xmlString,
																	 const GS::XMLNoTopLevelTagType,
																	 const ExceptionPolicy	exceptionPolicy = ExceptionPolicy::DontThrow);
	GSXMLUTILS_EXPORT GS::XMLIChannel*	CreateXMLIChannelFromMemory	(const unsigned char*	xmlInMemory,
																	 const USize			xmlLength,
																	 const char*			topLevelTagName,
																	 const ExceptionPolicy	exceptionPolicy = ExceptionPolicy::DontThrow);
	GSXMLUTILS_EXPORT GS::XMLIChannel*	CreateXMLIChannelFromMemory	(const unsigned char*	xmlInMemory,
																	 const USize			xmlLength,
																	 const GS::XMLNoTopLevelTagType,
																	 const ExceptionPolicy	exceptionPolicy = ExceptionPolicy::DontThrow);
	GSXMLUTILS_EXPORT GS::XMLIChannel*	CreateXMLIChannel			(const IO::Location&	fileLoc,
																	 const char*			topLevelTagName,
																	 const ExceptionPolicy	exceptionPolicy = ExceptionPolicy::DontThrow);
	GSXMLUTILS_EXPORT GS::XMLIChannel*	CreateXMLIChannel			(const IO::Location&	fileLoc,
																	 const GS::XMLNoTopLevelTagType,
																	 const ExceptionPolicy	exceptionPolicy = ExceptionPolicy::DontThrow);
	GSXMLUTILS_EXPORT void				DisposeXMLIChannel 			(GS::XMLIChannel*& ic);

	class GSXMLUTILS_EXPORT XMLIChannelGuard {
		private:
			GS::XMLIChannel** ic;
			GS::Array<GS::UniString>* messsages;
		public:
			XMLIChannelGuard (GS::XMLIChannel** ic);
			XMLIChannelGuard (GS::XMLIChannel** oc, GS::Array<GS::UniString>* errorMesssages);
			~XMLIChannelGuard ();
	};


	template <class Type>
	GSErrCode	ReadFromXMLFile (const IO::Location& xmlFileLoc, Type& object);


}		// namespace GSXML


// === Inline functions ================================================================================================

template <class Type>
GSErrCode	GSXML::WriteToXMLFile (const IO::Location& xmlFileLoc, const Type& object)
{
	Owner<GS::XMLOChannel> oc (CreateXMLOChannel (xmlFileLoc, GS::XMLNoTopLevelTag));

	if (oc == nullptr)
		return Error;

	return object.WriteXML (*oc);
}


template <class Type>
GSErrCode	GSXML::ReadFromXMLFile (const IO::Location& xmlFileLoc, Type& object)
{
	Owner<GS::XMLIChannel> ic (CreateXMLIChannel (xmlFileLoc, GS::XMLNoTopLevelTag));

	if (ic == nullptr)
		return Error;

	return object.ReadXML (*ic);
}


#endif

