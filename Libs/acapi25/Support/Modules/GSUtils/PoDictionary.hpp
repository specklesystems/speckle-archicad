#ifndef PO_DICTIONARY_HPP
#define PO_DICTIONARY_HPP

#include "GSUtilsExport.h"
#include "Definitions.hpp"
#include "HashTable.hpp"
#include "Pair.hpp"
#include "UniString.hpp"
#include "Channel.hpp"

typedef GS::Pair<GS::UniString, GS::UniString>		DictionaryKey;
typedef GS::HashTable<DictionaryKey, GS::UniString>	DictionaryTable;

namespace IO {
	class File;
}

namespace Localization {

class GSUTILS_DLL_EXPORT_CPP PoDictionary {
	bool isValid;
	bool inited;
	DictionaryTable	dictionary;
	DictionaryTable missingKeys;
	DictionaryTable foundKeys;
	GS::Array<GS::UniString> errorMessages;

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
	GSErrCode			WriteMissingToPoDictionary (IO::File& outPoDictionary);
	GSErrCode			WriteFoundToPoDictionary (IO::File& outPoDictionary);
	TranslationResult	Translate (const GS::UniString& context, const GS::UniString& inputString, GS::UniString& translated);

	bool		IsValid () const {return isValid;}
	UInt32		GetMissingKeysNum () const {return missingKeys.GetSize ();}
	const GS::Array<GS::UniString>& GetErrorMessages () const;
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
