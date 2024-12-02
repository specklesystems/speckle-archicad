#ifndef PO_DICTIONARY_HPP
#define PO_DICTIONARY_HPP

#include "GSUtilsExport.h"
#include "Definitions.hpp"
#include "HashTable.hpp"
#include "Pair.hpp"
#include "UniString.hpp"
#include "Channel.hpp"

#include <vector>

namespace IO {
	class File;
}

namespace Localization {

struct DictionaryValue {
	GS::UniString			   translated_string;
	std::vector<GS::UniString> comments;
	std::vector<GS::UniString> extracted_comments;
	std::vector<GS::UniString> references;
};

using DictionaryKey	  = GS::Pair<GS::UniString, GS::UniString>;
using DictionaryEntry = GS::Pair<DictionaryKey, DictionaryValue>;
using DictionaryTable = GS::HashTable<DictionaryKey, DictionaryValue>;


class GSUTILS_DLL_EXPORT_CPP PoDictionary {
	bool isValid;
	bool inited;
	DictionaryTable	dictionary;
	DictionaryTable missingKeys;
	DictionaryTable foundKeys;
	std::vector<GS::UniString> errorMessages;

public:
	enum class TranslationResult
	{
		Succeeded,
		NotFound,
		Error
	};

	PoDictionary ();
	virtual ~PoDictionary ();
	
	GSErrCode			SetPoDictionary (IO::File& inPoDictionary);
	void				SetEmptyPoDictionary (void);
	GSErrCode			WriteMissingToPoDictionary (IO::File& outPoDictionary) const;
	GSErrCode			WriteFoundToPoDictionary (IO::File& outPoDictionary);
	TranslationResult	Translate (const GS::UniString& context, const GS::UniString& inputString, GS::UniString& translated);

	bool		IsValid () const { return isValid; }
	bool		IsInited () const { return inited; }
	UInt64		GetMissingKeysNum () const { return missingKeys.GetSize (); }
	const std::vector<GS::UniString>& GetErrorMessages () const;
};


class GSUTILS_DLL_EXPORT_CPP PoDictionaryWriter {
public:
	PoDictionaryWriter (GS::OChannel& outPoDictionary);
	GSErrCode WriteDictionary (const DictionaryTable& table);
	virtual ~PoDictionaryWriter ();

private:
	GSErrCode WriteString (const GS::UniString& string);
	GS::OChannel& outPoDictionary;
};

}

#endif
