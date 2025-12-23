// *********************************************************************************************************************
// Description:
//
// Module:			GSXML
// Contact person:	TaB
//
// *********************************************************************************************************************

#ifndef XMLREADWRITECHECK_HPP
#define XMLREADWRITECHECK_HPP

#pragma once

// from GSRoot
#include "XMLChannel.hpp"

// from IO
#include "Location.hpp"
#include "FileSystem.hpp"

// from GSXML
#include "GSXMLInterface.hpp"
#include "GSXMLDOMBuilder.hpp"
#include "GSXMLDOMReader.hpp"

namespace GeneralTestFunction {

	typedef std::function<GSErrCode (GS::XMLOChannel&)> XMLWriteProcess;
	typedef std::function<GSErrCode (GS::XMLIChannel&)> XMLReadProcess;
	typedef std::function<bool ()>						XMLCheckProcess;


	GSXMLUTILS_EXPORT
		IO::Location GetLocationInTemporaryFolder ();


	GSXMLUTILS_EXPORT
		GSErrCode WriteToXMLFile (const IO::Location& location, const XMLWriteProcess& writeProcess);


	template <class ClassToTest>
	GSErrCode WriteObjectToXMLFile (const IO::Location& location, const ClassToTest& object)
	{
		XMLWriteProcess writeProcess = [&object] (GS::XMLOChannel& oc) -> GSErrCode {
			return object.WriteXML (oc);
		};
		return WriteToXMLFile (location, writeProcess);
	}


	GSXMLUTILS_EXPORT
		GSErrCode ReadFromXMLFile (const IO::Location& location, const XMLReadProcess& readProcess);


	template <class ClassToTest>
	GSErrCode ReadObjectFromXMLFile (const IO::Location& location, ClassToTest& object)
	{
		XMLReadProcess readProcess = [&object] (GS::XMLIChannel& ic) -> GSErrCode {
			return object.ReadXML (ic);
		};
		return ReadFromXMLFile (location, readProcess);
	}


	GSXMLUTILS_EXPORT
		GSErrCode XMLReadWriteTest (const XMLWriteProcess& writeProcess, const XMLReadProcess& readProcess, const XMLCheckProcess& checkProcess);


	template <class ClassToTest>
	GSErrCode XMLReadWriteObjectTest (const ClassToTest& object, const std::function<bool (const ClassToTest& object1, const ClassToTest& object2)>& isEqual)
	{
		IO::Location location = GetLocationInTemporaryFolder ();

		GSErrCode err = WriteObjectToXMLFile (location, object);
		ClassToTest readObject;
		if (err == NoError)
			err = ReadObjectFromXMLFile (location, readObject);

		if (err == NoError)
			err = isEqual (object, readObject) ? NoError : Error;

		IO::fileSystem.Delete (location);
		return err;
	}


	template <class ClassToTest>
	GSErrCode XMLReadWriteObjectTest (const ClassToTest& object)
	{
		return XMLReadWriteObjectTest<ClassToTest> (object, [&] (const ClassToTest& object1, const ClassToTest& object2) -> bool {
			return object1 == object2;
		});
	}


	template <class ClassToTest>
	GSErrCode XMLTransferContentForTesting (const ClassToTest& fromObject, ClassToTest& toObject)
	{
		GSXML::DOMBuilder domBuilder ("Root");

		GSErrCode err = domBuilder.WriteStartDocument ();
		GSXML::DOMReader domReader (domBuilder.GetActualNode (), "Root");
		if (err == NoError)
			err = fromObject.WriteXML (domBuilder);
		if (err == NoError)
			err = domBuilder.WriteEndDocument ();
		if (err == NoError)
			err = toObject.ReadXML (domReader);

		return err;
	}


	template <class ClassToTest>
	GSErrCode XMLReadWriteInMemoryTest (const ClassToTest& object)
	{
		ClassToTest readObject;
		GSErrCode err = XMLTransferContentForTesting (object, readObject);
		if (err == NoError)
			err = (object == readObject) ? NoError : Error;
		return err;
	}


}

#endif	// XMLREADWRITECHECK_HPP
