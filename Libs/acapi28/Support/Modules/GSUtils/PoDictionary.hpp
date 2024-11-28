#ifndef PO_DICTIONARY_HPP
#define PO_DICTIONARY_HPP

#include "GSUtilsExport.h"
#include "Definitions.hpp"
#include "HashTable.hpp"
#include "Pair.hpp"
#include "UniString.hpp"
#include "Channel.hpp"
#include "Owner.hpp"

#include <vector>

namespace IO {
	class File;
}

namespace Localization {

struct GSUTILS_DLL_EXPORT_CPP DictionaryValue {
	GS::UniString			   translated_string;
	std::vector<GS::UniString> comments;
	std::vector<GS::UniString> extracted_comments;
	std::vector<GS::UniString> references;
};

using DictionaryKey	  = GS::Pair<GS::UniString, GS::UniString>;
using DictionaryEntry = GS::Pair<DictionaryKey, DictionaryValue>;
using DictionaryTable = GS::HashTable<DictionaryKey, DictionaryValue>;

GSUTILS_DLL_EXPORT void ConvertNewLinesToPoFormat (Localization::DictionaryEntry& entry);
GSUTILS_DLL_EXPORT void ConvertNewLinesFromPoFormat (Localization::DictionaryEntry& entry);

class GSUTILS_DLL_EXPORT_CPP PoDictionary
{
protected:
	DictionaryTable			   dictionary;



public:
	enum class TranslationResult { Succeeded, NotFound, Error };

	PoDictionary () = delete;
	PoDictionary (const DictionaryTable&);
	virtual ~PoDictionary ();

	virtual TranslationResult Translate (const GS::UniString& context, const GS::UniString& inputString, GS::UniString& translated);
};


enum class NewLineCharacterHandling { Change, Keep };

class GSUTILS_DLL_EXPORT_CPP JournaledPoDictionary : public PoDictionary
{
	DictionaryTable			   missingKeys;
	DictionaryTable			   foundKeys;

public:
	JournaledPoDictionary () = delete;
	JournaledPoDictionary (const DictionaryTable&);
	virtual ~JournaledPoDictionary ();

	GSErrCode		  WriteMissingToPoDictionary (IO::File& outPoDictionary, std::function<void (DictionaryEntry&)> converterToPoFormat = &ConvertNewLinesToPoFormat) const;
	GSErrCode		  WriteFoundToPoDictionary (IO::File& outPoDictionary, std::function<void (DictionaryEntry&)> converterToPoFormat = &ConvertNewLinesToPoFormat);
	virtual TranslationResult Translate (const GS::UniString& context, const GS::UniString& inputString, GS::UniString& translated) override;

	UInt64 GetMissingKeysNum () const { return missingKeys.GetSize (); }
};

class PoDictionaryParserImpl;

class GSUTILS_DLL_EXPORT_CPP PoDictionaryParser
{
	
	GS::Owner<PoDictionaryParserImpl> impl;

public:

	PoDictionaryParser (IO::File& inPoDictionary);
	~PoDictionaryParser ();

	GSErrCode								ParseDictionary (std::function<void (DictionaryEntry&)> converterFromPoFormat = &ConvertNewLinesFromPoFormat);
	Localization::DictionaryTable			GetDictionary ();
	const std::vector<GS::UniString>& 		GetErrorMessages () const;
};



class GSUTILS_DLL_EXPORT_CPP PoDictionaryWriter
{
public:
	PoDictionaryWriter (GS::OChannel& outPoDictionary);
	GSErrCode WriteDictionary (const DictionaryTable& table, std::function<void (DictionaryEntry&)> converterToPoFormat = &ConvertNewLinesToPoFormat);

private:
	GSErrCode	  WriteString (const GS::UniString& string);
	GS::OChannel& outPoDictionary;
};

}

#endif
